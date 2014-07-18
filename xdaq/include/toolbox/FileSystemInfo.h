// $Id: FileSystemInfo.h,v 1.3 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_FileSystemInfo_h_
#define _toolbox_FileSystemInfo_h_

#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"
#include "toolbox/TimeVal.h"
#include "toolbox/exception/Unsupported.h"
#include "toolbox/exception/ReadError.h"
#include "toolbox/exception/NotFound.h"

#include <sys/types.h>
#include <unistd.h> // needed for pid_t
#include <string>
#include <set>

namespace toolbox
{
	/*! Abstract interface that gives access to a process. */
	class FileSystemInfo
	{
		public:
		
		typedef toolbox::mem::CountingPtr<FileSystemInfo, toolbox::mem::ThreadSafeReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;
		
		virtual ~FileSystemInfo() {}
		
		 /**
     		* \returns Returns a set with the names of available file systems
    		 */
		virtual std::set<std::string> getFileSystems() 
			throw (toolbox::exception::ReadError) = 0;

		/**
		 * \returns the state of the file system, e.g. 'OK', 'error', 'no size', 'unlimited size'
		 * Used to interpret the the file system size parameters
		 */
		virtual std::string state(const std::string& fs)
			throw (toolbox::exception::NotFound,
				toolbox::exception::Unsupported) = 0;

		/**
     		* \returns Returns the available space on the file system \param fs
		   The \param unit may be:
		   	B.....Bytes
			kB....kilo Bytes
			MB....Mega Bytes
			GB....Giga Bytes
			%.....percent
     		*/
		virtual double available(const std::string& fs, const std::string& unit) 
			throw (toolbox::exception::NotFound,
				toolbox::exception::Unsupported) = 0; 

		/**
     		* \returns Returns the used space on the file system \param fs
		   The \param unit may be:
		   	B.....Bytes
			kB....kilo Bytes
			MB....Mega Bytes
			GB....Giga Bytes
			%.....percent
     		*/
		virtual double used(const std::string& fs, const std::string& unit) 
			throw (toolbox::exception::NotFound,
				toolbox::exception::Unsupported) = 0; 
		
		/**
     		* \returns Returns the total (used+available) space on the file system \param fs
		   The \param unit may be:
		   	B.....Bytes
			kB....kilo Bytes
			MB....Mega Bytes
			GB....Giga Bytes
			%.....percent
     		*/
		virtual double total(const std::string& fs, const std::string& unit) 
			throw (toolbox::exception::NotFound,
				toolbox::exception::Unsupported) = 0; 

		//! Gather the file system information, \returns the sample time
		//
		virtual toolbox::TimeVal sample () 
			throw (toolbox::exception::ReadError) = 0;
		
		//! \returns the last sample duration in seconds and fraction of a second
		//
		virtual double sampleDuration () = 0;
		
		//! \returns the last sample time
		//
		virtual toolbox::TimeVal sampleTime () = 0;

		//! Dump process information to stdout
		virtual void show () = 0;
	};

} // end of toolbox namespace

#endif
