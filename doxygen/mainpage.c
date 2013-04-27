 /*! @mainpage Cloud Connector
 *
 * @htmlinclude nav.html
 *
 * @section table_of_contents Overview
 *
 *          -# @ref intro
 *          -# @ref language
 *          -# @ref requirements
 *              -# @ref CodespaceRequirements
 *              -# @ref RAMRequirements
 *              -# @ref StackRequirements
 *          -# @ref features
 *          -# @ref communicating
 *          -# @ref threading
 *          -# @ref code_organization
 *              -# @ref DirectoryStructure
 *              -# @ref AppStructure
 *              -# @ref PortingFocus
 *              -# @ref DebugTips
 *          -# @ref the_getting_started_process
 *
 * @section intro Introduction
 *
 * Cloud Connector is a software development package used to enable a device to
 * exchange information with Device Cloud.
 * Cloud Connector supports application to device data interaction (messaging),
 * application and device data storage, and remote management of devices. Devices
 * are associated with Device Cloud through the Internet or other wide
 * area network connections, which allows for communication between the device and
 * customer applications, via Device Cloud.  An important part of this communication
 * is the transfer of data from a device to Device Cloud.
 * Device Cloud is based on a cloud computing model that provides on-demand scalability so
 * you can rest assured that when you need additional computing and storage, Device Cloud will
 * scale to meet your needs.  Device Cloud is designed using a high-availability
 * architecture, with redundancy and failover characteristics in mind.
 * Using Cloud Connector, customers can now easily develop cloud connected devices and
 * applications that quickly scale from dozens to hundreds, thousands or even
 * millions of endpoints.
 *
 * @image html cloud.jpg
 *
 * @section language Language Support
 *
 * The Cloud Connector software provided is ANSI X3.159-1989 (ANSI C89) and ISO/IEC 9899:1999 (ANSI C99)
 * compliant. The sample platforms provided use standard ANSI C calls which are available in most operating systems.
 * If you are running on a Linux i486 based platform and using the GNU toolchain the Linux platform
 * and samples can be run without any major modifications.
 *
 * @note
 * Compilers that are not strictly ANSI C 89 or C99 compliant will most likely generate compilation
 * errors.  In that case, we recommend careful evaluation of each error and appropriate adjustments be
 * made within the public include area.  Cloud Connector was designed for portability.  This would
 * be the ideal place to make updates.
 *
 * @note
 * Some ANSI C89 compilers include elements of ANSI C99.  In particular, those
 * ANSI C89 compilers that also include stdint.h, which is apart of ANSI C99, will
 * result in compilation failures.  These compilation failures can be resolved
 * by defining CONNECTOR_HAVE_STDINT_HEADER in your make or build system.
 *
 * @section requirements Platform Memory Requirements
 * Cloud Connector requires both Flash and RAM.  Flash is needed to store instructions and variables.  RAM is needed for dynamic allocation
 * and program stack.
 *
 * @subsection CodespaceRequirements Code Space Estimates
 * The following Flash/Code space data was generated using Kubuntu 10.04 and gcc v4.4.3 for 32-bit i486 architecture
 * using the @ref step3 "compile_and_link" or @ref rci_sample "simple_remote_config" sample applications.
 *
 * The build was optimized for size (-Os) with @ref CONNECTOR_COMPRESSION disabled in all cases.
 * The metrics exclude any code space required for application layer calls.  This information should be treated as a typical use case.
 *
 * @htmlonly
 * <table class="apitable">
 * <tr>
 * <th class="title">Cloud Connector Service Options and Configuration Methodology</th>
 * <th class="title">Text</th>
 * <th class="title">rodata</th>
 * <th class="title">data</th>
 * <th class="title">bss</th>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref rci_sample "simple_remote_config" sample with @ref CONNECTOR_DEBUG, @ref CONNECTOR_RCI_SERVICE, @ref CONNECTOR_FILE_SYSTEM, @ref CONNECTOR_FIRMWARE_SERVICE, @ref CONNECTOR_DATA_SERVICE enabled, plus @ref CONNECTOR_FILE_SYSTEM_MAX_PATH_LENGTH and @ref CONNECTOR_RCI_MAXIMUM_CONTENT_LENGTH @htmlonly set to 256.</td>
 * <td>38305</td>
 * <td>11683</td>
 * <td>0</td>
 * <td>444</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref rci_sample "simple_remote_config" sample with @ref CONNECTOR_RCI_SERVICE, @ref CONNECTOR_FILE_SYSTEM, @ref CONNECTOR_FIRMWARE_SERVICE, @ref CONNECTOR_DATA_SERVICE enabled, plus @ref CONNECTOR_FILE_SYSTEM_MAX_PATH_LENGTH and @ref CONNECTOR_RCI_MAXIMUM_CONTENT_LENGTH @htmlonly set to 256.</td>
 * <td>32298</td>
 * <td>1236</td>
 * <td>0</td>
 * <td>440</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref rci_sample "simple_remote_config" sample with @ref CONNECTOR_DEBUG, @ref CONNECTOR_RCI_SERVICE, @ref CONNECTOR_FIRMWARE_SERVICE, @ref CONNECTOR_DATA_SERVICE enabled and @ref CONNECTOR_RCI_MAXIMUM_CONTENT_LENGTH @htmlonly set to 256.</td>
 * <td>32311</td>
 * <td>11274</td>
 * <td>0</td>
 * <td>444</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref rci_sample "simple_remote_config" sample with @ref CONNECTOR_RCI_SERVICE, @ref CONNECTOR_FIRMWARE_SERVICE, @ref CONNECTOR_DATA_SERVICE enabled and @ref CONNECTOR_RCI_MAXIMUM_CONTENT_LENGTH @htmlonly set to 256.</td>
 * <td>26513</td>
 * <td>1156</td>
 * <td>0</td>
 * <td>440</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref rci_sample "simple_remote_config" sample with @ref CONNECTOR_DEBUG, @ref CONNECTOR_RCI_SERVICE enabled and @ref CONNECTOR_RCI_MAXIMUM_CONTENT_LENGTH @htmlonly set to 256.</td>
 * <td>26946</td>
 * <td>9450</td>
 * <td>0</td>
 * <td>444</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref rci_sample "simple_remote_config" sample with @ref CONNECTOR_RCI_SERVICE enabled and @ref CONNECTOR_RCI_MAXIMUM_CONTENT_LENGTH @htmlonly set to 256.</td>
 * <td>22038</td>
 * <td>1020</td>
 * <td>0</td>
 * <td>440</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref step3 "compile_and_link" sample with @ref CONNECTOR_DEBUG, @ref CONNECTOR_FILE_SYSTEM, @ref CONNECTOR_FIRMWARE_SERVICE, @ref CONNECTOR_DATA_SERVICE enabled and @ref CONNECTOR_FILE_SYSTEM_MAX_PATH_LENGTH @htmlonly set to 256.</td>
 * <td>31366</td>
 * <td>9147</td>
 * <td>0</td>
 * <td>24</td>
 * </tr>
  * <tr>
 * <td>@endhtmlonly Uses the @ref step3 "compile_and_link" sample with @ref CONNECTOR_FILE_SYSTEM, @ref CONNECTOR_FIRMWARE_SERVICE, @ref CONNECTOR_DATA_SERVICE enabled and @ref CONNECTOR_FILE_SYSTEM_MAX_PATH_LENGTH @htmlonly set to 256.</td>
 * <td>26755</td>
 * <td>672</td>
 * <td>0</td>
 * <td>20</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref step3 "compile_and_link" sample with @ref CONNECTOR_DEBUG, @ref CONNECTOR_FIRMWARE_SERVICE, @ref CONNECTOR_DATA_SERVICE @htmlonly enabled.</td>
 * <td>25247</td>
 * <td>8702</td>
 * <td>0</td>
 * <td>24</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref step3 "compile_and_link" sample with @ref CONNECTOR_FIRMWARE_SERVICE, @ref CONNECTOR_DATA_SERVICE @htmlonly enabled.</td>
 * <td>20867</td>
 * <td>592</td>
 * <td>0</td>
 * <td>20</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref step3 "compile_and_link" sample with @ref CONNECTOR_FIRMWARE_SERVICE, @ref CONNECTOR_DATA_SERVICE enabled.  @ref connector_config_data_options used. @htmlonly </td>
 * <td>19477</td>
 * <td>592</td>
 * <td>0</td>
 * <td>20</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref step3 "compile_and_link" sample with @ref CONNECTOR_FIRMWARE_SERVICE enabled.  @ref connector_config_data_options used. @htmlonly </td>
 * <td>11795</td>
 * <td>472</td>
 * <td>0</td>
 * <td>20</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref step3 "compile_and_link" sample with @ref CONNECTOR_DATA_SERVICE enabled.  @ref connector_config_data_options used. @htmlonly </td>
 * <td>17085</td>
 * <td>460</td>
 * <td>0</td>
 * <td>20</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly Uses the @ref step3 "compile_and_link" sample with @ref CONNECTOR_DATA_SERVICE, @ref CONNECTOR_DATA_POINTS enabled.  @ref connector_config_data_options used. @htmlonly </td>
 * <td>19608</td>
 * <td>524</td>
 * <td>4</td>
 * <td>28</td>
 * </tr>
 * </table>
 * @endhtmlonly
 *
 * References to Text, rodata, data, and bss refer to program instructions, constant-read-only data, initialized global and
 * static variables, and uninitialized zero-ed data, respectively.  References to the @ref connector_config_data_options refers to
 * the code reduction defines in connector_config.h: @ref CONNECTOR_DEVICE_TYPE, @ref CONNECTOR_CLOUD_URL, @ref CONNECTOR_TX_KEEPALIVE_IN_SECONDS,
 * @ref CONNECTOR_RX_KEEPALIVE_IN_SECONDS, @ref CONNECTOR_WAIT_COUNT, @ref CONNECTOR_VENDOR_ID, @ref CONNECTOR_MSG_MAX_TRANSACTION, @ref CONNECTOR_CONNECTION_TYPE,
 * @ref CONNECTOR_WAN_LINK_SPEED_IN_BITS_PER_SECOND, @ref CONNECTOR_WAN_PHONE_NUMBER_DIALED, @ref CONNECTOR_FIRMWARE_SUPPORT, and @ref CONNECTOR_DATA_SERVICE_SUPPORT.
 *
 * @subsection RAMRequirements Dynamic RAM Usage
 * The following dynamic RAM usage measurements were taken during for the @ref fw_download_sample by monitoring the
 * high-water mark during the @ref connector_request_id_os_malloc @ref connector_callback_t "application-defined callback".
 *
 * @htmlonly
 * <table class="apitable">
 * <tr>
 * <th class="title">Description</th>
 * <th class="title">CONNECTOR_COMPRESSION enabled</th>
 * <th class="title">CONNECTOR_COMPRESSION disabled</th>
 * <th class="title">Notes</th>
 * </tr>
 * <tr>
 * <td>Cloud Connector base usage</td>
 * <td>2540</td>
 * <td>2540</td>
 * <td>Memory usage for internal state machines, infrastructure and communication buffers.</td>
 * </tr>
 * <tr>
 * <td>With @endhtmlonly @ref CONNECTOR_FIRMWARE_SERVICE @htmlonly enabled</td>
 * <td>104</td>
 * <td>104</td>
 * <td></td>
 * </tr>
 * <tr>
 * <td>With @endhtmlonly @ref CONNECTOR_DATA_SERVICE @htmlonly enabled</td>
 * <td>96</td>
 * <td>96</td>
 * <td></td>
 * </tr>
 * <tr>
 * <td>Total</td>
 * <td>6020</td>
 * <td>2856</td>
 * <td>With @endhtmlonly @ref CONNECTOR_FIRMWARE_SERVICE and @ref CONNECTOR_DATA_SERVICE @htmlonly enabled. </td>
 * </tr>
 * </table>
 * @endhtmlonly
 *
 * Two additional measurements of the @ref rci_sample "Simple RCI" and @ref file_system_sample "File System samples"
 * with @ref CONNECTOR_FIRMWARE_SERVICE disabled:
*
 * @htmlonly
 * <table class="apitable">
 * <tr>
 * <th class="title">Description</th>
 * <th class="title">CONNECTOR_COMPRESSION enabled</th>
 * <th class="title">CONNECTOR_COMPRESSION disabled</th>
 * </tr>
 * <tr>
 * <td>With @endhtmlonly @ref CONNECTOR_RCI_SERVICE and @ref CONNECTOR_DATA_SERVICE @htmlonly enabled.</td>
 * <td>9424</td>
 * <td>3408</td>
 * </tr>
 * <tr>
 * <td>With @endhtmlonly @ref CONNECTOR_FILE_SYSTEM and @ref CONNECTOR_DATA_SERVICE @htmlonly enabled.</td>
 * <td>6424</td>
 * <td>2884</td>
 * </tr>
 * </table>
 * @endhtmlonly
 *
 * @note All measurements above were taken with @ref CONNECTOR_MSG_MAX_TRANSACTION set to 1
 *
 * @subsection StackRequirements Program Stack Usage
 * The following program stack usage was observed using gcc 4.2.0 compiled for a 32-bit ARM9 TDMI architecture.
 *
 * @htmlonly
 * <table class="apitable">
 * <tr>
 * <th class="title">Build Details </th>
 * <th class="title"> Program stack size</th>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref CONNECTOR_DEBUG @htmlonly disabled</td>
 * <td>1107</td>
 * </tr>
 * <tr>
 * <td>@endhtmlonly @ref CONNECTOR_DEBUG @htmlonly enabled</td>
 * <td>1043</td>
 * </tr>
 * </table>
 * @endhtmlonly
 *
 * This includes all code from within the private Cloud Connector library, but none of the code implemented in the @ref connector_callback_t
 * "application-defined callback".  These metrics should be treated as typical.  It is recommended that the actual program stack size
 * used to call @ref connector_run() or connector_step() be these metrics plus the amount of memory typical for handling a TCP network client,
 * or a thread that accesses local configuration, or makes malloc/free OS calls, whichever is the worst case.
 *
 * @section features Cloud Connector Features
 *     @li Send data to and from a device through Device Cloud
 *     @li Update firmware on the device
 *     @li View and configure the device configurations
 *     @li Access a device's File System
 *     @li Reboot a device
 *
 * @section communicating Communicating with your device
 * To manage your device you can use the <a href="http://www.etherios.com/devicecloud/devicemanager">Device Manager</a>
 * interface by logging into your @ref step4 "Device Cloud account".  Alternatively, you can communicate with
 * your device programmatically by using @ref web_services "Device Cloud Web Services".
 *
 * @ref web_services "Device Cloud Web Services" requests are sent from a remote application to
 * Device Cloud, which then directly communicates to the device.  This
 * allows for bidirectional machine to machine communication.  Each Cloud Connector sample includes
 * a Python application demonstrating how to communicate to a device using the
 * @ref web_services "Device Cloud Web Services".
 *
 * @section threading Threading Model
 *
 * Cloud Connector can be deployed in a multithreaded (connector_run()) or round robin control loop (connector_step()) environment.
 * In environments that include preemptive threading, Cloud Connector can be implemented as a separate stand-alone thread
 * by calling connector_run().  This is a blocking call that only returns due to a major system failure.
 *
 * Alternatively, when threading is unavailable, in a round robin control loop or fixed state machine, Cloud Connector can
 * be implemented using the non-blocking connector_step() call within the round robin control loop.
 *
 * Note in a cooperative, non-preemptive multithreaded environment, either connector_run() or connector_step() can used, based on
 * system determinism and the potential for a non-cooperative thread to exceed Cloud Connector's system timing.
 *
 * @note You should decide before proceeding how you intend to call Cloud Connector (within a round robin control loop or running
 * as a separate thread).  In a limited services OS with no real time threading, you should use the connector_step() routine.
 * Otherwise you should use the connector_run() routine.
 *
 * @section code_organization Source Code Organization
 * The Cloud Connector source code is divided into two partitions, a private partition and a public Application Framework.  The private partition
 * includes the sources that implement the @ref api_overview "Cloud Connector public API".  The public Application Framework includes a
 * set of sample applications used for demonstration purposes.
 *
 * @note For forward compatibility the private partition should be treated as a black box and never changed or referenced directly.  It's recommended
 * after completing the @ref getting_started process that this private partition be converted into a library.   Note the term
 * "Cloud Connector library" is used synonymously for the "Cloud Connector private partition".
 *
 * @subsection DirectoryStructure Directory Structure
 *
 * When uncompressed the directory structure below will be created/.
 * The public directory is divided into a step and run branch to easily distinguish the different thread modeling
 * requirements.
 *
 *
 * @htmlonly
 * <table class="apitable">
 * <tr>
 *   <th class="title">Directory</th>
 *   <th class="title">Description</th>
 * </tr>
 * <tr>
 *   <td>private</td>
 *   <td>Cloud Connector Library Code<br></br>
 *   This directory contains all the private and internal files used to build Cloud Connector library.
 *   <b>You should never modify, directly call, debug, or reference any file from this directory</b>.</td>
 * </tr>
 * <tr>
 *   <td>public/include</td>
 *   <td> @endhtmlonly  @ref api_overview "Cloud Connector Public API" @htmlonly <br></br>
 *   Contains the twelve public headers:
 *      <ol><li>@endhtmlonly  @ref connector_api.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_api_config.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_api_data_point.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_api_data_service.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_api_file_system.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_api_firmware.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_api_network.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_api_os.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_api_remote.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_api_short_message.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_debug.h @htmlonly</li>
 *          <li>@endhtmlonly  @ref connector_types.h @htmlonly</li></ol>

 *
 *   <p>The @endhtmlonly @ref api_overview "Cloud Connector public API" @htmlonly is located in @endhtmlonly @ref connector_api.h @htmlonly and
 *   required for application development.  All the machine device types are located in @endhtmlonly @ref connector_types.h @htmlonly and
 *   might require updating to match your platform's characteristics (i.e., data size and supported compiler data types).
 *
 *   Public header @endhtmlonly @ref connector_debug.h @htmlonly contains the prototype for @endhtmlonly @ref connector_debug_printf() @htmlonly which is a required
 *   porting implementation function when @endhtmlonly @ref CONNECTOR_DEBUG @htmlonly is defined.  Also contains appropriate definitions for the macro ASSERT(),
 *   which is used within the private folder.</p>
 *
 *   <br></br>
 *   Note the header file @endhtmlonly @ref connector_config.h @htmlonly has now been moved into the samples directories. </td>
 * </tr>
 * <tr>
 *   <td>public/run</td>
 *   <td>Platforms and samples for running Cloud Connector as a separate thread <br></br>
 *   This directory contains platforms and samples that use @endhtmlonly connector_run() @htmlonly which runs
 *   Cloud Connector as a separate thread in a multitasking environment.</td>
 * </tr>
 * <tr>
 *   <td>public/run/platforms</td>
 *   <td>Platform files for running Cloud Connector as a separate thread<br></br>
 *   Platform dependent files that interface between Cloud Connector library (private) and the sample applications.
 *   These files include @endhtmlonly @ref network_tcp.c, file_system.c, @ref os.c, @ref config.c, and main.c. @htmlonly
 *   The Getting Started Procedure walks you through the process of porting and setting these platform files.</td>
 * </tr>
 * <tr>
 *   <td>public/run/samples</td>
 *   <td>Samples for Cloud Connector<br></br>
 *   Samples on how to use Cloud Connector, the compile_and_link sample is used to verify
 *   that your new environment is able to build. There is a sample for each major
 *   feature in Cloud Connector, there is documentation in this guide for each sample.</td>
 * </tr>
 * <tr>
 *   <td>public/step</td>
 *   <td>This directory contains platforms and samples that use @endhtmlonly connector_step() @htmlonly which makes
 *   repeated calls within a round robin control loop.</td>
 * </tr>
 * </table>
 * @endhtmlonly
 *
 * @subsection AppStructure Source Code Hierarchy
 * Cloud Connector is split into two separate partitions, a private partition and a public Application Framework.
 *
 * The private partition (Cloud Connector Library) includes source code that implements the @ref api_overview "Cloud Connector public API", plus all the internal code used to implement the
 * Device Cloud protocol.  For forward compatibility this private partition should be treated as a black box and never changed or referenced directly.
 *
 * The public Application Framework partition is further divided in two: a Platform and Sample section.  The Platform section is related to system
 * specific porting dependencies (i.e., fleshing out @ref os_callbacks "operating system" calls, @ref network_callbacks "networking", @ref config_callbacks "system configuration").  The Sample section contains an application
 * structure to cleanly interface between the Platform section and Cloud Connector private partition.
 *
 * For instance, in a linux run thread model, the main() routine starts two threads: connector_run_thread() and application_run_thread() in main.c.  This file is
 * located in the Platform section since it relies on threads (an operating system dependency).  The connector_run_thread() directly calls the @ref api_overview "Cloud Connector API"
 * connector_run(), and the application_run_thread() calls application_run().  The application_run() function has no system dependencies and contains
 * Cloud Connector specific functions, therefore, it resides within the Sample section.
 *
 * In the diagram below, Cloud Connector Library is shown encapsulated within the dotted line on top (in the Private Source Code Area).  The
 * bottom is the Platform section, where the bottom left side shows main() calling connector_init() and spawning the two threads.   Also
 * shown is the application_run_thread() calling application_run() in the Sample section.  The Sample section is encapsulated within the
 * dotted line on the center-right.
 *
 * @image html SWOverview.jpg
 *
 * Based on the particular sample, application_run() could either make calls to connector_initiate_action(), or could just return and complete.
 *
 * The diagram further shows Cloud Connector Library making callbacks into the Sample section.  The @ref connector_callback_t "application callback function", initially passed
 * to Cloud Connector library via the connector_init() call, will pass the callback request to the appropriate handler, which will either be in the Platform section for
 * @ref os_callbacks "operating system", @ref network_callbacks "networking", or @ref config_callbacks "configuration" callbacks; or remain locally
 * handled (in the Sample section) for the Data Service callbacks.
 *
 * @subsection PortingFocus Porting Guidelines
 * The Cloud Connector @ref getting_started process includes pulling Cloud Connector into your local build environment, getting the private partition
 * compiled and linked (using the @ref step3 "compile_and_link" sample) and then your @ref step5 "platform ported".  Once your platform
 * is ported, you will verify and confirm your port using the @ref step7 "connect_to_device_cloud" sample.
 *
 * When porting, it is strongly recommended that you maintain the structure of the public Application Framework.  Once porting, compilation and testing
 * are complete, the you can dismantle this framework and incorporate Cloud Connector into your environment as you see fit.
 *
 * When reusing the Application Framework, the largest effort will be updating the lowest layer of the Platform code.  Specifically, the
 * static @ref os_routines "operating system" functions located in os.c, the @ref network_routines "networking" functions in network_tcp.c and
 * the @ref configuration_routines "configuration" functions in config.c.
 *
 * There is no expectation that you will need to port any other code, with the exception of the @ref step1 "changes" required to get your code compiled.
 *
 * For example, the Application Framework includes code to handle an @ref connector_request_id_os_system_up_time callback in os.c.  The function requires a
 * stable system timer at one second resolution.  In the linux platform example, the function is implemented using the POSIX standard
 * time() function:
 *
 * @code
 * connector_callback_status_t app_os_get_system_time(unsigned long * const uptime)
 * {
 *    time((time_t *)uptime);
 *
 *    return connector_callback_continue;
 * }
 * @endcode
 *
 * However, a platform that does not support POSIX time() might port this function as such:
 *
 * @code
 * connector_callback_status_t app_os_get_system_time(unsigned long * const uptime)
 * {
 *    // Note mysys_GetTickTime() returns the system up time in milliseconds
 *    extern unsigned long mysys_GetTickTime(void);
 *
 *    *uptime = mysys_GetTickTime()/1000;
 *
 *    return connector_callback_continue;
 * }
 * @endcode
 *
 * After converting all the static @ref os_routines "operating system", @ref network_routines "networking", and @ref configuration_routines "configuration"
 * functions, your porting effort is complete.
 *
 * @subsection DebugTips How to debug your Port
 * After porting and compiling, you will run the @ref step7 "connect_to_device_cloud" sample.  We recommend that you carefully
 * observe the standard output from the application.  In particular, the @ref error_status callback will display error
 * data when porting errors are detected in the callbacks.
 *
 * Examples of @ref good_results_output "successful" and @ref bad_results_output "erroneous" output streams are available.
 *
 * @section the_getting_started_process Getting Started
 * To get started, follow along the steps of the @ref getting_started process.
 *
 * @htmlinclude terminate.html
 */

