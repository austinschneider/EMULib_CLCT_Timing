/*
 * myrfb_api.h  
 * 
 * this file contains definitions for the host API
 *
 *
 * $Id: myrfb_api.h 16773 2011-01-17 13:40:20Z frans $
 *         
 * todo:
 *
 */


#ifndef _MYRFB_API_H
#define _MYRFB_API_H

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
  
// generic return code for all API functions
// non-zero indicates fatal error (ie makes no sense to continue)
// the numeric values are specified in the myrfb.h header value

typedef int32_t myrfb_return_t;

// myrfb state code - just use int32_t 

//typedef int32_t myrfb_state_code_t;


// opaque type used as a handle to identify a particular Myrinet NIC

typedef struct myrfb_unit_struct
{
  int32_t unitno;			// unit number as allocated by the system. corresponds to device minor number  
  int32_t fd;			// associated file descriptor once device has been opened
} myrfb_unit_t;

//
// message send/recv (datagram) operations are done with handles to the buffers where the messages are stored
// it is the responsibility of the caller to allocate/free the memory for both the handles and the
//   message buffers to which they point
// the message buffers must be in pinned DMAable memory
// 

typedef struct myrfb_handle_struct
{
  // next field is used by library to build event structural information
  struct myrfb_handle_struct *next ;  // must not be touched by the user 
  int32_t status;			// on recv - non-zero status indicates error condition 
  int32_t len;			// on recv - length of message in bytes
  //  int src ;
  //  int dst ;
  // WARNING: careful with 64-bit - this structure is only used on host (ie NOT on mcp)
  //   wil expand to 32bit/64bit depending on platform
  myrfb_adr_t adr_bus;	// address of the buffer as seen from PCI
  myrfb_adr_t adr_user;	// address of the buffer as seen from user space
  // WARNING: next field to be revisited
  // free for user as a place holder for anything - not altered by myrfb
  uint32_t uint32_user;			
  uint64_t uint64_user;		
  void *ptr_user;		
  //  int rcv_used ;
  //  int rcv_bsx ;
} myrfb_handle_t;


/*************************************************************************
 *
 * function prototypes
 * in general all functions return non-zero for error
 * 
 *************************************************************************/

//
// get version number of API
// so that caller can compare it with his MYRFB_VERSION and abort if it is not consistent at run-time
//

myrfb_return_t myrfb_get_api_version (myrfb_version_t *api_version_p);

//
// utility routine to get error-code decoded as string
// it is the callers responsibility to allocate the string str[] and provide the number 
//   of bytes (including the terminating null-character) as the second argument n
// for convenience the pointer to the string is returned
//

// WARNING: not sure about next one for 64-bit
char *myrfb_err_string (char *str, int n, myrfb_return_t rt);

//
// the myrfb_open_by_xx routines provide the address of a pointer to a myrfb_unit structure
//   the memory of this structure is allocated by the API library
//  the user needs to pass the pointer to this unit stucture to all subsequent API functions
// the three open flavours are mutually exclusive and the _open_by_geoslot can only be used by FBI side

myrfb_return_t myrfb_open_by_unitno (myrfb_unit_t ** u, int32_t unitno);
myrfb_return_t myrfb_open_by_bus (myrfb_unit_t ** u, myrfb_pcibus_t *);
//   the geoslot is the geographical slot number in the cPCI crate and runs from 0 to, where 0 is the 
//   crate controller and the first FRL is in slot 1 (ie NOT 0)
myrfb_return_t myrfb_open_by_geoslot (myrfb_unit_t ** u, int32_t geoslot);

// matching close function 

myrfb_return_t myrfb_close (myrfb_unit_t * u);

//
// states and commands
//

myrfb_return_t myrfb_get_state (myrfb_unit_t * u, myrfb_state_t *);

//
// utility routine to get state number decoded as string
// it is the callers responsibility to allocate the string str[] and provide the number 
//   of bytes (including the terminating null-character) as the second argument n
// for convenience the pointer to the string is returned
//

// WARNING: not sure about next one for 64-bit
char *myrfb_state_string (char *state_text, int n, int32_t state);


//

myrfb_return_t myrfb_get_diag (myrfb_unit_t * u, myrfb_diag_t *);

// network configuration 

myrfb_return_t myrfb_set_netid (myrfb_unit_t * u, myrfb_netid_t *);
myrfb_return_t myrfb_get_netid (myrfb_unit_t * u, myrfb_netid_t *);
myrfb_return_t myrfb_set_net_routing (myrfb_unit_t * u, myrfb_net_routing_t *);

// configuration 

myrfb_return_t myrfb_set_fb_config (myrfb_unit_t * u, myrfb_fb_config_t *);
myrfb_return_t myrfb_set_fbi_config (myrfb_unit_t * u, myrfb_fbi_config_t *);

// the timeout argument of the myrfb_cmd_xx commands is in ms, and 0 as default 
myrfb_return_t myrfb_cmd_configure (myrfb_unit_t * u, int32_t timeout);
myrfb_return_t myrfb_cmd_enable (myrfb_unit_t * u, int32_t timeout);
myrfb_return_t myrfb_cmd_run (myrfb_unit_t * u, int32_t timeout);
myrfb_return_t myrfb_cmd_halt (myrfb_unit_t * u, int32_t timeout);


// misc can be updated at run-time
myrfb_return_t myrfb_set_discard_delay (myrfb_unit_t *u, int32_t nmb_ticks) ;

// utility functions

// construct the routing_table
// input is netid, result is stored in net_routing

myrfb_return_t myrfb_net_construct_routing_table (myrfb_netid_t *netid, myrfb_net_routing_t *net_routing);

myrfb_return_t myrfb_print_net_config (FILE * fp, myrfb_netid_t *netid, myrfb_net_routing_t *net_routing);


myrfb_return_t myrfb_calc_dest_table (myrfb_dest_table_t *ptable, myrfb_mask_t maskfbo);

void myrfb_busywait_us (int32_t number_of_microseconds);

//
// datagram handling (FBO only)
//

//
// Post a receive buffer
//   The following fields of the myrfb_handle_t must be set
//      .adr_bus
//   and optionally 
//      .user
//

myrfb_return_t myrfb_recv_post_buf (myrfb_unit_t * u, myrfb_handle_t * ph);

//
// check if a new receive buffer has been completed
// on return
//  ph is NULL pointer if no new message availabe, or
//  ph points to a handle (previously posted by caller) describing completed message
//   the following fields of the myrfb_handle have than been set
//   .status   0 means OK 
//   .len      length of message in bytes
//   
// note: it should not be relied upon that the buffers are completed in the same order
//    as they are posted
//     


myrfb_return_t myrfb_recv_completed (myrfb_unit_t * u, myrfb_handle_t ** ph);


myrfb_return_t myrfb_recv_get_next_evt_block (myrfb_unit_t *p_u, myrfb_handle_t ** pha) ;

// Monitoring ..

// to obtain the monitoring data structure (specified in myrfb.h)  
// this call is non-intrusive
 
 myrfb_return_t myrfb_get_fb_monitor (myrfb_unit_t * u, myrfb_fb_monitor_t *);

// Advanced routines

myrfb_return_t myrfb_get_mcpmem (myrfb_unit_t * u, myrfb_mcpmem_t *);
myrfb_return_t myrfb_get_moni_dispatcher (myrfb_unit_t * u, myrfb_moni_dispatcher_t *);



#ifdef __cplusplus
}
#endif
#endif				/* _MYRFB_API_H_ */
