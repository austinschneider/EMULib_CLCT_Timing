// $Id: Object.h,v 1.2 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_Object_h_
#define _xdaq_Object_h_

#include <string>
#include "xdaq/Application.h"

namespace xdaq
{
class Object
{
	public:

	//! Constructor which requires context application object
	//
	Object(xdaq::Application * owner);
	
	//! Returns the owner for this object
	//
	xdaq::Application * getOwnerApplication();

	virtual ~Object();
	
	private:
	
	xdaq::Application * owner_;
};
}
#endif
