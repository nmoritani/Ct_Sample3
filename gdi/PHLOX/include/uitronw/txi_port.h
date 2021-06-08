/********************************************************************************/
/*                Copyright (C) 2002-2009 Grape Systems, Inc.                   */
/*                     All Rights Reserved.                                     */
/*                                                                              */
/*  This software is furnished under a license and may be used and copied only  */
/*  in accordance with the terms of such license and with the inclusion of the  */
/*  above copyright notice. No title to and ownership of the software is        */
/*  transferred.                                                                */
/*  Grape Systems Inc. makes no warranties with respect to the performance of   */
/*  this computer program, and specifically disclaims any responsibility for    */
/*  any damages, special or consequential, connected with the use of this       */
/*  program.                                                                    */
/*                                                                              */
/********************************************************************************/

/********************************************************************************/
/*                                                                              */
/* FILE NAME                                                                    */
/*                                                                              */
/*    txi_port.h                                                                */
/*                                                                              */
/*    This file can change for target system.                                   */
/*                                                                              */
/* HISTORY                                                                      */
/*                                                                              */
/*  DATE            NAME                    DESCRIPTION                         */
/*                                                                              */
/*  2006/08/31      M. Miyashita    Initial version 2.0                         */
/*  2007/03/05      M. Miyashita    version 2.1, Modified comment(s).           */
/*  2009/07/10      M. Miyashita    version 2.2, Modified comment(s).           */
/*                                                                              */
/********************************************************************************/

#ifndef _TXI_PORT_H_
#define _TXI_PORT_H_

/****************************************************************************/
/* Data define of kernel configuration for target system                    */
/****************************************************************************/

/* for KZM-A9-Dual/KMC (Renesas Electronics EMMA Mobile EV2) */

/* Hardware time tic.(ms) */
//#define HARDWARE_TIMETIC    10
#define HARDWARE_TIMETIC    1		// V8FHD_TX 10msにするため"1"を設定

/*---------- System thread define ----------*/
/* System queue count */
#define SYSTEM_QUEUE_SIZE   10

/* Stack size of a system thread. */
#define SYSTEM_STACK_SIZE   1024

/*---------- Target interrupt define ----------*/
/* Interrupt handler number max. */
#define SYSTEM_INHNO_MAX    511

/* CPU exception number max. */
#define SYSTEM_EXC_MAX      5

/*---------- System memory define ----------*/
/* System memory size */
#define SYSTEM_MEMORY_SIZE  4096

/* ThreadX v5.5以上を使用する場合で以下の定義が無い場合は、以下の定義を有効にしてください */
/*
#define __THREADX_MAJOR_VERSION         5
#define __THREADX_MINOR_VERSION         5
*/

#endif  /* _TXI_PORT_H_ */

