// $Id: HeaderCollection.h,v 1.2 2008/07/18 15:27:49 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_HeaderCollection_h_
#define _ws_eventing_HeaderCollection_h_

#include <list>

namespace ws
{
namespace eventing
{
	class AddressHeader
	{
		public:
		
		std::string name;
		std::string namespace;
		std::string value;
	};

	class HeaderCollection : std::list<AddressHeader>
	{
		public:
		
        	std::list<AddressHeader>::iterator find(const std::string& name, const std::string& ns, bool throwex)
		{
		    if (name == "")
        		throw new ArgumentNullException("name");
		    if (ns == "")
        		throw new ArgumentNullException("ns");

			std::list<AddressHeader>::iterator ii;
		    for (ii = this.begin(); ii != this.end(); ++ii)
		    {
        		if ( (*ii).name == name && (*ii).namespace == ns)
        		    return ii;
		    }
		    
		    if(throwex)
        		throw new Exception(string.Format("The header name={0}, ns={1} doesn't exist", name, ns));
		    return this.end();
		}
		
        	std::string getValue( const std::string& name, const std::string& ns, bool throwex)
        	{
            		std::list<AddressHeader>::iterator i = this->find(name, ns, throwex);
			
			// Original code
			//
			// return ah == null ? default(T) : ah.GetValue<T>();
			if (i != this.end())
			{
				return (*i).value;
			}
			else
			{
				return "";
			}            		
        	}
	};
}
}

#endif


