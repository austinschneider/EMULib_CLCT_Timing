/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: S. Murray and J. Gutleber                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
 
#ifndef _xdaq2rc_RcmsStateNotifier_h
#define _xdaq2rc_RcmsStateNotifier_h

#include "xdaq/Application.h"
#include "xdaq/ApplicationDescriptor.h"
#include "xdata/ActionListener.h"
#include "xdata/Bag.h"
#include "xdata/Boolean.h"
#include "xdata/String.h"
#include "xoap/MessageReference.h"
#include "log4cplus/logger.h"
#include "xdaq2rc/ClassnameAndInstance.h"

#include <iostream>
#include <string>
#include <stdint.h>


namespace xdaq2rc 
{

/**
 * Helper class that enables XDAQ applications to send asynchronous state
 * notification messages to the run-control system.
 */
class RcmsStateNotifier :
public xdata::ActionListener
{
public:

    /**
     * Constructor.
     */
    RcmsStateNotifier
    (
        Logger                      &applicationLogger,
        xdaq::ApplicationDescriptor *applicationDescriptor,
        xdaq::ApplicationContext    *applicationContext
    );

    /**
     * Destructor.
     */
    virtual ~RcmsStateNotifier();

    /**
     * Subscribes the RcmsStateNotifier to changes in the parameter
     * "rcmsStateListener" in the specified info space.
     *
     * If the RcmsStateNotifier is subscribed to changes in the parameter
     * "rcmsStateListener", then the RcmsStateNotifier can automatically search
     * for the RCMS state listener when the parameter is modified.
     */
    void subscribeToChangesInRcmsStateListener
    (
        xdata::InfoSpace *infoSpace
    );

    /**
     * Returns the parameter "rcmsStateListener".
     *
     * The parameter "rcmsStateListener" specifies the classname and instance
     * number of the RCMS state listener.
     */
    xdata::Bag<ClassnameAndInstance> *getRcmsStateListenerParameter();

    /**
     * Returns the parameter "foundRcmsStateListener".
     *
     * The parameter "foundRcmsStateListener" is a read-only debugging
     * parameter.  It has the value true if the RcmsStateNotifier has found
     * the RCMS state listener, else it has the value false.
     */
    xdata::Boolean *getFoundRcmsStateListenerParameter();

    /**
     * Finds the RCMS state listener if it is present.
     *
     * It is not compulsory that the RCMS state listener be present.
     */
    void findRcmsStateListener();

    /**
     * Invoked when a change has occurred in the parameter "rcmsStateListener".
     */
    void actionPerformed(xdata::Event &event);

    /**
     * Notifies the RCMS state listener if it is present of the specified
     * state change.
     *
     * The reasonForStateChange parameter is not yet used, however its value
     * will be sent to the RCMS state listener in a future release.  Users of
     * this API are therefore advised to provide a value.
     */
    void stateChanged
    (
        const std::string &state,
        const std::string &reasonForStateChange
    );

    /**
     * Creates the SOAP message used to notify the run-control system of a
     * change in the application's state.
     */
    static xoap::MessageReference createStateNotificationMsg
    (
        const std::string &sourceURL,
        const std::string &className,
        const uint32_t    &instance,
        const std::string &state,
	const std::string &reasonForStateChange,
        const bool        asynchronousReply,
        const int64_t     timeout,
        const int64_t     timeStamp,
        const int64_t     transactionID
    );


private:

    /**
     * Returns the name to be given to the logger of the RcmsStateNotifier.
     */
    std::string getLoggerName
    (
        Logger &applicationLogger
    );

    /**
     * Returns the url of the specified application.
     */
    std::string getApplicationUrl
    (
        xdaq::ApplicationDescriptor *appDescriptor
    );

    /**
     * The logger of the RcmsStateNotifier.
     */
    Logger logger_;

    /**
     * The descriptor of the parent application.
     */
    xdaq::ApplicationDescriptor *applicationDescriptor_;

    /**
     * The context the parent application.
     */
    xdaq::ApplicationContext *applicationContext_;

    /**
     * Application descriptor of the RCMS state listener.
     *
     * It is valid for this pointer to be null.  If it is is null, then it
     * indicates that the RCMS state listener is not present.
     */
    xdaq::ApplicationDescriptor *rcmsStateListenerDescriptor_;

    /**
     * Exported read/write parameter specifying the classname and instance
     * number of the RCMS state listener.
     */
    xdata::Bag<ClassnameAndInstance> rcmsStateListener_;

    /**
     * Exported read-only parameter specifying whether or not the RCMS state
     * listener has been found.
     */
    xdata::Boolean foundRcmsStateListener_;
    
    xdata::InfoSpace* appInfoSpace_;
};

} // namespace xdaq2rc

#endif
