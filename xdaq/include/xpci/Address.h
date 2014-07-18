// $Id$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: L. Orsini and A. Petrucci                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xpci_Address_h_
#define _xpci_Address_h_


#include <exception>
#include <string>
#include <stdint.h>

// Insert file for pciaddr_t definition
#include "xpci/xpci-types.h"


namespace xpci {

class Bus;

class Address {
	
	public :
		~Address();

		// Returns address value
	        pciaddr_t getAddress();

		// Returns an Address pointing to the config space of a board, chosen by bus/dev/fn 
		static Address getConfigSpaceAddressByBus(unsigned int bus, unsigned int device, unsigned int function);

		// Returns an Address pointing to the config space of a board, chosen by vendor, device,index 
		static Address getConfigSpaceAddressByVendor(unsigned int vendor, unsigned int device, unsigned int index);
		
		// Returns an Address pointing to the memory space of the given physical address
		static Address getMemorySpaceAddress (pciaddr_t address);

		// Returns an Address pointing to the memory IO space of the given physical address
		static Address getMemorySpaceIOAddress (pciaddr_t address);

		
	friend class xpci::Bus;	
		
	private : 
		Address (pciaddr_t address);

		Address (unsigned int vendor, unsigned int device, unsigned int index);

		// PCI addres spaces 
		unsigned int type_;
		// Physical address
		pciaddr_t address_;
		// placeholder for vendor ID or bus ID (in condig space cases)
		unsigned int vendorbus_;
		// placeholder for device ID or device number (on bus) 
		unsigned int device_;
		// placeholder for index or function number */
		unsigned int indexfn_;
			
	};
}

#endif
