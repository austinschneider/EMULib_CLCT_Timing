// $Id: AutoSizeOutputStreamBuffer.h,v 1.2 2008/07/18 15:28:10 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_exdr_AutoSizeInputStreamBuffer_h_
#define _xdata_exdr_AutoSizeInputStreamBuffer_h_

#include "xdata/exdr/OutputStreamBuffer.h"


namespace xdata {
namespace exdr {

class AutoSizeOutputStreamBuffer: public OutputStreamBuffer
{	
	public:
	
	AutoSizeOutputStreamBuffer() throw (xdata::exception::Exception);
	virtual ~AutoSizeOutputStreamBuffer();
	
	void overflow() throw (xdata::exception::Exception);
	
	char * getBuffer();

	protected:
	
};


}}

#endif
