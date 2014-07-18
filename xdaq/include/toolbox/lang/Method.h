// $Id: Method.h,v 1.3 2008/07/18 15:27:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_lang_Method_h_
#define _toolbox_lang_Method_h_

#include <string>


namespace toolbox
{
	namespace lang {

		class Method {

			public:

			virtual ~Method()
			{
			}

			virtual std::string type() = 0;
		};

	}
}

#endif
