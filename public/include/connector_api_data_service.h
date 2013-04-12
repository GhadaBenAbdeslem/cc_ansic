/*
 * Copyright (c) 2013 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */
 /**
  * @file
  *  @brief Functions and prototypes for Connector Data Service related API
  *         public API
  *
  */
#ifndef _CONNECTOR_DS_API_H
#define _CONNECTOR_DS_API_H

/**
* @defgroup connector_request_data_service_send_t  To send data to Etherios Device Cloud.
* @{
*/
/**
* This structure is used when sending a data to Device Cloud with connector_initiate_action()
* call.The action ID used for this call is connector_initiate_send_data.
*
* @see connector_initiate_request_t
* @see connector_request_id_data_service_t
*/
typedef struct
{
    connector_transport_t transport;    /**< transport method to use to send the data */
    void * user_context;                /**< user context, this will be returned in subsequent callbacks */

    char const * path;                  /**< destination path */
    char const * content_type;          /**< null-terminated content type (text/plain, text/xml, application/json, etc. Applicable only in TCP transport method */

    enum
    {
        connector_data_service_send_option_overwrite,   /**< overwrite the content if the path is already exists */
        connector_data_service_send_option_archive,     /**< archive the data in given path */
        connector_data_service_send_option_append,      /**< append to existing file/path */
        connector_data_service_send_option_transient    /**< Device Cloud need not store the data but can send it to the consumer */
    } option;       /**< what action Device Cloud should take after receing this request. Applicable only in TCP transport method */

    connector_bool_t response_required; /**< set to connector_true if response is needed */
} connector_request_data_service_send_t;
/**
* @}
*/

/**
* @defgroup connector_request_id_data_service_t Data Service Request IDs
* @{
*/
/**
 * Data service request ID,used in data service related callbacks to get user request/response
 * or to pass Etherios Device Cloud request/response.
 */
typedef enum {
    connector_request_id_data_service_send_length,      /**< to get the total length of the data to send. Not applicable in TCP transport method */
    connector_request_id_data_service_send_data,        /**< to get the data to send to Device Cloud */
    connector_request_id_data_service_send_status,      /**< to inform the session status */
    connector_request_id_data_service_send_response,    /**< to pass Device Cloud response */

    connector_request_id_data_service_receive_target,   /**< indicates the start of Device Cloud request for a given target */
    connector_request_id_data_service_receive_data,     /**< to pass the received request data from Device Cloud */
    connector_request_id_data_service_receive_status,   /**< to inform the session status */
    connector_request_id_data_service_receive_reply_length, /**< to get the total length of the response data. Not applicable in TCP transport method */
    connector_request_id_data_service_receive_reply_data    /**< to get the response data */
} connector_request_id_data_service_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_length_t Length of data/response to send
* @{
*/
/**
* The callback data with request ID connector_request_id_data_service_send_length and connector_request_id_data_service_receive_reply_length
* will point to this structure. User needs to update total bytes with the number of bytes in send/response data. This callback will be called
* just before the callback for send_data and reply_data.
*/
typedef struct
{
    connector_transport_t CONST transport;   /**< transport method from where the callback is originated */
    void * user_context;                     /**< context passed in connector_initiate_action */

    size_t total_bytes;                      /**< total bytes in to send */
} connector_data_service_length_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_send_data_t  To get send data
* @{
*/
/**
* The callback data with request ID connector_request_id_data_service_send_data will point to this structure.
* The callback is called to get user data to send to Device Cloud. The callback will be called again if more_data
* field is set to connector_true. The bytes_used cannot exceed the bytes_available.
*/
typedef struct
{
    connector_transport_t CONST transport;  /**< transport method from where the callback is originated */
    void * user_context;                    /**< user context passed */

    uint8_t * CONST buffer;                 /**< to be filled with data to send */
    size_t CONST bytes_available;           /**< available bytes in buffer */
    size_t bytes_used;                      /**< bytes filled */
    connector_bool_t more_data;             /**< set to connector_true if more data to send */
} connector_data_service_send_data_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_status_t  Session status
* @{
*/
/**
* The callback data with request ID connector_request_id_data_service_send_status and
* connector_request_id_data_service_receive_status will point to this structure.
* The callback is called to report the the status why session is closed. User can free
* any allocated resources for this session after receing this callback.
*/
typedef struct
{
    connector_transport_t CONST transport;  /**< transport method used */
    void * user_context;                    /**< user context passed */

    enum
    {
        connector_data_service_status_complete,      /**< response is not requested and session is completed successfully */
        connector_data_service_status_cancel,        /**< session is cancelled by the user */
        connector_data_service_status_timeout,       /**< session timed out */
        connector_data_service_status_session_error  /**< error from lower communication layer  */
    } CONST status;       /**< reason for end of session */

    connector_session_error_t CONST session_error;   /**< lower communication layer error code */

} connector_data_service_status_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_send_response_t  Response from Etherios Device Cloud
* @{
*/
/**
* The callback data with request ID connector_request_id_data_service_send_response will point to this structure.
* The callback is called to pass Device Cloud response. User can free any allocated resources for this session
* after receing this callback.
*/
typedef struct
{
    connector_transport_t CONST transport;  /**< transport method used */
    void * user_context;                    /**< user context passed */

    enum
    {
        connector_data_service_send_response_success,       /**< send data success */
        connector_data_service_send_response_bad_request,   /**< at least some portion of the request is not valid */
        connector_data_service_send_response_unavailable,   /**< service not available, may retry later */
        connector_data_service_send_response_cloud_error    /**< Device Cloud encountered error while handling the request */
    } CONST response;     /**< Device Cloud response code for send data */

    char const * CONST hint;    /**< error hint returned from Device Cloud, NULL if success or hint is not provided */
} connector_data_service_send_response_t;
/**
* @}
*/


/**
* @defgroup connector_data_service_receive_target_t  The request target from Etherios Device Cloud
* @{
*/
/**
* The callback data with request ID connector_request_id_data_service_receive_target will point to
* this structure. The callback is called to pass the target for which the subsequent callback will be
* called with request data.
*/
typedef struct
{
    connector_transport_t CONST transport;  /**< transport method on which the request is received */
    void * user_context;                    /**< user can update this field with their context, the subsequent callback will carry this context */

    char const * CONST target;              /**< target of the data received */
    connector_bool_t CONST response_required;   /**< connector_true means Device Cloud needs the response and will get the callbacks to collect the response */
} connector_data_service_receive_target_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_receive_data_t  Request data from Etherios Device Cloud
* @{
*/
/**
* The callback data with request ID connector_request_id_data_service_receive_data will point to this structure.
* The callback is called to pass Device Cloud response. User can free any allocated resources for this session
* after receing this callback.
*/
typedef struct
{
    connector_transport_t CONST transport;  /**< transport method used */
    void * user_context;                    /**< user context passed */

    uint8_t const * CONST buffer;           /**< received request data from Device Cloud */
    size_t CONST bytes_used;                /**< bytes filled in the buffer */
    connector_bool_t CONST more_data;       /**< connector_true means more request data to follow */
} connector_data_service_receive_data_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_receive_reply_data_t  Response to Etherios Device Cloud
* @{
*/
/**
* The callback data with request ID connector_request_id_data_service_receive_reply_data will point
* to this structure. The callback is called to get the response to earlier request. User can free any
* allocated resources after returning the callback with no more response (more_data = connector_false).
*/
typedef struct
{
    connector_transport_t CONST transport;  /**< transport method used */
    void * user_context;                    /**< user context passed */

    uint8_t * CONST buffer;                 /**< to be filled with the response data */
    size_t CONST bytes_available;           /**< number of bytes available */
    size_t bytes_used;                      /**< number of bytes filled */
    connector_bool_t more_data;             /**< connector_true means more response to fill */
} connector_data_service_receive_reply_data_t;
/**
* @}
*/

#endif /* _CONNECTOR_DS_API_H */

