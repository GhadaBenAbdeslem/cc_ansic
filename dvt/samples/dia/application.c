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

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "connector_api.h"
#include "platform.h"
#include "application.h"

connector_auto_connect_type_t app_connector_reconnect(connector_class_t const class_id, connector_close_status_t const status)
{
    UNUSED_ARGUMENT(class_id);

    connector_auto_connect_type_t type;

    switch (status)
    {
           /* if either the server or our application cuts the connection, don't reconnect */
        case connector_close_status_device_terminated:
        case connector_close_status_device_stopped:
        case connector_close_status_abort:
             type = connector_manual_connect;
             break;

       /* otherwise it's an error and we want to retry */
       default:
             type = connector_auto_connect;
             break;
    }

    return type;
}

connector_callback_status_t app_connector_callback(connector_class_t const class_id, connector_request_t const request_id,
                                    void const * const request_data, size_t const request_length,
                                    void * response_data, size_t * const response_length)
{
    connector_callback_status_t   status = connector_callback_continue;

    switch (class_id)
    {
    case connector_class_config:
        status = app_config_handler(request_id.config_request, request_data, request_length, response_data, response_length);
        break;

    case connector_class_operating_system:
        status = app_os_handler(request_id.os_request, request_data, request_length, response_data, response_length);
        break;

#if defined CONNECTOR_TRANSPORT_TCP
    case connector_class_network_tcp:
        status = app_network_tcp_handler(request_id.network_request, request_data, request_length, response_data, response_length);
        break;
#endif

#if defined CONNECTOR_TRANSPORT_UDP
    case connector_class_network_udp:
        status = app_network_udp_handler(request_id.network_request, request_data, request_length, response_data, response_length);
        break;
#endif

    case connector_class_data_service:
        status = app_data_service_handler(request_id.data_service_request, request_data, request_length, response_data, response_length);
        break;

    case connector_class_sm:
        status = app_sm_handler(request_id.sm_request, request_data, request_length, response_data, response_length);
        break;

    case connector_class_status:
        status = app_status_handler(request_id.status_request, request_data, request_length, response_data, response_length);
        break;

    default:
        status = connector_callback_unrecognized;
        /* not supported */
        break;
    }

    return status;
}

int application_run(connector_handle_t handle)
{
    int return_status = 0;
    unsigned int const seconds_between_send = 10;
    connector_status_t status = connector_success;
    int cnt = 0;

    while(return_status == 0)
    {
        if (cnt < 6 || (cnt % 6) == 0)
           status = app_send_dia_data(handle);
#ifdef APP_USE_SM_UDP        
        else
           status = app_send_ping(handle);
#endif
        switch (status) 
        {
            case connector_init_error:
            case connector_service_busy:
            case connector_unavailable:
                sleep(2);
                break;

            case connector_success:
                sleep(seconds_between_send);
                cnt++; 
                break;
    
            default:
                APP_DEBUG("SM send failed [%d]\n", status);
                return_status = 1;
                break;
        }
    }
    return return_status;
}
