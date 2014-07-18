// $Id: Properties.h,v 1.5 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_Properties_h_
#define _toolbox_Properties_h_

#include <map>
#include <vector>
#include <string>

namespace toolbox
{

	class Properties
	{
		public:

		//! Retrieve the value of a  property
		//
		std::string getProperty(const std::string & name);
	
		//! Set a  name/value property pair
		//
		void setProperty(const std::string & name, const std::string & value);		
	
		//! Returns an enumeration of all the keys in this property list
		std::vector<std::string> propertyNames();
		
		//! Returns true if the property \param name exists or false if not
		bool hasProperty (const std::string& name);
		
		//! Remove all entries from the properties container
		void clear();
		
		bool empty();
	
		private:
	
		std::map<std::string, std::string, std::less<std::string> > properties_;
		
	};

}

#endif
