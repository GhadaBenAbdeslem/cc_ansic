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
 *  @brief Remote configuration generated by Cloud Connector remote configuration tool.
 *
 */
#ifndef remote_config_h
#define remote_config_h

/**
* @defgroup connector_request_id_remote_config_t Remote Configuration Request IDs
* @{
*/
/**
* Remote Configuration Request ID passed to the application's callback to query or set remote configuration data.
* The class id for this connector_request_id_remote_config_t is connector_class_id_remote_config.
*/

typedef enum {
    connector_request_id_remote_config_session_start,  /**< inform callback to start remote configuration request */
    connector_request_id_remote_config_action_start,   /**< requesting callback to start query or set remote configuration data */
    connector_request_id_remote_config_group_start,    /**< requesting callback to start query or set an individual configuration group */
    connector_request_id_remote_config_group_process,  /**< requesting callback to query or set an element or field of a configuration group */
    connector_request_id_remote_config_group_end,      /**< requesting callback to end query or set an individual configuration group */
    connector_request_id_remote_config_action_end,     /**< requesting callback to end query or set remote configuration data */
    connector_request_id_remote_config_session_end,    /**< inform callback to end remote configuration request
                                                            Callback may start writing data into NVRAM for set remote configuration request.
                                                            Callback should end and release any resources used when it's done. */
    connector_request_id_remote_config_session_cancel,  /**< Requesting callback to abort and cancel any query or set remote configuration request.
                                                            Callback should stop and release any resources used */
    connector_request_id_remote_config_configurations
} connector_request_id_remote_config_t;
/**
* @}
*/

/**
 * @defgroup connector_on_off_t  Cloud Connector on or off values
 * @{
 */
/**
 * Cloud Connector ON and OFF value types
 */
typedef enum {
    connector_off,  /**< OFF */
    connector_on    /**< ON */
} connector_on_off_t;
/**
* @}
*/

/**
 * @defgroup connector_element_value_type_t Cloud Connector remote configuration element types
 * @{
 */
/**
 * Remote configuration element value types
 */
typedef enum {
    connector_element_type_string = 1,          /**< Single line string */
    connector_element_type_multiline_string,    /**< This type is used for a string that may be more
                                               than one line. A "text area" is shown in Device
                                               Cloud that allows a user to form multiple lines by pressing enter. */
    connector_element_type_password,            /**< This Password type is same as string type except it's shown "*"
                                                when a user types in characters in  Device Cloud. */
    connector_element_type_int32,               /**< 32-bit signed integer value */
    connector_element_type_uint32,              /**< 32-bit unsigned integer value */
    connector_element_type_hex32,               /**< 32-bit unsigned hexadecimal */
    connector_element_type_0x_hex32,               /**< 32-bit unsigned hexadecimal with 0x prefix shown in the Device Cloud.*/
    connector_element_type_float,               /**< Floating value. float.h is included. */
    connector_element_type_enum,                /**< enum is used to define a set of allowed values for an element.
                                                This is a pull-down menu shown in the Device Cloud. */
    connector_element_type_on_off = 11,            /**< "on" or "off" value. An application's callback should use
                                                 connector_on value for "on"  or connector_off value for "off". See @ref connector_on_off_t*/
    connector_element_type_boolean,             /**< true or false value. An application's callback should use connector_true
                                                value for true  or connector_false value for false. See @ref connector_bool_t */

    connector_element_type_ipv4,                /**< Valid IPv4 address (32-bit value) which is shown aaa.bbb.ccc.ddd in the Device Cloud */
    connector_element_type_fqdnv4,              /**< This type accepts either ipv4 or DNS name. */
    connector_element_type_fqdnv6,              /**< This type accepts either IPv6 address, IPv4 address, or DNS name. */
    connector_element_type_mac_addr = 21,       /**> Valid MAC address which is shown as XX:XX:XX:XX:XX:XX in Device Cloud. */
    connector_element_type_datetime = 22        /**< Date and time type. It's string which contains the ISO 8601 standard
                                                 for date and time representation. The format is: YYYY-MM-DDTHH:MM:SStz
                                                 where
                                                     @htmlonly
                                                     <table>
                                                     <tr><td>YYYY:</td> <td>Year<td></tr>
                                                     <tr><td>MM:</td> <td>Month<td></tr>
                                                     <tr><td>DD:</td> <td>Day<td></tr>
                                                     <tr><td>T:</td> <td>The separator between date and time<td></tr>
                                                     <tr><td>HH:</td> <td>Hours in 24-hour clock<td></tr>
                                                     <tr><td>MM:</td> <td>Minutes<td></tr>
                                                     <tr><td>SS:</td> <td>Seconds<td></tr>
                                                     <tr><td>tz:</td> <td>Time zone, specified either in the
                                                         form [+,-]HHMM or Z for Coordinated Universal Time (UTC) <td></tr>
                                                     </table>
                                                    @endhtmlonly */
} connector_element_value_type_t;
/**
* @}
*/


/**
 * @defgroup connector_element_value_t Cloud Connector remote configuration element value union
 * @{
 */
/**
 * Remote Configuration Element value
 */
typedef union {
    char const * string_value;          /**< Pointer to a null-terminated string for the following value types:
                                             @htmlonly
                                             <ul>
                                             <li>@endhtmlonly @ref connector_element_type_string @htmlonly</li>
                                             <li>@endhtmlonly @ref connector_element_type_multiline_string @htmlonly</li>
                                             <li>@endhtmlonly @ref connector_element_type_password @htmlonly</li>
                                             <li>@endhtmlonly @ref connector_element_type_ipv4 @htmlonly</li>
                                             <li>@endhtmlonly @ref connector_element_type_fqdnv4 @htmlonly</li>
                                             <li>@endhtmlonly @ref connector_element_type_fqdnv6 @htmlonly</li>
                                             <li>@endhtmlonly @ref connector_element_type_datetime @htmlonly</li>
                                             </ul>
                                             @endhtmlonly
                                             Note: An application's callback must return the address of the pointer
                                             to the string for connector_remote_action_set.
                                         */

    int32_t signed_integer_value;       /**< Signed integer value for @ref connector_element_type_int32 value type */

    uint32_t unsigned_integer_value;    /**< Unsigned integer value for the following value types:
                                             @htmlonly
                                             <ul>
                                             <li>@endhtmlonly @ref connector_element_type_uint32 @htmlonly</li>
                                             <li>@endhtmlonly @ref connector_element_type_hex32 @htmlonly</li>
                                             <li>@endhtmlonly @ref connector_element_type_0x_hex32 @htmlonly</li>
                                             </ul>
                                             @endhtmlonly
                                           */

    float float_value;                 /**< Floating point value for @ref connector_element_type_float value type */

    unsigned int enum_value;            /**< Enumeration value for @ref connector_element_type_enum value type */

    connector_on_off_t  on_off_value;       /**< @ref connector_on for on or @ref connector_off for Off value for @ref connector_element_type_on_off value type */

    connector_bool_t boolean_value;      /**< @ref connector_true for true or @ref connector_false for false value for @ref connector_element_type_boolean value type */

} connector_element_value_t;
/**
* @}
*/

/**
/**
 * @defgroup connector_remote_action_t Cloud Connector remote configuration action types
 * @{
 */
/**
 * Remote request action types
 */
typedef enum {
    connector_remote_action_set,    /**< Set remote configuration */
    connector_remote_action_query   /**< Query remote configuration */
} connector_remote_action_t;
/**
 * @}
 */

/**
* @defgroup connector_remote_group_t Cloud Connector remote configuration group
* @{
*/
/**
* Remote configuration group
*/
typedef struct {
    connector_remote_group_type_t type; /**< Type of the remote configuration group:
                                         @htmlonly
                                         <ul>
                                         <li>@endhtmlonly @ref connector_remote_group_setting @htmlonly for setting configuration</li>
                                         <li>@endhtmlonly @ref connector_remote_group_state @htmlonly for state configuration</li>
                                         </ul>
                                         @endhtmlonly
                                       */
    unsigned int id;                /**< An enumeration value of the remote configuration group */
    unsigned int index;             /**< Index of the remote configuration group */
} connector_remote_group_t;
/**
* @}
*/

/**
* @defgroup connector_remote_element_t Cloud Connector remote configuration element
* @{
*/
/**
* Remote configuration element
*/
typedef struct {
    unsigned int id;                /**< An enumeration value of the element */
    connector_element_value_type_t type;/**< Value type of the element */
    connector_element_value_t * value;  /**< Pointer to memory which contains the element value to be
                                         set for @ref connector_remote_action_set action */
} connector_remote_element_t;
/**
* @}
*/

/**
* @defgroup connector_remote_config_t Cloud Connector remote configuration structure
* @{
*/
/**
* Remote configuration structure used in the following callbacks:
* -# @ref connector_request_id_remote_config_session_start
* -# @ref connector_request_id_remote_config_action_start
* -# @ref connector_request_id_remote_config_group_start
* -# @ref connector_request_id_remote_config_group_process
* -# @ref connector_request_id_remote_config_group_end
* -# @ref connector_request_id_remote_config_action_end
* -# @ref connector_request_id_remote_config_session_end
*
*/
typedef struct {
  void * user_context;                /**< Pointer to callback's context returned from previous callback call.
                                     Callback may write its own context which will be passed back to sub-sequential callback.*/
  connector_remote_action_t action;   /**< @htmlonly <ul><li> @endhtmlonly @ref connector_remote_action_set @htmlonly for setting remote configuration or</li>
                                         <li> @endhtmlonly @ref connector_remote_action_query @htmlonly for querying remote configuration </li></ul> @endhtmlonly */
  connector_remote_attribute_t attribute;  /**< 'source' and 'compare_to' attributes value which are optional in a query setting command request */
  connector_remote_group_t group;     /**< Group configuration to be accessed */
  connector_remote_element_t element; /**< Element of the group configuration */
  unsigned int error_id;              /**< Callback writes error enumeration value if error is encountered.
                                     Error description is sent if it's provided for the given error_id. */

  struct {
      char const * error_hint;        /**< Callback returns a pointer to a constant null-terminated string which will be sent
                                        to Device Cloud if an error is encountered.
                                        Note: this string cannot be altered until next callback call.
                                      */
      connector_element_value_t * element_value; /**< Pointer to memory where callback writes the element value */
  } response;                        /**< Callback writes error hint or element value */
} connector_remote_config_t;
/**
* @}
*/

/**
* @defgroup connector_remote_config_cancel_t Cloud Connector remote configuration cancel structure
* @{
*/
/**
* Remote configuration cancel structure used in connector_request_id_remote_config_session_cancel callback.
*
*/
typedef struct {
  void * user_context;                /**< Pointer to callback's context returned from previous callback call */
} connector_remote_config_cancel_t;
/**
* @}
*/

#endif
