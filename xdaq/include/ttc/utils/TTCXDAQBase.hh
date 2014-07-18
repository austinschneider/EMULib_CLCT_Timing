#ifndef _ttc_utils_TTCXDAQBase_hh_
#define _ttc_utils_TTCXDAQBase_hh_


#include "xdata/ActionListener.h"
#include "xdaq/WebApplication.h"

#include "xdata/String.h"
#include "xdata/Boolean.h"
#include "xdata/Integer.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include "toolbox/fsm/exception/Exception.h"
#include "toolbox/Event.h"
#include "xoap/MessageReference.h"
#include "log4cplus/logger.h"
#include "xgi/Method.h"

#include <map>
#include <sstream>
#include <string>
#include <vector>


namespace HAL
{
class VMEBusAdapterInterface;
}


namespace ttc
{

class BoardLockingProxy;
class HTMLTable;

struct CGIMethodSignature
{
    virtual ~CGIMethodSignature() {}
    virtual void invoke (xgi::Input * in, xgi::Output * out) = 0;
};

template <typename T>
struct CGIMethod: public CGIMethodSignature
{
  void invoke (xgi::Input * in, xgi::Output * out) { (obj_->*func_)(in, out); }
  T* obj_;
  void (T::*func_)(xgi::Input*, xgi::Output*);
};


//! base class for the XDAQ web applications of all the TTC module control applications
class TTCXDAQBase : public xdaq::WebApplication, public xdata::ActionListener
{

// types

protected:

//! nested class to hold error messages to display on top of application's web page
  class ErrorMessages
  {
  public:

    /** Free allocated pointers. */
    ~ErrorMessages();

    /**
     * Returns reference to output stream, for a given @param category of message. Example usage:
     * error_messages.add("WARNING") << "This is my warning: " << reason;
     */
    std::ostream& add(const std::string& category);

    //! tells whether any messages have been recorded so far
    bool isEmpty() const;

    //! clears recorded messages
    void clear();

    //! appends error messages from another ErrorMessages object
    void append(const ErrorMessages& other);

    //! returns messages as formatted HTML
    std::string asHtml() const;

  private:

    std::vector<std::pair<std::string, std::ostringstream*> > messages_;

    /**
     * Returns compact list of messages.
     * Sorts messages and groups identical messages (adding the occurrence count)
     * - time order is lost.
     */
    std::vector<std::pair<std::string, std::string> > compactified() const;
  };

  //! Struct holding information about one tab of the web application.
  struct TabInfo
  {
    TabInfo(const std::string& cmd, const std::string& dis) :
      command_name(cmd), display_name(dis) {}
    std::string command_name;
    std::string display_name;
  };

// static

public:

  /**
   * This is the URL used in the HTML footer shown at the bottom of
   * each page pointing to the CMSOS Trac page for TTC.
   */
  static std::string const supportURL;

  //! Id of the HTML 'div' element where the error messages are written into.
  static std::string ERROR_MESSAGES_DIV;

// members

public:

  TTCXDAQBase(
      xdaq::ApplicationStub* stub,
      const std::string& className,
      const std::string& boardType);

  virtual ~TTCXDAQBase();

  /**
   * Returns name of CMS group to which the controlled TTC module belongs.
   * Corresponds to the XML configuration file property 'group'.
   */
  std::string getCMSGroup() const;

  /**
   * Returns name of CMS system (lab, integration, production) to which the application belongs.
   * Corresponds to the XML configuration file property 'system'.
   */
  std::string getCMSSystem() const;

  /**
   * Returns identifier of controlled TTC module.
   * Corresponds to the XML configuration file property 'name'.
   */
  std::string getBoardID() const;

  /**
   * virtual method to return reference to BoardLockingProxy that
   * manages the resources needed for talking to the controlled GenericTTCModule
   */
  virtual BoardLockingProxy& boardLockingProxy() = 0;

  //! virtual method to return software version string for this RPM
  virtual std::string softwareVersion() = 0;

  /**
   * returns true if configuration process will use data from ASCII,
   *   false if data from the XML string are used directly
   */
  bool readConfigFromFile();

  /**
   * if ASCII file is used for configuration, returns file name
   *   else returns empty string
   */
  std::string pathToASCIIConfigFile();

  //! return Finite State Machine state
  std::string getFSMStateString();

protected:

  // SOAP - application info space

  /**
   * Adds a named xdata::Serializable item to the application infospace,
   * Optionally registers this TTCXDAQBase as an event listener of the infospace,
   *   for ItemRetrieveEvents and/or ItemChangedEvents.
   */
  void addItem(
      const std::string& itemName,
      xdata::Serializable& item,
      bool retrievable = false,
      bool changeable = false);

  //! Adds a retrievable item.
  void addItemRetrievable(
      const std::string& itemName,
      xdata::Serializable& item);

  //! Adds a retrievable and changeable item.
  void addItemRetrievableChangeable(
      const std::string& itemName,
      xdata::Serializable& item);

  /**
   * Adds a retrievable item, and maps its name to an index.
   * This is frequently useful for quickly accessing the index
   *   that corresponds to the name of an item within a given category.
   */
  template <typename T>
  void addItemRetrievableAssoc(
      const std::string& itemName,
      xdata::Serializable& item,
      std::map<std::string, T>& mapItemNameToIndex,
      T index)
  {
    mapItemNameToIndex[itemName] = index;
    addItem(itemName, item, true);
  }

  //! action for ItemRetrieveEvents, called by actionPerformed
  virtual void itemRetrieveAction(xdata::ItemRetrieveEvent& e);

  //! action for ItemChangedEvents, called by actionPerformed
  virtual void itemChangedAction(xdata::ItemChangedEvent& e);

  //! action for setDefaultValues events, called by actionPerformed
  virtual void setDefaultValuesAction();


  // SOAP - FSM

  virtual void ColdResetAction(toolbox::Event::Reference event);

  virtual void ConfigureAction(toolbox::Event::Reference event);

  virtual void EnableAction(toolbox::Event::Reference event);

  virtual void StopAction(toolbox::Event::Reference event);

  virtual void SuspendAction(toolbox::Event::Reference event);


  // SOAP - other

  //! sends a SOAP message @param commandname with several @param variables to this XDAQ application
  void SendSOAPMessageToMe(
      const std::string& commandname,
      const std::map<std::string, std::string>& variables);

  //! logs an exception and returns a SOAP messages containing the exception as the fault
  xoap::MessageReference failSoapCallback(xcept::Exception& e);


  // CGI

  //! The main HyperDAQ entry point.
  virtual void HTMLPageMain(xgi::Input* in, xgi::Output* out) = 0;

  virtual void CommandImpl(cgicc::Cgicc& cgi, const std::string& command);

  void RedirectMessage(xgi::Output* out, const std::string& url);

  //! virtual method producing HTML output for the currently recorded set of errors
  virtual void ErrorStatement(xgi::Output& out) = 0;

  //! abstract method to be called before every CGI callback
  virtual void initHTMLFields();

  //! tells whether setHTMLFieldsInited() was called
  bool areHTMLFieldsInited();

  //! declares HTML fields initialized (call this at the end of initHTMLFields)
  void setHTMLFieldsInited();

  /**
   * Binds the page name of a CGI request to a callback method.
   * (We first bind to Default, and from there redirect to the given method.)
   * If @param displayName is given, also registers a tab to be included
   *   in the standard header printed by PrintHTMLHeader.
   */
  template <typename T>
  void cgi_bind(
      T* obj, void (T::*func)(xgi::Input*, xgi::Output*),
      const std::string& pageName,
      std::string displayName = "")
  {
    // bind to the Default callback
    xgi::bind(this, &TTCXDAQBase::Default, pageName);

    // bind to a method to which Default redirects
    CGIMethod<T>* m = new CGIMethod<T>;
    m->obj_ = obj;
    m->func_ = func;
    mapCGIRequestPageNameToCallback_[pageName] = m;

    if (!displayName.empty())
    {
      tab_items.push_back(TabInfo(pageName, displayName));
    }
  }

  //! gets the page name (PATH_INFO) from an incoming CGI request's environment
  std::string getCGIRequestPageName(xgi::Input* in);

  /**
   * Returns the mapped callback for a given command.
   * If command is not registered, falls back to callback for 'Default'.
   * (If 'Default' is not registered, raises an exception.)
   */
  CGIMethodSignature* getCGIRequestCallback(std::string& command);

  //! produces HTML header for this web application
  void PrintHTMLHeader(xgi::Output& out, bool auto_refresh_button = true);

  //! produces HTML footer for this web application
  void PrintHTMLFooter(xgi::Output& out);

  //! prints the current FSM state in the corresponding color (if defined)
  void PrintFSMState(xgi::Output& out);

  //! prints the HTML 'control and status' table for the FSM
  void PrintFSMTable(xgi::Output& out);

  //! prints the sequence table (for TTCci and LTC)
  void PrintSequenceTable(xgi::Output& out);

  std::string getFullURL();

  //! tells wheter a given CGI command @param pageName corresponds represents a tab of the control page
  bool isTab(const std::string& pageName);

  //! streams javascript code to @param out, opening a popup window
  void WriteJavascriptPopupCode(std::ostream& out);


  // utilities

  /**
   * Extracts parameters ReadConfigFromFile_ & asciConfigurationFilePath_
   * from ConfigurationString_ (from infospace).
   */
  void extractConfigurationSourceParams();

  //! Returns the body background color, which is different from white if VME write access is disabled
  std::string GetBodyBackgroundColour();


  log4cplus::Logger logger_;

  //! the class name
  std::string className_;

  //! the type of TTC board controlled by this application
  std::string boardType_;

  time_t tnow_, tprevious_;

  //! Last page visited
  std::string lastPage_;

  bool autoRefresh_;

  //! group to which application belongs (TTC, ECAL, ...)
  xdata::String group_;

  //! system to which application belongs (P5, 904, test)
  xdata::String system_;

  //! name of TTC module (e.g. TTCci-EB+)
  xdata::String name_;

  //! Bus adapter name.
  xdata::String busadaptername_;

  //! exported parameter holding the base address of the TTC module
  xdata::Integer Location_;

  /**
   * Exported parameter telling whether VME write access to ordinary registers
   * (i.e. apart from CR/CSR space) should be disabled.
   */
  xdata::Boolean DisableVMEWrite_;

  //! exported parameter holding current state of state machine
  xdata::String StateName_;

  /**
   * exported parameter holding the configuration string;
   * this either holds the ASCII configuration data directly,
   * or encodes the name of the file to be used
   */
  xdata::String ConfigurationString_;

  /**
   * flag telling whether configuration process will read configuration data
   * from a file file or directly from ConfigurationString_
   */
  bool ReadConfigFromFile_;

  //! file to be used in case where ReadConfigFromFile_ == true
  xdata::String asciConfigurationFilePath_;

  //! Exported parameter, used in subclasses to disable XMAS monitoring, if desired.
  xdata::Boolean DisableMonitoring_;

  /**
   * Obsolete parameter, no longer used in the code.
   * Kept for backward compatibility with old XML configuration files.
   * (Used to specify the HyperDAQ Control Level, i.e. a kind of HTTP access control level.)
   */
  xdata::Integer CtrlLvl_;

  /**
   * Obsolete parameter, no longer used in the code.
   * Kept for backward compatibility with old XML configuration files.
   * (Used to specify whether the module controlled by this application is VME64X compatible;
   * if false then the base address was to be ignored.)
   */
  xdata::Boolean Is64XCompatible_;

  //! the application's state machine
  toolbox::fsm::FiniteStateMachine fsm_;

  double oldfrequency_;

  //! the ErrorMessages to be visualized at the top of this application's web page
  ErrorMessages error_messages;

 private:

  // SOAP - application info space

  //! Callback method for registered application infospace events
  void actionPerformed(xdata::Event& e);

  //! fail action when actionPerformed fails
  void failActionPerformed(const std::string& msg);

  // SOAP - FSM

  /**
   * Initializes the Finite State Machine.
   * Binds transition events to changeState().
   * Binds exceptions during transitions to transitionFailed()
   */
  void initFSM();

  //! Adds an FSM state by @param name, and assigns a color
  void fsmAddState(toolbox::fsm::State state, const std::string& name, const std::string& color);

  /**
   * Adds an FSM transition @param input, and binds it to ExecuteTransition,
   *   which passes it on to the callback @param func.
   */
  void fsmAddTransition(
      toolbox::fsm::State from,
      toolbox::fsm::State to,
      const std::string& input,
      void (TTCXDAQBase::*func)(toolbox::Event::Reference));

  /**
   * handler for exceptions thrown in FSM transitions:
   * resets FSM, and throws toolbox::fsm::exception::Exception
   * (the only exception that may be thrown out of fsm::FiniteStateMachine::fireEvent)
   */
  void transitionFailed(toolbox::Event::Reference e);

  //! callback for FSM transition events; in case of an exception, calls failFSMCallbackRethrow
  void ExecuteTransition(toolbox::Event::Reference event);


  // SOAP - other

  //! callback for SOAP messages tagged "getState"
  xoap::MessageReference getStateRCMS(xoap::MessageReference msg) throw (xoap::exception::Exception);

  //! callback for SOAP messages tagged "reset"
  xoap::MessageReference resetFSM(xoap::MessageReference msgIn) throw (xoap::exception::Exception);

  /**
   * callback for SOAP messages tagged with FSM transition names ("configure", "enable" etc.);
   * this fires a corresponding FSM transition event
   */
  xoap::MessageReference changeState(xoap::MessageReference msg) throw (xoap::exception::Exception);


  // CGI

  //! Implements the HyperDAQ 'Default' callback
  virtual void Default(xgi::Input* in, xgi::Output* out) throw (xgi::exception::Exception);

  //! output for the case when Default throws an exception
  void failCGICallbackDefault(xcept::Exception& e, xgi::Output& out);

  //! callback for CGI messages tagged "Command"
  void Command(xgi::Input* in, xgi::Output* out);

  //! callback for CGI messages tagged "SoapCommand"
  void SoapCommand(xgi::Input* in, xgi::Output* out);

  //! add a button to the FSM table
  void addFSMButton(
      ttc::HTMLTable& tab,
      xgi::Output& out,
      const std::string& action,
      bool enabled,
      const std::string& style = "");

  //! returns message for original (earliest) exception of the history
  std::string originalException(xcept::Exception& e);

  //! returns compact message history: final (latest) exception + original (earliest) exception of the history
  std::string compactExceptionHistory(xcept::Exception& e);


  //! container to map FSM states to color strings (as used in CSS styles)
  std::map<char, std::string> mapStateToColor;

  //! container to map FSM transition names to callback member functions
  std::map<std::string, void (TTCXDAQBase::*)(toolbox::Event::Reference)> mapTransitionToAction_;

  //! the vector holding the TabInfos for the several pages of this TTC web application
  std::vector<TabInfo> tab_items;

  //! container to map page names of CGI request to callback member functions
  std::map<std::string, CGIMethodSignature*> mapCGIRequestPageNameToCallback_;

  bool HTMLFieldsInited_;
};

}


#endif
