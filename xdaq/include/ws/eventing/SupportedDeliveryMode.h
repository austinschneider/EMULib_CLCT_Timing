// $Id: SupportedDeliveryMode.h,v 1.4 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_SupportedDeliveryMode_h_
#define _ws_eventing_SupportedDeliveryMode_h_

#include <list>
#include <string>
#include "ws/eventing/exception/InternalError.h"
#include "ws/eventing/exception/fault/DeliveryModeRequestedUnavailable.h"

namespace ws
{

namespace eventing
{ 
 
class SupportedDeliveryMode
{
	public:
	
	// SupportedDeliveryMode();
	
	SupportedDeliveryMode(std::list<std::string>  & modes);

	std::list<std::string>& getModes ();
	
	void setModes ( std::list<std::string>  & value);
	
	bool isSupported(const std::string& mode, bool throwex) 
		throw (ws::eventing::exception::InternalError, 
		       ws::eventing::exception::fault::DeliveryModeRequestedUnavailable);

	protected:
	
	std::list<std::string> modes_;
};

}
}    

#endif
