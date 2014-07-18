// $Id: Interface.h,v 1.5 2008/07/18 15:28:44 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xplore_Interface_h_
#define _xplore_Interface_h_

#include <string>
#include <vector>

#include "toolbox/ActionListener.h"
#include "toolbox/Properties.h"
#include "xdaq/exception/Exception.h"
#include "xplore/Advertisement.h"


namespace xplore
{
	/*! This is an abstract interface to be used by applications
	    if they require discovery services. This abstract interface
	    shall be implemented by xdaq Applications with the className
	    "XPlore"
	*/
	class Interface
	{
		public:
		
		virtual void search (const std::string& type, const std::string& filter,
			std::vector<xplore::Advertisement::Reference>& resultSet) 
			throw (xdaq::exception::Exception) = 0;
			
		/*! Retrieve the properties of a service URL
		*/
		virtual void retrieveProperties
		(
			const std::string& service,
			toolbox::Properties& properties
		) 
		throw (xdaq::exception::Exception) = 0;
		
		virtual void addListener( toolbox::ActionListener * listener, const std::string & service, const std::string  & filter) = 0;
		virtual void removeListener( toolbox::ActionListener * listener ) = 0;
				
		protected:
		
		virtual ~Interface() {}
	};
}

#endif
