
/*
 *  Copyright (c) 1996-2011 Digi International Inc., All Rights Reserved
 *
 *  This software contains proprietary and confidential information of Digi
 *  International Inc.  By accepting transfer of this copy, Recipient agrees
 *  to retain this software in confidence, to prevent disclosure to others,
 *  and to make no use of this software other than that for which it was
 *  delivered.  This is an unpublished copyrighted work of Digi International
 *  Inc.  Except as permitted by federal law, 17 USC 117, copying is strictly
 *  prohibited.
 *
 *  Restricted Rights Legend
 *
 *  Use, duplication, or disclosure by the Government is subject to
 *  restrictions set forth in sub-paragraph (c)(1)(ii) of The Rights in
 *  Technical Data and Computer Software clause at DFARS 252.227-7031 or
 *  subparagraphs (c)(1) and (2) of the Commercial Computer Software -
 *  Restricted Rights at 48 CFR 52.227-19, as applicable.
 *
 *  Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 *
 * =======================================================================
 *
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "connector_api.h"

#define DS_MAX_USER 1

#define TERMINATE_TEST_FILE "terminate_test.txt"
#define HEAP_USAGE_FILE     "./dvt/heap_usage.txt"

extern connector_handle_t connector_handle;
extern unsigned int put_file_active_count;
extern int firmware_download_started;
extern size_t total_malloc_size;
extern size_t total_max_malloc_size;
extern connector_status_t connector_run_thread_status;

extern void clear_stack_size(void);
void write_usage_file(char const * text);

#if (defined CONNECTOR_DATA_SERVICE)
extern connector_callback_status_t app_data_service_handler(connector_request_id_data_service_t const request_id,
                                                  void * const data);
extern connector_status_t send_put_request(connector_handle_t handle, int index);
#endif

#if (defined CONNECTOR_FILE_SYSTEM)
extern connector_callback_status_t app_firmware_handler(connector_request_id_firmware_t const request_id,
                                                  void * const data);
#endif

extern connector_status_t app_terminate_tcp_transport(connector_handle_t handle);

#endif /* APPLICATION_H_ */
