// $Id: Class.h,v 1.4 2008/07/18 15:27:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_lang_Class_h_
#define _toolbox_lang_Class_h_

#include <string>
#include <vector>
#include <map>
#include "toolbox/lang/Method.h"


namespace toolbox
{
	namespace lang {


		/*!
			Supported Method indexing
			- by name
			- by index (size_t)
		*/
		class Class
		{
			public:

			//! Adding a method by name
			//
			void addMethod (toolbox::lang::Method * m , std::string name);

			//! Remove message by name
			//
			void removeMethod (std::string name);

			//! Adding an method by index
			//
			void addMethod (toolbox::lang::Method * m, size_t fid );

			//! Remove method by index 
			//
			void removeMethod(size_t fid);

			//! Retrieve a method by its name
			//
			toolbox::lang::Method * getMethod(const std::string & name);

			//! Retrieve an method by its index
			//
			toolbox::lang::Method * getMethod(size_t fid);

			//! Retrieve a vector of all registered methods (by index and by name)
			//
			std::vector<toolbox::lang::Method*> getMethods();


			protected:

			// two tables for optimization of lookup: index is ordered by numeric function identifier
			std::vector<toolbox::lang::Method*> indexedMethods_;
			std::map<std::string, toolbox::lang::Method*, std::less<std::string> > namedMethods_;



		};
	}

}

#endif
