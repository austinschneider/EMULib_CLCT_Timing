/*
 * myrfb_uts_api.h  
 * 
 * this file contains definitions of utility routines used by test programs 
 *
 *
 * $Id: myrfb_uts_api.h 16773 2011-01-17 13:40:20Z frans $
 *         
 * todo:
 *
 */


#ifndef _MYRFB_UTS_API_H
#define _MYRFB_UTS_API_H


#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdio.h>
  
#include "myrfb.h"

/*************************************************************************
 *
 * data structures and associated typedefs
 *
 *************************************************************************/
  

#define FEDBLD_CONFIG_MAX_ELMS 32

typedef struct myrfb_uts_fedbld_config_struct {
  //  int my_net_adr ;
  uint32_t xports ;     // bitmask of xports
  uint32_t nmb_inps ;   // number of inputs in array
  uint32_t nmb_outs ;   // number of outputs in array
  int32_t net_adr_inps [FEDBLD_CONFIG_MAX_ELMS] ;  // network addresses of inputs
  int32_t net_adr_outs [FEDBLD_CONFIG_MAX_ELMS] ;
} myrfb_uts_fedbld_config_t ;



/*************************************************************************
 *
 * function prototypes
 * in general all functions return non-zero for error
 * 
 *************************************************************************/


// utility functions



/*************************************************************************
 * 
 * myrfb_uts_get_fedbld_config_for_netid (char *filename, myrfb_netid_t *p_netid, myrfb_ut_fedbld_config_t *p_conf, char *err_str, int err_str_len)
 *
 * parse fed-builder configuration file and get the fedbuilder configuration corresponding to the specified netid 
 *
 * 
 * 
 * note:
 *  
 *  returns 
 *  0  OK
 *  1  cannot open file
 *  2  net_adr not found
 *  3  net_adr occurred multiple times
 *  4  syntax error
 *  5  too many input or output netadr's
 *
 *************************************************************************/

// WARNING: check types for 64-bit

 myrfb_return_t
 myrfb_uts_get_fedbld_config_for_netid (char *filename, myrfb_netid_t *p_netid, myrfb_uts_fedbld_config_t *p_conf, char *err_str, int err_str_len) ;

  

#ifdef __cplusplus
}
#endif
#endif				/* _MYRFB_UTS_API_H_ */
