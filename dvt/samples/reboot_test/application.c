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

#include <unistd.h>
#include "connector_api.h"
#include "platform.h"
#include "application.h"

extern void clear_stack_size(void);

extern connector_callback_status_t app_data_service_handler(connector_data_service_request_t const request,
                                                  void const * const request_data, size_t const request_length,
                                                  void * response_data, size_t * const response_length);
extern connector_callback_status_t app_firmware_handler(connector_firmware_request_t const request,
                                                  void const * const request_data, size_t const request_length,
                                                  void * response_data, size_t * const response_length);

extern connector_status_t send_put_request(connector_handle_t handle, char * const filename, char * const content);

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

    case connector_class_network_tcp:
        status = app_network_tcp_handler(request_id.network_request, request_data, request_length, response_data, response_length);
        break;

    case connector_class_data_service:
        status = app_data_service_handler(request_id.data_service_request, request_data, request_length, response_data, response_length);
        break;

    case connector_class_firmware:
        status = app_firmware_handler(request_id.firmware_request, request_data, request_length, response_data, response_length);
        break;

    case connector_class_status:
        status = app_status_handler(request_id.status_request, request_data, request_length, response_data, response_length);
        break;

    default:
        /* not supported */
        break;
    }
    clear_stack_size();

    return status;
}

int application_run(connector_handle_t handle)
{
    connector_status_t status;
    static char reboot_result[32];

    for (;;)
    {
        int send_reboot_result = 0;

        switch (reboot_state)
        {
        case reboot_received:
            strcpy(reboot_result, "reboot_ok");
            send_reboot_result = 1;
            break;
        case receive_reset:
            strcpy(reboot_result, "reboot_reset");
            send_reboot_result = 1;
            break;
        case receive_error:
            sprintf(reboot_result, "reboot_receive_error = %d", reboot_errno);
            send_reboot_result = 1;
            break;
        case send_error:
            sprintf(reboot_result, "reboot_send_error = %d", reboot_errno);
            send_reboot_result = 1;
            break;
        case reboot_timeout:
            sprintf(reboot_result, "reboot_timeout");
            send_reboot_result = 1;
            break;
        default:
            usleep(5 * 1000000);
            break;
        }

        if (send_reboot_result)
        {
            status = send_put_request(handle, "reboot_test.txt", reboot_result);
            if (status != connector_success)
            {
                usleep(2 * 1000000);
            }
            else
            {
                APP_DEBUG("send_put_request for reboot_test.txt %d\n", status);
            }
        }

    }
    return 0;
}

