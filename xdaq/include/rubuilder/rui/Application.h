#ifndef _rubuilder_rui_Application_h_
#define _rubuilder_rui_Application_h_

#include "rubuilder/rui/SuperFragmentGenerator.h"
#include "rubuilder/rui/SynchronizedString.h"
#include "rubuilder/rui/exception/Exception.h"
#include "rubuilder/utils/WebUtils.h"
#include "i2o/i2oDdmLib.h"
#include "i2o/utils/AddressMap.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/mem/MemoryPoolFactory.h"
#include "toolbox/task/Action.h"
#include "toolbox/task/WorkLoop.h"
#include "toolbox/task/WorkLoopFactory.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/WebApplication.h"
#include "xdaq2rc/SOAPParameterExtractor.hh"
#include "xdata/Boolean.h"
#include "xdata/Double.h"
#include "xdata/InfoSpace.h"
#include "xdata/Integer32.h"
#include "xdata/String.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/Vector.h"


namespace rubuilder { namespace rui { // namespace rubuilder::rui

/**
 * Example Readout Unit Interface (RUI) to be copied and modified by end-users.
 */
class Application :
public xdaq::WebApplication
{
public:

    /**
     * Define factory method for the instantion of RUI applications.
     */
    XDAQ_INSTANTIATOR();

    /**
     * Constructor.
     */
    Application(xdaq::ApplicationStub *s)
    throw (xdaq::exception::Exception);


private:

    /**
     * When the RUI is enabled, at any moment in time it is either trying to
     * build a super-fragment, or trying to send one.
     */
    enum SuperFragActivity {BUILDING, SENDING};

    /**
     * When the RUI is enabled, at any moment in time it is either trying to
     * build a super-fragment, or trying to send one.
     */
    SuperFragActivity superFragActivity_;

    /**
     * Pointer to the descriptor of the RUBuilderTester application.
     *
     * It is normal for this pointer to be 0 if the RUBuilderTester application      * cannot be found.
     */
    xdaq::ApplicationDescriptor *rubuilderTesterDescriptor_;

    /**
     * Generator of dummy super-fragments.
     */
    rubuilder::rui::SuperFragmentGenerator superFragGenerator_;

    /**
     * I2o exception handler.
     */
    toolbox::exception::HandlerSignature *i2oExceptionHandler_;

    /**
     * The logger of this application.
     */
    Logger logger_;

    /**
     * Binary semaphore used to protect the internal data structures of the
     * application from multithreaded access.
     */
    toolbox::BSem applicationBSem_;

    /**
     * Used to display on the application web-pages the reason why the finite
     * state machine moved to the failed state if it did.
     */
    SynchronizedString reasonForFailed_;

    /**
     * Binary semaphore used to protect the credits counter.
     */
    toolbox::BSem nbCreditsBSem_;

    /**
     * The name of the info space that contains exported parameters used for
     * monitoring.
     */
    std::string monitoringInfoSpaceName_;

    /**
     * Info space that contains exported parameters used for monitoring.
     */
    xdata::InfoSpace *monitoringInfoSpace_;

    /**
     * The finite state machine of the application.
     */
    toolbox::fsm::FiniteStateMachine fsm_;

    /**
     * USed to access the work loop factory without a function call.
     */
    toolbox::task::WorkLoopFactory *workLoopFactory_;

    /**
     * Helper class to extract FSM command and parameters from SOAP command
     */
    xdaq2rc::SOAPParameterExtractor soapParameterExtractor_;

    /**
     * Used to access the I2O address map without a function call.
     */
    i2o::utils::AddressMap *i2oAddressMap_;

    /**
     * Used to access the memory pool factory without a function call.
     */
    toolbox::mem::MemoryPoolFactory *poolFactory_;

    /**
     * Used to access the application's info space without a function call.
     */
    xdata::InfoSpace *appInfoSpace_;

    /**
     * Used to access the application's descriptor without a function call.
     */
    xdaq::ApplicationDescriptor *appDescriptor_;

    /**
     * Used to access the application's context without a function call.
     */
    xdaq::ApplicationContext *appContext_;

    /**
     * The XML class name of the application.
     */
    std::string xmlClass_;

    /**
     * The instance number of the application.
     */
    unsigned int instance_;

    /**
     * The application's URN.
     */
    std::string urn_;

    /**
     * The I2O tid of the application.
     */
    I2O_TID tid_;

    /**
     * The descriptor of the application to which the RUI pushes super-fragment
     * data.
     */
    xdaq::ApplicationDescriptor *destinationDescriptor_;

    /**
     * The I2O tid of the application to which the RUI pushes super-fragment
     * data.
     */
    I2O_TID destinationTid_;

    /**
     * The action signature of the loop that generates dummy super-fragments.
     */
    toolbox::task::ActionSignature *workLoopActionSignature_;

    /**
     * The work loop that executes the loop that generates dummy
     * super-fragments.
     */
    toolbox::task::WorkLoop *workLoop_;

    /**
     * True if the work loop that executes the loop that generates dummy
     * super-fragments has been started, else false.
     */
    bool workLoopStarted_;

    /**
     * Memory pool used between the RUI and the application to which it sends
     * super-fragment data.
     */
    toolbox::mem::Pool *dataPool_;

    /**
     * The application's standard configuration parameters.
     */
    std::vector< std::pair<std::string, xdata::Serializable *> >
        stdConfigParams_;

    /**
     * The application's debug (private to developer) configuration parameters.
     */
    std::vector< std::pair<std::string, xdata::Serializable *> >
        dbgConfigParams_;

    /**
     * The application's monitor counters.
     */
    std::vector< std::pair<std::string, xdata::UnsignedInteger32 *> >
        monitorCounters_;

    /**
     * The application's standard monitoring parameters.
     */
    std::vector< std::pair<std::string, xdata::Serializable *> >
        stdMonitorParams_;

    /**
     * The application's debug (private to developer) monitoring parameters.
     */
    std::vector< std::pair<std::string, xdata::Serializable *> >
        dbgMonitorParams_;


    /////////////////////////////////////////////////////////////
    // Beginning of exported parameters used for configuration //
    /////////////////////////////////////////////////////////////

    /**
     * Exported read/write parameter specifying the class name of the
     * application to which the RUI will send event data blocks.
     *
     * An empty string is interpretted as meaning this parameter has not been
     * set.
     *
     * If this parameter is not set when the RUI is configured, then the RUI
     * will attempt to find the class name itself.
     */
    xdata::String destinationClass_;

    /**
     * Exported read/write parameter specifying the instance number of the
     * application to which the RUI will send event data blocks.
     *
     * A negative value is interpretted as meaning this parameter has not been
     * set.
     *
     * If this parameter is not set when the RUI is configured, then the RUI
     * will attempt to find the instance number itself.
     */
    xdata::Integer32 destinationInstance_;

    /**
     * Exported read/write parameter specifying the name of the work loop that
     * executes the behaviour of the RUI.
     *
     * If this string is "" when the RUI is configured, then the RUI will
     * name and create its own work loop.
     */
    xdata::String workLoopName_;

    /**
     * Exported read/write parameter specifying the size of an event data I2O
     * message frame.
     */
    xdata::UnsignedInteger32 dataBufSize_;

    /**
     * Exported read/write parameter specifiying the size of payload per FED
     * per event.
     *
     * fedPayloadSize is in bytes.
     */
    xdata::UnsignedInteger32 fedPayloadSize_;

    /**
     * Exported read/write parameter specifiying the source id of each FED
     * supplying data to a single super-fragment.
     *
     * The size of this vector specifies the number of FEDs that supply data
     * to a single super-fragment.
     */
    xdata::Vector<xdata::UnsignedInteger32> fedSourceIds_;

    /**
     * Exported read/write parameter specifying the name of the memory pool
     * between the RUI and the application to whcih it sends super-fragment
     * data
     */
    xdata::String dataPoolName_;

    /**
     * Exported read/write parameter specifying the "committed size" in bytes
     * of the event data pool between the RUI and the application to which it
     * sends super-fragment data.
     */
    xdata::UnsignedInteger32 dataPoolCommittedSize_;

    /////////////////////////////////////////////////////////////
    // End of exported parameters used for configuration       //
    /////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////
    // Beginning of exported parameters used for monitoring    //
    /////////////////////////////////////////////////////////////

    /**
     * Exported read-only parameter specifying the current state of the
     * application.
     */
    xdata::String stateName_;

    /**
     * Exported read-only parameter specifying the event number of the next
     * dummy super-fragment to be created.
     */
    xdata::UnsignedInteger32 eventNumber_;

    /**
     * Exported read-only parameter specifying the number times the RUI has
     * failed to send a data block to the destination application.
     */
    xdata::UnsignedInteger32 nbFailedSends_;

    /////////////////////////////////////////////////////////////
    // End of exported parameters used for monitoring          //
    /////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////////////
    // Beginning of exported parameters showing message payloads and counts //
    //////////////////////////////////////////////////////////////////////////

    /**
     * Exported read-only parameter specifying the payload transfered
     * by I2O_EVMRU_DATA_READY messages.
     */
    xdata::UnsignedInteger32 I2O_EVMRU_DATA_READY_Payload_;

    /**
     * Exported read-only parameter specifying the logical message
     * count for I2O_EVMRU_DATA_READY messages.
     */
    xdata::UnsignedInteger32 I2O_EVMRU_DATA_READY_LogicalCount_;

    /**
     * Exported read-only parameter specifying the i2o message frame
     * count for I2O_EVMRU_DATA_READY messages.
     */
    xdata::UnsignedInteger32 I2O_EVMRU_DATA_READY_I2oCount_;

    //////////////////////////////////////////////////////////////////////////
    // End of exported parameters showing message payloads and counts       //
    //////////////////////////////////////////////////////////////////////////


    /////////////////////////////////////////////////////////////
    // Beginning of exported parameters used for debugging     //
    /////////////////////////////////////////////////////////////

    /**
     * Exported read-only parameter specifying the number of times the RUI got
     * and out of memory exception when try to get a free block frame.
     */
    xdata::UnsignedInteger32 nbOutOfMemoryExceptions_;

    /////////////////////////////////////////////////////////////
    // End of exported parameters used for debugging           //
    /////////////////////////////////////////////////////////////


    /**
     * The blocks of the super-fragment under construction.
     */
    std::vector<toolbox::mem::Reference*> superFragBlocks_;

    /**
     * True if there are one or more super-fragment blocks waiting to be sent
     * to the RU.
     */
    bool blocksArePendingTransmission_;

    /**
     * Returns the name to be given to the logger of this application.
     */
    std::string generateLoggerName();

    /**
     * Returns a pointer to the descriptor of the RUBuilderTester application,
     * or 0 if the application cannot be found, which will be the case when
     * testing is not being performed.
     */
    xdaq::ApplicationDescriptor *getRUBuilderTester();

    /**
     * Defines the finite state machine of the application.
     */
    void defineFsm()
    throw (rubuilder::rui::exception::Exception);

    /**
     * Returns the name of the info space that contains exported parameters
     * for monitoring.
     */
    std::string generateMonitoringInfoSpaceName
    (
        const std::string  appClass,
        const unsigned int appInstance
    );

    /**
     * Initialises and returns the application's standard configuration
     * parameters.
     */
    std::vector< std::pair<std::string, xdata::Serializable*> >
    initAndGetStdConfigParams();

    /**
     * Initialises and returns the application's debug (private to developer)
     * configuration parameters.
     */
    std::vector< std::pair<std::string, xdata::Serializable*> >
    initAndGetDbgConfigParams();

    /**
     * Resets the specified counters to zero.
     */
    void resetCounters
    (
        std::vector
        <
            std::pair<std::string, xdata::UnsignedInteger32*>
        > &counters
    );

    /**
     * Adds the specified counters vector to specified general parameters
     * vector.
     */
    void addCountersToParams
    (
        std::vector
        <
            std::pair<std::string, xdata::UnsignedInteger32*>
        > &counters,
        std::vector
        <
            std::pair<std::string, xdata::Serializable*>
        > &params
    );

    /**
     * Returns the application's monitor counters.
     */
    std::vector< std::pair<std::string, xdata::UnsignedInteger32*> >
    getMonitorCounters();

    /**
     * Initialises and returns the application's standard monitoring
     * parameters.
     */
    std::vector< std::pair<std::string, xdata::Serializable*> >
    initAndGetStdMonitorParams();

    /**
     * Initialises and returns the application's debug (private to developer)
     * monitoring parameters.
     */
    std::vector< std::pair<std::string, xdata::Serializable*> >
    initAndGetDbgMonitorParams();

    /**
     * Puts the specified parameters into the specified info space.
     */
    void putParamsIntoInfoSpace
    (
        std::vector< std::pair<std::string, xdata::Serializable*> > &params,
        xdata::InfoSpace                                            *s
    )
    throw (rubuilder::rui::exception::Exception);

    /**
     * Binds the SOAP callbacks required to implement the finite state machine
     * of the application.
     */
    void bindFsmSoapCallbacks();

    /**
     * Web page used to visualise and control the finite state machine of the
     * application.
     */
    void fsmWebPage(xgi::Input *in, xgi::Output *out)
    throw (xgi::exception::Exception);

    /**
     * Processes the form sent from the finite state machine web page.
     */
    void processFsmForm(xgi::Input *in)
    throw (xgi::exception::Exception);

    /**
     * Callback responsible for processing FSM events received via
     * SOAP messages.
     */
    xoap::MessageReference processSoapFsmEvent(xoap::MessageReference msg)
    throw (xoap::exception::Exception);

    /**
     * Binds the XGI callbacks of the application.
     */
    void bindXgiCallbacks();

    /**
     * Creates the CSS file for this application.
     */
    void css
    (
        xgi::Input  *in,
        xgi::Output *out
    )
    { rubuilder::utils::css(in,out); }

    /**
     * The default web page of the application.
     */
    void defaultWebPage(xgi::Input *in, xgi::Output *out)
    throw (xgi::exception::Exception);

    /**
     * Displays the developer's web page used for debugging.
     */
    void debugWebPage
    (
        xgi::Input  *in,
        xgi::Output *out
    )
    throw (xgi::exception::Exception);

    /**
     * Prints the specified parameters as an HTML table with the specified name.
     */
    void printParamsTable
    (
        xgi::Input                                                  *in,
        xgi::Output                                                 *out,
        const std::string                                           name,
        std::vector< std::pair<std::string, xdata::Serializable*> > &params
    )
    throw (xgi::exception::Exception);

    /**
     * SOAP callback thats reset all the monitoring counters.
     */
    xoap::MessageReference resetMonitoringCountersMsg
    (
        xoap::MessageReference msg
    )
    throw (xoap::exception::Exception);

    /**
     * Callback implementing the action to be executed on the
     * Halted->Ready transition.
     */
    void configureAction(toolbox::Event::Reference e)
    throw (toolbox::fsm::exception::Exception);

    /**
     * Callback implementing the action to be executed on the
     * Ready->Enabled transition.
     */
    void enableAction(toolbox::Event::Reference e)
    throw (toolbox::fsm::exception::Exception);

    /**
     * Callback implementing the action to be executed on the
     * ANY STATE->Halted transition.
     */
    void haltAction(toolbox::Event::Reference e)
    throw (toolbox::fsm::exception::Exception);

    /**
     * Callback implementing the action to be executed on the
     * ANY STATE->Failed transition.
     */
    void failAction(toolbox::Event::Reference event)
    throw (toolbox::fsm::exception::Exception);

    /**
     * Callback invoked when the state machine of the application has changed.
     */
    void stateChanged(toolbox::fsm::FiniteStateMachine & fsm)
    throw (toolbox::fsm::exception::Exception);

    /**
     * Returns the name of the memory pool between the RUI and the application
     * to which is sends super-fragment data.
     */
    std::string createDataPoolName(const unsigned int  ruiInstance);

    /**
     * Returns a "HeapAllocator" memory pool with the specified name.
     */
    toolbox::mem::Pool *createHeapAllocatorMemoryPool
    (
        toolbox::mem::MemoryPoolFactory *poolFactory,
        const std::string               poolName
    )
    throw (rubuilder::rui::exception::Exception);

    /**
     * Returns a "CommittedHeapAllocator" memory pool with the specified
     * name and commited size.
     */
    toolbox::mem::Pool *createCommittedHeapAllocatorMemoryPool
    (
        toolbox::mem::MemoryPoolFactory *poolFactory,
        const std::string               poolName,
        const unsigned int              committedSize
    )
    throw (rubuilder::rui::exception::Exception);

    /**
     * Entry point for the work loop responsible for generating dummy
     * super-fragments.
     */
    bool workLoopAction(toolbox::task::WorkLoop *wl);

    /**
     * The behaviour of the RUI when it is enabled.
     */
    void processAndCommunicate();

    /**
     * Tries to send the next super-fragment block to the RU.
     *
     * Failure may occur if there is back pressure from the RUI to RU peer
     * transport.
     */
    void sendNextPendingBlock()
    throw (rubuilder::rui::exception::Exception);

    /**
     * Tries to add a single block to the super-fragment under construction.
     */
    void tryToAddASuperFragBlock()
    throw (rubuilder::rui::exception::Exception);

   /**
     * Fills each of the super-fragment's blocks with the total number of
     * blocks making up the super-fragment.
     */
    void setNbBlocksInSuperFragment(const unsigned int nbBlocks);

    /**
     * Returns the url of the specified application.
     */
    std::string getUrl(xdaq::ApplicationDescriptor *appDescriptor);

    /**
     * Invoked when there is an I2O exception.
     */
    bool onI2oException(xcept::Exception &exception, void *context);

    /**
     * Creates and returns the error message of an I2O exception by specifying
     * the source and destination involved.
     */
    std::string createI2oErrorMsg
    (
        xdaq::ApplicationDescriptor *source,
        xdaq::ApplicationDescriptor *destination
    );

}; // class Application

} } // namespace rubuilder::rui

#endif
