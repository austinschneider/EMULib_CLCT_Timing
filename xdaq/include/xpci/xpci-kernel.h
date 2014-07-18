/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: L. Orsini and A. Petrucci                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/


#ifndef _xpci_xpcikernel_h_
#define _xpci_xpcikernel_h_

#include <linux/types.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
#include <stdint.h>
#else
#endif
#include <asm/ioctl.h>

#include <xpci/xpci-types.h>

#ifdef __cplusplus
extern "C" {
#endif
 

typedef enum PCIBusSpace {
	XPCI_MEMORY =            0x102,
	XPCI_IO =                0x103,
	XPCI_CONFIG_VENDOR =     0x104,
	XPCI_CONFIG_BUS =        0x105
}__XPCI_BUS_SPACE_TYPE;

typedef enum PCIBusCommand {
	XPCI_READ  =0,
	XPCI_WRITE =1
} __XPCI_BUS_COMMAND_TYPE;

typedef enum PCIReadWriteSize {
	XPCI_8_BITS  = 8,
	XPCI_16_BITS = 16,
	XPCI_32_BITS = 32,
	XPCI_64_BITS = 64
} __XPCI_READ_WRITE_SIZE_TYPE;

/**
 * Structure for the IOCTL
 */

typedef struct XPCI {
	/** address relative to the BUS */
	pciaddr_t address;
	unsigned int vendorbus;
	unsigned int device;
	unsigned int indexfn;
	enum PCIReadWriteSize size; //  8, 16, 32, 64 bits
	union {
		uint8_t  value8;
		uint16_t value16;
		uint32_t value32;
		uint64_t value64;
	};
	enum PCIBusCommand command;
	enum PCIBusSpace type;
} __XPCI_TYPE;

#define XPCI_MAGIC ('R')

#define XPCI_READWRITE _IOWR(XPCI_MAGIC, 0, struct XPCI)
 
#ifdef __cplusplus
}
#endif


#endif 
