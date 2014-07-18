// $Id: SPYAddressTableReader.hh,v 1.4 2008/11/27 17:01:32 cschwick Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors:  R. Arcidiacono, L. Orsini, C. Schwick, J. Gutleber	         *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _fedbuilder_SPYAddressTableReader_hh_
#define _fedbuilder_SPYAddressTableReader_hh_

#include <string>

#include "hal/PCIAddressTableDynamicReader.hh"

/**
 *
 *
 *     @short A reader which generated the VME64x configuration space
 *
 *            This class is a hardcoded implementation of the address-
 *            items of the VME64x specification.
 *
 *       @see
 *    @author Christoph Schwick
 * $Revision: 1.4 $
 *     $Date: 2008/11/27 17:01:32 $
 *
 *
 **/

namespace fedbuilder {

    class SPYAddressTableReader : public HAL::PCIAddressTableDynamicReader {

    public:

        SPYAddressTableReader();

    };

} /* namespace fedbuilder */

#endif 
