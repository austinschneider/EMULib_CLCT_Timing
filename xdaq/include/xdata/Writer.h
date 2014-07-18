// $Id: Writer.h,v 1.3 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Writer_h_
#define _xdata_Writer_h_


namespace xdata {


// Approach 1


class Serializable;


class Serializer {

	public:
	

	virtual void writeObject(const Serializable * serializable)
	{
		serializer_[serializable->type()]->writeObject(serializable);
	
	}
	
	
	protected:
	
	void addSerializer(Serializer * serializer)
	{
		serializer_[serializer->type()] = serializer;
	}
	
	private:
	
	map<string, Serializer *> serializer_;
	
	

};


// Approach 2 is implementation specific
class Serializer {

	
	protected:
	
	void addSerializer(Serializer * serializer)
	{
		serializer_[serializer->type()] = serializer;
	}
	
	private:
	
	map<string, Serializer *> serializer_;
	
	

};


}

#endif
