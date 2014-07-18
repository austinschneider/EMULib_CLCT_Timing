// $Id: Output.h,v 1.4 2008/07/18 15:28:15 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xgi_Output_h_
#define _xgi_Output_h_

#include "cgicc/Cgicc.h"
#include "cgicc/HTTPResponseHeader.h"
#include <map>
#include <iostream>
#include <sstream>
#include <string>

namespace xgi
{	
	class Output: public std::ostringstream
	{
		public:

		Output();

		//! Get a reference to the HTTP header to be able to set values
		//
		cgicc::HTTPResponseHeader& getHTTPResponseHeader();
		
		//! Set a new HTTP header to the stream
		//
		void setHTTPResponseHeader(const cgicc::HTTPResponseHeader& header);
		
		private:
		
		cgicc::HTTPResponseHeader header_;		
	};
}
#endif
