// $Id: Settings.h,v 1.2 2008/07/18 15:28:23 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_las_Settings_h_
#define _xmas_las_Settings_h_

#include <vector>
#include <map>
#include <string>
#include "xmas/exception/Exception.h"
#include "toolbox/net/UUID.h"
#include "toolbox/Properties.h"
#include "xoap/domutils.h"

namespace xmas
{
	namespace las
	{
		/*!
			The following properties are allowed in the configuration tag:
			<flash name="flashlist" tag="tag1,tag2,..." haskey="key1,key2,..." filter="xpath" clear="true|false"/>
		*/
		class Settings: public toolbox::Properties
		{
			public:

			Settings() throw (xmas::exception::Exception);

			Settings( DOMNode* flashNode ) throw (xmas::exception::Exception);

			~Settings();

			toolbox::net::UUID& getId();

			protected:

			toolbox::net::UUID id_;		
		};
	}
}
#endif
