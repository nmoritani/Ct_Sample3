/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#ifndef __GDI_PERFORMANCE_MEAS_H__
#define __GDI_PERFORMANCE_MEAS_H__

extern void gdi_start_performance_meas();
extern void gdi_restart_performance_meas();
extern void gdi_add_performance_meas();
extern void gdi_dump_performance_meas();

#define	PERFORMANCE_MEAS_START	do {				\
									smDebugPrintf(1, "%s : line = %d\n", __func__, __LINE__ );	\
									gdi_start_performance_meas();								\
								} while(0)

#define	PERFORMANCE_MEAS_ADD_RESULT		gdi_add_performance_meas()
#define	PERFORMANCE_MEAS_RESTART		gdi_restart_performance_meas()
#define	PERFORMANCE_MEAS_DUMP			gdi_dump_performance_meas()

#endif /* __GDI_PERFORMANCE_MEAS_H__ */
