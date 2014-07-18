#ifndef _pt_atcp_exception_Exception_h_
#define _pt_atcp_exception_Exception_h_

#include "xcept/Exception.h"

/**
 * Exceptions thrown by the ATCP package in the
 * namespace pt::atcp::exception
 */

namespace pt {
/**
 * Generic exception raised by the atcp package.
 */
XCEPT_DEFINE_EXCEPTION(atcp, Exception)

/**
 * Exception raised by the atcp package on a monitoring problem.
 */
XCEPT_DEFINE_EXCEPTION(atcp, Monitoring)

/**
 * Exception raised by the atcp package when failing to handle the finite state machine
 */
XCEPT_DEFINE_EXCEPTION(atcp, FSM)

/**
 * Exception raised by the atcp package fails to connect all the sockets
 */
XCEPT_DEFINE_EXCEPTION(atcp, FailedConnectSockets)

/**
 * Exception raised by the atcp package fails to disconnect all the sockets
 */
XCEPT_DEFINE_EXCEPTION(atcp, FailedDisconnectSockets)

/**
 * Exception raised by the atcp package when a memory pool problem occured
 */
XCEPT_DEFINE_EXCEPTION(atcp, MemoryPool)


}
#endif
