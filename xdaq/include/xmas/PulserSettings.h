// $Id: PulserSettings.h,v 1.4 2008/07/18 15:28:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_PulserSettings_h_
#define _xmas_PulserSettings_h_

#include <vector>
#include <map>
#include <string>
#include "xmas/PulserEvent.h"
#include "xmas/exception/Exception.h"
#include "toolbox/BSem.h"
#include "toolbox/Properties.h"
#include "toolbox/net/UUID.h"

namespace xmas
{
	class PulserSettings: public toolbox::Properties
	{
		public:
		
		PulserSettings();
		
		~PulserSettings();
		
		void addEvents(DOMDocument * document) throw (xmas::exception::Exception);
		
		//! Create new pulse object, store it in settings and return its id
		//
		toolbox::net::UUID createPulserEvent (DOMNode* node) throw (xmas::exception::Exception);
		
		//! Creation of empty pulse that can be filled later
		toolbox::net::UUID createPulserEvent() throw (xmas::exception::Exception);

		bool hasPulserEvent(toolbox::net::UUID& id);
		
		PulserEvent* getPulserEvent (toolbox::net::UUID& id) throw (xmas::exception::Exception);
		
		void removePulserEvent(toolbox::net::UUID & id) throw (xmas::exception::Exception);
		
		std::map<toolbox::net::UUID, PulserEvent*>& getPulserEvents();
		
		void lock();
		
		void unlock();		
		
		protected:

		std::map<toolbox::net::UUID, PulserEvent*> settings_;
		toolbox::BSem mutex_;
	};
}

#endif
