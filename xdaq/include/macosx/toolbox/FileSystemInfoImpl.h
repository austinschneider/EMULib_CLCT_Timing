// $Id: FileSystemInfoImpl.h,v 1.4 2008/07/18 15:27:30 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_FileSystemInfoImpl_h_
#define _toolbox_FileSystemInfoImpl_h_

#include "toolbox/FileSystemInfo.h"

namespace toolbox
{
	/*! Abstract interface that gives access to a process. */
	class FileSystemInfoImpl: public toolbox::FileSystemInfo
	{
		protected:
		
		typedef struct Record
		{
			size_t available;
			size_t total;
			size_t blocksize;
			std::string state;
		} RecordType;
		
		toolbox::TimeVal sampleTime_;
		std::map<std::string, Record> fs_;
		
		// helper, returns value in unit, parameter value expected in Bytes
		//
		double convertTo (double value, size_t blocksize, const std::string& unit)
			throw (toolbox::exception::Unsupported);
		
		public:
		
		FileSystemInfoImpl();
		
		~FileSystemInfoImpl();
		
		std::set<std::string> getFileSystems()
			throw (toolbox::exception::ReadError);
			
		std::string state(const std::string& fs)
			throw (toolbox::exception::NotFound,
				toolbox::exception::Unsupported);

		double available(const std::string& fs, const std::string& unit)
			throw (toolbox::exception::NotFound,
				toolbox::exception::Unsupported);
		 
		double used(const std::string& fs, const std::string& unit)
			throw (toolbox::exception::NotFound,
				toolbox::exception::Unsupported);
		
		double total(const std::string& fs, const std::string& unit)
			throw (toolbox::exception::NotFound,
				toolbox::exception::Unsupported); 

		toolbox::TimeVal sample () 
			throw (toolbox::exception::ReadError);
		
		double sampleDuration ();
	
		toolbox::TimeVal sampleTime ();
	
		void show ();
	};

} // end of toolbox namespace

#endif
