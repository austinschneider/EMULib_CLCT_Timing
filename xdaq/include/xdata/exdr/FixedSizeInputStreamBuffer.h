// $Id: FixedSizeInputStreamBuffer.h,v 1.5 2008/07/18 15:28:11 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_exdr_FixedSizeInputStreamBuffer_h_
#define _xdata_exdr_FixedSizeInputStreamBuffer_h_

#include "xdata/exdr/InputStreamBuffer.h"


namespace xdata {
namespace exdr {

class FixedSizeInputStreamBuffer: public InputStreamBuffer
{	
	public:
	
	FixedSizeInputStreamBuffer(char* buf, unsigned int size);
	
	void overflow() throw (xdata::exception::Exception);
	
};


}}

#endif
