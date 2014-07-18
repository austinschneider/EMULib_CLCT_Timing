/**********************************************************************
 * All software on this website is made available under the following 
 * terms and conditions.  By downloading this software, you agree to 
 * abide by these terms and conditions with respect to this software.
 * 
 * I2O SIG All rights reserved.
 *
 * These header files are provided, pursuant to your I2O SIG membership
 * agreement, free of charge on an as-is basis without warranty of any 
 * kind, either express or implied, including but not limited to, 
 * implied warranties or merchantability and fitness for a particular 
 * purpose.  I2O SIG does not warrant that this program will meet the 
 * user's requirements or that the operation of these programs will be 
 * uninterrupted or error-free.  Acceptance and use of this program 
 * constitutes the user's understanding that he will have no recourse 
 * to I2O SIG for any actual or consequential damages including, but 
 * not limited to, loss profits arising out of use or inability to use 
 * this program.
 *
 * Member is permitted to create deriavative works to this header-file 
 * program.  However, all copies of the program and its derivative 
 * works must contain the I2O SIG copyright notice.
 *********************************************************************/

/**********************************************************************
 * i2odep.h -- I2O Dependencies
 *
 * NOTE:  This file is a template for the real i2odep.h  It provides 
 *        place holders for architecture and compiler dependencies. 
 *        It should be filled in and renamed as i2odep.h.  i2odep.h 
 *        is included by i2otypes.h. <xxx> marks the places to fill.
 *
 *        This file also contains the definition of the I2O Class 
 *        Organization ID.  
 **********************************************************************/

#ifndef __INCi2odeph
#define __INCi2odeph

#define I2ODEP_REV 1_5_5   /* I2O Dependency header file revision string */

#if !defined(BIG_ENDIAN__) && !defined(LITTLE_ENDIAN__)
    #error ERROR: An endian type must be defined
#endif

#ifndef ARCH
#define ARCH unknown_arch
#endif
#ifndef BSP
#define BSP unknown_bsp
#endif

/* Architecture-independent ProcessorVersion and ObjCodeFormat definitions */

#define I2O_IOP_PROC_VERSION_DEFAULT            0x00
#define I2O_IOP_OBJ_CODE_FORMAT_DEFAULT         0x00


#define PRAGMA_ALIGN_PUSH
#define PRAGMA_ALIGN_POP
#define PRAGMA_PACK_PUSH 
#define PRAGMA_PACK_POP 

#ifdef linux
#ifndef __KERNEL__
#include <stdint.h>
#else
#include <asm/types.h>
#endif
#endif

#ifdef NOT_WORKING
#if (CPU_FAMILY == I960)
#error "BYE"
/*
 * Pragma macros. These are to assure appropriate alignment between
 * host/IOP as defined by the I2O Specification. Each one of the shared
 * header files includes these macros.
 */


#define PRAGMA_ALIGN_PUSH   #pragma align 4
#define PRAGMA_ALIGN_POP    #pragma align 0
#define PRAGMA_PACK_PUSH    #pragma pack 1
#define PRAGMA_PACK_POP     #pragma pack 0



/* Architecture-specific processor versions and object code formats.
 * These values are dependent on processor type, and are defined by
 * the processor vendor.
 */

#define I2O_IOP_PROC_VERSION_INTEL_80960_RP_RD  0x00
#define I2O_IOP_PROC_VERSION_INTEL_80960_RM_RN  0x01

#define I2O_IOP_OBJ_CODE_FORMAT_COFF_INTEL_CTOOLS   0x00
#define I2O_IOP_OBJ_CODE_FORMAT_ELF                 0x01
#define I2O_IOP_OBJ_CODE_FORMAT_WRS_COMPRESSED      0x20


#elif (CPU_FAMILY == ARM)
#error "CIAO"
/*
 * Pragma macros. These are to assure appropriate alignment between
 * host/IOP as defined by the I2O Specification. Each one of the shared
 * header files includes these macros.
 */

#define PRAGMA_ALIGN_PUSH   
#define PRAGMA_ALIGN_POP    
#define PRAGMA_PACK_PUSH    #pragma pack(1)
#define PRAGMA_PACK_POP     #pragma pack()

/* Architecture-specific processor versions and object code formats.
 * These values are dependent on processor type, and are defined by
 * the processor vendor.
 */

#define I2O_IOP_PROC_VERSION_ARM_STRONGARM_110  0x00
#define I2O_IOP_PROC_VERSION_ARM_STRONGARM_120  0x01

#define I2O_IOP_OBJ_CODE_FORMAT_COFF_GNU        0x00
#define I2O_IOP_OBJ_CODE_FORMAT_WRS_COMPRESSED  0x20

#elif (CPU_FAMILY == SPARC)
#define PRAGMA_ALIGN_PUSH
#define PRAGMA_ALIGN_POP
#define PRAGMA_PACK_PUSH
#define PRAGMA_PACK_POP 
#elif (CPU_FAMILY == I80X86 )

#define PRAGMA_ALIGN_PUSH
#define PRAGMA_ALIGN_POP
#define PRAGMA_PACK_PUSH 
#define PRAGMA_PACK_POP 
#else

#error "The CPU type is not supported"

#endif /* end #if (CPU_FAMILY == I960) */

#endif // Not working
/* Setup the basics */

typedef    char   S8;
typedef    short  S16;

typedef    unsigned char  U8;
typedef    unsigned short U16;

typedef    unsigned int   U32;
typedef    int            S32;


/* Bitfields */

typedef    U32  BF;

/* VOID */
#ifndef __VOID
	#ifndef vxworks
		/* vxworks conflict */
		typedef    void  VOID;
	#endif
#define __VOID
#endif


/* Boolean */


#ifndef __BOOL
#define __BOOL
	#ifndef vxworks
		/* vxworks conflict */
		typedef int BOOL;
	#endif



#endif

/*#endif //vxWorks conflict*/
/* NULL */

#ifndef NULL
#define NULL  0
#endif

/* Substitute your company assigned Organization ID here.  See the I2O
   SIG (tm) web site for more details.    */
#define    I2O_CLASS_ORGANIZATION_ID                   0x0000

#endif /* __INCi2odeph */
