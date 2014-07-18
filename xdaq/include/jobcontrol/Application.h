// $Id: Application.h,v 1.11 2008/10/08 12:48:47 gutleber Exp $


#ifndef _jobcontrol_Application_h_
#define _jobcontrol_Application_h_

#include "xdaq/WebApplication.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/NamespaceURI.h"
#include "xdata/Boolean.h"
#include "xdata/UnsignedLong.h"
#include "xdata/UnsignedInteger.h"
#include "xdata/Integer.h"
#include "xdata/String.h"
#include "xdata/Table.h"
#include "xdata/TableIterator.h"

#include "xgi/Utils.h"
#include "xgi/Method.h"
#include "xoap/MessageFactory.h"
#include "xoap/MessageReference.h"
#include "xoap/Method.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/domutils.h"
#include "toolbox/Task.h"

#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/fsm/FailedEvent.h"
#include "toolbox/Properties.h"
#include "toolbox/net/URL.h"


#include "toolbox/task/Timer.h"
#include "toolbox/task/TimerFactory.h"
#include "toolbox/TimeInterval.h"
#include "toolbox/TimeVal.h"

#include "pt/PeerTransportAgent.h"
#include "pt/PeerTransportSender.h"
#include "pt/SOAPMessenger.h"

#include "xdaq/exception/ApplicationNotFound.h"
#include "xcept/tools.h"

#include "toolbox/task/WorkLoopFactory.h"
#include "toolbox/task/WaitingWorkLoop.h"

#include <list>
#include <string>
#include <sstream>
#include <fstream>

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <arpa/inet.h>

// include for RUNControlState Notifier
#include "xdaq2rc/RcmsStateNotifier.h"

#define _jobControl_NMAX 4096
#define _jobControl_MMAX 16
#define _jobControl_MAXENV 100

namespace jobcontrol
{

/**
 * Application responsible for managing xdaq executive objects.
 */
class Application : public xdaq::WebApplication,   
		   public toolbox::task::TimerListener,
		   public xdata::ActionListener
{
 public:
 
  
  //! define factory method for instantion of JobControl application
  XDAQ_INSTANTIATOR();

 
  /**
   * Constructor.
   */
  Application(xdaq::ApplicationStub *s) throw (xdaq::exception::Exception);
   

  /** 
   *  user soap command:
   *  start an executable EXE with environment ENV and user UID  
   *  sends process identifier via soap message to requester
   *
   *  sEnv format is ENVIRONMENT_VARIABLE1=VALUE1 ENVIRONMENT_VARIABLE2=VALUE2 ...
   * 
   *  arguments : sExe  (executable)
   *              sArgs (command line arguments)
   *              sEnv  (environment)
   *              iUid  (user id)
   */	        

 
  /**
   * user soap commands
   */
  
  virtual xoap::MessageReference getState( xoap::MessageReference soapMsg ) throw (xoap::exception::Exception);
  
  virtual xoap::MessageReference executeCommand(xoap::MessageReference soapMsg)
    throw (xoap::exception::Exception);
    
  virtual xoap::MessageReference startXdaqExe(xoap::MessageReference soapMsg)
    throw (xoap::exception::Exception);
  
  virtual xoap::MessageReference killAll( xoap::MessageReference soapMsg ) throw (xoap::exception::Exception);
  
  virtual xoap::MessageReference killExec( xoap::MessageReference soapMsg ) throw (xoap::exception::Exception);

  virtual xoap::MessageReference getJobStatus( xoap::MessageReference soapMsg ) throw (xoap::exception::Exception);


  /**
   * web page
   */
  void applySettings(xgi::Input*, xgi::Output*)	
	throw (xgi::exception::Exception);

  void defaultWebPage( 
		      xgi::Input  *in,
		      xgi::Output *out
		      )	throw (xgi::exception::Exception);

  void processLogWebPage( 
		      xgi::Input  *in,
		      xgi::Output *out
		      )	throw (xgi::exception::Exception);

  void processKillWebPage( 
		      xgi::Input  *in,
		      xgi::Output *out
		      )	throw (xgi::exception::Exception);

  void redirectToDefaultWebPage(
		      xgi::Output *out
		      )	throw (xgi::exception::Exception);

 void processKillAllWebPage( 
		      xgi::Input  *in,
		      xgi::Output *out
		      )	throw (xgi::exception::Exception);
			  
	void TabPanel( xgi::Output * out ) throw (xgi::exception::Exception) ;
	void JobsTabPage( xgi::Output * out ) throw (xgi::exception::Exception);
	void LogTabPage( xgi::Output * out ) throw (xgi::exception::Exception);
	  


 protected:
  
  /**
   *  create SOAP msg response returning the JobID
   */
  xoap::MessageReference createJIDReplyMsg( const std::string jid ) throw (xoap::exception::Exception);

  /**
   *  create SOAP msg response returning the PID
   *  DUMMY: WILL BE DEPRECATED IN RCMS3
   */
  xoap::MessageReference createPIDReplyMsg( const std::string pid ) throw (xoap::exception::Exception);

  /**
   *  create standard SOAP msg response
   */
  xoap::MessageReference createStandardReplyMsg( const std::string &responseStr ) throw (xoap::exception::Exception);

  void killExecByPid  (std::string sPid);

  void StartCommand()   
    throw (xcept::Exception);

 private:
  
  /**
   * Exported read-only parameter specifying the current state of the
   * application.
   */
  xdata::String stateName_;

  /**
   * Watchdog timer
   */
  toolbox::task::Timer * watchdogTimer_;
  bool            watchdogEnabled_;       // hack to prevent mutex locking

  /**
   * Table for monitoring with job information
   */
  xdata::Table jobTable_;

  /**
   * Used to access the application's info space without a function call.
   */
  xdata::InfoSpace *appInfoSpace_;

  /**
   * Used to access the monitor info space without a function call.
   */
  xdata::InfoSpace *monitorInfoSpace_;

  //Parameters for myKillDescendants function
  xdata::UnsignedInteger32 _numberOfTryForMyKillDescendants;
  xdata::UnsignedLong _sleepBetweenTryForMyKillDescendants;


  /**
   * ActionSignature of worker loop job.
   */
  toolbox::task::ActionSignature* workerLoopActionSignature_;

  /**
   * worker loop.
   */
  toolbox::task::WorkLoop* workerLoop_;

  struct _PidUid {                    // struct for PID UID Executable data
    pid_t           _pid;            // process id
    int             _uid;            // user id
    int             _port;           // xdaq port
    std::string     _sexe;           // path to executive
    std::string     _user;           // username
    std::string     _jid;            // job id
    int             _status;         // status as defined by waitpid()
    bool            _notified;       // if a job should crash, requestor will be notified once.
    std::string     _notifierURL;    // URL of the notification requestor. 
    std::string		_execURL;	 // URL of xdaq executive
    std::string     _configFile;     // Configuration File of xdaq executive. 	
    std::string     _configFilePath; // Path to Configuration File of xdaq executive. 	
    char _state;                     // state as defined by /proc/[pid]/stat
    unsigned long   _vsize;          // virtual memory size in bytes
    unsigned long   _start_time;     // start time
    unsigned long   _n_child_proc;   // number of child processes
    std::string     _child_tree;     // child tree asccii 
    std::list<int>  _children_list;  // list of children
    std::string	    _tag;	     // Information passed by job client, provided with exception on error
  };



  struct _ExecuteCommandData {                    // struct to hold the data for executeCommand
    std::list<std::string> _env;                  // environment list
    std::list<std::string> _args;                 // args list
    std::string            _jid;                  // current job ID
    int                    _intJid;               // int job id for automatic generation of jid
    std::string            _execPath;             // path to executive
    std::string            _execUser;             // user name
    int                    _execUid;              // user id 
    int                    _execGid;              // group id 
    std::string            _execNotifierURL;      // URL of the notification requestor. 
    std::string			   _execURL;	 		  // URL of xdaq executive
    std::string            _execConfigFile;       // Configuration File of xdaq executive. 
    std::string            _execConfigFilePath;   // Path to configuration file of xdaq executive. 
    pid_t                  _pid;                  // PID argument for kill and check
    std::string            _command;              // Command (start, kill, check) 
    std::string		   _tag;		  // Information passed by job client, provided with exception on error
  };



  std::list<_PidUid> _pidUidList;

  toolbox::rlist<_ExecuteCommandData> _exeCmdDatList; // list for start and destroy processes
  toolbox::rlist<_ExecuteCommandData> _exeWatchDogList; // list for trigger the watchDog
  


  std::string _caller;              // caller id used internally for thread communication
  std::string _executable;          // path to executive
  std::string _args;                // args list
  int    _uid;                      // user id 
  std::string _env;                 // environment string
  std::string _jid;                 // current job ID
  int _intJid;                      // int job id for automatic generation of jid

  //
  // constant
  //
  std::string workerName;
  std::string watchdogName;
  std::string start;
  std::string stop;  
  std::string watchdog;


  //
  // executeCommand / startXdaqExe parameters
  //

  std::string            execPath;
  int                    execUid;
  int                    execGid;
  std::string            execJid;

  std::string            execUser;
  std::string            execNotifierURL;
  std::string			 execURL;
  std::string            execConfigFile;
  std::string            execConfigFilePath;
  std::list<std::string> execArgList;
  std::list<std::string> execEnvList;
  
  std::string            execTag;

  // access control variables
  bool                   _rootAllowed;       // Taken from environment JC_ROOT_ALLOWED
  std::string            _usersAllowed;      // Taken from environment JC_USERS_ALLOWED

  toolbox::BSem          mutex_;            // semaphore for synchronization
  toolbox::Properties settings_;	

  /**
   * Exports the XDAQ variables.
   */
  void exportParams();


  /**
   * Updates the jobTable for monitoring information
   */
  void updateJobTable();

  /**
   * implementation of reply to GetState
   */
  xoap::MessageReference createStateReplyMsg(const std::string state) throw (xoap::exception::Exception);

  /**
   * implementation of reply to GetState
   */
  xoap::MessageReference createCrashNotificationMsg(const std::string state, const int status) throw (xoap::exception::Exception);


  /**
   * implementation of killExec, kill by pid
   */
  void killExec(const int iPid);


  /**
   * implementation of killExec, kill by executable name
   */
  void killExec(const std::string sExe);
  

  /**
   *  kill process by PID
   **/
  void killByPid(int PID) throw (xcept::Exception);

  /**
   *  kill process by PID in workloop
   **/
  void killByPidInWorkLoop(int PID) throw (xcept::Exception);


  /**
   *  kill all processes
   **/
  void killAllProcs() throw (xoap::exception::Exception);

  /**
   *  kill routine
   **/
  void myKill( pid_t pid );

  /**
    *  kill routine
    **/
  void myKillDescendants(pid_t pid, std::list<int> descendants, int numberOfTry, long sleepBetweenTry);


  /**
   *  helper function to build a list of strings out of a separated string
   **/
  void buildArgList(const std::string &sString, std::list<std::string> &lList);


  /**
   *  helper function to convert size_t to string
   **/
  std::string sizetToString(const size_t i);
  /**
   *  helper function to convert int to string
   **/
  std::string intToString(const int i);

  /**
   *  helper function to convert int to string
   **/
  int stringToInt(const std::string s);

  xoap::MessageReference fireEvent (xoap::MessageReference msg) throw (xoap::exception::Exception);

  toolbox::fsm::FiniteStateMachine fsm_; // application state machine

  /**
   * Callback for requesting current exported parameter values
   **/
  void actionPerformed (xdata::Event& e);

  /**
   * Callback for timers watchdog and worker
   **/
  void timeExpired (toolbox::task::TimerEvent& e); 

  /**
   * watchdog over started processes
   *
   * reads the /proc file system and looks at the
   * status of started processes.
   *
   **/
  void doWatchdog();

  /**
   * Callback for worker loop
   **/
  bool workerLoopJob (toolbox::task::WorkLoop* wl); 

  void executeCommandInLoop( _ExecuteCommandData ecd );

  xoap::MessageReference postSOAP 
	(
		xoap::MessageReference message, 
		std::string url
	)
	throw (xdaq::exception::Exception);
};

}

#endif
