// $Id: Browser.h,v 1.4 2008/07/18 15:28:44 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _Browser_h_
#define _Browser_h_

#include "toolbox/Properties.h"

#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "xcept/tools.h"

#include "xslp/DiscoveryService.h"
#include "xplore/Interface.h"
#include <map>
#include <set>
#include <string>
#include <sstream>
#include "xplore/Interface.h"
#include "exception/Exception.h"

namespace xplore 
{
	class Browser
	{	
		public:

			Browser(xplore::Interface* xplore, const std::string &baseurl, std::set<std::string>& zones, const std::string & resourceRoot);

			/*! Display a list of pre-defined search filters
			*/
			void showShortcuts(xgi::Output* out);

			void showServices(xgi::Output* out, const std::string& zone, const std::string& srvtype, const std::string& filter);

			void showProperties(xgi::Output* out, const std::string& url);

			bool hasShortcut (const std::string& name);

			toolbox::Properties* getShortcut (const std::string& name) throw (xplore::exception::Exception);

			toolbox::Properties* createShortcut (const std::string& name) throw (xplore::exception::Exception);

			void deleteShortcut (const std::string& name) throw (xplore::exception::Exception);

			void editShortcut(const std::string& name, xgi::Output* out) throw (xplore::exception::Exception);

			void display(xgi::Output* out);

			void showSearchBar(xgi::Output* out);

			std::map<std::string, toolbox::Properties*>& getShortcuts();

		protected:

		void showWidget
		(
			std::ostream      * out,
			const std::string & target,
			const std::string & text, 
			const std::string & tooltip,
			const std::string & url, 
			const std::string & command, 
			const std::string & icon
		);

			std::map<std::string, toolbox::Properties*> shortcuts_;
			std::string url_; // base url on which all commands are called

			std::set<std::string> comboZones_;
			std::set<std::string> comboServices_;
			xplore::Interface* xplore_;
			std::string httpRootDir_;
	};
}
#endif
