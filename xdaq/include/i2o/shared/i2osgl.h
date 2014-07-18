/****************************************************************
Copyright 1999 I2O Special Interest Group (I2O SIG).  All rights reserved.

TERMS AND CONDITIONS OF USE

This header file, and any modifications of this header file, are provided
contingent upon your agreement and adherence to the here-listed terms and
conditions.  By accepting and/or using this header file, you agree to
abide by these terms and conditions and that these terms and conditions will
be construed and governed in accordance with the laws of the State of
California, without reference to conflict-of-law provisions.  If you do not
agree to these terms and conditions, please delete this file, and any
copies, permanently, without making any use thereof.

THIS HEADER FILE IS PROVIDED FREE OF CHARGE ON AN AS-IS BASIS WITHOUT
WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  I2O SIG DOES NOT WARRANT THAT THIS HEADER FILE WILL MEET THE
USER'S REQUIREMENTS OR THAT ITS OPERATION WILL BE UNINTERRUPTED OR
ERROR-FREE.

I2O SIG DISCLAIMS ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF
ANY PROPRIETARY RIGHTS, RELATING TO THE IMPLEMENTATION OF THE I2O
SPECIFICATIONS.  I2O SIG DOES NOT WARRANT OR REPRESENT THAT SUCH
IMPLEMENTATIONS WILL NOT INFRINGE SUCH RIGHTS.

THE USER OF THIS HEADER FILE SHALL HAVE NO RECOURSE TO I2O SIG FOR ANY
ACTUAL OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT LIMITED TO, LOST DATA
OR LOST PROFITS ARISING OUT OF THE USE OR INABILITY TO USE THIS PROGRAM.

I2O SIG grants the user of this header file a license to copy, distribute,
and modify it, for any purpose, under the following terms.  Any copying,
distribution, or modification of this header file must not delete or alter
the copyright notice of I2O SIG or any of these Terms and Conditions.

Any distribution of this header file must not include a charge for the
header file (unless such charges are strictly for the physical acts of
copying or transferring copies).  However, distribution of a product in
which this header file is embedded may include a charge so long as any
such charge does not include any charge for the header file itself.

Any modification of this header file constitutes a derivative work based
on this header file.  Any distribution of such derivative work: (1) must
include prominent notices that the header file has been changed from the
original, together with the dates of any changes; (2) automatically
includes this same license to the original header file from I2O SIG, without
any restriction thereon from the distributing user; and (3) must include a
grant of license of the modified file under the same terms and conditions as
these Terms and Conditions.

****************************************************************

The I2O SIG Web site can be found at: http://www.i2osig.org

The I2O SIG encourages you to deposit derivative works based on this
header file at the I2O SIG Web site.  Furthermore, to become a Registered
Developer of the I2O SIG, sign up at the Web site or call 415.750.8352
(United States).

****************************************************************/

/*********************************************************************
 * i2osgl.h -- I2O Scatter-Gather List definition file
 *
 * This file contains information presented in Chapter 3 of the I2O(tm)
 * Specification.
 **********************************************************************/

#ifndef _I2O_V2_0_SGL_
#define _I2O_V2_0_SGL_

#define I2OSGL_REV 2_0_0  /* I2OExec header file revision string */

#include "i2otypes.h"

PRAGMA_ALIGN_PUSH

PRAGMA_PACK_PUSH

/****************************************************************************/

/* Element Type Field defines. */
#define    I2O_V2_SGL_LAST_ELEMENT                        0x80

#define    I2O_V2_SGL_ELEMENT_TYPE_FIELD_MASK             0x7F

#define    I2O_V2_SGL_SHORT_ELEMENT_FORMAT                0x70
#define    I2O_V2_SGL_SHORT_ELEMENT_TYPE_MASK             0x0F

/* Element Type defines */
#define    I2O_V2_SGL_TRANSACTION_ELEMENT                 0x70
#define    I2O_V2_SGL_TRANSACTION_BC_ELEMENT              0x71
#define    I2O_V2_SGL_PAGE_LIST_ELEMENT                   0x74
#define    I2O_V2_SGL_FRAGMENT_LIST_ELEMENT               0x75
#define    I2O_V2_SGL_IMMEDIATE_DATA_ELEMENT              0x76
#define    I2O_V2_SGL_TYPES_ELEMENT                       0x77
#define    I2O_V2_SGL_PLATFORM_DECLARATION_ELEMENT        0x7B
#define    I2O_V2_SGL_ATTRIBUTES_ELEMENT                  0x7C
#define    I2O_V2_SGL_CHAIN_POINTER_ELEMENT               0x7D
#define    I2O_V2_SGL_TRANSPORT_ELEMENT                   0x7E
#define    I2O_V2_SGL_IGNORE_ELEMENT                      0x7F

/* Address Size Field element flags defines */
#define    I2O_V2_SGL_ADDRESS_SIZE_U32                    0x00
#define    I2O_V2_SGL_ADDRESS_SIZE_U64                    0x01
#define    I2O_V2_SGL_ADDRESS_SIZE_U96                    0x02
#define    I2O_V2_SGL_ADDRESS_SIZE_U128                   0x03

#define    I2O_V2_SGL_ADDRESS_SIZE_U32_SZ                 0x04
#define    I2O_V2_SGL_ADDRESS_SIZE_U64_SZ                 0x08
#define    I2O_V2_SGL_ADDRESS_SIZE_U96_SZ                 0x0C
#define    I2O_V2_SGL_ADDRESS_SIZE_U128_SZ                0x10

/* SGL Element Flag defines */
#define    I2O_V2_SGL_FLAGS_ADDRESS_SIZE_MASK             0x03
#define    I2O_V2_SGL_FLAGS_LOCAL_ADDRESS                 0x04
#define    I2O_V2_SGL_FLAGS_DIR_OUTPUT_BUFFER             0x40
#define    I2O_V2_SGL_FLAGS_END_OF_BUFFER                 0x80
#define    I2O_V2_SGL_FLAGS_IMMED_DIR_OUTPUT_BUFFER       0x10
#define    I2O_V2_SGL_FLAGS_IMMED_END_OF_BUFFER           0x20

/* SG Size defines */
#define    I2O_V2_SG_COUNT_SZ                             24
#define    I2O_V2_SG_TYPES_SZ                             24
#define    I2O_V2_SG_FLAGS_SZ                             8
#define    I2O_V2_SG_IMMEDIATE_COUNT_SZ                   10
#define    I2O_V2_SG_IMMEDIATE_FLAGS_SZ                   6


/* Flags and Count fields for SG Elements Formats */
typedef struct _I2O_FLAGS_COUNT_SHORT_FORMAT
{
#if defined(LITTLE_ENDIAN__)
    U8                          Reserved;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
#elif defined(BIG_ENDIAN__)
#endif    
} I2O_FLAGS_COUNT_SF, *PI2O_FLAGS_COUNT_SF;

typedef struct _I2O_FLAGS_COUNT_LF
{
#if defined(LITTLE_ENDIAN__)
    BF                          Count:I2O_V2_SG_COUNT_SZ;
    BF                          Flags:I2O_V2_SG_FLAGS_SZ;
#elif defined(BIG_ENDIAN__)
#endif        
} I2O_FLAGS_COUNT_LF, *PI2O_FLAGS_COUNT_LF;


/* SGL Types Element TypeFlags */
#define    I2O_V2_SGL_ATTRIBUTES_TYPE                   0x001
#define    I2O_V2_SGL_CHAIN_POINTER_TYPE                0x002
#define    I2O_V2_SGL_TRANSPORT_TYPE                    0x004
#define    I2O_V2_SGL_IMMEDIATE_DATA_TYPE               0x008
#define    I2O_V2_SGL_FRAGMENT_LIST_TYPE                0x010
#define    I2O_V2_SGL_PAGE_LIST_TYPE                    0x020
#define    I2O_V2_SGL_PLATFORM_DECLARATION_TYPE         0x040
#define    I2O_V2_SGL_TRANSACTION_TYPE                  0x080
#define    I2O_V2_SGL_TRANSACTION_BC_TYPE               0x100
#define    I2O_V2_SGL_IGNORE_TYPE                       0x200


/* Types Element */
typedef struct _I2O_V2_SGE_SGL_TYPES_ELEMENT
{
#if defined(LITTLE_ENDIAN__)
    U16                         TypeFlags;
    U8                          ElementLength;
    U8                          ElementType;
#elif defined(BIG_ENDIAN__)
  U8                          ElementType;
  U8                          ElementLength;
  U16                         TypeFlags;	
#endif    
} I2O_V2_SGE_SGL_TYPES_ELEMENT, *PI2O_V2_SGE_SGL_TYPES_ELEMENT;


/* Chain Pointer Element */
typedef struct _I2O_V2_SGE_CHAIN_ELEMENT_U32_ADDRESS
{
#if defined(LITTLE_ENDIAN__)
    U8                          Reserved;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    U32                         PhysicalAddress;
    U32                         ByteCount;
#elif defined(BIG_ENDIAN__)
#endif    
} I2O_V2_SGE_CHAIN_ELEMENT_U32, *PI2O_V2_SGE_CHAIN_ELEMENT_U32;

typedef struct _I2O_V2_SGE_CHAIN_ELEMENT_U64_ADDRESS
{
#if defined(LITTLE_ENDIAN__)
    U8                          Reserved;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    U64                         PhysicalAddress;
    U32                         ByteCount;
#elif defined(BIG_ENDIAN__)
#endif        
} I2O_V2_SGE_CHAIN_ELEMENT_U64, *PI2O_V2_SGE_CHAIN_ELEMENT_U64;

typedef struct _I2O_V2_SGE_CHAIN_ELEMENT_U96_ADDRESS
{
#if defined(LITTLE_ENDIAN__)
    U8                          Reserved;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    U96                         PhysicalAddress;
    U32                         ByteCount;
#elif defined(BIG_ENDIAN__)
#endif        
} I2O_V2_SGE_CHAIN_ELEMENT_U96, *PI2O_V2_SGE_CHAIN_ELEMENT_U96;

typedef struct _I2O_V2_SGE_CHAIN_ELEMENT_U128_ADDRESS
{
#if defined(LITTLE_ENDIAN__)
    U8                          Reserved;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    U128                        PhysicalAddress;
    U32                         ByteCount;
#elif defined(BIG_ENDIAN__)
#endif        
} I2O_V2_SGE_CHAIN_ELEMENT_U128, *PI2O_V2_SGE_CHAIN_ELEMENT_U128;


/* Ignore Elements */
typedef struct _I2O_V2_SGE_IGNORE_ELEMENT_FORMAT
{
#if defined(LITTLE_ENDIAN__)
    U16                         Reserved;
    U8                          ElementLength;
    U8                          ElementType;
#elif defined(BIG_ENDIAN__)
    U8                          ElementType;
    U8                          ElementLength;
    U16                         Reserved;        
#endif        
} I2O_V2_SGE_IGNORE_ELEMENT, *PI2O_V2_SGE_IGNORE_ELEMENT;


/* Immediate Data Element */
typedef struct _I2O_V2_SGE_IMMEDIATE_DATA_ELEMENT
{
#if defined(LITTLE_ENDIAN__)
    BF                          ByteCount:I2O_V2_SG_IMMEDIATE_COUNT_SZ;
    BF                          ElementFlags:I2O_V2_SG_IMMEDIATE_FLAGS_SZ;
    U8                          ElementLength;
    U8                          ElementType;
    U8                          Data[1];
#elif defined(BIG_ENDIAN__)
    U8                          ElementType;  
    U8                          ElementLength;
    BF                          ElementFlags:I2O_V2_SG_IMMEDIATE_FLAGS_SZ;
    BF                          ByteCount:I2O_V2_SG_IMMEDIATE_COUNT_SZ;
    U8                          Data[1];    
#endif        
} I2O_V2_SGE_IMMEDIATE_DATA_ELEMENT, *PI2O_V2_SGE_IMMEDIATE_DATA_ELEMENT;


/* Page List Element */
typedef struct _I2O_V2_SGE_PAGE_LIST_ELEMENT_U32
{
#if defined(LITTLE_ENDIAN__)
    U8                          AddrCount;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    U32                         ByteCount;
    U32                         PhysicalAddress[1];
#elif defined(BIG_ENDIAN__)
#endif        
} I2O_V2_SGE_PAGE_LIST_ELEMENT_U32 , *PI2O_V2_SGE_PAGE_LIST_ELEMENT_U32;

typedef struct _I2O_V2_SGE_PAGE_LIST_ELEMENT_U64
{
#if defined(LITTLE_ENDIAN__)
    U8                          AddrCount;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    U32                         ByteCount;
    U64                         PhysicalAddress[1];
#elif defined(BIG_ENDIAN__)
#endif        
} I2O_V2_SGE_PAGE_LIST_ELEMENT_U64 , *PI2O_V2_SGE_PAGE_LIST_ELEMENT_U64;

typedef struct _I2O_V2_SGE_PAGE_LIST_ELEMENT_U96
{
#if defined(LITTLE_ENDIAN__)
    U8                          AddrCount;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    U32                         ByteCount;
    U96                         PhysicalAddress[1];
#elif defined(BIG_ENDIAN__)
#endif        
} I2O_V2_SGE_PAGE_LIST_ELEMENT_U96 , *PI2O_V2_SGE_PAGE_LIST_ELEMENT_U96;

typedef struct _I2O_V2_SGE_PAGE_LIST_ELEMENT_U128
{
#if defined(LITTLE_ENDIAN__)
    U8                          AddrCount;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    U32                         ByteCount;
    U128                        PhysicalAddress[1];
#elif defined(BIG_ENDIAN__)
#endif        
} I2O_V2_SGE_PAGE_LIST_ELEMENT_U128 , *PI2O_V2_SGE_PAGE_LIST_ELEMENT_U128;


/* Platform Declaration Element */
typedef struct _I2O_V2_SGE_PLATFORM_DECLARATION_ELEMENT
{
#if defined(LITTLE_ENDIAN__)
    U16                         Reserved;
    U8                          ElementLength;
    U8                          ElementType;
    U32                         Platform;
#elif defined(BIG_ENDIAN__)
#endif        
} I2O_V2_SGE_PLATFORM_DECLARATION_ELEMENT,
  *PI2O_V2_SGE_PLATFORM_DECLARATION_ELEMENT;


/* SGL Attribute Flags defines */
#define    I2O_V2_SGL_ATTRIBUTE_FLAGS_LOCAL_ADDRESS_HINT  0x0100
#define    I2O_V2_SGL_ATTRIBUTE_FLAGS_TRANSACTION_MASK    0x0004
#define    I2O_V2_SGL_ATTRIBUTE_FLAGS_32BIT_TRANSACTION   0x0000
#define    I2O_V2_SGL_ATTRIBUTE_FLAGS_64BIT_TRANSACTION   0x0004

/* SGL Attribute Element */
typedef struct _I2O_V2_SGE_SGL_ATTRIBUTES_ELEMENT
{
#if defined(LITTLE_ENDIAN__)
    U16                         SglAttributeFlags;
    U8                          ElementLength;
    U8                          ElementType;
    U32                         PageFrameSize;
    U32                         SourcePlatform;
#elif defined(BIG_ENDIAN__)
#endif
} I2O_V2_SGE_SGL_ATTRIBUTES_ELEMENT, *PI2O_V2_SGE_SGL_ATTRIBUTES_ELEMENT;


/* Transaction Parameters with Buffer Context Element */
typedef struct _I2O_V2_SGE_TRANSACTION_BC_ELEMENT
{
#if defined(LITTLE_ENDIAN__)
    U16                         ClassFields;
    U8                          ElementLength;
    U8                          ElementType;
    U64                         BufferContext;
    U32                         InfoField[1];
#elif defined(BIG_ENDIAN__)
#endif
} I2O_V2_SGE_TRANSACTION_BC_ELEMENT, *PI2O_V2_SGE_TRANSACTION_BC_ELEMENT;

/* Transaction Parameters Element */
typedef struct _I2O_V2_SGE_TRANSACTION_ELEMENT
{
#if defined(LITTLE_ENDIAN__)
    U16                         ClassFields;
    U8                          ElementLength;
    U8                          ElementType;
    U32                         InfoField[1];
#elif defined(BIG_ENDIAN__)
#endif
} I2O_V2_SGE_TRANSACTION_ELEMENT, *PI2O_V2_SGE_TRANSACTION_ELEMENT;


/* Fragment entries */
typedef struct _I2O_V2_SGE_FRAGMENT_ENTRY_U32
{
    U32                         PhysicalAddress;
    U32                         ByteCount;
} I2O_FRAGMENT_ENTRY_U32, *PI2O_FRAGMENT_ENTRY_U32;

typedef struct _I2O_V2_SGE_FRAGMENT_ENTRY_U64
{
    U64                         PhysicalAddress;
    U32                         ByteCount;
} I2O_FRAGMENT_ENTRY_U64, *PI2O_FRAGMENT_ENTRY_U64;

typedef struct _I2O_V2_SGE_FRAGMENT_ENTRY_U96
{
    U96                         PhysicalAddress;
    U32                         ByteCount;
} I2O_FRAGMENT_ENTRY_U96, *PI2O_FRAGMENT_ENTRY_U96;

typedef struct _I2O_V2_SGE_FRAGMENT_ENTRY_U128
{
    U128                        PhysicalAddress;
    U32                         ByteCount;
} I2O_FRAGMENT_ENTRY_U128, *PI2O_FRAGMENT_ENTRY_U128;

typedef struct _I2O_FRAGMENT_ENTRY
{
    union
    {
        I2O_FRAGMENT_ENTRY_U32          FU32;

        I2O_FRAGMENT_ENTRY_U64          FU64;

        I2O_FRAGMENT_ENTRY_U96          FU96;

        I2O_FRAGMENT_ENTRY_U128         FU128;

    }u;
} I2O_FRAGMENT_ENTRY, *PI2O_FRAGMENT_ENTRY;

/* Fragment elements */

/* LO,JG patch to cope with limited size due to 1 byte counters and size.
typedef struct _I2O_V2_SGE_FRAGMENT_ELEMENT_U32
{
#if defined(LITTLE_ENDIAN__)
    U8                          FragmentCount;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    I2O_FRAGMENT_ENTRY_U32       FragmentEntry[1];
#elif defined(BIG_ENDIAN__)
    U8                          ElementType;
    U8                          ElementLength;
    U8                          ElementFlags;
    U8                          FragmentCount;
    I2O_FRAGMENT_ENTRY_U32       FragmentEntry[1];
#endif
} I2O_V2_SGE_FRAGMENT_ELEMENT_U32, *PI2O_V2_SGE_FRAGMENT_ELEMENT_U32;
*/
typedef struct _I2O_V2_SGE_FRAGMENT_ELEMENT_U32
{
#if defined(LITTLE_ENDIAN__)
    U8                          FragmentCount_unused;
    U8                          ElementFlags;
    U8                          ElementLength_unused;
    U8                          ElementType;
    U32				ElementLength;
    U32				FragmentCount;
    I2O_FRAGMENT_ENTRY_U32       FragmentEntry[1];
#elif defined(BIG_ENDIAN__)
    U8                          ElementType;
    U8                          ElementLength_unused;
    U8                          ElementFlags;
    U8                          FragmentCount_unused;
    U32				ElementLength;
    U32				FragmentCount;    
    I2O_FRAGMENT_ENTRY_U32       FragmentEntry[1];
#endif
} I2O_V2_SGE_FRAGMENT_ELEMENT_U32, *PI2O_V2_SGE_FRAGMENT_ELEMENT_U32;
typedef struct _I2O_V2_SGE_FRAGMENT_ELEMENT_U64
{
#if defined(LITTLE_ENDIAN__)
    U8                          FragmentCount;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    I2O_FRAGMENT_ENTRY_U64       FragmentEntry[1];
#elif defined(BIG_ENDIAN__)
#endif    
} I2O_V2_SGE_FRAGMENT_ELEMENT_U64, *PI2O_V2_SGE_FRAGMENT_ELEMENT_U64;

typedef struct _I2O_V2_SGE_FRAGMENT_ELEMENT_U96
{
#if defined(LITTLE_ENDIAN__)
    U8                          FragmentCount;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    I2O_FRAGMENT_ENTRY_U96       FragmentEntry[1];
#elif defined(BIG_ENDIAN__)
#endif    
} I2O_V2_SGE_FRAGMENT_ELEMENT_U96, *PI2O_V2_SGE_FRAGMENT_ELEMENT_U96;

typedef struct _I2O_V2_SGE_FRAGMENT_ELEMENT_U128
{
#if defined(LITTLE_ENDIAN__)
    U8                          FragmentCount;
    U8                          ElementFlags;
    U8                          ElementLength;
    U8                          ElementType;
    I2O_FRAGMENT_ENTRY_U128      FragmentEntry[1];
#elif defined(BIG_ENDIAN__)
#endif    
} I2O_V2_SGE_FRAGMENT_ELEMENT_U128, *PI2O_V2_SGE_FRAGMENT_ELEMENT_U128;


/* Transport Element */
typedef struct _I2O_V2_SGE_TRANSPORT_ELEMENT
{
#if defined(LITTLE_ENDIAN__)
    U16                         TransportSpecific;
    U8                          ElementLength;
    U8                          ElementType;
#elif defined(BIG_ENDIAN__)
#endif    
} I2O_V2_SGE_TRANSPORT_ELEMENT, *PI2O_V2_SGE_TRANSPORT_ELEMENT;


/****************************************************************************/

/* Legacy 1.5 SGL definitions */

/****************************************************************************/

/* SglFlags defines. */

#define    I2O_SGL_FLAGS_LAST_ELEMENT                  0x80
#define    I2O_SGL_FLAGS_END_OF_BUFFER                 0x40

#define    I2O_SGL_FLAGS_IGNORE_ELEMENT                0x00
#define    I2O_SGL_FLAGS_TRANSPORT_ELEMENT             0x04
#define    I2O_SGL_FLAGS_BIT_BUCKET_ELEMENT            0x08
#define    I2O_SGL_FLAGS_IMMEDIATE_DATA_ELEMENT        0x0C
#define    I2O_SGL_FLAGS_SIMPLE_ADDRESS_ELEMENT        0x10
#define    I2O_SGL_FLAGS_PAGE_LIST_ADDRESS_ELEMENT     0x20
#define    I2O_SGL_FLAGS_CHAIN_POINTER_ELEMENT         0x30
#define    I2O_SGL_FLAGS_LONG_TRANSACTION_ELEMENT      0x40
#define    I2O_SGL_FLAGS_SHORT_TRANSACTION_ELEMENT     0x70
#define    I2O_SGL_FLAGS_SGL_ATTRIBUTES_ELEMENT        0x7C

#define    I2O_SGL_FLAGS_BC0                           0x01
#define    I2O_SGL_FLAGS_BC1                           0x02
#define    I2O_SGL_FLAGS_DIR                           0x04
#define    I2O_SGL_FLAGS_LOCAL_ADDRESS                 0x08

#define    I2O_SGL_FLAGS_CONTEXT_COUNT_MASK            0x03
#define    I2O_SGL_FLAGS_ADDRESS_MODE_MASK             0x3C
#define    I2O_SGL_FLAGS_NO_CONTEXT                    0x00

/*  Scatter/Gather Truth Table */

/*

typedef enum _SG_TYPE {
   INVALID,
   Ignore,
   TransportDetails,
   BitBucket,
   ImmediateData,
   Simple,
   PageList,
   ChainPointer,
   ShortTransaction,
   LongTransaction,
   SGLAttributes,
   INVALID/ReservedLongFormat,
   INVALID/ReservedShortFormat
} SG_TYPE, *PSG_TYPE;


   0x00    Ignore;
   0x04    TransportDetails;
   0x08    BitBucket;
   0x0C    ImmediateData;
   0x10    Simple;
   0x14    Simple;
   0x18    Simple;
   0x1C    Simple;
   0x20    PageList;
   0x24    PageList;
   0x28    PageList;
   0x2C    PageList;
   0x30    ChainPointer;
   0x34    INVALID;
   0x38    ChainPointer;
   0x3C    INVALID;
   0x40    LongTransaction;
   0x44    INVALID/ReservedLongFormat;
   0x48    BitBucket;
   0x4C    ImmediateData;
   0x50    Simple;
   0x54    Simple;
   0x58    Simple;
   0x5C    Simple;
   0x60    PageList;
   0x64    PageList;
   0x68    PageList;
   0x6C    PageList;
   0x70    ShortTransaction;
   0x74    INVALID/ReservedShortFormat;
   0x78    INVALID/ReservedShortFormat;
   0x7C    SGLAttributes;
*/


/* 32 Bit Context Field defines */

#define    I2O_SGL_FLAGS_CONTEXT32_NULL                0x00
#define    I2O_SGL_FLAGS_CONTEXT32_U32                 0x01
#define    I2O_SGL_FLAGS_CONTEXT32_U64                 0x02
#define    I2O_SGL_FLAGS_CONTEXT32_U96                 0x03

#define    I2O_SGL_FLAGS_CONTEXT32_NULL_SZ             0x00
#define    I2O_SGL_FLAGS_CONTEXT32_U32_SZ              0x04
#define    I2O_SGL_FLAGS_CONTEXT32_U64_SZ              0x08
#define    I2O_SGL_FLAGS_CONTEXT32_U96_SZ              0x0C

/* 64 Bit Context Field defines */

#define    I2O_SGL_FLAGS_CONTEXT64_NULL                0x00
#define    I2O_SGL_FLAGS_CONTEXT64_U64                 0x01
#define    I2O_SGL_FLAGS_CONTEXT64_U128                0x02
#define    I2O_SGL_FLAGS_CONTEXT64_U192                0x03

#define    I2O_SGL_FLAGS_CONTEXT64_NULL_SZ             0x00
#define    I2O_SGL_FLAGS_CONTEXT64_U64_SZ              0x08
#define    I2O_SGL_FLAGS_CONTEXT64_U128_SZ             0x10
#define    I2O_SGL_FLAGS_CONTEXT64_U192_SZ             0x18

/* SGL Attribute Element defines */

#define    I2O_SGL_ATTRIBUTE_FLAGS_BIT_BUCKET_HINT     0x0400
#define    I2O_SGL_ATTRIBUTE_FLAGS_IMMEDIATE_DATA_HINT 0x0200
#define    I2O_SGL_ATTRIBUTE_FLAGS_LOCAL_ADDRESS_HINT  0x0100
#define    I2O_SGL_ATTRIBUTE_FLAGS_32BIT_TRANSACTION   0x0000
#define    I2O_SGL_ATTRIBUTE_FLAGS_64BIT_TRANSACTION   0x0004
#define    I2O_SGL_ATTRIBUTE_FLAGS_32BIT_LOCAL_ADDRESS 0x0000

/* SG Size defines */

#define    I2O_SG_COUNT_SZ                             24
#define    I2O_SG_FLAGS_SZ                             8

/* Standard Flags and Count fields for SG Elements */

typedef struct _I2O_FLAGS_COUNT {
#if defined(LITTLE_ENDIAN__)
   BF                          Count:I2O_SG_COUNT_SZ;
   BF                          Flags:I2O_SG_FLAGS_SZ;
#elif defined(BIG_ENDIAN__)
   BF                          Flags:I2O_SG_FLAGS_SZ;
   BF                          Count:I2O_SG_COUNT_SZ;
#endif
} I2O_FLAGS_COUNT, *PI2O_FLAGS_COUNT;

/* Bit Bucket Element */

typedef struct _I2O_SGE_BIT_BUCKET_ELEMENT {
   I2O_FLAGS_COUNT             FlagsCount;
   U32                         BufferContext;
} I2O_SGE_BIT_BUCKET_ELEMENT, *PI2O_SGE_BIT_BUCKET_ELEMENT;

/* Chain Addressing Scatter-Gather Element */

typedef struct _I2O_SGE_CHAIN_ELEMENT {
   I2O_FLAGS_COUNT             FlagsCount;
   U32                         PhysicalAddress;
} I2O_SGE_CHAIN_ELEMENT, *PI2O_SGE_CHAIN_ELEMENT;

/* Chain Addressing with Context Scatter-Gather Element */

typedef struct _I2O_SGE_CHAIN_CONTEXT_ELEMENT {
   I2O_FLAGS_COUNT             FlagsCount;
   U32                         Context[1];
   U32                         PhysicalAddress;
} I2O_SGE_CHAIN_CONTEXT_ELEMENT, *PI2O_SGE_CHAIN_CONTEXT_ELEMENT;

/* Ignore Scatter-Gather Element */

typedef struct _I2O_SGE_IGNORE_ELEMENT {
   I2O_FLAGS_COUNT             FlagsCount;
} I2O_SGE_IGNORE_ELEMENT, *PI2O_SGE_IGNORE_ELEMENT;

/* Immediate Data Element */

typedef struct _I2O_SGE_IMMEDIATE_DATA_ELEMENT {
   I2O_FLAGS_COUNT             FlagsCount;
} I2O_SGE_IMMEDIATE_DATA_ELEMENT, *PI2O_SGE_IMMEDIATE_DATA_ELEMENT;

/* Immediate Data with Context Element */

typedef struct _I2O_SGE_IMMEDIATE_DATA_CONTEXT_ELEMENT {
   I2O_FLAGS_COUNT             FlagsCount;
   U32                         BufferContext;
} I2O_SGE_IMMEDIATE_DATA_CONTEXT_ELEMENT, *PI2O_SGE_IMMEDIATE_DATA_CONTEXT_ELEMENT;

/* Long Transaction Parameters Element */

typedef struct _I2O_SGE_LONG_TRANSACTION_ELEMENT {
   BF                          LongElementLength:I2O_SG_COUNT_SZ;
   BF                          Flags:I2O_SG_FLAGS_SZ;
   U32                         BufferContext;
} I2O_SGE_LONG_TRANSACTION_ELEMENT, *PI2O_SGE_LONG_TRANSACTION_ELEMENT;

/* Page List Scatter-Gather Element */

typedef struct _I2O_SGE_PAGE_ELEMENT {
   I2O_FLAGS_COUNT             FlagsCount;
   U32                         PhysicalAddress[1];
} I2O_SGE_PAGE_ELEMENT , *PI2O_SGE_PAGE_ELEMENT ;

/* Page List with Context Scatter-Gather Element */

typedef struct _I2O_SGE_PAGE_CONTEXT_ELEMENT {
   I2O_FLAGS_COUNT             FlagsCount;
   U32                         BufferContext[1];
   U32                         PhysicalAddress[1];
} I2O_SGE_PAGE_CONTEXT_ELEMENT, *PI2O_SGE_PAGE_CONTEXT_ELEMENT;

/* SGL Attribute Element */

typedef struct _I2O_SGE_SGL_ATTRIBUTES_ELEMENT {
#if defined(LITTLE_ENDIAN__)
   U16                         SglAttributeFlags;
   U8                          ElementLength;
   U8                          Flags;
   U32                         PageFrameSize;
#elif defined(BIG_ENDIAN__)
   U8                          Flags;
   U8                          ElementLength;
   U16                         SglAttributeFlags;
   U32                         PageFrameSize;
#endif
} I2O_SGE_SGL_ATTRIBUTES_ELEMENT, *PI2O_SGE_SGL_ATTRIBUTES_ELEMENT;

/* Short Transaction Parameters Element */

typedef struct _I2O_SGE_SHORT_TRANSACTION_ELEMENT {
#if defined(LITTLE_ENDIAN__)
   U16                         ClassFields;
   U8                          ElementLength;
   U8                          Flags;
   U32                         BufferContext;
#elif defined(BIG_ENDIAN__)
   U8                          Flags;
   U8                          ElementLength;
   U16                         ClassFields;
   U32                         BufferContext;
#endif
} I2O_SGE_SHORT_TRANSACTION_ELEMENT, *PI2O_SGE_SHORT_TRANSACTION_ELEMENT;

/* Simple Addressing Scatter-Gather Element */

typedef struct _I2O_SGE_SIMPLE_ELEMENT {
   I2O_FLAGS_COUNT             FlagsCount;
   U32                         PhysicalAddress;
} I2O_SGE_SIMPLE_ELEMENT, *PI2O_SGE_SIMPLE_ELEMENT;

/* Simple Addressing with Context Scatter-Gather Element */

typedef struct _I2O_SGE_SIMPLE_CONTEXT_ELEMENT {
   I2O_FLAGS_COUNT             FlagsCount;
   U32                         BufferContext[1];
   U32                         PhysicalAddress;
} I2O_SGE_SIMPLE_CONTEXT_ELEMENT, *PI2O_SGE_SIMPLE_CONTEXT_ELEMENT;

/* Transport Detail Element */

typedef struct _I2O_SGE_TRANSPORT_ELEMENT {
#if defined(LITTLE_ENDIAN__)
   BF                          LongElementLength:I2O_SG_COUNT_SZ;
   BF                          Flags:I2O_SG_FLAGS_SZ;
#elif defined(BIG_ENDIAN__)
   BF                          Flags:I2O_SG_FLAGS_SZ;
   BF                          LongElementLength:I2O_SG_COUNT_SZ;
#endif
} I2O_SGE_TRANSPORT_ELEMENT, *PI2O_SGE_TRANSPORT_ELEMENT;


/****************************************************************************/

/* All SGL elements */

/****************************************************************************/

typedef struct _I2O_SG_ELEMENT {
   union {

       /* Types Element */
       I2O_V2_SGE_SGL_TYPES_ELEMENT            Type;

       /* Ignore Scatter-Gather Element */
       I2O_V2_SGE_IGNORE_ELEMENT               Ignore;

       /* Immediate Data Element */
       I2O_V2_SGE_IMMEDIATE_DATA_ELEMENT       ImmediateData;

       /* Platform Element */
       I2O_V2_SGE_PLATFORM_DECLARATION_ELEMENT Platform;

       /* SGL Attribute Element */
       I2O_V2_SGE_SGL_ATTRIBUTES_ELEMENT       SglAttribute;

       /* Transaction Parameters Element */
       I2O_V2_SGE_TRANSACTION_ELEMENT          Transaction;

       /* Transaction Parameters Element */
       I2O_V2_SGE_TRANSACTION_BC_ELEMENT       TransactionBC;

       /* Transport Detail Element */
       I2O_V2_SGE_TRANSPORT_ELEMENT            Transport;

       /* Chain Addressing Element */
       I2O_V2_SGE_CHAIN_ELEMENT_U32            Chain32;

       /* Chain Addressing Element */
       I2O_V2_SGE_CHAIN_ELEMENT_U64            Chain64;

       /* Chain Addressing Element */
       I2O_V2_SGE_CHAIN_ELEMENT_U96            Chain96;

       /* Chain Addressing Element */
       I2O_V2_SGE_CHAIN_ELEMENT_U128           Chain128;

       /* Fragment Addressing Element */
       I2O_V2_SGE_FRAGMENT_ELEMENT_U32         Fragment32;

       /* Fragment Addressing Element */
       I2O_V2_SGE_FRAGMENT_ELEMENT_U64         Fragment64;

       /* Fragment Addressing Element */
       I2O_V2_SGE_FRAGMENT_ELEMENT_U96         Fragment96;

       /* Fragment Addressing Element */
       I2O_V2_SGE_FRAGMENT_ELEMENT_U128        Fragment128;

       /* Page List Element */
       I2O_V2_SGE_PAGE_LIST_ELEMENT_U32        Page32;

       /* Page List Element */
       I2O_V2_SGE_PAGE_LIST_ELEMENT_U64        Page64;

       /* Page List Element */
       I2O_V2_SGE_PAGE_LIST_ELEMENT_U96        Page96;

       /* Page List Element */
       I2O_V2_SGE_PAGE_LIST_ELEMENT_U128       Page128;

       union {

           /* 1.5 SGL elements */

           /* Bit Bucket Element */
           I2O_SGE_BIT_BUCKET_ELEMENT          BitBucket;

           /* Chain Addressing Element */
           I2O_SGE_CHAIN_ELEMENT               Chain;

           /* Chain Addressing with Context Element */
           I2O_SGE_CHAIN_CONTEXT_ELEMENT       ChainContext;

           /* Ignore Scatter-Gather Element */
           I2O_SGE_IGNORE_ELEMENT              Ignore;

           /* Immediate Data Element */
           I2O_SGE_IMMEDIATE_DATA_ELEMENT      ImmediateData;

           /* Immediate Data with Context Element */
           I2O_SGE_IMMEDIATE_DATA_CONTEXT_ELEMENT  ImmediateDataContext;

           /* Long Transaction Parameters Element */
           I2O_SGE_LONG_TRANSACTION_ELEMENT    LongTransaction;

           /* Page List Element */
           I2O_SGE_PAGE_ELEMENT                Page[1];

           /* Page List with Context Element */
           I2O_SGE_PAGE_CONTEXT_ELEMENT        PageContext;

           /* SGL Attribute Element */
           I2O_SGE_SGL_ATTRIBUTES_ELEMENT      SGLAttribute;

           /* Short Transaction Parameters Element */
           I2O_SGE_SHORT_TRANSACTION_ELEMENT   ShortTransaction;

           /* Simple Addressing Element */
           I2O_SGE_SIMPLE_ELEMENT              Simple[1];

           /* Simple Addressing with Context Element */
           I2O_SGE_SIMPLE_CONTEXT_ELEMENT      SimpleContext[1];

           /* Transport Detail Element */
           I2O_SGE_TRANSPORT_ELEMENT           Transport;
           } v15;
   }u;
} I2O_SG_ELEMENT, *PI2O_SG_ELEMENT;

PRAGMA_PACK_POP

PRAGMA_ALIGN_POP

#endif    /* _I2O_V2_0_SGL_ */
