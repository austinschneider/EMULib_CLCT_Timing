// $Id: Netfilter.h,v 1.3 2008/07/18 15:27:20 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_Netfilter_h_
#define _pt_tcp_Netfilter_h_

#include <string>
#include <exception>
#include <stdint.h>
#include "pt/Address.h"
#include "pt/tcp/msg.h"
#include "pt/BinaryListener.h"
#include "pt/tcp/exception/Exception.h"
#include "toolbox/mem/Reference.h"

namespace pt
{
	namespace tcp 
	{
		class Netfilter
		{
			public:

		
			toolbox::mem::Reference * append 
			(
				toolbox::mem::Reference* msg, 
				PTTCP_MESSAGE_FRAME & header,
				uint32_t key
			)
 			throw (pt::tcp::exception::Exception);
						
			size_t clear (uint16_t low);

			private:
			
			typedef struct {
				uint8_t packet;
				uint8_t total;
				size_t  sequence;
				toolbox::mem::Reference* first;
				toolbox::mem::Reference* last;
			} ChainDescriptor;

			std::map<uint32_t, ChainDescriptor>  chains_;
		};
	}
}

#endif
