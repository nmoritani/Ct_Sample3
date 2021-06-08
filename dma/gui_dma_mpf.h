#ifndef __GUI_DMA_MPF_H__
#define __GUI_DMA_MPF_H__

#include "kernel_id.h"
#include "itron.h"

#define GUI_DMA_MPF_BLKCNT			16	/**< �������u���b�N�� */
#define GUI_DMA_MPF_BLKSZ			64	/**< �������u���b�N�T�C�Y */
#define	GUI_DMA_MPF_SIZE	(TSZ_MPF(GUI_DMA_MPF_BLKCNT, GUI_DMA_MPF_BLKSZ))

extern UB GuiDmaMpfMem[];


#endif

