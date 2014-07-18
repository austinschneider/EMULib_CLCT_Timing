// $Id: VectorSerializer.h,v 1.2 2008/07/18 15:28:10 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_csv_VectorSerializer_h_
#define _xdata_csv_VectorSerializer_h_

#include "xdata/Serializable.h"
#include "xdata/exception/Exception.h"
#include "xdata/csv/ObjectSerializer.h"
#include "xdata/csv/Serializer.h"
#include "xdata/Vector.h"

namespace xdata {
namespace csv {

class VectorSerializer : public xdata::csv::ObjectSerializer 
{	
	public:

	std::string type() const;
	void exportAll(xdata::Serializer* serializer, xdata::Serializable* serializable, ofstream& f);
	void import (xdata::Serializer * serializer,  xdata::Serializable * serializable, ifstream& f) 
		throw (xdata::exception::Exception);
};

}}

#endif
