// $Id: msg.h,v 1.2 2008/07/18 15:27:20 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_msg_h_
#define _pt_tcp_msg_h_

#include <stdint.h>

/* PTTCP Message Frame common for all messages  */

#define PTTCP_SIGNATURE 0x70746370

typedef struct _PTTCP_MESSAGE_FRAME {
#if defined(LITTLE_ENDIAN__)
	uint32_t signature;
	uint8_t version;
	uint8_t flags;
	uint16_t qos;
	uint32_t length;
	uint32_t sequence;
	uint16_t identification; 
	uint8_t packet; 
	uint8_t total; 
	uint32_t protocol;
#elif defined(BIG_ENDIAN__)
  	uint32_t signature;
	uint16_t qos;
	uint8_t flags;
	uint8_t version;
	uint32_t length;
	uint32_t sequence;
	uint8_t total;
	uint8_t packet;
	uint16_t identification;
	uint32_t protocol;
#endif
} PTTCP_MESSAGE_FRAME, *PPTTCP_MESSAGE_FRAME;

#endif

