/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2007, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: L. Orsini, A. Petrucci                                       *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _pt_http_HeaderField_h_
#define _pt_http_HeaderField_h_

#include "xdata/Bag.h"
#include "xdata/String.h"
#include "xdata/Vector.h"

namespace pt
{

namespace http 
{

//! this is a Bag for one Header field 
//
class HeaderField 
{
	public:
        
	void registerFields(xdata::Bag<HeaderField>* bag)
	{
		bag->addField ("name", &name);
		bag->addField ("value", &value);
	}

	xdata::String name;
	xdata::String value;
};

}

}

#endif

