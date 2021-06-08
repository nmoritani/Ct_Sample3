
#include "CtTimeMesure.h"

#ifdef WIN32_GUI_SIM
#include <windows.h>
#include <mmsystem.h>	// timeGetTime()
#pragma comment( lib, "winmm.lib" )
#else
#include <itron.h>
#endif

unsigned long CtGetTime()
{
#ifdef WIN32_GUI_SIM
	return timeGetTime();
#else
	SYSTIM	time;
	get_tim(&time);
#if 1	// threadx‚Å‚ÍSYSTIM‚ÍlongŒ^‚Å‚·
	return time;
#else
	return time.ltime;
#endif
#endif
}



