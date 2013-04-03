/*
 * Copyright (c) 2011, 2013 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */
#ifndef CONNECTOR_API_CONFIG_H
#define CONNECTOR_API_CONFIG_H

/**
* @defgroup connector_request_id_config_t Configuration Request IDs
* @{
*/
/**
* Configuration Request Id passed to the application's callback for requesting configuration data.
* The class id for this connector_request_id_config_t is connector_class_id_config.
*/
typedef enum {
    connector_request_id_config_device_id,         /**< Requesting callback to return a unique device id which is used to identify the device.*/
    connector_request_id_config_vendor_id,         /**< Requesting callback to return a unique vendor id identifying the manufacturer of a device. */
    connector_request_id_config_device_type,       /**< Requesting callback to return device type that identifies the type of the device  */
    connector_request_id_config_device_cloud_url,  /**< Requesting callback to return Etherios Device Cloud URL which will be connected to */
    connector_request_id_config_connection_type,   /**< Requesting callback to return LAN or WAN connection type */
    connector_request_id_config_mac_addr,          /**< Requesting callback to return device's MAC addresss */
    connector_request_id_config_link_speed,        /**< Requesting callback to return link speed for WAN connection type */
    connector_request_id_config_phone_number,      /**< Requesting callback to return phone number dialed for WAN connection type */
    connector_request_id_config_tx_keepalive,      /**< Requesting callback to return server's Tx keep alive interval in seconds */
    connector_request_id_config_rx_keepalive,      /**< Requesting callback to return server's Rx keep alive interval in seconds */
    connector_request_id_config_wait_count,        /**< Requesting callback to return the number of intervals of not receiving a keep alive message after which a connection should be considered lost. */
    connector_request_id_config_ip_addr,           /**< Requesting callback to return device's IP address */
    connector_request_id_config_error_status,      /**< Error status notification which tells callback that error is encountered. */
    connector_request_id_config_firmware_facility, /**< Requesting callback to return whether firmware facility is supported or not. */
    connector_request_id_config_data_service,      /**< Requesting callback to return whether data service is supported or not. */
    connector_request_id_config_file_system,       /**< Requesting callback to return whether file system is supported or not. */
    connector_request_id_config_remote_configuration, /**< Requesting callback to return whether remote configuration is supported or not. */
    connector_request_id_config_max_transaction,   /**< Requesting callback to obtain maximum messaging sessions supported by client. */
    connector_request_id_config_device_id_method,  /**< Requesting callback to obtain method on how device id is generated */
    connector_request_id_config_imei_number,       /**< Requesting callback to return GSM IMEI number */
    connector_request_id_config_network_tcp,       /**< Requesting callback to return whether connection over TCP need to start now. */
    connector_request_id_config_network_udp,       /**< Requesting callback to return whether connection over UDP need to start now. */
    connector_request_id_config_network_sms,       /**< Requesting callback to return whether connection over SMS need to start now. */
    connector_request_id_config_wan_type,          /**< Requesting callback to return WAN type used. It tells iDigi connector whether it's GSM IMEI, CDMA ESN or CDMA MEID. */
    connector_request_id_config_esn,               /**< Requesting callback to return CDMA ESN (Electronic Serial Number) */
    connector_request_id_config_meid,              /**< Requesting callback to return CDMA MEID (Mobile Equipment Identifier) */
    connector_request_id_config_identity_verification,     /**< Requesting callback to return identity verification form. */
    connector_request_id_config_password           /**< Requesting callback to return password for the password identity verification form */
} connector_request_id_config_t;
/**
* @}
*/

/**
* @defgroup connector_config_pointer_data_t Data Pointer Configuration
* @{
*/
/**
* Application Binary Data Pointer Configuration for the following callbacks:
*   -# @ref connector_request_id_config_device_id
*   -# @ref connector_request_id_config_mac_addr
*   -# @ref connector_request_id_config_imei_number
*   -# @ref connector_request_id_config_esn
*   -# @ref connector_request_id_config_meid
*/
typedef struct {
    uint8_t * data;         /**< Application data pointer */
    size_t CONST bytes_required;  /**< Number of bytes required and needed on the application data pointer */
} connector_config_pointer_data_t;
/**
* @}
*/


/**
* @defgroup connector_config_vendor_t  Vendor ID Configuration
* @{
*/
/**
* Vendor ID configuration for @ref connector_request_id_config_vendor_id callback
*/
typedef struct {
    uint32_t id;    /**< Vendor ID */
} connector_config_vendor_id_t;
/**
* @}
*/


/**
* @defgroup connector_config_name_data_t String Pointer Configuration
* @{
*/
/**
* Application String Pointer Configuration for the following callbacks:
*
*   -# connector_request_id_config_device_type
*   -# connector_request_id_config_device_cloud_url
*   -# connector_request_id_config_phone_number
*   -# connector_request_id_config_password
*/
typedef struct {
    char * string;  /**< Application string pointer */
    size_t length;  /**< Number of bytes in the application string pointer */
} connector_config_pointer_string_t;
/**
* @}
*/

/**
* @defgroup connector_connection_type_t Connection Types
* @{
*/
/**
* Connection type configuration of the device
*
* @see connector_config_connection_type_t callback
*/
typedef enum {
   connector_connection_type_lan,   /**< LAN connection type for Ethernet or WiFi */
   connector_connection_type_wan    /**< WAN connection type for PPP over Modem */
} connector_connection_type_t;
/**
* @}
*/

/**
* @defgroup connector_config_connection_type_t Connection Type Configuration
* @{
*/
/**
* Device connection type configuration for @ref connector_request_id_config_connection_type callback
*/
typedef struct {
    connector_connection_type_t type; /**< Device connection type */
} connector_config_connection_type_t;
/**
* @}
*/


/**
* @defgroup connector_config_link_speed_t  Link Speed Configuration
* @{
*/
/**
* Device link speed configuration for WAN connection type for @ref connector_request_id_config_link_speed callback
*
* @see connector_request_id_config_connection_type
*/
typedef struct {
    uint32_t speed;        /**< Device link speed  */
} connector_config_link_speed_t;
/**
* @}
*/


/**
* @defgroup connector_config_keepalive_t Keep-Alive Interval Configuration
* @{
*/
/**
* Keep-alive interval configuration used for the following callbacks:
*   -# @ref connector_request_id_config_tx_keepalive
*   -# @ref connector_request_id_config_rx_keepalive
*/
typedef struct {
    uint16_t interval_in_seconds;       /**< Device keep-alive interval */
} connector_config_keepalive_t;
/**
* @}
*/


/**
* @defgroup connector_config_wait_count_t Wait Count Configuration
* @{
*/
/**
* Device wait count configuration for @ref connector_request_id_config_wait_count callback
*
* @see connector_request_id_config_tx_keepalive
*/
typedef struct {
    uint16_t count;       /**< wait count */
} connector_config_wait_count_t;
/**
* @}
*/


/**
* @defgroup connector_config_ip_addr_t Device IP Address Configuration
* @{
*/
/**
* Device IP Address Configuration for @ref connector_request_id_config_ip_addr callback
*/
typedef struct {
    uint8_t * address;        /**< Device's IP address */
    enum {
        connector_ip_address_ipv4,  /**< IPv4 address TODO: bytes count example  ??*/
        connector_ip_address_ipv6   /**< IPv6 address */
    } ip_address_type;
} connector_config_ip_address_t;
/**
* @}
*/


/**
* @defgroup connector_config_support_status_t Service Supported Configuration
* @{
*/
/**
* Service supported status configuarion for the following callbacks:
*   -# @ref connector_request_id_config_firmware_facility
*   -# @ref connector_request_id_config_data_service
*   -# @ref connector_request_id_config_file_system
*/
typedef struct {
    connector_bool_t supported; /**< Application service supported status */
} connector_config_supported_t;
/**
* @}
*/


/**
* @defgroup connector_device_id_method_t Device ID Method Types
* @{
*
*/
/**
 * Device ID method type which is used in the applciation's callback telling
 * the connector how to obtain a device ID.
 *
 * @see @ref device_id
 */
typedef enum {
    connector_device_id_method_auto,         /**< Callback returns this type telling iDigi connector to
                                                 generate the device ID from MAC address (See @ref connector_config_mac_addr callback)
                                                 for LAN connection type or genearte the device ID according to the @ref wan_type.
                                                 @note iDigi connector will not call @ref connector_config_device_id callback. */
    connector_device_id_method_manual       /**< Callback returns this type telling iDigi connector to retrieve device ID from @ref connector_config_device_id callback */
} connector_device_id_method_t;
/**
* @}
*/


/**
* @defgroup connector_config_device_id_method_t Device ID Method Configuration
* @{
*/
/**
 * Device ID method configuration returned by the application's callback for @ref connector_request_id_config_device_id_method callback.
 */
typedef struct {
    connector_device_id_method_t method;    /**< Device ID method */
} connector_config_device_id_method_t;
/**
* @}
*/


/**
* @defgroup connector_connect_auto_type_t Network Connection Action Types
* @{
*/
/**
* Network connection action used to tell the connector to automat?? or manually make connection.
*
* @see @ref connector_network_close
*/
typedef enum {

    connector_connect_auto,     /**< Automic connect to Etherios Device Cloud */
    connector_connect_manual   /**< Manual connect to Etherios Device Cloud */
} connector_connect_auto_type_t;
/**
* @}
*/


/**
* @defgroup connector_config_connect_status_t Network Connection Action Type Configuration
* @{
*/
/**
* Connection action which is used to to tell the connector to make connection to
* Etherios Device Cloud automatically or manually. It's used for the following callbacks:
*   -# @ref connector_request_id_config_network_tcp
*   -# @ref connector_request_id_config_network_upd
*   -# @ref connector_request_id_config_network_sms
*/
typedef struct {
    connector_connect_auto_type_t type;   /**< Connection action */
} connector_config_connect_type_t;
/**
* @}
*/


/**
* @defgroup connector_wan_type_t Device WAN Types
* @{
*/
/**
 * Device WAN connection type which tells the connector the device WAN type for the device WAN ID.
 *
 * @ref connector_config_wan_type_t
 */
typedef enum {
    connector_wan_type_imei,    /**< IMEI number for GSM network */
    connector_wan_type_esn,     /**< ESN for CDMA network */
    connector_wan_type_meid     /**< MEID for CDMA network */
} connector_wan_type_t;
/**
* @}
*/


/**
* @defgroup connector_config_wan_type_t Device WAN Type Configuration
* @{
*/
/**
* Device WAN type configuration for @ref connector_request_id_config_wan_type callback.
* This is used to tell the connector the device WAN type. The connector uses this WAN type to
* get a corresponding WAN ID.
*
* @ref wan_type
* @ref imei_number
* @ref esn_number
* @ref meid_number
**/
typedef struct {
    connector_wan_type_t type;   /**< WAN type */
} connector_config_wan_type_t;
/**
* @}
*/


/**
* @defgroup connector_identity_verification_t  Identity Verification Form Types
* @{
*/
/**
 * Identify verification tells the connector to use simple or password identity verification for TCP connection.
 *
 * @see @ref connector_config_identity_verification_t
 */
typedef enum {
    connector_identity_verification_simple,         /**< Callback returns this form for simple identity verification. iDigi connector just transmits the
                                                     device ID and Etherios Device Cloud URL. */
    connector_identity_verification_password        /**< Callback returns this form for password identity verification. iDigi connector exchanges a pre-shared
                                                     secret password with Etherios Device Cloud. The password must match the password set in Etherios Device Cloud.
                                                     @note iDigi connector will call @ref connector_request_id_config_password callback for the password. */
} connector_identity_verification_t;
/**
* @}
*/


/**
* @defgroup connector_config_identity_verification_t Device Identity Verification Configuration
* @{
*/
/**
* Identify verification configuration for @ref connector_request_id_config_identity_verification callback.
* It tells the connector to use simple or password identity verification for TCP connection.
*
* @see identity_verification
* @see password
* @see connector_request_id_config_password
**/
typedef struct {
    connector_identity_verification_t type;   /**< Identity verification type */

} connector_config_identity_verification_t;
/**
* @}
*/


/**
* @defgroup connector_config_max_transaction_t Device Maximum Transaction Configuration
* @{
*/
/**
* Device maximum transaction configuration for @ref connector_request_id_config_max_transaction callback.
*
* @see @ref max_msg_transactions
**/
typedef struct {
    uint8_t count;   /**< Maximum transaction count */
} connector_config_max_transaction_t;
/**
* @}
*/


#endif /* CONNECTOR_API_CONFIG_H */

