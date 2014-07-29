/*
 * Copyright (c) 2014 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */

#include <time.h> /* TODO: Remove this header */

typedef struct enhs_info enhs_info_t;

typedef union {
    int32_t int32;
    uint64_t uint64;
    float flt;
    char const * string;
} enhs_item_value_t;

static connector_status_t enhs_setup_csv_data(connector_data_t * const connector_ptr)
{
    enhs_info_t * enhs_info = &connector_ptr->enhs.info;
    static char const csv_header[] = "#DATA,TIMESTAMP,STREAMCATEGORY,STREAMID\n";
    unsigned int const total_bytes = 256;
    connector_status_t status = connector_working;

    status = malloc_data(connector_ptr, total_bytes, (void * *)&enhs_info->csv.data);
    ASSERT_GOTO(status == connector_working, done);

    if (enhs_info->csv.data == NULL)
    {
        connector_debug_line("Error while allocating memory for CSV data");
        status = free_data(connector_ptr, enhs_info);
        ASSERT_GOTO(status == connector_working, done);
        enhs_info = NULL;
        status = connector_no_resource;
        goto done;
    }
    enhs_info->csv.total_size = total_bytes;
    strcpy(enhs_info->csv.data, csv_header);
    enhs_info->csv.free_bytes = total_bytes - sizeof csv_header;
    enhs_info->csv.status = ENHS_CSV_STATUS_PROCESSING;

done:
    return status;
}

STATIC connector_status_t enhs_teardown_csv_data(connector_data_t * const connector_ptr)
{
    connector_status_t status;

    status = free_data(connector_ptr, connector_ptr->enhs.info.csv.data);
    ASSERT_GOTO(status == connector_working, done);
    connector_ptr->enhs.info.csv.data = NULL;
done:
    return status;
}

STATIC connector_status_t enhs_reallocate_csv_data(connector_data_t * const connector_ptr, enhs_info_t * const enhs_info)
{
    unsigned int const old_size = enhs_info->csv.total_size;
    unsigned int const additional_size = 128;
    unsigned int const new_size = old_size + additional_size;
    connector_status_t const status = realloc_data(connector_ptr, old_size, new_size, (void * *) &enhs_info->csv.data);

    ASSERT_GOTO(status == connector_working, done);
    if (enhs_info->csv.data == NULL)
    {
        connector_debug_line("Error when reallocating CSV buffer from %d to %d", enhs_info->csv.total_size, new_size);
    }
    enhs_info->csv.total_size = new_size;
    enhs_info->csv.free_bytes += additional_size;

done:
    return status;
}

STATIC void process_csv_data(char * const csv, enhs_item_value_t const * const value, enhs_value_type_t const type)
{
    switch (type)
    {
        case ENHS_TYPE_INT32:
        {
            sprintf(csv, "%d", value->int32);
            break;
        }
        case ENHS_TYPE_UINT64:
        {
            sprintf(csv, "%lu", value->uint64);
            break;
        }
        case ENHS_TYPE_FLOAT:
        {
            sprintf(csv, "%f", value->flt);
            break;
        }
        case ENHS_TYPE_STRING:
        case ENHS_TYPE_JSON:
        case ENHS_TYPE_GEOJSON:
        {
            connector_bool_t const needs_quotes = string_needs_quotes(value->string);
            unsigned int const temp_csv_size = 128;
            dp_process_string(value->string, csv, temp_csv_size, NULL, needs_quotes, connector_true);
            break;
        }
        case ENHS_TYPE_NONE:
        {
            connector_debug_line("Fatal error, type not set");
            break;
        }
    }
}

STATIC void process_csv_timestamp(connector_data_t * const connector_ptr, char * const csv)
{
    time_t const timestamp = time(NULL);

    UNUSED_PARAMETER(connector_ptr); /* TODO: implement callback for getting timestamp */
    sprintf(csv, "%s,%ld000", csv, timestamp); /* Timestamp is in milliseconds */
}

STATIC void process_csv_stream_category(char * const csv)
{
    strcat(csv, ",metrics");
}

STATIC void process_csv_stream_id(char * const csv, char const * const stream_id)
{
    sprintf(csv, "%s,%s\n", csv, stream_id);
}

STATIC void add_item_to_csv(connector_data_t * const connector_ptr, enhs_item_value_t const * const value, enhs_value_type_t const type)
{
    enhs_info_t * const enhs_info = &connector_ptr->enhs.info;
    char temp_csv[128];
    unsigned int temp_csv_strlen;
    char * const stream_id = enhs_info->stream_id.string;

    process_csv_data(temp_csv, value, type);
    process_csv_timestamp(connector_ptr, temp_csv);
    process_csv_stream_category(temp_csv);
    process_csv_stream_id(temp_csv, stream_id);

    temp_csv_strlen = strlen(temp_csv);

    if (temp_csv_strlen > enhs_info->csv.free_bytes)
    {
        connector_status_t const status = enhs_reallocate_csv_data(connector_ptr, enhs_info);
        ASSERT(status == connector_working);
    }

    enhs_info->csv.free_bytes -= temp_csv_strlen;
    strcat(enhs_info->csv.data, temp_csv);
}

STATIC void enhs_process_item(connector_data_t * const connector_ptr, enhs_item_t const * const element, unsigned int const index)
{
    enhs_info_t * const enhs_info = &connector_ptr->enhs.info;
    enhs_query_fn_t const function = element->getter;
    enhs_value_type_t const type = element->type;
    connector_bool_t item_present = connector_false;
    enhs_item_value_t value;

    ASSERT(function != NULL);
    switch (type)
    {
        case ENHS_TYPE_INT32:
        {
            item_present = function(index, &value.int32);
            break;
        }
        case ENHS_TYPE_UINT64:
        {
            item_present = function(index, &value.uint64);
            break;
        }
        case ENHS_TYPE_FLOAT:
        {
            item_present = function(index, &value.flt);
            break;
        }
        case ENHS_TYPE_STRING:
        {
            item_present = function(index, &value.string);
            break;
        }
        case ENHS_TYPE_JSON:
        {
            item_present = function(index, &value.string);
            break;
        }
        case ENHS_TYPE_GEOJSON:
        {
            item_present = function(index, &value.string);
            break;
        }
        case ENHS_TYPE_NONE:
        {
            connector_debug_line("Fatal error, type not set");
            ASSERT(type != ENHS_TYPE_NONE);
            break;
        }
    }

    if (item_present)
    {
        char * const stream_id = enhs_info->stream_id.string;

        enhs_info->stream_id.len = sprintf(stream_id, "%s/%s", stream_id, element->name);

        add_item_to_csv(connector_ptr, &value, type);
    }
}

static char const * get_remaining_path(char const * const path)
{
    char const * remaining_path = NULL;
    static char const * const empty_path = "";

    if (strchr(path, '/') != NULL)
    {
        remaining_path = strchr(path, '/') + 1;
    }
    else
    {
        remaining_path = empty_path;
    }

    return remaining_path;
}

STATIC void enhs_process_group_items(connector_data_t * const connector_ptr, unsigned int const index, enhs_item_t const * const * const items_array, unsigned int const array_size, char const * const path)
{
    enhs_info_t * const enhs_info = &connector_ptr->enhs.info;
    unsigned int const stream_id_len = enhs_info->stream_id.len;
    char * const p_original_stream_id_end = &enhs_info->stream_id.string[stream_id_len];
    connector_bool_t const handle_all = path[0] == '\0' ? connector_true : connector_false;
    unsigned int i;

    for (i = 0; i < array_size; i++)
    {
        enhs_item_t const * const item = items_array[i];
        unsigned int const name_len = strlen(item->name);

        if (handle_all || strncmp(path, item->name, name_len) == 0)
        {
            enhs_process_item(connector_ptr, item, index);
        }
        *p_original_stream_id_end = '\0';
    }
}

STATIC void enhs_process_next_group(connector_data_t * connector_ptr, unsigned int index, enhs_path_group_t const * const group, char const * const path);

STATIC void enhs_process_subgroups(connector_data_t * connector_ptr, unsigned int index, enhs_path_group_t const * const * const subgroups_array, unsigned int const array_size, char const * const path)
{
    enhs_info_t * const enhs_info = &connector_ptr->enhs.info;
    connector_bool_t const handle_all = path[0] == '\0' ? connector_true : connector_false;
    unsigned int stream_id_len = enhs_info->stream_id.len;
    char * const p_stream_id_end = &enhs_info->stream_id.string[stream_id_len];
    unsigned int i;

    for (i = 0; i < array_size; i++)
    {
        enhs_path_group_t const * const subgroup = subgroups_array[i];
        unsigned int const name_len = strlen(subgroup->name);
        char const * const remaining_path = get_remaining_path(path);

        enhs_info->stream_id.len = sprintf(enhs_info->stream_id.string, "%s/%s", enhs_info->stream_id.string, subgroup->name);
        if (handle_all || strncmp(path, subgroup->name, name_len) == 0)
        {
            enhs_process_next_group(connector_ptr, index, subgroup, remaining_path); /* recursion */
        }

        *p_stream_id_end = '\0';
    }
}

STATIC void enhs_process_next_group(connector_data_t * connector_ptr, unsigned int index, enhs_path_group_t const * const group, char const * const path)
{
    enhs_path_type_t const type = group->child.type;

    switch (type)
    {
        case ITEMS:
        {
            enhs_item_t const * const * const items_array = group->child.data.items.array;
            unsigned int const array_size = group->child.data.items.size;

            enhs_process_group_items(connector_ptr, index, items_array, array_size, path);
            break;
        }
        case SUBGROUPS:
        {
            enhs_path_group_t const * const * const subgroups_array = group->child.data.subgroups.array;
            unsigned int const array_size = group->child.data.subgroups.size;

            /* Calls us recursively until "type" is "ITEM"*/
            enhs_process_subgroups(connector_ptr, index, subgroups_array, array_size, path);
            break;
        }
    }
}

STATIC void enhs_process_root_group(connector_data_t * const connector_ptr, enhs_path_group_t const * const root_group, char const * const path)
{
    connector_bool_t const handle_all = path[0] == '\0' ? connector_true : connector_false;
    connector_bool_t const multi_instance = root_group->multi_instance != NULL ? connector_true : connector_false;
    enhs_info_t * const enhs_info = &connector_ptr->enhs.info;

    if (handle_all)
    {
        unsigned long int current_instance;
        unsigned long int const total_instances = multi_instance ? root_group->multi_instance() : 1;

        for (current_instance = 0; current_instance < total_instances; current_instance++)
        {
            if (multi_instance)
            {
                enhs_info->stream_id.len = sprintf(enhs_info->stream_id.string, "%s/%lu", root_group->name, current_instance);
            }
            else
            {
                enhs_info->stream_id.len = sprintf(enhs_info->stream_id.string, "%s", root_group->name);
            }

            enhs_process_next_group(connector_ptr, current_instance, root_group, path);
        }
    }
    else
    {
        char const * const remaining_path = get_remaining_path(path);
        unsigned long int const single_instance = strtoul(path, NULL, 10);

        if (multi_instance)
        {
            enhs_info->stream_id.len = sprintf(enhs_info->stream_id.string, "%s/%lu", root_group->name, single_instance);
        }
        else
        {
            enhs_info->stream_id.len = sprintf(enhs_info->stream_id.string, "%s", root_group->name);
        }

        enhs_process_next_group(connector_ptr, single_instance, root_group, remaining_path);
    }
}

STATIC void enhs_process_path(connector_data_t * const connector_ptr, char const * const path)
{
    unsigned int i;

    for(i = 0; i < asizeof(enhs_root_groups); i++)
    {
        enhs_path_group_t const * const root_group = enhs_root_groups[i];
        unsigned int const name_len = strlen(root_group->name);

        if (strncmp(path, root_group->name, name_len) == 0)
        {
            char const * const remaining_path = get_remaining_path(path);

            enhs_process_root_group(connector_ptr, root_group, remaining_path);
            break;
        }
    }
}
