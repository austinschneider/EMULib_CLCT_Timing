// $Id: Gauge.h,v 1.3 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and S. Murray					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_Gauge_h_
#define _toolbox_Gauge_h_

#include <iostream>
#include "BSem.h"
#include "toolbox/ActionListener.h"
#include "toolbox/exception/Exception.h"
#include "toolbox/ActionListener.h"
#include "toolbox/EventDispatcher.h"

namespace toolbox 
{
	class Gauge
	{
		public:
		
		Gauge();

		Gauge(const double min, const double max, const double value)
			throw (toolbox::exception::Exception);
		~Gauge();

		//! Perform thread safe locking
		//
 		void lock ();

		//! Unlock the previous lock
		//
		void unlock ();

		void addThreshold ( const std::string& name, const double v )
			throw (toolbox::exception::Exception);
			
		void removeThreshold ( const std::string& name )
			throw (toolbox::exception::Exception);
			
		double getThreshold ( const std::string& name )
			throw (toolbox::exception::Exception);

		bool isThresholdExceeded (const std::string& name)
			throw (toolbox::exception::Exception);

		void init(const double min, const double max, const double value)
			throw (toolbox::exception::Exception);

                double getMinValue();
                double getMaxValue();

		//! Set the current value of the gauge to \param v
		/*  This function is not lock protected
			\sa getValue() 
			\sa lock()
			\sa unlock()
		*/
                void setValue(const double v)
			throw (toolbox::exception::Exception);

		//! Get the current value of the gauge 
		/*  This function is not lock protected
			\sa setValue() 
			\sa lock()
			\sa unlock()
		*/
                double getValue();

		void incValue(const double inc)
			throw (toolbox::exception::Exception);

		void decValue(const double dec)
			throw (toolbox::exception::Exception);

		//! Add a listener to the gauge for threshold events
		//
		void addActionListener (toolbox::ActionListener* listener);
			
		//! Remove a listener
		//
		void removeActionListener (toolbox::ActionListener* listener)
			throw (toolbox::exception::Exception);
			
		protected:
		
		double min_;
		double max_;		
		double value_;
		std::map <double, std::string, std::less<double> > thresholds_;
		BSem mutex_;
		toolbox::EventDispatcher dispatcher_;
	};
}

#endif
