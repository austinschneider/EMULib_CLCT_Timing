// $Id: Statistics.h,v 1.2 2008/07/18 15:28:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _b2in_utils_Statistics_h_
#define _b2in_utils_Statistics_h_

#include <string>
#include <map>
#include <vector>

#include "xdata/UnsignedInteger64.h"

namespace b2in
{
	namespace utils
	{
		
		/*! This class holds statistics information about flashlist losses
		*/
		class Statistics
		{
		public:
			Statistics();
			virtual ~Statistics();

			void incrementPulseCounter();
			void incrementFireCounter();
			void incrementInternalLossCounter();
			void incrementCommunicationLossCounter();
			void incrementMemoryLossCounter();
			void incrementUnassignedLossCounter();
			
			xdata::UnsignedInteger64T getPulseCounter();
			xdata::UnsignedInteger64T getFireCounter();
			xdata::UnsignedInteger64T getInternalLossCounter();
			xdata::UnsignedInteger64T getCommunicationLossCounter();
			xdata::UnsignedInteger64T getMemoryLossCounter();
			xdata::UnsignedInteger64T getUnassignedLossCounter();
			
			private:

			xdata::UnsignedInteger64T monitorPulseCounter_;
			xdata::UnsignedInteger64T monitorFireCounter_;

			xdata::UnsignedInteger64T monitorInternalLossCounter_;
			xdata::UnsignedInteger64T monitorCommunicationLossCounter_;
			xdata::UnsignedInteger64T monitorMemoryLossCounter_;
			xdata::UnsignedInteger64T monitorUnassignedLossCounter_;
		};
	}
}

#endif

