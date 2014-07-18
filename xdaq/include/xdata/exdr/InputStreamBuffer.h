// $Id: InputStreamBuffer.h,v 1.3 2008/07/18 15:28:11 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_exdr_InputStreamBuffer_h_
#define _xdata_exdr_InputStreamBuffer_h_

#include "xdata/exdr/StreamBuffer.h"

namespace xdata {
namespace exdr {

class InputStreamBuffer:  public xdata::exdr::StreamBuffer
{
	protected:
	
	InputStreamBuffer(char* buf, unsigned int  n);
	~InputStreamBuffer();
};


}}

#endif
