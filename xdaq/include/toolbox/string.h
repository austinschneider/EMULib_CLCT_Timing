// $Id: string.h,v 1.19 2008/09/19 09:07:10 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_string_h_
#define _toolbox_string_h_

#include <string>
#include <set>
#include <list>
#include <sstream>
#include "toolbox/exception/Exception.h"

namespace toolbox
{
	//! Escape special characters in a string, e.g.: " -> %22
	//
	std::string escape(const std::string& s);

	//! Quote special characters in a string, e.g. " -> \"
	//
	std::string quote(const std::string& s);

	std::string jsonquote(const std::string& s);


	//! Unquote special characters in a string, e.g. \" -> "
	//! Also remove leading and trailing optional quote
	//
	std::string unquote(const std::string& s);

	std::string toString (char * format, ... );

	std::string toString (const char * format, ... );
	
	long toLong (const std::string& n) throw (toolbox::exception::Exception);
	
	unsigned long toUnsignedLong (const std::string& n) throw (toolbox::exception::Exception);

	double toDouble (const std::string& n) throw (toolbox::exception::Exception);
	
	 
	std::string tolower (const std::string& str);
	std::string toupper (const std::string& str);
	std::string trim(const std::string& str) throw (toolbox::exception::Exception);
	void charmask(const  char *input, int len, char *mask) throw (toolbox::exception::Exception);
	std::string trim(const char *c, int len, const char *what, int what_len,  int mode ) throw (toolbox::exception::Exception);
	std::string trim (const std::string& str, std::string what) throw (toolbox::exception::Exception);

	bool startsWith(const std::string& str, const std::string& start);
	bool endsWith(const std::string& str, const std::string& end);

	class StringTokenizer
	{

   		public:

	    	StringTokenizer(const std::string& str, const std::string& delim);
   		~StringTokenizer() {};

    		size_t    countTokens();
    		bool   hasMoreTokens();
    		std::string nextToken();
    		std::string nextToken(const std::string& delim);
    		std::string remainingString();
    		std::string filterNextToken(const std::string& filterStr);

		
		
   		private:

    		std::string  tokenStr_;
    		std::string  delim_;
	};
	
	std::list<std::string> parseTokenList(const std::string& str, const std::string& delim);
	
	std::set<std::string> parseTokenSet(const std::string& str, const std::string& delim);
	
	/*! Convert a \param tokenList into a \returns string separated by a \param delimiter
	*/
	std::string printTokenSet(const std::set<std::string> & tokenList, const std::string& delimiter);

	/*! Convert a \param tokenList into a \returns string separated by a \param delimiter
	*/
	std::string printTokenList(const std::list<std::string> & tokenList, const std::string& delimiter);

	

} // end of namespace toolbox

#endif
