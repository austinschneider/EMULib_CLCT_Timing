// $Id: Alarm.h,v 1.2 2008/11/13 14:30:51 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_utils_Alarm_h_
#define _sentinel_utils_Alarm_h_

#include <string>
#include "xdata/exception/Exception.h"
#include "xdata/Serializable.h"
#include "xdaq/Application.h"

namespace sentinel {
namespace utils {

//
// XCEPT_DECLARE(toolbox::exception::Exception, "error message", e);
// sentinel::utils::Alarm * a = new sentinel::utils::Alarm("severity",e);
//
// sentinel::utils::Alarm * a = new sentinel::utils::Alarm(e);
class Alarm: public xdata::Serializable
{	
	public:
	
		Alarm(const std::string & severity, xcept::Exception & e, xdaq::Application * owner);
		
			
		virtual ~Alarm();
		
		void setValue(const xdata::Serializable & s);
		
		// Comparison operators inherited from Serializable
		int equals(const xdata::Serializable & s);
		

		
		std::string type() const;

		std::string toString () throw (xdata::exception::Exception);
		void  fromString (const std::string& value) throw (xdata::exception::Exception);
	
		xcept::Exception & getException();

		xdaq::Application * getOwnerApplication();
		
		private:
		Alarm() {}

		
		std::string severity_;	
		xcept::Exception e_;
		xdaq::Application * owner_;
};


}} // end namespace 

#endif
