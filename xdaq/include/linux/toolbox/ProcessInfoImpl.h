// $Id: ProcessInfoImpl.h,v 1.5 2008/07/18 15:27:30 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_ProcessInfoImpl_
#define _toolbox_ProcessInfoImpl_

//
// Implementation of the Process interface for Linux
//
//#include <string>
//#include <fstream>
//#include <unistd.h> // needed for pid_t
//#include <sys/types.h>

#include "toolbox/ProcessInfo.h"
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

class ProcessInfoImpl: public toolbox::ProcessInfo
{

    /**
     * Checks if a thread exists by trying to open its file in proc
     */
    bool isThreadExisting();

    pid_t thread_pid;
    char proc_cpu_file[32];
    std::ifstream* cpu_info;

  public:

	//! Constructor opens /proc/pid/stat file
    	ProcessInfoImpl (pid_t pid) throw (toolbox::exception::Exception);
    
    	//! Destructor closes /proc/pid/stat file
    	~ProcessInfoImpl();
    
    /**
     * \returns Returns the virtual memory used by the process, default unit is MBytes
     */
	size_t vsize();
    
    /**
     * \returns Returns the resident memory used by the process, default unit if MBytes
     */
	size_t rsize();
	
	//! Return the process id
	pid_t pid();
    
    	//! Return the commandline that was used to start this process
	std::string command();
    
    	//! Return the cpu usage in % over the last sample period
	double cpuUsage ();
    
    	//! Take a new sample of process information values
	void sample();
	
	//! Return las sample duration in seconds and fractions of a second
	double sampleDuration();
    
    	//! Dump samled values to standard output
	void show();
    
    protected:
    
    	// values than can be retrieved from /proc/pid/stat
	std::string command_;
	char state_;
	pid_t ppid_;
	gid_t pgrp_;
	ssize_t session_;
	ssize_t tty_;
	ssize_t tpgid_;
	size_t flags_;
	size_t minflt_;
	size_t cminflt_;
	size_t majflt_;
	size_t cmajflt_;
	time_t utime_;
	time_t stime_;
	time_t cutime_;
	time_t cstime_;
	ssize_t counter_;
	ssize_t priority_;
	size_t timeout_;
	size_t itrealvalue_;
	time_t starttime_;
	size_t vsize_;
	size_t rss_;
	size_t rlim_;
	size_t startcode_;
	size_t endcode_;
	size_t startstack_;
	size_t kstkesp_;
	size_t kstkeip_;
	ssize_t signal_;
	double blocked_;
	ssize_t sigignore_;
	ssize_t sigcatch_;
	size_t wchan_;

	// newly introduced fields with linux 2.4.21 >>
	size_t nswap_;
        size_t cnswap_;
        ssize_t exit_signal_;
        ssize_t task_;
        size_t rt_priority_;
        size_t policy_;
        size_t group_utime_;
        size_t group_stime_;
        size_t group_cutime_;
        size_t group_cstime_;

	
	double cpu_percent_; // cpu usage of process in % since last sample time
	
	
	// Temporary storage for sampled data
	// used for statistics, e.g. CPU%
	time_t last_stime_; // in jiffies = 1/100 sec
	time_t last_utime_; // in jiffies = 1/100 sec
	
	double last_sample_time_; // a time stamp (in seconds since 1970)
	time_t last_process_time_; // last processes CPU usage time in seconds
	double last_sample_duration_; // last sample duration in seconds and fractions of a second
	
	// Helper function to calculate process CPU% usage
	void calcCPUUsage(double sample_duration);
	
	size_t pageSize_; // system page size
	size_t ncpu_; // number of CPUs in the system
};

}

#endif

