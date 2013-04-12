
/*! @page network_ssl_callbacks Network Callbacks for SSL connection
 *
 * @htmlinclude nav.html
 *
 * @section net_ssl Network Callbacks
 * From the top level these callbacks are analogous to the @ref network_callbacks. Internally they provide
 * interface to securely connect to Etherios Device Cloud on SSL. Any application can make use of these APIs to
 * obtain secure connection just by including network_tcp_ssl.c instead of network_tcp.c. The sample application
 * @ref connect_on_ssl is created to demonstrate how easy to enable SSL connections. Like @ref network_callbacks,
 * the SSL network interface module will provide the following callback APIs 
 * 
 *  -# @ref ssl_connect
 *  -# @ref ssl_send
 *  -# @ref ssl_receive
 *  -# @ref ssl_close
 * 
 * The SSL network callback APIs use openssl functions to communicate with Etherios Device Cloud over SSL connection.
 * These APIs can be found in network_tcp_ssl.c under platforms/<i>my_platform</i> to demonstrate how one can
 * write the network layer callback APIs to connect, send, receive and close the SSL connection.
 * As far as the top level calls are concerned there is no change between the SSL and non-SSL connection.
 *
 * The CA certificate is stored in public/certificates/ directory. A define APP_SSL_CA_CERT can be found
 * in platform.h. By default it is set to "../../../certificates/idigi-ca-cert-public.crt".
 *
 * @section ssl_connect Open
 *
 * This callback is called to establish SSL connection between Etherios Cloud Connector and Etherios Device Cloud.
 * Callback is responsible to setup any socket options and SSL specific initial settings.
 * 
 * This callback is trapped in application.c, in the @b Sample section of @ref AppStructure "Public Application Framework"
 * and implemented in the @b Platform function app_network_tcp_open() in network_tcp_ssl.c.
 *
 *
 * @htmlonly
 * <table class="apitable">
 * <tr>
 *   <th colspan="2" class="title">Arguments</th>
 * </tr>
 * <tr>
 *   <th class="subtitle">Name</th> <th class="subtitle">Description</th>
 * </tr>
 * <tr>
 *   <th>class_id</th>
 *   <td>@endhtmlonly @ref connector_class_network_tcp @htmlonly</td>
 * </tr>
 * <tr>
 *   <th>request_id</th>
 *   <td>@endhtmlonly @ref connector_network_open @htmlonly</td>
 * </tr>
 * <tr>
 *   <th>request_data</th>
 *   <td>Pointer to server URL that callback will make connection to on @endhtmlonly @ref CONNECTOR_SSL_PORT @htmlonly for secure communication </td>
 * </tr>
 * <tr>
 *   <th>request_length</th>
 *   <td> Length of the server URL.</td>
 * </tr>
 * <tr>
 *   <th>response_data</th>
 *   <td> Callback returns the pointer to  @endhtmlonly @ref connector_network_handle_t @htmlonly which is used throughout network socket callback calls. </td>
 * </tr>
 * <tr>
 *   <th>response_length</th>
 *   <td>Pointer to memory where callback writes the size of connector_network_handle_t</td>
 * </tr>
 * <tr>
 *   <th colspan="2" class="title">Return Values</th>
 * </tr>
 * <tr>
 *   <th class="subtitle">Values</th> <th class="subtitle">Description</th>
 * </tr>
 * <tr>
 *   <td>@endhtmlonly @ref connector_callback_continue @htmlonly</td>
 *   <td>Callback successfully established a connection</td>
 * </tr>
 * <tr>
 *   <td>@endhtmlonly @ref connector_callback_busy @htmlonly</td>
 *   <td>Callback is busy connecting and needs to be called back again</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_error @htmlonly</td>
 * <td>Callback was unable to connect to the server; Etherios Cloud Connector will exit @endhtmlonly @ref connector_run "connector_run()"@htmlonly. 
 *     The callback will be retried when @endhtmlonly @ref connector_run "connector_run()" @htmlonly is called again,
 *     if the transport is configured to start automatically</td>
 * </tr>
 * <tr>
 *   <td>@endhtmlonly @ref connector_callback_abort @htmlonly</td>
 *   <td>Callback was unable to connect to the server and callback aborted Etherios Cloud Connector</td>
 * </tr>
 * </table>
 * @endhtmlonly
 *
 * Example:
 *
 * @code
 * 
 * #include "connector_api.h"
 * #include "platform.h"
 *
 * typedef struct
 * {
 *    int sfd;
 *    SSL_CTX * ctx;
 *    SSL * ssl;
 * } app_ssl_t;
 *
 * connector_callback_status_t app_connector_callback(connector_class_id_t const class_id, connector_request_id_t const request_id
 *                              void * const request_data, size_t const request_length,
 *                              void * response_data, size_t * const response_length)
 * {
 *
 *     // resolve address
 *     // create socket fd, set socket option for keep alive and no delay
 *     // connect to CONNECTOR_SSL_PORT on Etherios Device Cloud
 *
 *    SSL_library_init();
 *    OpenSSL_add_all_algorithms();
 *    SSL_load_error_strings();
 *    ssl_ptr->sfd = fd;
 *    ssl_ptr->ctx = SSL_CTX_new(TLSv1_client_method());    
 *    if (ssl_ptr->ctx == NULL)
 *    {
 *        ERR_print_errors_fp(stderr);
 *        goto error;
 *    } 
 *
 *    ssl_ptr->ssl = SSL_new(ssl_ptr->ctx);
 *    if (ssl_ptr->ssl == NULL)
 *    {
 *        ERR_print_errors_fp(stderr);
 *        goto error;
 *    }
 *
 *    SSL_set_fd(ssl_ptr->ssl, ssl_ptr->sfd);
 *
 *    ret = SSL_CTX_load_verify_locations(ctx, APP_SSL_CA_CERT, NULL);
 *    if (ret != 1) 
 *    {
 *        APP_DEBUG("Failed to load CA cert [%d]\n", ret);
 *        ERR_print_errors_fp(stderr);
 *        goto error;
 *    }
 *    
 *    SSL_set_options(ssl_ptr->ssl, SSL_OP_ALL);
 *    if (SSL_connect(ssl_ptr->ssl) <= 0)
 *    {
 *        ERR_print_errors_fp(stderr);
 *        goto error;
 *    }
 *
 *    {
 *        X509 * const server_cert = SSL_get_peer_certificate(ssl);
 *
 *        if (server_cert == NULL)
 *        {
 *            APP_DEBUG("No server certificate is provided\n");
 *            goto done;
 *        }
 *
 *        ret = SSL_get_verify_result(ssl);
 *        if (ret !=  X509_V_OK)
 *        {
 *            APP_DEBUG("Server certificate is invalid [%d]\n", ret);
 *           goto done;
 *        }
 *    }
 *
 * }
 *
 * @endcode
 *
 * @section ssl_send Send
 *
 * Callback is called to send data to Etherios Device Cloud over SSL connection. This function must not block. 
 * If it encounters EAGAIN or EWOULDBLOCK error it must return @ref connector_callback_busy and Etherios Cloud Connector will 
 * continue calling this function.
 *
 * This callback is trapped in application.c, in the @b Sample section of @ref AppStructure "Public Application Framework"
 * and implemented in the @b Platform function @ref app_network_tcp_send() in network_tcp.c.
 *
 * @htmlonly
 * <table class="apitable">
 * <tr> <th colspan="2" class="title">Arguments</th> </tr> 
 * <tr><th class="subtitle">Name</th> <th class="subtitle">Description</th></tr>
 * <tr>
 * <th>class_id</th>
 * <td>@endhtmlonly @ref connector_class_network_tcp @htmlonly</td>
 * </tr>
 * <tr>
 * <th>request_id</th>
 * <td>@endhtmlonly @ref connector_network_send @htmlonly</td>
 * </tr>
 * <tr>
 * <th>request_data</th>
 * <td>Pointer to @endhtmlonly connector_write_request_t @htmlonly</td>
 * </tr>
 * <tr>
 * <th>request_length</th>
 * <td> Size of @endhtmlonly connector_write_request_t. @htmlonly</td>
 * </tr>
 * <tr>
 * <th>response_data</th>
 * <td> Pointer to size_t type memory where callback writes number of bytes sent to Etherios Device Cloud. </td>
 * </tr>
 * <tr>
 * <th>response_length</th>
 * <td>N/A</td>
 * </tr>
 * <tr> <th colspan="2" class="title">Return Values</th> </tr> 
 * <tr><th class="subtitle">Values</th> <th class="subtitle">Description</th></tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_continue @htmlonly</td>
 * <td>Callback successfully sent some data to server</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_busy @htmlonly</td>
 * <td>Callback is busy and needs to be called again to send data</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_error @htmlonly</td>
 * <td>Callback was unable to send data due to irrecoverable communications error. 
 *     Etherios Cloud Connector will @endhtmlonly @ref close "close" @htmlonly the network handle</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_abort @htmlonly</td>
 * <td>Callback aborts Etherios Cloud Connector</td>
 * </tr>
 * </table>
 * @endhtmlonly
 *
 * Example:
 *
 * @code
 *
 * connector_callback_status_t app_connector_callback(connector_class_id_t const class_id, connector_request_id_t const request_id
 *                              void * const request_data, size_t const request_length,
 *                              void * response_data, size_t * const response_length)
 * {
 *     connector_callback_status_t status = connector_callback_continue;
 *     app_ssl_t * const ssl_ptr = (app_ssl_t *)write_data->network_handle;
 *     int const bytes_sent = SSL_write(ssl_ptr->ssl, write_data->buffer, write_data->length);
 *
 *     if (bytes_sent <= 0)
 *     {
 *         // call SSL_get_error() to find out exact cause
 *         APP_DEBUG("SSL_write failed %d\n", bytes_sent);
 *         status = connector_callback_error;
 *     }
 *
 *     *sent_length = bytes_sent;
 *     return status;
 * }
 * @endcode
 *
 * @section ssl_receive Receive
 *
 * Callback is called to receive a specified number of bytes of data from the iDigi Device
 * Cloud.  This function must not block.
 *
 * This callback is trapped in application.c, in the @b Sample section of @ref AppStructure "Public Application Framework"
 * and implemented in the @b Platform function @ref app_network_tcp_receive() in network_tcp_ssl.c.
 *
 * @note In the multithreaded model (connector_run()) this is the point where the ICC
 * will relinquish control of the CPU.
 *
 * @htmlonly
 * <table class="apitable">
 * <tr> <th colspan="2" class="title">Arguments</th> </tr> 
 * <tr><th class="subtitle">Name</th> <th class="subtitle">Description</th></tr>
 * <tr>
 * <th>class_id</th>
 * <td>@endhtmlonly @ref connector_class_network_tcp @htmlonly</td>
 * </tr>
 * <tr>
 * <th>request_id</th>
 * <td>@endhtmlonly @ref connector_network_receive @htmlonly</td>
 * </tr>
 * <tr>
 * <th>request_data</th>
 * <td>Pointer to @endhtmlonly connector_read_request_t @htmlonly</td>
 * </tr>
 * <tr>
 * <th>request_length</th>
 * <td> Size of @endhtmlonly connector_read_request_t. @htmlonly</td>
 * </tr>
 * <tr>
 * <th>response_data</th>
 * <td> Pointer to size_t type memory where callback writes number of bytes received from Etherios Device Cloud. </td>
 * </tr>
 * <tr>
 * <th>response_length</th>
 * <td>N/A</td>
 * </tr>
 * <tr> <th colspan="2" class="title">Return Values</th> </tr> 
 * <tr><th class="subtitle">Values</th> <th class="subtitle">Description</th></tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_continue @htmlonly</td>
 * <td>Callback successfully received some data</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_busy @htmlonly</td>
 * <td>Callback is busy and needs to be called again to receive data</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_error @htmlonly</td>
 * <td> Callback was unable to receive data due to irrecoverable communications error. 
 *     Etherios Cloud Connector will @endhtmlonly @ref close "close" @htmlonly the network handle</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_abort @htmlonly</td>
 * <td>Callback aborts Etherios Cloud Connector</td>
 * </tr>
 * </table>
 * @endhtmlonly
 *
 * Example:
 *
 * @code
 *
 * connector_callback_status_t app_connector_callback(connector_class_id_t const class_id, connector_request_id_t const request_id
 *                              void * const request_data, size_t const request_length,
 *                              void * response_data, size_t * const response_length)
 * {
 *     connector_callback_status_t status = connector_callback_continue;
 *     app_ssl_t * const ssl_ptr = (app_ssl_t *)read_data->network_handle;
 *     int bytes_read = 0;
 *
 *     *read_length = 0;
 *     if (SSL_pending(ssl_ptr->ssl) == 0)
 *     {
 *         int ready;
 *         struct timeval timeout;
 *         fd_set read_set;
 *
 *         timeout.tv_sec = read_data->timeout;
 *         timeout.tv_usec = 0;
 *
 *         FD_ZERO(&read_set);
 *         FD_SET(ssl_ptr->sfd, &read_set);
 *
 *         // Blocking point for Etherios Cloud Connector
 *         ready = select(ssl_ptr->sfd + 1, &read_set, NULL, NULL, &timeout);
 *         if (ready == 0)
 *         {
 *             status = connector_callback_busy;
 *             goto done;
 *         }
 *
 *         if (ready < 0)
 *         {
 *            APP_DEBUG("app_network_receive: select failed\n");
 *            goto done;
 *         }
 *     }
 *
 *     bytes_read = SSL_read(ssl_ptr->ssl, read_data->buffer, )read_data->length);
 *     if (bytes_read <= 0)
 *     {
 *         // EOF on input: the connection was closed.
 *         APP_DEBUG("SSL_read failed %d\n", bytes_read);
 *         status = connector_callback_error;
 *     }
 *
 *     *read_length = (size_t)bytes_read;
 *
 * done:
 *     return status;
 * }
 *
 * @endcode
 *
 * @section ssl_close Close
 *
 * Callback is called to close a connection between a device and Etherios Device Cloud. This API
 * should release all the SSL based allocation.
 *
 * This callback is trapped in application.c, in the @b Sample section of @ref AppStructure "Public Application Framework"
 * and implemented in the @b Platform function @ref app_network_tcp_close() in network_tcp_ssl.c.
 *
 * @htmlonly
 * <table class="apitable">
 * <tr> <th colspan="2" class="title">Arguments</th> </tr> 
 * <tr><th class="subtitle">Name</th> <th class="subtitle">Description</th></tr>
 * <tr>
 * <th>class_id</th>
 * <td>@endhtmlonly @ref connector_class_network_tcp @htmlonly</td>
 * </tr>
 * <tr>
 * <th>request_id</th>
 * <td>@endhtmlonly @ref connector_network_close @htmlonly</td>
 * </tr>
 * <tr>
 * <th>request_data</th>
 * <td>Pointer to @endhtmlonly connector_close_request_t,@htmlonly in which @endhtmlonly @ref connector_close_status_t "status" @htmlonly 
 *     field provides reason for close</td>
 * </tr>
 * <tr>
 * <th>request_length</th>
 * <td> Size of @endhtmlonly connector_close_request_t @htmlonly</td>
 * </tr>
 * <tr>
 * <th>response_data</th>
 * <td>Pointer to @endhtmlonly @ref connector_auto_connect_type_t "connector_auto_connect_type_t"@htmlonly memory where callback 
 *     writes action on transport close.</td>
 * </tr>
 * <tr>
 * <th>response_length</th>
 * <td> Size of @endhtmlonly @ref connector_auto_connect_type_t "connector_auto_connect_type_t"@htmlonly</td>
 * </tr>
 * <tr> <th colspan="2" class="title">Return Values</th> </tr> 
 * <tr><th class="subtitle">Values</th> <th class="subtitle">Description</th></tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_continue @htmlonly</td>
 * <td>Callback successfully closed the connection</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_busy @htmlonly</td>
 * <td>Callback is busy completing the network close and will be called again</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref connector_callback_abort @htmlonly</td>
 * <td>Callback was unable to close the connection and callback aborted ICC</td>
 * </tr>
 * </table>
 * @endhtmlonly
 *
 * Example:
 *
 * @code
 *
 * connector_callback_status_t app_connector_callback(connector_class_id_t const class_id, connector_request_id_t const request_id
 *                              void * const request_data, size_t const request_length,
 *                              void * response_data, size_t * const response_length)
 * {
 *
 *     connector_callback_status_t status = connector_callback_continue;
 *     app_ssl_t * const ssl_ptr = (app_ssl_t *)handle;
 *     connector_auto_connect_type_t * const is_to_reconnect = (connector_auto_connect_type_t *) response_data;
 *
 *     // send close notify to peer
 *     if (SSL_shutdown(ssl_ptr->ssl) == 0) 
 *         SSL_shutdown(ssl_ptr->ssl);  // wait for peer's close notify
 *
 *     if (ssl_ptr->ssl != NULL) 
 *     {
 *         SSL_free(ssl_ptr->ssl);
 *         ssl_ptr->ssl = NULL;
 *     }
 *
 *     if (ssl_ptr->ctx != NULL) 
 *     {
 *         SSL_CTX_free(ssl_ptr->ctx);
 *         ssl_ptr->ctx = NULL;
 *     }
 *
 *     if (ssl_ptr->sfd != -1) 
 *     {
 *         close(ssl_ptr->sfd);
 *         ssl_ptr->sfd = -1;
 *     }
 *     *is_to_reconnect = connector_auto_connect;
 *     return status;
 * }
 *
 * @endcode
 *
 * @htmlinclude terminate.html
 */
