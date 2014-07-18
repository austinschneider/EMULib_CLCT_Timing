// $Id: Properties.h,v 1.5 2008/07/24 13:38:16 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Properties_h_
#define _xdata_Properties_h_

#include <map>

#include "xdata/Serializable.h"
#include "xdata/exception/Exception.h"
#include "xdata/AbstractProperties.h"


namespace xdata {

class Properties 
	: public std::map<std::string, xdata::Serializable*, std::less<std::string> >, 
	public xdata::Serializable, 
	public xdata::AbstractProperties
{
	public:
	
	Properties() throw (xdata::exception::Exception);
	
	Properties(const Properties& b) throw (xdata::exception::Exception);
	
	virtual ~Properties();
	
	Properties & operator=(const Properties & b) 
		throw (xdata::exception::Exception);
	
	int operator==(const Properties& b);

	int operator!=(const Properties& b);
	
	int equals(const xdata::Serializable& s) 
		throw (xdata::exception::Exception);
	
	std::string type() const;
	
	//! Retrieve the value of a monitorable property
	//
	std::string getProperty(const std::string & name);
	
	//! Set a monitorable name/value property pair
	//
	void setProperty(const std::string & name, const std::string & value);

	//! Returns true if property has \param name property, false otherwise
	//
	bool hasProperty(const std::string & name);
	
	std::string toString() throw (xdata::exception::Exception);

	void fromString(const std::string& value) throw (xdata::exception::Exception);
	
	std::map<std::string, std::string, std::less<std::string> >& getProperties();
		
	private:
	
	std::map<std::string, std::string, std::less<std::string> > properties_;
};

} // end namescape xdata

#endif



