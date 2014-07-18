// $Id: AbstractVector.h,v 1.8 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_AbstractVector_h_
#define _xdata_AbstractVector_h_

#include "xdata/Serializable.h"
#include "xdata/UnsignedInteger.h" 

namespace xdata {

class AbstractVector {

	public:
	
	virtual ~AbstractVector();
	
	virtual size_t elements() = 0;
	virtual Serializable * elementAt(size_t i) = 0;
	virtual void setSize(size_t s) = 0;
	virtual void clear() = 0;
	virtual void erase(size_t i) = 0;
	virtual std::string getElementType() = 0;
};


}

#endif
