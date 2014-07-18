/* 
 * myrfb.h
 *
 * This file contains global definitions used by all components, 
 *  namely on host: application, api library, driver and on the NIC by the MCP 
 * 
 * WARNING:
 *   all data structures should be composed of 32-bit (unsigned) integers
 *   (this is to ease copying from host to lanai and byte swap)
 *
 * $Id: myrfb.h 18550 2012-03-23 14:35:36Z frans $
 *
 */

//
// note on 32bit/64bit PC platform
// lanaix is a 32bit big-endian processor
// host PC is either a 32bit / 64bit little-endian processor
// in memory mapped structures both used in lanai and pc do NOT use generic pointers for addresses but explicit 32/64 bit (uint32_t) for now
//   on host PC use myrfb_adr_t (void *) as generic address
//

#ifndef _MYRFB_H_
#define _MYRFB_H_

// the C99 style uint8_t types are picked up in user state from stdint.h, kernel space from linux/types.h and MCP from custom mcp_types.h 

// catch definitions for unit32_t and friends
#if defined (__KERNEL__) || defined (_MCP_)
// do nothing
#else
#include <stdint.h>
#endif

//
// version number to trap at run-time consistency between api-library and driver
// user can get this from api and check against its own version in this header file
//
// WARNING:
// update the next version number any time a shared data-structure or define is altered in
//   any of the relevant header files
// You must also update version and release files in rpm directory to update the rpm spec file

#define MYRFB_VERSION_MAJOR 5
#define MYRFB_VERSION_MINOR 4
#define MYRFB_VERSION_PATCH 1

//
// type to hold version
//

typedef struct myrfb_version_struct
{
  uint32_t major ;
  uint32_t minor ;
  uint32_t patch ;
} myrfb_version_t;

// generic type for address used on host
// will expand to 32-bit / 64-bit depending on platform
// can NOT be used in data structures shared between host and MCP (need to be explicit there) 

typedef void * myrfb_adr_t ;


// mask type for fbi- and fbo masks

typedef uint32_t myrfb_mask_t;


//
// event-number wrap at 24-bits
// 

#define MYRFB_EVTNO_MASK (0xFFFFFF) 
#define MYRFB_FRL_EVTNO_SHIFT (32-24)

//
// error codes
//

// [when adding error codes, do not forget to add corresponding text in myrfb_err_string() ]  

// errors originating from host-side
#define MYRFB_ERR_NOT_SUPPORTED                  1
#define MYRFB_ERR_ILL_UNIT                       2
#define MYRFB_ERR_ILL_UNITNO                     3
#define MYRFB_ERR_SYS_OPEN                       4
#define MYRFB_ERR_UNIT_NOT_FOUND                 5
#define MYRFB_ERR_INCOMPATIBLE_DRIVER_VERSION    6
#define MYRFB_ERR_ILL_FRL_BLOCKSIZE              7
#define MYRFB_ERR_STATEX_STATE_ERROR             8
#define MYRFB_ERR_STATEX_STATE_PANIC             9
#define MYRFB_ERR_STATEX_TIMEOUT                0xA
#define MYRFB_ERR_RECV_FREE_BUF_Q_FULL          0xB
#define MYRFB_ERR_ILL_NET_TYPE                  0xC
#define MYRFB_ERR_ILL_NET_ADR                   0xD
#define MYRFB_ERR_ILL_FB_CONFIG                 0xE
#define MYRFB_ERR_NO_NET_CONFIG                 0xF
#define MYRFB_ERR_NO_FB_CONFIG                  0x10
#define MYRFB_ERR_BAD_NETADR                    0x11
#define MYRFB_ERR_ILL_FBI_MASK                 0x12
#define MYRFB_ERR_ILL_FBO_MASK                 0x13
#define MYRFB_ERR_DUPLICATE_NETADR             0x14
#define MYRFB_ERR_FBI_MASK_VOID_NETADR         0x15
#define MYRFB_ERR_FBO_MASK_VOID_NETADR         0x16
#define MYRFB_ERR_FBO_BAD_HOST_BLOCKSIZE       0x17

#define MYRFB_ERR_RECV_SLOT_BUSY                0x20
#define MYRFB_ERR_RECV_SLOT_NOT_POSTED          0x21

#define MYRFB_ERR_RECV_NOT_READY                0x22

#define MYRFB_ERR_ANY  0x100
#define MYRFB_ERR_RECV_CHAOS  0x101



// errors originating from MCP - fatal conditions from logic

#define MYRFB_ERR_MCP_UNSPECIFIED            0x10000

#define MYRFB_ERR_MCP_OUT_OF_MEMORY          0x10001
#define MYRFB_ERR_MCP_DISPATCH_ERROR         0x10002
#define MYRFB_ERR_MCP_NO_RCVBUFFER_P0        0x10003
#define MYRFB_ERR_MCP_NO_RCVBUFFER_P1        0x10004
#define MYRFB_ERR_MCP_OUT_OF_DESCR           0x10005
#define MYRFB_ERR_MCP_WRONG_SUBTYPE          0x10006
#define MYRFB_ERR_MCP_FBO_RECV               0x10007
#define MYRFB_ERR_MCP_BROKEN_DRD_CHAIN       0x10008
#define MYRFB_ERR_MCP_MISROUTED              0x10009
#define MYRFB_ERR_MCP_BAD_LFBO               0x1000A
#define MYRFB_ERR_MCP_BAD_DST_ADR            0x1000B
#define MYRFB_ERR_MCP_BAD_ROUTE              0x1000C

#define MYRFB_ERR_MCP_BAD_Q_DMA0              0x1000D
#define MYRFB_ERR_MCP_BAD_RECV_FREE_BUF       0x1000E
#define MYRFB_ERR_MCP_BAD_Q_RCVBUF_P0         0x1000F
#define MYRFB_ERR_MCP_BAD_Q_RCVBUF_P1         0x10010
#define MYRFB_ERR_MCP_BAD_RECV_BUF_PCI_ADR    0x10011
#define MYRFB_ERR_MCP_BAD_SEQ                 0x10012
#define MYRFB_ERR_MCP_NO_SEND_PENDING         0x10013

#define MYRFB_ERR_MCP_NACK_EMPTY_Q          0x10014
#define MYRFB_ERR_MCP_NACK_BAD_SEQ          0x10015

#define MYRFB_ERR_MCP_BROKEN_FBI_MAP_BUSY   0x10016

#define MYRFB_ERR_MCP_SPURIOUS              0x10017
#define MYRFB_ERR_MCP_NO_HOST_BLOCK_DESCR   0x10018
#define MYRFB_ERR_MCP_BAD_Q_HOST_BLOCK_DMA  0x10019
#define MYRFB_ERR_MCP_BAD_EVB_MATRIX_INDEX  0x10020
#define MYRFB_ERR_MCP_BAD_OSTREAM           0x10021
#define MYRFB_ERR_MCP_NO_OSTREAM            0x10022
#define MYRFB_ERR_MCP_BAD_OUTPUT_STATE      0x10023

#define MYRFB_ERR_MCP_DISPATCH_LOOP         0x10024
#define MYRFB_ERR_MCP_WRONG_LFBU            0x10025 
#define MYRFB_ERR_MCP_NULL_HOST_BLOCK       0x10026
#define MYRFB_ERR_MCP_HOST_BLOCK_BAD_STATE  0x10027

#define MYRFB_ERR_MCP_FRLC_DMA_PENDING      0x10028
#define MYRFB_ERR_MCP_NO_HOST_BLOCK         0x10029

#define MYRFB_ERR_MCP_BAD_CREDIT_RBUF_WIN   0x10030
#define MYRFB_ERR_MCP_BAD_CREDIT_RBUF_SEQ   0x10031

// errors originating from MCP - related to bad input from FRL
#define MYRFB_ERR_MCP_FRL_BAD_SEQUENCE_SEGNO 0x20001
#define MYRFB_ERR_MCP_FRL_BAD_SEQUENCE_EVTNO 0x20002
#define MYRFB_ERR_MCP_FRL_SEGSIZE_TOO_BIG    0x20003

//
// definition of FSM states and commands
// this is the FSM of the FB application, not the lanaikit
//


#define MYRFB_STATE_NULL 0

#define MYRFB_STATE_ERROR -1
#define MYRFB_STATE_PANIC -2

#define MYRFB_STATE_BOOTED  1


//#define MYRFB_STATE_STANDBY  2
#define MYRFB_STATE_HALTED 2

#define MYRFB_COMMAND_CONFIGURE 3
#define MYRFB_STATE_CONFIGURED  3

#define MYRFB_COMMAND_ENABLE 4
#define MYRFB_STATE_ENABLED  4

#define MYRFB_COMMAND_RUN 5
#define MYRFB_STATE_RUNNING 5

#define MYRFB_COMMAND_HALT 6
// halting can take a while because it attempts to empty all queues
#define MYRFB_STATE_HALTING 6

#define MYRFB_STATE_SYNCLOST 7

//#define MYRFB_COMMAND_CLOSE 8
// guess closing no longer needed because goes to Standby
//#define MYRFB_STATE_CLOSING 8  

//
// type to hold the state of the myrfb FSM
//

typedef struct myrfb_state_struct
{
  int32_t code;			// should be one of the values defined as MYRFB_STATE_XX
} myrfb_state_t;

//
// type to hold diagnostics words
//

#define MYRFB_DIAG_N (8)

typedef struct myrfb_diag
{
  uint32_t d[MYRFB_DIAG_N];
} myrfb_diag_t;

//
// type with net configuration info 
//

//
// The network consists of a number of nodes.  Each node is identified by an address.
// The address is a small non-negative number in the range [0..MYRFB_NET_MAX_NODES-1]
// A node corresponds to a L2XP NIC, and not to one of the individual ports (P0 or P1) of the L2XP.
// Instead, the two ports are used to construct a two-rail network 
// The MCP selects the port to use for sending the packets, where a packet sent from port P0 (P1)
//    will be routed to port P0 (P1) of the receiving node    
//     

// running with 2048 nodes requires large malloc chunks which sometimes gives problems
//  TODO: remove some malloc() and free() in driver

#define MYRFB_NET_MAX_NODES (2048)
//#define MYRFB_NET_MAX_NODES (64)

#define MYRFB_NET_TYPE_VOID  0	// no connection

// symmetric two-rail networks
// all P0's are connected to one switch, and all P1's to the second in the same way
// The numbering scheme of the external ports of the switches is the same as for MAZE
//

#define MYRFB_NET_TYPE_P2P      1	// point-to-point connection (without switch in between)
#define MYRFB_NET_TYPE_M3E16    2	// dual-rail M3E16
#define MYRFB_NET_TYPE_M3E128   3	// dual-rail M3E128

#define MYRFB_NET_TYPE_M3E128_2RAIL_BISECT   4	// dual-rail M3E128 b32 rail-0 switch ports 0-63  rail-1 switch ports 64-127
#ifdef OBSOLETE
#define MYRFB_NET_TYPE_M3E128_CESSY   6	// dual-rail M3E128 cessy rail-1 0-63 swapped 64-127
#endif

#define MYRFB_NET_TYPE_M3E256_1RAIL_P0 10 // one-rail P0 256 nodes by single M3E256
#define MYRFB_NET_TYPE_M3E256_1RAIL_P1 11 // one-rail P1 256 nodes by single M3E256
#define MYRFB_NET_TYPE_M3E256_2RAIL_SYM 12 // dual-rail 256 nodes by two M3E256 switches in symmetric config
#define MYRFB_NET_TYPE_M3E256_2RAIL_BISECT 12 // dual-rail 128 nodes by single M3E256 switches, bisected linecards 0-7 for P0, 12-19 for P1  

// fabric contructed out of two M3E256 connected by intercrate quad line cards

#define MYRFB_NET_TYPE_DUAL_M3E256_1RAIL_P0 13 // one-rail P0 512 nodes by dual M3E256
#define MYRFB_NET_TYPE_DUAL_M3E256_1RAIL_P1 14 // one-rail P1 512 nodes by single M3E256
#define MYRFB_NET_TYPE_DUAL_M3E256_2RAIL_SYM 15 // dual-rail 512 nodes by two daul M3E256 switches in symmetric config
#define MYRFB_NET_TYPE_DUAL_M3E256_2RAIL_BISECT 16 // dual-rail 256 nodes by dual M3E256 switches, bisected linecards 0-7 for P0,12-19 for P1  

// fabric out of M3E256 in USC 
//
// _TEST for minidaq
// 2 rails by symmetric configuration: P0 in lower crate, P1 in upper crate   
// linecard 0 = monitor
// linecard 1  adr 0-15  bottum to top (label 16-31)
//          2-8   16 - 125 
// linecard  9 quad adr  256 - 321  top-to-bottum (label 0-16)
// linecard 10 quad      322 - 
// linecard 11 quad 
// linecard 12 quad 
// linecard 13 adr 128 - 143
// linecard 14 adr  
// linecard 15 adr  
// linecard 16 adr  
// linecard 17 adr  
// linecard 18 adr 208 - 223  
// linecard 19 adr 224 
// linecard 20 adr 240 - 255 

//          
//

#define MYRFB_NET_TYPE_M3E256_2RAIL_SYM_USC_TEST 17
#define MYRFB_NET_TYPE_M3E256_2RAIL_SYM_USC_SCX 18


typedef struct myrfb_netid_struct
{
  // warning: this structure must be a multiple of 8-bytes (for alignment of routes in MCP) 
  int32_t net_type;			// type of network (see defines MYRFB_NET_TYPE_XX above)
  int32_t net_adr;			// address of this node on the network 
  int32_t routing_policy;		// not yet used 
  int32_t pad;			// pad to multiple of 8-bytes
} myrfb_netid_t;


// individual route
// this struct supports up to 8 Xbar hops
// take care of alignment (in the MCP hops[] must be 8-byte aligned)

typedef struct myrfb_route_struct
{
  int32_t nmb_hops;			//
  int32_t pad;
  uint8_t hops[8];			// the routing bytes; hops[0] is for first Xbar encountered
} myrfb_route_t;

//
// routing table for a particular port
// gives route to traverse network of Xbars from port PX on sender NIC to port PX on receiver NIC (where PX=P0,P1) 
// Hence, a packet received at port P0 is always sent from P0, and anologously for P1

typedef struct myrfb_xport_routing_table_struct
{
  myrfb_route_t routes[MYRFB_NET_MAX_NODES];
} myrfb_xport_routing_table_t;

// routing table for one nic 
// this is the aggregate of the routing tables of the two ports p0 and p1

typedef struct myrfb_nic_routing_table_struct
{
  myrfb_xport_routing_table_t routing_xports[2];
} myrfb_nic_routing_table_t;

//
// 
// network routing configuration collected into a single structure
//

typedef struct myrfb_net_routing_struct
{
  myrfb_nic_routing_table_t nic_routing_table;
} myrfb_net_routing_t;


//
//  
// number of blocks in FBI

#define MYRFB_FBI_NMB_BLOCKS 256

//
// configuration info for the FB (fed-builder) ..
//


//
// 
// FBI = FED Builder Input
// FBO = FED Builder Output aka RUI
//
// lfbi = logical unit FBI 
// lfbo = logical unit FBO
// logical unit numbers are small non-negative integers [0..MYRFB_FB_MAX_NMB_LFBU-1]
//
// the participating FBIs and FBOs are represented in mask (bit lfbi set in the mask means lfbi is participating)
// because of the use of an (32-bit) integer for the masks  MYRFB_FB_MAX_NMB_LFBU <= 32
//

//#define MYRFB_MAX_NMB_LFBU 16
#define MYRFB_MAX_NMB_LFBU 31

//
// type to implement the conversion table between lfbu and network-address
// 

#define MYRFB_NETADR_VOID (-1)

typedef struct myrfb_lfbu2adr_table_struct
{
  // translation between logical unit to myrinet network address number
  // index = lfb ; value is address
  // note: non-existent logical units must have address set to MYRFB_NETADR_VOID
  int32_t lfbu2adr[MYRFB_MAX_NMB_LFBU];
} myrfb_lfbu2adr_table_t;

//
// destination assignment based on the event-number in the FRL header
// 

//#define MYRFB_NMB_DEST_TABLE_ENTRIES 256
//#define MYRFB_DEST_TABLE_NUM_BITS 8
//#define MYRFB_EVTNO_DEST_MASK (0xFF)

#define MYRFB_NMB_DEST_TABLE_ENTRIES 1024
#define MYRFB_DEST_TABLE_NUM_BITS 10
#define MYRFB_EVTNO_DEST_MASK (0x3FF)

typedef struct myrfb_dest_table_struct
{
  // index is trigno & MASK
  // value is lfbo 
  int32_t evtno2lfbo[MYRFB_NMB_DEST_TABLE_ENTRIES];
} myrfb_dest_table_t;

// possible values for myrfb_init_config_t.fbappl

#define MYRFB_FBAPPL_NULL 0	// null application
#define MYRFB_FBAPPL_FBI  1	// FED-builder Input ie FRL side
#define MYRFB_FBAPPL_FBO  2	// FED-builder Output ie RUI PC side


//
// configuration info known at initialisation time
// ie when module gets initiialised
// this info is put immediately after mcp load-and-init
//

typedef struct myrfb_init_config_struct
{
  // general - can move to lanaikit
  uint32_t mcp_size ;   // mcp size in bytes (is probably equal to text section)
  //
  int32_t fbappl;			// fb application - must be FBI or FBO (or null)
  // relevant for FBI
  uint32_t frl_version ;             // to optionally switch between FRL versions
  // WARNING: for 64-bit
  // keep this explicitely 32 bit for now !!! because it is shared by both host and MCP
  uint32_t frl_base_pci32;	// the base address of the FRL as seen from the Myrinet NIC
  uint32_t fbi_nmb_blocks;		// the number of blocks inside the FBI to buffer the data coming from the FRL
  //  uint32_t frl_blocksize ;    // FRL block-szie in bytes. includes the FED header+trailer, but excludes the 6 32-bit FRL-header words
} myrfb_init_config_t;



// 

#define MYRFB_FB_OPTION_DISCARD_IN_NIC 0x1
#define MYRFB_FB_OPTION_CHECK_FRL_DATA 0x2
// the NO_BUILDING option has to be set in all fedbuilder peers ie FBIs included
// [is is needed in the FBI to disable the event-number credit]
#define MYRFB_FB_OPTION_NO_BUILDING    0x4

// for debugging FBI
// MYRFB_FB_OPTION_MARK_FRL_BLOCKS 
// it zeroes the frl blocks in the fbi before they are written by the frl-fpga.
//  this makes the FBI very slow
#define MYRFB_FB_OPTION_MARK_FRL_BLOCKS 0x8

typedef struct myrfb_fb_config_struct
{
  uint32_t fb_options_mask;		// operation options flagged by bits
  uint32_t xports_mask;		// bitmask of which of the two xports (P0,P1) to use, ie
  // =x0: no ports =x1: P0 =x2: P1 =x3: both ports  (all nodes communicating should use same value)
  // destination assignment info
  // note that all of this info has to be given to all participating FBIs and FBOs
  myrfb_dest_table_t fb_dest_table;	// destination table based on event-number in FRL header
  myrfb_mask_t fbi_mask;	// mask of participating FBIs
  myrfb_mask_t fbo_mask;	// mask of participating FBOs
  myrfb_lfbu2adr_table_t lfbi2adr;	// net-adr lookup table FBIs 
  myrfb_lfbu2adr_table_t lfbo2adr;	// net-adr lookup table FBOs
  // this_lfbu is the lfbu of FBI or FBO of this node. 
  // it should not be specified by the user of the API, as the value is calculated by the myrfb host side
  //    from the info of the net_config and the bet-adr lookup tables above in this structure
  int32_t this_lfbu ;
  // FBO only
  uint32_t host_recv_blocksize;	// in bytes.
} myrfb_fb_config_t;


// type with configuration info for the FBI only

typedef struct myrfb_fbi_config_struct
{
  int32_t dummy;
} myrfb_fbi_config_t;


// type with configuration info for the FBO only

typedef struct myrfb_fbo_config_struct
{
  // nic2host ..
  // host_receiver
  //  uint32_t host_recv_blocksize;	// in bytes.
  // PCI window can be useful for checks 
  uint32_t pci_window_lower;	// lowest PCI address of any buffer posted 
  uint32_t pci_window_upper;	// highest PCI address of any buffer posted
} myrfb_fbo_config_t;




//
// type with monitoring info collected from the FRL data passing through
//

typedef struct myrfb_frl_moni_struct
{
  // snapshot values
  uint32_t last_evtno_from_frl;
  uint32_t last_segno_from_frl;
  // counters incrementing from start onwards
  uint32_t cnt_blocks_from_frl;
  uint32_t cnt_evts_from_frl;
  uint32_t cnt_evts_from_frl_bad_crc_slink;	// last segment of event fragment has bit set indicating bad CRC on FED data 
  uint32_t cnt_evts_from_frl_bad_crc_fed;	// last segment of event fragment has bit set indicating bad CRC on FED data 
  uint32_t cnt_bad_seq_segno;
  uint32_t cnt_bad_seq_evtno;
  uint32_t cnt_evts_from_frl_bad_header_marker ;
  uint32_t cnt_evts_from_frl_bad_trailer_marker ;
  uint32_t cnt_resync ;
  // latched
  uint32_t last_resync_at_evtno ;
  //
} myrfb_frl_moni_t;

//
// ..
//

typedef struct myrfb_moni_pkt_snd_struct
{
  // snapshot values
  // counters incrementing from start onwards
  uint32_t cnt_snd;
  //
} myrfb_moni_pkt_snd_t;

//
// ..
//

typedef struct myrfb_moni_pkt_rcv_struct
{
  // snapshot values
  // counters incrementing from start onwards
  uint32_t cnt_bad_crc;
  uint32_t cnt_bad_invalid;
  uint32_t cnt_bad_alien;
  uint32_t cnt_bad_len;
  uint32_t cnt_bad_misrouted;
  uint32_t cnt_good;
  uint32_t cnt_dropped;  // good but dropped because not arriving in correct state
  //
} myrfb_moni_pkt_rcv_t;


//
// typedef for sequence numbers
// put it in this header for now as the flow_t in myrfb_mcp.h depends on it 
//

typedef uint32_t myrfb_seq;

// associated macros to compare sequence numbers


#define SEQ_LT(a,b) ((int32_t) ((a)-(b)) < 0)
#define SEQ_LE(a,b) ((int32_t) ((a)-(b)) <= 0)
#define SEQ_GT(a,b) ((int32_t) ((a)-(b)) > 0)
#define SEQ_GE(a,b) ((int32_t) ((a)-(b)) >= 0)

// sliding window
// do NOT modify this - must be compatible with map-array in flows and number of recv-bufs
#define MYRFB_SEQ_WINDOW (8)
//#define MYRFB_SEQ_WINDOW (16)



//
// ..
//

// TODO: change name - also relevant for fbi 

typedef struct myrfb_moni_fbo_rcv_struct
{
  // snapshot values
  uint32_t nmb_rcvbufs_active ;
  uint32_t nmb_rcvbufs_completed ;
  uint32_t nmb_packets_in_rcvbufs ;
  // counters incrementing from start onwards
  uint32_t cnt_no_rcvbuf;
} myrfb_moni_fbo_rcv_t;

//
// ..
//

typedef struct myrfb_moni_host_rcv_struct
{
  // snapshot values
  uint32_t nmb_in_use_by_nic;
  // counters incrementing from start onwards
  uint32_t cnt_completed;
  // incremented by timer in fbo_proc (with a beat of 8 us)
   uint32_t cnt_hostbuf_poll_polls ;
   uint32_t cnt_hostbuf_poll_nobuf ;
} myrfb_moni_host_rcv_t;



//
// ..
//


// selected items from frl-header
typedef struct frlhditem_struct
{
  uint32_t evtno0 ;
  uint32_t evtno1 ;
  uint32_t segsize ;
  uint32_t segno ;
} frlhditem_t ;

#define MAX_FBI_SYNCLOST_FRLHDITEMS 16 

typedef struct myrfb_moni_fbi_synclost_struct
{
  uint32_t cnt_synclost ;
  uint32_t latched_evtno_exp_synclost ;
  uint32_t latched_evtno_rcv0_synclost ;
  uint32_t latched_evtno_rcv1_synclost ;
  // save some frl-header info from the first 16 blocks arriving in sync-lost
  uint32_t nmb_frlhditems ;  // number of elements filled in next array
  frlhditem_t frlhditem[MAX_FBI_SYNCLOST_FRLHDITEMS] ;
} myrfb_moni_fbi_synclost_t;

typedef struct myrfb_moni_flow_struct
{
  uint32_t cnt_bad_reply_wrong_srcadr ;  
  uint32_t bad_reply_wrong_srcadr_last ;
  uint32_t spares[8] ;
} myrfb_moni_flow_t ;


//
// type acting as container for various monitor data 
//

typedef struct myrfb_fb_monitor_struct
{
  //
  uint32_t bufmem_occupancy ; // in NIC - nunber in range [0-100]
  // 
  myrfb_moni_fbi_synclost_t fbi_synclost ;
  // ..
  uint32_t frl_nmb_posted_free_blocks ;   // to be moved to structure somewhere
  uint32_t fbi_nmb_blocks_buffered ;   // to be moved to structure somewhere
  myrfb_frl_moni_t frl ;
  // LX packet interfaces
  myrfb_moni_pkt_snd_t pkt_snd[2];	// packet-interface sender P0, P1
  myrfb_moni_pkt_rcv_t pkt_rcv[2];	// packet-interface receiver P0, P1
  // LX receive buffers
  myrfb_moni_fbo_rcv_t fbo_rcv[2];	// receive-buffers P0, P1 
  // [next struct is cleared by fbo_cmd_configure()]
  myrfb_moni_host_rcv_t fbo_host_rcv;	//
  // ..
  myrfb_moni_flow_t flow ;
} myrfb_fb_monitor_t;


typedef struct myrfb_moni_dispatcher_struct {
  uint32_t isr ;         // hw state
  uint32_t dsp_state ;   // sw state
  // counters incrementing from start onwards
  uint32_t cnt_evts[65];	// index of highest-priority event disptach
} myrfb_moni_dispatcher_t;


typedef struct myrfb_moni_evb_s
{
  // counters for the basic things 
  uint32_t packets_in;
  uint32_t dropped_packets;
  uint32_t output_flushes;
  uint32_t output_retries;
  uint32_t output_retries_with_flush;
  uint32_t packets_out;
  uint32_t streams_out;
  uint32_t events_out;
  uint32_t last_event_id_received;
  uint32_t last_event_id_sent;
  uint32_t checkpoint;
  uint32_t checkpoint_data[10];
  uint32_t nmb_evts_in_matrix ; 
  /* See later for a superfragment dump */
} myrfb_moni_evb_t;


//
// next is needed by user and driver, but NOT mcp

// type to identify location of Myrinet NIC on the PCI bus 

typedef struct myrfb_pcibus_struct
{
  uint32_t bus;
  uint32_t slot;
  uint32_t func;
} myrfb_pcibus_t;

// type to store info on the memory allocation in the MCP  

typedef struct myrfb_mcpmem_struct
{
  uint32_t static_upper;
  uint32_t malloc_lower;
  uint32_t malloc_upper;
} myrfb_mcpmem_t;



#endif /* _MYRFB_H_ */
