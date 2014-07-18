// $Id: FRLController.hh,v 1.64 2009/04/29 10:25:54 cschwick Exp $
#ifndef _fedbuilder_FRLController_h_
#define _fedbuilder_FRLController_h_

#include <vector>

#include "myrfb_api.h"
#include "log4cplus/logger.h"

#include "fedbuilder/FRLControllerDevice.hh"
#include "fedbuilder/FRLLinkDevice.hh"
#include "fedbuilder/SOAPFSMHelper.hh"

#include "xdaq/WebApplication.h"
#include "xdaq/ApplicationStub.h"
#include "xdaq/exception/Exception.h"

#include "xoap/MessageReference.h"

#include "xdata/UnsignedInteger32.h"
#include "xdata/Double.h"
#include "xdata/Float.h"
#include "xdata/String.h"
#include "xdata/Vector.h"
#include "xdata/Table.h"

#include "toolbox/task/TimerFactory.h"
#include "toolbox/fsm/AsynchronousFiniteStateMachine.h"
#include "toolbox/task/WorkLoop.h"
#include "toolbox/BSem.h"
#include "toolbox/rlist.h"

#include "hal/linux/StopWatch.hh"

// include for RUNControlState Notifier
#include "xdaq2rc/RcmsStateNotifier.h"

namespace fedbuilder {

    class FRLController : public xdaq::WebApplication , public xdata::ActionListener
    {
    public:

      //enum CommandEnum{ CONFIGURE, ENABLE, STOP, HALT, SUSPEND, RESUME };

        XDAQ_INSTANTIATOR();

        FRLController(xdaq::ApplicationStub* stub)
            throw (xdaq::exception::Exception);

        virtual ~FRLController();

        /**
         * Write an item to a FRLControllerCard.
         * This function is intended for debugging only.
         */
        xoap::MessageReference writeItem( xoap::MessageReference message ) throw (xoap::exception::Exception);

        /**
         * Read an item from a FRLControllerCard via SOAP.
         * This function is for debugging only.
         */
        xoap::MessageReference readItem( xoap::MessageReference message )  throw(xoap::exception::Exception);
	    
	      
        /**
         * Workloop function to generate monitoring information.
         */
      bool monitorTask(toolbox::task::WorkLoop *wl) throw( toolbox::fsm::exception::Exception );

        /**
         * Workloop function for commands in asynchronous state changes.
         */
        bool commandLoop(toolbox::task::WorkLoop *wl);

        /**
         * Read counters when action is performed 
         * 
         */
        void actionPerformed (xdata::Event& e);

        /**
         * XDAQ state transition callback.
         * Creates address table and FRLCard.
         */
        void ConfigureAction(toolbox::Event::Reference e)  
          throw (toolbox::fsm::exception::Exception);

        /**
         * XDAQ state transition callback.
         */
      void EnableAction(toolbox::Event::Reference e)
          throw (toolbox::fsm::exception::Exception);

        /**
         * XDAQ state transition callback.
         */
      void StopAction(toolbox::Event::Reference e)
          throw (toolbox::fsm::exception::Exception);

        /**
         * XDAQ state transition callback.
         */
      void SuspendAction(toolbox::Event::Reference e)
          throw (toolbox::fsm::exception::Exception);

        /**
         * XDAQ state transition callback.
         */
      void ResumeAction(toolbox::Event::Reference e)
          throw (toolbox::fsm::exception::Exception);

        /**
         * XDAQ state transition callback.
         */
      void HaltAction(toolbox::Event::Reference e)
          throw (toolbox::fsm::exception::Exception);

        /**
         * XDAQ state transition callback.
         */
      void FailAction(toolbox::Event::Reference e );

        /**
         * XDAQ state transition callback.
         */
      void ErrorAction(toolbox::Event::Reference e );


        /**
         * Callback when a new fsm state has been reached (asynchronous state changes to Failed)
         * RCMS will be notified of the state change.
         */
        void stateChangedWithNotification( toolbox::fsm::FiniteStateMachine & fsm );

        /**
         * Callback when the Failed state has been reached.
         * RCMS will be notified of the state change.
         */
        void stateChangedToFailedWithNotification( toolbox::fsm::FiniteStateMachine & fsm ) ;

        /**
         * Callback when the Error state has been reached.
         * RCMS will be notified of the state change.
         */
        void stateChangedToErrorWithNotification( toolbox::fsm::FiniteStateMachine & fsm ) ;

        /**
         * HyperDAQ default WEB PAGE for the application
         * 
         */
        void defaultWebPage(xgi::Input *in, xgi::Output *out) throw (xgi::exception::Exception);

        void testLinks( xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	  
        void resetZBT( xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);	  

        void applySettings( xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);

        void generateEvtNoError( xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);
	  
        void control(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	  
        void slowRead( xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);

        // void setDelay( xgi::Input * in, xgi::Output * out) throw (xgi::exception::Exception);

      void lockInfospaces();
      void unlockInfospaces();

    private:

      void notifyRCMS( toolbox::fsm::FiniteStateMachine & fsm, std::string msg );
      void gotoFailed() throw (toolbox::fsm::exception::Exception);
      void gotoError();
        void TabPanel( xgi::Output * out );
        void linkTab(xgi::Output * out );
        void controlTab(xgi::Output * out );
        void statusTab( xgi::Output * out );
        void settingsTab( xgi::Output * out );
        void testLinks() throw(fedbuilder::exception::Exception);
        void updateMonitoringInfo()
          throw (toolbox::fsm::exception::Exception);
      
      //toolbox::rlist< CommandEnum > commandFifo_; ///< A fifo which buffers the soap commands for asynchronous handling of commands.

        xoap::MessageReference    changeState (xoap::MessageReference msg)  throw (xoap::exception::Exception);

        FRLControllerDevice* frlDevice_;	  

        uint64_t counter64;
        bool pushDbInfospace_ ; 
        std::string errorString_;
  
        // 
        // To protect the Hardware access 
        //

        //
        // exported Properties of the Application
        //
        std::string               stateVar_;
        xdata::String             stateName_;
        xdata::String             subState_;
        xdata::String             fedbuilderConfigFile_;    ///< file to configure the fedbuilder (fbi- fbo addresses)
        xdata::String             fedbuilderConfigMethod_;  ///< May be 'string' or 'file'
        xdata::String             fedbuilderConfiguration_; ///< If configmethod is 'file' contains fedb. configuration
        xdata::UnsignedInteger32  myrfb_option_;            ///< extra option for  Myrinet 
        xdata::UnsignedInteger32  fbiMask_;                 ///< introduced to disable FEDs  
        xdata::UnsignedInteger32  fboMask_;                 ///< on the fly via RCMS-function-manager
        xdata::Vector< xdata::Float > sliceWeights_;        ///< relative weights for the routing to the slices. Allows static load balancing. The weights must be different from 0 for all destinations which are '1' in the fboMask_ 
        xdata::UnsignedInteger32  myrDelay_;                ///< Myrinet latency time (special test case)
        xdata::UnsignedInteger32  slowReadEvents_;          ///< Number of fragments to be read in a slow read
        xdata::UnsignedInteger32  requiredFRLVersion_;      
        xdata::UnsignedInteger32  requiredBridgeVersion;    
        xdata::UnsignedInteger32  frlMode_;                 ///< FRL_DAQ_MODE (0) for daq mode, 
        xdata::Boolean            fireItemGroupRetrieveEvents_;  ///< see comment in code: default correct for Sensor in Profile with or without ISB
        xdata::Boolean            fireItemGroupChangedEvents_;   ///< see comment in code: default correct for Sensor in Profile with or without ISB
        xdata::Boolean            pushHistos_;              ///< If set to true also histograms are pushed into the monitoring system
        xdata::UnsignedInteger32  pushHistoMultiplier_;     ///< Multiple of deltaT_ which determines the intervals the Histos are pushed
        xdata::UnsignedInteger32  pushHistoCnt_;            ///< Internal counter

        // from the hardware:
        xdata::UnsignedInteger32  frlType_;
        xdata::UnsignedInteger32  frlVersion_;
        xdata::UnsignedInteger32  bridgeType_;
        xdata::UnsignedInteger32  bridgeVersion_;
        xdata::String             serialNumber_;
        ///< FRL_GENERATOR_MODE (1) for generator mode
        xdata::UnsignedInteger32  expectedFEDSrcIdLink0_;   ///< Meta info from configurator to include in exceptions
        xdata::UnsignedInteger32  expectedFEDSrcIdLink1_;   ///< Meta info from configurator to include in exceptions
        xdata::UnsignedInteger32  WCHistoResolution_;       ///< resolution of WC histograms  < it should become a vector!! 
        xdata::UnsignedInteger32  slotNumber_;              ///< BUS location to ident. the CARD
        xdata::Boolean            dumpProcFile_;            ///< if set the proc file of the myrfb driver is read into a monitor infospace string 
        xdata::Boolean            enableDCBalance_;         ///< if set, the DCBalance is on at the transmitter side
        xdata::Boolean            enableDeskew_;            ///< enable the Deskew procedure on the two Links
        xdata::Boolean            enableLink0_;             ///< if set receives data link 0 (upper connector)
        xdata::Boolean            enableLink1_;             ///< if set receives data link 1 (lower connector)
        xdata::Boolean            enableSPY_;               ///< if set enable spy events
        xdata::Boolean            enableWChisto_;           ///< if set enable WC histos 
        xdata::UnsignedInteger32  deltaTMon_;               ///< deltaT monitor
        xdata::UnsignedInteger32  runNumber_;               ///< very temporary
        xdata::UnsignedInteger32  testDurationMs_;          ///< in ms the duration of the slink selftest

        /**
         * Event generation
         */
        xdata::UnsignedInteger32 genTriggerNo_;
        xdata::UnsignedInteger32 fragmentSize_;
        xdata::UnsignedInteger32 emulatorFEDId_;
        xdata::UnsignedInteger32 fragmentSizeStdDev_;
        xdata::UnsignedInteger32 minFragmentSize_;
        xdata::UnsignedInteger32 maxFragmentSize_;
        xdata::UnsignedInteger32 deltaT_;
        xdata::UnsignedInteger32 eventSizeSeed_;
        xdata::UnsignedInteger32 eventTableRank_;
        xdata::UnsignedInteger32 sttsReadyThreshold_;
        xdata::UnsignedInteger32 sttsBusyThreshold_;
        xdata::UnsignedInteger32 pendingTriggers_;
 
        uint32_t monLoopCnt_;
        toolbox::task::WorkLoop  *monWorkLoop_;
   
        /**
         * For the exception declaraion (sentinel)
         */
        xdata::String geoSlotStr_;

        /**
         * the statemachine of the application:
         */
         toolbox::fsm::AsynchronousFiniteStateMachine *fsm_;
        

        /**
         * a helper class for annoying SOAP and FSM code
         **/
         SOAPFSMHelper *soapFsmHelper_;


	/**
         * RCMS state notifier.
         */
	xdaq2rc::RcmsStateNotifier rcmsStateNotifier_;

	toolbox::Properties settings_;
	xdata::InfoSpace* isStatus_;

      /** 
       * To do some measurements
       */
      HAL::StopWatch timer_;
    };

}
#endif /* __FRLController */
