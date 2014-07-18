// $Id: Utils.h,v 1.15 2008/07/18 15:28:15 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xgi_Utils_h_
#define _xgi_Utils_h_

#include <string>
#include "cgicc/Cgicc.h"
#include "xgi/exception/Exception.h"

namespace xgi
{
	
	class Utils 
	{
		public:
			static const char* DaysOfWeek [];				
			static const char* MonthsOfYear [];
		
			static std::string getResponsePhrase(int code);

			//! Output an error page with the title \param comment. Output an OK button that leads to \param url when clicked
			//
			static void ErrorDialog(std::ostream* out, xcept::Exception& e, const std::string& comment, const std::string& url);

			static std::string getFailurePage(const std::string& failure, const std::string& comment);
			static std::string getSimpleFailurePage(const std::string& failure, const std::string& comment);
			
			static void getPageHeader(std::ostream * out, const std::string& title, 
							const std::string& url, const std::string& urn,  const std::string& icon );
							
			static void getPageHeader(std::ostream * out, const std::string& title, const std::string& subtitle, 
							const std::string& url, const std::string& urn,  const std::string& icon );
							
			static void getPageCSS(std::ostream * out);
			static void getPageHeaderWithCSS(std::ostream * out, const std::string& title, 
							const std::string& url, const std::string& urn,  const std::string& icon );
			static void getPageHeaderWithCSS(std::ostream * out, const std::string& title, const std::string& subtitle,
							const std::string& url, const std::string& urn,  const std::string& icon );					
			//deprecated					
			
			static void getPageHeader(std::ostream& out, const std::string& title, const std::string& id = "");
			static std::string getCurrentTime();

			
			static void getPageFooter(std::ostream& out);
			static void getPageFooterWithCSS(std::ostream& out);
			
			//! Retrieve a form element by giving its \param name. Return an interator or throw if element not found
			static cgicc::const_form_iterator getFormElement(const cgicc::Cgicc& cgi, const std::string& name) 
				throw (xgi::exception::Exception);
			
			
			//! Retrieve a form element by giving its \param name. Return an interator or throw if element not found
			static bool hasFormElement(const cgicc::Cgicc& cgi, const std::string& name); 
			
			/*! Renders a folder/file like widget that is clickable and can be used to make a browser
			    \param out is an HTTP output stream used to render the HTML code
			    \param title is the title to be displayed under the icon
			    \param url is the base url that the user is re-directed to when clicking the icon
			    \param command is the command appended to the url
			    \param icon is the path to the icon to be displayed
			    \param tooltip is additional text rendered as a tooltip
			*/
			static void getWidget
			(
				std::ostream      * out, 
				const std::string & text, 
				const std::string & tooltip,
				const std::string & url, 
				const std::string & command, 
				const std::string & icon
			);
				
		};

}

#endif
