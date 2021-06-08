/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactWindowDialog
*/


#include "CtFactWindowDialog.h"

CtFactWindowDialog::MessageInfo CtFactWindowDialog::InfoTable[] = {
	{ WindowID_Fact_VERSION     ,MessageType_Version     ,0 ,""             , false },
	{ WindowID_Fact_HOUR_METERS ,MessageType_HourMeters  ,0 ,""             , false },
	{ WindowID_Fact_PleaseWait  ,MessageType_Center      ,1 ,"Please Wait." , false },
	{ WindowID_Fact_SaveOK      ,MessageType_Center      ,1 ,"SAVE OK."     , true  },
	{ WindowID_Fact_SaveNG      ,MessageType_Center      ,1 ,"SAVE NG."     , true  },
	{ WindowID_Fact_END         ,MessageType_End         ,1 ,""             , false },
};

CtFactWindowDialog::MessageInfo* CtFactWindowDialog::getInfo(CtWindowID WindowID)
{
	for (unsigned int i = 0; i < sizeof(InfoTable) / sizeof(MessageInfo); i++) {
		if (WindowID == InfoTable[i].id) {
			return &InfoTable[i];
		}
	}
	return NULL;
}


CtFactWindowDialog::CtFactWindowDialog():
	m_pWin(NULL),
	m_pInfo(NULL)
{
	setClassType(CtClassType_WindowFACT);
}
CtFactWindowDialog::~CtFactWindowDialog()
{
}
bool CtFactWindowDialog::destroyWindow()
{
	return true;
}

CtWindow* CtFactWindowDialog::createWindow()
{
	m_pWin = new CtWindow();

	CtLayout* pLayout = NULL;
	CtContainerCtrlButton* pCtrl = NULL;

	m_pInfo = getInfo(getWindowID());

	MessageType type = (m_pInfo == NULL) ? MessageType_Max : m_pInfo->type;

	switch (type){
	case MessageType_Version:
		pLayout = createVersion();
		break;
	case MessageType_HourMeters:
		pLayout = createHourMeters();
		break;
	case MessageType_Center:
		pLayout = createCenterMessage();
		break;
	case MessageType_End:
		pLayout = createEndMessage();
		break;
	default:
		pCtrl = new CtContainerCtrlButton(false, false, false, true);
		pLayout = new CtLayout(CtColor::Black);
		pLayout->addContainer(pCtrl);
		break;
	}

	m_pWin->addWidget(pLayout);
	
	return m_pWin;
}

CtLayout* CtFactWindowDialog::createVersion()
{
	char Data[32] = {};

	CtFontSet fSet_Center = CtFontSet(FontTypeNormal_alignCenter, CtColor::orange);
	CtFontSet fSet_Left = CtFontSet(FontTypeNormal, CtColor::White);
	CtFontSet fSet_Right = CtFontSet(FontTypeNormal_alignRight, CtColor::White);

	CtHLayout* pLayout1 = new CtHLayout();
	CtHLayout* pLayout2 = new CtHLayout();
	CtHLayout* pLayout3 = new CtHLayout();
	CtHLayout* pLayout4 = new CtHLayout();
	CtHLayout* pLayout5 = new CtHLayout();
	CtHLayout* pLayout6 = new CtHLayout();
	CtHLayout* pLayout7 = new CtHLayout();
	CtHLayout* pLayout8 = new CtHLayout();
	CtHLayout* pLayout9 = new CtHLayout();
	CtHLayout* pLayout10 = new CtHLayout();

	CtVLayout* pAll = new CtVLayout();
	pAll->addWidget(pLayout1, 2);
	pAll->addWidget(pLayout2, 2);
	pAll->addWidget(pLayout3, 2);
	pAll->addWidget(pLayout4, 2);
	pAll->addWidget(pLayout5, 2);

	pAll->addWidget(pLayout6, 1);

	pAll->addWidget(pLayout7, 2);
	pAll->addWidget(pLayout8, 2);
	pAll->addWidget(pLayout9, 2);
	pAll->addWidget(pLayout10, 2);


	/* 1段目 */
	pLayout1->addWidget(new CtLabel("VERSION : ", fSet_Right));

	int Value = APL_PARAM_GET_DATA(AplParamInfoVersion);
	convertVersionInfo(Value, Data);
	pLayout1->addWidget(new CtLabel(Data, fSet_Left));

	/* 2段目 */
	pLayout2->addWidget(new CtLabel("BE SOFT : ", fSet_Right));
	{
		int Value = APL_PARAM_GET_DATA(AplParamBeSoftVer);
		sprintf(Data, "v%03d", Value);
	}
	pLayout2->addWidget(new CtLabel(Data, fSet_Left));

	/* 3段目 */
	pLayout3->addWidget(new CtLabel("CAM SOFT : ", fSet_Right));
	{
		int Value = APL_PARAM_GET_DATA(AplParamCamSoftVer);
		sprintf(Data, "v%03d", Value);
	}
	pLayout3->addWidget(new CtLabel(Data, fSet_Left));

	/* 4段目 */
	pLayout4->addWidget(new CtLabel("ACT SOFT : ", fSet_Right));
	{
		int Value = APL_PARAM_GET_DATA(AplParamActSoftVer);
		sprintf(Data, "v%03d", Value);
	}
	pLayout4->addWidget(new CtLabel(Data, fSet_Left));

	/* 5段目 */
	pLayout5->addWidget(new CtLabel("FPGA : ", fSet_Right));
	{
		int Value = APL_PARAM_GET_DATA(AplParamFpgaVer);
		sprintf(Data, "v%03d", Value);
	}
	pLayout5->addWidget(new CtLabel(Data, fSet_Left));

	/* 6段目 */
	pLayout6->addWidget(new CtLabel("", fSet_Right));
	pLayout6->addWidget(new CtLabel());

	/* 7段目 */
	pLayout7->addWidget(new CtLabel("BE EEPROM : ", fSet_Right));
	{
		int Value = APL_PARAM_GET_DATA(AplParamBeEepVer);
		sprintf(Data, "%08X", Value);
	}
	pLayout7->addWidget(new CtLabel(Data, fSet_Left));

	/* 8段目 */
	pLayout8->addWidget(new CtLabel("CAM EEPROM : ", fSet_Right));
	{
		int Value = APL_PARAM_GET_DATA(AplParamCamEepVer);
		sprintf(Data, "%08X", Value);
	}
	pLayout8->addWidget(new CtLabel(Data, fSet_Left));

	/* 9段目 */
	pLayout9->addWidget(new CtLabel("BE CRC : ", fSet_Right));
	{
		int Value = APL_PARAM_GET_DATA(AplParamBeCrc);
		sprintf(Data, "%04X", Value);
	}
	pLayout9->addWidget(new CtLabel(Data, fSet_Left));

	/* 10段目 */
	pLayout10->addWidget(new CtLabel("CAM CRC : ", fSet_Right));
	{
		int Value = APL_PARAM_GET_DATA(AplParamCamCrc);
		sprintf(Data, "%04X", Value);
	}
	pLayout10->addWidget(new CtLabel(Data, fSet_Left));

	CtContainerCtrlButton* pCtrl = new CtContainerCtrlButton(false, false, false, true);
	pCtrl->setFocusable(true);

	CtLayout* pLayout = new CtLayout(CtColor::Black);
	pLayout->addContainer(pCtrl);
	pLayout->addWidget(pAll);

	return pLayout;
}

CtLayout* CtFactWindowDialog::createHourMeters()
{
	const int line = 8;

	enum HourMetertype {
		HourMeter_Time,
		HourMeter_Time2,
		HourMeter_Count,
		HourMeter_Num,
	};

	struct HourMeter {
		char* name;
		AplParamEepromId id;
		HourMetertype type;
	};

	HourMeter teble[line] = {
		{ "TOTAL OPERATION", AplParamInfoTotalOperation, HourMeter_Time  },	/* 1段目 TOTAL OPERATION */
		{ "P.ON TIMES"     , AplParamInfoPowerOnTimes  , HourMeter_Count },	/* 2段目 P.ON TIMES */
		{ "SERVO ZOOM"     , AplParamInfoServoZoom     , HourMeter_Count },	/* 3段目 SERVO ZOOM */
		{ "GRIP ZOOM"      , AplParamInfoGripZoom      , HourMeter_Count },	/* 4段目 GRIP ZOOM */
		{ "HANDLE ZOOM"    , AplParamInfoHandleZoom    , HourMeter_Count },	/* 5段目 HANDLE ZOOM */
		{ "LCD OPERATION"  , AplParamInfoLcdOperation  , HourMeter_Time2 },	/* 6段目 LCD OPERATION */
		{ "EVF OPERATION"  , AplParamInfoEvfOperation  , HourMeter_Time2 },	/* 7段目 EVF OPERATION */
		{ "SENSOR TEMP"    , AplParamInfoSensorTemp    , HourMeter_Num   },	/* 8段目 SENSOR TEMP */
	};

	char Data[32] = {};
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtVLayout* pAll = new CtVLayout();
	pAll->addStretch(1);

	CtHLayout* pH = NULL;
	for (int i = 0; i < line; i++) {

		switch (teble[i].type){
		case HourMeter_Time:
		{
			unsigned int Value = APL_PARAM_GET_DATA(teble[i].id);
			sprintf(Data, "%dh", Value);
			break;
		}
		case HourMeter_Time2:
		{
			unsigned int Value = APL_PARAM_GET_DATA(teble[i].id);
			sprintf(Data, "%06dh%02dm%02ds", Value / 60 / 60, (Value / 60) % 60, Value % 60);
			break;
		}
		case HourMeter_Count:
		{
			int Value = APL_PARAM_GET_DATA(teble[i].id);
			sprintf(Data, "%06d", Value);
			break;
		}
		case HourMeter_Num:
		{
			int Value = APL_PARAM_GET_DATA(teble[i].id);
			sprintf(Data, "%d", Value);
			break;
		}
		default:
			sprintf(Data, "");
			break;
		}

		pH = new CtHLayout();
		pH->addStretch(128);
		pH->addWidget(new CtLabel(teble[i].name, fSet), AlignLeft, 400);
		pH->addWidget(new CtLabel(" : ", fSet), AlignHCenter, 32);
		pH->addWidget(new CtLabel(Data, fSet), AlignLeft, 400);
		pAll->addWidget(pH,1);
	}
	
	pAll->addStretch(1);

	CtContainerCtrlButton* pCtrl = new CtContainerCtrlButton(false, false, false, true);
	pCtrl->setFocusable(true);

	CtLayout* pLayout = new CtLayout(CtColor::Black);
	pLayout->addContainer(pCtrl);
	pLayout->addWidget(pAll);

	return pLayout;
}

CtLayout* CtFactWindowDialog::createCenterMessage()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);

	CtVLayout* pAll = new CtVLayout();
	pAll->addStretch(9 - m_pInfo->line);	/* pgr0398 */
	pAll->addWidget(new CtLabel(m_pInfo->str, fSet), m_pInfo->line * 2);	/* pgr0398 */
	pAll->addStretch(10 - m_pInfo->line);	/* pgr0398 */

	CtContainerCtrlButton* pCtrl = new CtContainerCtrlButton(false, false, false, m_pInfo->ret);
	pCtrl->setFocusable(true);

	CtLayout* pLayout = new CtLayout(CtColor::Black);
	pLayout->addContainer(pCtrl);
	pLayout->addWidget(pAll);

	return pLayout;
}

CtLayout* CtFactWindowDialog::createEndMessage()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtLabel* pLabel = new CtLabel("END.", fSet);

	CtVLayout* pV = new CtVLayout(CtColor(ColorRGBA, 0x262626ff, NULL));
	pV->addStretch(8);
	{
		CtHLayout* pH = new CtHLayout();
		pH->addWidget(pLabel, AlignRight, 7);
		pH->addStretch(1);
		pV->addWidget(pH, 4);
	}
	pV->addStretch(1);

	CtLayout* pLayout = new CtLayout(CtColor::Trans);
	pLayout->addWidget(pV, CtMargin(20));
	
	setTransView(true);

	return pLayout;
}

bool CtFactWindowDialog::handleButtonEvent(const CtEventButton& Button)
{
    if( Button.getPressType() == CtEventButton::Release ||
        Button.getPressType() == CtEventButton::RepeatPress){
        if( (Button.getWidgetID() == WidgetID_RET) ){
			CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)Close, WindowNone);
			return true;
		}
    }

    return false;
}

bool CtFactWindowDialog::handleKeyEvent(const CtEventKey& Key)
{
	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_Exit:
	case CtEventKey::KeyCode_GripUser1:
		if (m_pInfo == NULL) {
			if (Key.getKeyAction() == CtEventKey::Release) {
				CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
				return true;
			}
		}
		else {
			if (m_pInfo->ret) {
				if (Key.getKeyAction() == CtEventKey::Release) {
					CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
					return true;
				}
			}
		}
		break;
	default:
		break;
	}
	return false;

}

bool CtFactWindowDialog::convertVersionInfo(int Value, char *Data)
{
    if( NULL == Data ) return false;
    unsigned char Version[5] = {};

    Version[0] = (unsigned char)( (Value & 0xFF000000) >> 24 );
    Version[1] = (unsigned char)( (Value & 0x00FF0000) >> 16 );
    Version[2] = (unsigned char)( (Value & 0x0000F000) >> 12 );
    Version[3] = (unsigned char)( (Value & 0x00000F00) >>  8 );
    Version[4] = (unsigned char)( (Value & 0x000000FF) >>  0 );

    sprintf( Data, "%01d.%02d-%02d-%01d.%02d", Version[0], Version[1], Version[2], Version[3], Version[4] );
 //       sprintf( Data, "Ver.%01d.%02d-%02d-%01d.%02d", Version[0], Version[1], Version[2], Version[3], Version[4] );
    return true;
}
