// $Id: Repository.h,v 1.1 2008/09/02 07:11:49 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _statepanel_Repository_h_
#define _statepanel_Repository_h_

#include <string>
#include <list>
#include <set>
#include "state/panel/Repository.h"
#include "state/panel/Entry.h"
#include "state/panel/Notification.h"
#include "state/panel/exception/NotFound.h"

#include "xgi/Output.h"

#include "toolbox/BSem.h"

namespace state
{
namespace panel
{
	class Repository
	{
		public:

		Repository();

		~Repository();

		void store(const state::panel::Notification & e);

		void catalog(xgi::Output* out, const std::string& format, const std::string& mark )
			throw (state::panel::exception::NotFound);

		void retrieve(xgi::Output* out, const std::string& format, const std::string& identifier, const std::string& mark )
			throw (state::panel::exception::NotFound);

		void action(xgi::Output* out, const std::string& action, const std::string& identifier, const std::set<std::string>& uuids )
			throw (state::panel::exception::NotFound);

		std::list<state::panel::Entry> getCatalog(const std::string& mark);

		private:

		toolbox::BSem repositoryLock_;

		std::map<std::string, state::panel::Entry*> entries_;

	};
}
}
#endif

