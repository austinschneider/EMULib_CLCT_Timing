// $Id: stl.h,v 1.6 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_stl_h_
#define _toolbox_stl_h_

#include <set>
#include <algorithm>
#include <iterator>

namespace toolbox 
{
	namespace stl
	{
		template<typename T> std::set<T> intersection(std::set<T>& s1, std::set<T>& s2)
		{
			std::set<T> match;
		  	std::insert_iterator<std::set<T> > iter (match, match.begin());	
			std::set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(), iter);
			return match;
		}
		
		template<typename T> std::set<T> merge (std::set<T>& s1, std::set<T>& s2)
		{
			std::set<T> match;
		  	std::insert_iterator<std::set<T> > iter (match, match.begin());	
			std::set_union(s1.begin(),s1.end(),s2.begin(),s2.end(), iter);
			return match;
		}

		template<typename T> std::set<T> difference (std::set<T>& s1, std::set<T>& s2)
                {
                        std::set<T> match;
                        std::insert_iterator<std::set<T> > iter (match, match.begin());
                        std::set_difference(s1.begin(),s1.end(),s2.begin(),s2.end(), iter);
                        return match;
                }
		
		// case-independent (ci) string less_than returns true if s1 < s2
		//
		struct ci_less : std::binary_function<std::string, std::string, bool>
		{

			// case-independent (ci) compare_less binary function
			struct nocase_compare : public std::binary_function<unsigned char,unsigned char,bool> 
			{
				bool operator() (const unsigned char& c1, const unsigned char& c2) const 
				{ 
					return ::tolower (c1) < ::tolower (c2); }
				};

				bool operator() (const std::string & s1, const std::string & s2) const
				{
					return std::lexicographical_compare (s1.begin (), s1.end (),   // source range
						s2.begin (), s2.end (),   // dest range
						nocase_compare ());  // comparison
				}
		}; // end of ci_less

		// templated version of my_equal so it could work with both char and wchar_t
		template<typename charT>
		struct ciequal {
    			ciequal( const std::locale& loc ) : loc_(loc) {}
    			bool operator()(charT ch1, charT ch2) 
			{
        			return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    			}
			private:
    			const std::locale& loc_;
		};

		
		// find substring (case insensitive)
		size_t cifind( const std::string & str1, const std::string & str2, const std::locale& loc = std::locale() );

		// Usage examples
		// std::string str1 
		// std::string str2 
		//int f1 = toolbox::stl::cifind( str1, str2 );
	}
}

#endif
