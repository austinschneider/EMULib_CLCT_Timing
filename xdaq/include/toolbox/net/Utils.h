// $Id: Utils.h,v 1.14 2008/07/18 15:27:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 * Contributors: V. Boyer						 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_net_Utils_h_
#define _toolbox_net_Utils_h_

#include <string>
#include <netdb.h>
#include <unistd.h>
#include <stdint.h>
#include "toolbox/exception/Exception.h"
#include "toolbox/net/exception/Exception.h"
#include "toolbox/net/exception/UnresolvedAddress.h"

#if (defined (AF_INET))
#   define HAS_SOCKETS /* System supports BSD style sockets */
#else
#   undef  HAS_SOCKETS
#endif


#undef SOCKET_LOOPBACK
#define SOCKET_LOOPBACK 0x7f000001L /* Loopback address 127.0.0.1 */

namespace toolbox 
{
namespace net 
{

	struct sockaddr_in getSocketAddressByName
		(
			const std::string & hostname, 
			uint16_t port
		) 
	throw (toolbox::net::exception::UnresolvedAddress );

/*!
 *   Returns a string containing the local hostname.  
 *   If sockets are not supported, returns the value "localhost".
*/
std::string getHostName();

/*!
 *   Returns a string containing the hosts network domain name.  
 *   If sockets are not supported, returns an empty string "".
*/
std::string getDomainName();

/*!
 *   Returns a string containing the DNS resolved name for the hostname provided  
 *   If the resolution could not be done, the function returns an empty string ""
 *   If the resolution fails, the function throws an exception
 *   Example: getDNSHostName(myHost) -> returns: myHost.myNetork.myDomain
*/
std::string getDNSHostName(const std::string& name) 
	throw (toolbox::net::exception::Exception);

/*! Returns the current the host address as a 4-byte value in
 *  network order.  Returns 0x7f000001 (loopback) if sockets are not 
 *  supported or there was an error getting the current host IP address.
 *  If there are several IP addresses on the system, returns one arbitrary 
 *  address.
 */
// unsigned long getHostAddr();
// unsigned long getHostAddr(const std::string & hostname);

/*! Calculate CRC16  based on the poynom 1 + X2 + X15 +X16 for a datagram
 *  \param buffer points to a byte array that holds the data for which the CRC is calculated
 *  \param length is size of the datagram pointed to by the parameter \param buffer
 *  \return the calculated CRC   	
 * Use : if you want to check the CRC of a datagram, store the received CRC
 *       and replace it by 0x0000. Then use this function to calculate a new 
 * CRC. Compare the two CRCs. If they are equal the message was correctly received. 
 */
uint16_t calculateCRC16 (unsigned char *buffer, size_t length);

/*! Calculate CRC16  based on the poynom 1 + X2 + X15 +X16 for a single byte
 *  \param crc is an already existint CRC checksum.
 *  \param byte is the additional byte for which the CRC has to be re-calculated
 *  \return the newly calculated CRC   	
*/
uint16_t recalculateCRC16 (uint16_t crc, unsigned char byte);

}}

#endif
