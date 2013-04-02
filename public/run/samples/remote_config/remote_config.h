/*
 * This is an auto-generated file - DO NOT EDIT!
 * This is generated by ConfigGenerator tool
 * This file was generated on: 2013/04/02 10:59:57
 * The command line arguments were: "username:***** "Linux Application" 1.0.0.0 config.rci"
 * The version of ConfigGenerator tool was: 2.0.0.0 */

#ifndef remote_config_h
#define remote_config_h

#define RCI_PARSER_USES_ERROR_DESCRIPTIONS
#define RCI_PARSER_USES_STRING
#define RCI_PARSER_USES_MULTILINE_STRING
#define RCI_PARSER_USES_PASSWORD
#define RCI_PARSER_USES_INT32
#define RCI_PARSER_USES_UINT32
#define RCI_PARSER_USES_0X_HEX32
#define RCI_PARSER_USES_ENUM
#define RCI_PARSER_USES_ON_OFF
#define RCI_PARSER_USES_BOOLEAN
#define RCI_PARSER_USES_IPV4
#define RCI_PARSER_USES_FQDNV4
#define RCI_PARSER_USES_DATETIME
#define RCI_PARSER_USES_UNSIGNED_INTEGER
#define RCI_PARSER_USES_STRINGS

typedef enum {
    connector_off,
    connector_on
} connector_on_off_t;


typedef enum {
    connector_element_type_string = 1,
    connector_element_type_multiline_string,
    connector_element_type_password,
    connector_element_type_int32,
    connector_element_type_uint32,
    connector_element_type_0x_hex32 = 7,
    connector_element_type_enum = 9,
    connector_element_type_on_off = 11,
    connector_element_type_boolean,
    connector_element_type_ipv4,
    connector_element_type_fqdnv4,
    connector_element_type_datetime = 22
} connector_element_value_type_t;

typedef struct {
    size_t min_length_in_bytes;
    size_t max_length_in_bytes;
} connector_element_value_string_t;

typedef struct {
   int32_t min_value;
   int32_t max_value;
} connector_element_value_signed_integer_t;

typedef struct {
   uint32_t min_value;
   uint32_t max_value;
} connector_element_value_unsigned_integer_t;

typedef struct {
    size_t count;
} connector_element_value_enum_t;


typedef union {
    char const * string_value;
    int32_t signed_integer_value;
    uint32_t unsigned_integer_value;
    unsigned int enum_value;
    connector_on_off_t  on_off_value;
    connector_bool_t  boolean_value;
} connector_element_value_t;


#include "connector_api_remote.h"


typedef struct {
    connector_element_access_t access;
    connector_element_value_type_t type;
} connector_group_element_t;

typedef struct {
  size_t instances;
  struct {
    size_t count;
    connector_group_element_t const * const data;
  } elements;

  struct {
      size_t count;
     char const * const * description;
  } errors;
} connector_group_t;

typedef struct {
  connector_remote_group_type_t type;
  unsigned int id;
  unsigned int index;
} connector_remote_group_t;

typedef struct {
  unsigned int id;
  connector_element_value_type_t type;
  connector_element_value_t * value;
} connector_remote_element_t;

typedef struct {
  void * user_context;
  connector_remote_action_t action;
  connector_remote_group_t group;
  connector_remote_element_t element;
  unsigned int error_id;

  union {
      char const * error_hint;
      connector_element_value_t * element_value;
  } response;
} connector_remote_config_t;

typedef struct {
  void * user_context;
} connector_remote_config_cancel_t;

typedef struct {
  connector_group_t const * groups;
  size_t count;
} connector_remote_group_table_t;

typedef enum {
 connector_rci_error_OFFSET = 1,
 connector_rci_error_bad_command =  connector_rci_error_OFFSET,
 connector_rci_error_bad_descriptor,
 connector_rci_error_COUNT
} connector_rci_error_id_t;


typedef enum {
 connector_global_error_OFFSET = connector_rci_error_COUNT,
 connector_global_error_load_fail =  connector_global_error_OFFSET,
 connector_global_error_save_fail,
 connector_global_error_memory_fail,
 connector_global_error_COUNT
} connector_global_error_id_t;

typedef enum {
 connector_setting_serial_baud_2400,
 connector_setting_serial_baud_4800,
 connector_setting_serial_baud_9600,
 connector_setting_serial_baud_19200,
 connector_setting_serial_baud_38400,
 connector_setting_serial_baud_57600,
 connector_setting_serial_baud_115200,
 connector_setting_serial_baud_230400,
 connector_setting_serial_baud_COUNT
} connector_setting_serial_baud_id_t;

typedef enum {
 connector_setting_serial_parity_none,
 connector_setting_serial_parity_odd,
 connector_setting_serial_parity_even,
 connector_setting_serial_parity_COUNT
} connector_setting_serial_parity_id_t;

typedef enum {
 connector_setting_serial_baud,
 connector_setting_serial_parity,
 connector_setting_serial_databits,
 connector_setting_serial_xbreak,
 connector_setting_serial_txbytes,
 connector_setting_serial_COUNT
} connector_setting_serial_id_t;

typedef enum {
 connector_setting_serial_error_invalid_baud = connector_global_error_COUNT,
 connector_setting_serial_error_invalid_databits,
 connector_setting_serial_error_invalid_parity,
 connector_setting_serial_error_invalid_xbreak,
 connector_setting_serial_error_invalid_databits_parity,
 connector_setting_serial_error_COUNT
} connector_setting_serial_error_id_t;

typedef enum {
 connector_setting_ethernet_duplex_auto,
 connector_setting_ethernet_duplex_half,
 connector_setting_ethernet_duplex_full,
 connector_setting_ethernet_duplex_COUNT
} connector_setting_ethernet_duplex_id_t;

typedef enum {
 connector_setting_ethernet_ip,
 connector_setting_ethernet_subnet,
 connector_setting_ethernet_gateway,
 connector_setting_ethernet_dhcp,
 connector_setting_ethernet_dns,
 connector_setting_ethernet_duplex,
 connector_setting_ethernet_COUNT
} connector_setting_ethernet_id_t;

typedef enum {
 connector_setting_ethernet_error_invalid_duplex = connector_global_error_COUNT,
 connector_setting_ethernet_error_invalid_ip,
 connector_setting_ethernet_error_invalid_subnet,
 connector_setting_ethernet_error_invalid_gateway,
 connector_setting_ethernet_error_invalid_dns,
 connector_setting_ethernet_error_COUNT
} connector_setting_ethernet_error_id_t;

typedef enum {
 connector_setting_device_time_curtime,
 connector_setting_device_time_COUNT
} connector_setting_device_time_id_t;

typedef enum {
 connector_setting_device_time_error_invalid_time = connector_global_error_COUNT,
 connector_setting_device_time_error_COUNT
} connector_setting_device_time_error_id_t;

typedef enum {
 connector_setting_device_info_version,
 connector_setting_device_info_product,
 connector_setting_device_info_model,
 connector_setting_device_info_company,
 connector_setting_device_info_desc,
 connector_setting_device_info_COUNT
} connector_setting_device_info_id_t;

typedef enum {
 connector_setting_system_description,
 connector_setting_system_contact,
 connector_setting_system_location,
 connector_setting_system_COUNT
} connector_setting_system_id_t;

typedef enum {
 connector_setting_devicesecurity_identityVerificationForm_simple,
 connector_setting_devicesecurity_identityVerificationForm_password,
 connector_setting_devicesecurity_identityVerificationForm_COUNT
} connector_setting_devicesecurity_identityVerificationForm_id_t;

typedef enum {
 connector_setting_devicesecurity_identityVerificationForm,
 connector_setting_devicesecurity_password,
 connector_setting_devicesecurity_COUNT
} connector_setting_devicesecurity_id_t;

typedef enum {
 connector_setting_serial,
 connector_setting_ethernet,
 connector_setting_device_time,
 connector_setting_device_info,
 connector_setting_system,
 connector_setting_devicesecurity,
 connector_setting_COUNT
} connector_setting_id_t;

typedef enum {
 connector_state_device_state_system_up_time,
 connector_state_device_state_signed_integer,
 connector_state_device_state_COUNT
} connector_state_device_state_id_t;

typedef enum {
 connector_state_device_state_error_invalid_integer = connector_global_error_COUNT,
 connector_state_device_state_error_COUNT
} connector_state_device_state_error_id_t;

typedef enum {
 connector_state_gps_stats_latitude,
 connector_state_gps_stats_longitude,
 connector_state_gps_stats_COUNT
} connector_state_gps_stats_id_t;

typedef enum {
 connector_state_device_state,
 connector_state_gps_stats,
 connector_state_COUNT
} connector_state_id_t;



#if defined CONNECTOR_RCI_PARSER_INTERNAL_DATA

#define CONNECTOR_BINARY_RCI_SERVICE

#define FIRMWARE_TARGET_ZERO_VERSION  0x1000000

#define CONNECTOR_RCI_ERROR_BAD_COMMAND (connector_remote_all_strings+0)
#define CONNECTOR_RCI_ERROR_BAD_DESCRIPTOR (connector_remote_all_strings+12)
#define SETTING_SERIAL_ERROR_INVALID_BAUD (connector_remote_all_strings+30)
#define SETTING_SERIAL_ERROR_INVALID_DATABITS (connector_remote_all_strings+49)
#define SETTING_SERIAL_ERROR_INVALID_PARITY (connector_remote_all_strings+67)
#define SETTING_SERIAL_ERROR_INVALID_XBREAK (connector_remote_all_strings+83)
#define SETTING_SERIAL_ERROR_INVALID_DATABITS_PARITY (connector_remote_all_strings+106)
#define SETTING_ETHERNET_ERROR_INVALID_DUPLEX (connector_remote_all_strings+150)
#define SETTING_ETHERNET_ERROR_INVALID_IP (connector_remote_all_strings+182)
#define SETTING_ETHERNET_ERROR_INVALID_SUBNET (connector_remote_all_strings+201)
#define SETTING_ETHERNET_ERROR_INVALID_GATEWAY (connector_remote_all_strings+221)
#define SETTING_ETHERNET_ERROR_INVALID_DNS (connector_remote_all_strings+245)
#define SETTING_DEVICE_TIME_ERROR_INVALID_TIME (connector_remote_all_strings+265)
#define STATE_DEVICE_STATE_ERROR_INVALID_INTEGER (connector_remote_all_strings+278)
#define CONNECTOR_GLOBAL_ERROR_LOAD_FAIL (connector_remote_all_strings+300)
#define CONNECTOR_GLOBAL_ERROR_SAVE_FAIL (connector_remote_all_strings+310)
#define CONNECTOR_GLOBAL_ERROR_MEMORY_FAIL (connector_remote_all_strings+320)

char const connector_remote_all_strings[] = {
 11,'B','a','d',' ','c','o','m','m','a','n','d',
 17,'B','a','d',' ','c','o','n','f','i','g','u','r','a','t','i','o','n',
 18,'I','n','v','a','l','i','d',' ','b','a','u','d',' ','r','a','t','e',' ',
 17,'I','n','v','a','l','i','d',' ','d','a','t','a',' ','b','i','t','s',
 15,' ','I','n','v','a','l','i','d',' ','p','a','r','i','t','y',
 22,'I','n','v','a','l','i','d',' ','x','b','r','e','a','k',' ','s','e','t','t','i','n','g',
 43,'I','n','v','a','l','i','d',' ','c','o','m','b','i','n','a','t','i','o','n',' ','o','f',' ','d','a','t','a',' ','b','i','t','s',' ','a','n','d',' ','p','a','r','i','t','y',
 31,'I','n','v','a','l','i','d',' ','e','t','h','e','r','n','e','t',' ','d','u','p','l','e','x',' ','s','e','t','t','i','n','g',
 18,'I','n','v','a','l','i','d',' ','I','P',' ','a','d','d','r','e','s','s',
 19,'I','n','v','a','l','i','d',' ','s','u','b','n','e','t',' ','m','a','s','k',
 23,'I','n','v','a','l','i','d',' ','g','a','t','e','w','a','y',' ','a','d','d','r','e','s','s',
 19,'I','n','v','a','l','i','d',' ','D','N','S',' ','a','d','d','r','e','s','s',
 12,'I','n','v','a','l','i','d',' ','t','i','m','e',
 21,'I','n','v','a','l','i','d',' ','i','n','t','e','g','e','r',' ','v','a','l','u','e',
 9,'L','o','a','d',' ','f','a','i','l',
 9,'S','a','v','e',' ','f','a','i','l',
 19,'I','n','s','u','f','f','i','c','i','e','n','t',' ','m','e','m','o','r','y'
};

static char const * const connector_rci_errors[] = {
 CONNECTOR_RCI_ERROR_BAD_COMMAND, /*bad_command*/
 CONNECTOR_RCI_ERROR_BAD_DESCRIPTOR, /*bad_descriptor*/
 CONNECTOR_GLOBAL_ERROR_LOAD_FAIL, /*load_fail*/
 CONNECTOR_GLOBAL_ERROR_SAVE_FAIL, /*save_fail*/
 CONNECTOR_GLOBAL_ERROR_MEMORY_FAIL /*memory_fail*/
};

static connector_group_element_t const setting_serial_elements[] = {
 {  /*baud*/
   connector_element_access_read_write,
   connector_element_type_enum
 },
 {  /*parity*/
   connector_element_access_read_write,
   connector_element_type_enum
 },
 {  /*databits*/
   connector_element_access_read_write,
   connector_element_type_uint32
 },
 {  /*xbreak*/
   connector_element_access_read_write,
   connector_element_type_on_off
 },
 {  /*txbytes*/
   connector_element_access_read_only,
   connector_element_type_uint32
 }
};

static char const * const setting_serial_errors[] = {
 SETTING_SERIAL_ERROR_INVALID_BAUD, /*invalid_baud*/
 SETTING_SERIAL_ERROR_INVALID_DATABITS, /*invalid_databits*/
 SETTING_SERIAL_ERROR_INVALID_PARITY, /*invalid_parity*/
 SETTING_SERIAL_ERROR_INVALID_XBREAK, /*invalid_xbreak*/
 SETTING_SERIAL_ERROR_INVALID_DATABITS_PARITY /*invalid_databits_parity*/
};

static connector_group_element_t const setting_ethernet_elements[] = {
 {  /*ip*/
   connector_element_access_read_write,
   connector_element_type_ipv4
 },
 {  /*subnet*/
   connector_element_access_read_write,
   connector_element_type_ipv4
 },
 {  /*gateway*/
   connector_element_access_read_write,
   connector_element_type_ipv4
 },
 {  /*dhcp*/
   connector_element_access_read_write,
   connector_element_type_boolean
 },
 {  /*dns*/
   connector_element_access_read_write,
   connector_element_type_fqdnv4
 },
 {  /*duplex*/
   connector_element_access_read_write,
   connector_element_type_enum
 }
};

static char const * const setting_ethernet_errors[] = {
 SETTING_ETHERNET_ERROR_INVALID_DUPLEX, /*invalid_duplex*/
 SETTING_ETHERNET_ERROR_INVALID_IP, /*invalid_ip*/
 SETTING_ETHERNET_ERROR_INVALID_SUBNET, /*invalid_subnet*/
 SETTING_ETHERNET_ERROR_INVALID_GATEWAY, /*invalid_gateway*/
 SETTING_ETHERNET_ERROR_INVALID_DNS /*invalid_dns*/
};

static connector_group_element_t const setting_device_time_elements[] = {
 {  /*curtime*/
   connector_element_access_read_write,
   connector_element_type_datetime
 }
};

static char const * const setting_device_time_errors[] = {
 SETTING_DEVICE_TIME_ERROR_INVALID_TIME /*invalid_time*/
};

static connector_group_element_t const setting_device_info_elements[] = {
 {  /*version*/
   connector_element_access_read_only,
   connector_element_type_0x_hex32
 },
 {  /*product*/
   connector_element_access_read_write,
   connector_element_type_string
 },
 {  /*model*/
   connector_element_access_read_write,
   connector_element_type_string
 },
 {  /*company*/
   connector_element_access_read_write,
   connector_element_type_string
 },
 {  /*desc*/
   connector_element_access_read_write,
   connector_element_type_multiline_string
 }
};

static connector_group_element_t const setting_system_elements[] = {
 {  /*description*/
   connector_element_access_read_write,
   connector_element_type_string
 },
 {  /*contact*/
   connector_element_access_read_write,
   connector_element_type_string
 },
 {  /*location*/
   connector_element_access_read_write,
   connector_element_type_string
 }
};

static connector_group_element_t const setting_devicesecurity_elements[] = {
 {  /*identityVerificationForm*/
   connector_element_access_read_write,
   connector_element_type_enum
 },
 {  /*password*/
   connector_element_access_write_only,
   connector_element_type_password
 }
};

static connector_group_t const connector_setting_groups[] = {
 {  /*serial*/
   2,
   { asizeof(setting_serial_elements),
     setting_serial_elements
   },
   { asizeof(setting_serial_errors),
     setting_serial_errors
   }
 }
,
 {  /*ethernet*/
   1,
   { asizeof(setting_ethernet_elements),
     setting_ethernet_elements
   },
   { asizeof(setting_ethernet_errors),
     setting_ethernet_errors
   }
 }
,
 {  /*device_time*/
   1,
   { asizeof(setting_device_time_elements),
     setting_device_time_elements
   },
   { asizeof(setting_device_time_errors),
     setting_device_time_errors
   }
 }
,
 {  /*device_info*/
   1,
   { asizeof(setting_device_info_elements),
     setting_device_info_elements
   },
   { 0,
     NULL
   }
 },
 {  /*system*/
   1,
   { asizeof(setting_system_elements),
     setting_system_elements
   },
   { 0,
     NULL
   }
 },
 {  /*devicesecurity*/
   1,
   { asizeof(setting_devicesecurity_elements),
     setting_devicesecurity_elements
   },
   { 0,
     NULL
   }
 }
};

static connector_group_element_t const state_device_state_elements[] = {
 {  /*system_up_time*/
   connector_element_access_read_only,
   connector_element_type_uint32
 },
 {  /*signed_integer*/
   connector_element_access_read_write,
   connector_element_type_int32
 }
};

static char const * const state_device_state_errors[] = {
 STATE_DEVICE_STATE_ERROR_INVALID_INTEGER /*invalid_integer*/
};

static connector_group_element_t const state_gps_stats_elements[] = {
 {  /*latitude*/
   connector_element_access_read_only,
   connector_element_type_string
 },
 {  /*longitude*/
   connector_element_access_read_only,
   connector_element_type_string
 }
};

static connector_group_t const connector_state_groups[] = {
 {  /*device_state*/
   1,
   { asizeof(state_device_state_elements),
     state_device_state_elements
   },
   { asizeof(state_device_state_errors),
     state_device_state_errors
   }
 }
,
 {  /*gps_stats*/
   1,
   { asizeof(state_gps_stats_elements),
     state_gps_stats_elements
   },
   { 0,
     NULL
   }
 }
};

static connector_remote_group_table_t const connector_group_table[] = {
 {connector_setting_groups,
 asizeof(connector_setting_groups)
 },
 {connector_state_groups,
 asizeof(connector_state_groups)
 }
};


#endif /* CONNECTOR_RCI_PARSER_INTERNAL_DATA */


#endif /* remote_config_h */
