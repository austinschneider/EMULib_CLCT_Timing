// $Id: HostInfo.h,v 1.1 2009/05/08 13:01:31 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_HostInfo_h_
#define _toolbox_HostInfo_h_

#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"

//#include <sys/types.h>
#include <string>

namespace toolbox
{
	/*! Abstract interface that gives access to a process. */
	class HostInfo
	{
		public:

		/*! Minumum sample time in seconds. If \function sample() is called at
		    a higher rate, sampling does not take place until the minSampleTime
		    is elapsed. Therefore it does not make sense to call \function sample()
		    more often then this specified constant.
		*/
		static const size_t minSampleTime = 5;
		
		typedef toolbox::mem::CountingPtr<HostInfo, toolbox::mem::ThreadSafeReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;
		
		virtual ~HostInfo() {}
		
		//! Take a new sample of process information values
		virtual void sample() = 0;
	
		//! Return las sample duration in seconds and fractions of a second
		virtual double sampleDuration() = 0;
    
		//! Dump process information to stdout
		virtual void show () = 0;

		//! \returns Returns the cpuusage in percent
		virtual double getCpuUsage() = 0;
	};

} // end of toolbox namespace

#endif
