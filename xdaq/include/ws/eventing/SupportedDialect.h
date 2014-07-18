// $Id: SupportedDialect.h,v 1.6 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_SupportedDialect_h_
#define _ws_eventing_SupportedDialect_h_

#include <string>
#include <list>

#include "ws/eventing/exception/fault/FilteringNotSupported.h"
#include "ws/eventing/exception/fault/FilteringRequestedUnavailable.h"

namespace ws
{
namespace eventing
{ 
	class SupportedDialect
	{
		public:

		// SupportedDialect();

		virtual ~SupportedDialect();

		SupportedDialect(std::list<std::string>& dialects);

		std::list<std::string> getDialects();

		void setDialects ( std::list<std::string> & value );

		bool isSupported(const std::string& dialect, bool throwex) 
			throw 
			( 
				ws::eventing::exception::fault::FilteringNotSupported, 
				ws::eventing::exception::fault::FilteringRequestedUnavailable 
			);

		protected:

		std::list<std::string> dialects_;
	};
}
}    
#endif
