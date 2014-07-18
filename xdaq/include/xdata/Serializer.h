// $Id: Serializer.h,v 1.5 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Serializer_h_
#define _xdata_Serializer_h_

#include <string>
#include <map>
#include "xdata/exception/Exception.h"
#include "xdata/ObjectSerializer.h"
#include <iostream>

namespace xdata {

class Serializer {
		
	
	protected:
	
	virtual ~Serializer()
	{
		std::map<std::string, xdata::ObjectSerializer*, std::less<std::string> >::iterator i = objectSerializer_.begin();
		while ( i != objectSerializer_.end() )
		{
			delete (*i).second;
			i++;
		}     	      
	
	}
	
	
	void addObjectSerializer(xdata::ObjectSerializer * serializer) throw (xdata::exception::Exception)
	{
		objectSerializer_[serializer->type()] = serializer;
	}
	
	
	xdata::ObjectSerializer * getObjectSerializer(const std::string & typeName) throw (xdata::exception::Exception)
	{
	
		std::map<std::string, xdata::ObjectSerializer*, std::less<std::string> >::iterator i = objectSerializer_.find(typeName);
		if ( i != objectSerializer_.end() ) 
		{
			return dynamic_cast<xdata::ObjectSerializer*>((*i).second);
		
		}
		std::string msg ="Cannot find object serializer for type: ";
		msg += typeName;
		XCEPT_RAISE(xdata::exception::Exception, msg);
	
	}
	
	
	// Dynamic binder to object handlers by type
	std::map<std::string, xdata::ObjectSerializer*, std::less<std::string> > objectSerializer_;
	

};


}

#endif
