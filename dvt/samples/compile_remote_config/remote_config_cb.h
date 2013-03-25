/*
 * Copyright (c) 2011, 2012 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */

#ifndef REMOTE_CONFIG_CB_H_
#define REMOTE_CONFIG_CB_H_

#include "remote_config.h"

extern connector_callback_status_t app_system_session_start(connector_remote_group_response_t * const response);

extern connector_callback_status_t app_system_session_end(connector_remote_group_response_t * const response);

extern connector_callback_status_t app_system_action_start(connector_remote_group_request_t const * const request,
                                                        connector_remote_group_response_t * const response);

extern connector_callback_status_t app_system_action_end(connector_remote_group_request_t const * const request,
                                                      connector_remote_group_response_t * const response);

extern connector_callback_status_t app_system_group_init(connector_remote_group_request_t const * const request,
                                                 connector_remote_group_response_t * const response);

extern connector_callback_status_t app_system_group_set(connector_remote_group_request_t const * const request,
                                                 connector_remote_group_response_t * const response);

extern connector_callback_status_t app_system_group_get(connector_remote_group_request_t const * const request,
                                                 connector_remote_group_response_t * const response);

extern connector_callback_status_t app_system_group_end(connector_remote_group_request_t const * const request,
                                                 connector_remote_group_response_t * const response);

extern void app_system_session_cancel(void * const context);

#endif /* REMOTE_CONFIG_CB_H_ */
