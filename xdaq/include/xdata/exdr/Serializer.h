// $Id: Serializer.h,v 1.16 2008/07/18 15:28:11 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_exdr_Serializer_h_
#define _xdata_exdr_Serializer_h_

#include <bitset>
#include <rpc/types.h>
#include <rpc/xdr.h>

#include "xdata/exception/Exception.h"
#include "xdata/Serializer.h"
#include "xdata/exdr/ObjectSerializer.h"
#include "xdata/exdr/InputStreamBuffer.h"
#include "xdata/exdr/OutputStreamBuffer.h"
#include "xdata/SimpleType.h"
namespace xdata {

namespace exdr {

class Serializer : public xdata::Serializer 
{
	public:
	
	enum DataTypeTag 
	{
		Unknown        		= 0,
		Integer      		 = 1,
		Float          		= 2,
		Double         		= 3,
		String         		= 4,
		UnsignedLong   		= 5,
		UnsignedShort  		= 6,
		Boolean        		= 7,
		Bag            		= 8,
		Vector         		= 9,
		Properties     		= 10,
		Table          		= 11,
		Mime	       		= 12,
		UnsignedInteger 	= 13,
		UnsignedInteger64 	= 14,
		UnsignedInteger32 	= 15,
		Integer32 		= 16,
		Integer64 		= 17,
		TimeVal 		= 18,
		VectorUnsignedInteger32 = 19,
		VectorUnsignedInteger64 = 20,
		VectorUnsignedShort 	= 21,
		VectorFloat 		= 22,
		VectorDouble 		= 23,
		VectorString 		= 24,
		VectorBoolean 		= 25,
		VectorTimeVal 		= 26,
		VectorInteger 		= 27,
                VectorInteger32 	= 28,
                VectorInteger64 	= 29,
                VectorUnsignedInteger	= 30

	};
	
	// tell the serializer to pack all data types (no meta information), default is false
	Serializer(bool packed = false);


	/*! 
	*/
	void exportAll
	(
		xdata::Serializable * s,
		xdata::exdr::OutputStreamBuffer * buf
	) 
	throw (xdata::exception::Exception);

	/*! 
	*/
	void import
	(
		xdata::Serializable * s,
		xdata::exdr::InputStreamBuffer * buf
	) 
	throw (xdata::exception::Exception);	
	
	void encodeTag
	(
		DataTypeTag tag,
		xdata::exdr::OutputStreamBuffer * sbuf
	) 
	throw (xdata::exception::Exception);
	
	void decodeTag
	(
		DataTypeTag tag,
		xdata::exdr::InputStreamBuffer * sbuf
	) 
	throw (xdata::exception::Exception);
	
	void encodeTag
	(
		DataTypeTag tag,
		std::bitset<xdata::NumberOfLimits> & limits,
		xdata::exdr::OutputStreamBuffer * sbuf
	) 
	throw (xdata::exception::Exception);
	
	void decodeTag
	(
		DataTypeTag tag,
		std::bitset<xdata::NumberOfLimits> & limits,
		xdata::exdr::InputStreamBuffer * sbuf
	) 
	throw (xdata::exception::Exception);
	protected:
	
	bool packed_;	
};

}}

#endif

