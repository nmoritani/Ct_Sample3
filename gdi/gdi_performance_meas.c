/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#include <kernel.h>
#include <kernel_id.h>
#include "smDebugSerial.h"

#include "Tmr.h"

#include "gdi.h"
#include "gdi_performance_meas.h"

#define	PERFORMANCE_MEAS_COUNT_MAX		(20)
static long s_aResult[PERFORMANCE_MEAS_COUNT_MAX];
static long *s_pResult = s_aResult;

static void gdi_performance_tmr_init(void)
{
	TMR_Open(14,100000);
}

void gdi_performance_tmr_exit(void)
{
	if (!TMR_Close(14)) {
		smDebugPrintf(1,"Error : gdi_performance_tmr_exit\n");
	}
}

unsigned long gdi_performance_tmr_get(void)
{
	UW count = 0;

	if (!TMR_GetCount(14, &count)) {
		smDebugPrintf(1,"Error : TMR_GetCount\n");
	}
	return (unsigned long)count;
}

void gdi_reset_performance_meas()
{
	int i;
	for (i = 0; i < PERFORMANCE_MEAS_COUNT_MAX; i++) {
		s_aResult[i] = 0;
	}
	s_pResult = &s_aResult[0];
}

unsigned long gdi_performance_tmr_start(void)
{
	gdi_performance_tmr_exit();
	gdi_performance_tmr_init();
	return gdi_performance_tmr_get();
}


unsigned long gdi_performance_tmr_end(void)
{
	return gdi_performance_tmr_get();
}


void gdi_start_performance_meas()
{
	gdi_reset_performance_meas();
	gdi_performance_tmr_start();
}
void gdi_restart_performance_meas()
{
	gdi_performance_tmr_start();
}

void gdi_add_performance_meas()
{
	*s_pResult++ = gdi_performance_tmr_end();
	gdi_restart_performance_meas();
}

void gdi_dump_performance_meas()
{
	int iCnt;
	for (iCnt = 0; iCnt < (s_pResult - &s_aResult[0]); iCnt++) {
		smDebugPrintf(1, "%d0\n", s_aResult[iCnt]);	//タイマは10μs単位なので、0をつけてダンプ
	}
}
