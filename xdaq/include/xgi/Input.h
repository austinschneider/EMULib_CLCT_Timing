// $Id: Input.h,v 1.3 2008/07/18 15:28:15 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xgi_Input_h_
#define _xgi_Input_h_

#include "cgicc/Cgicc.h"
#include <map>
#include <iostream>
#include <sstream>
#include <string>

namespace xgi
{

	class Input: public cgicc::CgiInput
	{
		public:

		//! Construct an input stream with a pre-filled character buffer
		Input(const char* buffer, size_t length);

		//! Returns the contained stream that can be used for input
		std::istringstream& cin();

		/*! Read \param length characters from the stream into the pre-allocated array \param data.
		     * The function returns the number of characters actually read.
		    */
		size_t read (char* data, size_t length);

		/*! Return the value of a variable named \param varName */
		std::string getenv(const char* varName);

		/*! Put the \param name, \param value pair into the environment of the input stream */
		void putenv(const std::string& name, const std::string& value);

		/*! write \param length characters from the array \param data
		 * 
		 */
		void write(const char* buffer, size_t length);

		protected:

		std::map<std::string, std::string, std::less<std::string> > environment_;

		// string stream that operates over the buffer gine at ctor time
		std::stringstream instream_;
		size_t length_;

	};
	
}

#endif
