/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:            CtContainerThumbnailTitleBar
*/


#include "CtContainerThumbnailTitleBar.h"

#include "CtContainerWifi.h"
#include "CtContainerBattery.h"


CtContainerThumbnailTitleBar::CtContainerThumbnailTitleBar(CtWindowID _id) :
	m_WindowID(_id),
	m_pTitle(NULL),
	m_pWaiting(NULL),
	m_pOpratorSel(NULL),
	m_pP2(NULL),
	m_pMov(NULL),
	m_pAvchd(NULL),
	m_pNG(NULL),
	m_pSd1(NULL),
	m_pSd2(NULL),
	m_pWifi(NULL),
	m_pBatt(NULL),
	m_MediaType(ClipMediaType_None)
{
	setClassType(CtClassType_Container);
}

bool CtContainerThumbnailTitleBar::destroyContainer()
{
	if (m_pWaiting != NULL) {
		m_pWaiting->stopFlash();
	}
	return true;
}

CtLayout* CtContainerThumbnailTitleBar::createContainer()
{
	/* Label作成 */
	createLabels();

	/* レイアウト構築 */
	CtLayout* pLayout = createLayout();

	/* 更新 */
	updateUpper();

	return pLayout;
}

void CtContainerThumbnailTitleBar::createLabels()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	/* Title or SlotSel  */
	m_pTitle = new CtStackLabel();
	m_pTitle->addLabel(new CtLabel(STR_ID_NO_10004, fSet), CtMargin(), AlignLeft);	/* ALL SLOT       */
	m_pTitle->addLabel(new CtLabel(STR_ID_NO_10005, fSet), CtMargin(), AlignLeft);	/* SLOT 1         */
	m_pTitle->addLabel(new CtLabel(STR_ID_NO_10006, fSet), CtMargin(), AlignLeft);	/* SLOT 2         */
	m_pTitle->addLabel(new CtLabel(STR_ID_NO_10918, fSet), CtMargin(), AlignLeft);	/* SLOT1->SLOT2   */
	m_pTitle->addLabel(new CtLabel(STR_ID_NO_10919, fSet), CtMargin(), AlignLeft);	/* SLOT2->SLOT1   */
	m_pTitle->addLabel(new CtLabel(STR_ID_NO_11002, fSet), CtMargin(), AlignLeft);	/* SAME FORMAT    */
	m_pTitle->addLabel(new CtLabel("MARKED", fSet), CtMargin(), AlignLeft);			/* MARKED         */
	m_pTitle->addLabel(new CtLabel("TEXT MEMO", fSet), CtMargin(), AlignLeft);		/* TEXT MEMO      */
	m_pTitle->addLabel(new CtLabel(STR_ID_NO_10626, fSet), CtMargin(), AlignLeft);	/* CLIPINFOMATION */

	/* Waiting Status */
	const CtStyle::CtProperty& prop = CtStyle::getProperty();
	m_pWaiting = new CtLayout();
	m_pWaiting->addWidget(new CtLabel(CtRoundRect(prop.Button.ArcWidth, prop.Button.ArcWidth, CtColor::Black, prop.Button.StrokeWidth, CtColor::White)));
	m_pWaiting->addWidget(new CtLabel("waiting..", fSet), CtMargin(0, 0, 5, 5), AlignCenter);

	/* 機能名称 */
	m_pOpratorSel = new CtStackLabel();
	m_pOpratorSel->addLabel(new CtLabel("", fSet), CtMargin(), AlignLeft);				/* 表示無し */
	m_pOpratorSel->addLabel(new CtLabel(STR_ID_NO_10012, fSet), CtMargin(), AlignLeft);	/* PROTECT  */
	m_pOpratorSel->addLabel(new CtLabel(STR_ID_NO_10014, fSet), CtMargin(), AlignLeft);	/* DELETE   */
	m_pOpratorSel->addLabel(new CtLabel(STR_ID_NO_10016, fSet), CtMargin(), AlignLeft);	/* COPY     */

	/* P2 */
	m_pP2 = new CtStackLabel();
	m_pP2->addLabel(new CtLabel(IC_THUMBNAIL_MODE_P2_NORMAL));			/* P2通常   */
	m_pP2->addLabel(new CtLabel(IC_THUMBNAIL_MODE_P2_SELECTED));		/* P2選択   */
	m_pP2->addLabel(new CtLabel(""));									/* 表示無し */

	/* MOV */
	m_pMov = new CtStackLabel();
	m_pMov->addLabel(new CtLabel(IC_THUMBNAIL_MODE_MOV_NORMAL));        /* MOV通常  */
	m_pMov->addLabel(new CtLabel(IC_THUMBNAIL_MODE_MOV_SELECTED));      /* MOV選択  */
	m_pMov->addLabel(new CtLabel(""));                                  /* 表示無し */

	/* AVCHD */
	m_pAvchd = new CtStackLabel();
	m_pAvchd->addLabel(new CtLabel(IC_THUMBNAIL_MODE_AVCHD_NORMAL));    /* AVCHD通常 */
	m_pAvchd->addLabel(new CtLabel(IC_THUMBNAIL_MODE_AVCHD_SELECTED));  /* AVCHD選択 */
	m_pAvchd->addLabel(new CtLabel(""));                                /* 表示無し  */

	/* NG */
	m_pNG = new CtStackLabel();
	m_pNG->addLabel(new CtLabel(""));									/* 表示なし     */
	m_pNG->addLabel(new CtLabel(IC_THUMBNAIL_P2_REPAIRABLE));			/* P2修復可能   */
	m_pNG->addLabel(new CtLabel(IC_THUMBNAIL_P2_UNREPAIRABLE));			/* P2修復不可能 */

	/* SD1 */
	m_pSd1 = new CtStackLabel();
	m_pSd1->addLabel(new CtLabel(IC_THUMBNAIL_MEDIA_SD_1_NONE));        /* SD1無し */
	m_pSd1->addLabel(new CtLabel(IC_THUMBNAIL_MEDIA_SD_1_NORMAL));      /* SD1有り */
	m_pSd1->addLabel(new CtLabel(IC_THUMBNAIL_MEDIA_SD_1_SELECTED));    /* SD1表示 */

	/* SD2 */
	m_pSd2 = new CtStackLabel();
	m_pSd2->addLabel(new CtLabel(IC_THUMBNAIL_MEDIA_SD_2_NONE));        /* SD2無し */
	m_pSd2->addLabel(new CtLabel(IC_THUMBNAIL_MEDIA_SD_2_NORMAL));      /* SD2有り */
	m_pSd2->addLabel(new CtLabel(IC_THUMBNAIL_MEDIA_SD_2_SELECTED));    /* SD2表示 */

	/* Wifi */
	m_pWifi = new CtContainerWifi();

	/* バッテリー */
	m_pBatt = new CtContainerBattery();
}

CtLayout* CtContainerThumbnailTitleBar::createLayout()
{
	/* Layout構築 960                                                                                                               */
	/*  |--|---232------------------|-80------|---150-------------|-80----|-|-80----|-|-80----|--|30|-|24|-|24|--|-44-|--|-57-|--|  */
	/*  |14|                        |         |                   |       |5|       |5|       |10|  |5|  |5|  |10|    |10|    |15|  */
	/*  |  | Title or SlotSel       | Waiting | 機能名称          | P2    | | MOV   | | AVCHD |  |NG| |SD| |SD|  |Wifi|  |Batt|  |  */
	/*  |__|________________________|_________|___________________|_______|_|_______|_|_______|__|__|_|__|_|__|__|____|__|____|__|  */

	CtHLayout *pLayout = new CtHLayout();
	pLayout->addStretch(14);
	pLayout->addWidget(m_pTitle, 232);							/* Title or SlotSel */
	pLayout->addWidget(m_pWaiting, 80);							/* Waiting */
	pLayout->addWidget(m_pOpratorSel, 150);						/* 機能名称 */

	pLayout->addWidget(m_pP2, CtMargin(5, 5, 0, 0), 80);		/* P2 */
	pLayout->addStretch(5);
	pLayout->addWidget(m_pMov, CtMargin(5, 5, 0, 0), 80);		/* MOV */
	pLayout->addStretch(5);
	pLayout->addWidget(m_pAvchd, CtMargin(5, 5, 0, 0), 80);		/* AVCHD */
	pLayout->addStretch(10);
	
	pLayout->addWidget(m_pNG, CtMargin(5, 5, 0, 0), 30);		/* NG */
	pLayout->addStretch(5);
	pLayout->addWidget(m_pSd1, CtMargin(5, 5, 0, 0), 24);		/* SD1 */
	pLayout->addStretch(5);
	pLayout->addWidget(m_pSd2, CtMargin(5, 5, 0, 0), 24);		/* SD2 */
	pLayout->addStretch(10);
	pLayout->addContainer(m_pWifi, CtMargin(1, 5, 0, 0), 44);	/* WIFI */
	pLayout->addStretch(10);
	pLayout->addContainer(m_pBatt, CtMargin(7, 7, 0, 0), 57);	/* バッテリー */
	pLayout->addStretch(15);

	return pLayout;
}

void CtContainerThumbnailTitleBar::updateUpper()
{
	updateTitle();
	updateWaiting();
	updateOpratorSel();
	updateP2();
	updateMov();
	updateAvchd();
	updateP2Start();
	updateSd();
}

bool CtContainerThumbnailTitleBar::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id){
	case AplParamPlaySlot:
	case AplParamCopyDirection:
		return updateTitle();

	case AplParamPlayWaitingStatus:
		return updateWaiting();

	case AplParamPlayAvchdIcon:
		return updateAvchd();

	case AplParamPlayMovIcon:
		return updateMov();

	case AplParamPlayP2Icon:
		return updateP2();

	case AplParamPlayP2StartIcon:
		return updateP2Start();

	case AplParamSlot1InOutStatus:
	case AplParamSlot2InOutStatus:
		return updateSd();

	default:
		break;
	}
	return false;
}

bool CtContainerThumbnailTitleBar::updateTitle()
{
	if (m_pTitle == NULL) return false;

	switch (m_WindowID) {
	case Window_ThumbNailClip:
		return m_pTitle->index(8);

	case Window_ThumbNail_Copy:
		switch (APL_PARAM_GET_DATA(AplParamCopyDirection)){
		case APL_SYS_PARAM_COPY_DIRECTION_SLOT1_SLOT2:
			return m_pTitle->index(3);

		case APL_SYS_PARAM_COPY_DIRECTION_SLOT2_SLOT1:
			return m_pTitle->index(4);

		default:
			break;
		}
		break;
	default:
		switch (APL_PARAM_GET_DATA(AplParamPlaySlot)) {
		case APL_SYS_PARAM_PLAY_SLOT_ALL:
			return m_pTitle->index(0);

		case APL_SYS_PARAM_PLAY_SLOT_SLOT1:
			return m_pTitle->index(1);

		case APL_SYS_PARAM_PLAY_SLOT_SLOT2:
			return m_pTitle->index(2);

		case APL_SYS_PARAM_PLAY_SLOT_SAME_FORMAT:
			return m_pTitle->index(5);

		case APL_SYS_PARAM_PLAY_SLOT_MARKED:
			return m_pTitle->index(6);

		case APL_SYS_PARAM_PLAY_SLOT_TEXT_MEMO:
			return m_pTitle->index(7);

		default:
			break;
		}
		break;
	}
	return false;
}

bool CtContainerThumbnailTitleBar::updateWaiting()
{
	if (m_pWaiting == NULL) return false;

	if (APL_PARAM_GET_DATA(AplParamPlayWaitingStatus) == APL_SYS_PARAM_SWITCH_ON) {
		m_pWaiting->startFlash(CtEventFlash::Freq_1Hz);
		return m_pWaiting->setVisible(true);
	}
	else {
		m_pWaiting->stopFlash();
		return m_pWaiting->setVisible(false);
	}
	return false;
}

bool CtContainerThumbnailTitleBar::updateOpratorSel()
{
	if (m_pOpratorSel == NULL) return false;

	switch (m_WindowID) {
	case Window_ThumbNail:
		return m_pOpratorSel->index(0);

	case Window_ThumbNail_Protect:
		return m_pOpratorSel->index(1);

	case Window_ThumbNail_Delete:
		return m_pOpratorSel->index(2);

	case Window_ThumbNail_Copy:
		return m_pOpratorSel->index(3);

	default:
		break;
	}
	return false;
}

bool CtContainerThumbnailTitleBar::updateP2Start()
{
	if (m_pNG == NULL) return false;

	switch (APL_PARAM_GET_DATA(AplParamPlayP2StartIcon)) {
	case APL_SYS_PARAM_PLAY_P2_START_ICON_NORMAL:
		return m_pNG->index(0);

	case APL_SYS_PARAM_PLAY_P2_START_ICON_REPAIRABLE:
		return m_pNG->index(1);

	case APL_SYS_PARAM_PLAY_P2_START_ICON_UNREPAIRABLE:
		return m_pNG->index(2);

	default:
		return m_pNG->index(0);

	}
	return false;
}

bool CtContainerThumbnailTitleBar::updateP2()
{
	if (m_pP2 == NULL) return false;

	switch (APL_PARAM_GET_DATA(AplParamPlayP2Icon)) {
	case APL_SYS_PARAM_PLAY_P2_ICON_DISSELECT:
		return m_pP2->index(0);

	case APL_SYS_PARAM_PLAY_P2_ICON_SELECT:
		return m_pP2->index(1);

	case APL_SYS_PARAM_PLAY_P2_ICON_NOTHING:
		return m_pP2->index(2);

	default:
		return m_pP2->index(2);

	}
	return false;
}

bool CtContainerThumbnailTitleBar::updateMov()
{
	if (m_pMov == NULL) return false;

	switch (APL_PARAM_GET_DATA(AplParamPlayMovIcon)) {
	case APL_SYS_PARAM_PLAY_MOV_ICON_DISSELECT:
		return m_pMov->index(0);

	case APL_SYS_PARAM_PLAY_MOV_ICON_SELECT:
		return m_pMov->index(1);

	case APL_SYS_PARAM_PLAY_MOV_ICON_NOTHING:
		return m_pMov->index(2);

	default:
		return m_pMov->index(2);

	}
	return false;
}

bool CtContainerThumbnailTitleBar::updateAvchd()
{
	if (m_pAvchd == NULL) return false;

	switch (APL_PARAM_GET_DATA(AplParamPlayAvchdIcon)) {
	case APL_SYS_PARAM_PLAY_AVCHD_ICON_DISSELECT:
		return m_pAvchd->index(0);

	case APL_SYS_PARAM_PLAY_AVCHD_ICON_SELECT:
		return m_pAvchd->index(1);

	case APL_SYS_PARAM_PLAY_AVCHD_ICON_NOTHING:
		return m_pAvchd->index(2);

	default:
		return m_pAvchd->index(2);

	}
	return false;
}

bool CtContainerThumbnailTitleBar::updateSd()
{
	if (m_pSd1 == NULL) return false;
	if (m_pSd2 == NULL) return false;

	bool bRet = false;

	int sd1_select = 0;
	int sd2_select = 0;

	/* SD1挿入確認 */
	if (APL_PARAM_GET_DATA(AplParamSlot1InOutStatus) == APL_SYS_PARAM_SWITCH_OFF)
	{
		sd1_select = 0;
	}
	else {
		sd1_select = 1;
	}
	/* SD2挿入確認 */
	if (APL_PARAM_GET_DATA(AplParamSlot2InOutStatus) == APL_SYS_PARAM_SWITCH_OFF)
	{
		sd2_select = 0;
	}
	else {
		sd2_select = 1;
	}

	/* サムネイル選択状態 */
	switch (m_MediaType) {
	case ClipMediaType_SD1:
		sd1_select = 2;
		break;
	case ClipMediaType_SD2:
		sd2_select = 2;
		break;
	default:
		break;
	}

	if (m_pSd1->index(sd1_select))
		bRet = true;

	if (m_pSd2->index(sd2_select))
		bRet = true;

	return bRet;
}

bool CtContainerThumbnailTitleBar::updateOpratorSel(CtWindowID _id)
{
	if (m_WindowID == _id)
		return false;

	m_WindowID = _id;

	return updateOpratorSel();
}

bool CtContainerThumbnailTitleBar::updateMediaType(ClipMediaType _MediaType)
{
	if (m_MediaType == _MediaType)
		return false;

	m_MediaType = _MediaType;

	return updateSd();
}
