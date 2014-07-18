// $Id: HostInfoImpl.h,v 1.1 2009/05/08 13:01:31 rmoser Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_HostInfoImpl_
#define _toolbox_HostInfoImpl_

//
// Implementation of the Process interface for Linux
//
//#include <string>
//#include <fstream>
//#include <unistd.h> // needed for pid_t
//#include <sys/types.h>

#include "toolbox/HostInfo.h"
#include "toolbox/exception/Exception.h"

// JIFFIES is Linux way to calculate process time
// in 'normal' Linux (x86) a Jiffie is 1/100 of a second
// the value varies in different implementations.
// TODO: get Jiffie value from kernel. See procps package
//
//#define JIFFIES 100

/**
 * This class reads infos about the cpu utilisation of a thread from proc
 */
namespace toolbox {

typedef struct
{
	unsigned long long user_;
	unsigned long long nice_;
	unsigned long long system_;
	unsigned long long idle_;
	unsigned long long iowait_;
	unsigned long long irqwait_;
	unsigned long long softirqwait_;
	unsigned long long all_;
}cpuinfo_t;

class HostInfoImpl: public toolbox::HostInfo
{
	std::ifstream* host_info;

public:

	//! Constructor opens /proc/stat file
	HostInfoImpl () throw (toolbox::exception::Exception);
    
    	//! Destructor closes /proc/stat file
    	~HostInfoImpl();
    
    	//! Take a new sample of process information values
	void sample();
	
	//! Return las sample duration in seconds and fractions of a second
	double sampleDuration();
    
    	//! Dump samled values to standard output
	void show();

	//! \returns Returns the cpuusage in percent
	double getCpuUsage();

    protected:
	//! Number of jiffies per second
	long jiffies_;
	size_t ncpu_;
 
    	// values than can be retrieved from /proc/stat
	std::vector<cpuinfo_t> old_;
	std::vector<cpuinfo_t> new_;

	// Temporary storage for sampled data
	// used for statistics, e.g. CPU%
	std::vector<double> cpuUsage_;

	double last_sample_time_; // a time stamp (in seconds since 1970)
	time_t last_process_time_; // last processes CPU usage time in seconds
	double last_sample_duration_; // last sample duration in seconds and fractions of a second
};

}

#endif

