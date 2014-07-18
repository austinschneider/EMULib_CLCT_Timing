// $Id: AbstractBag.h,v 1.5 2008/07/18 15:28:07 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_AbstractBag_h_
#define _xdata_AbstractBag_h_

#include <string>
#include "xdata/exception/Exception.h"
#include "xdata/Serializable.h"


namespace xdata {

class AbstractBag
{
	public:
	virtual ~AbstractBag()
	{
	}

	virtual xdata::Serializable * getField(const std::string & name) = 0;
	virtual void addField(const std::string & name, xdata::Serializable* s) throw (xdata::exception::Exception) = 0;
	
};

} // end namescape xdata

#endif



