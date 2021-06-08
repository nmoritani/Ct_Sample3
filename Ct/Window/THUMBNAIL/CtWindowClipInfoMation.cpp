/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:            CtWindowClipInfoMation
 */


#include "CtWindowClipInfoMation.h"
#include "string_api.h"
#include "CtDrawCache.h"

#define WidgetIDUP (0xFFFF)
#define WidgetIDDW (0xFFFE)
#define WidgetIDRETURN (0xFFFB)

typedef struct _IconSet {
	int AplNo;
	GDI_STRING_ID StringID;
	GDI_IMAGE_ID ImageID;
} tIconSet;

static const GDI_STRING_ID  InfoDetailTitle[] = {
		STR_ID_NO_10603,    /* 10603: �uSTART TC�v: �B�e�J�n���̃^�C���R�[�h */
		STR_ID_NO_10604,    /* 10604: �uSTART UB�v: �B�e�J�n���̃��[�U�[�Y�r�b�g */
		STR_ID_NO_10605,    /* 10605: �uDATE�v: �B�e�� */
		STR_ID_NO_10606,    /* 10606: �uTIME�v: �B�e���� */
		STR_ID_NO_10608,    /* 10608: �uDURATION�v: �L�^���� */
		STR_ID_NO_10609,    /* 10609: �uPIXEL/FREQ�v: �L�^�𑜓x/�L�^���g�� */
		STR_ID_NO_10610,    /* 10610: �uCODEC�v: �L�^�R�[�f�b�N */
		STR_ID_NO_10368,	/* 10368: �uFRAME RATE�v*/
		STR_ID_NO_10255,	/* 10255: �uGAMMA�v*/
};

static const GDI_STRING_ID  InfoDetailCodec[] = {
	STR_ID_NO_10622,    /* 10622: �uAVCHD PS�v: AVCHD 4:2:0 8bit LongGOP 25Mbps */
	STR_ID_NO_10623,    /* 10623: �uAVCHD PH�v: AVCHD 4:2:0 8bit LongGOP 21Mbps */
	STR_ID_NO_10624,    /* 10624: �uAVCHD HA�v: AVCHD 4:2:0 8bit LongGOP 17Mbps */
	STR_ID_NO_10625,    /* 10625: �uAVCHD PM�v: AVCHD 4:2:0 8bit LongGOP 8Mbps */
	STR_ID_NO_11428,	/* 11428: �uAVCHD SA�v: AVCHD 4:2:0 8bit LongGOP 8Mbps */
	STR_ID_NO_10611,    /* 10611: �uMOV 420LongG 150M�v: MOV 4:2:0 8bit LongGOP 150Mbps */
	STR_ID_NO_10612,    /* 10612: �uMOV 420LongG 100M�v: MOV 4:2:0 8bit LongGOP 100Mbps */
	STR_ID_NO_10613,    /* 10613: �uMOV 420LongG 50M�v: MOV 4:2:0 8bit LongGOP 50Mbps */
	STR_ID_NO_10614,    /* 10614: �uMOV 420LongG 12M�v: MOV 4:2:0 8bit LongGOP 12Mbps */
	STR_ID_NO_10615,    /* 10615: �uMOV 420LongG 6M�v: MOV 4:2:0 8bit LongGOP 6Mbps */
	STR_ID_NO_10616,    /* 10616: �uMOV 422LongG 150M�v: MOV 4:2:2 10bit LongGOP 150Mbps */
	STR_ID_NO_10617,    /* 10617: �uMOV 422LongG 100M�v: MOV 4:2:2 10bit LongGOP 100Mbps */
	STR_ID_NO_10618,    /* 10618: �uMOV 422LongG 50M�v: MOV 4:2:2 10bit LongGOP 50Mbps */
	STR_ID_NO_10619,    /*  */
	STR_ID_NO_10620,    /*  */
	STR_ID_NO_10621,    /*  */
	STR_ID_NO_11426,	/* 11426: �uMOV HEVC LongG 200M�v: MOV HEVC LongG 200M(MAIN CODEC) */
	STR_ID_NO_11427,	/* 11427: �uMOV HEVC LongG 150M�v: MOV HEVC LongG 150M(MAIN CODEC) */
	STR_ID_NO_10610,	/* Dummy: �uMOV HEVC LongG 100M�v: */
	STR_ID_NO_10610,	/* Dummy: �uAVC ULTRA 422Intra�v: */
	STR_ID_NO_10610,	/* Dummy: �uAVC ULTRA LongG50�v: */
	STR_ID_NO_10610,	/* Dummy: �uAVC ULTRA LongG25�v: */
	STR_ID_NO_10610,	/* Dummy: �uAVC ULTRA LongG12�v: */
};

static const GDI_STRING_ID InfoDetailPixel[] = {
	STR_ID_NO_10450, // "720x480p"
	STR_ID_NO_10451, // "720x576p"
	STR_ID_NO_10036, // "4096x2160"
	STR_ID_NO_10037, // "3840x2160"
	STR_ID_NO_10038, // "2048x1080"
	STR_ID_NO_10039, // "1920x1080"
	STR_ID_NO_10040, // "1280x720"
};
static  const GDI_STRING_ID InfoDetailFrenc[] = {
	STR_ID_NO_10026,    /* 10026: �u59.94p�v: 59.94p */
	STR_ID_NO_10028,    /* 10028: �u59.94i�v: 59.94i */
	STR_ID_NO_10025,    /* 10025: �u50.00p�v: 50.00p */
	STR_ID_NO_10027,    /* 10027: �u50.00i�v: 50.00i */
	STR_ID_NO_10024,    /* 10024: �u29.97p�v: 29.97p */
	STR_ID_NO_10023,    /* 10023: �u25.00p�v: 25.00p */
	STR_ID_NO_10022,    /* 10022: �u24.00p�v: 24.00p */
	STR_ID_NO_10021,    /* 10021: �u23.98p�v: 23.98p */
};
static const char* StringList[3] = {
	"--:--:--.--",
	"--:--:--:--",
	"--------"
};

CtWindowClipInfoMation::CtWindowClipInfoMation() :
	m_pBtnUp(NULL),
	m_pBtnDown(NULL),
	m_pBtnReturn(NULL),
	m_pTitleBar(NULL),
	m_pDrawInfo(NULL),
	m_pInitInfo(NULL),
	m_pSelectClipInfo(NULL),
	m_wcEvent(WC_NONE),
	m_Clipcnt(0),
	m_pPixel(NULL),
	m_pSeparate(NULL),
	m_pFreq(NULL),
	m_read_clip_state(S_READ_CLIP_IDLE),
	m_pReConnect(NULL),
	m_pP2Start(NULL)
{
	for (int i = 0; i < 12; i++) {
		m_pLabeIcon[i] = NULL;
	}
	setClassType(CtClassType_LayoutMain);
}

CtWindow* CtWindowClipInfoMation::createWindow()
{
	// �^�C�g��
	m_pTitleBar = new CtContainerThumbnailTitleBar(getWindowID());

	// Main
	CtHLayout* pMain = new CtHLayout();
	pMain->addStretch(14);
	pMain->addWidget(createLayoutLeftButton(), 78);
	pMain->addStretch(64);
	pMain->addWidget(createLayoutOneItemIcon(), 218);
	pMain->addStretch(56);
	pMain->addWidget(createLayoutRightText(), 530);

	// �S��
	CtVLayout* pAll = new CtVLayout();
	pAll->addContainer(m_pTitleBar, 42);
	pAll->addWidget(new CtLabel(CtColor(134, 134, 134, 0xff)), 2);
	pAll->addWidget(pMain, 596);

	CtWindow* pWin = new CtWindow(CtColor::Black);
	pWin->addWidget(pAll);

	return pWin;
}

CtLayout* CtWindowClipInfoMation::createLayoutLeftButton() {

	// �����̍��O�{�^����ǉ�����
	m_pBtnUp = new CtButton(CtSize(78, 66), IC_MENU_UP);
	m_pBtnUp->setWidgetID(WidgetIDUP);
	m_pBtnUp->setInvalid(true);
	m_pBtnUp->setFocusable(false);  // KeyCode_MmrMinus�AKeyCode_MmrPlus���A�t�H�[�J�X�ڂ̂ŁA�����ňړ��ł��Ȃ��ɐݒ肷��
	m_pBtnDown = new CtButton(CtSize(78, 66), IC_MENU_DOWN);
	m_pBtnDown->setWidgetID(WidgetIDDW);
	m_pBtnDown->setInvalid(true);
	m_pBtnDown->setFocusable(false);// KeyCode_MmrMinus�AKeyCode_MmrPlus���A�t�H�[�J�X�ڂ̂ŁA�����ňړ��ł��Ȃ��ɐݒ肷��
	m_pBtnReturn = new CtButton(CtSize(78, 66), IC_MENU_RETURN);
	m_pBtnReturn->setWidgetID(WidgetIDRETURN);
	m_pBtnReturn->setFocusable(false);// KeyCode_MmrMinus�AKeyCode_MmrPlus���A�t�H�[�J�X�ڂ̂ŁA�����ňړ��ł��Ȃ��ɐݒ肷��

	CtVLayout* pLayout = new CtVLayout(CtColor::Black);
	pLayout->addStretch(14 + 66 + 72);
	pLayout->addWidget(m_pBtnUp, 66);
	pLayout->addStretch(62);
	pLayout->addWidget(m_pBtnDown, 66);
	pLayout->addStretch(72);
	pLayout->addWidget(m_pBtnReturn, 66);
	pLayout->addStretch(14);

	return pLayout;
}

CtLayout* CtWindowClipInfoMation::createLayoutOneItemIcon() {

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor(255, 255, 255, 0xff));

	// �A�C�R������
	m_pLabeIcon[0] = new CtLabel("", fSet);

	m_pLabeIcon[1] = new CtLabel(IC_THUMBNAIL_IMPOSSIBLE_TO_PLAY);
	m_pLabeIcon[1]->setVisible(false);

	m_pLabeIcon[2] = new CtLabel(IC_THUMBNAIL_PROTECT);
	m_pLabeIcon[2]->setVisible(false);

	m_pLabeIcon[3] = new CtLabel(CtSize(218, 120), CtColor::Trans);
	m_pLabeIcon[3]->setColor(CtColor(0, 0, 0, 0xff), CtColor(134, 134, 134, 0xff));
	m_pLabeIcon[4] = new CtLabel("", fSet);

	m_pP2Start = new CtStackLabel();
	m_pP2Start->addLabel(new CtLabel(""));
	m_pP2Start->addLabel(new CtLabel(IC_THUMBNAIL_P2_CLIP_REPAIRABLE));
	m_pP2Start->addLabel(new CtLabel(IC_THUMBNAIL_P2_CLIP_UNREPAIRABLE));
	m_pP2Start->addLabel(new CtLabel(IC_THUMBNAIL_P2_CLIP_UNKNOWN));

	m_pReConnect = new CtLabel(IC_THUMBNAIL_P2_CLIP_RE_CONNECT);
	m_pReConnect->setVisible(false);

	// ��i��
	CtHLayout *pLayout1 = new CtHLayout(CtColor(30, 30, 30, 0xff));
	pLayout1->addWidget(m_pLabeIcon[0]);

	// ��i��
	CtHLayout *pLayout2_1 = new CtHLayout();
	pLayout2_1->addStretch(8);
	pLayout2_1->addWidget(m_pLabeIcon[1], 42);
	pLayout2_1->addStretch(126);
	pLayout2_1->addWidget(m_pLabeIcon[2], 34);
	pLayout2_1->addStretch(8);

	CtHLayout *pLayout2_2 = new CtHLayout();
	pLayout2_2->addStretch(126);
	pLayout2_2->addWidget(m_pP2Start, 42);
	pLayout2_2->addStretch(8);
	pLayout2_2->addWidget(m_pReConnect, 34);
	pLayout2_2->addStretch(8);

	CtLayout *pLayout2 = new CtLayout(CtColor(30, 30, 30, 0xff));
	pLayout2->addWidget(pLayout2_1);
	pLayout2->addWidget(pLayout2_2);

	// �O�i��
	CtHLayout *pLayout3 = new CtHLayout(CtColor::Trans);
	pLayout3->addWidget(m_pLabeIcon[3]);

	// �l�i��
	CtHLayout *pLayout4 = new CtHLayout(CtColor(30, 30, 30, 0xff));
	pLayout4->addWidget(m_pLabeIcon[4]);

	// ���C�A�E�g�\�z
	CtVLayout* pMain = new CtVLayout(CtSize(218, 240), CtColor::Trans);
	pMain->addWidget(pLayout1, 41);
	pMain->addWidget(pLayout2, 29);
	pMain->addStretch(2);
	pMain->addWidget(pLayout3, 120);
	pMain->addStretch(2);
	pMain->addWidget(pLayout4, 46);
	pMain->setVisible(true);

	CtVLayout* pAll = new CtVLayout();
	pAll->addStretch(137);
	pAll->addWidget(pMain, 283);
	pAll->addStretch(167);

	return pAll;
}

CtLayout* CtWindowClipInfoMation::createLayoutRightText() {

	CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor(255, 255, 255, 0xff));
	CtHLayout* pLayout = NULL;

	CtVLayout* pLayoutRight = new CtVLayout();
	pLayoutRight->setSize(CtSize(530, 498));
	pLayoutRight->addWidget(new CtLabel(), 22);
	int indexMax = sizeof(InfoDetailTitle) / sizeof(GDI_STRING_ID);
	for (int i = 0; i < indexMax; i++) {
		pLayout = new CtHLayout();
		pLayout->addWidget(new CtLabel(InfoDetailTitle[i], fSet), 28 * 8);
		pLayout->addSpacing(CtSize(60, 0));

		if (InfoDetailTitle[i] == STR_ID_NO_10609) {
			/* PIXEL/FREQ�̂ݓ��� */
			/* m_pLabeIcon��[10]�̂ݖ��g�p�ɂȂ� */
			CtHLayout *pPixFreq = new CtHLayout();
			m_pPixel = new CtLabel("", fSet);
			m_pSeparate = new CtLabel("/", fSet);
			m_pFreq = new CtLabel("", fSet);
			pPixFreq->addWidget(m_pPixel, 9);
			pPixFreq->addWidget(m_pSeparate, 1);
			pPixFreq->addWidget(m_pFreq, 6);
			pLayout->addWidget(pPixFreq, 36 * 8);
		}
		else {
			m_pLabeIcon[i + 5] = new CtLabel("", fSet);
			pLayout->addWidget(m_pLabeIcon[i + 5], 36 * 8);
		}
		pLayout->addSpacing(CtSize(100, 0));
		pLayoutRight->addWidget(pLayout, 64);
	}
	pLayoutRight->addWidget(new CtLabel(), 28);
	pLayoutRight->setVisible(true);

	return pLayoutRight;
}

bool CtWindowClipInfoMation::setContents(const CtWindowContents* pContents)
{
	if (pContents == NULL) {
		return false;
	}

	switch (pContents->getType()) {
	case Window_ThumbNailClip:
		break;
	default:
		return false;
	}

	CtWindowContentsThumb* pThumb = (CtWindowContentsThumb*)pContents;
	if (pThumb == NULL) {
		return false;
	}

	switch (pThumb->getContentsThumbType()) {
	case CtWindowContentsThumb::ContentsThumbType_Thumb:
		return false;

	case CtWindowContentsThumb::ContentsThumbType_DrawThumb:
	{
		if (m_pDrawInfo != NULL) {
			delete m_pDrawInfo;
			m_pDrawInfo = NULL;
		}

		m_pDrawInfo = new CtWindowContentsDrawThumb((CtWindowContentsDrawThumb&)*pContents);
		m_wcEvent = WC_DRAW_THUMNAIL;
	}
	return true;

	case CtWindowContentsThumb::ContentsThumbType_Init:
	{
		if (m_pInitInfo != NULL) {
			delete m_pInitInfo;
			m_pInitInfo = NULL;
		}
		m_pInitInfo = new CtWindowContentsThumbInit((CtWindowContentsThumbInit&)*pContents);
		setClipCnt(m_pInitInfo->getClipCount());
	}
	m_wcEvent = WC_DRAW_INIT;
	return true;

	case CtWindowContentsThumb::ContentsThumbType_SelectClipInfo:
	{
		if (m_pSelectClipInfo != NULL) {
			delete m_pSelectClipInfo;
			m_pSelectClipInfo = NULL;
		}
		m_pSelectClipInfo = new CtWindowContentsSelectClipInfo((CtWindowContentsSelectClipInfo&)*pContents);
	}
	m_wcEvent = WC_SELECT_CLIPINFO;
	return true;

	default:
		break;
	}

	return false;
}

void CtWindowClipInfoMation::callback_setCurrentIndex(int index)
{
	if (NULL == m_pInitInfo) {
		return;
	}

	ContentsThumbSelectIndexCallback func = m_pInitInfo->getFuncSetFocus();
	if (NULL == func) {
		return;
	}
	(*func)(index + 1);
}

bool CtWindowClipInfoMation::handleButtonEvent(const CtEventButton& Button)
{

	/* Release�ł̂ݏ��� */
	if (Button.getPressType() != CtEventButton::ShortPress
		&& Button.getPressType() != CtEventButton::RepeatPress) {
		return false;
	}

	switch (Button.getWidgetID()) {
	case WidgetIDUP:
	{
		unsigned long index = getCurrentNo();
		if (index == 1) {
			index = getClipCnt();
		}
		else {
			index--;
		}
		setCurrentClipNo(index);
		updateThumbnail(getCurrentNo() - 1);
		updatePicture();

		return true;
	}
	break;
	case WidgetIDDW:
	{
		unsigned long index = getCurrentNo();
		index++;
		if (index > getClipCnt()) {
			index = 1;
		}
		setCurrentClipNo(index);
		updateThumbnail(getCurrentNo() - 1);
		updatePicture();

		return true;
	}
	break;
	case WidgetIDRETURN:
		//(2017.07.10) ���CLOSE��APL�ɔC����
		CtEventInterface::requestFuncCmd(getWindowID(),FuncID_CLIPINFO_RETURN);
		return true;
	default:
		break;
	}
	return false;
}

bool CtWindowClipInfoMation::destroyWindow()
{
	if (m_pInitInfo != NULL) {
		delete m_pInitInfo;
		m_pInitInfo = NULL;
	}
	if (m_pSelectClipInfo != NULL) {
		delete m_pSelectClipInfo;
		m_pSelectClipInfo = NULL;
	}
	if (m_pDrawInfo != NULL) {
		delete m_pDrawInfo;
		m_pDrawInfo = NULL;
	}

	if (!m_list.empty()) {
		for (int i = 0; i < m_list.size(); i++) {
			if (NULL != m_list[i]) delete m_list[i];
			m_list[i] = NULL;
			DeleteThumbnailDrawable(i);
		}
		m_list.clear();
	}
	return true;
}

bool CtWindowClipInfoMation::handleParamEvent(const CtEventParam& Param) {
	bool bRet = false;
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	return false;
}

void CtWindowClipInfoMation::initThumbnail()
{
	if (NULL == m_pInitInfo) {
		return;
	}

	int size = m_pInitInfo->getClipCount();

	//���X�g��������
	if (!m_list.empty()) {
		for (int i = 0; i < m_list.size(); i++) {
			if (NULL != m_list[i]) delete m_list[i];
			m_list[i] = NULL;
		}
		m_list.clear();
	}

	for (int i = 0; i < size; i++) {
		m_list.push_back(NULL);
	}

	m_read_clip_state = S_READ_CLIP_IDLE;
	setCurrentClipNo(m_pInitInfo->getCurrentIndex());
}

void CtWindowClipInfoMation::BlankClipInfomation(unsigned long index)
{
	char str[50] = { 0 };
	CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor(255, 255, 255, 0xff));
	fSet.setAspectRatio(AspectRatio_Wide);

	memset(str, 0, sizeof(str));

	/* ���i���� */
	updateClipNo(index + 1);									// �N���b�v�ԍ�
	updateClipName("");											// �N���b�v��
	updateNotPlayIcon(false);									// �Đ��s�N���b�v
	updateProtectIcon(false);									// �N���b�v�v���e�N�g
	updateP2StartIcon(CtClipInfo::ClipInfoP2StartType_Normal);	// P2�s��/�s�ǃN���b�v
	updateReConnectIcon(false);									// P2�s���S�N���b�v

	// �@�X�^�[�gTC
	m_pLabeIcon[5]->setText("--:--:--:--");
	m_pLabeIcon[5]->setFontSet(fSet);

	// �A�X�^�[�gUB
	m_pLabeIcon[6]->setText("--------");
	m_pLabeIcon[6]->setFontSet(fSet);

	// �B�B�e��
	m_pLabeIcon[7]->setText("");
	m_pLabeIcon[7]->setFontSet(fSet);

	// �C�B�e����
	m_pLabeIcon[8]->setText("");
	m_pLabeIcon[8]->setFontSet(fSet);


	// �D�L�^����
	m_pLabeIcon[9]->setText("--:--:--:--");
	m_pLabeIcon[9]->setFontSet(fSet);

	// �E�L�^�𑜓x�����g��
	m_pPixel->setVisible(false);
	m_pSeparate->setVisible(false);
	m_pFreq->setVisible(false);

	// �F�L�^�R�[�f�b�N
	m_pLabeIcon[11]->setVisible(false);

	// �G�L�^�t���[�����[�g
	m_pLabeIcon[12]->setText("");
	m_pLabeIcon[12]->setVisible(false);

	// �H�K���}
	m_pLabeIcon[13]->setText("");
	m_pLabeIcon[13]->setVisible(false);
}

void CtWindowClipInfoMation::updateThumbnail(unsigned long index)
{
	char str[50] = { 0 };
	CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor(255, 255, 255, 0xff));
	CtFontSet fSetInvalid = CtFontSet(FontTypeNormal, CtColor(255, 255, 255, 0xff));
	fSetInvalid.setAspectRatio(AspectRatio_Wide);

	static char* pMonth[12] = {
		"JAN",
		"FEB",
		"MAR",
		"APR",
		"MAY",
		"JUN",
		"JUL",
		"AUG",
		"SEP",
		"OCT",
		"NOV",
		"DEC"
	};

	memset(str, 0, sizeof(str));

	/*NULL�`�F�b�N*/
	if (m_pInitInfo == NULL) {
		return;
	}

	CtClipInfo* pClipInfo = m_list[index];
	if (NULL == pClipInfo) {
		BlankClipInfomation(index);
		updatePicture();
		return;
	}

	CtClipInfo::ClipInfo ClipInfoItem = m_list[index]->getClipInfo();

	/* ���i���� */
	updateClipNo(ClipInfoItem.ClipNumber);				// �N���b�v�ԍ�
	updateClipName(ClipInfoItem.ClipName);				// �N���b�v��
	updateNotPlayIcon(ClipInfoItem.DifferentFreqFlag);	// �Đ��s�N���b�v
	updateProtectIcon(ClipInfoItem.LockFlag);			// �N���b�v�v���e�N�g
	updateP2StartIcon(ClipInfoItem.P2Start);			// P2�s��/�s�ǃN���b�v
	updateReConnectIcon(ClipInfoItem.ReConnectFlag);	// P2�s���S�N���b�v


	// �@�X�^�[�gTC
	memset(str, NULL, sizeof(str));
	if (ClipInfoItem.StartTC.ValidFlag) {
		m_pLabeIcon[5]->setFontSet(fSet);
		(ClipInfoItem.StartTC.DFType == CtClipInfo::ClipInfoDFType_DF) ?
			sprintf(str, "%02d:%02d:%02d.%02d",
				ClipInfoItem.StartTC.Hour,
				ClipInfoItem.StartTC.Min,
				ClipInfoItem.StartTC.Sec,
				ClipInfoItem.StartTC.Frame)
			:
			sprintf(str, "%02d:%02d:%02d:%02d",
				ClipInfoItem.StartTC.Hour,
				ClipInfoItem.StartTC.Min,
				ClipInfoItem.StartTC.Sec,
				ClipInfoItem.StartTC.Frame);
		m_pLabeIcon[5]->setText(str);
	}
	else {
		m_pLabeIcon[5]->setFontSet(fSetInvalid);
		if (ClipInfoItem.StartTC.DFType == CtClipInfo::ClipInfoDFType_DF) {
			m_pLabeIcon[5]->setText(StringList[0]);
		}
		else {
			m_pLabeIcon[5]->setText(StringList[1]);
		}
	}
	// �A�X�^�[�gUB
	memset(str, NULL, sizeof(str));
	if (ClipInfoItem.StartUB.ValidFlag) {
		m_pLabeIcon[6]->setFontSet(fSet);
		sprintf(str, "%02X%02X%02X%02X",
			ClipInfoItem.StartUB.First,
			ClipInfoItem.StartUB.Second,
			ClipInfoItem.StartUB.Third,
			ClipInfoItem.StartUB.Fourth);
	}
	else {
		m_pLabeIcon[6]->setFontSet(fSetInvalid);
		sprintf(str, "--------");
	}
	m_pLabeIcon[6]->setText(str);

	// �B�B�e��
	memset(str, NULL, sizeof(str));
	if (ClipInfoItem.DateTime.Date.ValidFlag == true) {
		int date_month = ClipInfoItem.DateTime.Date.Month - 1;
		if ((0 <= date_month) && (date_month < 12)) {
			m_pLabeIcon[7]->setFontSet(fSet);
			switch (APL_PARAM_GET_DATA(AplParamDateFormatMode)) {
			case APL_SYS_PARAM_DATE_FORMAT_YEAR:
			default:
				sprintf(str, "%2d %s %2d",
					ClipInfoItem.DateTime.Date.Year,
					pMonth[date_month],
					ClipInfoItem.DateTime.Date.Day);
				break;
			case APL_SYS_PARAM_DATE_FORMAT_MONTH:
				sprintf(str, "%s %2d %2d",
					pMonth[date_month],
					ClipInfoItem.DateTime.Date.Day,
					ClipInfoItem.DateTime.Date.Year);
				break;
			case APL_SYS_PARAM_DATE_FORMAT_DATE:
				sprintf(str, "%2d %s %2d",
					ClipInfoItem.DateTime.Date.Day,
					pMonth[date_month],
					ClipInfoItem.DateTime.Date.Year);
				break;
			}
		}
		else {
			m_pLabeIcon[7]->setFontSet(fSetInvalid);
			sprintf(str, "");
		}
	}
	else {
		sprintf(str, "");
	}
	m_pLabeIcon[7]->setText(str);

	// �C�B�e����
	memset(str, NULL, sizeof(str));
	m_pLabeIcon[8]->setFontSet(fSet);
	char strTimeFormat[] = "%02d:%02d:%02d";
	char strSignFlgFormat[] = "(GMT+%02d:%02d)";
	char strFormat[] = "(GMT-%02d:%02d)";
	char format[32] = "";
	char strTimeZone[32] = "";

	if (ClipInfoItem.DateTime.Time.ValidFlag == true) {
		sprintf(str, strTimeFormat,
			ClipInfoItem.DateTime.Time.Hour,
			ClipInfoItem.DateTime.Time.Min,
			ClipInfoItem.DateTime.Time.Sec);

	}
	if (ClipInfoItem.TimeZone.ValidFlag == true) {
		if (ClipInfoItem.TimeZone.SignFlag == true) {
			memcpy(format, strSignFlgFormat, sizeof(strSignFlgFormat));
		}
		else {
			memcpy(format, strFormat, sizeof(strFormat));
		}
		sprintf(strTimeZone, format,
			ClipInfoItem.TimeZone.Hour,
			ClipInfoItem.TimeZone.Min);

		strcat(str, strTimeZone);
	}
	m_pLabeIcon[8]->setText(str);

	// �D�L�^����
	memset(str, NULL, sizeof(str));
	if (ClipInfoItem.Duration.ValidFlag) {
		m_pLabeIcon[9]->setFontSet(fSet);
		(ClipInfoItem.Duration.DFType == CtClipInfo::ClipInfoDFType_DF) ?
			sprintf(str, "%02d:%02d:%02d.%02d",
				ClipInfoItem.Duration.Hour,
				ClipInfoItem.Duration.Min,
				ClipInfoItem.Duration.Sec,
				ClipInfoItem.Duration.Frame)
			:
			sprintf(str, "%02d:%02d:%02d:%02d",
				ClipInfoItem.Duration.Hour,
				ClipInfoItem.Duration.Min,
				ClipInfoItem.Duration.Sec,
				ClipInfoItem.Duration.Frame);

		m_pLabeIcon[9]->setText(str);
	}
	else {
		m_pLabeIcon[9]->setFontSet(fSetInvalid);
		if (ClipInfoItem.Duration.DFType == CtClipInfo::ClipInfoDFType_DF) {
			m_pLabeIcon[9]->setText(StringList[0]);
		}
		else {
			m_pLabeIcon[9]->setText(StringList[1]);
		}
	}

	// �E�L�^�𑜓x�����g��
	// Pixel or Freq �� None�̏ꍇ�S�ĕ\�����Ȃ�
	if (ClipInfoItem.PixelType == CtClipInfo::ClipInfoPixelType_None
		|| ClipInfoItem.FrequencyType == CtClipInfo::ClipInfoFrequencyType_None) {
		m_pPixel->setVisible(false);
		m_pSeparate->setVisible(false);
		m_pFreq->setVisible(false);
	}
	else {
		m_pPixel->setStringID(InfoDetailPixel[getDetailPixelType(ClipInfoItem.PixelType, ClipInfoItem.FrequencyType)]);
		m_pFreq->setStringID(InfoDetailFrenc[(ClipInfoItem.FrequencyType != 0) ? (ClipInfoItem.FrequencyType - 1) : 0]);
		m_pPixel->setVisible(true);
		m_pSeparate->setVisible(true);
		m_pFreq->setVisible(true);
	}

	// �F�L�^�R�[�f�b�N
	// Codec��None�̎��ɂ͉����\�����Ȃ�
	if (ClipInfoItem.CodecType == CtClipInfo::ClipInfoCodecType_None) {
		m_pLabeIcon[11]->setVisible(false);
	}
	else {
		m_pLabeIcon[11]->setStringID(InfoDetailCodec[(ClipInfoItem.CodecType != 0) ? (ClipInfoItem.CodecType - 1) : 0]);
		m_pLabeIcon[11]->setVisible(true);
	}

	// �G�L�^�t���[�����[�g
	if (ClipInfoItem.FPSvalue.ValidFlag == false) {
		m_pLabeIcon[12]->setVisible(false);
	}
	else {
		memset(str, NULL, sizeof(str));
		sprintf(str, "%.0ffps", ClipInfoItem.FPSvalue.fps);
		m_pLabeIcon[12]->setText(str);
		m_pLabeIcon[12]->setVisible(true);
	}

	// �H�K���}
	memset(str, NULL, sizeof(str));
	sprintf(str, "%s", ClipInfoItem.CaptureGamma);
	m_pLabeIcon[13]->setText(str);
	m_pLabeIcon[13]->setVisible(true);

	updateSd();
	callback_setCurrentIndex(index);

	CtDebugPrint(CtDbg, "%s %d ----------\n", __FUNCTION__, __LINE__);

}

bool CtWindowClipInfoMation::updateClipNo(unsigned long index)
{
	if (m_pLabeIcon[0] == NULL)
		return false;

	char str[10] = { 0 };
	sprintf(str, "No.%04d", index);

	return m_pLabeIcon[0]->setText(str);
}

bool CtWindowClipInfoMation::updateNotPlayIcon(bool bVisible)
{
	if (m_pLabeIcon[1] == NULL)
		return false;

	return m_pLabeIcon[1]->setVisible(bVisible);
}

bool CtWindowClipInfoMation::updateProtectIcon(bool bVisible)
{
	if (m_pLabeIcon[2] == NULL)
		return false;

	return m_pLabeIcon[2]->setVisible(bVisible);
}

bool CtWindowClipInfoMation::updateClipName(const char* name)
{
	if (m_pLabeIcon[4] == NULL)
		return false;

	if (name == NULL)
		return m_pLabeIcon[4]->setText("");

	return m_pLabeIcon[4]->setText(name);
}

bool CtWindowClipInfoMation::updateP2StartIcon(CtClipInfo::ClipInfoP2StartType Type)
{
	if (m_pP2Start == NULL)return false;

	switch (Type) {
	case CtClipInfo::ClipInfoP2StartType_Repairable:
		return m_pP2Start->index(1);

	case CtClipInfo::ClipInfoP2StartType_Unrepairable:
		return m_pP2Start->index(2);

	case CtClipInfo::ClipInfoP2StartType_Unknown:
		return m_pP2Start->index(3);

	case CtClipInfo::ClipInfoP2StartType_Normal:
	default:
		return m_pP2Start->index(0);
	}
	return false;
}

bool CtWindowClipInfoMation::updateReConnectIcon(bool bVisible)
{
	if (m_pReConnect == NULL)return false;

	return m_pReConnect->setVisible(bVisible);
}

bool CtWindowClipInfoMation::updateSd()
{
	/* �T���l�C���I����� */
	if (NULL != m_pInitInfo) {  //�������ς݂�������X�V
		unsigned long list_index = getCurrentNo() - 1; /* (����)CurrentIndex��[1]�J�n */
		if (list_index < (unsigned long)m_list.size()) {    /* pgr0360 */
			if ((list_index + 1) <= (unsigned long)m_list.size() && m_list[list_index] != NULL) {

				switch (m_list[list_index]->getClipInfo().MediaType) {
				case CtClipInfo::ClipInfoMediaType_SD1:
					return m_pTitleBar->updateMediaType(CtContainerThumbnailTitleBar::ClipMediaType_SD1);

				case CtClipInfo::ClipInfoMediaType_SD2:
					return m_pTitleBar->updateMediaType(CtContainerThumbnailTitleBar::ClipMediaType_SD2);

				default:
					break;
				}
			}
		}
	}
	return false;
}


void CtWindowClipInfoMation::setClipCnt(unsigned long cnt) {
	m_Clipcnt = cnt;
	if (cnt > 1) {
		m_pBtnUp->setInvalid(false);
		m_pBtnDown->setInvalid(false);
	}
	else {
		m_pBtnUp->setInvalid(true);
		m_pBtnDown->setInvalid(true);
	}
}

unsigned long CtWindowClipInfoMation::getClipCnt() {
	return m_Clipcnt;
}

bool CtWindowClipInfoMation::updateContents()
{
	WindowContentType event = m_wcEvent;
	m_wcEvent = WC_NONE;

	switch (event) {
	case WC_DRAW_THUMNAIL:
		updateThumbnailImage();
		return true;

	case WC_DRAW_INIT:
		initThumbnail();
		return true;

	case WC_SELECT_CLIPINFO:
		UpdateClipInfo();
		return true;

	case WC_NONE:
	default:
		CtDebugPrint(CtDbg, "%s %d ----------\n", __FUNCTION__, __LINE__);
		break;
	}

	return false;
}


//�T���l�C���摜�p�̃h���A�u��ID�̎擾
void CtWindowClipInfoMation::DeleteThumbnailDrawable(int index)
{
	CtDrawCache *CacheController = CtDrawCache::getInstance();
	int drawableID = GetThumbNailDrawableID(index);

	//�T���l�C���摜�L���b�V���̔j��
	if (NULL != CacheController->getCache(drawableID)) {
		CacheController->deleteCache(drawableID);
	}
}


//�T���l�C���摜�p�̃h���A�u��ID�̎擾
#define WidgetTHUMB_OFFSET (1000)
unsigned long CtWindowClipInfoMation::GetThumbNailDrawableID(int index)
{
	int ThumBaseID = 0x100000;
	return index + 1 + WidgetTHUMB_OFFSET + ThumBaseID;
}


//�T���l�C���摜�p�̃h���A�u���̎擾
GDI_HANDLER CtWindowClipInfoMation::GetImageDrawableHandle(int index)
{
	//�L���b�V��������o��
	CtDrawCache *CacheController = CtDrawCache::getInstance();
	unsigned long drawableID = GetThumbNailDrawableID(index);
	GDI_HANDLER hYuvDrawable = (GDI_HANDLER)CacheController->getCache(drawableID);

	//�L���b�V��������������V�K�ǉ�
	if (GDI_INVALID_ID == hYuvDrawable) {
		CtLabel *pTmp = new CtLabel(CtSize(214, 120));
		hYuvDrawable = CtDraw::getInstance()->convertDrawable(pTmp, Format_YUV420);

		CacheController->setCache(drawableID, (GDI_DRAWABLE_ID)hYuvDrawable);
		delete pTmp;
	}

	return hYuvDrawable;
}

// �L���b�V������Ă��邩�m�F
CtWindowClipInfoMation::READ_THUM_YUV CtWindowClipInfoMation::IsAlreadyReadYuv(int index)
{
	CtDrawCache *CacheController = CtDrawCache::getInstance();
	unsigned long drawableID = GetThumbNailDrawableID(index);
	GDI_HANDLER hYuvDrawable = (GDI_HANDLER)CacheController->getCache(drawableID);

	if (GDI_INVALID_ID != hYuvDrawable) {
		return READ_THUM_SET_FINISH;
	}

	return READ_THUM_NOT_SATRTED_YET;
}


bool CtWindowClipInfoMation::DrawRequestYuv(int clipNo)
{
	gdi_pbuffer_context *pContext;
	ContentsThumbStartDrawCallback pfunc;

	int index;

	if (NULL == m_pInitInfo) {
		return false;
	}

	if (clipNo <= 0) {
		return false;
	}

	index = clipNo - 1;

	//���ɓǂݍ��ݍς݂�������ǂݍ��܂Ȃ�
	if (READ_THUM_SET_FINISH == IsAlreadyReadYuv(index)) {
		return false;
	}

	pfunc = m_pInitInfo->getFuncRequestPicture();
	if (NULL == pfunc) {
		return false;
	}

	pContext = (gdi_pbuffer_context *)GetImageDrawableHandle(index);
	if (NULL == pContext) {
		return false;
	}


	ContentsThumbInfo ThumbInfo = {
		ContentsThumbResultType_OK,
		(unsigned long)clipNo,							//�N���b�vNo.
		{
			pContext->width,			//�摜�̕�
			pContext->height			//�摜�̍���
		},
		pContext->color_buffer0,		//Y�v���[���A�h���X
		pContext->color_buffer1			//C�v���[���A�h���X
	};
	(*pfunc)(ThumbInfo);

	return true;

}


//�h���A�u�����T���l�C���摜�ɃZ�b�g
void CtWindowClipInfoMation::setThumbNailImage(unsigned long ClipNo)
{
	if (ClipNo <= 0) {
		return;
	}

	int index = ClipNo - 1;

	if (NULL == m_pInitInfo) {
		return;
	}

	//�ǂݍ��񂾃N���b�v���C���f�b�N�X�l�ƈ�v���Ă�����h���A�u�����Z�b�g����
	if (ClipNo == m_CurrentClipNo) {
		//�w�肵��index�̃T���l�C���{�^���ɁA�ǂݍ���Drawable���Z�b�g����
		setDrawableYUV(index);
	}

	//�͈͊O�̃h���A�u���͏���
	for (unsigned long i = 0; i < m_Clipcnt; i++) {
		if (i != (m_CurrentClipNo - 1)) {
			DeleteThumbnailDrawable(i);
		}
	}
}

//�h���A�u�����T���l�C���摜�ɃZ�b�g
void CtWindowClipInfoMation::setDrawableYUV(int index)
{
	if (NULL == m_pLabeIcon[3]) {
		return;
	}

	CtDrawCache *CacheController = CtDrawCache::getInstance();
	int drawableID = GetThumbNailDrawableID(index);

	GDI_HANDLER hYuvDrawable = (GDI_HANDLER)CacheController->getCache(drawableID);

	if (GDI_INVALID_ID != hYuvDrawable) {
		m_pLabeIcon[3]->setDrawable(hYuvDrawable);
	}
}

void CtWindowClipInfoMation::updatePicture()
{
	/* �摜��waiting�ɒu�������� */
	if (m_pLabeIcon[3] != NULL) {
		CtDebugPrint(CtDbg, "%s %d ----------\n", __FUNCTION__, __LINE__);
		CtFontSet fSet1 = CtFontSet(FontTypeNormal_alignCenter, CtColor(255, 255, 255, 0xff));
		fSet1.setSize(30);
		m_pLabeIcon[3]->setFontSet(fSet1);
		m_pLabeIcon[3]->setText("waiting...");
	}
}


void CtWindowClipInfoMation::UpdateClipInfo()
{
	if (NULL == m_pSelectClipInfo) return;
	SetReadClipInfoEvent(CtWindowClipInfoMation::E_READ_CLIP_FINISH);   //�N���b�v�Ǐo�����ʒm
}

bool CtWindowClipInfoMation::handleKeyEvent(const CtEventKey& Key) {
	bool bRet = false;

	unsigned long index = 0;
	if (CtEventKey::Press != Key.getKeyAction()
		&& CtEventKey::RepeatPress != Key.getKeyAction()
		&& CtEventKey::FastPress != Key.getKeyAction()) {
		return false;
	}

	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_MmrPlus:
	case CtEventKey::KeyCode_DialPressUp:
	case CtEventKey::KeyCode_Up:
		if (m_pBtnDown->isInvalid() == false) {
			index = getCurrentNo();
			if (index == 1) {
				index = getClipCnt();
			}
			else {
				index--;
			}
			setCurrentClipNo(index);
			updateThumbnail(getCurrentNo() - 1);
			updatePicture();
		}
		return true;

	case CtEventKey::KeyCode_DialPressDown:
	case CtEventKey::KeyCode_MmrMinus:
	case CtEventKey::KeyCode_Down:
		if (m_pBtnUp->isInvalid() == false) {
			index = getCurrentNo();
			index++;
			if (index > getClipCnt()) {
				index = 1;
			}
			setCurrentClipNo(index);
			updateThumbnail(getCurrentNo() - 1);
			updatePicture();
		}
		return true;

	default:
		break;
	}

	return bRet;
}

void CtWindowClipInfoMation::updateThumbnailImage()
{
	if (NULL == m_pDrawInfo) return;
	SetReadClipInfoEvent(CtWindowClipInfoMation::E_READ_THUM_FINISH);   //�N���b�v�Ǐo�����ʒm
}

void CtWindowClipInfoMation::setCurrentClipNo(unsigned long clipNo)
{
	m_CurrentClipNo = clipNo;

	//�N���b�v���ǂݏo���v�����M
	SetReadClipInfoEvent(CtWindowClipInfoMation::E_READ_CLIP_REQ);
}

unsigned long CtWindowClipInfoMation::getCurrentNo()
{
	return m_CurrentClipNo;
}

int CtWindowClipInfoMation::getDetailPixelType(int nPixelTypeIndex, int nFrequencyIndex) {
	switch (nPixelTypeIndex)
	{
	case CtClipInfo::ClipInfoPixelType_720:
		if (nFrequencyIndex == CtClipInfo::ClipInfoFrequencyType_5994i) {
			return nPixelTypeIndex - 1;
		}
		else {
			return nPixelTypeIndex;
		}
		break;
	case CtClipInfo::ClipInfoPixelType_4096:
	case CtClipInfo::ClipInfoPixelType_3840:
	case CtClipInfo::ClipInfoPixelType_2048:
	case CtClipInfo::ClipInfoPixelType_1920:
	case CtClipInfo::ClipInfoPixelType_1280:
		return nPixelTypeIndex;
		break;
	case CtClipInfo::ClipInfoPixelType_None:
	default:
		return CtClipInfo::ClipInfoPixelType_4096;
		break;
	}
}

/////////////////////////////////////////////////////
// �N���b�v���ǂݍ��ݗp��ԑJ��
void CtWindowClipInfoMation::SetReadClipInfoEvent(READ_CLIP_EVENT _event)
{
	READ_CLIP_EVENT event = _event;
	do {
		switch (m_read_clip_state) {
		case S_READ_CLIP_IDLE:
			event = State_ReadClipIdle(event);
			break;
		case S_READ_CLIP_WAIT:
			event = State_ReadClipWait(event);
			break;
		case S_READ_THUM_IDLE:
			event = State_ReadThumIdle(event);
			break;
		case S_READ_THUM_WAIT:
			event = State_ReadThumWait(event);
			break;
		default:
			return;
		}
	} while (E_READ_CLIP_END != event);
}

CtWindowClipInfoMation::READ_CLIP_EVENT CtWindowClipInfoMation::State_ReadClipIdle(READ_CLIP_EVENT event)
{
	switch (event) {
	case E_READ_CLIP_REQ:
	{
		ContentsThumbReqClipInfoCallback func = m_pInitInfo->getFuncRequestClipInfo();
		if (NULL == func) return E_READ_CLIP_END;
		int index = getCurrentNo() - 1;
		if (index < 0) {
			return E_READ_CLIP_END;
		}
		if (m_list.size() <= index) {
			return E_READ_CLIP_END;
		}
		(*func)(getCurrentNo(), 1);
		m_ReadClipNo = getCurrentNo();
		m_read_clip_state = S_READ_CLIP_WAIT;
	}
	return E_READ_CLIP_END;
	case E_READ_CLIP_FINISH:
	default:
		return E_READ_CLIP_END;
	}
}

CtWindowClipInfoMation::READ_CLIP_EVENT CtWindowClipInfoMation::State_ReadClipWait(READ_CLIP_EVENT event)
{
	switch (event) {
	case E_READ_CLIP_FINISH:
		if (NULL == m_pSelectClipInfo) {
			m_read_clip_state = S_READ_CLIP_IDLE;
			return E_READ_CLIP_END;
		}

		//�N���b�v���𔽉f
		{
			CtWindowContentsClipInfo::ClipInfoList& list = m_pSelectClipInfo->getClipInfoList();
			int topClipNo = m_pSelectClipInfo->getTopIndex();
			int topIndex = topClipNo - 1;

			if (m_list[topIndex] == NULL) {
				m_list[topIndex] = new CtClipInfo(*list[0]);
			}
			updateThumbnail(getCurrentNo() - 1);
		}

		m_read_clip_state = S_READ_THUM_IDLE;
		return E_READ_THUM_REQ;

	case E_READ_CLIP_REQ:		//�ǂݍ��ݗv�����̗v���͖���
	default:
		return E_READ_CLIP_END;
	}
}

//�T���l�C���ǂݍ��ݗv���҂����
CtWindowClipInfoMation::READ_CLIP_EVENT CtWindowClipInfoMation::State_ReadThumIdle(READ_CLIP_EVENT event)
{
	switch (event) {
	case E_READ_THUM_REQ:
		if (m_ReadClipNo != getCurrentNo()) {
			//�J�����g�̃N���b�v�ԍ����X�V����Ă�����N���b�v�ԍ�����ǂݒ���
			m_read_clip_state = S_READ_CLIP_IDLE;		//�ēx�N���b�v���ǂݍ��݂�
			return E_READ_CLIP_REQ;
		}

		if (DrawRequestYuv(m_ReadClipNo)) {				//�T���l�C���ǂݍ��ݗv�����M
			m_read_clip_state = S_READ_THUM_WAIT;		//�ǂݍ��ݗv���𑗐M������T���l�C���̓ǂݍ��ݑ҂���Ԃ�
			return E_READ_CLIP_END;
		}
		else {
			if (READ_THUM_SET_FINISH == IsAlreadyReadYuv(m_ReadClipNo - 1)) {
				setThumbNailImage(m_ReadClipNo);
			}
			m_read_clip_state = S_READ_CLIP_IDLE;		//�N���b�v���ǂݍ��ݏ�Ԃ�
			return E_READ_CLIP_END;
		}
		break;

	default:
		return E_READ_CLIP_END;
	}
}

//�T���l�C���ǂݍ��݊����҂����
CtWindowClipInfoMation::READ_CLIP_EVENT CtWindowClipInfoMation::State_ReadThumWait(READ_CLIP_EVENT event)
{
	switch (event) {
	case E_READ_THUM_FINISH:
	{
		if (NULL == m_pDrawInfo) return E_READ_CLIP_END;
		setThumbNailImage(m_pDrawInfo->getDrawThumbInfo().ClipNum);		//�ǂݍ��񂾃T���l�C���摜���{�^���ɔ��f
		m_read_clip_state = S_READ_CLIP_IDLE;							//�N���b�v���ǂݍ��ݏ�Ԃ�
		if (m_ReadClipNo != getCurrentNo()) {
			return E_READ_CLIP_REQ;										//���̂܂܎��̃X�e�[�g���p��
		}
		return E_READ_CLIP_END;
	}

	default:
		return E_READ_CLIP_END;
	}
}
