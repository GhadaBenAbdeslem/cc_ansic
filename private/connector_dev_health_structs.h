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

typedef connector_bool_t (* dev_health_query_fn_t)(connector_indexes_t const * const indexes, void * const value);
typedef unsigned int (* dev_health_get_instances_fn_t)(void);

typedef enum {
    DEV_HEALTH_TYPE_NONE,
    DEV_HEALTH_TYPE_INT32,
    DEV_HEALTH_TYPE_UINT64,
    DEV_HEALTH_TYPE_FLOAT,
    DEV_HEALTH_TYPE_STRING,
    DEV_HEALTH_TYPE_JSON,
    DEV_HEALTH_TYPE_GEOJSON
} dev_health_value_type_t;

typedef struct {
    char const * name;
    dev_health_value_type_t type;
    dev_health_query_fn_t getter;
} dev_health_item_t;

typedef enum {
    ITEMS,
    SUBGROUPS
} dev_health_path_type_t;

typedef struct dev_health_path_group {
    char const * name;
    dev_health_get_instances_fn_t multi_instance;

    struct {
        dev_health_path_type_t type;
        union {
            struct {
                dev_health_item_t const * const * array;
                unsigned int size;
            } items;
            struct {
                struct dev_health_path_group const * const * array;
                unsigned int size;
            } subgroups;
        } data;
    } child;
} dev_health_path_group_t;

#define JSON_MAX_SIZE   128

STATIC unsigned int count_special_chars(char const * const string)
{
    unsigned int i;
    unsigned int escaped_chars = 0;

    for (i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == '"' || string[i] == '\\')
        {
            escaped_chars++;
        }
    }

    return escaped_chars;
}

STATIC void escape_string(char * * const string)
{
    unsigned int escape_chars;

    ASSERT(*string != NULL);
    escape_chars = count_special_chars(*string);

    if (escape_chars)
    {
        unsigned int const new_size = strlen(*string) + escape_chars + 1;
        char * string_escaped = cc_dev_health_malloc_string(new_size);

        ASSERT(string_escaped != NULL);
        dp_process_string(*string, string_escaped, new_size, NULL, connector_false, connector_true);
        cc_dev_health_free_string(*string);
        *string = string_escaped;
    }
}

STATIC connector_bool_t cc_dev_health_get_mobile_module_json(connector_indexes_t const * const indexes, connector_json_t * const value)
{
    connector_bool_t const present = cc_dev_health_mobile_module_present(indexes);

    if (present)
    {
        char * const module_json = cc_dev_health_malloc_string(JSON_MAX_SIZE);
        static const char module_json_format[] = "{\"modem_id\":\"%s\",\"cell_id\":\"%s\", \"network\":\"%s\",\"sims\":%u,\"active_sim\":%u}";
        char * modem_id = NULL;
        char * cell_id = NULL;
        char * network = NULL;
        unsigned int sims;
        unsigned int active_sim;
        int json_size;

        ASSERT(module_json != NULL);
        cc_dev_health_get_mobile_module_modem_id(indexes, &modem_id);
        cc_dev_health_get_mobile_module_cell_id(indexes, &cell_id);
        cc_dev_health_get_mobile_module_network(indexes, &network);
        cc_dev_health_get_mobile_module_sims(indexes, &sims);
        cc_dev_health_get_mobile_module_active_sim(indexes, &active_sim);

        ASSERT(modem_id != NULL);
        ASSERT(cell_id != NULL);
        ASSERT(network != NULL);

        escape_string(&modem_id);
        escape_string(&cell_id);
        escape_string(&network);

        json_size = sprintf(module_json, module_json_format, modem_id, cell_id, network, sims, active_sim);
        UNUSED_VARIABLE(json_size); /* Prevent variable set but not used in non-debug */
        ASSERT(json_size <= JSON_MAX_SIZE);

        cc_dev_health_free_string(modem_id);
        cc_dev_health_free_string(cell_id);
        cc_dev_health_free_string(network);

        *value = module_json;
    }

    return present;
}

STATIC connector_bool_t cc_dev_health_get_mobile_net_sim_json(connector_indexes_t const * const indexes, connector_json_t * const value)
{
    connector_bool_t const present = cc_dev_health_get_mobile_net_present(indexes);

    if (present)
    {
        char * const sim_json = cc_dev_health_malloc_string(JSON_MAX_SIZE);
        static const char sim_json_format[] = "{\"iccid\":\"%s\",\"imsi\":\"%s\",\"phone_num\":\"%s\"}";
        char * iccid = NULL;
        char * imsi = NULL;
        char * phone_num = NULL;
        int json_size;

        ASSERT(sim_json != NULL);

        cc_dev_health_get_mobile_net_sim_iccid(indexes, &iccid);
        cc_dev_health_get_mobile_net_sim_imsi(indexes, &imsi);
        cc_dev_health_get_mobile_net_sim_phone_num(indexes, &phone_num);

        ASSERT(iccid != NULL);
        ASSERT(imsi != NULL);
        ASSERT(phone_num != NULL);

        escape_string(&iccid);
        escape_string(&imsi);
        escape_string(&phone_num);

        json_size = sprintf(sim_json, sim_json_format, iccid, imsi, phone_num);
        UNUSED_VARIABLE(json_size); /* Prevent variable set but not used in non-debug */
        ASSERT(json_size <= JSON_MAX_SIZE);

        cc_dev_health_free_string(iccid);
        cc_dev_health_free_string(imsi);
        cc_dev_health_free_string(phone_num);

        *value = sim_json;
    }

    return present;
}

STATIC connector_bool_t cc_dev_health_get_wifi_radio_json(connector_indexes_t const * const indexes, connector_geojson_t * const value)
{
    connector_bool_t const present = cc_dev_health_get_wifi_radio_present(indexes);

    if (present)
    {
        char * const radio_json = cc_dev_health_malloc_string(JSON_MAX_SIZE);
        static const char radio_json_format[] = "{\"mode\":\"%s\",\"ssid\":\"%s\",\"channel\":%u,\"protocol\":\"%s\"}";
        char * mode = NULL;
        char * ssid = NULL;
        char * protocol = NULL;
        unsigned int channel = 0;
        int json_size;

        ASSERT(radio_json != NULL);

        cc_dev_health_get_wifi_radio_mode(indexes, &mode);
        cc_dev_health_get_wifi_radio_ssid(indexes, &ssid);
        cc_dev_health_get_wifi_radio_protocol(indexes, &protocol);
        cc_dev_health_get_wifi_radio_channel(indexes, &channel);

        ASSERT(mode != NULL);
        ASSERT(ssid != NULL);
        ASSERT(protocol != NULL);

        escape_string(&mode);
        escape_string(&ssid);
        escape_string(&protocol);

        json_size = sprintf(radio_json, radio_json_format, mode, ssid, channel, protocol);
        UNUSED_VARIABLE(json_size); /* Prevent variable set but not used in non-debug */
        ASSERT(json_size <= JSON_MAX_SIZE);

        cc_dev_health_free_string(mode);
        cc_dev_health_free_string(ssid);
        cc_dev_health_free_string(protocol);

        *value = radio_json;
    }

    return present;
}

STATIC connector_bool_t cc_dev_health_get_gps_location_geojson(connector_indexes_t const * const indexes, connector_geojson_t * const value)
{
    connector_bool_t const present = cc_dev_health_get_gps_location_present(indexes);

    if (present)
    {
        char * const location_json = cc_dev_health_malloc_string(JSON_MAX_SIZE);
        static const char gps_location_json_format[] = "{\"type\":\"Point\",\"coordinates\":[%f,%f]}";
        float latitude;
        float longitude;
        int json_size;

        ASSERT(location_json != NULL);
        cc_dev_health_get_gps_location_latitude(indexes, &latitude);
        cc_dev_health_get_gps_location_longitude(indexes, &longitude);

        json_size = sprintf(location_json, gps_location_json_format, latitude, longitude);
        UNUSED_VARIABLE(json_size); /* Prevent variable set but not used in non-debug */
        ASSERT(json_size <= JSON_MAX_SIZE);

        *value = location_json;
    }

    return present;
}

static const dev_health_item_t dev_health_net_latency_min = {"min", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_net_latency_min};
static const dev_health_item_t dev_health_net_latency_avg = {"avg", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_net_latency_avg};
static const dev_health_item_t dev_health_net_latency_max = {"max", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_net_latency_max};

static dev_health_item_t const * const dev_health_net_latency_elements[] =
{
    &dev_health_net_latency_min,
    &dev_health_net_latency_avg,
    &dev_health_net_latency_max
};

static dev_health_path_group_t const dev_health_net_latency =
{
    "latency",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_net_latency_elements,
                asizeof(dev_health_net_latency_elements)
            }
        }
    }
};

static const dev_health_item_t dev_health_net_transactions_count = {"count", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_net_transactions_count};

static dev_health_item_t const * const dev_health_net_transactions_elements[] =
{
    &dev_health_net_transactions_count,
};

static dev_health_path_group_t const dev_health_net_transactions =
{
    "transactions",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_net_transactions_elements,
                asizeof(dev_health_net_transactions_elements)
            }
        }
    }
};

static const dev_health_item_t dev_health_net_drop_count = {"count", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_net_drop_count};

static dev_health_item_t const * const dev_health_net_drop_elements[] =
{
    &dev_health_net_drop_count
};

static dev_health_path_group_t const dev_health_net_drop =
{
    "drop",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_net_drop_elements,
                asizeof(dev_health_net_drop_elements)
            }
        }
    }
};

static const dev_health_item_t dev_health_net_oos_count = {"count", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_net_oos_count};

static dev_health_item_t const * const dev_health_net_oos_elements[] =
{
    &dev_health_net_oos_count,
};

static dev_health_path_group_t const dev_health_net_oos =
{
    "oos",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_net_oos_elements,
                asizeof(dev_health_net_oos_elements)
            }
        }
    }
};

static dev_health_path_group_t const * const dev_health_net_levels[] =
{
    &dev_health_net_latency,
    &dev_health_net_transactions,
    &dev_health_net_drop,
    &dev_health_net_oos
};

static dev_health_path_group_t const dev_health_root_group_net =
{
    "net",
    NULL,
    {
        SUBGROUPS,
        {
            {
                (dev_health_item_t const * const *)dev_health_net_levels,
                asizeof(dev_health_net_levels)
            }
        }
    }
};

/**************/

unsigned int cc_dev_health_get_mobile_net_instances(void)
{
    return 2;
}

static const dev_health_item_t dev_health_mobile_module = {"module", DEV_HEALTH_TYPE_JSON, (dev_health_query_fn_t)cc_dev_health_get_mobile_module_json};

static dev_health_item_t const * const dev_health_mobile_module_elements[] =
{
    &dev_health_mobile_module,
};

static const dev_health_item_t dev_health_mobile_net_status = {"status", DEV_HEALTH_TYPE_STRING, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_status};
static const dev_health_item_t dev_health_mobile_net_rssi = {"rssi", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_rssi};
static const dev_health_item_t dev_health_mobile_net_ecio = {"ecio", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_ecio};
static const dev_health_item_t dev_health_mobile_net_rsrp = {"rsrp", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_rsrp};
static const dev_health_item_t dev_health_mobile_net_rsrq = {"rsrq", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_rsrq};
static const dev_health_item_t dev_health_mobile_net_sinr = {"sinr", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_sinr};
static const dev_health_item_t dev_health_mobile_net_snr = {"snr", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_snr};
static const dev_health_item_t dev_health_mobile_net_registration = {"registration", DEV_HEALTH_TYPE_STRING, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_registration};
static const dev_health_item_t dev_health_mobile_net_lac = {"lac", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_lac};
static const dev_health_item_t dev_health_mobile_net_tac = {"tac", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_tac};
static const dev_health_item_t dev_health_mobile_net_session = {"session", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_session};
static const dev_health_item_t dev_health_mobile_net_temperature = {"temperature", DEV_HEALTH_TYPE_FLOAT, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_temperature};
static const dev_health_item_t dev_health_mobile_net_sim = {"sim", DEV_HEALTH_TYPE_JSON, (dev_health_query_fn_t)cc_dev_health_get_mobile_net_sim_json};

static dev_health_item_t const * const dev_health_mobile_net_elements[] =
{
    &dev_health_mobile_net_status,
    &dev_health_mobile_net_rssi,
    &dev_health_mobile_net_ecio,
    &dev_health_mobile_net_rsrp,
    &dev_health_mobile_net_rsrq,
    &dev_health_mobile_net_sinr,
    &dev_health_mobile_net_snr,
    &dev_health_mobile_net_registration,
    &dev_health_mobile_net_lac,
    &dev_health_mobile_net_tac,
    &dev_health_mobile_net_session,
    &dev_health_mobile_net_temperature,
    &dev_health_mobile_net_sim
};

static dev_health_path_group_t const dev_health_mobile_module_group =
{
    "",
    NULL,
    {
        ITEMS,
        {
            {
                (dev_health_item_t const * const *)dev_health_mobile_module_elements,
                asizeof(dev_health_mobile_module_elements)
            }
        }
    }
};

static dev_health_path_group_t const dev_health_mobile_net_group =
{
    "net",
    cc_dev_health_get_mobile_net_instances,
    {
        ITEMS,
        {
            {
                (dev_health_item_t const * const *)dev_health_mobile_net_elements,
                asizeof(dev_health_mobile_net_elements)
            }
        }
    }
};

static dev_health_path_group_t const * const dev_health_mobile_levels[] =
{
    &dev_health_mobile_module_group,
    &dev_health_mobile_net_group
};

static dev_health_path_group_t const dev_health_root_group_mobile =
{
    "mobile",
    cc_dev_health_get_mobile_instances,
    {
        SUBGROUPS,
        {
            {
                (dev_health_item_t const * const *)dev_health_mobile_levels,
                asizeof(dev_health_mobile_levels)
            }
        }
    }
};
/**************/

static const dev_health_item_t dev_health_eth_tx_bytes = {"bytes", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_eth_tx_bytes};
static const dev_health_item_t dev_health_eth_tx_packets = {"packets", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_eth_tx_packets};
static const dev_health_item_t dev_health_eth_tx_dropped = {"dropped", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_eth_tx_dropped};
static const dev_health_item_t dev_health_eth_tx_overruns = {"overruns", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_eth_tx_overruns};

static dev_health_item_t const * const dev_health_eth_tx_elements[] =
{
    &dev_health_eth_tx_bytes,
    &dev_health_eth_tx_packets,
    &dev_health_eth_tx_dropped,
    &dev_health_eth_tx_overruns
};

static dev_health_path_group_t const dev_health_eth_tx =
{
    "tx",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_eth_tx_elements,
                asizeof(dev_health_eth_tx_elements)
            }
        }
    }
};

static const dev_health_item_t dev_health_eth_rx_bytes = {"bytes", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_eth_rx_bytes};
static const dev_health_item_t dev_health_eth_rx_packets = {"packets", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_eth_rx_packets};
static const dev_health_item_t dev_health_eth_rx_dropped = {"dropped", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_eth_rx_dropped};

static dev_health_item_t const * const dev_health_eth_rx_elements[] =
{
    &dev_health_eth_rx_bytes,
    &dev_health_eth_rx_packets,
    &dev_health_eth_rx_dropped
};

static dev_health_path_group_t const dev_health_eth_rx =
{
    "rx",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_eth_rx_elements,
                asizeof(dev_health_eth_rx_elements)
            }
        }
    }
};

static const dev_health_item_t dev_health_eth_link_down_count = {"down_count", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_eth_link_down_count};
static const dev_health_item_t dev_health_eth_link_down_duration = {"down_duration", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_eth_link_down_duration};

static dev_health_item_t const * const dev_health_eth_link_elements[] =
{
    &dev_health_eth_link_down_duration,
    &dev_health_eth_link_down_duration
};

static dev_health_path_group_t const dev_health_eth_link =
{
    "link",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_eth_link_elements,
                asizeof(dev_health_eth_link_elements)
            }
        }
    }
};

static dev_health_path_group_t const * const dev_health_eth_levels[] =
{
    &dev_health_eth_tx,
    &dev_health_eth_rx,
    &dev_health_eth_link
};

static dev_health_path_group_t const dev_health_root_group_eth =
{
    "eth",
    cc_dev_health_get_eth_instances,
    {
        SUBGROUPS,
        {
            {
                (dev_health_item_t const * const *)dev_health_eth_levels,
                asizeof(dev_health_eth_levels)
            }
        }
    }
};

static const dev_health_item_t dev_health_wifi_radio = {"radio", DEV_HEALTH_TYPE_JSON, (dev_health_query_fn_t)cc_dev_health_get_wifi_radio_json};
static const dev_health_item_t dev_health_wifi_status = {"status", DEV_HEALTH_TYPE_STRING, (dev_health_query_fn_t)cc_dev_health_get_wifi_status};
static const dev_health_item_t dev_health_wifi_rssi = {"rssi", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_wifi_rssi};
static const dev_health_item_t dev_health_wifi_rate = {"rate", DEV_HEALTH_TYPE_FLOAT, (dev_health_query_fn_t)cc_dev_health_get_wifi_rate};
static const dev_health_item_t dev_health_wifi_clients = {"clients", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_wifi_clients};

static dev_health_item_t const * const dev_health_wifi_elements[] =
{
    &dev_health_wifi_radio,
    &dev_health_wifi_status,
    &dev_health_wifi_rssi,
    &dev_health_wifi_rate,
    &dev_health_wifi_clients
};

static dev_health_path_group_t const dev_health_root_group_wifi =
{
    "wifi",
    cc_dev_health_get_wifi_instances,
    {
        ITEMS,
        {
            {
                dev_health_wifi_elements,
                asizeof(dev_health_wifi_elements)
            }
        }
    }
};

static const dev_health_item_t dev_health_system_mem_free = {"free", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_system_mem_free};
static const dev_health_item_t dev_health_system_mem_used = {"used", DEV_HEALTH_TYPE_UINT64, (dev_health_query_fn_t)cc_dev_health_get_system_mem_used};

static dev_health_item_t const * const dev_health_system_mem_elements[] =
{
    &dev_health_system_mem_free,
    &dev_health_system_mem_used
};

static dev_health_path_group_t const dev_health_system_mem =
{
    "mem",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_system_mem_elements,
                asizeof(dev_health_system_mem_elements)
            }
        }
    }
};

static const dev_health_item_t dev_health_system_reboots_items = {"", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_system_reboots};

static dev_health_item_t const * const dev_health_system_reboots_elements[] =
{
    &dev_health_system_reboots_items,
};

static dev_health_path_group_t const dev_health_system_reboots =
{
    "reboots",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_system_reboots_elements,
                asizeof(dev_health_system_reboots_elements)
            }
        }
    }
};

static const dev_health_item_t dev_health_system_msg_free = {"free", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_system_msg_free};
static const dev_health_item_t dev_health_system_msg_min = {"min", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_system_msg_min};

static dev_health_item_t const * const dev_health_system_msg_elements[] =
{
    &dev_health_system_msg_free,
    &dev_health_system_msg_min
};

static dev_health_path_group_t const dev_health_system_msg =
{
    "msg",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_system_msg_elements,
                 asizeof(dev_health_system_msg_elements)
            }
        }

    }
};

static const dev_health_item_t dev_health_system_buf_free = {"free", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_system_buf_free};
static const dev_health_item_t dev_health_system_buf_used = {"used", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_system_buf_used};

static dev_health_item_t const * const dev_health_system_buf_elements[] =
{
    &dev_health_system_buf_free,
    &dev_health_system_buf_used
};

static dev_health_path_group_t const dev_health_system_buf =
{
    "buf",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_system_buf_elements,
                asizeof(dev_health_system_buf_elements)
            }
        }
    }
};

static const dev_health_item_t dev_health_system_bigbuf_free = {"free", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_system_bigbuf_free};
static const dev_health_item_t dev_health_system_bigbuf_used = {"used", DEV_HEALTH_TYPE_INT32, (dev_health_query_fn_t)cc_dev_health_get_system_bigbuf_used};

static dev_health_item_t const * const dev_health_system_bigbuf_elements[] =
{
    &dev_health_system_bigbuf_free,
    &dev_health_system_bigbuf_used
};

static dev_health_path_group_t const dev_health_system_bigbuf =
{
    "bigbuf",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_system_bigbuf_elements,
                asizeof(dev_health_system_bigbuf_elements)
            }
        }
    }
};

static dev_health_path_group_t const * const dev_health_system_groups[] =
{
    &dev_health_system_mem,
    &dev_health_system_reboots,
    &dev_health_system_msg,
    &dev_health_system_buf,
    &dev_health_system_bigbuf
};

static dev_health_path_group_t const dev_health_root_group_system =
{
    "system",
    NULL,
    {
        SUBGROUPS,
        {
            {
                (dev_health_item_t const * const *)dev_health_system_groups,
                asizeof(dev_health_system_groups)
            }
        }
    }
};

static const dev_health_item_t dev_health_gps_location = {"location", DEV_HEALTH_TYPE_GEOJSON, (dev_health_query_fn_t)cc_dev_health_get_gps_location_geojson};

static dev_health_item_t const * const dev_health_gps_elements[] =
{
    &dev_health_gps_location
};

static dev_health_path_group_t const dev_health_root_group_gps =
{
    "gps",
    NULL,
    {
        ITEMS,
        {
            {
                dev_health_gps_elements,
                asizeof(dev_health_gps_elements)
            }
        }
    }
};

static dev_health_path_group_t const * const dev_health_root_groups[] =
{
    &dev_health_root_group_net,
    &dev_health_root_group_mobile,
    &dev_health_root_group_eth,
    &dev_health_root_group_wifi,
    &dev_health_root_group_system,
    &dev_health_root_group_gps
};
