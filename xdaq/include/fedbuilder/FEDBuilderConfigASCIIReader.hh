#ifndef __FEDBuilderConfigASCIIReader_hh_
#define __FEDBuilderConfigASCIIReader_hh_

#include <string>
#include "FEDBuilderConfigReaderInterface.hh"

namespace fedbuilder 
{
  
  class FEDBuilderConfigASCIIReader : 
    public FEDBuilderConfigReaderInterface 
  {
    
  public:
    

    FEDBuilderConfigASCIIReader( std::string configStr );

    ~FEDBuilderConfigASCIIReader();
    

    /*
     * Read configuration of fedbuilder into structure p_conf.
     *
     * @param netid contains the network address of the device
     *        for which the configuration is searched in the 
     *        the configuration file.
     *
     * @param errorString contains an error message in case
     *        an error is encountered during the parsing 
     *        of the configuration file.
     */
    int getConfiguration( myrfb_netid_t *p_netid, 
			  myrfb_uts_fedbld_config_t *p_conf, 
			  std::string &errorString );

    uint32_t getMaskPosition() { return outMaskPosition_; };
    
  private:

    // return code

    enum status 
      { 
	status_ok=0, 
	status_no_file, 
	status_no_netadr, 
	status_multiple_netadr,
	status_syntax_error, 
	status_too_many_elements 
      };  
    

    // parser state

    enum parse_state 
      { 
	state_null, 
	state_xports, 
	state_inp, 
	state_out 
      } state ;
    

    
    std::string configuration_;
    uint32_t outMaskPosition_;

  };
  
}; /* namespace fedbuilder */

#endif /* __FEDBuilderConfigASCIIReader_hh_ */
