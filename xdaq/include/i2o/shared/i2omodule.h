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

#ifndef __INCi2omoduleh
#define __INCi2omoduleh

#define I2OMODULE_REV 2_0_0

#include "i2otypes.h"

/* major capabilities bit definitions */

#define I2O_MODULE_32_BIT_CONTEXT_SUPPORT          0x0
#define I2O_MODULE_64_BIT_CONTEXT_SUPPORT          0x1
#define I2O_MODULE_32_OR_64_BIT_CONTEXT_SUPPORT    0x2
#define I2O_MODULE_32_AND_64_BIT_CONTEXT_SUPPORT   0x3


/* module header table types */

#define I2O_MODULE_INDEX_TABLE         0x0000
#define I2O_MODULE_ADAPTER_TABLE       0x0001
#define I2O_MODULE_DEVICE_TABLE        0x0002
#define I2O_MODULE_OBSOLETE_DDM_TABLE  0x0003
#define I2O_MODULE_TCL_TABLE           0x0004


/* Module header */

typedef struct
    {
    U32         headerSize;         /* size of this header and tables */
    U16         orgId;              /* I2O organization ID */
    U16         moduleId;           /* assigned to vendor of module */
    U16         day;                /* ascii 4 digit day DDM produced */
    U16         month;              /* ascii 4 digit month DDM produced */
    U32         year;               /* ascii 4 digit year DDM produced */
    U8          i2oVersion;         /* I2O version info */
    U8          majorCapabilities;  /* capbilities bits */
    U16         reserved;           /* reserved */
    U32         codeSize;           /* text/data/bss */
    U32         tableOffset;        /* offset to numTables */
    U32         memoryReq;          /* pre-attach memory requiremets */
    U32         memoryPreferred;    /* additional desired */
    char        moduleVersion[4];   /* 4 ascii characters */
    U8          processorType;      /* IOP processor type */
    U8          processVersion;     /* IOP processor type */
    U8          objCodeFormat;      /* DDM object module format */
    U8          attachNotificationLevel; /* Level for AttachComplete events */
    U32         numTables;          /* number of descriptor tables */
    char        moduleInfo[24];     /* ascii string name */
    } I2O_MODULE_DESC_HDR;


/* Module Parameter Block */

typedef struct
    {
    U32             mpbSize;        /* size of this header and tables */
    U16             orgId;          /* I2O organization ID */
    U16             modId;          /* assigned to vendor of module */
    U32             mpbVersion;     /* MPB version info */
    U32             reserved;       /* reserved */
    } I2O_MODULE_PARAM_BLK;

/* Generic header for module tables. This applies to all tables in the
 * module header apart from the TCL script table, which does not define
 * the entrySize and numEntries fields.
 */

typedef struct
    {
    U16      length;        /* length of table in 32 bit words */
    U16      descriptorId;  /* descriptor ID = 0x0000 */
    U8       entrySize;     /* size of entries in 32 bit words */
    U8       numEntries;    /* number of entries */
    U8       tableVersion;  /* table version */
    U8       reserved;      /* reserved */
} I2O_MODULE_TABLE;

typedef struct
    {
    U16      tableDescId;   /* descriptor ID of table */
    U16      reserved;      /* reserved */
    U32      tableOffset;   /* offset in bytes of table from start
of mod hdr */
} I2O_INDEX_TABLE_ENTRY;

typedef struct
    {
    U32      classId;       /* Message class */
    U32      subClass;      /* Subclass */
} I2O_DEVICE_TABLE_ENTRY;

typedef struct
    {
    U16      orgId;         /* Organization ID */
    U16      modId;         /* Module ID */
} I2O_OBSOLETE_DDM_TABLE_ENTRY;

#endif /* __INCi2omoduleh */
