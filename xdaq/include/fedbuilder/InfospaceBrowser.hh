#ifndef __InfospaceBrowser_hh_
#define __InfospaceBrowser_hh_

// standard stuff
#include <map>

// basic xdaq stuff
#include "xdaq/WebApplication.h"
#include "xdaq/Application.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/NamespaceURI.h"

// i2o definitions
#include "i2o/i2o.h"
#include "i2o/Method.h"
#include "i2o/utils/AddressMap.h"

// xoap definitions
#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"

// for the semaphore
#include "toolbox/BSem.h"

// hyperdaq stuff
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"

#define MAX_INBUF_VECTOR_SIZE 1024
#define UGMON_MAX_CHARS 1024          // maximal number of characters per item in i2o message

namespace fedbuilder
{
   class InfospaceBrowser : public xdaq::WebApplication
   {
   public:
     XDAQ_INSTANTIATOR();

     InfospaceBrowser(xdaq::ApplicationStub * s);

     ~InfospaceBrowser();

    /**
     * The routine to create the hyperdaq web page.
     */
     void defaultWebPage(xgi::Input *in, xgi::Output *out) throw( xgi::exception::Exception );
     void debugWebPage(xgi::Input *in, xgi::Output *out) throw( xgi::exception::Exception );
     void retrieveCatalog(xgi::Input *in, xgi::Output *out) throw( xgi::exception::Exception );
     void retrieveCollection(xgi::Input *in, xgi::Output *out) throw( xgi::exception::Exception );

     /**
      * I2O callback routine invoked when monitoring data are received.
      * Data is immediately processed. This is done only once at startup
      * for every application to be monitored.
      * The following steps are executed:
      * 1) Retrieve the application Identifier and the instance of the appl
      *    from the incoming data and create a new descriptor in the 2 dim
      *    array inBuffers_. Prior to saving the descriptor in the array 
      *    initialize it correctly.
      *    Save a pointer also in a vector for later cleanup.
      * 2) See if there is already metadata for the infospace. If so do nothing.
      *    If there is no entry yet create one:
      *    Retrieve the number of items in the infospace and parse the 
      *    [name type] pairs. 
      *    
      */
     void metaInfoReceived(toolbox::mem::Reference *bufRef);

     /**
      * I2O callback routine invoked to purge an infospace.
      * The message contains the infospace name and the uuid of the infospace.
      * On reception the data map of this infosapce is erased.
      * The call is used by the FRLController where infosapces are newly created
      * for every new run. Data vectors correspoding to old uuids (= old infospaces)
      * need to be deleted in this case. 
      *    
      */
     void purgeInfospace(toolbox::mem::Reference *bufRef);

     /**
      * I2O callback routine invoked when infospace data are recieved.
      * Here some remarks to the algorithm:
      * 1) The aim is not to loose "freshly arriving" monitoring data. 
      *    If monitoring data gets lost (i.e. has not been processed or asked for) 
      *    then it should be the oldest one.
      * 2) There is a thread going around to prepare the soap replies, or the data
      *    processing is triggered only when the soap request comes in. Both of these
      *    possibilities need access to the data: they will lock the buffer and work
      *    through the data before unlocking them again: during this period it is not
      *    possible to throw away or overwrite the old data.
      * 3) From 1) and 2) it follows what seems to be a reasonable algorithm:
      *      - A 2-dimensional array holds pointers to descriptor structors. The indices
      *        are the application identifier and the instance number.
      *      - If a new buffer comes in, the callback tries to lock the descriptor 
      *        for the appl,instance pair
      *           o if no such descriptor exists an error is issued and the incoming buffer freed
      *           o if the descriptor is currently locked, the buffer is put on the 'inbuf-vector'.
      *           o if the descriptor is free, the old buffer referenced there is freed and the
      *             new one is put in place. Then the descriptor is unlocked again.
      *        After one of these steps has been executed a tentative is made to work through
      *        bufferlist of the inbuf-vector' in order to try to get rid of the pending work.
      */
    void dataReceived(toolbox::mem::Reference *bufRef);

   private:
     class IFData {
     public:
       uint32_t size;
       std::string ifname;
       std::string items;
       std::map< std::string, std::string > data;
       IFData()
	 :size( 0 ) {} ;
     };
     
     
     // protected with a semaphore during every access.
     std::map< std::string, IFData* > infoMap_;
     toolbox::BSem mapSem_;

     Logger logger_;
     const int32_t reservedSize_;
     uint32_t cntIncomingData_;
     uint32_t cntIncomingMeta_;
     uint32_t cntIncomingPurge_;
     
     std::string urn_;
   };
 
}
#endif 
