// $Id: HostDescriptor.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_HostDescriptor_h_
#define _xdaq_util_HostDescriptor_h_

#include <string>

namespace xdaq 
{

namespace util
{

	class HostDescriptor
	{
		public:

		//! Create a new host with name.
		/*! A context is uniquely identified by its name, e.g. lxcmd112 */
		HostDescriptor (const std::string & name, const std::string & info ): name_(name), info_(info)
		{
		}
		


		//! Retrieve the name that uniquely identifies a host 
		std::string getName()
		{
			return name_;
		}
		
		//! Retrieve the name that uniquely identifies a host 
		std::string getInfo()
		{
			return info_;
		}

		private:

		std::string name_;
		std::string info_;
	};
}	

}

#endif
