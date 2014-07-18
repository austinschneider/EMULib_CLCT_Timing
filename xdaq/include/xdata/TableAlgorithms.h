// $Id: TableAlgorithms.h,v 1.2 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
#ifndef _xdata_TableAlgorithms_h_
#define _xdata_TableAlgorithms_h_


#include <sstream> 
#include <set>
#include "xdata/Table.h"
#include "xdata/Vector.h"
#include "xdata/UnsignedLong.h"
#include "xdata/UnsignedInteger.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/UnsignedInteger64.h"
#include "xdata/UnsignedShort.h"
#include "xdata/Integer.h"
#include "xdata/Float.h"
#include "xdata/Double.h"
#include "xdata/String.h"
#include "xdata/Boolean.h"
#include "xdata/TimeVal.h"
#include "xdata/Mime.h"

#include "xdata/TableIterator.h"

namespace xdata {

	xdata::Table::iterator find(xdata::Table * destination,  xdata::Table::Row & row, std::set<std::string> & key)
		throw (xdata::exception::Exception);

	void merge(xdata::Table * destination,  xdata::Table * source, std::set<std::string> & key)
		throw (xdata::exception::Exception);
}

#endif
