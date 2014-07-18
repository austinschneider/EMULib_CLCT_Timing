// $Id: regex.h,v 1.5 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_regex_h_
#define _toolbox_regex_h_

#include <iostream>
#include <string>
#include <vector>
#include <regex.h>
#include <exception>
#include <stdexcept>

#define  REGX_PRNT 1    // Print error messages
#define  REGX_HIDE 0    // Hide  error messages

namespace toolbox {

/*!
 Overview:
 ===========================================================================
 
 bool regx_match( const std::string &stl_string, const std::string &pattern )
      throw( bad_alloc, invalid_argument );
 
 bool regx_match( const std::string &stl_string, const std::string &pattern,
                 std::vector<std::string> &sub_strings )
      throw( bad_alloc, invalid_argument );

*/


/*! Provide regular expression searches to Standard Template Library (STL) string objects.		     
   \param stl_string is the STL string object that will be searched.					     
   \param pattern is the regular expression pattern used in the search.					     
   \return true if there is a regular expression match, false otherwise. 				     
   \exception If there are any errors with the regular expression   
               pattern, this method will throw one of the exceptions 
               listed in the exception specification.		     
               Other possible exceptions are those that may be       
               thrown by the STL string or vector classes.	     
        							     
*/
bool regx_match_nocase( const std::string &stl_string, const std::string &pattern )
 	throw( std::bad_alloc, std::invalid_argument );
	
bool regx_match( const std::string &stl_string, const std::string &pattern )
 	throw( std::bad_alloc, std::invalid_argument );
	
bool regx_match( const std::string &stl_string, const std::string &pattern , int cflags)
     	throw( std::bad_alloc, std::invalid_argument );


/*! Provide regular expression searches to Standard Template Library (STL) string objects.		 
	\param stl_string is the STL string object that will be searched.						 
	\param pattern is the regular expression pattern used in the search. 					 
	\param sub_strings is an STL vector of STL string objects that represents any substring matches within the	 
	    regular expression. 	 
	\return true if there is a regular expression match, false otherwise.					 
	\exception If there are any errors with the regular expression  
	    pattern, this method will throw one of the exceptions
	    listed in the exception specification.		 
	    Other possible exceptions are those that may be	 
	    thrown by the STL string or vector classes. 	 
								 
	 \note  Details on "sub_strings":				 
	    sub_strings[0] = the substring within "stl_string"   
	      that is matched by the entire regular expression.  
	    Any other strings in "sub_strings" represent	 
	      substrings within "stl_string" that are matched by 
	      parts of the regular expression "pattern" that are 
	      enclosed in parentheses.  			 
	    For example (run on Linux): 			 
	    stl_string = "This 234 is jklfjk my 0...9 string"	 
	    pattern    = "([0-9]+) is(.*?)([0-9]+)"		 
	    sub_strings[0] = "234 is jklfjk my 0...9"		 
	    sub_strings[1] = "234"				 
	    sub_strings[2] = " jklfjk my 0..."  		 
	    sub_strings[3] = "9"				 
								 
	    For those of you who are accustomed to Perl syntax,  
	    sub_strings[1] = $1 				 
	    sub_strings[2] = $2 				 
	    etc.						 
*/
bool regx_match( const std::string &stl_string, const std::string &pattern,
                 std::vector<std::string> &sub_strings )
     throw( std::bad_alloc, std::invalid_argument );


}

/*!
\note Example program

#include <iostream>
#include <string>
#include <vector>
#include "stl_string_regex.h"


int main()
{
    int i = 0;
    vector<string> sub_strings;
    string mystring = "This 234 is jklfjk my 0...9 string";
    string pattern  = "([0-9]+) is(.*?)([0-9]+)";

    try
    {
        if( regx_match( mystring, pattern, sub_strings ) )
        {
            cout << "REGEX MATCH..." << endl;
            for( i = 0; i < sub_strings.size(); i++ )
                cout << "sub_strings[" << i << "] = \"" << sub_strings[i] << "\"" << endl;
        }
        else
            cout << "NO REGEX MATCH" << endl;
    }
    catch( bad_alloc ba )
    {
        cout << ba.what() << endl;
    }
    catch( invalid_argument ia )
    {
        cout << ia.what() << endl;
    }
    catch( ... )
    {
        cout << "some other exception caught" << endl;
    }

    return 0;
}

*/

/*! \note Some helpful regular expressions
  [0-9]        =>  match any digit
  [^0-9]       =>  match any non-digit
  [ \r\t\n\f]  =>  match any whitespace character
  [^ \r\t\n\f] =>  match any non-whitespace character
  [a-zA-Z0-9]  =>  match any alphanumeric character
  [^a-zA-Z0-9] =>  match any non-alphanumeric character
  x{4}         =>  match exactly 4 x's
  x{0,4}       =>  match at most 4 x's
  x{4,6}       =>  match between 4 and 6 x's (inclusive)
  x{4,}        =>  match at least 4 x's
*/

#endif

