/*
 * Copyright (c) 2014 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */
#ifndef CONNECTOR_API_DEVICE_HEALTH_H_
#define CONNECTOR_API_DEVICE_HEALTH_H_

#if (defined CONNECTOR_DEVICE_HEALTH)

#define DEV_HEALTH_MAX_STREAM_ID_LEN               64

typedef struct {
    connector_bool_t metrics;
    unsigned long sample_rate;
} dev_health_simple_metric_t;

typedef struct {
    dev_health_simple_metric_t eth;
    dev_health_simple_metric_t mobile;
    dev_health_simple_metric_t sys;
    unsigned long report_rate;
} dev_health_simple_metrics_config_t;

typedef struct {
    unsigned int upper;
    unsigned int lower;
} connector_indexes_t;

typedef enum {
  NETWORK_TECH_2G,
  NETWORK_TECH_3G,
  NETWORK_TECH_4G
} mobile_network_tech_t;

connector_callback_status_t cc_dev_health_simple_config_load(dev_health_simple_metrics_config_t * const simple_metrics);
connector_callback_status_t cc_dev_health_simple_config_save(dev_health_simple_metrics_config_t const * const simple_metrics);

char * cc_dev_health_malloc_string(size_t size);
void cc_dev_health_free_string(char const * const string);

uint32_t cc_dev_health_get_posix_time(void);

unsigned int cc_dev_health_get_mobile_instances(unsigned int const upper_index);
unsigned int cc_dev_health_get_mobile_net_instances(unsigned int const upper_index);

void cc_dev_health_get_mobile_module_imei(connector_indexes_t const * const indexes, char * * const value);
void cc_dev_health_get_mobile_module_modem_id(connector_indexes_t const * const indexes, char * * const value);
void cc_dev_health_get_mobile_module_sims(connector_indexes_t const * const indexes, unsigned int * const value);

void cc_dev_health_get_mobile_net_info_iccid(connector_indexes_t const * const indexes, char * * const value);
void cc_dev_health_get_mobile_net_info_imsi(connector_indexes_t const * const indexes, char * * const value);
void cc_dev_health_get_mobile_net_info_phone_num(connector_indexes_t const * const indexes, char * * const value);

void cc_dev_health_get_mobile_net_status_registration(connector_indexes_t const * const indexes, char * * const value);
void cc_dev_health_get_mobile_net_status_attachment(connector_indexes_t const * const indexes, char * * const value);

connector_bool_t cc_dev_health_mobile_module_present(connector_indexes_t const * const indexes);
connector_bool_t cc_dev_health_mobile_module_net_status_present(connector_indexes_t const * const indexes);
connector_bool_t cc_dev_health_get_mobile_net_info_present(connector_indexes_t const * const indexes);

connector_bool_t cc_dev_health_get_mobile_temperature(connector_indexes_t const * const indexes, float * const value);
connector_bool_t cc_dev_health_get_mobile_active_sim(connector_indexes_t const * const indexes, unsigned int * const value);
connector_bool_t cc_dev_health_get_mobile_net_cell_id(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_network(connector_indexes_t const * const indexes, char * * const value);
connector_bool_t cc_dev_health_get_mobile_net_rssi(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_ecio(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_rsrp(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_rsrq(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_sinr(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_snr(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_lac(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_tac(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_session(connector_indexes_t const * const indexes, int32_t * const value);

connector_bool_t cc_dev_health_get_mobile_net_rxbytes(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_txbytes(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_latency_min(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_latency_avg(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_latency_max(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_transactions_count(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_fdrop_count(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_losspercent(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_drop_count(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_oos_count(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);
connector_bool_t cc_dev_health_get_mobile_net_uptime(connector_indexes_t const * const indexes, mobile_network_tech_t tech, int32_t * const value);

unsigned int cc_dev_health_get_eth_instances(unsigned int const upper_index);

connector_bool_t cc_dev_health_get_eth_tx_bytes(connector_indexes_t const * const indexes, uint64_t * const value);
connector_bool_t cc_dev_health_get_eth_tx_packets(connector_indexes_t const * const indexes, uint64_t * const value);
connector_bool_t cc_dev_health_get_eth_tx_dropped(connector_indexes_t const * const indexes, uint64_t * const value);
connector_bool_t cc_dev_health_get_eth_tx_overruns(connector_indexes_t const * const indexes, uint64_t * const value);
connector_bool_t cc_dev_health_get_eth_rx_bytes(connector_indexes_t const * const indexes, uint64_t * const value);
connector_bool_t cc_dev_health_get_eth_rx_packets(connector_indexes_t const * const indexes, uint64_t * const value);
connector_bool_t cc_dev_health_get_eth_rx_dropped(connector_indexes_t const * const indexes, uint64_t * const value);

connector_bool_t cc_dev_health_get_eth_link_down_count(connector_indexes_t const * const indexes, uint64_t * const value);
connector_bool_t cc_dev_health_get_eth_link_down_duration(connector_indexes_t const * const indexes, uint64_t * const value);

unsigned int cc_dev_health_get_wifi_instances(unsigned int const upper_index);

void cc_dev_health_get_wifi_radio_mode(connector_indexes_t const * const indexes, char * * const value);
void cc_dev_health_get_wifi_radio_ssid(connector_indexes_t const * const indexes, char * * const value);
void cc_dev_health_get_wifi_radio_channel(connector_indexes_t const * const indexes, unsigned int * const value);
void cc_dev_health_get_wifi_radio_protocol(connector_indexes_t const * const indexes, char * * const value);
connector_bool_t cc_dev_health_get_wifi_radio_present(connector_indexes_t const * const indexes);

connector_bool_t cc_dev_health_get_wifi_status(connector_indexes_t const * const indexes, char * * const value);
connector_bool_t cc_dev_health_get_wifi_rssi(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_wifi_rate(connector_indexes_t const * const indexes, float * const value);
connector_bool_t cc_dev_health_get_wifi_clients(connector_indexes_t const * const indexes, int32_t * const value);

connector_bool_t cc_dev_health_get_system_mem_available(connector_indexes_t const * const indexes, uint64_t * const value);
connector_bool_t cc_dev_health_get_system_mem_free(connector_indexes_t const * const indexes, uint64_t * const value);
connector_bool_t cc_dev_health_get_system_reboots(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_system_msg_free(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_system_msg_min(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_system_buf_free(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_system_buf_min(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_system_bigbuf_free(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_system_bigbuf_min(connector_indexes_t const * const indexes, int32_t * const value);
connector_bool_t cc_dev_health_get_system_cpu_used(connector_indexes_t const * const indexes, int32_t * const value);

#endif

#endif
