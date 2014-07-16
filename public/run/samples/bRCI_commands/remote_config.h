/*
 * This is an auto-generated file - DO NOT EDIT! 
 * This is generated by RCI Generator tool 
 * This file was generated on: 2014/07/15 13:02:05 
 * The command line arguments were: "-rci_legacy_commands -rci_dc_target_max=50 -url=test.etherios.com testframework:***** "Linux Application" 1.0.0.0 config.rci"
 * The version of RCI Generator tool was: 2.0.0.0 */

#ifndef remote_config_h
#define remote_config_h



#include "connector_api.h"


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

#define RCI_LEGACY_COMMANDS

#define DO_COMMAND_TARGET_MAX_LEN 50

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

typedef struct rci_data {
 unsigned int group_index;
 connector_remote_action_t action;
 connector_remote_group_type_t group_type;
 char const * error_hint;
 void * user_context;
} rci_info_t;

typedef connector_callback_status_t (*rci_function_t)(rci_info_t * const info, ...);

typedef struct {
    connector_element_access_t access;
    connector_element_value_type_t type;
} connector_group_element_t;

typedef struct {
  size_t instances;
  struct {
      size_t count;
      connector_group_element_t CONST * CONST data;
  } elements;

  struct {
      size_t count;
      char CONST * CONST * description;
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

typedef struct connector_remote_group_table {
  connector_group_t CONST * groups;
  size_t count;
} connector_remote_group_table_t;


typedef enum {
 connector_rci_error_OFFSET = 1,
 connector_rci_error_bad_command =  connector_rci_error_OFFSET,
 connector_rci_error_bad_descriptor,
 connector_rci_error_reboot_failed,
 connector_rci_error_invalid_arguments,
 connector_rci_error_do_command_failed,
 connector_rci_error_set_factory_default_failed,
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
 connector_setting_system_description,
 connector_setting_system_contact,
 connector_setting_system_location,
 connector_setting_system_COUNT
} connector_setting_system_id_t;

typedef enum {
 connector_setting_system_error_bad_command = 1, /* Protocol defined */
 connector_setting_system_error_bad_descriptor,
 connector_setting_system_error_reboot_failed,
 connector_setting_system_error_invalid_arguments,
 connector_setting_system_error_do_command_failed,
 connector_setting_system_error_set_factory_default_failed,
 connector_setting_system_error_load_fail, /* User defined (global errors) */
 connector_setting_system_error_save_fail,
 connector_setting_system_error_memory_fail,
 connector_setting_system_error_invalid_length,  /* User defined (group errors)*/
 connector_setting_system_error_COUNT
} connector_setting_system_error_id_t;

typedef enum {
 connector_setting_system,
 connector_setting_COUNT
} connector_setting_id_t;

typedef enum {
 connector_state_gps_stats_latitude,
 connector_state_gps_stats_longitude,
 connector_state_gps_stats_COUNT
} connector_state_gps_stats_id_t;

typedef enum {
 connector_state_gps_stats,
 connector_state_COUNT
} connector_state_id_t;


extern connector_remote_config_data_t rci_desc_data;


#undef CONST
#if (defined CONNECTOR_CONST_STORAGE)
#define CONST CONNECTOR_CONST_STORAGE
#undef CONNECTOR_CONST_STORAGE
#endif


#endif
