#include "mdmac.h"
#include "gui_dma_command.h"
#include "Mml.h"	/* for MML_LogicalMemAddr() */

#define	GUI_DMA_TRANS_END	0x00000001

extern UW gdi_fill_color;


extern GDI_DRAW_BUFFER *gdi_pixmap_draw_buffer_pointer;
extern GDI_DRAW_BUFFER	gdi_pixmap_draw_buffer;

GDI_DRAW_BUFFER	*gdi_pixmap_draw_buffer_pointer = NULL;
GDI_DRAW_BUFFER	 gdi_pixmap_draw_buffer;
static UW m_hDmac = 0;

/* �]���f�[�^������ */
void gui_dma_GetTransferLength( UW srcadr, UW dstadr, UW size, UW *ptw, UW *ptu )
{
	UW tmptu, tmptw;

	if(ptw == NULL) return;
	if(ptu == NULL) return;

	/* �]���T�C�Y����]���f�[�^�������� */
	if (size % 64 == 0) {
		tmptu = MDMAC_TU_64B;		// 6
	} else if (size % 32 == 0) {
		tmptu = MDMAC_TU_32B;		// 5
	} else if (size % 16 == 0) {
		tmptu = MDMAC_TU_16B;		// 4
	} else if (size % 8 == 0) {
		tmptu = MDMAC_TU_8B;		// 3
	} else if (size % 4 == 0) {
		tmptu = MDMAC_TU_4B;		// 2
	} else if (size % 2 == 0) {
		tmptu = MDMAC_TU_2B;		// 1
	} else {
		tmptu = MDMAC_TU_1B;		// 0
	}

	/* �]�����A�]����A�h���X����]���P�ʂ����� */
	if ((srcadr % 4 == 0) && (dstadr % 4 == 0)) {
		tmptw = MDMAC_TW_4B;		// 2
	} else if ((srcadr % 2 == 0) && (dstadr % 2 == 0)) {
		tmptw = MDMAC_TW_2B;		// 1
	} else {
		tmptw = MDMAC_TW_1B;		// 0
	}
	
	/* �]���P�ʂ��]���f�[�^�����傫���ꍇ�͓]���P�ʂ�]���f�[�^���ɍ��킹�� */	
	if (tmptw > tmptu) {
		tmptw = tmptu;
	}

	// V9 PF�ˑ��d�l
	if( (tmptu == MDMAC_TU_64B) && (tmptw < MDMAC_TW_4B) ){
		tmptu = MDMAC_TU_32B;		// 5
	}
	if( (tmptu == MDMAC_TU_32B) && (tmptw < MDMAC_TW_2B) ){
		tmptu = MDMAC_TU_16B;		// 4
	}
	
	*ptu = tmptu;
	*ptw = tmptw;
}


static void endCallBackFunc(UW h_mdmac)
{
	if (h_mdmac == m_hDmac) {
		iset_flg(GUI_DMA_TRANS_FLGID, GUI_DMA_TRANS_END);
	}
}

static void endErrCallBackFunc(UW h_mdmac)
{
	if (h_mdmac == m_hDmac) {
		iset_flg(GUI_DMA_TRANS_FLGID, GUI_DMA_TRANS_END);
	}
}


//MDMAC�]���P�ʕ␳����
//�p�����[�^�␳ �]���T�C�Y���]���P�ʂŊ���؂�Ȃ���΁A�]���P�ʂ�␳����
static UW gd_mdmac_adj_tw(UW tw, UW rect_dst_data_size)
{
	UW ret_tw = tw;

	if( (MDMAC_TW_8B == ret_tw) && (rect_dst_data_size % 8) ){
		ret_tw = MDMAC_TW_4B;
	}
	if( (MDMAC_TW_4B == ret_tw) && (rect_dst_data_size % 4) ){
		ret_tw = MDMAC_TW_2B;
	}
	if( (MDMAC_TW_2B == ret_tw) && (rect_dst_data_size % 2) ){
		ret_tw = MDMAC_TW_1B;
	}

	return ret_tw;
}

// -------------------------------------------------------------------

//#define DBG_MDMAC_TIME_MEASURE
//MDMAC FILL�]�����s����
// ���� �v���p�e�B�ݒ�
//�@�߂�l�FRet �]�����ہ@�i1=����, 0=���s�j
int gui_dma_fillrect_exec(mdmac_prop *p_prop, mdmac_prop3 *p_prop3)
{
	W 	MdmacErr,MdmacErr1,MdmacErr2;
	int Ret = 0;

	if(p_prop == NULL) return 0;
	if(p_prop3 == NULL) return 0;

	//DMAC�̎g�p�����擾
	if((MdmacErr = MDMAC_Open(MDMAC_CH_5, &m_hDmac)) == MDMAC_OK){
		MdmacErr1 = MDMAC_SetCB(m_hDmac, endCallBackFunc);		//DMAC�]�������ʒm�R�[���o�b�N�֐���ݒ�
		MdmacErr2 = MDMAC_SetECB(m_hDmac, endErrCallBackFunc);	//DMAC�]���G���[�ʒm�R�[���o�b�N�֐���ݒ�
		if( (MdmacErr1 == MDMAC_OK)&&(MdmacErr2 == MDMAC_OK) ){
			//�]���P�ʕ␳
			p_prop->tw = gd_mdmac_adj_tw(p_prop->tw, p_prop3->rect_dst_data_size);

			/*--- for MDMAC_SetProp3---*/
			if ((MdmacErr = MDMAC_SetProp3(MDMAC_CH_5, p_prop3)) == MDMAC_OK) {
				/*--- for MDMAC_SetProp---*/
	 			if ((MdmacErr = MDMAC_SetProp(m_hDmac, p_prop)) == MDMAC_OK) {
					//MDMAC�]���J�n
					clr_flg(GUI_DMA_TRANS_FLGID, GUI_DMA_TRANS_END);
					if((MdmacErr = MDMAC_Start(m_hDmac)) == MDMAC_OK) {
						FLGPTN FlgPtn;
						ER Err = twai_flg(GUI_DMA_TRANS_FLGID, GUI_DMA_TRANS_END, TWF_ORW, &FlgPtn, 500);
						if (Err == E_OK) {
							Ret = 1;
						}
					}
				}
			}
		}
	    //DMAC�̎g�p�����J��
		MDMAC_Close(m_hDmac);
	}
	return Ret;	
}

/*
 *	DMA�]���i�t�B���j
 *   (���ӎ���)2016.8.10
 *   �����̃A�h���X�́u�����A�h���X�v���w�肷�鎖
 *    (param->dst_adr,param->src_adr)
 *   Remap�ݒ�ɂ��_���A�h���X�ւ̕ϊ��́A�{�֐����Ŏ��s����
 */
INT gui_dma_fillrect(gui_dma_fillrect_param *param, BOOL lock)
{
	mdmac_prop3 gd_prop3;
	mdmac_prop gd_prop;
	
	if(param == NULL) return 0;

	/*--- for MDMAC_SetProp3---*/
	gd_prop3.key_color_mode		= MDMAC_KC_OFF;	//�ʏ�
	gd_prop3.key_color_data		= 0;	//
	gd_prop3.rect_src_data_size	= 0;	//�ʏ�
	gd_prop3.rect_src_skip_size	= 0;	//�ʏ�
	
	gd_prop3.rect_dst_skip_size = param->skip_size;		//�]����̋�`�]���̃f�[�^�X�L�b�v�T�C�Y
	//�]����̃X�L�b�v�T�C�Y��0�Ȃ�ʏ�]��
	if (gd_prop3.rect_dst_skip_size == 0) { 
		gd_prop3.rect_dst_data_size = 0;				//�ʏ�]��
	} else {
		gd_prop3.rect_dst_data_size = param->data_size;	//��`�]���F�f�[�^�T�C�Y
	}
	/*--- for MDMAC_SetProp---*/
	{
		gdi_fill_color = param->color;			//�F�f�[�^���A���L���b�V���̈�ɃR�s�[
		
		gd_prop.sam		= MDMAC_AM_FIX;			//FIX
		gd_prop.src_adr	= MML_LogicalMemAddr((UW)&gdi_fill_color);	//�]�����̓A���L���b�V���̈�ł��鎖
		gd_prop.dst_adr	= MML_LogicalMemAddr(param->dst_adr);		//�]����

		gd_prop.dam		= MDMAC_AM_INC;			//INC
		gd_prop.size	= param->size;

		gui_dma_GetTransferLength(gd_prop.src_adr, gd_prop.dst_adr, gd_prop3.rect_dst_data_size, &gd_prop.tw, &gd_prop.tu);
		
		/* �f�[�^����2�o�C�g�Ȃ̂ōŒ�ł�2�o�C�g�]���Ƃ��� */
		if (gd_prop.tw <= MDMAC_TW_1B) {
			gd_prop.tw = MDMAC_TW_2B;
			gd_prop.tu = MDMAC_TU_2B;
		}
		
		gd_prop.tm = MDMAC_TM_BAT;
		gd_prop.start_trg = MDMAC_TRG_SOFT;
	}
	
	//MDMAC�]�����s�������҂�
	if (gui_dma_fillrect_exec(&gd_prop, &gd_prop3) == 0) {
		return GDI_HW_BUSY_ERROR;
	}
	
	return GDI_NO_ERROR;
}


