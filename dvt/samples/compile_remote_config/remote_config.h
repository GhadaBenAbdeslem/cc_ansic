/*
 * This is an auto-generated file - DO NOT EDIT! 
 * This is generated by ConfigGenerator tool 
 * This file was generated on: 2012/12/17 10:42:01 
 * The command line arguments were: "-server=test.idigi.com mlchan:***** "Linux Application" 1.0.0.0 boolean.rci"
 * The version of ConfigGenerator tool was: 1.1.0.0 */

#ifndef remote_config_h
#define remote_config_h

#define RCI_PARSER_USES_ERROR_DESCRIPTIONS
#define RCI_PARSER_USES_BOOLEAN

typedef enum {
    connector_boolean_false,
    connector_boolean_true
} connector_boolean_t;


typedef enum {
    connector_element_type_boolean = 12
} connector_element_value_type_t;

typedef struct {
    size_t count;
} connector_element_value_enum_t;


typedef struct {
    connector_boolean_t  boolean_value;
} connector_element_value_t;


typedef void connector_element_value_limit_t;


#include "connector_remote.h"


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
 connector_setting_system_COUNT
} connector_setting_system_id_t;

typedef enum {
 connector_setting_system,
 connector_setting_COUNT
} connector_setting_id_t;



#if defined CONNECTOR_RCI_PARSER_INTERNAL_DATA

#define CONNECTOR_BINARY_RCI_SERVICE 

#define FIRMWARE_TARGET_ZERO_VERSION  0x1000000

#define CONNECTOR_RCI_ERROR_BAD_COMMAND (connector_remote_all_strings+0)
#define CONNECTOR_RCI_ERROR_BAD_DESCRIPTOR (connector_remote_all_strings+12)

char const connector_remote_all_strings[] = {
 11,'B','a','d',' ','c','o','m','m','a','n','d',
 17,'B','a','d',' ','c','o','n','f','i','g','u','r','a','t','i','o','n'
};

static char const * const connector_rci_errors[] = {
 CONNECTOR_RCI_ERROR_BAD_COMMAND, /*bad_command*/
 CONNECTOR_RCI_ERROR_BAD_DESCRIPTOR /*bad_descriptor*/
};

static connector_group_element_t const setting_system_elements[] = {
 {  /*contact*/
  NULL,
   connector_element_access_read_write,
   connector_element_type_boolean,
  NULL
 }
};

static connector_group_t const connector_setting_groups[] = {
 {  /*system*/
  NULL,
   1,
   { asizeof(setting_system_elements),
     setting_system_elements
   },
   { 0,
     NULL
   }
 }
};

static connector_group_table_t const connector_group_table[] = {
 {connector_setting_groups,
 asizeof(connector_setting_groups)
 },
 {NULL,
 0
 }
};


#endif /* CONNECTOR_RCI_PARSER_INTERNAL_DATA */


#endif /* remote_config_h */
