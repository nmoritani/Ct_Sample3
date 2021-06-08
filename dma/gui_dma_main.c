#include "gui_dma_main.h"
#include "smDebugSerial.h"

void
GUI_DMA_main(void)
{
	ER err;
	T_MSG *pTMsg = NULL;
	GUI_DMA_CMD_DATA_MSG	*pCmdMsg;		/* ����M���b�Z�[�W */
	GUI_DMA_CMD_DATA		*pCmdData;

	/* ���C�����[�v */
	while (1) {
		/* ���b�Z�[�W��M */
		err = rcv_mbx(GUI_DMA_MBXID_CMD, &pTMsg);

		if (err != E_OK) {
			break;
		}
		
		pCmdMsg	= (GUI_DMA_CMD_DATA_MSG *)pTMsg;
		pCmdData = (GUI_DMA_CMD_DATA *)&pCmdMsg->CmdData;
		
		switch (pCmdData->ComType){
		case GUI_DMA_COM_EXTREQ:
			switch (pCmdData->Param1) {
			case GUI_DMA_COM_EXT_DRAW_FILLRECT_SIMPLE:
				{
					// DMAC�]��
					gui_dma_pack_fillrect_simple *pack = pCmdData->pParam;
					gui_dma_fillrect_simple(pack);
				}
				break;
			default:
				break;
			}
			rel_mpf(GUI_DMA_MPFID_CMD, pTMsg);
			break;
		default:
			break;
		}	
	}
}
