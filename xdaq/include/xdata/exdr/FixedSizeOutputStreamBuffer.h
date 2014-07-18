// $Id: FixedSizeOutputStreamBuffer.h,v 1.6 2008/07/18 15:28:11 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_exdr_FixedSizeOutputStreamBuffer_h_
#define _xdata_exdr_FixedSizeOutputStreamBuffer_h_

#include "xdata/exdr/OutputStreamBuffer.h"


namespace xdata {
namespace exdr {

class FixedSizeOutputStreamBuffer: public OutputStreamBuffer
{	
	public:
	
	FixedSizeOutputStreamBuffer(char* buf, unsigned int size);
	virtual ~FixedSizeOutputStreamBuffer();
	
	void overflow() throw (xdata::exception::Exception);
	
};


}}

#endif
