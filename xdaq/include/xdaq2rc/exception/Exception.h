#ifndef __xdaq2rc_Exception_h__
#define __xdaq2rc_Exception_h__


#include "xcept/Exception.h"

/**
 * Exception raised by the xdaq2rc package.
 */

/**
 * Generic exception raised by the xdaq2rc package.
 */
XCEPT_DEFINE_EXCEPTION(xdaq2rc, Exception)

/**
 * Exception raised by the xdaq2rc package on failure to subscribe to the InfoSpace.
 */
XCEPT_DEFINE_EXCEPTION(xdaq2rc, InfoSpace)

/**
 * Exception raised by the xdaq2rc package on failure to create SOAP message.
 */
XCEPT_DEFINE_EXCEPTION(xdaq2rc, soap)

/**
 * Exception raised by the xdaq2rc package on failure to send SOAP message.
 */
XCEPT_DEFINE_EXCEPTION(xdaq2rc, SendFailed)

/**
 * Exception raised by the xdaq2rc package when a bad reply is received.
 */
XCEPT_DEFINE_EXCEPTION(xdaq2rc, BadReply)

#endif
