// $Id: MonitorSettingsFactory.h,v 1.4 2008/07/18 15:28:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xmas_MonitorSettingsFactory_h_
#define _xmas_MonitorSettingsFactory_h_

#include <string>
#include <vector>

#include "xmas/MonitorSettings.h"

namespace xmas
{
	class MonitorSettingsFactory
	{
		public:
		
		//! Convert DOM document into memory objects
		//
		static std::vector<xmas::MonitorSettings *> create(DOMDocument* doc) 
			throw (xmas::exception::Exception);

	};
}

#endif
