/**
 *  Copyright (c) 2018 Persol AVC Technology
 *  Element:          CtFastContainerLevelGauge
 */

#include <stdlib.h> 
#include "CtFastContainerLevelGauge.h"
#include "smDebugSerial.h"

const int CtFastContainerLevelGauge::a_table[] = {
	418,	// -28 Under
	413,	// -28
	408,	// -27
	408,	// -26
	403,	// -25
	403,	// -24
	398,	// -23
	398,	// -22
	393,	// -21
	393,	// -20
	388,	// -19
	388,	// -18
	383,	// -17
	383,	// -16
	378,	// -15
	378,	// -14
	373,	// -13
	373,	// -12
	368,	// -11
    368,	// -10
	363,	// -9
	358,	// -8
	353,	// -7
	348,	// -6
	343,	// -5
	338,	// -4
	333,	// -3
	328,	// -2
//	272,	// -1 under
	318,	// -0.1 ~ +0.1
//	262,	// 1 over
	308,	// 2
	303,	// 3
	298,	// 4
	293,	// 5 
	288,	// 6
	283,	// 7
	278,	// 8
	273,	// 9
	268,	// 10
	268,	// 11
	263,	// 12
	263,	// 13
	258,	// 14
	258,	// 15
	253,	// 16
	253,	// 17
	248,	// 18
	248,	// 19
	243,	// 20
	243,	// 21
	238,	// 22
	238,	// 23
	233,	// 24
	233,	// 25
	228,	// 26
	228,	// 27
	223,	// 28
	218,	// 28 Over
};

const int CtFastContainerLevelGauge::l_table[] = {
	105,	// -28
	100,	// -27
	100,	// -26
	95,		// -25
	95,		// -24
	90,		// -23
	90,		// -22
	85,		// -21
	85,		// -20
	80,		// -19
	80,		// -18
	75,		// -17
	75,		// -16
	70,		// -15
	70,		// -14
	65,		// -13
	65,		// -12
	60,		// -11
	60,		// -10
	55,		// -9
	50,		// -8
	45,		// -7
	40,		// -6
	35,		// -5
	30,		// -4
	25,		// -3
	20,		// -2
	15,		// -1
//	10,		// -0.2 ~ -0.9
	 5,		// -0.1 ~ 0.1
//	10,		// 0.2 ~ 0.9
	15,		// 1
	20,		// 2
	25,		// 3
	30,		// 4
	35,		// 5
	40,		// 6
	45,		// 7
	50,		// 8
	55,		// 9
	60,		// 10
	60,		// 11
	65,		// 12
	65,		// 13
	70,		// 14
	70,		// 15
	75,		// 16
	75,		// 17
	80,		// 18
	80,		// 19
	85,		// 20
	85,		// 21
	90,		// 22
	90,		// 23
	95,		// 24
	95,		// 25
	100,	// 26
	100,	// 27
	105,	// 28
};

CtFastContainerLevelGauge::CtFastContainerLevelGauge() :
    m_pAori(NULL),
    m_pCenter(NULL),
    m_pBar(NULL)
{
#ifdef WIN32_GUI_SIM
    m_angle = 0;
    m_level = 0;
#endif
	//dispcouter = LEVEL_DISP_COUNT;
    setClassType(CtClassType_LayoutMain);
}

CtLayout* CtFastContainerLevelGauge::createContainer()
{
    /* 部品生成 ==================================== */
#if 1
	CtLayout *pLayout = new CtLayout();
	m_pAori     = new CtLabel(CtSize(VIEW_LEVELGAUGE_WIDE_W, 5), getFarColor());
	m_pCenter   = new CtLabel(CtSize(VIEW_LEVELGAUGE_WIDE_W, 5), getFarColor());
	m_pBar      = new CtLabel(CtSize(VIEW_LEVELGAUGE_SHORT_W, 50), getFarColor());		// ある程度の高さがないと、拡大して表示する際に上下端の色がぼける
#else // test
	CtLayout *pLayout = new CtLayout(CtColor(0xFF, 0xFF, 0xFF, 0x20));
	m_pAori = new CtLabel(CtSize(VIEW_LEVELGAUGE_WIDE_W, 5), CtColor::Blue);
	m_pCenter = new CtLabel(CtSize(VIEW_LEVELGAUGE_WIDE_W, 5), CtColor::Red);
	m_pBar = new CtLabel(CtSize(VIEW_LEVELGAUGE_SHORT_W, 50), CtColor::green);		// ある程度の高さがないと、拡大して表示する際に上下端の色がぼける
#endif
	m_pAori->setFastDraw(true);
	m_pCenter->setFastDraw(true);
	m_pBar->setFastDraw(true);

    /* Layout生成 ================================== */
    /* 座標とサイズは後で設定 */
	pLayout->addWidget( m_pAori     );
	pLayout->addWidget( m_pCenter   );
	pLayout->addWidget( m_pBar      );

    return pLayout;
}

bool CtFastContainerLevelGauge::startupContainer()
{
	return setVisible(isDispLevelGauge());
}

bool CtFastContainerLevelGauge::handleParamEvent(const CtEventParam& Param) {
	bool isRedraw = true;
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamBalanceLevel:
	case AplParamColorBar:
	case AplParamLcdFocusExpandUserSw:
		setVisible(isDispLevelGauge());
		return true;
		break;
	default:
		break;
	}
	return isRedraw;
}

CtFastContainerLevelGauge::~CtFastContainerLevelGauge(){
    destroyContainer();
}

bool CtFastContainerLevelGauge::destroyContainer(){
    return true;
}

bool CtFastContainerLevelGauge::updateFastDraw()
{
	updatePos();
    return true;
}

int CtFastContainerLevelGauge::getAngleValue()
{
#ifdef WIN32_GUI_SIM
    short value;
    m_angle = m_angle - 1;
    if( m_angle < -280){
        m_angle = 280;
    }
	value = m_angle;
#else
    short value = APL_PARAM_GET_DATA(AplParamLcdLevelGaugeAoriAngle);
#endif

    if( value >= 280 ){
        value = 280;
    } else if(value <= -280) {
        value = -280;
    }

    return value;
}

int CtFastContainerLevelGauge::getBalanceValue()
{
#ifdef WIN32_GUI_SIM
    short value = m_level;
    m_level = m_level + 1;
    if( m_level > 280){
        m_level = -280;
    }
	value = m_level;
#else
    short value = APL_PARAM_GET_DATA(AplParamLcdLevelGaugeBalanceAngle);
#endif
	
    if( value >= 280 ){
        value = 280;
    } else if(value <= -280) {
        value = -280;
    }

    return value;
}

void CtFastContainerLevelGauge::updatePos()
{
}

CtColor CtFastContainerLevelGauge::getFarColor()
{
	unsigned char r = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorFarR);
	unsigned char g = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorFarG);
	unsigned char b = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorFarB);
	unsigned char a = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorFarA);
	return CtColor(r, g, b, a);
}

CtColor CtFastContainerLevelGauge::getNearColor() {
	unsigned char r = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorNearR);
	unsigned char g = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorNearG);
	unsigned char b = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorNearB);
	unsigned char a = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorNearA);
	return CtColor(r, g, b, a);
}

CtColor CtFastContainerLevelGauge::getFocusLockColor() {
	unsigned char r = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorFocusLockR);
	unsigned char g = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorFocusLockG);
	unsigned char b = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorFocusLockB);
	unsigned char a = (unsigned char)APL_PARAM_GET_DATA(AplParamBalanceAngleColorFocusLockA);
	return CtColor(r, g, b, a);
}

bool CtFastContainerLevelGauge::isDispLevelGauge(){
    bool isDisp = true;

	if( APL_PARAM_GET_DATA( AplParamColorBar ) == APL_SYS_PARAM_SWITCH_ON ){
		isDisp = false;
	}
	if( APL_PARAM_GET_DATA( AplParamLcdFocusExpandUserSw ) == APL_SYS_PARAM_SWITCH_ON ){
		isDisp = false;
	}
	if( APL_PARAM_GET_DATA( AplParamBalanceLevel ) == APL_SYS_PARAM_SWITCH_OFF ){
		isDisp = false;
	}
	if( APL_PARAM_GET_DATA( AplParamLcdCleanViewUserSw) == APL_SYS_PARAM_SWITCH_ON ){
		isDisp = false;
	}
	/*
	if( isDisp == true ){
		if( dispcouter == 0 ){
			isDisp = true;
		} else {
			isDisp = false;
		}
		if( dispcouter > 0 ) {dispcouter--;}
	} else {
		dispcouter = LEVEL_DISP_COUNT;
	}
	*/
	return isDisp;
}

CtFastContainerLevelGauge::LevelGaugeFocusType CtFastContainerLevelGauge::getFocusType(int value)
{
	if (-1 <= value && value <= 1) {
		return LevelGaugeFocusType_FocusLock;
	}
	else if (-9 <= value && value <= -2) {
		return LevelGaugeFocusType_NearMinus;
	}
	else if (2 <= value && value <= 9) {
		return LevelGaugeFocusType_NearPlus;
	}
	
	return LevelGaugeFocusType_Far;
}

void CtFastContainerLevelGauge::updatePosCommon(int aori, int balance, CtRegion rAori, CtRegion rCenter, CtRegion rBar)
{
	CtLayout* pLayout = getLayout();
	CtColor color;
	int y = 0, h = 0, sy = 0;

	const int center_y = 317;	// Barの高さ考慮(3)、レイアウト高さ/2

	if (pLayout == NULL) {
		return;
	}

	/*
		<メモ>
		あおり引数    => AoriラベルのYおよび色、CenterラベルのY に影響
		バランス引数  => Centerラベルの色、Barラベルの色, YおよびHeightに影響
	*/

	switch (getFocusType(aori)) {
	case LevelGaugeFocusType_FocusLock:
		color = getFocusLockColor();
		y = center_y;
		break;
	case LevelGaugeFocusType_NearMinus:
		color = getNearColor();
		y = center_y + 5;
		break;
	case LevelGaugeFocusType_NearPlus:
		color = getNearColor();
		y = center_y - 5;
		break;
	case LevelGaugeFocusType_Far:
	default:
		color = getFarColor();
		y = a_table[aori / 10 + 28];
		break;
	}

	rAori.y = y;/* pgr0351 */
	m_pAori->setColor(color);
	m_pAori->setRegion(rAori);

	switch (getFocusType(balance)) {
	case LevelGaugeFocusType_FocusLock:
		color = getFocusLockColor();
		h = 5;
		break;
	case LevelGaugeFocusType_NearMinus:
	case LevelGaugeFocusType_NearPlus:
		color = getNearColor();
		h = 10;
		break;
	case LevelGaugeFocusType_Far:
	default:
		color = getFarColor();
		h = l_table[balance / 10 + 28];
		break;
	}

	rCenter.y = y;/* pgr0351 */
	m_pCenter->setColor(color);
	m_pCenter->setRegion(rCenter);

	if (balance < 0) {
		sy = (y - h) + 5;
	}
	else {
		sy = y;
	}

	rBar.y = sy;/* pgr0351 */
	rBar.height = h;/* pgr0351 */
	m_pBar->setColor(color);
	m_pBar->setRegion(rBar);
}
