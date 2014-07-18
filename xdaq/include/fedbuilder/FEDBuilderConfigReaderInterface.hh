#ifndef __FEDBuilderConfigReaderInterhace_hh_
#define __FEDBuilderConfigReaderInterhace_hh_

#include <string>

#include "myrfb.h"
#include "myrfb_api.h"
#include "myrfb_uts_api.h"

namespace fedbuilder 
{

  class FEDBuilderConfigReaderInterface {
    
  public:
    
    virtual ~FEDBuilderConfigReaderInterface() {}; 
    
    
    /*
     * Should be usable from non-xdaq applications.
     * Therefore no use of xdaq-exceptions or similar.
     * Just error codes. 
     */
    virtual int getConfiguration( myrfb_netid_t *p_netid, 
				  myrfb_uts_fedbld_config_t *p_conf, 
				  std::string &errorString ) = 0;
    
    uint32_t getMaskPosition();
    
  };

} /* namespace fedbuilder */

#endif /* __FEDBuilderConfigReaderInterhace_hh_ */
