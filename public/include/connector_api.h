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
 /**
  * @file
  *  @brief Functions and prototypes for iDigi Connector
  *         public API
  *
  */
#ifndef _CONNECTOR_API_H
#define _CONNECTOR_API_H

/**
 * Current version of the iDigi connector that application is using or built for.
 *
 * Note current version number denotes:  1.1.0.0
 *                                       | | | |
 *                                       v v v v
 *                                    0x01010000UL
 */
#define CONNECTOR_VERSION   0x01030000UL

#include "connector_config.h"
#include "connector_types.h"

#if (defined CONNECTOR_FIRMWARE_SERVICE)
#include "connector_fw_api.h"
#endif

#define asizeof(array)  (sizeof array/sizeof array[0])

 /**
 * @defgroup connector_port_numbers iDigi Port Numbers
 * @{
 */
/**
 * iDigi server connect port number
 *
 * This port number is for connector_network_open callback to make
 * a connection to iDigi server.
 *
 * @see CONNECTOR_SSL_PORT
 * @see CONNECTOR_UDP_PORT
 * @see connector_network_open
 */
#define CONNECTOR_PORT       3197   /**< Port number used to connect to iDigi server. */

/**
 * iDigi server secured connect port number
 *
 * This port number is for connector_network_open callback to make
 * a secured connection to iDigi server.
 *
 * @see CONNECTOR_PORT
 * @see CONNECTOR_UDP_PORT
 * @see connector_network_open
 */
#define CONNECTOR_SSL_PORT   3199   /**< Secured port number used to connect to iDigi server. */

/**
 * iDigi server UDP port number
 *
 * This port number is for connector_network_open callback to communicate with
 * the iDigi server over UDP.
 *
 * @see CONNECTOR_PORT
 * @see CONNECTOR_SSL_PORT
 * @see connector_network_open
 */
#define CONNECTOR_UDP_PORT       3297   /**< UDP port number used to communicate with iDigi server. */
/**
* @}
*/

 /**
 * @defgroup connector_status_t idigi Status values
 * @{
 */
 /**
 * Status returned by iDigi connector API calls.
 */
typedef enum {
   connector_success,               /**< No error. */
   connector_init_error,            /**< iDigi connector was not initialized. */
   connector_invalid_data_size,     /**< Callback returned configuration with invalid size. */
   connector_invalid_data_range,    /**< Callback returned configuration that is out of range. */
   connector_invalid_data,          /**< Callback returned invalid data. Callback returned a NULL data. */
   connector_keepalive_error,       /**< iDigi connector did not receive keepalive messages. Server may be offline. */
   connector_bad_version,           /**< Invalid firmware version number. Incorrect firmware version number used in Remote Configuration (RCI) */
   connector_device_terminated,     /**< iDigi connector was terminated by user via connector_initiate_action call.
                                     All memory is freed and connector_init must be called to restart iDigi connector. */
   connector_service_busy,          /**< Someone else is using the same service or the device is busy. */
   connector_invalid_response,      /**< Received invalid response from the server. */
   connector_no_resource,           /**< Lack of resource */
   connector_unavailable,           /**< Not available to perform the specified action. */
   connector_idle,                  /**< iDigi connector is idling. iDigi connector has no message to process.
                                     Other task should be processed. */
   connector_working,               /**< iDigi connector has processed a message and should be called at the earliest possible time. */
   connector_pending,               /**< iDigi connector is waiting to process a message or a callback to complete. This allows
                                     iDigi connector to relinquish for other task to run. */
   connector_active,                /**< iDigi connector is processing a message and it should be called at the earliest possible time. */
   connector_abort,                 /**< iDigi connector was aborted and terminated either iDigi connector encountered fatal error or callback aborted iDigi connector.
                                     All memory is freed and connector_init must be called to restart iDigi connector. */
   connector_device_error,          /**< Close Callback returns error. If connector_step or connector_run is called again, it will re-establish the connection. */

   connector_exceed_timeout,        /**< Callback exceeded timeout value before it returned. */
   connector_invalid_payload_packet, /**< iDigi connector received invalid payload message. */
   connector_open_error             /**< Open callback was not successfully opened and returned @ref connector_callback_error.
                                     iDigi connector must be called again to continue running. It will reconnect if
                                     it's initially setup to connect automatically. */
} connector_status_t;
/**
* @}
*/

/**
* @defgroup connector_class_id_t Class IDs
* @{
*/
/**
* Class Id for which class is used in the application's callback.
* It tells class id for the request id passed to the application's callback.
*/
typedef enum {
    connector_class_config,             /**< Configuration Class Id */
    connector_class_operating_system,   /**< Operating System Class Id */
    connector_class_id_firmware,           /**< Firmware Facility Class Id */
    connector_class_data_service,       /**< Data Service Class Id */
    connector_class_remote_config_service, /**< Remote Configuration Class ID */
    connector_class_file_system,        /**< File System Class Id */
    connector_class_network_tcp,        /**< TCP Network Class ID */
    connector_class_network_udp,        /**< UDP Network Class ID */
    connector_class_network_sms,        /**< SMS Network Class ID */
    connector_class_status,             /**< Class ID for all status */
    connector_class_sm                  /**< Short message specific class ID */
} connector_class_t;
/**
* @}
*/

/**
* @defgroup connector_service_supported_status_t Service Support
* @{
*/
/**
* Service supported status which is used in the application's callback
* telling iDigi connector whether application supports a service or not.
* @see @ref firmware_support
* @see @ref data_service_support
*/
typedef enum {
    connector_service_unsupported,  /**< Service is not supported */
    connector_service_supported     /**< Service is supported */
} connector_service_supported_status_t;
/**
* @}
*/

/**
* @defgroup connector_config_request_t Configuration Requests
* @{
*/
/**
* Configuration Request Id passed to the application's callback for requesting configuration data.
* The class id for this connector_config_request_t is connector_class_config.
*/
typedef enum {
    connector_config_device_id,         /**< Requesting callback to return a unique device id which is used to identify the device.*/
    connector_config_vendor_id,         /**< Requesting callback to return a unique vendor id identifying the manufacturer of a device. */
    connector_config_device_type,       /**< Requesting callback to return device type that identifies the type of the device  */
    connector_config_server_url,        /**< Requesting callback to return iDigi Device Cloud URL which will be connected to */
    connector_config_connection_type,   /**< Requesting callback to return LAN or WAN connection type */
    connector_config_mac_addr,          /**< Requesting callback to return device's MAC addresss */
    connector_config_link_speed,        /**< Requesting callback to return link speed for WAN connection type */
    connector_config_phone_number,      /**< Requesting callback to return phone number dialed for WAN connection type */
    connector_config_tx_keepalive,      /**< Requesting callback to return server's Tx keep alive interval in seconds */
    connector_config_rx_keepalive,      /**< Requesting callback to return server's Rx keep alive interval in seconds */
    connector_config_wait_count,        /**< Requesting callback to return the number of intervals of not receiving a keep alive message after which a connection should be considered lost. */
    connector_config_ip_addr,           /**< Requesting callback to return device's IP address */
    connector_config_error_status,      /**< Error status notification which tells callback that error is encountered. */
    connector_config_firmware_facility, /**< Requesting callback to return whether firmware facility is supported or not. */
    connector_config_data_service,      /**< Requesting callback to return whether data service is supported or not. */
    connector_config_file_system,       /**< Requesting callback to return whether file system is supported or not. */
    connector_config_remote_configuration, /**< Requesting callback to return whether remote configuration is supported or not. */
    connector_config_max_transaction,   /**< Requesting callback to obtain maximum messaging sessions supported by client. */
    connector_config_device_id_method,  /**< Requesting callback to obtain method on how device id is generated */
    connector_config_imei_number,       /**< Requesting callback to return GSM IMEI number */
    connector_config_network_tcp,       /**< Requesting callback to return whether connection over TCP need to start now. */
    connector_config_network_udp,       /**< Requesting callback to return whether connection over UDP need to start now. */
    connector_config_network_sms,       /**< Requesting callback to return whether connection over SMS need to start now. */
    connector_config_wan_type,          /**< Requesting callback to return WAN type used. It tells iDigi connector whether it's GSM IMEI, CDMA ESN or CDMA MEID. */
    connector_config_esn,               /**< Requesting callback to return CDMA ESN (Electronic Serial Number) */
    connector_config_meid,              /**< Requesting callback to return CDMA MEID (Mobile Equipment Identifier) */
    connector_config_identity_verification,     /**< Requesting callback to return identity verification form. */
    connector_config_password,          /**< Requesting callback to return password for the password identity verification form */
    connector_config_sms_service_id     /**< Requesting callback to return service ID to be used as a preamble in each message */
} connector_config_request_t;
/**
* @}
*/

/**
* @defgroup connector_device_id_method_t Device ID Method Types
* @{
*/
/**
 * Device ID method returned by the application's callback for @ref connector_config_device_id_method callback.
 */
typedef enum {
    connector_auto_device_id_method,                  /**< Callback returns this type telling iDigi connector to
                                                       generate the device ID from MAC address (See @ref connector_config_mac_addr callback)
                                                       for LAN connection type or genearte the device ID according to the @ref wan_type.
                                                       @note iDigi connector will not call @ref connector_config_device_id callback. */
    connector_manual_device_id_method                 /**< Callback returns this type telling iDigi connector to retrieve device ID from @ref connector_config_device_id callback */
} connector_device_id_method_t;
/**
* @}
*/

/**
* @defgroup connector_identity_verification_t  Identity Verification Form Types
* @{
*/
/**
 * Identify verification returned by the application's callback for @ref connector_config_identity_verification callback.
 */
typedef enum {
    connector_simple_identity_verification,         /**< Callback returns this form for simple identity verification. iDigi connector just transmits the
                                                     device ID and the iDigi Device Cloud URL. */
    connector_password_identity_verification        /**< Callback returns this form for password identity verification. iDigi connector exchanges a pre-shared
                                                     secret password with the iDigi Device Cloud. The password must match the password set in the iDigi Device Cloud.
                                                     @note iDigi connector will call @ref connector_config_password callback for the password. */
} connector_identity_verification_t;
/**
* @}
*/

/**
* @defgroup connector_network_request_t Network Request IDs
* @{
*/
/**
* Network Request ID passed to the application's callback for network interface.
* The class id for this connector_network_request_t is connector_class_network_tcp,
* connector_class_network_udp, or connector_class_network_sms.
*/
typedef enum {
    connector_network_open,     /**< Requesting callback to set up and make connection to the iDigi Device Cloud */
    connector_network_send,     /**< Requesting callback to send data to the iDigi Device Cloud */
    connector_network_receive,  /**< Requesting callback to receive data from the iDigi Device Cloud */
    connector_network_close     /**< Requesting callback to close the iDigi Device Cloud connection */
} connector_network_request_t;
/**
* @}
*/


 /**
 * @defgroup connector_os_request_t OS Request IDs
 * @{
 */
 /**
 * Operating System Request ID passed to the application's callback for operating system interface.
 * The class id for this connector_os_request_t is connector_class_operating_system.
 */
typedef enum {
    connector_os_malloc,            /**< Callback used to dynamically allocate memory.. */
    connector_os_free,              /**< Callback is called to free previous allocated memory. */
    connector_os_system_up_time,    /**< Callback is called to return system up time in seconds. It is the time that a device has been up and running. */
    connector_os_yield,             /**< Callback is called with @ref connector_status_t to relinquish for other task to run when @ref connector_run is used. */
    connector_os_reboot            /**< Callback is called to reboot the system. */
} connector_os_request_t;
/**
* @}
*/

/**
* @defgroup connector_remote_config_request_t Remote Configuration Requests
* @{
*/
/**
* Remote Configuration Request Id passed to the application's callback to query or set remote configuration data.
* The class id for this connector_remote_config_request_t is connector_class_remote_config_service.
*/

typedef enum {
    connector_remote_config_session_start,  /**< inform callback to start remote configuration request */
    connector_remote_config_action_start,   /**< requesting callback to start query or set remote configuration data */
    connector_remote_config_group_start,    /**< requesting callback to start query or set an individual configuration group */
    connector_remote_config_group_process,  /**< requesting callback to query or set an element or field of a configuration group */
    connector_remote_config_group_end,      /**< requesting callback to end query or set an individual configuration group */
    connector_remote_config_action_end,     /**< requesting callback to end query or set remote configuration data */
    connector_remote_config_session_end,    /**< inform callback to end remote configuration request
                                            Callback may start writing data into NVRAM for set remote configuration request.
                                            Callback should end and release any resources used when it's done. */
    connector_remote_config_session_cancel  /**< Requesting callback to abort and cancel any query or set remote configuration request.
                                            Callback should stop and release any resources used */
} connector_remote_config_request_t;
/**
* @}
*/

/**
* @defgroup connector_file_system_request_t File System Request IDs
* @{
*/
/**
* File System Request Id passed to the application's callback to use file system.
* The class id for this connector_file_system_request_t is connector_class_file_system.
*/

typedef enum {
    connector_file_system_open,             /**< inform callback to open a file */
    connector_file_system_read,             /**< inform callback to read a file */
    connector_file_system_write,            /**< inform callback to write a file */
    connector_file_system_lseek,            /**< inform callback to seek file position */
    connector_file_system_ftruncate,        /**< inform callback to truncate a file */
    connector_file_system_close,            /**< inform callback to close a file */
    connector_file_system_rm,               /**< inform callback to remove a file */
    connector_file_system_stat,             /**< inform callback to geten file status */
    connector_file_system_opendir,          /**< inform callback to start processing a directory */
    connector_file_system_readdir,          /**< inform callback to read next directory entry */
    connector_file_system_closedir,         /**< inform callback to end processing a directory */
    connector_file_system_strerror,         /**< inform callback to get an error code description  */
    connector_file_system_msg_error,        /**< inform callback of an error in messaging layer */
    connector_file_system_hash              /**< inform callback to return file hash value */
} connector_file_system_request_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_request_t Data Service Request IDs
* @{
*/
/**
 * Data service request ID, passed to the application callback
 * to request the data, to pass the response, and to pass the
 * error.
 */
typedef enum {
    connector_data_service_put_request,     /**< Indicates data service request related to send data to the iDigi Device Cloud */
    connector_data_service_device_request,  /**< Indicates data service request related to receive data from the iDigi Device Cloud */
    connector_data_service_dp_response     /**< Used in a callback when the iDigi Connector receives a response to data point request */
} connector_data_service_request_t;
/**
* @}
*/

/**
* @defgroup connector_os_status_type_t OS Status Reason Types
* @{
*/
/**
* TCP Status values passed to the application's callback for @ref connector_tcp_status.
*
* These status values are used for an event notification.
*/
typedef enum {
    connector_tcp_communication_started,      /**< iDigi connector has established connection with the iDigi Device Cloud and starts communicating. */
    connector_tcp_keepalive_missed,           /**< iDigi connector didn't receive a keep alive message within the specified keep alive interval @ref tx_keepalive. */
    connector_tcp_keepalive_restored          /**< iDigi connector received a keep alive message after a keep alive message was not received.
                                         This is called after the callback has been previously notified with connector_miss_keepalive status. */
} connector_tcp_status_t;
/**
* @}
*/

/**
* @defgroup connector_status_request_t  iDigi Connector/Cloud status request IDs
* @{
*/
/**
* These request IDs are used whenever the iDigi Connector wants to communicate either its
* status or the iDigi Device Cloud's status to the user.The class ID associated with these
* request ID is connector_class_status.
*/
typedef enum {
    connector_status_ping_response,    /**< Used in a callback when the iDigi Connector receives a status/ping response from the server */
    connector_status_ping_request,     /**< Used in a callback when the iDigi Connector receives a status/ping request from the server */
    connector_status_tcp,              /**< Used in a callback for iDigi connector TCP status. The callback is called to notify the application that
                                        TCP connection has been established, a keep-alive message was not received, or keep-alive message was received and restored.
                                          @see connector_tcp_status_t */
    connector_status_stop_completed    /**< Used in a callback when the iDigi connector has stopped a transport running via @ref connector_initiate_action call with @ref connector_initiate_transport_stop. */

} connector_status_request_t;
/**
* @}
*/

/**
* @defgroup connector_sm_request_t Short message specific request IDs
* @{
*/
/**
* Short message related callbacks will use these request IDs. The class ID associated with these request ID is
* connector_class_sm and supported transport methods under this class are SMS and UDP.
*/
typedef enum {
    connector_sm_cli_request,     /**< Indicates CLI request is received from the iDigi device cloud. Also used to get the CLI response from the user */
    connector_sm_server_to_device_config,  /**< Used when device receives a server to device config request from iDigi Device Cloud. Used only if the transport method is SMS */
    connector_sm_device_to_server_config,  /**< Used when device receives a device to server config response from iDigi Device Cloud. Used only if the transport method is SMS */
    connector_sm_more_data,       /**< More data is available on the server. Applicable only if UDP transport method is used.
                                   User must use new request (can be ping) to pull the pending messages from iDigi Device Cloud. */
    connector_sm_opaque_response    /**< iDigi Connector uses this to provide the cloud response for which there is no associated request. */
} connector_sm_request_t;
/**
* @}
*/

/**
* @defgroup connector_initiate_request_t Initiate action enumeration
* @{
*/
/**
* Request IDs used in connector_initiate_action()
*/
typedef enum {
    connector_initiate_terminate,       /**< Terminates and stops iDigi connector from running. */
    connector_initiate_data_service,    /**< Initiates the action to send generic data to the iDigi Device Cloud, the data will be stored in a file on the cloud. */
    connector_initiate_transport_start, /**< Starts the specified (TCP, UDP or SMS) transport method */
    connector_initiate_transport_stop,  /**< Stops the specified (TCP, UDP or SMS) transport method */
    connector_initiate_status_message,  /**< Sends status message to the iDigi Device Cloud. Supported only under UDP and SMS transport methods */
    connector_initiate_binary_point,    /**< Initiates the action to send data points to the iDigi Device Cloud */
    connector_initiate_data_point,      /**< Initiates the action to send data points to the iDigi Device Cloud */
    connector_initiate_config_message,  /**< Sends device configuration to the iDigi Device Cloud. Supported only under SMS transport method */
    connector_initiate_session_cancel   /**< Initiates the action to cancel the session, can be used in case of timeout. Supported only under UDP and SMS transport methods */
} connector_initiate_request_t;
/**
* @}
*/

/**
* @defgroup connector_connection_type_t iDigi connection types
* @{
*/
/**
* Connection type for @see connector_config_connection_type callback
*/
typedef enum {
   connector_lan_connection_type,   /**< LAN connection type for Ethernet or WiFi */
   connector_wan_connection_type    /**< WAN connection type for PPP over Modem */
} connector_connection_type_t;
/**
* @}
*/

/**
* @defgroup connector_wan_type_t iDigi WAN types for WAN connection type
* @{
*/
/**
 * WAN connection type for @ref connector_config_wan_type callback.
 */
typedef enum {
    connector_imei_wan_type,    /**< IMEI number for GSM network */
    connector_esn_wan_type,     /**< ESN for CDMA network */
    connector_meid_wan_type     /**< MEID for CDMA network */
} connector_wan_type_t;
/**
* @}
*/


/**
* @defgroup.connector_callback_status_t Callback return status
* @{
*/
/**
* Return status from iDigi connector callback
*/
typedef enum  {
    connector_callback_continue,        /**< Continues with no error */
    connector_callback_busy,            /**< Callback is busy */
    connector_callback_abort,           /**< Aborts iDigi connector. iDigi connector frees all memory. @ref connector_init must be called to restart iDigi connector. */
    connector_callback_unrecognized,    /**< Unsupported callback request */
    connector_callback_error            /**< Exits iDigi connector when error is encountered. iDigi connector will try reconnecting to the iDigi Device Cloud
                                         if @ref connector_step or @ref connector_run is called again. */
} connector_callback_status_t;
/**
* @}
*/

/**
* @defgroup connector_request_t Request IDs
* @{
*/
/**
* Request IDs passed to callback identifying the type of request
* @see connector_class_t
*/
typedef union {
   connector_config_request_t config_request;               /**< Configuration request ID for configuration class */
   connector_os_request_t os_request;                       /**< Operating system request ID for operating system class */
   connector_request_id_firmware_t firmware_request;           /**< Firmware request ID for firmware facility class */
   connector_data_service_request_t data_service_request;   /**< Data service request ID for data service class */
   connector_remote_config_request_t remote_config_request; /**< Remote configuration request ID for remote configuration service class */
   connector_file_system_request_t   file_system_request;   /**< File system request ID for file system class */
   connector_network_request_t  network_request;            /**< Network request ID for network TCP class, network UDP class, and network SMS class */
   connector_status_request_t status_request;               /**< Status request ID for status class */
   connector_sm_request_t sm_request;                       /**< Short message request ID for SM class */
} connector_request_t;
/**
* @}
*/

/**
* @defgroup connector_handle_t iDigi Handle
* @{
*/
/**
*
* iDigi connector Handle type that is used throughout iDigi connector APIs, this is used by the application
* to store context information about a connections, for example this could
* be used to store a file descriptor or a pointer to a structure.
*/
#define connector_handle_t void *
/**
* @}
*/

/**
* @defgroup connector_error_status_t Error Status
* @{
*/
/**
* Error status structure for @ref connector_config_error_status callback which
* is called when iDigi connector encounters an error.
* @see connector_config_request_t
*/
typedef struct  {
    connector_class_t class_id;         /**< Class ID which iDigi connector encounters error with */
    connector_request_t request_id;     /**< Request ID which iDigi connector encounters error with */
    connector_status_t status;          /**< Error status */
} connector_error_status_t;
/**
* @}
*/

/**
* @defgroup connector_network_open_data_t Network Open Data Structure
* @{
*/
/**
* Network open data structure for @ref connector_network_open callback which is called to open and connect to the iDigi Device Cloud.
*/
typedef struct  {
    char const * server_url;        /**< Pointer to Etherios Cloud URL */
    connector_network_handle_t * handle;    /**< Application defined network handle associated with the connection */
} connector_network_open_data_t;
/**
* @}
*/


/**
* @defgroup connector_network_send_data_t Network Send Data Structure
* @{
*/
/**
* Send data structure for @ref connector_network_send callback which is called to send data to the iDigi Device Cloud.
*/
typedef struct  {
    connector_network_handle_t * network_handle;    /**< Pointer to network handle associated with a connection through the connector_network_open callback */
    uint8_t const * buffer;                     /**< Pointer to data to be sent */
    size_t bytes_available;                         /**< Number of bytes to send in the buffer */
    size_t bytes_used;                              /**< Number of bytes sent */
} connector_network_send_data_t;
/**
* @}
*/

/**
* @defgroup connector_network_receive_data_t Network Receive Request
* @{
*/
/**
* Read request structure for connector_network_receive callback which is called to receive
* a specified number of bytes data from the iDigi Device Cloud.
*/
typedef struct  {
    connector_network_handle_t * network_handle;    /**< Pointer to network handle associated with a connection through the connector_network_open callback */
    uint8_t * buffer;                               /**< Pointer to memory where callback writes received data to */
    size_t bytes_available;                         /**< Number of bytes available in the buffer */
    size_t bytes_used;                              /**< Number of bytes received and copied to the buffer */
} connector_network_receive_data_t;
/**
* @}
*/

/**
* @defgroup connector_auto_connect_type_t Action on Network Close
* @{
*/
/**
* Response to @ref connector_network_close callback which is called to close the connection to the iDigi Device Cloud.
*/
typedef enum {

    connector_auto_connect,     /**< Connect to the iDigi Device Cloud automatically */
    connector_manual_connect    /**< Connect to the iDigi Device Cloud manually */

} connector_auto_connect_type_t;
/**
* @}
*/


/**
* @defgroup connector_close_status_t iDigi Connection Close Status Values
* @{
*/
/**
* Reasons for @ref connector_network_close callback which is called to close the connection to the iDigi Device Cloud.
*/
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
    connector_close_status_device_error                /**< iDigi connector received error from callback which requires to close the connection. */
} connector_close_status_t;
/**
* @}
*/

/**
* @defgroup connector_close_data_t Network Close Request
* @{
*/
/**
* Close request structure for @ref connector_network_close callback which is called to close the connection to the iDigi Device Cloud.
*/
typedef struct  {
    connector_network_handle_t * network_handle;    /**< Pointer to network handle associated with a connection through the connector_network_open callback */
    connector_close_status_t  status;                     /**< Reason for closing the network handle */

    connector_auto_connect_type_t  connect_action;
} connector_network_close_data_t;
/**
* @}
*/


/**
* @defgroup connector_msg_error_t iDigi Connector Error Codes
* @{
*/
/**
 * Error values returned either from the remote the iDigi Device Cloud or
 * from the local iDigi client. These are errors originated from
 * messaging layer, where compression/decompression, resource
 * allocation and state handling take place.
 */
typedef enum
{
    connector_msg_error_none,                   /**< Success */
    connector_msg_error_fatal,                  /**< Generally represents internal, unexpected error */
    connector_msg_error_invalid_opcode,         /**< Opcode used in the message is invalid/unsupported */
    connector_msg_error_format,                 /**< Packet is framed incorrectly */
    connector_msg_error_session_in_use,         /**< Session with same ID is already in use */
    connector_msg_error_unknown_session,        /**< Session is not opened or already closed */
    connector_msg_error_compression_failure,    /**< Failed during compression of the data to send */
    connector_msg_error_decompression_failure,  /**< Failed during decompression of the received data */
    connector_msg_error_memory,                 /**< Malloc failed, try to restrict the number of active sessions */
    connector_msg_error_send,                   /**< Send socket error */
    connector_msg_error_cancel,                 /**< Used to force termination of a session */
    connector_msg_error_busy,                   /**< Either the iDigi Device Cloud or iDigi client is busy processing */
    connector_msg_error_ack,                    /**< Invalid ack count */
    connector_msg_error_timeout,                /**< Session timed out */
    connector_msg_error_no_service,             /**< Requested service is not supported */
    connector_msg_error_count                   /**< Maximum error count value, new value goes before this element */
} connector_msg_error_t;
/**
* @}
*/

/**
* @defgroup connector_session_status_t Status of a session
* @{
*/
/**
 * Possible reason for a session to complete, it could be a success response from the iDigi Cloud or from a device.
 */
typedef enum
{
    connector_session_status_success,       /**< Got success response from the iDigi Cloud */
    connector_session_status_complete,      /**< Session completed, maybe response not needed */
    connector_session_status_cancel,        /**< Session is cancelled */
    connector_session_status_timeout,       /**< Session is timed out */
    connector_session_status_no_resource,   /**< Session terminated due to lack of resource */
    connector_session_status_cloud_error,   /**< Received error from the iDigi Cloud */
    connector_session_status_device_error,  /**< An application error from a device */
    connector_session_status_internal_error /**< Error originated in iDigi Client */
} connector_session_status_t;
/**
* @}
*/

/**
* @defgroup put_flags Data service put flags
* @{
*/
/**
 * Message archive bit flag
 *
 * Used in connector_data_service_put_request_t indicating server needs to archive
 * the message file. Valid only if the transport method is TCP.
 *
 * @see connector_data_service_put_request_t
 * @see connector_data_service_put_request callback
 */
#define CONNECTOR_DATA_PUT_ARCHIVE   0x0001

/**
 * Message append bit flag
 *
 * Used in connector_data_service_put_request_t indicating server need to append to
 * existing data if applicable. Valid only if the transport method is TCP.
 *
 * @see connector_data_service_put_request_t
 * @see connector_data_service_put_request callback
 */
#define CONNECTOR_DATA_PUT_APPEND    0x0002

/**
* Response not needed bit flag
*
* Used in all device originated requests on UDP and SMS transport indicating that
* the device doesn't need response to the request.
*
* @see connector_data_service_put_request_t
* @see connector_message_status_request_t
* @see connector_data_point_request_t
* @see connector_device_to_server_config_t
*/
#define CONNECTOR_DATA_RESPONSE_NOT_NEEDED    0x0004

/**
* @}
*/

/**
* @defgroup connector_transport_t  Transport layer type
* @{
*/
/**
* iDigi Cloud Connector's will use the specified transport method when sending a request to the
* iDigi Device Cloud.
*/
typedef enum
{
    connector_transport_tcp, /**< Use TCP. @ref CONNECTOR_TRANSPORT_TCP must be enabled. */
    connector_transport_udp, /**< Use UDP. @ref CONNECTOR_TRANSPORT_UDP must be enabled. */
    connector_transport_sms, /**< Use SMS. @ref CONNECTOR_TRANSPORT_SMS must be enabled. */
    connector_transport_all  /**< All transports. */
} connector_transport_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_put_request_t connector_data_service_put_request_t
* @{
*/
/**
 * Put request header information. Used as initiate_action() request parameter to
 * initiate the send operation. Subsequent handling is done via callback functions.
 * This header information is returned as user_context in each callback request.
 * If the transport layer is UDP or SMS, the user_context in subsequent callbacks
 * will contain the context field value.
 */
typedef struct
{
    connector_transport_t transport; /**< Transport method to send data to the iDigi Device Cloud */
    char const * path;           /**< NUL terminated file path where user wants to store the data on the iDigi Device Cloud */
    char const * content_type;   /**< NUL terminated content type (text/plain, text/xml, application/json, etc. */
    unsigned int flags;          /**< Indicates whether server should archive and/or append, one of the following @ref put_flags */
    void const * context;        /**< To hold the user context */
} connector_data_service_put_request_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_type_t Data service types
* @{
*/
/**
* Data service types which is used in connector_data_service_device_request and
* connector_data_service_put_request callbacks indicating the type of message.
*/
typedef enum
{
    connector_data_service_type_need_data,      /**< Indicating callback needs to write data onto specified buffer which will be sent to server */
    connector_data_service_type_have_data,      /**< Indicating a message contains data from server that needs callback to process it. */
    connector_data_service_type_error,          /**< Indicating error is encountered. Message will be terminated */
    connector_data_service_type_total_length,   /**< Callback to get the total length of the data to be sent. Not applicable in TCP transport method */
    connector_data_service_type_session_status  /**< Callback to pass the reason for session complete. Not applicable in TCP transport method */
} connector_data_service_type_t;
/**
* @}
*/

/**
* @defgroup data_service_flags Data Service Flags
* @{
*/
/**
 * This flag is used in to indicate that this is the first message for this
 * data transfer.
 *
 * @see connector_data_service_put_request callback
 * @see connector_data_service_device_request callback
 */
#define CONNECTOR_MSG_FIRST_DATA            0x0001  /**< First chunk of data */

/**
 * This flag is to indicate that this is the last message for this transfer.
 *
 * @see connector_data_service_put_request callback
 * @see connector_data_service_device_request callback
 */
#define CONNECTOR_MSG_LAST_DATA             0x0002  /**< Last chunk of data */

/**
* This flag is to indicate whether the response is needed for this request or not.
* Used only under SMS and UDP transport method. In case of TCP this flag is ignored
* and response is always needed.
*
* @see connector_data_service_device_request callback
*/
#define CONNECTOR_MSG_RESPONSE_NOT_NEEDED   0x0004  /**< Response is not needed */

/**
 * This flag is used to indicate tha the message was not processed.
 *
 * @see connector_data_service_device_request callback
 */
#define CONNECTOR_MSG_DATA_NOT_PROCESSED    0x0010  /**< This flag is used in connector_data_service_device_request callback
                                                     telling server that callback did not process the message */
/**
 * Message success bit flag
 * This flag is used in connector_data_service_block_t indicating
 * message successfully handled.
 *
 * @see connector_data_service_put_request callback
 */
#define CONNECTOR_MSG_RESP_SUCCESS          0x0100  /**< This flag is used in connector_data_service_put_request callback
                                                     telling the callback that server successfully received the message. */
/**
 * This flag is used to indicate that the message was invalid.
 *
 * @see connector_data_service_put_request callback
 */
#define CONNECTOR_MSG_BAD_REQUEST           0x0200  /**< This flag is used in connector_data_service_put_request callback
                                                     from server telling the callback that some portion of the data was invalid. */
/**
 * This flag is used to indicate that the service is unavailable to process the message.
 *
 * @see connector_data_service_put_request callback
 */
#define CONNECTOR_MSG_UNAVAILABLE           0x0400  /**< This flag is used in connector_data_service_put_request callback
                                                     from server telling the callback that service is unavailable due to overload
                                                     or other issues. Callback may try to resend the message later. */
/**
 * This flag is used to indicate that the server encountered an error handling the message.
 *
 * @see connector_data_service_put_request callback
 */
#define CONNECTOR_MSG_SERVER_ERROR          0x0800  /**< This flag is used in connector_data_service_put_request callback
                                                     from server telling the callback that server encountered an error handling the message. */
/**
* @}
*/

/**
* @defgroup.connector_data_service_block_t Data Service Block
* @{
*/
/**
* Data service block structure is used to send data between the iDigi Device cloud and client.
* This structure is used in connector_data_service_put_request and connector_data_service_device_request callbacks.
*
* When message type is connector_data_service_type_need_data in connector_data_service_msg_request_t,
* callback needs to update this structure with data to be sent to server.
*
* When message type is connector_data_service_type_have_data in connector_data_service_msg_request_t,
* this structure contains data for callback to process.
*
* @see connector_data_service_request_t
* @see connector_initiate_action
* @see connector_data_service_put_request_t
* @see connector_data_service_device_request_t
* @see connector_data_service_type_t

*/
typedef struct
{
    void * data;                /**< Pointer to data */
    size_t length_in_bytes;     /**< Number of bytes in data */
    unsigned int flags;         /**< Bit mask flags. See each callback for specified bit mask flags, defined in @ref data_service_flags*/
} connector_data_service_block_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_msg_request_t Data Service Message Request
* @{
*/
/**
* Data service message request structure is used to tell the callback to process data from the
* iDigi Device Cloud, to return data to be sent to the iDigi Device Cloud, or to cancel an active message.
*
* This structure is used in connector_data_service_put_request and connector_data_service_device_request callbacks.
*
* @see connector_data_service_request_t
* @see connector_initiate_action
* @see connector_data_service_put_request_t
* @see connector_data_service_device_request_t
* @see connector_data_service_type_t
*/
typedef struct
{
    void * service_context;                     /**< Service context is pointer to connector_data_service_put_request_t for connector_data_service_put_request callback
                                                    or to connector_data_service_device_request_t for connector_data_service_device_request callback. */
    connector_data_service_type_t message_type;     /**< It contains connector_data_service_type_need_data to request callback for data to be sent to server,
                                                   connector_data_service_type_have_data to tell callback to process data from server, or
                                                   connector_data_service_type_error to tell callback to cancel the message since error is encountered. */
    connector_data_service_block_t * server_data;   /**< It's pointer to data from server to be processed for connector_data_service_type_have_data message type or
                                                     pointer to error status for connector_data_service_type_error message type. */
} connector_data_service_msg_request_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_msg_response_t Data service response message
* @{
*/
/**
* Data service message response structure is used in connector_data_service_put_request
* and connector_data_service_device_request callbacks to return data to be sent to the
* iDigi Device Cloud, or to cancel the message.
*
* @see connector_data_service_request_t
* @see connector_data_service_type_t
*/
typedef struct
{
    void * user_context;                        /**< Used for connector_data_service_device_request callback's context which will
                                                    be returned on subsequent callbacks for its reference.
                                                    For connector_data_service_put_request callback, it's not used. */
    connector_msg_error_t message_status;           /**< Callback writes error status when it encounters error and cancels the message */
    connector_data_service_block_t * client_data;   /**< Pointer to memory where callback writes data to for connector_data_service_type_need_data message type */
} connector_data_service_msg_response_t;
/**
* @}
*/

/**
* @defgroup connector_data_service_device_request_t Data service device request
* @{
*/
/**
* Data service device request structure is used in @see connector_data_service_device_request
* callback to process device request. connector_data_service_device_request callback is passed with
* @see connector_sevice_msg_request_t where service_context is pointing to this structure.
*
* @see connector_data_service_type_t
*/
typedef struct
{
    void * device_handle;       /**< Device handle for current device request */
    char const * target;        /**< Contains nul terminated target name. The target name is only provided on
                                    the first chunk of data (CONNECTOR_MSG_FIRST_DATA bit is set on flags. @see connector_data_service_block_t).
                                    Otherwise, it’s null. */
} connector_data_service_device_request_t;

/**
* @}
*/

/**
* @defgroup connector_file_seek_origin_t File seek origin
* @{
*/
/**
 * Seek file position relative to start-of-file.
 *
 * @see connector_file_lseek_request_t
 * @see connector_file_system_lseek
 */
#define CONNECTOR_SEEK_SET	0

/**
 * Seek file position relative to current position.
 *
 * @see connector_file_lseek_request_t
 * @see connector_file_system_lseek
 */
#define CONNECTOR_SEEK_CUR	1

/**
 * Seek file position relative to end-of-file.
 *
 * @see connector_file_lseek_request_t
 * @see connector_file_system_lseek
 */
#define CONNECTOR_SEEK_END	2
/**
* @}
*/

/**
* @defgroup file_open_flag_t File open flags
* @{
*/
/**
 * Open file for reading only.
 *
 * @see connector_file_open_request_t
 * @see connector_file_system_open callback
 */
#define	CONNECTOR_O_RDONLY	0

/**
 * Open for writing only.
 *
 * @see connector_file_open_request_t
 * @see connector_file_system_open callback
 */
#define	CONNECTOR_O_WRONLY	1

/**
 * Open for reading and writing.
 *
 * @see connector_file_open_request_t
 * @see connector_file_system_open callback
 */
#define	CONNECTOR_O_RDWR	2

/**
 * File offset shall be set to the end of the file prior to each write.
 *
 * @see connector_file_open_request_t
 * @see connector_file_system_open callback
 */
#define	CONNECTOR_O_APPEND	0x0008

/**
 * Create file, if does not exist.
 *
 * @see connector_file_open_request_t
 * @see connector_file_system_open callback
 */
#define	CONNECTOR_O_CREAT	0x0200

/**
 *
 * Truncate file, successfully opened for writing to 0 length, don't change
 * the owner and ile access modes.
 *
 * @see connector_file_open_request_t
 * @see connector_file_system_open callback
 */
#define	CONNECTOR_O_TRUNC	0x0400
/**
* @}
*/

/**
* @defgroup file_stat_flag_t File status flags
* @{
*/
/**
 * File is a directory.
 *
 * @see connector_file_stat_t
 * @see connector_file_system_stat callback
 */
#define CONNECTOR_FILE_IS_DIR   0x01

/**
 * File is a regular file.
 *
 * @see connector_file_stat_t
 * @see connector_file_system_stat callback
 */
#define CONNECTOR_FILE_IS_REG   0x02
/**
* @}
*/

/**
* @defgroup connector_file_error_status_t File system error status
* @{
*/
/**
* Error code, used on return in the error_status field of @ref connector_file_error_data_t
* in all file system callbacks.
*/
typedef enum
{
    connector_file_noerror,                      /**< No error */
    connector_file_user_cancel,                  /**< User application requests to cancel the session */
    connector_file_unspec_error,                 /**< Fatal unspecified error */
    connector_file_path_not_found,               /**< Path not found */
    connector_file_insufficient_storage_space,   /**< Insufficient storage space */
    connector_file_request_format_error,         /**< Request format error */
    connector_file_invalid_parameter,            /**< Invalid parameter */
    connector_file_out_of_memory,                /**< Out of memory */
    connector_file_permision_denied              /**< Permision denied */
} connector_file_error_status_t;
/**
* @}
*/

/**
* @defgroup connector_file_hash_algorithm_t File system hash algorithm
* @{
*/
/**
* Hash algorithm gives different options for hash values returned in the file lisings.
*
* @see @ref connector_file_system_stat
* @see @ref connector_file_system_hash
*/
typedef enum
{
    connector_file_hash_none,       /**< Don't return hash value */
    connector_file_hash_best,       /**< Use best available algorithm */
    connector_file_hash_crc32,      /**< Use crc32 */
    connector_file_hash_md5         /**< Use md5 */
} connector_file_hash_algorithm_t;
/**
* @}
*/

/**
* @defgroup connector_file_stat_t File status data
* @{
*/
/**
* File status data structure is used to return the status of a direcory or a file, specified by the path.
* It is used in @ref connector_file_stat_response_t for @ref connector_file_system_stat callback.
* The returned hash_alg value will be used in the consequent @ref connector_file_system_hash callbacks.
*/
typedef struct
{
  uint32_t     last_modified; /**< Last modified time for the entry (seconds since 1970). If not supported, use 0 */
  size_t       file_size;               /**< File size in bytes */
  connector_file_hash_algorithm_t hash_alg; /**< hash algorithm */
  uint8_t flags;                   /**< 0, or @ref file_stat_flag_t */
} connector_file_stat_t;
/**
* @}
*/

/**
* @defgroup connector_file_request_t File or directory request
* @{
*/
/**
* File or directory request structure is used for @ref connector_file_system_read, @ref connector_file_system_close,
* @ref connector_file_system_readdir, and @ref connector_file_system_closedir,
*/
typedef struct
{
    void * handle;            /**< Application defined file or directory handle */

} connector_file_request_t;
/**
* @}
*/

/**
* @defgroup connector_file_lseek_request_t File lseek request
* @{
*/
/**
* File lseek request structure is used for @ref connector_file_system_lseek callback.
*/
typedef struct
{
    void   * handle;      /**< Application defined file handle */
    long int offset;      /**< File offset */
    int      origin;      /**< File seek origin of @ref connector_file_seek_origin_t type */

} connector_file_lseek_request_t;
/**
* @}
*/

/**
* @defgroup connector_file_ftruncate_request_t File ftruncate request
* @{
*/
/**
* File ftruncate request structure is used for @ref connector_file_system_ftruncate callback.
*/
typedef struct
{
    void   * handle; /**< Application defined file handle */
    long int length;      /**< File length in bytes to truncate to */

} connector_file_ftruncate_request_t;
/**
* @}
*/

/**
* @defgroup connector_file_write_request_t File write request
* @{
*/
/**
* File write request structure is used for @ref connector_file_system_write callback.
*/
typedef struct
{
    void       * handle;        /**< Application defined file handle */
    void const * data_ptr;      /**< A pointer to data to be written to a file */
    size_t       size_in_bytes; /**< Number of bytes to write */

} connector_file_write_request_t;
/**
* @}
*/

/**
* @defgroup connector_file_open_request_t File open request
* @{
*/
/**
* File open request structure is used for @ref connector_file_system_open callback.
*/
typedef struct
{
    char const * path;                      /**< File path */
    int          oflag;                     /**< bitwise-inclusive OR of @ref file_open_flag_t flags */
} connector_file_open_request_t;
/**
* @}
*/

/**
* @defgroup connector_file_stat_request_t File status request
* @{
*/
/**
* File status request structure is used for @ref connector_file_system_stat and @ref connector_file_system_hash
* callbacks.
*/
typedef struct
{
    char const * path;                      /**< File path */
    connector_file_hash_algorithm_t hash_alg;   /**< suggested hash algorithm */
} connector_file_stat_request_t;
/**
* @}
*/

/**
* @defgroup connector_file_path_request_t File path request
* @{
*/
/**
* File path request structure is used for @ref connector_file_system_rm and
* @ref connector_file_system_opendir callbacks.
*/
typedef struct
{
    char const * path;                      /**< File path */
} connector_file_path_request_t;
/**
* @}
*/

/**
* @defgroup connector_file_error_data_t File error data
* @{
*/
/**
* Error data structure is used to return error status and error token for all file system callbacks.
* An error token is used to return an error description in a future @ref connector_file_system_strerror callback.
*
*/
typedef struct
{
    void const * errnum;                    /**< Application defined error token.*/
    connector_file_error_status_t error_status; /**< Error status of @ref connector_file_error_status_t type */
} connector_file_error_data_t;
/**
* @}
*/

/**
* @defgroup connector_file_error_request_t File system messaging error request
* @{
*/
/**
* Messaging error request structure is used for @ref connector_file_system_msg_error callback.
*/
typedef struct
{
    connector_msg_error_t message_status;   /**< Error status in messaging layer */
} connector_file_error_request_t;
/**
* @}
*/

/**
* @defgroup connector_file_data_response_t File system data response
* @{
*/
/**
* File system data response structure is used for @ref connector_file_system_read,
* @ref connector_file_system_readdir, and @ref connector_file_system_strerror callbacks.
*/
typedef struct
{
    void                    * user_context; /**< To hold the user context */
    connector_file_error_data_t * error;        /**< Holds error status of @ref connector_file_error_status_t type and errnum */
    void                    * data_ptr;     /**< Pointer to write response data */
    size_t                  size_in_bytes;  /**< On input size of data buffer, on output size of response data */
} connector_file_data_response_t;
/**
* @}
*/

/**
* @defgroup connector_file_response_t File system basic response
* @{
*/
/**
* File system basic response structure is used for @ref connector_file_system_close,
* @ref connector_file_system_rm, @ref connector_file_system_closedir,
* @ref connector_file_system_ftruncate, and  @ref connector_file_system_msg_error callbacks.
*/
typedef struct
{
    void                    * user_context; /**< To hold the user context */
    connector_file_error_data_t * error;        /**< Pointer to file error data */
} connector_file_response_t;
/**
* @}
*/

/**
* @defgroup connector_file_open_response_t File or directory open response
* @{
*/
/**
* File or directory open response structure is used for the @ref connector_file_system_open
* and @ref connector_file_system_opendir callback.
*/
typedef struct
{
    void                    * user_context; /**< To hold the user context */
    connector_file_error_data_t * error;        /**< Pointer to file error data */
    void                    * handle;       /**< Application defined file handle or directory */
} connector_file_open_response_t;
/**
* @}
*/

/**
* @defgroup connector_file_lseek_response_t File lseek response
* @{
*/
/**
* File lseek response structure is used for @ref connector_file_system_lseek callback.
*/
typedef struct
{
    void                    * user_context; /**< To hold the user context */
    connector_file_error_data_t * error;        /**< Pointer to file error data */
    long int                  offset;       /**< Resulting file position */
} connector_file_lseek_response_t;
/**
* @}
*/

/**
* @defgroup connector_file_write_response_t File write response
* @{
*/
/**
* File write response structure is used for @ref connector_file_system_write callback.
*/
typedef struct
{
    void                    * user_context;  /**< To hold the user context */
    connector_file_error_data_t * error;         /**< Pointer to file error data */
    size_t                    size_in_bytes; /**< On input size of data buffer, on output size of response data */
} connector_file_write_response_t;
/**
* @}
*/


/**
* @defgroup connector_file_stat_response_t File status response
* @{
*/
/**
* File status response structure is used for @ref connector_file_system_stat callback.
*/
typedef struct
{
    void                    * user_context; /**< To hold the user context */
    connector_file_error_data_t * error;        /**< Pointer to file error data */
    connector_file_stat_t         statbuf;      /**< Pointer to place file status data on output */
} connector_file_stat_response_t;
/**
* @}
*/

/**
* @defgroup connector_message_status_response_t Data type used in all the status responses
* @{
*/
/**
* This data structure is used when the callback is called with the iDigi Device Cloud response
* if the response is requested and it contains just the status.
*
* @see connector_status_ping_response
* @see connector_data_service_dp_response
* @see connector_sm_device_to_server_config
* @see connector_initiate_data_point
* @see connector_initiate_binary_point
*/
typedef struct
{
    void const * user_context;  /**< User context passed in the request */
    connector_session_status_t status;  /**< Response status */
    char const * error_text;    /**< An optional, null-terminated error string */
} connector_message_status_response_t;
/**
* @}
*/

/**
* @defgroup connector_message_status_request_t Data type used for status message/response
* @{
*/
/**
* This data structure is used when the connector_initiate_action() API is called with
* connector_initiate_status_message, connector_initiate_config_message where only the status
* is returned from the iDigi Device Cloud.
*
* @see connector_initiate_status_message
* @see connector_initiate_config_message
* @see connector_initiate_action
* @see connector_initiate_session_cancel
*/
typedef struct
{
    connector_transport_t transport;    /**< Transport method to use */
    unsigned int flags;             /**< Set to CONNECTOR_DATA_RESPONSE_NOT_NEEDED if response is not needed */
    void const * user_context;      /**< User provided application context */
} connector_message_status_request_t;
/**
* @}
*/

/**
* @defgroup connector_sm_cli_request_t Data type used for cli request and response
* @{
*/
/**
* This data structure is used when the callback is called to pass the request or to get the response.
*
* @see connector_sm_cli_request
*
*/
typedef struct
{
    connector_data_service_type_t type;    /**< Type to select the content to use. have_data: CLI request, need_data: CLI response,  total_length: Need total response bytes */
    void const * user_context;         /**< User context, will be NULL when request is called, so that user can update this. Will carry user assigned context in the response */

    union
    {
        struct
        {
            char const * buffer;       /**< Buffer pointer to write the CLI response to */
            size_t bytes;              /**< It carries the sizeof CLI command */
            unsigned int flags;        /**< Will be set to CONNECTOR_MSG_RESPONSE_NOT_NEEDED if response is not needed */
        } request;

        struct
        {
            char * buffer;             /**< Buffer pointer to write the CLI response to */
            size_t bytes;              /**< When called it contains the size of the available response buffer size, in return it will carry the filled buffer size */
            connector_session_status_t status; /**< Response status */
        } response;

        connector_session_status_t status; /**< When the type is connector_data_service_type_session_status, then this field will carry the reason for the session close */
        size_t * total_bytes_ptr;      /**< When the type is connector_data_service_type_total_length, then user need to update the content of this pointer
                                            with total response length. Applicable only for UDP and SMS transport methods */
    } content;

} connector_sm_cli_request_t;
/**
* @}
*/

/**
* @defgroup connector_data_point_type_t data types for Data Points
* @{
*/
/**
* This lists the types supported for Data Points for Devices.
*
* @see connector_data_point_request_t
*/
typedef enum
{
    connector_data_point_type_integer,   /**< data can be represented with a network (big endian) 32-bit two's complement integer */
    connector_data_point_type_long,      /**< data can be represented with a network (big endian) 64-bit two's complement integer */
    connector_data_point_type_float,     /**< data can be represented with a network (big endian) 32-bit IEEE754 floating point */
    connector_data_point_type_double,    /**< data can be represented with a network (big endian) 64-bit IEEE754 floating point */
    connector_data_point_type_string,    /**< UTF-8 encoding (ASCII compatible) */
    connector_data_point_type_binary     /**< binary data */
} connector_data_point_type_t;
/**
* @}
*/

/**
* @defgroup connector_timeval_t  Structure to represent time in seconds and milliseconds.
* @{
*/
/**
* The data structure to represent seconds and milliseconds since the epoch (00:00:00 UTC on 1 January 1970).
* Devices on which milliseconds are not available then use 0 for milliseconds.
*
* @see connector_data_point_t
*/
typedef struct connector_timeval_t
{
    time_t seconds;
    unsigned int milliseconds;
} connector_timeval_t;
/**
* @}
*/

/**
* @defgroup connector_data_point_t Data structure used to represent each Data Point.
* @{
*/
/**
* User can use this structure to make linked list of Data Points to send it out in one transaction.
* Note: All data points must belong to same stream.
*
* @see connector_data_point_request_t
* @see connector_data_point_type_t
*/
typedef struct connector_data_point_t
{
    struct
    {
        enum
        {
            connector_data_type_native, /**< the data value is in native format */
            connector_data_type_text    /**< the data value is in ascii/text format */
        } type;

        union
        {
            union
            {
                int int_value;       /**< 32-bit two's complement integer */
                long long_value;     /**< 64-bit two's complement integer */
                char * string_value; /**< a null-terminated utf-8 encoding string */
                #if (defined FLOATING_POINT_SUPPORTED)
                float float_value;   /**< 32-bit IEEE754 floating point */
                double double_value; /**< 64-bit IEEE754 floating point */
                #endif
            } native;

            char * text;            /**< carries data in ascii format, a null-terminated string */
        } element;

    } data;

    struct
    {
        enum
        {
            connector_time_server,          /**< The timev.alue is ignored and the server time is used instead. */
            connector_time_local_epoch,     /**< A transport-specific time.value is specified in epoch long format. */
            connector_time_local_iso8601    /**< A transport-specific time.value is specified in ISO 8601 string format. */
        } source;

        union
        {
            connector_timeval_t msec_since_epoch; /**< Time since the Epoch time in milliseconds */
            char * iso8601_string;      /**< A null-terminated local time in ISO 8601 format */
        } value;

    } time;   /**< Time at the data point is captured */

    struct
    {
        enum
        {
            connector_location_type_ignore, /**< location is ignored */
            #if (defined FLOATING_POINT_SUPPORTED)
            connector_location_type_native,  /**< location value is represented in float */
            #endif
            connector_location_type_text   /**< location value is represented in ascii */
        } type;

        union
        {
            #if (defined FLOATING_POINT_SUPPORTED)
            struct
            {
                float latitude;     /**< latitude in degree */
                float longitude;    /**< longitude in degree */
                float elevation;    /**< elevation in meters */
            } native;
            #endif

            struct
            {
                char * latitude;   /**< latitude in degree (null-terminated string) */
                char * longitude;  /**< longitude in degree (null-terminated string) */
                char * elevation;  /**< elevation in meters (null-terminated string) */
            } text;

        } value;

    } location;

    struct
    {
        enum
        {
            connector_quality_type_ignore, /**< Quality is ignored */
            connector_quality_type_native  /**< user specified data quality, an integer value */
        } type;

        int value;
    } quality;

    char * description; /**< null terminated description string (optional field, set to NULL if not used) */

    struct connector_data_point_t * next; /**< Points to next data point, set to NULL if this is the last one. */
} connector_data_point_t;
/**
* @}
*/

/**
* @defgroup connector_data_point_header_t Data structure used to represent each binary Data Point.
* @{
*/
/**
* User can use this structure to send binary data. Small foot print devices can use this data
* structure to send simple data points.
*
* @see connector_data_point_request_t
* @see connector_data_point_type_t
*/
typedef struct connector_data_point_header_t
{
    connector_transport_t transport;     /**< transport method (TCP, UDP or SMS) to use */
    char * path;                     /**< data point path in the stream */
    unsigned int flags;              /**< set to CONNECTOR_DATA_RESPONSE_NOT_NEEDED if response is not needed, ignored if the transport is TCP */
    void const * user_context;       /**< user context to be passed back in response */
} connector_data_point_header_t;
/**
* @}
*/

/**
* @defgroup connector_binary_point_request_t Data type used to send binary data point of a stream to the Cloud.
* @{
*/
/**
* This data structure is used when the connector_initiate_action() API is called with connector_initiate_binary_point
* request id. This can be used on a device where foot print and or the bandwidth is limited.
*
* @see connector_message_status_response_t
* @see connector_initiate_action
* @see connector_initiate_binary_point
* @see connector_data_point_header_t
*/
typedef struct
{
    connector_data_point_header_t header; /**< data point header info */
    void * point;   /**< binary data of size specified in bytes */
    size_t bytes;   /**< size of data in bytes */
} connector_binary_point_request_t;
/**
* @}
*/

/**
* @defgroup connector_data_point_request_t Data type used to send Data Points of a stream to the Cloud.
* @{
*/
/**
* This data structure is used when the connector_initiate_action() API is called with
* connector_initiate_data_point request id.
*
* @see connector_message_status_response_t
* @see connector_data_point_t
* @see connector_initiate_action
* @see connector_initiate_data_point
* @see connector_data_point_type_t
* @see connector_data_point_header_t
*/
typedef struct
{
    connector_data_point_header_t header; /**< data point header info */
    connector_data_point_type_t type;     /**< data point content type (Ex. integer, float, string, binary...) */
    char * unit;                      /**< null-terminated unit (optional field, set to NULL if not used), eg: "inch\0" */
    char * forward_to;                /**< comma separated list of streams to replicate data points to (a null-terminated optional field, set to NULL if not used) */
    connector_data_point_t * point;       /**< data point or list of data points */
} connector_data_point_request_t;
/**
* @}
*/

/**
* @defgroup connector_server_to_device_config_t Data type used for the Cloud to device config request
* @{
*/
/**
* This data structure is used when the callback is called with connector_data_service_server_to_device_config request id.
*
* @see connector_sm_server_to_device_config
*
*/
typedef struct
{
    char * phone_number;    /**< A null-terminated phone number */
    char * service_id;      /**< A null-terminated service identifier. It can be empty */
} connector_server_to_device_config_t;
/**
* @}
*/

/**
* @defgroup connector_device_to_server_config_t Data type used to send transport specific configuration message
* @{
*/
/**
* This data structure is used when the connector_initiate_action() API is called with
* connector_initiate_config_message request id.
*
* @see connector_initiate_action
* @see connector_initiate_config_message
* @see connector_sm_device_to_server_config
* @see connector_message_status_response_t
*/
typedef struct
{
    connector_transport_t transport; /**< Transport layer to use */
    unsigned int flags;          /**< Set to CONNECTOR_DATA_RESPONSE_NOT_NEEDED if response is not needed */
    void const * user_context;   /**< User context to be passed back in the response */
    unsigned int sim_slot;       /**< The SIM slot number, use 0 for unknown */
    char * identifier;           /**< A null-terminated, SIM or phone number identifier */
} connector_device_to_server_config_t;
/**
* @}
*/

/**
* @defgroup connector_sm_opaque_response_t Data type used to deliver the opaque response from the Cloud
* @{
*/
/**
* This data structure is used when the callback is called to pass the Cloud response for which the
* associated request is not present. It may be cancelled by the user or iDigi Connector maybe restarted
* after sending the request.
*
* @see connector_sm_opaque_response
*
*/
typedef struct
{
    uint32_t id;                    /**< Can be used to keep track of a multipart response */
    void * data;                    /**< Pointer to opaque response */
    size_t bytes;                   /**< Number of bytes available in the data */
    unsigned int flags;             /**< Can be used to track last data block */
    connector_session_status_t status;  /**< Response status, Application can use this to discard the subsequent
                                        parts by returning connector_session_status_cancel */
} connector_sm_opaque_response_t;
/**
* @}
*/

/**
* @defgroup connector_stop_condition_t Condition used on @ref connector_initiate_transport_stop in @ref connector_initiate_action
* @{
*/
/**
* This is used to tell how iDigi connector handles all active sessions before stopping.
*
*/
typedef enum {
    connector_stop_immediately,             /**< Cancel all active sessions and stop the transport of iDigi connector immediately */
    connector_wait_sessions_complete         /**< Stop the transport of iDigi connector after all active sessions complete */
} connector_stop_condition_t;
/**
* @}
*/

/**
* @defgroup connector_initiate_stop_request_t Data type used to stop a transport of iDigi connector
* @{
*/
/**
* This data structure is used on @ref connector_initiate_transport_stop in @ref connector_initiate_action API
* to stop a transport.
*
*/
typedef struct
{
    connector_transport_t transport;        /**< Transport will be stopped:
                                            - @ref connector_transport_tcp
                                            - @ref connector_transport_udp
                                            - @ref connector_transport_sms
                                            - @ref connector_transport_all */

    connector_stop_condition_t condition;   /**< Condition to stop the transport:
                                             - @ref connector_stop_immediately
                                             - @ref connector_wait_sessions_complete */

    void * user_context;                /**< User's defined context that will be passed to @ref connector_status_stop_completed after the transport of  iDigi connector has stopped running. */

} connector_initiate_stop_request_t;
/**
* @}
*/


 /**
 * @defgroup connector_callback_t Application-defined callback
 * @{
 * @b Include: connector_api.h
 *
 * @brief   The is the iDigi Connector Application defined callback structure.
 *
 * An application must define this function and pass this to the iDigi Connector during the
 * connector_init() call.  This callback is used to pass configuration data and exchange system
 * services with the iDigi COnnector state machine.  The callback return value is then used to
 * guide the iDigi Connector how to proceed after completion of the application callback.
 *
 */
 /**
 * @param class_id 				This is a grouping or category of callback functions.  Each class_id contains a number of related request_id's.
 * @param request_id 			The request ID defines the specific callback being requested.
 * @param data 			        Points to specific structure for the request ID
 *
 * @retval	connector_callback_continue		The callback completed successfully and the iDigi Connector should continue
 * 										it's process.
 * @retval  connector_callback_busy			The callback could not complete the operation within the allowable time frame.
 * 										Do not advance the state of the iDigi Connector and recall this callback at some
 * 										later time.
 * @retval 	connector_callback_abort		The application is requesting the iDigi Connector to abort execution.  This will
 * 										cause connector_run() or connector_step() to terminate with status @ref connector_abort.
 * @retval	connector_callback_unrecognized	An unsupported and unrecognized callback was received.  The application does not
 * 										support this request.  This should be implemented in the application to allow for
 * 										graceful recovery and upgrade-ability to future iDigi Connector releases.
 *
 * @see connector_callback_status_t
 * @see connector_init()
 */
typedef connector_callback_status_t (* connector_callback_t) (connector_class_t const class_id, connector_request_t const request_id,
                                                             void * const data);
/**
* @}
*/

 /**
 * @defgroup connector_init Initialize the iDigi connector.
 *@{
 * @b Include: connector_api.h
 */
/**
 * @brief This API is called initially at startup to allocate and initialize the iDigi connector.
 *
 * This function takes the @ref iik_callback "application-defined callback" function pointer as
 * it's only argument.  This callback is used by the iDigi connector to communicate with the
 * application environment.  This function must be called prior to other iDigi connector APIs,
 * like connector_step(), connector_run(), and connector_initiate_action().
 *
 * @param [in] callback  Callback function that is used to
 *        interface between the application and the iDigi connector.
 *
 * @retval NULL   		An error occurred and the iDigi connector was unable to initialize.
 * @retval "Not NULL"	Success.  A Handle was returned for subsequent iDigi Connector calls.
 *
 * Example Usage:
 * @code
 *    connector_handle = connector_init(application_callback);
 * @endcode
 *
 * @see connector_handle_t
 * @see connector_callback_t
 */
connector_handle_t connector_init(connector_callback_t const callback);
/**
* @}
*/

/**
 * @defgroup connector_step Step Routine
 * @{
 * @b Include: connector_api.h
 */
/**
 * @brief   Executes a small portion of the iDigi Connector in a non-blocking call.
 *
 * This non-blocking function is used to execute a portion the iDigi Connector after it's been
 * successfully initialized with an connector_init() call.  This function performs a sequence of
 * operations or events and then returns.  This allows applications to perform other tasks,
 * especially in non-threading environment.  For more information on the differences between
 * connector_run() and connector_step() see the @ref threading "iDigi Connector threading model".
 *
 * This function is similar to connector_run() except this is the non-blocking variant.  This function would
 * normally be made from system control loop or state machine.  This function must be repeatedly made to
 * maintain the iDigi Connector state.
 *
 * See the iDigi Connector @ref threading "threading model" section for more information on the differences
 * between connector_run() and connector_step().
 *
 * @param [in] handle  Handle returned from connector_init
 *
 * @retval connector_init_error             The iDigi connector was not properly initialized.  The application requires a
 * 										call to connector_init() prior to calling this function.
 * @retval connector_abort                  iDigi connector was aborted by callback function.
 * @retval connector_invalid_data_size      An @ref iik_callback "application callback" returned an invalid response_length.
 *   									This is an application callback defect and should be corrected.  To locate the
 *  									faulty callback, enable @ref CONNECTOR_DEBUG.  For more information on
 * 										debugging, see the section on @ref debug_routine "how to implement debug support".
 * @retval connector_invalid_data_range     An @ref iik_callback "application callback" returned invalid response_data.
 *  									This is an application callback defect and should be corrected.  To locate the
 *  									faulty callback, enable @ref CONNECTOR_DEBUG.  For more information on
 * 										debugging, see the section on @ref debug_routine "how to implement debug support".
 * @retval connector_invalid_payload_packet iDigi connector received invalid payload message.
 * @retval connector_keepalive_error        iDigi connector did not receive keep alive messages. Server may be offline.
 * @retval connector_server_overload        Server overload.
 * @retval connector_bad_version            Server rejected version number.
 * @retval connector_exceed_timeout         Callback exceeded timeout value before it returned.
 * @retval connector_unsupported_security   iDigi connector received a packet with unsupported security.
 * @retval connector_invalid_data           An @ref iik_callback "application callback" returned unexpected NULL response_data.
 *  									This is an application callback defect and should be corrected.  To locate the
 *  									faulty callback, enable @ref CONNECTOR_DEBUG.  For more information on
 * 										debugging, see the section on @ref debug_routine "how to implement debug support".
 * @retval connector_device_terminated      iDigi connector was terminated by user via connector_initiate_action() call.
 * @retval connector_server_redirect        iDigi connector was stopped when redirecting to a new server.
 * @retval connector_idle                   iDigi connector is idling. iDigi connector has no message to process and relinquishes other task execution.
 * @retval connector_working                iDigi connector is processing a message and should be called at the earliest possible time.
 * @retval connector_pending                iDigi connector is busy or waiting to process a message and relinquishes other task execution
 * @retval connector_active                 iDigi connector is busy or waiting to process a message and should be called
 *                                      at the earliest possible time
 *
 *
 * Example Usage:
 * @code
 *     connector_status_t status;
 *     connector_handle_t connector_handle = connector_init(application_callback);
 *
 *     for (;;)
 *     {
 *     	    status = connector_step(connector_handle);
 *     	    other_system_tasks();
 *     }
 * @endcode
 *
 * @see connector_init()
 * @see connector_handle_t
 * @see connector_status_t
 * @see connector_run()
 */
connector_status_t connector_step(connector_handle_t const handle);
/**
* @}
*/


 /**
 * @defgroup connector_run Run routine
 * @{
 * @b Include: connector_api.h
 */
/**
 * @brief   Runs the iDigi Connector as a blocking call.
 *
 * This blocking function is typically used in a separate thread (in a multi-threaded environment) to run
 * the iDigi Connector after it's been successfully initialized with an connector_init() call.  This function
 * only returns when the iDigi Connector encounters an unexpected error.  This function is similar to
 * connector_step() except this is the blocking variant.
 *
 * See the iDigi Connector @ref threading "Threading Model section" for more information on the differences
 * between connector_run() and connector_step().
 *
 * @param [in] handle  					Handle returned from connector_init() call.
 *
 * @retval connector_init_error             The iDigi connector was not properly initialized.  The application requires a
 * 										call to connector_init() prior to calling this function.
 * @retval connector_abort                  iDigi connector was aborted by callback function.
 * @retval connector_invalid_data_size      An @ref iik_callback "application callback" returned an invalid response_length.
 *   									This is an application callback defect and should be corrected.  To locate the
 *  									faulty callback, enable @ref CONNECTOR_DEBUG.  For more information on
 * 										debugging, see the section on @ref debug_routine "how to implement debug support".
 * @retval connector_invalid_data_range     An @ref iik_callback "application callback" returned invalid response_data.
 *  									This is an application callback defect and should be corrected.  To locate the
 *  									faulty callback, enable @ref CONNECTOR_DEBUG.  For more information on
 * 										debugging, see the section on @ref debug_routine "how to implement debug support".
 * @retval connector_keepalive_error        iDigi connector did not receive keep alive messages. Server may be offline.
 * @retval connector_server_overload        Server overload.
 * @retval connector_bad_version            Server rejected version number.
 * @retval connector_exceed_timeout         Callback exceeded timeout value before it returned.
 * @retval connector_unsupported_security   iDigi connector received a packet with unsupported security.
 * @retval connector_invalid_data           An @ref iik_callback "application callback" returned unexpected NULL response_data.
 *  									This is an application callback defect and should be corrected.  To locate the
 *  									faulty callback, enable @ref CONNECTOR_DEBUG.  For more information on
 * 										debugging, see the section on @ref debug_routine "how to implement debug support".
 * @retval connector_server_disconnected    Server disconnected iDigi connector.
 * @retval connector_device_error           Close Callback returns
 *                                      error. If connector_step or connector_run is called again, it
 *                                      will re-establish the connection.
 * @retval connector_device_terminated      iDigi connector was terminated by user via connector_initiate_action call.
 * @retval connector_server_redirect        iDigi connector was stopped when redirecting to a new server.
*
 * Example Usage:
 * @code
 *     connector_status_t status;
 *     connector_handle_t connector_handle = connector_init(application_callback);
 *
 *     status = connector_run(connector_handle);
 * @endcode
 *
 * @see connector_init()
 * @see connector_handle_t
 * @see connector_status_t
 * @see connector_step()
 */
connector_status_t connector_run(connector_handle_t const handle);
/**
* @}
*/


 /**
 * @defgroup connector_initiate_action Initiate Action
 * @{
 * @b Include: connector_api.h
 */
/**
 * @brief   Requests the iDigi Connector to perform an asynchronous action.
 *
 * This function is called to initiate an iDigi Connector action.  It can be
 * used to initiate a send data sequence from the device to the iDigi Device Cloud,
 * or to terminate the iDigi Connector library.
 *
 * @param [in] handle  Handle returned from the connector_init() call.
 *
 * @param [in] request  Request action (one of the following):
 *                      @li @b connector_initiate_terminate:
 *                          Terminates and stops the iDigi Connector from running.  This call closes all open network
 *                          Handles and frees all allocated memory.
 *                          If the application is using connector_step(), the next call to connector_step() terminates
 *                          the iDigi connector.  If a blocking call to connector_run() is still pending, this call
 *                          will eventually terminate that call.  Once the iDigi Connector is terminated, the
 *                          iDigi Connector must restart by calling connector_init().
 *
 *                      @li @b connector_initiate_data_service:
 *                           This is used to trigger the send
 *                           data to the iDigi Device Cloud. Only the
 *                           header information is passed by
 *                           this method. The actual data is
 *                           transferred through callbacks. The
 *                           data is stored in a specified file
 *                           on the server.
 *
 *                      @li @b connector_initiate_transport_start:
 *                          Starts the specified (@ref connector_transport_tcp, @ref connector_transport_udp or
 *                          @ref connector_transport_sms) transport method.
 *
 *                      @li @b connector_initiate_transport_stop:
 *                          Stops the specified transport:
 *                              - @ref connector_transport_tcp - TCP transport,
 *                              - @ref connector_transport_udp - UDP transport
 *                              - @ref connector_transport_sms - SMS transport
 *                              - @ref connector_transport_all - all transports.
 *                              - @ref @b Note: This triggers @ref connector_status_stop_completed callback. @b See @ref status_stop_completed callback.
 *
 *                      @li @b connector_initiate_status_message:
 *                          Sends status message to the iDigi Device Cloud.  Supported only under
 *                          @ref connector_transport_udp and @ref connector_transport_sms transport methods.
 *
 *                      @li @b connector_initiate_data_point:
 *                          Initiates the action to send data point to the iDigi Device Cloud.
 *
 *                      @li @b connector_initiate_config_message:
 *                          Sends configuration info to the iDigi Device Cloud. Supported only under SMS transport method.
 *
 *                      @li @b connector_initiate_session_cancel:
 *                          Initiates the action to cancel the timedout session.
 *
 * @param [in] request_data  Pointer to Request data
 *                      @li @b connector_initiate_terminate:
 *                          Should be NULL.
 *                      @li @b connector_initiate_data_service:
 *                          Pointer to connector_data_service_put_request_t.
 *                      @li @b connector_initiate_transport_start:
 *                          Pointer to @ref connector_transport_t "connector_transport_t"
 *                      @li @b connector_initiate_transport_stop:
 *                          Pointer to @ref connector_initiate_stop_request_t "connector_initiate_stop_request_t"
 *                      @li @b connector_initiate_status_message:
 *                          Pointer to connector_message_status_request_t
 *                      @li @b connector_initiate_data_point:
 *                          Pointer to connector_data_point_request_t
 *                      @li @b connector_initiate_config_message:
 *                          Pointer to connector_device_to_server_config_t
 *                      @li @b connector_initiate_session_cancel:
 *                          Pointer to connector_message_status_request_t
 *
 * @param [out] response_data  Pointer to Response data
 *                      @li @b connector_initiate_terminate:
 *                          Should be NULL.
 *                      @li @b connector_initiate_data_service:
 *                          Should be NULL.
 *                      @li @b connector_initiate_transport_start:
 *                          Should be NULL.
 *                      @li @b connector_initiate_transport_stop:
 *                          Should be NULL.
 *                      @li @b connector_initiate_status_message:
 *                          Not used, can be NULL.
 *                      @li @b connector_initiate_data_point:
 *                          Not used, can be NULL.
 *                      @li @b connector_initiate_config_message:
 *                          Not used, can be NULL.
 *                      @li @b connector_initiate_session_cancel:
 *                          Not used, can be NULL.
 *
 * @retval connector_success              No error
 * @retval connector_init_error           iDigi connector was not initialized or not connected to the iDigi Device Cloud.
 * @retval connector_abort                Callback aborted iDigi connector.
 * @retval connector_invalid_data         Invalid parameter
 * @retval connector_no_resource          Insufficient memory
 * @retval connector_service_busy         iDigi connector is busy
 *
 * Example Usage:
 * @code
 *     connector_data_service_put_request_t  file_info;
 *     :
 *     status = connector_initiate_action(handle, connector_initiate_data_service, &file_info, NULL);
 *     :
 *     :
 *     status = connector_initiate_action(connector_handle, connector_initiate_terminate, NULL, NULL);
 * @endcode
 *
 * @see connector_handle_t
 * @see connector_callback_t
 */
connector_status_t connector_initiate_action(connector_handle_t const handle, connector_initiate_request_t const request,
                                     void const * const request_data, void * const response_data);
/**
* @}.
*/
#endif /* _CONNECTOR_API_H */

