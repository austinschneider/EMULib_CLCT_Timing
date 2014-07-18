// $Id: SOAPParameterExtractor.hh,v 1.1 2009/02/04 15:17:18 cschwick Exp $
#ifndef _fedbuilder_SOAPParameterExtractor_h_
#define _fedbuilder_SOAPParameterExtractor_h_

#include "xdaq/Application.h"
#include "xoap/exception/Exception.h"
#include "xoap/MessageReference.h"
#include "xdata/soap/Serializer.h"

#include <string>


namespace xdaq2rc
{
    class SOAPParameterExtractor 
    {

    public:
        SOAPParameterExtractor( xdaq::Application *appl );
        std::string extractParameters( xoap::MessageReference msg )
            throw( xoap::exception::Exception );

    private:
        xdaq::Application *appl_;
        xdata::soap::Serializer serializer_;
    };
}

#endif /* _xdaq2rc_SOAPParameterExtractor_h_ */
