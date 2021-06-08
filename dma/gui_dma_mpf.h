#ifndef __GUI_DMA_MPF_H__
#define __GUI_DMA_MPF_H__

#include "kernel_id.h"
#include "itron.h"

#define GUI_DMA_MPF_BLKCNT			16	/**< メモリブロック数 */
#define GUI_DMA_MPF_BLKSZ			64	/**< メモリブロックサイズ */
#define	GUI_DMA_MPF_SIZE	(TSZ_MPF(GUI_DMA_MPF_BLKCNT, GUI_DMA_MPF_BLKSZ))

extern UB GuiDmaMpfMem[];


#endif

