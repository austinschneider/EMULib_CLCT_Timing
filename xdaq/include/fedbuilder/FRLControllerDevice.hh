// $Id: FRLControllerDevice.hh,v 1.29 2009/01/22 16:36:00 cschwick Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors:  R. Arcidiacono, L. Orsini, C. Schwick			 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _fedbuilder_FRLControllerDevice_h_
#define _fedbuilder_FRLControllerDevice_h_

#include <unistd.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>

#include "xdata/InfoSpace.h"
#include "xdata/TimeVal.h"
#include "xdata/UnsignedInteger64.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/Boolean.h"
#include "xdata/String.h"
#include "xdata/Float.h"

#include "xdaq/Object.h"

#include "hal/PCIAddressTable.hh"
#include "hal/PCILinuxBusAdapter.hh"
#include "hal/PCIDevice.hh"
#include "hal/HardwareAccessException.hh"

#include "fedbuilder/FedbuilderExceptions.hh"
#include "fedbuilder/FRLLinkDevice.hh"
#include "fedbuilder/MyrinetConfigurator.hh"

#include "myrfb.h"
#include "myrfb_api.h"

#include "log4cplus/logger.h"

#define FRLCONTROLLER_VENDORID 0xecd6
#define FRLCONTROLLER_DEVICEID 0xff10

#define SPYCONTROLLER_VENDORID 0xecd6
#define SPYCONTROLLER_DEVICEID 0xff01

#define NLINK 2         // number of links physically present in the FRL
#define FRL_GENE_SIZE_TRIGGER_FIFO 2000
#define FRL_TRIGNO_MASK 0x00FFFFFF

/**
 * The MAZE_USER_PAYLOAD is defined as everything which is not the 
 * myrinet header. This means that it is data payload plus SLINK 
 * header plus FRL header. (It is the payload size going over the 
 * Myrinet link, from the Myrinet cards view)
 */

// SHOULD BE IN MAZE HEADERS: (NEAR FUTURE...)
#define FRL_FBI_PAYLOAD      4096

namespace fedbuilder 
{
    class FRLControllerDevice : public  xdata::ActionListener, public xdaq::Object 
    {
    public:

	FRLControllerDevice( xdaq::Application * owner ); 

	~FRLControllerDevice();

        void closeDown() throw (fedbuilder::exception::FRLControllerDeviceCloseDownFailed);

        void setupInfospace() throw ( fedbuilder::exception::FRLControllerDeviceInfospaceSetupFailed );

        void init() throw(fedbuilder::exception::FRLControllerDeviceCreationFailed);

        // This copies some config parameters of the FRLController to this class.
        // It should be executed in Configure also if the FRLController is no in use in the run. 
        void copyControllerConfigData() throw( fedbuilder::exception::FRLControllerDeviceCreationFailed );

	// Dump link
	//
	void  slowRead(uint32_t nfrag = 1) throw (fedbuilder::exception::HardwareAccessFailed);

	// Reset histogramming buffer memory and return the approximate
	// time at which the reset has finished
	//
	void resetZBTMem() throw (fedbuilder::exception::HardwareAccessFailed);

	uint32_t generateTriggers( uint32_t trigNo, uint32_t fraglen, uint32_t sourceId ) throw (fedbuilder::exception::HardwareAccessFailed);
		
	void setDAQMode() throw (fedbuilder::exception::HardwareAccessFailed);
	
	void setGeneratorMode() throw (fedbuilder::exception::HardwareAccessFailed);

	void setEfedMode() throw (fedbuilder::exception::HardwareAccessFailed);
	
	void checkMyrinetStatus() throw (fedbuilder::exception::MyrinetError, fedbuilder::exception::MyrinetSyncLost);
	
	void haltMyrinet() throw (fedbuilder::exception::MyrinetHaltError, fedbuilder::exception::HardwareAccessFailed);

	void  actionPerformed (xdata::Event& e); 
	
	void enable(xdata::Boolean & enableHistogram , xdata::UnsignedInteger32 & resolution )
          throw (fedbuilder::exception::Exception,
                 fedbuilder::exception::HardwareAccessFailed );

	void testLinks( uint32_t mseconds ) throw (fedbuilder::exception::FRLLinkDeviceTestFailed);
	
        void suspendEfed() throw (fedbuilder::exception::HardwareAccessFailed);;
        void resumeEfed() throw (fedbuilder::exception::HardwareAccessFailed);;

        // void setMyrinetDelay (uint32_t useconds ) throw (fedbuilder::exception::MyrinetAccessFailed);
	
	xdata::InfoSpace* getInfoSpace();
	
	std::map<uint32_t, fedbuilder::FRLLinkDevice*>& getLinkDevices();

        bool initialized() { return initialized_; };

        void setFixedEventSize( uint32_t eventSize,
                                uint32_t source ,
                                uint32_t deltaT ) throw( fedbuilder::exception::FRLControllerDeviceCreationFailed );

        void setLogNormalEventSize( uint32_t mean,
                                    uint32_t source,
                                    uint32_t deltaT,
                                    uint32_t logNEvt,
                                    uint32_t seed,
                                    uint32_t stdDev,
                                    uint32_t minSize,
                                    uint32_t maxSize ) throw( fedbuilder::exception::FRLControllerDeviceCreationFailed );

        uint32_t getFRLType() const { return actualFRLType_; };
        uint32_t getFRLVersion() const { return actualFRLVersion_; };
        uint32_t getBridgeType() const { return actualBridgeType_; };
        uint32_t getBridgeVersion() const { return actualBridgeVersion_; };
        std::string getSerialNumber() const { return serialNumber_; };

        void readItem( std::string item, uint32_t *result, uint32_t offset = 0 ) throw ( HAL::HardwareAccessException );
        void writeItem( std::string item, uint32_t value, uint32_t offset = 0 ) throw ( HAL::HardwareAccessException );

    private:
      
        xdaq::Application *owner_;

        HAL::PCILinuxBusAdapter   *busAdapter_; 
        HAL::PCIDevice* spyCard_;
        HAL::PCIDevice* frlCard_;
        uint32_t geogrSlot_;
        bool enableLink0_;
        bool enableLink1_;
        myrfb_unit_t*   myrinetCard_;
        std::map<uint32_t, fedbuilder::FRLLinkDevice*> linkDevice_;
        HAL::PCIAddressTable      *frlAddressTable_;
        HAL::PCIAddressTable      *spyAddressTable_;
        MyrinetConfigurator       myrinetConfigurator_;
        std::string             serialNumber_;
        uint32_t  actualFRLVersion_;
        uint32_t  actualBridgeVersion_;
        uint32_t  actualFRLType_;
        uint32_t  actualBridgeType_;
        bool initialized_;

        xdata::InfoSpace*         is_;
        xdata::String             myrState_;
        xdata::UnsignedInteger32  myrnetAddr_;
        xdata::UnsignedInteger32  myrOccupancy_;
        xdata::UnsignedInteger32  myrlastFrlEvt_;
        xdata::UnsignedInteger32  myrlastSegNo_;
        xdata::UnsignedInteger32  myrlastResyncEvt_;

        xdata::UnsignedInteger32  cntmyrEvt_;
        xdata::UnsignedInteger32  cntmyrresync_;
        xdata::UnsignedInteger32  cntmyrbadHeaderMark_;
        xdata::UnsignedInteger32  cntmyrbadTrailerMark_;
        xdata::UnsignedInteger32  cntmyrbadcrcfed_;
        xdata::UnsignedInteger32  cntmyrbadcrcslink_;
        xdata::UnsignedInteger32  cntmyrblock_;
        xdata::UnsignedInteger32  cntmyrbadEvtNo_;
        xdata::UnsignedInteger32  cntmyrbadSegNo_;

        xdata::UnsignedInteger64  triggerCount_;
        xdata::UnsignedInteger32  PCIretryCount_;
        xdata::UnsignedInteger32  freeBlockCount_;
        xdata::UnsignedInteger32  statusFifos_;
        xdata::UnsignedInteger64  timer_;
        xdata::UnsignedInteger64  clockCount_;
        xdata::UnsignedInteger64  oldClockCount_;
        xdata::UnsignedInteger64  deltaClockCount_;
        xdata::UnsignedInteger32  myrinetAdr_;
        xdata::UnsignedInteger32  pendingTriggers_;
        xdata::UnsignedInteger32  slotNumber_;
        xdata::UnsignedInteger32  frlMode_;		
        xdata::UnsignedInteger32  eventSize_;		
        xdata::UnsignedInteger32  eventSizeStdDev_;		
        xdata::UnsignedInteger32  minFragmentSize_;		
        xdata::UnsignedInteger32  maxFragmentSize_;		
        xdata::UnsignedInteger32  deltaT_;		
        xdata::UnsignedInteger32  eventSizeSeed_;		
        xdata::UnsignedInteger32  eventTableRank_;		
        xdata::UnsignedInteger32  sttsReadyThreshold_;		
        xdata::UnsignedInteger32  sttsBusyThreshold_;		
        xdata::UnsignedInteger32  fedId_;		
        xdata::UnsignedInteger32  slot_;		
        xdata::String             procFile_;
        xdata::Boolean            dumpProcFile_;

        xdata::String geoSlotStr_;

    };  
}
        
#endif
