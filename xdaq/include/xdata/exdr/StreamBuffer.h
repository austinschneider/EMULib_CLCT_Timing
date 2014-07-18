// $Id: StreamBuffer.h,v 1.11 2008/07/18 15:28:11 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_exdr_StreamBuffer_h_
#define _xdata_exdr_StreamBuffer_h_

#include <rpc/types.h>
#include <rpc/xdr.h>

#include "xdata/exception/Exception.h"

namespace xdata 
{
	namespace exdr 
	{
		class StreamBuffer 
		{
			public:

			virtual ~StreamBuffer() {}
			
			//! Integer 8 bit
			void encodeInt8(const  int8_t & i) throw (xdata::exception::Exception);
			void decodeInt8( int8_t & i) throw (xdata::exception::Exception);

			//! Integer 16 bit
			void encodeInt16(const  int16_t & i) throw (xdata::exception::Exception);
			void decodeInt16( int16_t & i) throw (xdata::exception::Exception);

			//! Integer 32 bit
			void encodeInt32(const  int32_t & i) throw (xdata::exception::Exception);
			void decodeInt32( int32_t & i) throw (xdata::exception::Exception);

			//! Integer 64 bit
			void encodeInt64(const  int64_t & i) throw (xdata::exception::Exception);
			void decodeInt64( int64_t & i) throw (xdata::exception::Exception);

			//! Integer unsigned 8 bit
			void encodeUInt8(const  uint8_t & i) throw (xdata::exception::Exception);
			void decodeUInt8( uint8_t & i) throw (xdata::exception::Exception);

			//! Integer unsigned 16 bit
			void encodeUInt16(const  uint16_t & i) throw (xdata::exception::Exception);
			void decodeUInt16( uint16_t & i) throw (xdata::exception::Exception);

			//! Integer unsigned 32 bit
			void encodeUInt32(const  uint32_t & i) throw (xdata::exception::Exception);
			void decodeUInt32( uint32_t & i) throw (xdata::exception::Exception);

			//! Integer unsigned 64 bit
			void encodeUInt64(const  uint64_t & i) throw (xdata::exception::Exception);
			void decodeUInt64( uint64_t & i) throw (xdata::exception::Exception);

			//! Float
			void encode(const float & i) throw (xdata::exception::Exception);
			void decode(float & i) throw (xdata::exception::Exception);

			//! Double
			void encode(const double & i) throw (xdata::exception::Exception);
			void decode(double  & i) throw (xdata::exception::Exception);
			
			//! Boolean
			void encode(const bool & i) throw (xdata::exception::Exception);
			void decode(bool & i) throw (xdata::exception::Exception);

			//! String
			void decode(std::string & s) throw (xdata::exception::Exception);
			void encode(const std::string & s) throw (xdata::exception::Exception);

			//! Opaque - character array
			void decode(char* c, unsigned int len) throw (xdata::exception::Exception);
			void encode(char* c, unsigned int len) throw (xdata::exception::Exception);

			//! Return current position of stream pointer
			virtual u_int tellp();

			protected:

			virtual void overflow() throw (xdata::exception::Exception) = 0;

			XDR xdr_;
		};
	}
}
#endif
