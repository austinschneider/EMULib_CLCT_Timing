// $Id: UDPAppender.h,v 1.2 2008/07/18 15:26:55 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _log4cplus_UDPAppender_h_
#define _log4cplus_UDPAppender_h_

//#include <log4cplus/config.h>
#include <log4cplus/appender.h>
#include <log4cplus/helpers/socket.h>
#include <log4cplus/helpers/socketbuffer.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <sys/time.h> /* select() */ 

#ifndef UNICODE
#  define LOG4CPLUS_UDP_MAX_MESSAGE_SIZE (8*1024)
#else
#  define LOG4CPLUS_UDP_MAX_MESSAGE_SIZE (2*8*1024)
#endif

namespace log4cplus 
{

void registerUDPAppenderFactory();

    /**
     * Sends {@link LoggingEvent} objects to a UDP socket server via UDP datagrams.
     *
     * <p>The UDPAppender has the following properties:
     *
     * <ul>
     *   <p><li>Remote logging is non-intrusive as far as the log event is
     *   concerned. In other words, the event will be logged with the same
     *   time stamp, {@link org.apache.log4j.NDC}, location info as if it
     *   were logged locally by the client.
     *
     *   <p><li>The UDPAppender does not use a layout.
     *
     *   <p><li>Logging uses the OCCI library and embedded protocols. 
	 *   Consequently, if
     *   the database server is reachable, then log events will eventually arrive
     *   at the server.
     *
     *   <p><li>If the database server is down, the logging requests are
     *   simply dropped. However, if and when the server comes back up,
     *   then event transmission is resumed transparently. This
     *   transparent reconneciton is performed by a <em>connector</em>
     *   thread which periodically attempts to connect to the server.
     *
     *   <p><li>Logging events are automatically <em>buffered</em> by the
     *   OCCI implementation. This means that if the link to server
     *   is slow but still faster than the rate of (log) event production
     *   by the client, the client will not be affected by the slow
     *   network connection. However, if the network connection is slower
     *   then the rate of event production, then the client can only
     *   progress at the network rate. In particular, if the network link
     *   to the the server is down, the client will be blocked.
     *
     *   <p>On the other hand, if the network link is up, but the server
     *   is down, the client will not be blocked when making log requests
     *   but the log events will be lost due to server unavailability.
     */
    class LOG4CPLUS_EXPORT UDPAppender : public Appender 
	{
    public:
      // Ctors
        UDPAppender(const log4cplus::tstring& host, 
		    int port,
		    const log4cplus::tstring& serverName,
		    const log4cplus::tstring& session);

        UDPAppender(const log4cplus::helpers::Properties properties);

      // Dtor
        ~UDPAppender();

      // Methods
        virtual void close();
		
		// Public commit thread specific data
		pthread_attr_t commit_thread_attr_;
		pthread_t commit_thread_id_;

    protected:
        void openConnection();
		
        virtual void append(const spi::InternalLoggingEvent& event);
	
	log4cplus::helpers::SocketBuffer convertToBuffer(const spi::InternalLoggingEvent& event);

	log4cplus::spi::InternalLoggingEvent readFromBuffer(log4cplus::helpers::SocketBuffer& buffer);

      // Data
	log4cplus::tstring host_;
	int port_;
	log4cplus::tstring serverName_;
	log4cplus::tstring session_;
	
	struct sockaddr_in cliAddr_, remoteServAddr_;
	int udpSocket_;
		
    private:
      // Disallow copying of instances of this class
        UDPAppender(const UDPAppender&);
        UDPAppender& operator=(const UDPAppender&);
    };

} // end namespace log4cplus

#endif // _log4cplus_UDPAppender_h_

