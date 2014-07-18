// $Id: GaugeFactory.h,v 1.4 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and S. Murray					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_GaugeFactory_h_
#define _toolbox_GaugeFactory_h_

#include "toolbox/Gauge.h"
#include <string>
#include <map>

#include "toolbox/exception/Exception.h"
#include "toolbox/Gauge.h"
#include "toolbox/EventDispatcher.h"
#include "toolbox/ActionListener.h"
#include "toolbox/net/URN.h"

namespace toolbox 
{
	
	class GaugeFactory
	{
		public:

		//! Retrieve a pointer to the toolbox::GaugeFactory singleton
		//
		static GaugeFactory* getInstance();

		//! Destroy the manager and destroy all pools.
		//
		static void destroyInstance();

		//! Add a listener to the gauge manager for events that announce that a gauge is made available or revoked
		//
		void addActionListener (toolbox::ActionListener* listener);

		void removeActionListener (toolbox::ActionListener* listener) throw (toolbox::exception::Exception);

		//! Retrieves a list of all guage names that are managed by this factory.
		//
		std::vector<std::string> getGaugeNames();

		//! Create a gauge. It is available until removeGauge() is called.
		//
		toolbox::Gauge* createGauge(toolbox::net::URN& urn)
			throw (toolbox::exception::Exception);
		
		toolbox::Gauge* createGauge(const std::string & name)
			throw (toolbox::exception::Exception);
			
		toolbox::Gauge* createGauge(toolbox::net::URN& urn, double min, double max, double value)
			throw (toolbox::exception::Exception);
		
		toolbox::Gauge* createGauge(const std::string & name, double min, double max, double value)
			throw (toolbox::exception::Exception);
				
		//! Find a gauge that has been created.
		//
		toolbox::Gauge* findGauge(toolbox::net::URN& urn) 
			throw (toolbox::exception::Exception);

		//! Make a pool unaccessible to users of the MemoryPoolFactory.
		/*! The pool is not destroyed, but made unaccessible to the user. Subsequent find
		    operations will not anymore reveal the pool. The pool is finally destroyed and
		    removed from the manager, when the cleanup() function is called.
		    */
		void removeGauge(toolbox::net::URN& urn) 
			throw (toolbox::exception::Exception);

		//! Destroy a gauge
		/*! The gauge is really destroyed and removed from the manager.
		    */
		void destroyGauge(toolbox::net::URN& urn) 
			throw (toolbox::exception::Exception);
			
		//! Cleanup, remove gauges from temporary storage
		//
		void cleanup();

		private:

		// Forbid the empty constructor to avoid that someone instantiates this class
		GaugeFactory();
		~GaugeFactory();

		std::map<std::string, toolbox::Gauge*, std::less<std::string> > gauges_;
		std::list<toolbox::Gauge*> unusedGauges_;
		static GaugeFactory* instance_;

		toolbox::EventDispatcher dispatcher_;
	};

	GaugeFactory* getGaugeFactory();
}


#endif

