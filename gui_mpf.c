#include "kernel_id.h"
#include "itron.h"
#include "gui_config.h"


UB GfxMpfMem[GUI_MPF_SIZE];

void gfx_free_mpf(VP blk)
{
	ID mpfid;
	UW object = (UW)blk;
	if (((UW)GfxMpfMem <= object) && (object < ((UW)GfxMpfMem + GUI_MPF_SIZE))) {
		mpfid = GUI_MPFID_CMD;
	} else {
		return;
	}
	
	rel_mpf(mpfid, blk);
}


