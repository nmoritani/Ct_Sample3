/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:	CtThumbButton
*/

#include "CtThumbButton.h"
#include "gdi_local.h"
#include "CtThumbCache.h"
#include "CtDrawCache.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
CtThumbButton::CtThumbButton() :
	m_IconType(IconType_Resume),
	m_ClipNo(0),
	m_pClipNumber(NULL),
	m_pMultiIcon(NULL),
	m_pFormatIcon(NULL),
	m_pImpossiblePlayIcon(NULL),
	m_pCodecIcon(NULL),
	m_pProtectIcon(NULL),
	m_pP2StartIcon(NULL),
	m_pReConnectIcon(NULL),
	m_pTitle(NULL),
	m_pPicture(NULL),
	m_bFunc(false)
{
	// Press���̃A�C�R�����h��΍�
	this->PressedLabelColor = CtColor::NoColor;

	initLayout();
	setThumbInfo(NULL);
}

CtThumbButton::~CtThumbButton()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//���C�A�E�g�쐬

//ThumbNail�{�^���̃��C�A�E�g��������
void CtThumbButton::initLayout()
{
	//�{�^�����̃A�C�R������CtLabel��������
	{
		CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter_Bottom, CtColor(255, 255, 255, 0xff));
		fSet.setSize(26);
		
		m_pClipNumber = new CtLabel();
		m_pMultiIcon = new CtLabel(CtSize(24, 24));
		m_pFormatIcon = new CtLabel(CtSize(102, 24));
		
		m_pImpossiblePlayIcon = new CtLabel(CtSize(42, 24), IC_THUMBNAIL_IMPOSSIBLE_TO_PLAY);
		m_pCodecIcon = new CtLabel(CtSize(102, 24));
		
		m_pProtectIcon = new CtLabel(CtSize(34, 24), IC_THUMBNAIL_PROTECT);
		m_pP2StartIcon = new CtLabel(CtSize(34, 24));
		m_pReConnectIcon = new CtLabel(CtSize(24, 24), IC_THUMBNAIL_P2_CLIP_RE_CONNECT);
		
		m_pTitle = new CtLabel("", fSet);
		m_pPicture = new CtLabel(CtSize(214, 120));
		m_pPicture->setVisible(false);
	}

	// Total Horizon 214
	//��i
	CtHLayout *pItemTop = new CtHLayout(CtColor(ColorRGBA, 0x00000037, NULL));
	pItemTop->addStretch(7);
	pItemTop->addWidget(m_pClipNumber, 69);				//�N���b�vNo.
	pItemTop->addWidget(m_pMultiIcon, 24);				//RESUME/DELETE/COPY...etc.�̃A�C�R��
	pItemTop->addStretch(8);
	pItemTop->addWidget(m_pFormatIcon, 102);			//format�̃A�C�R��
	pItemTop->addStretch(4);
	
	//���i�@ Total Horizon 214
	CtHLayout *pItemHighMiddle = new CtHLayout(CtColor::Trans);
	pItemHighMiddle->addStretch(8);
	pItemHighMiddle->addWidget(m_pImpossiblePlayIcon, 42);	//�Đ��s�A�C�R��a
	pItemHighMiddle->addStretch(58);
	pItemHighMiddle->addWidget(m_pCodecIcon, 102);			//�L�^�R�[�f�b�N
	pItemHighMiddle->addStretch(4);
	//���i�A-1
	CtHLayout *pItemLowMiddle1st = new CtHLayout(CtColor::Trans);
	pItemLowMiddle1st->addStretch(174);
	pItemLowMiddle1st->addWidget(m_pProtectIcon, 34);			//�v���e�N�g�A�C�R��
	pItemLowMiddle1st->addStretch(6);
	//���i�A-2
	CtHLayout *pItemLowMiddle2nd = new CtHLayout(CtColor::Trans);
	pItemLowMiddle2nd->addStretch(155);
	pItemLowMiddle2nd->addWidget(m_pP2StartIcon, 24);			//P2�s��/�s���N���b�v
	pItemLowMiddle2nd->addStretch(5);
	pItemLowMiddle2nd->addWidget(m_pReConnectIcon, 24);		//P2�s���S�N���b�v
	pItemLowMiddle2nd->addStretch(6);
	//���i�A
	CtLayout *pItemLowMiddle = new CtLayout(CtColor::Trans);
	pItemLowMiddle->addWidget(pItemLowMiddle1st);
	pItemLowMiddle->addWidget(pItemLowMiddle2nd);
	
	//��i�ƒ��i�����킹�ă��C�A�E�g����� Total Vertical 155
	CtVLayout* pItemIcons = new CtVLayout(CtSize(214, 151), CtColor::Trans);
	pItemIcons->addWidget(pItemTop, 30);
	pItemIcons->addWidget(pItemHighMiddle, 24);
	pItemIcons->addWidget(pItemLowMiddle, 24);
	pItemIcons->addStretch(66 + 8);
	
	//���i�w�i
	CtVLayout* pItemPicture = new CtVLayout();
	pItemPicture->addWidget(m_pPicture, 120);
	pItemPicture->addStretch(31);
	pItemPicture->setSize(CtSize(214, 151));
	
	// waiting�̔w�i�����ƃ^�C�g����
	CtVLayout* pItemTitle = new CtVLayout();
	CtFontSet fSet(FontTypeNormal_alignCenter, CtButton::LabelColor);
	fSet.setSize(30);
	pItemTitle->addWidget(new CtLabel("waiting...", fSet), 120);
	pItemTitle->addWidget(m_pTitle, 31);
	pItemTitle->setSize(CtSize(214, 151));
	
	//�T���l�C���{�^���̃��C�A�E�g���\�z
	setSize(CtSize(224, 159));
	setButtonShape(Rect, 5);
	
	CtLayout *pLayout = new CtLayout();
	pLayout->addWidget(pItemTitle);				// ���i�̃^�C�g��
	pLayout->addWidget(pItemPicture);			// �T���l�C���摜
	pLayout->addWidget(pItemIcons);				// �㒆�i�̃A�C�R��
	setTop(pLayout);
}

bool CtThumbButton::setIconType(CtThumbButton::IconType _Type)
{
	if (m_IconType == _Type)
		return false;
	
	m_IconType = _Type;
	return true;
}

bool CtThumbButton::setFunction(ContentsThumbSyncSelectCallback SelectClipFunc)
{
	m_SelectClip = SelectClipFunc;
	return true;
}

//�T���l�C���{�^���̃A�C�R���E�N���b�vNo.�Ȃǂ̍X�V
bool CtThumbButton::setThumbInfo(CtThumbInfo* pInfo)
{
	const char*  pName           = "";
	int          clipNo          = 0;
	bool         bImpossiblePlay = false;
	bool         bProtect        = false;
	bool         bReConnect      = false;
	GDI_IMAGE_ID CodecImageId    = GDI_IMAGE_ID_MAX;
	GDI_IMAGE_ID FormatImageId   = GDI_IMAGE_ID_MAX;
	GDI_IMAGE_ID P2StartImageId  = GDI_IMAGE_ID_MAX;
	bool         bFunc           = false;
	GDI_HANDLER  hPicture        = GDI_INVALID_ID;

	if (pInfo == NULL) {
		setVisible(false);		//NULL���󂯂����\���ɂ���
	} else {
		pName           = pInfo->getClipName();
		clipNo          = pInfo->getClipNo();
		bImpossiblePlay = pInfo->isImpossiblePlay();
		bProtect        = pInfo->isProtect();
		bReConnect      = pInfo->isReConnect();
		P2StartImageId  = pInfo->getP2StartImageID();
		CodecImageId    = pInfo->getCodecImageID();
		FormatImageId   = pInfo->getFormatImageID();
		bFunc           = pInfo->isFunc((int)m_IconType);
		hPicture        = pInfo->getPicture();

		setVisible(true);
	}

	/* �X�V */
	bool bVisible = (clipNo > 0);

	setTitle(pName);
	setClipNo(clipNo);
	if (m_pClipNumber != NULL) {
		m_pClipNumber->setVisible(bVisible);
	}
	if (m_pPicture != NULL) {
		m_pPicture->setDrawable(hPicture);
		m_pPicture->setVisible(bVisible);
	}
	setImpossiblePlayIcon(bImpossiblePlay);
	setProtectIcon(bProtect);
	setReConnectIcon(bReConnect);
	setP2StartIcon(P2StartImageId);
	setCodecIcon(CodecImageId);
	setFormatIcon(FormatImageId);
	setInfoIcon(m_IconType, bFunc);

	return true;
}

void CtThumbButton::readyGo(int ClipNo)
{
	if (m_pThumbCache != NULL) {
		setThumbInfo(m_pThumbCache->getThumbInfo(ClipNo, this));
	}
	m_ClipNo = ClipNo;
	setVisible(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�ʐ^�̍X�V
void CtThumbButton::setPicture(GDI_HANDLER hPicture)
{
	if (m_pPicture == NULL)
		return;
	m_pPicture->setDrawable(hPicture);
}

//�{�^�������̃^�C�g���̍X�V
void CtThumbButton::setTitle(const char* str)
{
	if (m_pTitle == NULL)
		return;
	m_pTitle->setText((str == NULL) ? "" : str);
}

//�{�^�����㑤�̃N���b�vNo�̍X�V
void CtThumbButton::setClipNo(int ClipNo)
{
	char clipNumber[5] = { 0 };
	m_ClipNo = ClipNo;
	CtThumbInfo* pThumbInfo = NULL;

	if (m_pClipNumber == NULL)
		return;
	
	sprintf(clipNumber, "%04d", ClipNo);

	if ( 0 != clipNumber[0]) {
		CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor(255, 255, 255, 0xff));
		fSet.setSize(26);				//TODO�F�N���b�vNo.�̕����T�C�Y��ύX����ꍇ�A�����őΉ��B
		m_pClipNumber->setText(clipNumber);
		m_pClipNumber->setFontSet(fSet);
	}
}

//�{�^�������̍Đ��s�A�C�R���̍X�V
void CtThumbButton::setImpossiblePlayIcon(bool bVisible)
{
	if (m_pImpossiblePlayIcon == NULL)
		return;
	m_pImpossiblePlayIcon->setVisible(bVisible);
}

//�{�^���E���̃v���e�N�g�A�C�R���̍X�V
void CtThumbButton::setProtectIcon(bool bVisible)
{
	if (m_pProtectIcon == NULL)
		return;
	m_pProtectIcon->setVisible(bVisible);
}

//�{�^���E����ReConnect�A�C�R���̍X�V
void CtThumbButton::setReConnectIcon(bool bVisible)
{
	if (m_pReConnectIcon == NULL)
		return;
	m_pReConnectIcon->setVisible(bVisible);
}

void CtThumbButton::setP2StartIcon(GDI_IMAGE_ID imageID)
{
	if (m_pP2StartIcon == NULL)
		return;

	if (imageID == GDI_IMAGE_ID_MAX) {
		m_pP2StartIcon->setVisible(false);
	}
	else {
		m_pP2StartIcon->setImage(imageID);
		m_pP2StartIcon->setVisible(true);
	}
}

void CtThumbButton::setCodecIcon(GDI_IMAGE_ID imageID)
{
	if (m_pCodecIcon == NULL)
		return;
	
	if (imageID == GDI_IMAGE_ID_MAX) {
		m_pCodecIcon->setVisible(false);
	}
	else {
		m_pCodecIcon->setImage(imageID);
		m_pCodecIcon->setVisible(true);
	}
}

//RESUME/DELETE/COPY...etc.�̃A�C�R���̍X�V
void CtThumbButton::setInfoIcon(CtThumbButton::IconType _Type, bool bVisible)
{
	GDI_IMAGE_ID id = IMAGE_ID_INVALID;
	CtSize size;
	m_bFunc = bVisible;
	if (!m_pMultiIcon) return;

	switch (_Type) {
	case IconType_Resume:
		if (APL_PARAM_GET_DATA(AplParamResume) == APL_SYS_PARAM_SWITCH_ON && m_bFunc) {
			id = IC_THUMBNAIL_RESUME;
			bVisible = true;
		}
		else {
			bVisible = false;
		}
		break;

	case IconType_Delete:
		id = IC_THUMBNAIL_DELETE;
		break;

	case IconType_Copy:
		id = IC_THUMBNAIL_COPY;
		break;

	default:
		break;
	}

	m_pMultiIcon->setImage(id);
	if (_Type == IconType_Delete) {
		m_pMultiIcon->setColor(CtColor::Red);
	}
	m_pMultiIcon->setVisible(bVisible);
}

void CtThumbButton::setFormatIcon(GDI_IMAGE_ID imageID)
{
	if (m_pFormatIcon == NULL)
		return;
	
	if (imageID == GDI_IMAGE_ID_MAX) {
		m_pFormatIcon->setVisible(false);
	}
	else {
		m_pFormatIcon->setImage(imageID);
		m_pFormatIcon->setVisible(true);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//!! �t�H�[�J�X�����������ꍇ�AAPL��SetFocus��ʒm����K�v������B

//!! AplParamDisplayData���ύX���ꂽ�ꍇ�A�N���b�v���\����StartTC�Ɛ؂�ւ����K�v�B

bool CtThumbButton::handleParamEvent(const CtEventParam & Param)
{
	switch (Param.getParamId()) {
	case AplParamDisplayData:
		if (m_pThumbCache != NULL) {
			return setThumbInfo(m_pThumbCache->getThumbInfo(m_ClipNo, this));
		}
		break;
	case AplParamResume:
		setInfoIcon(m_IconType, m_bFunc);
		break;
	default:
		break;
	}
	return false;
}

bool CtThumbButton::styleNormal()
{
	bool bRet = CtButton::styleNormal();
	if (m_IconType == IconType_Delete)
		m_pMultiIcon->setColor(CtColor::Red);
	
	return bRet;
}

bool CtThumbButton::styleFocused()
{
	bool bRet = CtButton::styleFocused();
	if (m_IconType == IconType_Delete)
		m_pMultiIcon->setColor(CtColor::Red);
	
	return bRet;
}

bool CtThumbButton::stylePressed()
{
	bool bRet = CtButton::stylePressed();
	if (m_IconType == IconType_Delete)
		m_pMultiIcon->setColor(CtColor::Red);
	
	m_pTitle->setColor(CtColor::Black);
	
	return bRet;
}

bool CtThumbButton::styleInvalid()
{
	bool bRet = CtButton::styleInvalid();
	if (m_IconType == IconType_Delete)
		m_pMultiIcon->setColor(CtColor::Red);
	
	return bRet;
}

bool CtThumbButton::onRelease()
{
	bool bRet = false;
	bRet = CtButton::onRelease();
	
	if (m_SelectClip != NULL) {
		ContentsThumbSelectInfo SelectInfo = {(unsigned long)m_ClipNo};
		
		if ((*m_SelectClip)(&SelectInfo) == false)
			return true;

		if (m_pThumbCache == NULL)
			return true;

		CtThumbInfo* pInfo = m_pThumbCache->getThumbInfo(m_ClipNo);
		if (pInfo == NULL)
			return true;
		
		switch (m_IconType) {
		case IconType_Delete:
		case IconType_Copy:
			pInfo->invertFuncIcon();
			setThumbInfo(pInfo);
			break;
		case IconType_Protect:
			pInfo->invertProtectIcon();
			setThumbInfo(pInfo);
			break;
		default:
			break;
		}
	}
	return bRet;
}
