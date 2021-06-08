/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_003
 */


#include "CtWindow_003.h"
#include "CtStyle.h"

CtWindow* CtWindow_003::createWindow()
{
	//CtDebugPrint(CtDbg, " CreateWindow ID:%d ---\n", id);
	CtFontSet fSet = CtFontSet(CtColor::White);
	CtLabel* pLabel = NULL;

	m_pWin = new CtWindow();
	
	CtHLayout *pLayout001 = new CtHLayout();
	pLayout001->addWidget(new CtLabel(IC_OSD_A_IRIS_BACK), 1);
	pLayout001->addWidget(new CtLabel(IC_OSD_A_IRIS_SPOT),  1);
	pLayout001->addWidget(new CtLabel(IC_OSD_A_IRIS_STD),  1);
	pLayout001->addWidget(new CtLabel(IC_OSD_AF_AREA),  1);
	pLayout001->addWidget(new CtLabel(IC_OSD_AREA),  1);
	pLayout001->addWidget(new CtLabel(IC_OSD_AUTO),  1);
	pLayout001->addWidget(new CtLabel(IC_OSD_BONDING_ANTENNA_0),  1);
	pLayout001->addWidget(new CtLabel(IC_OSD_BONDING_ANTENNA_1),  1);
	pLayout001->addWidget(new CtLabel(IC_OSD_BONDING_ANTENNA_2),  1);
	pLayout001->addWidget(new CtLabel(IC_OSD_BONDING_ANTENNA_3),  1);

	CtHLayout *pLayout002 = new CtHLayout();
	pLayout002->addWidget(new CtLabel(IC_OSD_BONDING_ANTENNA_4),  1);
	pLayout002->addWidget(new CtLabel(IC_OSD_BONDING_ANTENNA_5),  1);
	pLayout002->addWidget(new CtLabel(IC_OSD_DIAL),  1);
	pLayout002->addWidget(new CtLabel(IC_OSD_DRS),  1);
	pLayout002->addWidget(new CtLabel(IC_OSD_HDR),  1);
	pLayout002->addWidget(new CtLabel(IC_OSD_LAN_OFF),  1);
	pLayout002->addWidget(new CtLabel(IC_OSD_LAN_ON),  1);
	pLayout002->addWidget(new CtLabel(IC_OSD_LAN_ON_ROP),  1);
	pLayout002->addWidget(new CtLabel(IC_OSD_LEVEL_OFF),  1);
	pLayout002->addWidget(new CtLabel(IC_OSD_LEVEL_ON),  1);
	
	CtHLayout *pLayout003 = new CtHLayout();
	pLayout003->addWidget(new CtLabel(IC_OSD_LEVEL_RED),  1);
	pLayout003->addWidget(new CtLabel(IC_OSD_MACRO),  1);
	pLayout003->addWidget(new CtLabel(IC_OSD_PREREC),  1);
	pLayout003->addWidget(new CtLabel(IC_OSD_S_SLOW_100),  1);
	pLayout003->addWidget(new CtLabel(IC_OSD_S_SLOW_120),  1);
	pLayout003->addWidget(new CtLabel(IC_OSD_SLOT1_OFF),  1);
	pLayout003->addWidget(new CtLabel(IC_OSD_SLOT1_ON),  1);
	pLayout003->addWidget(new CtLabel(IC_OSD_SLOT2_OFF),  1);
	pLayout003->addWidget(new CtLabel(IC_OSD_SLOT2_ON),  1);
	pLayout003->addWidget(new CtLabel(IC_OSD_STREAM_OFF),  1);

	CtHLayout *pLayout004 = new CtHLayout();
	pLayout004->addWidget(new CtLabel(IC_OSD_STREAM_STANDBY),  1);
	pLayout004->addWidget(new CtLabel(IC_OSD_STREAMING),  1);
	pLayout004->addWidget(new CtLabel(IC_OSD_VOL_OFF),  1);
	pLayout004->addWidget(new CtLabel(IC_OSD_VOL_ON),  1);
	pLayout004->addWidget(new CtLabel(IC_OSD_TARRY_G),  1);

	pLayout004->addWidget(new CtLabel(IC_OSD_WIFI_ROP_LV4),  1);
	pLayout004->addWidget(new CtLabel(IC_OSD_AC),  1);
	pLayout004->addWidget(new CtLabel(IC_OSD_AUDIO_REC_OFF),  1);
	pLayout004->addWidget(new CtLabel(IC_OSD_BACKGR_OFF),  1);
	pLayout004->addWidget(new CtLabel(IC_OSD_BACKGR_ON),  1);
	
	CtHLayout *pLayout005 = new CtHLayout();
	pLayout005->addWidget(new CtLabel(IC_OSD_BATT_LV0_RED),  1);
	pLayout005->addWidget(new CtLabel(IC_OSD_BATT_LV1),  1);
	pLayout005->addWidget(new CtLabel(IC_OSD_BATT_LV2),  1);
	pLayout005->addWidget(new CtLabel(IC_OSD_BATT_LV3),  1);
	pLayout005->addWidget(new CtLabel(IC_OSD_BATT_LV4),  1);
	pLayout005->addWidget(new CtLabel(IC_OSD_BATT_LV5),  1);
	pLayout005->addWidget(new CtLabel(IC_OSD_BOS),  1);
	pLayout005->addWidget(new CtLabel(IC_OSD_CH1_CH2),  1);
	pLayout005->addWidget(new CtLabel(IC_OSD_EOS),  1);
	pLayout005->addWidget(new CtLabel(IC_OSD_FFX10),  1);

	CtHLayout *pLayout006 = new CtHLayout();
	pLayout006->addWidget(new CtLabel(IC_OSD_FFX20),  1);
	pLayout006->addWidget(new CtLabel(IC_OSD_PLAY),  1);
	pLayout006->addWidget(new CtLabel(IC_OSD_REC),  1);
	pLayout006->addWidget(new CtLabel(IC_OSD_RELAY_OFF),  1);
	pLayout006->addWidget(new CtLabel(IC_OSD_RELAY_ON),  1);
	pLayout006->addWidget(new CtLabel(IC_OSD_REWX10),  1);
	pLayout006->addWidget(new CtLabel(IC_OSD_SIMUL_OFF),  1);
	pLayout006->addWidget(new CtLabel(IC_OSD_SIMUL_ON),  1);
	pLayout006->addWidget(new CtLabel(IC_OSD_SLOW_BACK),  1);
	pLayout006->addWidget(new CtLabel(IC_OSD_SLOW_FEED),  1);

	CtHLayout *pLayout007 = new CtHLayout();
	pLayout007->addWidget(new CtLabel(CtSize(90, 56), IC_OSD_STILL),  1);
	pLayout007->addWidget(new CtLabel(CtSize(90, 56), IC_OSD_STOP),  1);
	pLayout007->addWidget(new CtLabel(CtSize(90, 56), IC_OSD_WIFI_LV0),  1);
	pLayout007->addWidget(new CtLabel(CtSize(90, 56), IC_OSD_WIFI_LV1),  1);
	pLayout007->addWidget(new CtLabel(CtSize(90, 56), IC_OSD_WIFI_LV2),  1);
	pLayout007->addWidget(new CtLabel(CtSize(90, 56), IC_OSD_WIFI_LV3),  1);
	pLayout007->addWidget(new CtLabel(CtSize(90, 56), IC_OSD_WIFI_LV4),  1);
	pLayout007->addWidget(new CtLabel(CtSize(90, 56), IC_OSD_WIFI_OFF),  1);
	pLayout007->addWidget(new CtLabel(CtSize(90, 56), IC_OSD_WIFI_ROP_LV0),  1);
	pLayout007->addWidget(new CtLabel(CtSize(90, 56), IC_OSD_WIFI_ROP_LV1),  1);

	CtHLayout *pLayout008 = new CtHLayout();
	pLayout008->addWidget(new CtLabel(IC_OSD_WIFI_ROP_LV2),  1);
	pLayout008->addWidget(new CtLabel(IC_OSD_WIFI_ROP_LV3),  1);

	pLayout008->addWidget(new CtLabel(IC_MENU_LEVEL_LARGE_ON),  1);
	pLayout008->addWidget(new CtLabel(IC_MENU_LEVEL_SMALL_OFF),  1);
	pLayout008->addWidget(new CtLabel(IC_MENU_LEVEL_SMALL_ON),  1);
	pLayout008->addWidget(new CtLabel(IC_MENU_RETURN),  1);
	pLayout008->addWidget(new CtLabel(IC_MENU_SET),  1);
	pLayout008->addWidget(new CtLabel(IC_MENU_UP),  1);
	pLayout008->addWidget(new CtLabel(TEXTBOX_MENU_SPIN_BOX_1_1_ADJUST),  1);
	pLayout008->addWidget(new CtLabel(TEXTBOX_MENU_SPIN_BOX_1_1_SELECTED),  1);

	CtHLayout *pLayout009 = new CtHLayout();
	pLayout009->addWidget(new CtLabel(TEXTBOX_MENU_SPIN_BOX_1_2_ADJUST),  1);
	pLayout009->addWidget(new CtLabel(TEXTBOX_MENU_SPIN_BOX_1_2_SELECTED),  1);
	pLayout009->addWidget(new CtLabel(TEXTBOX_MENU_SPIN_BOX_1_3),  1);
	pLayout009->addWidget(new CtLabel(IC_MENU_KB_LEFT),  1);
	pLayout009->addWidget(new CtLabel(IC_MENU_KB_RIGHT),  1);
	pLayout009->addWidget(new CtLabel(IC_MENU_KB_SPACE),  1);
	pLayout009->addWidget(new CtLabel(IC_SETTINGS_UPDATE_ARROW),  1);

	//スライドで動作するラベルの実験用
	m_pSlideLabel = new CtSlideLabel(IC_ALERT);
	m_pSlideLabel->setAspectRatio(AspectRatio_Default);
	//	pLabel->setAspectRatio(AspectRatio_Default);
	pLayout001->addWidget(m_pSlideLabel,  1);

	CtVLayout *pLayoutAll = new CtVLayout();
	pLayoutAll->addWidget(pLayout001, CtMargin(10,10,4,4), 1);
	pLayoutAll->addWidget(pLayout002, CtMargin(10,10,4,4), 1);
	pLayoutAll->addWidget(pLayout003, CtMargin(10,10,4,4), 1);
	pLayoutAll->addWidget(pLayout004, CtMargin(10,10,4,4), 1);
	pLayoutAll->addWidget(pLayout005, CtMargin(10,10,4,4), 1);
	pLayoutAll->addWidget(pLayout006, CtMargin(10,10,4,4), 1);
	pLayoutAll->addWidget(pLayout007, CtMargin(10,10,4,4), 1);
	pLayoutAll->addWidget(pLayout008, CtMargin(10,10,4,4), 1);
	pLayoutAll->addWidget(pLayout009, CtMargin(10,10,4,4), 1);
	m_pWin->addWidget(pLayoutAll);

	//pWin->setWindowID(id);
	m_pWin->setColor(CtColor::White);

	return m_pWin;
}


bool CtWindow_003::handleTouchEvent(const CtEventTouch& Touch)
{
	bool bRet = false;
	
	bRet = m_pSlideLabel->handleTouchEvent(Touch);
	return bRet;
}


CtWindow_003::CtWindow_003(CtWindowContents *pContents)
{
}

CtWindow_003::~CtWindow_003()
{
	destroyWindow();
}

bool CtWindow_003::destroyWindow()
{
	if (m_pWin != NULL) delete m_pWin;
	if (m_pSlideLabel != NULL) delete m_pSlideLabel;
	return true;
}
