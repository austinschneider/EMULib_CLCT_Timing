/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: R. Mommsen                                                   *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
 
#ifndef _xdaq2rc_RcmsNotificationSender_h
#define _xdaq2rc_RcmsNotificationSender_h

#include "toolbox/net/URL.h"
#include "xdaq/Application.h"
#include "xdaq/ApplicationDescriptor.h"
#include "xdata/ActionListener.h"
#include "xdata/Bag.h"
#include "xdata/Boolean.h"
#include "xdata/Table.h"
#include "xoap/MessageReference.h"
#include "log4cplus/logger.h"
#include "xdaq2rc/RcmsNotifierInstance.h"

#include <iostream>
#include <string>
#include <stdint.h>


namespace xdaq2rc 
{

/**
 * Helper class that enables XDAQ applications to send xdata::table data
 * via SOAP messages directly to the run-control system.
 */
class RcmsNotificationSender :
public xdata::ActionListener
{
public:

    /**
     * Constructor.
     */
    RcmsNotificationSender
    (
        Logger                      &applicationLogger,
        xdaq::ApplicationDescriptor *applicationDescriptor,
        xdaq::ApplicationContext    *applicationContext
    );

    /**
     * Destructor.
     */
    virtual ~RcmsNotificationSender();

    /**
     * Subscribes the RcmsNotificationSender to changes in the parameter
     * "rcmsNotificationReceiver" in the specified info space.
     *
     * If the RcmsNotificationSender is subscribed to changes in the parameter
     * "rcmsNotificationReceiver", then the RcmsNotificationSender can automatically search
     * for the RCMS state listener when the parameter is modified.
     */
    void subscribeToChangesInRcmsNotificationReceiver
    (
        xdata::InfoSpace *infoSpace
    );

    /**
     * Returns the parameter "rcmsNotificationReceiver".
     *
     * The parameter "rcmsNotificationReceiver" specifies the classname and instance
     * number of the RCMS notification receiver.
     */
    xdata::Bag<RcmsNotifierInstance> *getRcmsNotificationReceiverParameter();

    /**
     * Returns the parameter "foundRcmsNotificationReceiver".
     *
     * The parameter "foundRcmsNotificationReceiver" is a read-only debugging
     * parameter.  It has the value true if the RcmsNotificationSender has found
     * the RCMS notification receiver, else it has the value false.
     */
    xdata::Boolean *getFoundRcmsNotificationReceiverParameter();

    /**
     * Finds the RCMS notification receiver if it is present.
     *
     * It is not compulsory that the RCMS notification receiver be present.
     */
    void findRcmsNotificationReceiver();

    /**
     * Invoked when a change has occurred in the parameter "rcmsNotificationReceiver".
     */
    void actionPerformed(xdata::Event &event);

    /**
     * Send the data in form of a xdata::Table to the RCMS notification receiver.
     */
    void sendData
    (
        xdata::Table& table,
        const std::string& name
    );


private:

    /**
     * Returns the name to be given to the logger of the RcmsNotificationSender.
     */
    std::string getLoggerName
    (
        Logger &applicationLogger
    );

    /**
     * Returns the url of the specified application.
     */
    toolbox::net::URL getApplicationUrl
    (
        xdaq::ApplicationDescriptor *appDescriptor
    );

    /**
     * The logger of the RcmsNotificationSender.
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
     * Application descriptor of the RCMS notification receiver.
     *
     * It is valid for this pointer to be null.  If it is is null, then it
     * indicates that the RCMS notification receiver is not present.
     */
    xdaq::ApplicationDescriptor *rcmsNotificationReceiverDescriptor_;

    /**
     * Exported read/write parameter specifying the classname and instance
     * number of the RCMS notification receiver.
     */
    xdata::Bag<RcmsNotifierInstance> rcmsNotificationReceiver_;

    /**
     * Exported read-only parameter specifying whether or not the RCMS
     * notification receiver has been found.
     */
    xdata::Boolean foundRcmsNotificationReceiver_;

    /**
     * Creates the SOAP message used to send the data to the RCMS notification receiver.
     */
    xoap::MessageReference createNotificationMsg
    (
        const toolbox::net::URL &sourceURL,
        xdata::Table            &table,
        const std::string       &name,
        const int64_t           timeStamp
    );
    
    xdata::InfoSpace* appInfoSpace_;
};

} // namespace xdaq2rc

#endif
