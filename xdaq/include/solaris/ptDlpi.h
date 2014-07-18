// $Id: ptDlpi.h,v 1.4 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ptDlpi_h_
#define _ptDlpi_h_

#include "pt.h"
#include "vxioslib.h"
#include "Task.h"
#include "SmartBufPool.h"

struct dlpiAddr : public Addr {
	short sap;
	char host[6];
};


class ptDlpi: public pt, public Task {

	public:
	
	ptDlpi (SmartBufPool* pool = 0) {
			
		if ( pool == 0 ) {
			//create private pool
		}


	}
	
	~ptDlpi() {
	
	}
	
	protected:
	
	ptDlpi(Address * addr, pta * ptap, ptDlpi* proto): pt(ptap) {
	
		pool_  = proto->pool_;
	
	}
	int svc() {
	
		return 0;
	}

	inline void pollRecv()  {
	//virtual BOOL pollRecv(BufRef * ref)  {
		return;
		
	}
	pt * createSend( Addr * addr, pta * ptap) {
		
		ptDlpi * tmp = new ptDlpi(addr, ptap, this);
		return tmp;
	
	}
	
	pt * createRecv( Addr * addr, pta * ptap, int polling) {
		
		ptDlpi * tmp = new ptDlpi(addr, ptap, this);
		return tmp;
	
	}
	
	//not used
	void setSendRtnFunc(SendRtnFunc func, void * context) {
		
	}
	
	virtual void send( BufRef * ref)
	{
	
		
	}
	

	
	int type() {
	
		return(XDAQ_TRANSPORT_DLPI);
	}
	
	
	protected:
		dlpiAddr  address_;
		SmartBufPool   * pool_;
	
	
};


#endif
