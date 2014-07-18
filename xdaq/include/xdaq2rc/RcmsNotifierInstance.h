/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: S. Murray and J. Gutleber                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/
 
#ifndef _xdaq2rc_RcmsNotifierInstance_h
#define _xdaq2rc_RcmsNotifierInstance_h

#include "xdata/Bag.h"
#include "xdata/Boolean.h"
#include "xdata/String.h"
#include "xdata/UnsignedInteger32.h"


namespace xdaq2rc 
{

/**
 * Used to export the classname, instance, and HLTSG URI
 */
class RcmsNotifierInstance
{
public:
    void registerFields
    (
        xdata::Bag<RcmsNotifierInstance> *bag
    );

    xdata::String            classname;
    xdata::UnsignedInteger32 instance;
    xdata::String            hltsgURI;
};

} // namespace xdaq2rc

#endif
