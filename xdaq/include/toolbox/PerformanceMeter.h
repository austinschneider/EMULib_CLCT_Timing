// $Id $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_PerformanceMeter_h_
#define _toolbox_PerformanceMeter_h_

#include <string>

#include "toolbox/Chrono.h"
#include "toolbox/string.h"

namespace toolbox {

class PerformanceMeter 
{
	public:
	
	void init(size_t samples);
	
	PerformanceMeter();
			
	//
	//! Take the received amount of data in bytes and
	//! add it to the total amount of received bytes.
	//! After the number of samples specified in
	//! instance variable samples_ has been collected,
	//! print out some statistics information.
	//!
	//! return true if a measurements has been taken false otherwise
	//
	bool addSample(size_t size);

	double bandwidth();
	
	double rate();
	
	double latency();
	
	protected:
	
	double totalMB_;
	double throughput_;
	double rate_;
	double  latency_;
	size_t loopCounter_;
	size_t samples_;
	toolbox::Chrono chrono_;	
};

}

#endif
