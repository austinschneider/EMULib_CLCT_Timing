// $Id: Storage.h,v 1.5 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_Storage_h_
#define _ws_eventing_Storage_h_

#include<string>
#include<map>
#include "toolbox/net/UUID.h"
#include "ws/eventing/PersistedObject.h"

namespace ws
{
namespace eventing
{
	class Storage 
	{
		public:

		Storage(const std::string & name);

		std::string getName();

		void purge();

		std::map<std::string, toolbox::net::UUID> key; // key is a keyword and the value is a unique id
		std::map<std::string, PersistedObject*> val; // key is unique id 

		protected:

		std::string name_;
	};
}
}
#endif


