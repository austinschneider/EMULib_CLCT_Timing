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

#ifndef _xpci_h_
#define _xpci_h_


#include <sys/types.h>
#include <string>
#include <stdint.h>
#include "xpci/exception/IOError.h"
#include "xpci/exception/OpenFileFailed.h"
#include "xpci/exception/InvalidAddress.h"
#include "xpci/Address.h"

namespace xpci {

class Bus 
{
public:	 
	Bus () throw (xpci::exception::OpenFileFailed);
	~Bus();

/*
	void read (const xpci::Address& addr, pciaddr_t offset, uint8_t & data) 
		throw (xpci::exception::IOError);

	void read (const xpci::Address& addr, pciaddr_t offset, uint16_t & data) 
		throw (xpci::exception::IOError);
*/

	void read (const xpci::Address& addr, pciaddr_t offset, uint32_t & data) 
		throw (xpci::exception::IOError);

	void read (const xpci::Address& addr, pciaddr_t offset, uint64_t & data) 
		throw (xpci::exception::IOError);

/*
	void write (const xpci::Address& addr, pciaddr_t offset, uint8_t data) 
		throw (xpci::exception::IOError);

	void write (const xpci::Address& addr, pciaddr_t offset, uint16_t data) 
		throw (xpci::exception::IOError);
*/

	void write (const xpci::Address& addr, pciaddr_t offset, uint32_t data) 
		throw (xpci::exception::IOError);

	void write (const xpci::Address& addr, pciaddr_t offset, uint64_t data) 
		throw (xpci::exception::IOError);

	/** Returns an Address referring to the address mapping as holded in the corresponding Base Address Register 'number' of the PCI card. 
	 * The base address has to be a config space, pointing the start address of the configuration space
	 */
	xpci::Address BAR(unsigned int barNumber, const xpci::Address& configSpaceAddress) 
		throw (xpci::exception::InvalidAddress,xpci::exception::IOError);

	//
	//std::list<xpci::Address> scan();

private:
	int fd_;
};

}

#endif
