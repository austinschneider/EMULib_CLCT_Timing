// $Id: i2oStreamIOMsg.h,v 1.2 2008/07/18 15:26:40 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _i2oStreamIOMsg_h_
#define _i2oStreamIOMsg_h_

#include "i2o/i2o.h"

// callback binding (user defined)
#define I2O_TOKEN_CODE 0x0001

typedef struct _I2O_TOKEN_MESSAGE_FRAME {
  I2O_PRIVATE_MESSAGE_FRAME PvtMessageFrame;
  unsigned long last; // 0 false 1 true
} I2O_TOKEN_MESSAGE_FRAME, *PI2O_TOKEN_MESSAGE_FRAME;

#endif
