// $Id: ProcessInfo.h,v 1.4 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_ProcessInfo_h_
#define _toolbox_ProcessInfo_h_

#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"

#include <sys/types.h>
#include <unistd.h> // needed for pid_t
#include <string>

namespace toolbox
{
	/*! Abstract interface that gives access to a process. */
	class ProcessInfo
	{
		public:

        /*! Minumum sample time in seconds. If \function sample() is called at
            a higher rate, sampling does not take place until the minSampleTime
            is elapsed. Therefore it does not make sense to call \function sample()
            more often then this specified constant.
        */
        static const size_t minSampleTime = 5;
		
		typedef toolbox::mem::CountingPtr<ProcessInfo, toolbox::mem::ThreadSafeReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;
		
		virtual ~ProcessInfo() {}
		
		 /**
     		* \returns Returns the virtual memory used by the process, unit is Bytes
    		 */
		virtual size_t vsize() = 0;

		/**
     		* \returns Returns the resident memory used by the process, unit is Bytes
     		*/
		virtual size_t rsize() = 0; 

		//! Return process id
		virtual pid_t pid() = 0; 

		//! Return the command used to start the process
		virtual std::string command () = 0; 

		// start time

		// total time		

		//! returns the CPU usage in percent
		virtual double cpuUsage() = 0;

		//! Sample the process information
		virtual void sample () = 0;
		
		//! Return the last sample duration in seconds and fraction of a second
		virtual double sampleDuration () = 0;

		//! Dump process information to stdout
		virtual void show () = 0;
	};

} // end of toolbox namespace

#endif
