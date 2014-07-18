#ifndef __FBO_h__
#define __FBO_h__

#include <fstream>
#include <sstream>
#include <math.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <sched.h>
#include <iomanip>
#include <ios>
#include <fstream>
#include <netinet/in.h>  // for ntohl() and friends

#include "xdaq/WebApplication.h"
#include "xdaq/Application.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/NamespaceURI.h"

// i2o definitions
#include "i2o/i2o.h"
#include "i2o/Method.h"
#include "i2o/utils/AddressMap.h"

// toolbox definitions
#include "toolbox/mem/Reference.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/mem/MemoryPoolFactory.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/task/Action.h"
#include "toolbox/task/WorkLoop.h"
#include "toolbox/task/WorkLoopFactory.h"
#include "toolbox/math/random.h"
#include "toolbox/rlist.h"
//#include "toolbox/task/TimerFactory.h"

// xdata definitions
#include "xdata/UnsignedInteger32.h"
#include "xdata/Double.h"
#include "xdata/Boolean.h"
#include "xdata/ActionListener.h"
#include "xdata/Vector.h"
#include "xdata/String.h"
#include "xdata/InfoSpace.h"
#include "xdata/Float.h"

// xoap definitions
#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"

// hyperdaq stuff
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"

// includes from the Myrinet FB library
#include "myrfb.h"
#include "myrfb_api.h"

#include "pheaps/Buffer.h"
// includes from the common interface directory
#include "interface/shared/i2oXFunctionCodes.h"
#include "interface/evb/i2oEVBMsgs.h"
#include "interface/shared/frl_header.h"

#include "fedbuilder/MyrinetConfigurator.hh"
#include "fedbuilder/FEDBuilderConfigASCIIReader.hh"
#include "fedbuilder/WebPageMaker.hh"
#include "fedbuilder/DataChecker.hh"
#include "fedbuilder/LendBuffer.hh"
#include "fedbuilder/MemoryManager.hh"
#include "fedbuilder/SOAPFSMHelper.hh"

// include for RUNControlState Notifier
#include "xdaq2rc/RcmsStateNotifier.h"

#define FBO_MAX_BLOCKS_PER_FRAGMENT 65536
#define MYRINETFB_MAX_ALLOWED_BLOCKS   ( 16*1024-1 )
#define FBO_MAX_DUMP_REQUESTS 256
#define PHEAPS_DEFAULT_FBO_POOLNAME "FBOPool"

namespace fedbuilder {

    class FBO : public xdaq::WebApplication
    {        
    public:	

        XDAQ_INSTANTIATOR();

        /**
         * Constructor: export Parameters to xdaq for set and get.
         */
        FBO(xdaq::ApplicationStub * s)
            throw (xdaq::exception::Exception);

        /**
         * Destructor
         */
        ~FBO();

        /**
         *
         * Called on state change from halted to configured. 
         *
         * @li Calls ParameterSet with dummy list in order to set Paramenters 
         *     in hardware.
         * @li Reset internal counters to 0.
         * @li Gets destinationTid from destination class (if not selfTest_)
         */
        xoap::MessageReference Configure(xoap::MessageReference msg) throw (xoap::exception::Exception);

        /**
         *
         * Called on state change from configured to enabled.
         *
         * @li calcualate actualDataSizePerBlock.
         * @li activate Myrinet FB poll-thread.
         */
        xoap::MessageReference Enable (xoap::MessageReference msg) throw (xoap::exception::Exception);

        xoap::MessageReference Halt (xoap::MessageReference msg) throw (xoap::exception::Exception);

        /**
         * Readout the Myrinet but do not block
         */
        xoap::MessageReference readFBO(xoap::MessageReference msg) throw (xoap::exception::Exception);

        /**
         * Request a dump of an event via SOAP.
         */
        xoap::MessageReference dumpFragment( xoap::MessageReference msg );

        /**
         * The routine to create the hyperdaq web page.
         */
        void defaultWebPage(xgi::Input *in, xgi::Output *out) throw( xgi::exception::Exception );


    private:		
        /**
         * Initialize an i2o frame for sending a buffer chain of a fragment.
         *   @parameter data points to the start of the header of the message
         *   @parameter length is the length of the fragment in bytes (i.e. without
         *              the bytes of the i2o header; all bytes coming from the FRL.)
         *   @paramnter msgNb is the number of the block in the fragment chain 
         *              (start with 0)
         *   @paramnter nbMsg is the total number blocks in the fragment.
         *   @parameter lvl1Id of the fragment corresponding to the segment 
         */
        void fillFrame ( toolbox::mem::Reference *ref, int32_t length, int32_t msgNb, int32_t nbMsgs, int32_t lvl1Id );
                

        /**
         * update the monitoring info
         */
        void updateMonitoringInfo();

        /**
         * Resets counters
         */
        void resetCounters();

        /**
         * Creates a chain of BufRefs containing the block chain obtained from 
         * the Myrinet FB for the fragment. 
         */
        toolbox::mem::Reference * fboRead()  throw( xcept::Exception, xdaq::exception::Exception );

        /**
         * Helper function to generate a fragment in the FED
         */
        void generateFragment();

        /**
         * A function to create delays which are not interrupted by signals
         * @return the number of usecs actually waited
         */
        uint32_t uDelay( uint32_t delay );

        /**
         * A helper function for uDelay
         */
        uint32_t subtractTime(struct timeval& t, struct timeval& sub);

        xoap::MessageReference changeState (xoap::MessageReference msg)
            throw ( xoap::exception::Exception );

        /**
         * State Transition Callback
         */
      void ConfigureAction( toolbox::Event::Reference e);


        /**
         * State Transition Callback
         */
      void EnableAction( toolbox::Event::Reference e);


        /**
         * State Transition Callback
         */
      void StopAction( toolbox::Event::Reference e);


        /**
         * State Transition Callback
         */
      void HaltAction( toolbox::Event::Reference e);

        /**
         * State Transition Callback
         */
      void FailAction( toolbox::Event::Reference e);

        /**
         * State Transition Callback
         */
      void ErrorAction( toolbox::Event::Reference e);

        bool poll (toolbox::task::WorkLoop *wl)
          throw (toolbox::fsm::exception::Exception);

        bool monitor (toolbox::task::WorkLoop *wl);

        void feedMyrfb( std::list< LendBuffer_t* > &lendBufs ) throw (fedbuilder::exception::MyrinetError);

        void registerDumps(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

        void stateChanged( toolbox::fsm::FiniteStateMachine & fsm ) throw (toolbox::fsm::exception::Exception) ;
  
      void stateChangedWithNotification( toolbox::fsm::FiniteStateMachine & fsm );
  
        /**
         * Callback when the Failed state has been reached.
         * RCMS will be notified of the state change.
         */
      void stateChangedToFailedWithNotification( toolbox::fsm::FiniteStateMachine & fsm );
      
        /**
         * Callback when the Error state has been reached.
         * RCMS will be notified of the state change.
         */
      void stateChangedToErrorWithNotification( toolbox::fsm::FiniteStateMachine & fsm );
      
        void gotoFailed(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

    private:

      void notifyRCMS( toolbox::fsm::FiniteStateMachine & fsm, std::string msg );
      void gotoFailed();
      void gotoError();

        const int32_t      payloadOffset_c;    //< set to sizeof (FragChainMsg) (constructor)
        const int32_t      reservedSize_c;     //< set to sizeof (FragChainMsg - sizeof (U32)) (constructor)


        //////////////////////////////////////
        //                                  //
        //        InfoSpace variables       //
        //                                  //
        //////////////////////////////////////

        // Run Control variables
        xdata::String        stateName_;           //< needed by RunControl to determine the state
        xdata::String        misStateName_;        //< for monitoring infospace
        xdata::String        destinationClass_;    //< where to deliver the FED data (class name)
        xdata::UnsignedInteger32  destinationInstance_; //< where to deliver the FED data (class name)

        // memory allocation
        xdata::UnsignedInteger32  blockSize_;         //< size of fedkit blocks (data + header)
        xdata::UnsignedInteger32  maxInputBlocks_;    //< maximal number of input blocks
        xdata::UnsignedInteger32  spareBlocks_;       //< spare blocks to allocate
        
        // Myrinet FB Parameters
        xdata::UnsignedInteger32  myrinetUnitNo_;           //< number of the Myrinet unit
        xdata::String             fedbuilderConfigFile_;    //< contains topology of fedbuilder
        xdata::String             fedbuilderConfiguration_; //< Contains fedbuilder config in string. (for automatic configuration)
        xdata::String             fedbuilderConfigMethod_;  //< May be 'string' or 'file'
        xdata::UnsignedInteger32  myrfb_option_;            //< extra option for  Myrinet 
        xdata::UnsignedInteger32  fbiMask_;                 //< introduced to disable FEDs  
        xdata::UnsignedInteger32  fboMask_;                 //< on the fly via RCMS-function
        xdata::Vector< xdata::Float > sliceWeights_;        //< relative weights for the routing to the slices. Allows static load balancing. The weights must be different from 0 for all destinations which are '1' in the fboMask_

        // test and measure variables
        xdata::Boolean selfTest_;
        xdata::UnsignedInteger32 fragmentCounter_;        //< read only: counts fragments from fedkit
        xdata::UnsignedInteger32 segmentCounter_;         //< read only: counts incoming Myrinet FB-segments        
        xdata::Boolean analyzeFragment_;                  //< if true dumps blocks of the fragments on screen
        xdata::Boolean checkSuperFragment_;               //< if true checks the superfragment consistency by analyzing all slink fragments
        xdata::Boolean stopOnDataCheckError_;             //< if true stops and sends state notification to RCMS
        xdata::Boolean dumpToFile_;                       //< if true all dumps go to files in /tmp. (otherwise to the logger)
        xdata::Boolean dumpProcFile_;                     //< if true dumps myrfb proc file to monitoring infospace string
        xdata::Boolean dumpMyrinetFBSegment_;             //< if true dumps header info of Myrinet FB descriptor and FRL header
        xdata::UnsignedInteger32 maxErrorDump_;           //< max number of events to be dumped if crc error occurs
        xdata::UnsignedInteger32  deltaTMon_;             //< deltaT monitor
        xdata::String errorString_;                       //< In case of an error holds a human readable string;

        // memory management variables		   
        xdata::UnsignedInteger32 gaveToMyrinetFB_;        //< counter for blocks currently held by myrinet card 
        xdata::UnsignedInteger32 provideRequests_;        //< global counter for yet unsatisfied requests for providing

        xdata::Boolean cheatMode_;
        xdata::UnsignedInteger32 autoGeneratedMeanSize_;  //< in case data are generated by the application

        xdata::UnsignedInteger32 totalSlinkPayload_;      //< Counts the total payload transfered over the SLINK
        xdata::UnsignedInteger32 totalFBOPayload_;        //< Counts the total payload sent to the FBO

        xdata::Boolean stopThread_;                       //< if switched to 1 finishes poll task

        xdata::String pheapsPoolName_;                    //< only needed in case of >1 FBOs in one host

        xdata::String myrfbStatus_;
        xdata::String procFile_;                          //< the contents of the myrfb proc file
        xdata::UnsignedInteger32 myrfb_crc_err_0_;        //< indicates usage of memory in myrfb
        xdata::UnsignedInteger32 myrfb_crc_err_1_;        //< indicates usage of memory in myrfb
        xdata::UnsignedInteger32 myrfb_bufmem_occ_;       //< indicates usage of memory in myrfb
        xdata::UnsignedInteger32 instance_;
        xdata::UnsignedInteger32 runNumber_;
        xdata::UnsignedInteger32 numberOfDumps_;
        xdata::Boolean fireItemGroupRetrieveEvents_;  //< see comment in code: default correct for Sensor in Profile with or without ISB
        xdata::Boolean fireItemGroupChangedEvents_;   //< see comment in code: default correct for Sensor in Profile with or without ISB


        ////////////////////////// end InfoSpace ////////////////////////////

        toolbox::rlist< toolbox::mem::Reference* > fragmentBlocks_; //< list of blocks for a fragment
        toolbox::rlist< uint32_t > fragmentBlockLengths_;       //< list of blocks lengths of fragments in fragmentBlocks_
        toolbox::rlist< uint32_t > dumpRequestList_ ;           //< list of numbers of events to dump
        // Local class variables
        int32_t myTid_;                                                 //< is filled in the Configure method.
        int32_t destinationTid_;                                        //< where to deliver the FED data (Configure)
        uint32_t actualDataSizePerBlock_;                       //< block size - header (Enable)
        uint32_t currentLvl1Id_;                                //< for check on the Lvl1Id in the FRL header
        uint32_t currentSegmentNumber_;                         //< for check on segment number in Myrinet FB segments.
        uint32_t currentPayloadLength_;                         //< builds up the total payload length as segment come in. 
        //< This number can be checked against the SLINK Trailer.
        uint32_t currentTotalFragmentLength_;                   //< builds up the fragment length including the FRL-headers 
        //< as segments come in.
        int32_t eventSize_;			                        
					                        
        bool crcError_;                                             //< flag to remember slink crcError in a segment of an event
        bool fedcrcError_;                                          //< flag to remember fedcrcError in a segment of an event
        uint32_t crcErrorCount_;                                //< counts the number of crc errors
        uint32_t superFragmentErrorCount_;                      //< counts the number of errors in checkSuperFragment

        uint32_t monLoopCnt_;

        bool enableMyrinet_;

        toolbox::task::WorkLoop *workLoop_;
        toolbox::task::WorkLoop *monWorkLoop_;

        toolbox::fsm::AsynchronousFiniteStateMachine *fsm_;
        xdaq::ApplicationDescriptor* destinationDescriptor_;
        
        fedbuilder::WebPageMaker webPage_;
        fedbuilder::DataChecker dataChecker_;
        fedbuilder::MemoryManager *memoryManagerPtr_;
        std::list< void * > myrfbBufs_;
        bool artificialError_;

        struct timeval time_start;
        struct timeval time_stop;    
      
        MyrinetConfigurator myrinetConfigurator_;

        xdata::InfoSpace *mis_;
  
        /**
         * a helper class for annoying SOAP and FSM code
         **/
        SOAPFSMHelper *soapFsmHelper_;

        /**
         * RCMS state notifier.
         */
        xdaq2rc::RcmsStateNotifier rcmsStateNotifier_;

        xdata::InfoSpace* applInfoSpace_;
    };
  
} /* namespace fedbuilder */

#endif /* __FBO_h__ */

