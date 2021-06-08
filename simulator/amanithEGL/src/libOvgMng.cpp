#include "EGL/egl.h"

#include "amanithvg/openvg.h"
#include "amanithvg/vgplatform.h"
#include "amanithVG.h"
#include "libOvgMng.h"

#include <windows.h>
static HANDLE s_hMutex;

void InitLibOpenVG(int width, int height)
{
	//ミューテックスの初期化
	s_hMutex = CreateMutex(0, FALSE, 0);

	lib_AmanithVG_Load();
}

void TerminateLibOvg(void)
{
	lib_AmanithVG_Free();

}

void wai_sem_amanith()
{
	WaitForSingleObject(s_hMutex, INFINITE);
}

void sig_sem_amanith()
{
	ReleaseMutex(s_hMutex);
}
