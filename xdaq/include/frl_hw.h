/*
 * frl_hw.h  
 * 
 * this file is .. 
 *
 * $Id: frl_hw.h 16983 2011-04-04 10:46:57Z frans $
 *
 * mods:
 * 24-mar-2011 FM with version 5.3.5 frl-header with evtno from link-0 and -1
 * 27-sep-2006 FM rename reserved to status and use for resync
 * 04-sep-2006 FM use explicit types from stdint.h as prepartion for 64 bit
 * 27-mar-2006 FM crc bit for fed
 * 11-may-2005 FM correct comments
 * 09-jul-2004 from frl.h only hw part - renme a little bit
 * 09-may-2003 register layout (pending), change page to block 
 * 12-may-2003 control register (soft reset)        
 * 27-may-2003 CS: changed include file asm/bytorder.h to netinet/in.h
 *                 in order to avoid clashes with XDAQ.
 */


#ifndef _FRL_HW_H
#define _FRL_HW_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _MCP_
  //#include <stdint.h>
#endif

/*************************************************************************
 *
 * data structures and associated typedefs
 *
 *************************************************************************/


/* 
 *
 * all FRL registers are little-endian (LE) (seen from host PC) 
 * the FRL-headers are big-endian (BE) seen from the NIC
 *   but the myrfb-host-software swaps it back to LE before delivering it to user
 *
 * there are two fifos:
 *   fifo_free_block_entry: 1024 entries
 *   fifo_trigger_entry:    1024 entries
 *
 * A trigger descriptor consists of two 32-bit words
 * first word 
 * bits 31-24 (8 bits): source number
 *      23-0  (24 bits): length in 64bit words - including FED head+tail
 * second word 
 * bits 31-24 (8 bits): seed
 *      23-0  (24 bits): event-number
 *
 * range
 */

// TODO: seperate control and control2 !!!


#define FRL_CONTROL_CLEAR_FIFO_FREE_BLOCK (1<<16) 
#define FRL_CONTROL_SOFTRESET          0x00020000	// bit 17
#define FRL_CONTROL_FLUSH_FREE_FIFO    0x00040000	// bit 18
#define FRL_CONTROL_FLUSH_FREE_FIFO_BE 0x00000400    
#define FRL_CONTROL_GENERATOR          0x00800000	// bit 23
#define FRL_CONTROL_ENABLE_LINK0       0x01000000	// bit 24

  /*
   * setting the _FLUSH_FREE_FIFO bit in the control register 
   * will initiate the flush of the free-blocks in the free-block FIFO
   * these will be delivered to the FBI with the FRL_SEGSIZE_FLUSH bit 
   * set in the segsize word of the FRL header. There is no payload
   * for these blocks and the segsize-proper is zero
   */


  typedef struct frl_control_struct
  {
    /* 0x00 */
    uint32_t control;	// configuration and control
    uint32_t fifo_free_block_entry;
    uint32_t fifo_trigger_entry;
    uint32_t pad_a1[1];
    uint32_t control2;	// control for specific resets    
    uint32_t pad_a2[11];
    /* 0x40 */
    uint32_t nmb_segments;
    uint32_t nmb_triggers;	/* x44 no longer used, superseded by 64b counter at x128 */
    uint32_t current_trigno;	/* x48 not sure still filled */
    uint32_t nmb_free_blocks ;	/* 4C */
    uint32_t nmb_triggers_pending;	/* 50 for block-2 only */
    uint32_t pad_b[11];
    /* 0x80 */
    uint32_t block_size_bytes;	/* better: block size (payload) in bytes */
    uint32_t frl_header_size_32;	/* better: frl header size: in 32b words */
  } frl_control_t;

/*
 * FRL header - in front of each segment
 */

// the items are treated by the myrics as follows
// source: the value set by the FRL is ignored and overwritten for internal use and finally cleared on output
// evtno: this is evtno for link-0 on input (including enable bit), will be the global evtno (of link 0 and 1)
//    on output with all special MSB bits cleared. Note that the evtno is 24-bit
// segno: used and can be re-numbered on output due to the super fragment buildinf and change of block-size on output
// evtno1: evtno for link-1 on input, cleared on output
// segsize: note that this word is used to indicate the end of transfer of the block (a.k.a. segment) by the FRL by
//   a non-zero value. Hence, in order to avoid race conditions, this must be the last word transferred by the FRL.
//   This word is used and can be resized on output if the block-size is different on output.
//   clearly LAST_SEGM bit is used as well
//   CRC bits used to count statistics on FRL side in /proc file
//   CRC bits or'red on output if change of block-size   
//    

  typedef struct frlh_struct
  {
    uint32_t source;
    uint32_t evtno;
    uint32_t segno;
    uint32_t evtno1;
    uint32_t segsize;
    uint32_t status;
  } frlh_t;


#define FRL_MAX_FREE_BLOCKS 1024
#define FRL_GEN_SIZE_TRIGGER_FIFO 1024

  //#define FRL_GEN_TRIGNO_MASK  0x00FFFFFF
#define FRL_GEN_SOURCE_MASK  0x000000FF
  //#define FRL_GEN_FRAGLEN_MASK  0x00FFFFFF


#define FRL_EVTNO_MASK   0x0FFFFFFF
#define FRL_EVTNO_LINKENABLED 0x80000000

#define FRL_SEGSIZE_LAST_SEGM   0x80000000
#define FRL_SEGSIZE_BAD_CRC_SLINK     0x40000000    /* s-link */
  /* warning when the FLUSH bit is set, the LAST_SEGM bit can also be set */
#define FRL_SEGSIZE_FLUSH       0x20000000
#define FRL_SEGSIZE_BAD_CRC_FED 0x10000000    /* fed */
#define FRL_SEGSIZE_SIZE_MASK   0x0FFFFFFF


#define FRL_STATUS_RESYNC 0x80000000

#ifdef __cplusplus
}
#endif
#endif				/* _FRL_HW_H_ */
