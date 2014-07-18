// $Id: Request.h,v 1.2 2008/07/18 15:28:37 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_utils_Request_h_
#define _xmas_utils_Request_h_

#include "ws/addressing/Headers.h"


namespace xmas 
{
namespace utils 
{

	class Request
	{
		public:
		
		Request()
		{
		}

		protected:
		
		ws::addressing::Headers aheaders_;


	};
}}

#endif
