
#include "GUI_OsdDispIf.h"
#include "guiif_avc.h"

void GUI_setDisplayOsdLcd( GUI_ST_DISPLAY_LCD* pDisplay )
{
	// LCD	----------------------
	GUIAVC_DisplayOsdLcd( pDisplay );
}
void GUI_setDisplayOsdLout( GUI_ST_DISPLAY_LOUT* pDisplay )
{
	// LOUT	----------------------
	GUIAVC_DisplayOsdLout( pDisplay );
}

//OSD�\���A�h���X�ݒ�
void GUI_DisplayOsdLcdWithColorFormat( UW addr )
{
	//OSD�\���A�h���X�ݒ�
	GUIAVC_DisplayOsdLcdInfo(addr);
	//���̓v���[���T�C�Y�ݒ�	RGBA4444/8888�𓮓I�ɐ؂�ւ���ׁA�\���ʐؑւƓ�����AVC�֒ʒm����
	GUIAVC_setOsdPlaneSizeLcd();
}

void GUI_DisplayOsdLoutWithColorFormat( UW addr )
{
	//OSD�\���A�h���X�ݒ�
	GUIAVC_DisplayOsdLoutInfo(addr);
	//���̓v���[���T�C�Y�ݒ�	RGBA4444/8888�𓮓I�ɐ؂�ւ���ׁA�\���ʐؑւƓ�����AVC�֒ʒm����
	GUIAVC_setOsdPlaneSizeLout();
}


//OSD�O���o�̓X�P�[���ݒ�
void GUI_OsdLoutScale(BOOL is90percent)
{
	GUIAVC_OsdLoutScale(is90percent);
}
