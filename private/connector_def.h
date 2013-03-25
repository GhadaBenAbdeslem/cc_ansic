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

#ifndef CONNECTOR_DEF_H_
#define CONNECTOR_DEF_H_

#ifndef CONNECTOR_MAX_VENDOR_ID_NUMBER
#define CONNECTOR_MAX_VENDOR_ID_NUMBER 0xFE000000
#endif

#if (CONNECTOR_VERSION <= CONNECTOR_VERSION_1200)
#define connector_unavailable           (connector_status_t)(connector_no_resource + 1)
#define connector_idle                  (connector_status_t)(connector_no_resource + 2)
#define connector_working               (connector_status_t)(connector_no_resource + 3)
#define connector_pending               (connector_status_t)(connector_no_resource + 4)
#define connector_active                (connector_status_t)(connector_no_resource + 5)
#define connector_device_error          (connector_status_t)(connector_no_resource + 6)
#define connector_abort                 connector_configuration_error
#define connector_open_error            connector_connect_error

typedef enum {
    connector_close_status_server_disconnected = 1,    /**< iDigi connector received a disconnect from the server. */
    connector_close_status_server_redirected,          /**< iDigi connector is redirected to different server. */
    connector_close_status_device_terminated,          /**< iDigi connector is terminated via @ref connector_initiate_action
                                                 iDigi connector will terminate all active messages or requests and free all memory.
                                                 @ref connector_auto_connect_type_t returned status from the close callback will be ignored. */
    connector_close_status_device_stopped,             /**< iDigi connector is stopped via @ref connector_initiate_action */
    connector_close_status_no_keepalive,               /**< iDigi connector has not received keep alive messages from the server */
    connector_close_status_abort,                      /**< iDigi connector is aborted either it encountered fatal error or callback aborted iDigi connector.
                                                 iDigi connector will terminate all active messages or requests and free all memory.
                                                 @ref connector_auto_connect_type_t returned status from the close callback will be ignored. */
    connector_close_status_device_error,               /**< iDigi connector received error from callback which requires to close the connection. */

    /* 1.2 support */
    connector_close_receive_error,             /* equivalent to connector_receive_error in 1.2 */
    connector_close_send_error                /* equivalent to connector_send_error in 1.2 */
} connector_close_status_t;

#endif

#define UNUSED_VARIABLE(x)      ((void) (x))
#define UNUSED_PARAMETER(x)     UNUSED_VARIABLE(x)

#define ON_FALSE_DO_(cond, code)        do { if (!(cond)) {code;} } while (0)

#if (defined CONNECTOR_DEBUG)
#define ON_ASSERT_DO_(cond, code, output)   ON_FALSE_DO_((cond), {ASSERT(cond); code;})
#else
#define ON_ASSERT_DO_(cond, code, output)   ON_FALSE_DO_((cond), {code})
#endif

#define ASSERT_GOTO(cond, label)    ON_ASSERT_DO_((cond), {goto label;}, {})
#define CONFIRM(cond)               do { switch(0) {case 0: case (cond):;} } while (0)

#define COND_ELSE_GOTO(cond, label)    ON_FALSE_DO_((cond), {goto label;})


#define DEVICE_ID_LENGTH    16
#define SERVER_URL_LENGTH   64

#define CONNECTOR_GSM_IMEI_LENGTH   8
#define CONNECTOR_ESN_HEX_LENGTH    4
#define CONNECTOR_MEID_HEX_LENGTH   7

#define MAC_ADDR_LENGTH     6

#define CONNECTOR_DATA_POINT_REQUEST      0x8000

#define MIN_VALUE(x,y)        (((x) < (y))? (x): (y))
#define MAX_VALUE(x,y)        (((x) > (y))? (x): (y))

#define connector_callback_no_response(callback, class_id, request_id, request_data, request_length) connector_callback((callback), (class_id), (request_id), (request_data), (request_length), NULL, NULL)
#define connector_callback_no_request_data(callback, class_id, request_id, response_data, response_length) connector_callback((callback), (class_id), (request_id), NULL, 0, (response_data), (response_length))

#define MAX_RECEIVE_TIMEOUT_IN_SECONDS  1
#define MIN_RECEIVE_TIMEOUT_IN_SECONDS  0

#if (CONNECTOR_VERSION < CONNECTOR_VERSION_1200)
#define asizeof(array)      (sizeof array/sizeof array[0])
#endif

typedef enum {
    connector_network_tcp,
    connector_network_udp,
    connector_network_sms,
    connector_network_count
} connector_network_type_t;

typedef enum {
    connector_transport_idle,
    connector_transport_open,
    connector_transport_send,
    connector_transport_receive,
    connector_transport_close,
    connector_transport_terminate,
    connector_transport_redirect
} connector_transport_state_t;

typedef enum {
    connector_false,
    connector_true,
    connector_bool_integer_width = INT_MAX
} connector_bool_t;

#define connector_bool(cond)    ((cond) ? connector_true : connector_false)

#define add_list_node(head, tail, node) \
    do { \
        ASSERT(node != NULL); \
        if (*head != NULL) \
        {\
            *head->prev = node;\
        }\
        node->next = *head;\
        node->prev = NULL;\
        *head = node;\
        if ((tail != NULL) && (*tail == NULL)) \
        { \
            *tail = node; \
        } \
   } while (0)

#define remove_list_node(head, tail, node) \
    do { \
        ASSERT(node != NULL); \
        if (node->next != NULL) \
        {\
            node->next->prev = node->prev;\
        }\
        if (node->prev != NULL) \
        {\
            node->prev->next = node->next;\
        }\
        if (node == *head)\
        {\
            *head = node->next;\
        }\
        if ((tail != NULL) && (node == *tail))\
        {\
            *tail = node->prev;\
        }\
    } while (0)

#define add_node(head, node) \
    do { \
        ASSERT(node != NULL); \
        if (*head != NULL) \
        {\
            *head->prev = node;\
        }\
        node->next = *head;\
        node->prev = NULL;\
        *head = node;\
    } while (0)

#define remove_node(head, node) \
    do { \
        ASSERT(node != NULL); \
        if (node->next != NULL) \
        {\
            node->next->prev = node->prev;\
        }\
        if (node->prev != NULL) \
        {\
            node->prev->next = node->next;\
        }\
        if (node == *head)\
        {\
            *head = node->next;\
        }\
    } while (0)

struct connector_data;

#if (CONNECTOR_VERSION <= CONNECTOR_VERSION_1200) || (defined CONNECTOR_TRANSPORT_TCP)
#include "connector_edp_def.h"
#endif

#if (defined CONNECTOR_TRANSPORT_UDP) || (defined CONNECTOR_TRANSPORT_SMS)
#include "connector_sm_def.h"
#endif

typedef struct connector_data {

    char const * signature;

    uint8_t * device_id;
    uint8_t * mac_addr;
    uint8_t * wan_id;
    size_t wan_id_length;

    char * device_cloud_url;
    size_t device_cloud_url_length;

    connector_connection_type_t connection_type;

#if (CONNECTOR_VERSION >= CONNECTOR_VERSION_1300)
    connector_wan_type_t wan_type;
#endif

#if !(defined CONNECTOR_WAN_LINK_SPEED_IN_BITS_PER_SECOND)
    uint32_t link_speed;
#endif

#if !(defined CONNECTOR_WAN_PHONE_NUMBER_DIALED)
    char * phone_dialed;
    size_t phone_dialed_length;
#endif

#if (CONNECTOR_VERSION >= CONNECTOR_VERSION_1200)
    connector_device_id_method_t device_id_method;
#endif

    connector_network_type_t first_running_network;

    connector_callback_t callback;
    connector_status_t error_code;

#if (defined CONNECTOR_TRANSPORT_UDP)
    connector_sm_data_t sm_udp;
#endif

#if (defined CONNECTOR_TRANSPORT_SMS)
    connector_sm_data_t sm_sms;
#endif

#if (CONNECTOR_VERSION <= CONNECTOR_VERSION_1200) || (defined CONNECTOR_TRANSPORT_TCP)
    connector_edp_data_t edp_data;
#endif

    struct {
        enum {
            connector_state_running,
            connector_state_stop_by_initiate_action,
            connector_state_terminate_by_initiate_action,
            connector_state_abort_by_callback
        } state;
#if (CONNECTOR_VERSION >= CONNECTOR_VERSION_1300)
        connector_stop_condition_t condition;
        void * user_context;
#endif
    } stop;

} connector_data_t;

#endif /* CONNECTOR_DEF_H_ */
