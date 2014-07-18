// $Id: AbstractProperties.h,v 1.3 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_AbstractProperties_h_
#define _xdata_AbstractProperties_h_

#include <string>
#include <map>
#include "xdata/exception/Exception.h"
#include "xdata/Serializable.h"

namespace xdata {

/*!
	Abstract interfaces for the xdata::Properties class.
*/
class AbstractProperties
{
	public:
	virtual ~AbstractProperties()
	{
	}

	//! Retrieve the value of a monitorable property or "" if not found
	//
	virtual std::string getProperty(const std::string & name) = 0;
	
	//! Set a monitorable name/value property pair
	//
	virtual void setProperty(const std::string & name, const std::string & value) = 0;

	//! Returns true if property \param name exists, otherwise false
	//
	virtual bool hasProperty(const std::string & name) = 0;
	
	//! Return the map of properties
	//
	virtual std::map<std::string, std::string, std::less<std::string> >& getProperties() = 0;
};

} // end namescape xdata

#endif



