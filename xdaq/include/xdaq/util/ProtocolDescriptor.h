// $Id: ProtocolDescriptor.h,v 1.3 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_ProtocolDescriptor_h_
#define _xdaq_util_ProtocolDescriptor_h_

#include <string>
#include "xdaq/exception/DuplicateProperty.h"
#include "xdaq/exception/PropertyNotFound.h"

namespace xdaq 
{

namespace util
{

	class ProtocolDescriptor
	{
		public:

		//! Create a protocol with name.
		/*! A protocol is uniquely identified by its name, e.g. tcp, maze, udp */
		ProtocolDescriptor (const std::string & name, const std::string & className ): name_(name), className_(className)
		{
		}

		//! Retrieve the name that uniquely identifies a host 
		std::string getName()
		{
			return name_;
		}
		
		//! Retrieve the class name that implements the protocol 
		std::string getImplementationClass()
		{
			return className_;
		}
		// template for end point construction
		void addProperty(const std::string & name, const std::string & type) throw (xdaq::exception::DuplicateProperty)
		{
			if ( properties_.find(name) == properties_.end() ) 
			{
				properties_[name] = type;
			}
			else
			{
				std::string msg = toolbox::toString("Property name %s already existing", name.c_str());
				XCEPT_RAISE(xdaq::exception::DuplicateProperty, msg);
			}	 
                }
		
		void removeProperty(const std::string & name) throw (xdaq::exception::PropertyNotFound)
                {
		 	if ( properties_.find(name) != properties_.end() )
                        {
                                properties_.erase(name);
                        }
                        else
                        {
                                std::string msg = toolbox::toString("Property name %s not existing", name.c_str());
                                XCEPT_RAISE(xdaq::exception::PropertyNotFound, msg);
                        }
                }


		// retrieve all properties
		std::map<std::string, std::string, std::less<std::string> >  getProperties()
                {
                        return properties_;
                }


		private:

		std::string name_;
		std::string className_;
		std::map<std::string, std::string, std::less<std::string> > properties_;
	};
}	

}

#endif
