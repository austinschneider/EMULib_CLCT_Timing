// $Id: MessageReference.h,v 1.3 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_MessageReference_h_
#define _xoap_MessageReference_h_

#include "xoap/CountingPtr.h"
#include "xoap/ThreadSafeReferenceCount.h"
#include "xoap/StandardObjectPolicy.h"
#include "SOAPMessage.h"

namespace xoap
{
typedef CountingPtr<SOAPMessage, ThreadSafeReferenceCount,StandardObjectPolicy> MessageReference;
}

#endif
