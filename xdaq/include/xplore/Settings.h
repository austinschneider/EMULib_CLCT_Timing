// $Id: Settings.h,v 1.3 2008/07/18 15:28:44 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xplore_Settings_h_
#define _xplore_Settings_h_

#include <string>
#include "xplore/exception/Exception.h"
#include "xoap/domutils.h"

#define XPloreSettingsNS "http://xdaq.web.cern.ch/xdaq/xsd/2006/XPlore-Settings-10"


namespace xplore
{
	//! Forward declaration
	//
	class Application;

	class Settings
	{
		public:
		
		/*! Settings CTOR takes pointer to XPlore to be able to 
		 *  change/read the settings
		 */
		Settings(xplore::Application* xplore);
		
		//! Remove all loaded flashlist configurations from memory
		//
		void reset();
				
		//! Load the XPlore settings from a file
		//
		void load(std::string url) throw 
			(xplore::exception::Exception);

		//! Save the XPlore settings to a file
		//
		void save(const std::string& filename) 
			throw (xplore::exception::Exception);		
		
		protected:
		
		DOMDocument* loadDOM (const std::string& pathname) throw (xcept::Exception);
		xplore::Application* xplore_;	
	};
}

#endif
