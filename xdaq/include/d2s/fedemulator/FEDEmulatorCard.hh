// $Id: FEDEmulatorCard.hh,v 1.1 2007/04/27 18:05:48 cschwick Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors:  R. Arcidiacono, L. Orsini, C. Schwick			 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _d2s_FEDEmulatorCard_h_
#define _d2s_FEDEmulatorCard_h_

#include "hal/PCIDevice.hh"
#include "hal/PCIAddressTableASCIIReader.hh"
#include "hal/PCILinuxBusAdapter.hh"
#include "hal/HardwareAccessException.hh"
#include "hal/NoSuchFileException.hh"
#include "log4cplus/logger.h"
#include "toolbox/string.h"

#include <stdint.h>

#define FEDEMULATOR_VENDORID 0xecd6
#define FEDEMULATOR_DEVICEID 0xfe05
#define FEDEMULATOR_SEED 0x12

using namespace log4cplus;

namespace d2s {

  class FEDEmulatorCard : public HAL::PCIDevice {

  public:

    FEDEmulatorCard( HAL::PCIAddressTable& fedEmulatorAddressTable,
		     HAL::PCIBusAdapterInterface& busAdapter,
		     HAL::PCIDevice::PCILocationIdentifier busLocation,
		     Logger logger)
      throw(HAL::HardwareAccessException);
    
    FEDEmulatorCard( HAL::PCIAddressTable& fedEmulatorAddressTable,
		     HAL::PCIBusAdapterInterface& busAdapter,
		     uint32_t pciIndex,
		     Logger logger)
      throw(HAL::HardwareAccessException);
    
    virtual ~FEDEmulatorCard();

    /**
     * @param eventSize counts only payload without SLINK header or trailer.
	   */
    void setFixedEventSize( uint32_t source,
			    uint32_t eventSize,
			    uint32_t deltaT  ) 
      throw( HAL::HardwareAccessException );
    
    void setLogNormalEventSize( uint32_t mean,
				uint32_t source,
				uint32_t deltaT,
				uint32_t logNEvt,
				uint32_t seed,
				uint32_t stdDev,
				uint32_t minSize,
				uint32_t maxSize ) 
      throw( HAL::HardwareAccessException );
    
    /**
     * preload events from file into GIII memory
     */
    void preloadEvents( std::string fileName ) 
      throw( HAL::HardwareAccessException );
    
  private:
    Logger logger_;
    
  };
  
}

#endif 

