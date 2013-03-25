/*! @page api_overview Public API Overview
 *
 * @htmlinclude nav.html
 *
 * @section api1_overview Public API Overview
 *
 * The iDigi connector API includes two major software interfaces:
 *      @li iDigi connector function calls
 *      @li iDigi connector application-defined callback
 *
 *  The functions available in the iDigi connector are listed below:
 *
 * @htmlonly
 * <table class="apitable">
 * <tr>
 * <th class="title">Routine</th>
 * <th class="title">Description</th>
 * </tr>
 * <tr>
 * <td>@endhtmlonly connector_init() @htmlonly</td>
 * <td>Start the iDigi connector</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly connector_step() @htmlonly</td>
 * <td>Execute the iDigi connector and return</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly connector_run() @htmlonly</td>
 * <td>Start the iDigi connector and do not return</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly connector_initiate_action() @htmlonly</td>
 * <td>Initiate an iDigi connector operation, like starting a data transfer</td>
 * </tr>
 * </table>
 * @endhtmlonly
 *
 *
 * @subsection initialization Initialization: connector_init()
 *
 * The function connector_init() is called once at startup to  initialize the iDigi connector.
 * The application-defined callback function is passed as an argument; the @ref connector_callback_t
 * "application-defined callback" is used by the iDigi connector to communicate with the application.
 * The connector_init() function must be called before all other iDigi connector APIs.
 *
 * @subsection single_threaded Single-threaded model: connector_step()
 *
 * The function connector_step() is called to perform a sequence of operations or events
 * and then returns control back to the caller.  This allows a caller to perform other tasks
 * within a single thread or round robin based control loop.  A caller must call
 * this API repeatedly to continue iDigi connector operations.
 *
 * The connector_step() performs the following operations:
 *  -# Establish and maintain a connection with the iDigi Device Cloud.
 *  -# Wait for incoming messages from the iDigi Device Cloud.
 *  -# Send outstanding messages to the iDigi Device Cloud.
 *
 * @subsection multi_threaded Multi-threaded model: connector_run()
 *
 * The function connector_run() is similar to connector_step() except it blocks and doesn't return control back to
 * caller unless the iDigi connector encounters an error. This function is typically executed as a separate thread.
 * This is the recommended method of running the iDigi connector within in a multithreaded
 * environment.
 *
 * @note To relinquish control of the CPU in a multithreaded environment the iDigi connector
 * calls the yield (@ref yield) callback.
 *
 * @subsection initiate_action Initiate an action: connector_initiate_action()
 *
 * The function connector_initiate_action() is used to indicate to the iDigi connector to perform a
 * device-requested action.  The currently supported actions are:
 *
 *  @li Initiate a data transfer to the server, described in the data service API
 *  @li Terminate the iDigi connector
 *  @li Start transport (TCP, UDP or SMS)
 *  @li Stop transport (TCP, UDP, SMS or ALL) transport method
 *  @li Request iDigi Device Cloud status status (Ping)
 *  @li Send dia message to the iDigi Device Cloud
 *  @li Send device to cloud config message
 *
 * @subsection iik_callback Application Callback
 *
 * The iDigi connector uses a single application-defined @ref connector_callback_t "callback" function to process network events,
 * handle operating system (OS) calls, return device configuration data, and process firmware updates.
 * The callback is also used to report error status and event notification.  The application-defined
 * @ref connector_callback_t "callback" is passed into connector_init() upon startup.  When the iDigi connector needs to allocate
 * memory, access the network or perform other actions the application defined callback
 * is called.
 *
 * The iDigi connector will invoke the application-defined callback to perform the following actions:
 *   @li Obtain configuration information
 *   @li OS calls
 *   @li Networking calls
 *   @li Firmware download
 *   @li Handle a device request
 *   @li Request more data when sending data to the iDigi Device Cloud
 *   @li Access file system
 *   @li Access device configurations
 *   @li Short message calls
 *   @li Status calls
 *
 * @b Class @b ID and @b Request @b ID
 * enumeration values are used to identify the callback action. The application must perform and return
 * the appropriate action and return data, according to the class and request
 * enumeration values.
 *
 * Each callback is passed in a Class ID which is defined by the enumerated type
 * @ref connector_class_t.  For each Class ID there is a set of Request ID's, for example the
 * @ref connector_class_operating_system the corresponding Request ID's are defined
 * by the enum @ref connector_os_request_t.
 *
 * The parameters for the application-defined callback: request_data, request_length,
 * response_data and response_length are defined by the corresponding class_id and
 * the request_id. There is a section in the documentation for each class of callbacks.
 * For example, the Operating System callbacks are described on the @ref os_callbacks
 * "Operating System" page.
 *
 *
 * @htmlinclude terminate.html
 *
 */
