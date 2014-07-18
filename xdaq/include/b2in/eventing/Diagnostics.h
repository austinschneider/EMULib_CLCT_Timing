/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2008, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: R. Moser                                                     *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _b2in_eventing_Diagnostics_h_
#define _b2in_eventing_Diagnostics_h_

#include <string>
#include <map>

#include "xdata/UnsignedInteger64.h"
#include "xgi/Output.h"
#include "xgi/Utils.h"


namespace b2in
{
	namespace eventing
	{
		class Diagnostics {
			public:
				Diagnostics();
				virtual ~Diagnostics();

				void incrementInternalLoss(const std::string & topic, const std::string & originator);
				void incrementOutgoingLoss(const std::string & topic, const std::string & originator);
				void incrementMemoryLoss(const std::string & topic, const std::string & originator);
				void incrementEnqueuingLoss(const std::string & topic, const std::string & originator);
				void incrementIncoming(const std::string & topic, const std::string & originator);
				void incrementOutgoing(const std::string & topic, const std::string & originator);

				void enable();
				void disable();

				void writeTo(xgi::Output * out);

			private:
				void increment( const std::string & topic, const std::string & originator, unsigned int type);

				std::vector<xdata::UnsignedInteger64T> initCounters();

				typedef enum
				{
					INTERNAL_LOSS   = 0,
					OUTGOING_LOSS   = 1,
					MEMORY_LOSS     = 2,
					ENQUEUING_LOSS  = 3,
					INCOMING        = 4,
					OUTGOING        = 5
				} COUNTERTYPE;


				std::map<std::string, std::map<std::string, std::vector<xdata::UnsignedInteger64T> > > counters_;
	
				bool enabled_;

		};
	}
}

#endif


