// $Id: Platform.h,v 1.2 2008/07/18 15:28:40 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_filter_Platform_h_
#define _xoap_filter_Platform_h_

namespace xoap
{
namespace filter
{
	class Platform
	{
		public:
		
		//! Can be called many times
		//
		static void initialize();
		
		static void terminate();
		
		private:
		
		static bool initialized_;
	};
}
}
#endif

