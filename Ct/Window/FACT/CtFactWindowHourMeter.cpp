/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactWindowHourMeter
*/

#include "CtFactWindowHourMeter.h"


CtFactWindowHourMeter::CtFactWindowHourMeter(CtWindowContents* pContents):
	m_pContents(NULL)
{
	if (pContents != NULL) {
		m_pContents = new CtWindowContentsFactHourMeter((CtWindowContentsFactHourMeter&)*pContents);
	}
	setClassType(CtClassType_WindowFACT);
}
CtFactWindowHourMeter::~CtFactWindowHourMeter()
{
	if (m_pContents != NULL) {
		delete m_pContents;
		m_pContents = NULL;
	}
}
bool CtFactWindowHourMeter::destroyWindow()
{
	return true;
}

CtWindow* CtFactWindowHourMeter::createWindow()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtVLayout* pAll = new CtVLayout();
	pAll->addStretch(1);

#if 0
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
		{ "TOTAL OPERATION", AplParamInfoTotalOperation, HourMeter_Time },	/* 1段目 TOTAL OPERATION */
		{ "P.ON TIMES"     , AplParamInfoPowerOnTimes  , HourMeter_Count },	/* 2段目 P.ON TIMES */
		{ "SERVO ZOOM"     , AplParamInfoServoZoom     , HourMeter_Count },	/* 3段目 SERVO ZOOM */
		{ "GRIP ZOOM"      , AplParamInfoGripZoom      , HourMeter_Count },	/* 4段目 GRIP ZOOM */
		{ "HANDLE ZOOM"    , AplParamInfoHandleZoom    , HourMeter_Count },	/* 5段目 HANDLE ZOOM */
		{ "LCD OPERATION"  , AplParamInfoLcdOperation  , HourMeter_Time2 },	/* 6段目 LCD OPERATION */
		{ "EVF OPERATION"  , AplParamInfoEvfOperation  , HourMeter_Time2 },	/* 7段目 EVF OPERATION */
		{ "SENSOR TEMP"    , AplParamInfoSensorTemp    , HourMeter_Num },	/* 8段目 SENSOR TEMP */
	};

	char Data[32] = {};

	CtHLayout* pH = NULL;
	for (int i = 0; i < line; i++) {

		switch (teble[i].type) {
		case HourMeter_Time:
		{
			unsigned int Value = APL_PARAM_GET_DATA(teble[i].id);
			sprintf(Data, "%06dh", Value);
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
		pAll->addWidget(pH, 1);
	}
#else
	CtHLayout* pH = NULL;

	CtWindowContentsFactHourMeter::HourMeterList& list = m_pContents->getHourMeterList();
	for (CtWindowContentsFactHourMeter::HourMeterListItr Itr = list.begin(); Itr != list.end(); ++Itr) {
		CtWindowContentsFactHourMeter::HourMeterInfo Info = *Itr;
		pH = new CtHLayout();
		pH->addStretch(128);
		pH->addWidget(new CtLabel(Info.name, fSet), AlignLeft, 400);
		pH->addWidget(new CtLabel(" : ", fSet), AlignHCenter, 32);
		pH->addWidget(new CtLabel(Info.data, fSet), AlignLeft, 400);
		pAll->addWidget(pH);
	}
#endif
	pAll->addStretch(1);

	CtContainerCtrlButton* pCtrl = new CtContainerCtrlButton(false, false, false, true);
	pCtrl->setFocusable(true);

	CtLayout* pLayout = new CtLayout(CtColor::Black);
	pLayout->addContainer(pCtrl);
	pLayout->addWidget(pAll);

	CtWindow* pWin = new CtWindow();
	pWin->addWidget(pLayout);
	
	return pWin;
}



bool CtFactWindowHourMeter::handleButtonEvent(const CtEventButton& Button)
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
bool CtFactWindowHourMeter::handleKeyEvent(const CtEventKey& Key)
{
	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_Exit:
	case CtEventKey::KeyCode_GripUser1:
		if (Key.getKeyAction() == CtEventKey::Release) {
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
			return true;
		}
		break;
	default:
		break;
	}
	return false;

}
