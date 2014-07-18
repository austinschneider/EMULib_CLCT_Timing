// $Id: ClassesTable.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_ClassesTable_h_
#define _xdaq_util_ClassesTable_h_

#include <string>
#include <map>


#include "xdaq/exception/ClassNotFound.h"
#include "xdaq/exception/DuplicateClass.h"

#include "xdaq/util/ClassDescriptor.h"


namespace xdaq {

namespace util {

class ClassesTable
{
	public:
	
	// DTOR
	~ClassesTable()
	{
		std::map<std::string, xdaq::util::ClassDescriptor*, std::less<std::string> >::iterator i;
		for ( i =  classes_.begin(); i != classes_.end(); i++ )
		{
			delete (*i).second;

		}
	}
	
	//! Create a new class with name.
        /*! A device is uniquely identified by its name, e.g. RoundTrip, HelloWorld */
	xdaq::util::ClassDescriptor* createClass(const std::string & name, 
                                                const std::string & info 
                                                )
                                        throw  (xdaq::exception::DuplicateClass )
	{
		if ( classes_.find(name) == classes_.end() ) 
		{
			classes_[name] = new xdaq::util::ClassDescriptor(name,info);
			return classes_[name];
		}
		else
		{
			std::string msg = toolbox::toString("Device name %s already existing", name.c_str());
			XCEPT_RAISE(xdaq::exception::DuplicateClass, msg);
		}	
	}
	
	//! Remove a class descriptor by name 
 	void removeClass(const std::string & name) throw (xdaq::exception::ClassNotFound)
	{
		if ( classes_.find(name) != classes_.end() ) 
		{
			xdaq::util::ClassDescriptor* d = classes_[name];
			delete d;
			classes_.erase(name);
		}
		else
		{
			std::string msg = toolbox::toString("No descriptor for name % found",name.c_str());
			XCEPT_RAISE(xdaq::exception::ClassNotFound, msg);
		}
	}
	
	//! Retrieve a class by indicating the name 
 	xdaq::util::ClassDescriptor*  getClassDescriptor(const std::string & name) throw (xdaq::exception::ClassNotFound)
	{
		if ( classes_.find(name) != classes_.end() ) 
		{
			return classes_[name];

		}
		else
		{
			std::string msg = toolbox::toString("No descritptor for name % found",name.c_str());
			XCEPT_RAISE(xdaq::exception::ClassNotFound, msg);
		}
	}
	
	std::vector<xdaq::util::ClassDescriptor*>  getClasses() 
	{
		std::vector<xdaq::util::ClassDescriptor*> classes;

		std::map<std::string, xdaq::util::ClassDescriptor*, std::less<std::string> >::iterator i;
		for ( i =  classes_.begin(); i != classes_.end(); i++ )
		{
			classes.push_back((*i).second);

		}
		return classes;

	}
	
	private:
	
	std::map<std::string, xdaq::util::ClassDescriptor*, std::less<std::string> > classes_;
	
};
}
}

#endif
