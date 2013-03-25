/*
 * Copyright (c) 2011 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */
#include "debug.h"

/* facility opcodes */
#define E_MSG_MT2_MSG_NUM          0x0000
#define E_MSG_FAC_FW_NUM           0x0070
#define E_MSG_FAC_RCI_NUM          0x00a0
#define E_MSG_FAC_MSG_NUM          0x00c0
#define E_MSG_FAC_DEV_LOOP_NUM     0xff00
#define E_MSG_FAC_CC_NUM           0xffff

#define named_buffer_id(name)  name##_static_buffer_id
typedef enum
{
    named_buffer_id(none) = 0,
    named_buffer_id(msg_facility),
    named_buffer_id(msg_session),
    named_buffer_id(msg_service),
    named_buffer_id(msg_session_client),
    named_buffer_id(put_request),
    named_buffer_id(sm_session),
    named_buffer_id(sm_data_block),
    named_buffer_id(sm_packet),
    named_buffer_id(data_point_block),
    named_buffer_id(connector_data) = 29,
    named_buffer_id(cc_facility) = 30,
    named_buffer_id(fw_facility) = 31

} connector_static_buffer_id_t;

#ifdef CONNECTOR_NO_MALLOC
static connector_status_t malloc_static_data(connector_data_t * const connector_ptr,
                                                  size_t const size,
                                                  connector_static_buffer_id_t const buffer_id,
                                                  void ** const ptr);

static void free_static_data(connector_data_t * const connector_ptr,
                                 connector_static_buffer_id_t const buffer_id,
                                 void * const ptr);
#endif


static connector_callback_status_t connector_callback(connector_callback_t const callback, connector_class_t const class_id,  connector_request_t const request_id,
                                                                       void const * const request_data, size_t const request_length,
                                                                       void * const response_data, size_t * const response_length)
{
    connector_callback_status_t status = callback(class_id, request_id, request_data, request_length, response_data, response_length);

    switch (status)
    {
        case connector_callback_continue:
        case connector_callback_busy:
            break;

        case connector_callback_unrecognized:
            connector_debug_printf("connector_callback : callback returns unrecognized request for request=%d class_id = %d\n",
                        request_id.config_request, class_id);
            break;

        case connector_callback_abort:
            connector_debug_printf("connector_callback: callback for class id = %d request id = %d returned abort\n", class_id, request_id.config_request);
            break;

#if (CONNECTOR_VERSION >= CONNECTOR_VERSION_1300)
        case connector_callback_error:
#endif
            connector_debug_printf("connector_callback: callback for class id = %d request id = %d returned error\n", class_id, request_id.config_request);
            break;

        default:
            connector_debug_printf("connector_callback: callback for class id = %d request id = %d returned invalid return code %d\n", class_id, request_id.config_request, status);
            status = connector_callback_abort;
            break;
    }

    return status;
}

static connector_status_t notify_error_status(connector_callback_t const callback, connector_class_t const class_number, connector_request_t const request_number, connector_status_t const status)
{
    connector_status_t result = connector_working;

#if (defined CONNECTOR_DEBUG)
    connector_error_status_t err_status;
    connector_request_t request_id;

    request_id.config_request = connector_config_error_status;
    err_status.class_id = class_number;
    err_status.request_id = request_number;
    err_status.status = status;

#if (CONNECTOR_VERSION >= CONNECTOR_VERSION_1300)
    {
        connector_callback_status_t const callback_status = connector_callback_no_response(callback, connector_class_config, request_id, &err_status, sizeof err_status);
        switch (callback_status)
        {
            case connector_callback_continue:
                break;
            default:
                result = connector_abort;
                break;
        }
    }
#else
    connector_callback_no_response(callback, connector_class_config, request_id, &err_status, sizeof err_status);

#endif

#else
    UNUSED_PARAMETER(callback);
    UNUSED_PARAMETER(class_number);
    UNUSED_PARAMETER(request_number);
    UNUSED_PARAMETER(status);
#endif
    return result;
}


static connector_status_t get_system_time(connector_data_t * const connector_ptr, unsigned long * const uptime)
{
    size_t  length;
    connector_status_t result = connector_abort;
    connector_callback_status_t status;
    connector_request_t request_id;

    /* Call callback to get system up time in second */
    request_id.os_request = connector_os_system_up_time;
    status = connector_callback_no_request_data(connector_ptr->callback, connector_class_operating_system, request_id, uptime, &length);
    switch (status)
    {
    case connector_callback_continue:
        result = connector_working;
        break;
    case connector_callback_abort:
        break;
    default:
        ASSERT(connector_false);
        break;
    }


    return result;
}

#ifndef CONNECTOR_NO_MALLOC
static connector_status_t malloc_cb(connector_callback_t const callback, size_t const length, void ** ptr)
{
    connector_status_t result = connector_working;
    connector_callback_status_t status;
    size_t  size = length;
    size_t len;
    connector_request_t request_id;

    request_id.os_request = connector_os_malloc;
    *ptr = NULL;
    status = connector_callback(callback, connector_class_operating_system, request_id, &size, sizeof size, ptr, &len);
    switch (status)
    {
    case connector_callback_continue:
        if (*ptr == NULL)
        {
            result = (notify_error_status(callback, connector_class_operating_system, request_id, connector_invalid_data) == connector_working) ? connector_pending : connector_abort;
        }
#if (DEBUG == true)
        else
        {
            memset(*ptr,0, size);
        }
#endif
        break;
    case connector_callback_busy:
        result = connector_pending;
        break;
    case connector_callback_abort:
    case connector_callback_unrecognized:
#if (CONNECTOR_VERSION >= CONNECTOR_VERSION_1300)
    case connector_callback_error:
#endif
        result = connector_abort;
        break;
    }
    return result;
}

static connector_status_t malloc_data(connector_data_t * const connector_ptr, size_t const length, void ** ptr)
{
    return malloc_cb(connector_ptr->callback, length, ptr);
}

static connector_status_t free_data(connector_data_t * const connector_ptr, void * const ptr)
{
    connector_status_t result = connector_working;
    connector_request_t request_id;

    request_id.os_request = connector_os_free;

#if (CONNECTOR_VERSION >= CONNECTOR_VERSION_1300)
    {
        connector_callback_status_t const callback_status = connector_callback_no_response(connector_ptr->callback, connector_class_operating_system, request_id, ptr, 0);
        switch (callback_status)
        {
            case connector_callback_continue:
                break;
            default:
                result = connector_abort;
                break;
        }
    }
#else
    connector_callback_no_response(connector_ptr->callback, connector_class_operating_system, request_id, ptr, 0);

#endif

    return result;
}
#endif


static connector_status_t malloc_data_buffer(connector_data_t * const connector_ptr, size_t const length, connector_static_buffer_id_t id, void ** ptr)
{
    connector_status_t status;

#ifndef CONNECTOR_NO_MALLOC
    UNUSED_PARAMETER(id);
    status = malloc_data(connector_ptr, length, ptr);
#else
    status = malloc_static_data(connector_ptr, length, id, ptr);
#endif
    return status;
}

static connector_status_t free_data_buffer(connector_data_t * const connector_ptr, connector_static_buffer_id_t id, void * const ptr)
{
    connector_status_t status = connector_working;

#ifndef CONNECTOR_NO_MALLOC
    UNUSED_PARAMETER(id);
    status = free_data(connector_ptr, ptr);
#else
    free_static_data(connector_ptr, id, ptr);
#endif

    return status;
}

#if (CONNECTOR_VERSION >= CONNECTOR_VERSION_1300)
static connector_status_t yield_process(connector_data_t * const connector_ptr, connector_status_t const status)
{
    connector_status_t result = connector_working;

    {
        connector_request_t request_id;
        connector_status_t  request_data = status;
        connector_callback_status_t callback_status;

        request_id.os_request = connector_os_yield;
        callback_status = connector_callback_no_response(connector_ptr->callback, connector_class_operating_system, request_id, &request_data, sizeof request_data);

        switch (callback_status)
        {
            case connector_callback_continue:
                break;
            default:
                result = connector_abort;
                break;
        }
    }

    return result;
}
#else
static void sleep_timeout(connector_data_t * const connector_ptr)
{
    /* no receive buffer and nothing to be read */
    if (connector_ptr->edp_data.receive_packet.free_packet_buffer == NULL &&
        connector_ptr->edp_data.receive_packet.total_length == 0)
    {
        connector_request_t request_id;
        unsigned int const timeout = connector_ptr->edp_data.receive_packet.timeout;

        request_id.os_request = connector_os_sleep;
        connector_callback_no_response(connector_ptr->callback, connector_class_operating_system, request_id, &timeout, sizeof timeout);
    }

    return;
}
#endif

static connector_status_t connector_reboot(connector_data_t * const connector_ptr)
{
    connector_status_t result;

    connector_callback_status_t status = connector_callback_continue;
    connector_request_t request_id;

#if (CONNECTOR_VERSION >= CONNECTOR_VERSION_1300)
    connector_class_t class_id = connector_class_operating_system;
    request_id.os_request = connector_os_reboot;
#else
    connector_class_t class_id = connector_class_network_tcp;
    request_id.network_request = connector_network_reboot;
#endif

    /* server reboots us */

    status = connector_callback_no_response(connector_ptr->callback, class_id, request_id, NULL, 0);
    switch (status)
    {
    case connector_callback_continue:
        result = connector_working;
        break;
    case connector_callback_busy:
        result = connector_pending;
        break;
    default:
        result = connector_abort;
        break;
    }

    return result;

}
