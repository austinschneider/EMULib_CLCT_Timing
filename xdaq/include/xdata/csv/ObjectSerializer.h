// $Id: ObjectSerializer.h,v 1.3 2008/07/18 15:28:09 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_csv_ObjectSerializer_h_
#define _xdata_csv_ObjectSerializer_h_

#include "xdata/Serializable.h"
#include "xdata/ObjectSerializer.h"
#include "xdata/exception/Exception.h"
#include "xdata/Serializer.h"

namespace xdata {
namespace csv {

class ObjectSerializer : public xdata::ObjectSerializer 
{
	public:
	
	virtual void exportAll(xdata::Serializer* serializer, xdata::Serializable* serializable, std::ofstream& f) = 0;
	
	virtual void import (xdata::Serializer * serializer,  xdata::Serializable * serializable, std::ifstream& f) throw (xdata::exception::Exception) = 0;
};

}}

#endif
