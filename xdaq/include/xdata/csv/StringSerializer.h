// $Id: StringSerializer.h,v 1.3 2008/07/18 15:28:09 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_csv_StringSerializer_h_
#define _xdata_csv_StringSerializer_h_

#include "xdata/csv/ObjectSerializer.h"
#include "xdata/String.h"

namespace xdata {
namespace csv {

class StringSerializer : public xdata::csv::ObjectSerializer  
{
	public:

	std::string type() const;
	void exportAll(xdata::Serializer* serializer, xdata::Serializable* serializable, std::ofstream& f);
	void import (xdata::Serializer * serializer,  xdata::Serializable * serializable, std::ifstream& f)
		throw (xdata::exception::Exception);
};

}}

#endif
