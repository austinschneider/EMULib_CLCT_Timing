#ifndef __InfospaceSender__
#define __InfospaceSender__

#include "xdaq/Application.h"
#include "xdata/UnsignedInteger32.h"

#define INFOSPACEBROWSER_DEFAULT_BUFFSIZE 8000

namespace fedbuilder
{

  class InfospaceSender {
			
  public:
    
    enum DataType{ INFOSPACEINFO, INFOSPACEDATA, INFOSPACEUNREG, ILLEGAL};

    InfospaceSender( xdaq::Application *appl, uint32_t sendBufferSize = INFOSPACEBROWSER_DEFAULT_BUFFSIZE );
    ~InfospaceSender();

    void setSendBufferSize( uint32_t bufferSize );
    bool registerInfoSpace( xdata::InfoSpace *infoSpace ) throw( xcept::Exception );
    void unregisterInfoSpace( xdata::InfoSpace *infoSpace ) throw( xcept::Exception );
    void sendInfospaceData( std::string ifname = "",DataType datatype = INFOSPACEDATA ) 
      throw( xcept::Exception );
    bool ugmonActive() const;
    std::string extractIfName( const std::string &orName ) const;
    std::string extractUUID( const std::string &orName ) ;

  private:

    // helper functions:
    void dumpSendBuffer( char* buffer, uint32_t length );

    bool fillInfospaceMetainfo( char** buffer, uint32_t &spaceLeft, 
				uint32_t &length, const std::string &name );
    bool fillInfospaceUnreginfo( char** buffer, uint32_t &spaceLeft, 
				 uint32_t &length, const std::string &name );
    bool fillInfospaceData( char** buffer, uint32_t &spaceLeft, 
			    uint32_t &length, const std::string &name );
    void fillFrame ( toolbox::mem::Reference *ref, int32_t length, uint16_t messageType ) ;
    void terminate(char** buffer, uint32_t &spaceLeft, uint32_t &length);



    // internal data:

    Logger logger_;
    const int reservedSize_; 

    xdaq::Application *appl_;

    std::map< std::string, std::map<std::string, xdata::Serializable*, std::less<std::string> > > infospacemaps_;
    std::map< std::string, xdata::InfoSpace * > infospaces_;

    std::string applicationName_;
    std::string applicationContext_;
    std::string sessionId_;
    //    uint32_t applicationInstance_;
    //std::string applicationInstanceStr_;
    toolbox::mem::Pool *memPool_;

    uint32_t myTid_;
    uint32_t destinationTid_;
    xdaq::ApplicationDescriptor *receiver_;

    uint32_t sendBufferSize_;
  };
}

#endif
