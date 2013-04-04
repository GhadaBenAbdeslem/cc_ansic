/*
 * This is an auto-generated file - DO NOT EDIT!
 * This is generated by ConfigGenerator tool
 * This file was generated on: 2013/04/04 15:03:10
 * The command line arguments were: "username:***** "Linux Application" 1.0.0.0 config.rci"
 * The version of ConfigGenerator tool was: 2.0.0.0 */

#ifndef remote_config_h
#define remote_config_h


#if (defined CONNECTOR_CONST_PROTECTION)
#define CONST
#undef CONNECTOR_CONST_PROTECTION
#else
#if (defined CONST)
#define CONNECTOR_CONST_STORAGE CONST
#undef CONST
#endif
#define CONST const
#endif

#define RCI_PARSER_USES_ERROR_DESCRIPTIONS
#define RCI_PARSER_USES_STRING
#define RCI_PARSER_USES_STRINGS


typedef enum {
    connector_element_type_string = 1
} connector_element_value_type_t;

typedef struct {
    size_t min_length_in_bytes;
    size_t max_length_in_bytes;
} connector_element_value_string_t;


typedef struct {
    char const * string_value;
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
  connector_remote_action_t CONST action;
  connector_remote_group_t CONST group;
  connector_remote_element_t CONST element;
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
 connector_global_error_COUNT = connector_global_error_OFFSET
} connector_global_error_id_t;

typedef enum {
 connector_setting_system_contact,
 connector_setting_system_location,
 connector_setting_system_description,
 connector_setting_system_COUNT
} connector_setting_system_id_t;

typedef enum {
 connector_setting_system_error_invalid_length = connector_global_error_COUNT,
 connector_setting_system_error_no_memory,
 connector_setting_system_error_COUNT
} connector_setting_system_error_id_t;

typedef enum {
 connector_setting_system,
 connector_setting_COUNT
} connector_setting_id_t;



#if defined CONNECTOR_RCI_PARSER_INTERNAL_DATA

#define CONNECTOR_BINARY_RCI_SERVICE

#define FIRMWARE_TARGET_ZERO_VERSION  0x1000000

#define CONNECTOR_RCI_ERROR_BAD_COMMAND (connector_remote_all_strings+0)
#define CONNECTOR_RCI_ERROR_BAD_DESCRIPTOR (connector_remote_all_strings+12)
#define SETTING_SYSTEM_ERROR_INVALID_LENGTH (connector_remote_all_strings+30)
#define SETTING_SYSTEM_ERROR_NO_MEMORY (connector_remote_all_strings+45)

char const connector_remote_all_strings[] = {
 11,'B','a','d',' ','c','o','m','m','a','n','d',
 17,'B','a','d',' ','c','o','n','f','i','g','u','r','a','t','i','o','n',
 14,'I','n','v','a','l','i','d',' ','L','e','n','g','t','h',
 19,'I','n','s','u','f','f','i','c','i','e','n','t',' ','m','e','m','o','r','y'
};

static char const * const connector_rci_errors[] = {
 CONNECTOR_RCI_ERROR_BAD_COMMAND, /*bad_command*/
 CONNECTOR_RCI_ERROR_BAD_DESCRIPTOR /*bad_descriptor*/
};

static connector_group_element_t const setting_system_elements[] = {
 {  /*contact*/
   connector_element_access_read_write,
   connector_element_type_string
 },
 {  /*location*/
   connector_element_access_read_write,
   connector_element_type_string
 },
 {  /*description*/
   connector_element_access_read_write,
   connector_element_type_string
 }
};

static char const * const setting_system_errors[] = {
 SETTING_SYSTEM_ERROR_INVALID_LENGTH, /*invalid_length*/
 SETTING_SYSTEM_ERROR_NO_MEMORY /*no_memory*/
};

static connector_group_t const connector_setting_groups[] = {
 {  /*system*/
   1,
   { asizeof(setting_system_elements),
     setting_system_elements
   },
   { asizeof(setting_system_errors),
     setting_system_errors
   }
 }

};

static connector_remote_group_table_t const connector_group_table[] = {
 {connector_setting_groups,
 asizeof(connector_setting_groups)
 },
 {NULL,
 0
 }
};


#endif /* CONNECTOR_RCI_PARSER_INTERNAL_DATA */


#undef CONST
#if (defined CONNECTOR_CONST_STORAGE)
#define CONST CONNECTOR_CONST_STORAGE
#undef CONNECTOR_CONST_STORAGE
#endif


#endif /* remote_config_h */
