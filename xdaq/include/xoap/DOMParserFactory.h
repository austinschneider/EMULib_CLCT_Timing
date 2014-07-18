// $Id: DOMParserFactory.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and S. Murray					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_DOMParserFactory_h_
#define _xoap_DOMParserFactory_h_

#include <string>
#include "toolbox/BSem.h"
#include "xoap/exception/Exception.h"
#include "xoap/DOMParser.h"

namespace xoap 
{
	class DOMParserFactory
	{
		public:

		static DOMParserFactory* getInstance();

		static void destroyInstance();
		
		bool has(const std::string& name);
		
		xoap::DOMParser* create (const std::string& name) throw (xoap::exception::Exception);
		
		xoap::DOMParser* get (const std::string& name) throw (xoap::exception::Exception);
		
		void destroy (const std::string & name) throw (xoap::exception::Exception);
		
		void lock();
		
		void unlock();

		private:

		DOMParserFactory();
		
		~DOMParserFactory();

		static DOMParserFactory* instance_;
		
		std::map<std::string, xoap::DOMParser*, std::less<std::string> > parsers_;
		
		toolbox::BSem mutex_;
	};

	DOMParserFactory* getDOMParserFactory();
}


#endif

