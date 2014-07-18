// $Id: Runtime.h,v 1.8 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_Runtime_h_
#define _toolbox_Runtime_h_

#include "toolbox/ActionListener.h"
#include "toolbox/EventDispatcher.h"
#include "toolbox/ProcessInfo.h"
#include "toolbox/FileSystemInfo.h"
#include "toolbox/BSem.h"

#include <signal.h>
// Works on Linux 2.4: atexit()
#include <stdlib.h>
#include <unistd.h>

namespace toolbox 
{

class Runtime
{
	public:
	
	//! Retrieve a pointer to the toolbox::Runtime singleton
	//
	static Runtime* getInstance();

	//! Destroy the Runtime; 
	//
	static void destroyInstance();

	//! Add a listener that is called when the runtime is destroyed or the process is terminated with exit()
	//
	void addShutdownListener (toolbox::ActionListener* listener);

	//! Remove a previously registered shutdown listener
	//
	void removeShutdownListener (toolbox::ActionListener* listener) throw (toolbox::exception::Exception);
	
	//! call shutdown listeners now. An \param event can be passed.
	//
	void fireEvent (toolbox::Event& e);
	
	void enableSignals();
	
	void disableSignals();
	
	void halt(int code);
	
	//! Create a file that contains the current process identifier as a text string in format 'number\n'
	/*! \throws toolbox::exception::Exception if the file cannot be created or written
	    for any reason. A detailed error report is contained in the exception.	
	*/
	void createPidFile(const std::string& filename) throw (toolbox::exception::Exception); 
	
	//! expandPathName expansion produces a vector of words (strings). 
	/*! Word expansion means the process of splitting a string into words 
		and substituting for variables, commands, and wildcards just as the shell does 
	*/
	std::vector<std::string> expandPathName(const std::string & pathname)  throw (toolbox::exception::Exception);
	
	//! expandPathPattern expansion produces a vector of words (strings). 
	/*! Expands path patterns to lists of paths with expressions like *.{txt,doc}
	*/
	std::vector<std::string> expandPathPattern(const std::string & pattern)  throw (toolbox::exception::Exception);

	//! retrieve process id of this process	
	pid_t getPid();
	
	//! \returns a reference counted object for a process id, \throws exception if pid not existing
	//
	toolbox::ProcessInfo::Reference getProcessInfo(pid_t pid) throw (toolbox::exception::Exception);
	
	//! \returns a reference counted object for file system information, \throws exception if information not accessible
	//
	toolbox::FileSystemInfo::Reference getFileSystemInfo() throw (toolbox::exception::Exception);

	private:
	
	// Forbid empty CTOR to avoid that someone instantiates this class
	Runtime();
	~Runtime();
	
	toolbox::EventDispatcher dispatcher_;
	
	static Runtime* instance_;
	
	bool handleSignals_;
	
	protected:
	
	friend void signalCallback(int sig, siginfo_t* info, void* c);
	friend void signalSEGVCallback(int sig, siginfo_t* info, void* c);
	int pendingSignal_;
	siginfo_t* pendingSigInfo_;
	void* pendingContext_;
	BSem mutex_;
	int exitStatus_;
};

Runtime* getRuntime();
void signalCallback(int sig, siginfo_t* info, void* c);
void signalSEGVCallback(int sig, siginfo_t* info, void* c);

}

#endif
