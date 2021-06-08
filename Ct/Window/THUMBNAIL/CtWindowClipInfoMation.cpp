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
		STR_ID_NO_10603,    /* 10603: 「START TC」: 撮影開始時のタイムコード */
		STR_ID_NO_10604,    /* 10604: 「START UB」: 撮影開始時のユーザーズビット */
		STR_ID_NO_10605,    /* 10605: 「DATE」: 撮影日 */
		STR_ID_NO_10606,    /* 10606: 「TIME」: 撮影時刻 */
		STR_ID_NO_10608,    /* 10608: 「DURATION」: 記録時間 */
		STR_ID_NO_10609,    /* 10609: 「PIXEL/FREQ」: 記録解像度/記録周波数 */
		STR_ID_NO_10610,    /* 10610: 「CODEC」: 記録コーデック */
		STR_ID_NO_10368,	/* 10368: 「FRAME RATE」*/
		STR_ID_NO_10255,	/* 10255: 「GAMMA」*/
};

static const GDI_STRING_ID  InfoDetailCodec[] = {
	STR_ID_NO_10622,    /* 10622: 「AVCHD PS」: AVCHD 4:2:0 8bit LongGOP 25Mbps */
	STR_ID_NO_10623,    /* 10623: 「AVCHD PH」: AVCHD 4:2:0 8bit LongGOP 21Mbps */
	STR_ID_NO_10624,    /* 10624: 「AVCHD HA」: AVCHD 4:2:0 8bit LongGOP 17Mbps */
	STR_ID_NO_10625,    /* 10625: 「AVCHD PM」: AVCHD 4:2:0 8bit LongGOP 8Mbps */
	STR_ID_NO_11428,	/* 11428: 「AVCHD SA」: AVCHD 4:2:0 8bit LongGOP 8Mbps */
	STR_ID_NO_10611,    /* 10611: 「MOV 420LongG 150M」: MOV 4:2:0 8bit LongGOP 150Mbps */
	STR_ID_NO_10612,    /* 10612: 「MOV 420LongG 100M」: MOV 4:2:0 8bit LongGOP 100Mbps */
	STR_ID_NO_10613,    /* 10613: 「MOV 420LongG 50M」: MOV 4:2:0 8bit LongGOP 50Mbps */
	STR_ID_NO_10614,    /* 10614: 「MOV 420LongG 12M」: MOV 4:2:0 8bit LongGOP 12Mbps */
	STR_ID_NO_10615,    /* 10615: 「MOV 420LongG 6M」: MOV 4:2:0 8bit LongGOP 6Mbps */
	STR_ID_NO_10616,    /* 10616: 「MOV 422LongG 150M」: MOV 4:2:2 10bit LongGOP 150Mbps */
	STR_ID_NO_10617,    /* 10617: 「MOV 422LongG 100M」: MOV 4:2:2 10bit LongGOP 100Mbps */
	STR_ID_NO_10618,    /* 10618: 「MOV 422LongG 50M」: MOV 4:2:2 10bit LongGOP 50Mbps */
	STR_ID_NO_10619,    /*  */
	STR_ID_NO_10620,    /*  */
	STR_ID_NO_10621,    /*  */
	STR_ID_NO_11426,	/* 11426: 「MOV HEVC LongG 200M」: MOV HEVC LongG 200M(MAIN CODEC) */
	STR_ID_NO_11427,	/* 11427: 「MOV HEVC LongG 150M」: MOV HEVC LongG 150M(MAIN CODEC) */
	STR_ID_NO_10610,	/* Dummy: 「MOV HEVC LongG 100M」: */
	STR_ID_NO_10610,	/* Dummy: 「AVC ULTRA 422Intra」: */
	STR_ID_NO_10610,	/* Dummy: 「AVC ULTRA LongG50」: */
	STR_ID_NO_10610,	/* Dummy: 「AVC ULTRA LongG25」: */
	STR_ID_NO_10610,	/* Dummy: 「AVC ULTRA LongG12」: */
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
	STR_ID_NO_10026,    /* 10026: 「59.94p」: 59.94p */
	STR_ID_NO_10028,    /* 10028: 「59.94i」: 59.94i */
	STR_ID_NO_10025,    /* 10025: 「50.00p」: 50.00p */
	STR_ID_NO_10027,    /* 10027: 「50.00i」: 50.00i */
	STR_ID_NO_10024,    /* 10024: 「29.97p」: 29.97p */
	STR_ID_NO_10023,    /* 10023: 「25.00p」: 25.00p */
	STR_ID_NO_10022,    /* 10022: 「24.00p」: 24.00p */
	STR_ID_NO_10021,    /* 10021: 「23.98p」: 23.98p */
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
	// タイトル
	m_pTitleBar = new CtContainerThumbnailTitleBar(getWindowID());

	// Main
	CtHLayout* pMain = new CtHLayout();
	pMain->addStretch(14);
	pMain->addWidget(createLayoutLeftButton(), 78);
	pMain->addStretch(64);
	pMain->addWidget(createLayoutOneItemIcon(), 218);
	pMain->addStretch(56);
	pMain->addWidget(createLayoutRightText(), 530);

	// 全体
	CtVLayout* pAll = new CtVLayout();
	pAll->addContainer(m_pTitleBar, 42);
	pAll->addWidget(new CtLabel(CtColor(134, 134, 134, 0xff)), 2);
	pAll->addWidget(pMain, 596);

	CtWindow* pWin = new CtWindow(CtColor::Black);
	pWin->addWidget(pAll);

	return pWin;
}

CtLayout* CtWindowClipInfoMation::createLayoutLeftButton() {

	// 下部の左三つボタンを追加する
	m_pBtnUp = new CtButton(CtSize(78, 66), IC_MENU_UP);
	m_pBtnUp->setWidgetID(WidgetIDUP);
	m_pBtnUp->setInvalid(true);
	m_pBtnUp->setFocusable(false);  // KeyCode_MmrMinus、KeyCode_MmrPlus時、フォーカス移ので、ここで移動できないに設定する
	m_pBtnDown = new CtButton(CtSize(78, 66), IC_MENU_DOWN);
	m_pBtnDown->setWidgetID(WidgetIDDW);
	m_pBtnDown->setInvalid(true);
	m_pBtnDown->setFocusable(false);// KeyCode_MmrMinus、KeyCode_MmrPlus時、フォーカス移ので、ここで移動できないに設定する
	m_pBtnReturn = new CtButton(CtSize(78, 66), IC_MENU_RETURN);
	m_pBtnReturn->setWidgetID(WidgetIDRETURN);
	m_pBtnReturn->setFocusable(false);// KeyCode_MmrMinus、KeyCode_MmrPlus時、フォーカス移ので、ここで移動できないに設定する

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

	// アイコン生成
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

	// 一段目
	CtHLayout *pLayout1 = new CtHLayout(CtColor(30, 30, 30, 0xff));
	pLayout1->addWidget(m_pLabeIcon[0]);

	// 二段目
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

	// 三段目
	CtHLayout *pLayout3 = new CtHLayout(CtColor::Trans);
	pLayout3->addWidget(m_pLabeIcon[3]);

	// 四段目
	CtHLayout *pLayout4 = new CtHLayout(CtColor(30, 30, 30, 0xff));
	pLayout4->addWidget(m_pLabeIcon[4]);

	// レイアウト構築
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
			/* PIXEL/FREQのみ特殊 */
			/* m_pLabeIconの[10]のみ未使用になる */
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

	/* Releaseでのみ処理 */
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
		//(2017.07.10) 画面CLOSEはAPLに任せる
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

	//リストを初期化
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

	/* 部品生成 */
	updateClipNo(index + 1);									// クリップ番号
	updateClipName("");											// クリップ名
	updateNotPlayIcon(false);									// 再生不可クリップ
	updateProtectIcon(false);									// クリッププロテクト
	updateP2StartIcon(CtClipInfo::ClipInfoP2StartType_Normal);	// P2不明/不良クリップ
	updateReConnectIcon(false);									// P2不完全クリップ

	// ①スタートTC
	m_pLabeIcon[5]->setText("--:--:--:--");
	m_pLabeIcon[5]->setFontSet(fSet);

	// ②スタートUB
	m_pLabeIcon[6]->setText("--------");
	m_pLabeIcon[6]->setFontSet(fSet);

	// ③撮影日
	m_pLabeIcon[7]->setText("");
	m_pLabeIcon[7]->setFontSet(fSet);

	// ④撮影時刻
	m_pLabeIcon[8]->setText("");
	m_pLabeIcon[8]->setFontSet(fSet);


	// ⑤記録時間
	m_pLabeIcon[9]->setText("--:--:--:--");
	m_pLabeIcon[9]->setFontSet(fSet);

	// ⑥記録解像度＆周波数
	m_pPixel->setVisible(false);
	m_pSeparate->setVisible(false);
	m_pFreq->setVisible(false);

	// ⑦記録コーデック
	m_pLabeIcon[11]->setVisible(false);

	// ⑧記録フレームレート
	m_pLabeIcon[12]->setText("");
	m_pLabeIcon[12]->setVisible(false);

	// ⑨ガンマ
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

	/*NULLチェック*/
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

	/* 部品生成 */
	updateClipNo(ClipInfoItem.ClipNumber);				// クリップ番号
	updateClipName(ClipInfoItem.ClipName);				// クリップ名
	updateNotPlayIcon(ClipInfoItem.DifferentFreqFlag);	// 再生不可クリップ
	updateProtectIcon(ClipInfoItem.LockFlag);			// クリッププロテクト
	updateP2StartIcon(ClipInfoItem.P2Start);			// P2不明/不良クリップ
	updateReConnectIcon(ClipInfoItem.ReConnectFlag);	// P2不完全クリップ


	// ①スタートTC
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
	// ②スタートUB
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

	// ③撮影日
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

	// ④撮影時刻
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

	// ⑤記録時間
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

	// ⑥記録解像度＆周波数
	// Pixel or Freq が Noneの場合全て表示しない
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

	// ⑦記録コーデック
	// CodecがNoneの時には何も表示しない
	if (ClipInfoItem.CodecType == CtClipInfo::ClipInfoCodecType_None) {
		m_pLabeIcon[11]->setVisible(false);
	}
	else {
		m_pLabeIcon[11]->setStringID(InfoDetailCodec[(ClipInfoItem.CodecType != 0) ? (ClipInfoItem.CodecType - 1) : 0]);
		m_pLabeIcon[11]->setVisible(true);
	}

	// ⑧記録フレームレート
	if (ClipInfoItem.FPSvalue.ValidFlag == false) {
		m_pLabeIcon[12]->setVisible(false);
	}
	else {
		memset(str, NULL, sizeof(str));
		sprintf(str, "%.0ffps", ClipInfoItem.FPSvalue.fps);
		m_pLabeIcon[12]->setText(str);
		m_pLabeIcon[12]->setVisible(true);
	}

	// ⑨ガンマ
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
	/* サムネイル選択状態 */
	if (NULL != m_pInitInfo) {  //初期化済みだったら更新
		unsigned long list_index = getCurrentNo() - 1; /* (注意)CurrentIndexは[1]開始 */
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


//サムネイル画像用のドロアブルIDの取得
void CtWindowClipInfoMation::DeleteThumbnailDrawable(int index)
{
	CtDrawCache *CacheController = CtDrawCache::getInstance();
	int drawableID = GetThumbNailDrawableID(index);

	//サムネイル画像キャッシュの破棄
	if (NULL != CacheController->getCache(drawableID)) {
		CacheController->deleteCache(drawableID);
	}
}


//サムネイル画像用のドロアブルIDの取得
#define WidgetTHUMB_OFFSET (1000)
unsigned long CtWindowClipInfoMation::GetThumbNailDrawableID(int index)
{
	int ThumBaseID = 0x100000;
	return index + 1 + WidgetTHUMB_OFFSET + ThumBaseID;
}


//サムネイル画像用のドロアブルの取得
GDI_HANDLER CtWindowClipInfoMation::GetImageDrawableHandle(int index)
{
	//キャッシュから取り出し
	CtDrawCache *CacheController = CtDrawCache::getInstance();
	unsigned long drawableID = GetThumbNailDrawableID(index);
	GDI_HANDLER hYuvDrawable = (GDI_HANDLER)CacheController->getCache(drawableID);

	//キャッシュが無かったら新規追加
	if (GDI_INVALID_ID == hYuvDrawable) {
		CtLabel *pTmp = new CtLabel(CtSize(214, 120));
		hYuvDrawable = CtDraw::getInstance()->convertDrawable(pTmp, Format_YUV420);

		CacheController->setCache(drawableID, (GDI_DRAWABLE_ID)hYuvDrawable);
		delete pTmp;
	}

	return hYuvDrawable;
}

// キャッシュされているか確認
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

	//既に読み込み済みだったら読み込まない
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
		(unsigned long)clipNo,							//クリップNo.
		{
			pContext->width,			//画像の幅
			pContext->height			//画像の高さ
		},
		pContext->color_buffer0,		//Yプレーンアドレス
		pContext->color_buffer1			//Cプレーンアドレス
	};
	(*pfunc)(ThumbInfo);

	return true;

}


//ドロアブルをサムネイル画像にセット
void CtWindowClipInfoMation::setThumbNailImage(unsigned long ClipNo)
{
	if (ClipNo <= 0) {
		return;
	}

	int index = ClipNo - 1;

	if (NULL == m_pInitInfo) {
		return;
	}

	//読み込んだクリップがインデックス値と一致していたらドロアブルをセットする
	if (ClipNo == m_CurrentClipNo) {
		//指定したindexのサムネイルボタンに、読み込んだDrawableをセットする
		setDrawableYUV(index);
	}

	//範囲外のドロアブルは消す
	for (unsigned long i = 0; i < m_Clipcnt; i++) {
		if (i != (m_CurrentClipNo - 1)) {
			DeleteThumbnailDrawable(i);
		}
	}
}

//ドロアブルをサムネイル画像にセット
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
	/* 画像をwaitingに置き換える */
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
	SetReadClipInfoEvent(CtWindowClipInfoMation::E_READ_CLIP_FINISH);   //クリップ読出完了通知
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
	SetReadClipInfoEvent(CtWindowClipInfoMation::E_READ_THUM_FINISH);   //クリップ読出完了通知
}

void CtWindowClipInfoMation::setCurrentClipNo(unsigned long clipNo)
{
	m_CurrentClipNo = clipNo;

	//クリップ情報読み出し要求送信
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
// クリップ情報読み込み用状態遷移
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

		//クリップ情報を反映
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

	case E_READ_CLIP_REQ:		//読み込み要求中の要求は無視
	default:
		return E_READ_CLIP_END;
	}
}

//サムネイル読み込み要求待ち状態
CtWindowClipInfoMation::READ_CLIP_EVENT CtWindowClipInfoMation::State_ReadThumIdle(READ_CLIP_EVENT event)
{
	switch (event) {
	case E_READ_THUM_REQ:
		if (m_ReadClipNo != getCurrentNo()) {
			//カレントのクリップ番号が更新されていたらクリップ番号から読み直し
			m_read_clip_state = S_READ_CLIP_IDLE;		//再度クリップ情報読み込みへ
			return E_READ_CLIP_REQ;
		}

		if (DrawRequestYuv(m_ReadClipNo)) {				//サムネイル読み込み要求送信
			m_read_clip_state = S_READ_THUM_WAIT;		//読み込み要求を送信したらサムネイルの読み込み待ち状態へ
			return E_READ_CLIP_END;
		}
		else {
			if (READ_THUM_SET_FINISH == IsAlreadyReadYuv(m_ReadClipNo - 1)) {
				setThumbNailImage(m_ReadClipNo);
			}
			m_read_clip_state = S_READ_CLIP_IDLE;		//クリップ情報読み込み状態へ
			return E_READ_CLIP_END;
		}
		break;

	default:
		return E_READ_CLIP_END;
	}
}

//サムネイル読み込み完了待ち状態
CtWindowClipInfoMation::READ_CLIP_EVENT CtWindowClipInfoMation::State_ReadThumWait(READ_CLIP_EVENT event)
{
	switch (event) {
	case E_READ_THUM_FINISH:
	{
		if (NULL == m_pDrawInfo) return E_READ_CLIP_END;
		setThumbNailImage(m_pDrawInfo->getDrawThumbInfo().ClipNum);		//読み込んだサムネイル画像をボタンに反映
		m_read_clip_state = S_READ_CLIP_IDLE;							//クリップ情報読み込み状態へ
		if (m_ReadClipNo != getCurrentNo()) {
			return E_READ_CLIP_REQ;										//そのまま次のステートを継続
		}
		return E_READ_CLIP_END;
	}

	default:
		return E_READ_CLIP_END;
	}
}
