// $Id: FRLLinkDevice.hh,v 1.18 2009/03/04 13:45:32 cschwick Exp $

#ifndef _fedbuilder_FRLLinkDevice_hh_
#define _fedbuilder_FRLLinkDevice_hh_

#include "xdata/InfoSpace.h"
#include "xdata/String.h"
#include "xdata/Double.h"
#include "xdata/Table.h"
#include "xdata/Boolean.h"
#include "xdata/TimeVal.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/UnsignedInteger64.h"
#include "xdata/Vector.h"
#include "xdata/ActionListener.h"


#include "xdaq/Object.h"
#include "xdaq/Application.h"

#include "fedbuilder/TimeUtils.hh"
#include "fedbuilder/FirmwareHandler.hh"

#include "fedbuilder/FedbuilderExceptions.hh"

#include "hal/PCIAddressTable.hh"
#include "hal/PCILinuxBusAdapter.hh"
#include "hal/PCIDevice.hh"
#include "hal/HardwareAccessException.hh"

#define WCBIN  257   
#define BXBIN  4096

namespace fedbuilder 
{
    class FRLLinkDevice: public xdata::ActionListener, public xdaq::Object 
    { 
    public:

        FRLLinkDevice( xdaq::Application * owner );

        ~FRLLinkDevice( );

        void init ( xdata::UnsignedInteger32 linkNumber, 		     
                    HAL::PCIDevice * frlCard, 
                    HAL::PCIDevice * spyCard, 
                    xdata::InfoSpace * father 
                    ) throw (fedbuilder::exception::FRLLinkDeviceCreationFailed);

        void closeDown() throw( fedbuilder::exception::FRLLinkDeviceCloseDownFailed );

        bool initialized() { return initialized_; };

	  
        void actionPerformed (xdata::Event& e);
	  
        void testLink( uint32_t mseconds ) throw (fedbuilder::exception::FRLLinkDeviceTestFailed,
                                                  fedbuilder::exception::HardwareAccessFailed);

        void enable() throw (fedbuilder::exception::HardwareAccessFailed);
			
        void deskew() throw (fedbuilder::exception::HardwareAccessFailed);
			
        void setDCBalance( bool dcflag ) throw (fedbuilder::exception::HardwareAccessFailed);
	
        bool fifoAlmostFullChanged();

	xdata::InfoSpace* getDBInfoSpace();
        xdata::InfoSpace* getStatusInfoSpace();
        xdata::InfoSpace* getHistogramInfoSpace();

    protected:

        TimeUtils timeUtil_;
        bool initialized_;

        xdata::InfoSpace* isStatus_;
        xdata::InfoSpace* isHistograms_;
        xdata::InfoSpace* cardInfoSpace_;
        xdata::InfoSpace* dbis_;
        HAL::PCIDevice * frlCard_; 
        HAL::PCIDevice * spyCard_;
	  
        xdata::UnsignedInteger32  linkNumber_; 	
        xdata::UnsignedInteger32  autotest_;    
        xdata::UnsignedInteger32  tstl_lowbit_; 
        xdata::UnsignedInteger32  tstl_highbit_;
        xdata::UnsignedInteger32  backpressure_;
        xdata::UnsignedInteger32  backpressdyn_;
        xdata::UnsignedInteger32  lvdsstatus_;  
        xdata::UnsignedInteger32  BXNumber_; 
        xdata::UnsignedInteger32  triggerNum_; 
        xdata::UnsignedInteger32  slinkBadCRC_; 	
        xdata::UnsignedInteger32  fedBadCRC_; 	
        xdata::UnsignedInteger32  fedSourceId_; 
        xdata::UnsignedInteger32  wcHistoSum_;        
        xdata::Double             wcHistoSumSquare_;  
        xdata::UnsignedInteger32  histoEntries_;    
        xdata::UnsignedInteger32  CMCversion_;    
        xdata::UnsignedInteger32  fedClk_;    
        xdata::UnsignedInteger32  LFFOnCycles_;    
        xdata::UnsignedInteger32  LFFOnCyclesHigh_; 
        xdata::UnsignedInteger32  fifoStatus_; 
        xdata::Boolean            enabled_; 		
        xdata::Double 	    timer_;		
        xdata::Vector<xdata::UnsignedInteger32> wchisto_;
        xdata::Vector<xdata::UnsignedInteger32> bxhisto_;
        xdata::UnsignedInteger64  wordCount_;
        xdata::UnsignedInteger64  clockCount_;
        xdata::UnsignedInteger64  fifoAlmostFullCount_;
        uint64_t                  newFifoAlmostFullCount_;
        uint64_t                  oldTimerCounter_;
      //        uint64_t                  oldClockCount_;
        uint64_t                  newTimerCounter_;
        bool                      fifoAlmostFullChanged_;
        xdata::Double             deltaT_;
        xdata::UnsignedInteger64  deltaT_int;
        xdata::UnsignedInteger64  deltaT_clk;
        xdata::UnsignedInteger32  deltaN_;
        xdata::Double             deltaSumOfSizes_;
        xdata::Double             deltaSumOfSquares_;
        xdata::UnsignedInteger32  expectedFEDSrcId_;
        xdata::UnsignedInteger32  geoslot_;
        xdata::String             fedsrcidStr_;
        xdata::String             channelStr_;
        xdata::String             geoslotStr_;
        xdata::TimeVal            timestamp_;
        uint32_t triggerNumLast_;

        uint32_t frlMode_;
        uint32_t generatorSourceId_;

        uint64_t wordCountLast_;


    };
}
#endif
