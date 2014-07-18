// $Id: ItemDefinition.h,v 1.5 2008/07/18 15:28:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_ItemDefinition_h_
#define _xmas_ItemDefinition_h_

#include <vector>
#include <set>
#include <map>
#include <string>
#include "toolbox/stl.h"
#include "xmas/exception/Exception.h"
#include "toolbox/Properties.h"
#include "xoap/domutils.h"

namespace xmas
{
	
	class ItemDefinition: public toolbox::Properties
	{
		public:
		
		ItemDefinition(DOMNode* item) throw (xmas::exception::Exception);
		
		virtual ~ItemDefinition();
		
		
		std::vector<xmas::ItemDefinition*> getItems();
		ItemDefinition* getItem(const std::string & name)  throw (xmas::exception::Exception);
		
		void getNestedDepth(size_t depth, size_t & maxdepth);
		
		protected:
				
		
		std::map<std::string, xmas::ItemDefinition*, toolbox::stl::ci_less> items_;
		
	};
}
#endif	
