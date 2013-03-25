/*
 * Copyright (c) 2012 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */

static void state_call_return(rci_t * const rci, rci_parser_state_t const call_state, rci_parser_state_t const return_state)
{
    rci->parser.state.previous = return_state;
    rci->parser.state.current = call_state;
}

static void state_call(rci_t * const rci, rci_parser_state_t const call_state)
{
    state_call_return(rci, call_state, rci->parser.state.current);
}

static void rci_error(rci_t * const rci, unsigned int const id, char const * const description, char const * const hint)
{
    rci->shared.response.error_id = id;
    rci->shared.response.element_data.error_hint = hint;

    rci->error.description = description;

    state_call(rci, rci_parser_state_error);
}

#if defined RCI_PARSER_USES_ERROR_DESCRIPTIONS
#define get_rci_global_error(rci, id)   connector_rci_errors[(id) - connector_rci_error_OFFSET]
static char const * get_rci_group_error(rci_t * const rci, unsigned int const id)
{
    connector_group_t const * const group = get_current_group(rci);
    unsigned int const index = (id - connector_global_error_COUNT);

    ASSERT(id >= connector_global_error_COUNT);
    ASSERT(index < group->errors.count);

    return group->errors.description[index];
}
#else
#define get_rci_global_error(rci, id)   ((void) (rci), (void) (id), NULL)
#define get_rci_group_error(rci, id)    ((void) (rci), (void) (id), NULL)
#endif

static void rci_global_error(rci_t * const rci, unsigned int const id, char const * const hint)
{
    char const * const description = get_rci_global_error(rci, id);

    rci_error(rci, id, description, hint);
}

static void rci_group_error(rci_t * const rci, unsigned int const id, char const * const hint)
{
    if (id < connector_global_error_COUNT)
    {
        rci_global_error(rci, id, hint);
    }
    else
    {
        char const * const description = get_rci_group_error(rci, id);

        rci_error(rci, id, description, hint);
    }
}

static connector_bool_t pending_rci_callback(rci_t * const rci)
{
    connector_bool_t const pending = connector_bool(rci->callback.status == connector_callback_busy);

    return pending;
}

static void trigger_rci_callback(rci_t * const rci, connector_remote_config_request_t const remote_config_request)
{
    switch (remote_config_request)
    {
    UNHANDLED_CASES_ARE_NEEDED;
    case connector_remote_config_session_cancel:
        break;

    case connector_remote_config_session_start:
    case connector_remote_config_session_end:
    case connector_remote_config_action_start:
    case connector_remote_config_action_end:
        ASSERT(!have_group_id(rci));
        ASSERT(!have_group_index(rci));
        ASSERT(!have_element_id(rci));
        break;

    case connector_remote_config_group_start:
        ASSERT(have_group_id(rci));
        ASSERT(have_group_index(rci));
        ASSERT(!have_element_id(rci));

        rci->shared.request.group.id = get_group_id(rci);
        rci->shared.request.group.index = get_group_index(rci);
        break;

    case connector_remote_config_group_end:
        ASSERT(have_group_id(rci));
        ASSERT(have_group_index(rci));
        ASSERT(!have_element_id(rci));
        break;

    case connector_remote_config_group_process:
        ASSERT(have_group_id(rci));
        ASSERT(have_group_index(rci));
        ASSERT(have_element_id(rci));

        rci->shared.request.element.id = get_element_id(rci);
        {
            connector_group_element_t const * const element = get_current_element(rci);

            rci->shared.request.element.type = element->type;
        }

        rci->shared.request.element.value = is_set_command(rci->input.command) ? &rci->shared.value : NULL;
        break;
    }

    rci->callback.request.remote_config_request = remote_config_request;
    rci->callback.status = connector_callback_busy;
}

static connector_bool_t rci_callback(rci_t * const rci)
{
    connector_bool_t callback_complete;
    connector_remote_group_response_t * response_data = &rci->shared.response;
    size_t response_length = sizeof *response_data;
    connector_remote_group_request_t * request_data = NULL;
    size_t request_length = 0;

    response_data->error_id = connector_success;

    switch (rci->callback.request.remote_config_request)
    {
    UNHANDLED_CASES_ARE_NEEDED;
    case connector_remote_config_session_start:
    case connector_remote_config_session_end:
        break;

    case connector_remote_config_action_start:
    case connector_remote_config_action_end:
    case connector_remote_config_group_start:
    case connector_remote_config_group_end:
    case connector_remote_config_group_process:
        request_data = &rci->shared.request;
        request_length = sizeof *request_data;
        break;

    case connector_remote_config_session_cancel:
        response_data = rci->shared.response.user_context;
        response_length = sizeof rci->shared.response.user_context;
        break;
    }

    rci->callback.status = connector_callback(rci->service_data->connector_ptr->callback, connector_class_remote_config_service, rci->callback.request, request_data, request_length, response_data, &response_length);

    switch (rci->callback.status)
    {
    case connector_callback_abort:
        callback_complete = connector_false;
        rci->status = rci_status_error;
        break;

    case connector_callback_continue:
        callback_complete = connector_true;

        break;

    case connector_callback_busy:
        callback_complete = connector_false;
        break;

    default:
        callback_complete = connector_false;
        rci->status = rci_status_internal_error;
        break;
    }

    return callback_complete;
}


