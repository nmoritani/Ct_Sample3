/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowClipInfoMation
 */


#ifndef __CtWindowClipInfoMation_H__
#define __CtWindowClipInfoMation_H__

#include "CtWindowCommon.h"
#include "AplParamService.h"

#include "CtWindowContentsDrawThumb.h"
#include "CtWindowContentsThumbInit.h"
#include "CtWindowContentsSelectClipInfo.h"

#include "CtContainerWifi.h"
#include "CtContainerBattery.h"
#include "CtContainerThumbnailTitleBar.h"

#include "CtThumbDesign.h"
#include "CtStackLabel.h"

#include "gdi.h"
#include "gdi_local.h"

class CtWindowClipInfoMation : public CtWindowMain
{
#define LeftFont  CtFontSet(FontTypeNormal, CtColor::White)
#define CenterFont  CtFontSet(FontTypeNormal_alignCenter, CtColor::White)
typedef enum WindowContentType {
	WC_DRAW_THUMNAIL,
	WC_DRAW_INIT,
	WC_SELECT_CLIPINFO,
	WC_NONE,
}WindowContentType;

typedef enum {
	S_READ_CLIP_IDLE = 0,
	S_READ_CLIP_WAIT,
	S_READ_THUM_IDLE,
	S_READ_THUM_WAIT,
	S_READ_CLIP_MAX,
} READ_CLIP_STATE;


typedef enum {
	E_READ_THUM_INIT,
	E_READ_THUM_REQ,
	E_READ_THUM_FINISH,
	E_READ_CLIP_REQ,
	E_READ_CLIP_FINISH,
	E_READ_CLIP_END,
} READ_CLIP_EVENT;

typedef enum {
	READ_THUM_NOT_SATRTED_YET,
	READ_THUM_SET_FINISH,
	READ_THUM_REROAD,
	READ_THUM_END,
} READ_THUM_YUV;

public:
	CtWindowClipInfoMation();
	virtual ~CtWindowClipInfoMation() {}

	void callback_setCurrentIndex(int index);

	virtual bool handleParamEvent(const CtEventParam& Param);
    virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleKeyEvent(const CtEventKey& Key);


	void initThumbnail();
	bool setContents(const CtWindowContents* pContents);
    void setClipCnt(unsigned long cnt);
    unsigned long getClipCnt(void);
	virtual bool updateContents();
	void updateThumbnailImage();
	void DeleteThumbnailDrawable(int index);
	unsigned long GetThumbNailDrawableID(int index);
	GDI_HANDLER GetImageDrawableHandle(int index);
	READ_THUM_YUV IsAlreadyReadYuv(int index);
	bool DrawRequestYuv(int clipNo);
	void setThumbNailImage(unsigned long ClipNo);
	void setDrawableYUV(int index);
	// �R���e���c�X�V�ʒm
	void updatePicture();										// �摜�����X�V����

	void UpdateClipInfo();

private:
	// ���C�A�E�g����
	virtual CtWindow* createWindow();
	CtLayout* createLayoutLeftButton();
	CtLayout* createLayoutOneItemIcon();
	CtLayout* createLayoutRightText();

	bool destroyWindow();                                      // �E�B���h����������
	void setCurrentClipNo(unsigned long clipNo);
	unsigned long getCurrentNo();
	int getDetailPixelType(int nPixelTypeIndex, int nFrequencyIndex);

	// �\���X�V
    void updateThumbnail(unsigned long index);
	void BlankClipInfomation(unsigned long index);
	bool updateClipNo(unsigned long index);							// �N���b�v�ԍ�
	bool updateNotPlayIcon(bool bVisible);							// �Đ��s�N���b�v
	bool updateProtectIcon(bool bVisible);							// �N���b�v�v���e�N�g
	bool updateClipName(const char* name);							// �N���b�v��
	bool updateP2StartIcon(CtClipInfo::ClipInfoP2StartType Type);	// P2�s��/�s���N���b�v
	bool updateReConnectIcon(bool bVisible);						// �s���S�N���b�v

	bool updateSd();												// SD

private:
	/* WindowContent��M��� */
	WindowContentType	m_wcEvent;
	
	CtWindowContentsThumbInit*			m_pInitInfo;
	CtWindowContentsSelectClipInfo*		m_pSelectClipInfo;
	CtWindowContentsDrawThumb*			m_pDrawInfo;

	CtButton* m_pBtnUp;         // (�{�^��)�O�y�[�W
    CtButton* m_pBtnDown;       // (�{�^��)���y�[�W
	CtButton* m_pBtnReturn;		// �߂�{�^��

	CtContainerThumbnailTitleBar* m_pTitleBar;	// �^�C�g��

    CtLabel*   m_pLabeIcon[14];	//0:�N���b�v�ԍ�
								//1:�Đ��s�N���b�v�A�C�R��
								//2:�N���b�v�v���e�N�g�A�C�R��
								//3:�T���l�C���摜
								//4:�N���b�v��
								//5:�X�^�[�gTC
								//6:�X�^�[�gUB
								//7:�B�e��
								//8:�B�e����
								//9:�L�^����
								//10:�L�^�𑜓x/&���g��
								//11:�L�^�R�[�f�b�N
								//12:�L�^�t���[�����[�g
								//13:Gamma
	CtLabel* m_pReConnect;
	CtStackLabel* m_pP2Start;

	CtLabel*   m_pPixel;
	CtLabel*   m_pSeparate;
	CtLabel*   m_pFreq;
	
	unsigned long m_Clipcnt;		// �N���b�v��
	unsigned long m_CurrentClipNo;	// �N���b�v�ԍ�
	unsigned long m_ReadClipNo;		// ���ǂݍ��ݒ��̃N���b�v�ԍ�


	typedef CtVector::Vector<CtClipInfo*> ClipInfoItemList;
	ClipInfoItemList m_list;

private:
	void SetReadClipInfoEvent(READ_CLIP_EVENT _event);
	READ_CLIP_EVENT State_ReadClipIdle(READ_CLIP_EVENT event);
	READ_CLIP_EVENT State_ReadClipWait(READ_CLIP_EVENT event);
	READ_CLIP_EVENT State_ReadThumIdle(READ_CLIP_EVENT event);
	READ_CLIP_EVENT State_ReadThumWait(READ_CLIP_EVENT event);
	READ_CLIP_STATE m_read_clip_state;
};

#endif
