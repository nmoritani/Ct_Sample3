/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtBuilderDialog
 */

#include "CtBuilderDialog.h"



CtBuilderDialog::CtBuilderDialog(CtWindowID id):
	m_WindowId(id)
{
	memset(m_Content.version, 0, Version_Size);

	setClassType(CtClassType_Interface);
}
CtBuilderDialog::~CtBuilderDialog()
{
}

CtLayout* CtBuilderDialog::createContainer(CtWindowContents* pContents)
{
	if (pContents != NULL) {
		switch (m_WindowId) {

		case WindowID_Menu_UPDATE_CONFIRM:
		{
			unsigned char *version = static_cast<CtWindowContentsVersionDisp*>(pContents)->getNextVersion();
			memcpy(m_Content.version, version, Version_Size);
		}
		break;
		default:
			break;
		}
	}
	CtMenuInfoDialog::CtMenuDialogInfo *Info = CtMenuInfoDialog::getDialogInfo(m_WindowId);
	if (Info == NULL) {
		CtDebugPrint(CtDbg, "%s --- That WindowID is invalid ---\n", __PRETTY_FUNCTION__);
		return NULL;
	}



	CtLayout *pLayout = createLayout();


	return pLayout;
}

CtLayout* CtBuilderDialog::createLayout()
{
	/* Info */
	CtMenuInfoDialog::CtMenuDialogInfo *Info = CtMenuInfoDialog::getDialogInfo(m_WindowId);
	bool bSet = (Info != NULL) ? Info->set.flag : false;
	bool bRet = (Info != NULL) ? Info->ret.flag : false;

	/* Title */
	CtContainerMenuTitle* pTitle = new CtContainerMenuTitle(m_WindowId);
	/* Main */
	CtLayout* pMain  = createMain();
	/* Ctrl */
	CtContainerCtrlButton* pCtrl = new CtContainerCtrlButton(bSet, false, false, bRet);
	pCtrl->setFocusable(true);

	CtColor color = CtMenuInfo::getMenuBackColor();

	CtVLayout* pLayout = new CtVLayout();
	pLayout->addContainer(pTitle, 80);
	pLayout->addWidget(new CtLabel(CtSize(960, 2), CtColor::White), 2);
	pLayout->addWidget(pMain, 640 - 80);

	CtLayout* pAll = new CtLayout(color);
	pAll->addContainer(pCtrl);
	pAll->addWidget(pLayout);

	return pAll;
}

CtLayout* CtBuilderDialog::createMain()
{
	CtLayout* pLayout = NULL;

	switch (m_WindowId){
	case WindowID_Menu_VERSION:
		pLayout = createVersion();
		break;
	case WindowID_Menu_OPERATION_TIME:
		pLayout = createOperationTime();
		break;
	case WindowID_Menu_UPDATE_CONFIRM:
		pLayout = createUpdateConfirm();
		break;
	default:
		pLayout = new CtLayout();
		break;
	}

	return pLayout;
}

CtLayout* CtBuilderDialog::createVersion()
{
	CtFontSet fSetR = CtFontSet(FontTypeNormal_alignRight_Middle, CtColor::White);
	CtFontSet fSetL = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
	fSetR.setSize(39);
	fSetL.setSize(39);

	/* Label */
	CtVLayout* pVLayout = new CtVLayout();
	CtHLayout* pHLayout = NULL;
	char Data[32] = {};

	// Model
	APL_PARAM_GET_DATA_AREA(AplParamInfoModel, (unsigned char*)Data, AplParamInfoModel_Size);
	pHLayout = new CtHLayout();
	pHLayout->addWidget(new CtLabel(STR_ID_NO_10157, fSetR), AlignRight,464);
	pHLayout->addStretch(32);
	pHLayout->addWidget(new CtLabel(Data, fSetL), AlignLeft,464);
	pVLayout->addWidget(pHLayout,1);

	// Serial No.
	APL_PARAM_GET_DATA_AREA(AplParamInfoSerialNo, (unsigned char*)Data, AplParamInfoModel_Size);
	pHLayout = new CtHLayout();
	pHLayout->addWidget(new CtLabel(STR_ID_NO_10158, fSetR), AlignRight, 464);
	pHLayout->addStretch(32);
	pHLayout->addWidget(new CtLabel(Data, fSetL), AlignLeft, 464);
	pVLayout->addWidget(pHLayout,1);

	// Mac Address
	APL_PARAM_GET_DATA_AREA(AplParamInfoMacAddrString, (unsigned char*)Data, AplParamInfoMacAddrString_Size);
	pHLayout = new CtHLayout();
	pHLayout->addWidget(new CtLabel(STR_ID_NO_10554, fSetR), AlignRight, 464);
	pHLayout->addStretch(32);
	pHLayout->addWidget(new CtLabel(Data, fSetL), AlignLeft, 464);
	pVLayout->addWidget(pHLayout, 1);

	// Version
	convertVersionInfo(APL_PARAM_GET_DATA(AplParamInfoVersion), Data);
	pHLayout = new CtHLayout();
	pHLayout->addWidget(new CtLabel(STR_ID_NO_10156, fSetR), AlignRight, 464);
	pHLayout->addStretch(32);
	pHLayout->addWidget(new CtLabel(Data, fSetL), AlignLeft, 464);
	pVLayout->addWidget(pHLayout,1);

	// BE SOFT
	sprintf(Data, "v%03d", APL_PARAM_GET_DATA(AplParamBeSoftVer));
	pHLayout = new CtHLayout();
	pHLayout->addWidget(new CtLabel(STR_ID_NO_10707, fSetR), AlignRight, 464);
	pHLayout->addStretch(32);
	pHLayout->addWidget(new CtLabel(Data, fSetL), AlignLeft, 464);
	pVLayout->addWidget(pHLayout, 1);

	// CAM SOFT
	sprintf(Data, "v%03d", APL_PARAM_GET_DATA(AplParamCamSoftVer));
	pHLayout = new CtHLayout();
	pHLayout->addWidget(new CtLabel(STR_ID_NO_10708, fSetR), AlignRight, 464);
	pHLayout->addStretch(32);
	pHLayout->addWidget(new CtLabel(Data, fSetL), AlignLeft, 464);
	pVLayout->addWidget(pHLayout, 1);

	// ACT SOFT
	sprintf(Data, "v%03d", APL_PARAM_GET_DATA(AplParamActSoftVer));
	pHLayout = new CtHLayout();
	pHLayout->addWidget(new CtLabel(STR_ID_NO_10709, fSetR), AlignRight, 464);
	pHLayout->addStretch(32);
	pHLayout->addWidget(new CtLabel(Data, fSetL), AlignLeft, 464);
	pVLayout->addWidget(pHLayout, 1);

	// FOGA
	sprintf(Data, "v%03d", APL_PARAM_GET_DATA(AplParamFpgaVer));
	pHLayout = new CtHLayout();
	pHLayout->addWidget(new CtLabel(STR_ID_NO_10710, fSetR), AlignRight, 464);
	pHLayout->addStretch(32);
	pHLayout->addWidget(new CtLabel(Data, fSetL), AlignLeft, 464);
	pVLayout->addWidget(pHLayout, 1);

	return pVLayout;

}
CtLayout* CtBuilderDialog::createOperationTime()
{
	CtFontSet fSetR = CtFontSet(FontTypeNormal_alignRight_Middle, CtColor::White);
	CtFontSet fSetL = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
	fSetR.setSize(39);
	fSetL.setSize(39);

	char Data[32] = {};

	/* Label */
	{
		int Value = APL_PARAM_GET_DATA(AplParamInfoTotalOperation);
		if (Value > 999999) Value = 999999;
		sprintf(Data, "%dh", Value);
	}
	CtHLayout* pHLayout = new CtHLayout();
	pHLayout->addWidget(new CtLabel(STR_ID_NO_10161, fSetR),AlignRight, 464);
	pHLayout->addStretch(32);
	pHLayout->addWidget(new CtLabel(Data, fSetL), AlignLeft, 464);

	CtVLayout* pLayout = new CtVLayout();
	pLayout->addStretch(7);
	pLayout->addWidget(pHLayout,2);
	pLayout->addStretch(7);

	return pLayout;
}
CtLayout* CtBuilderDialog::createUpdateConfirm()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	fSet.setSize(39);

	/* Label */
	char Data1[32] = {};
	char Data2[32] = {};
	bool flag = true;

	//Get version
	int Value = APL_PARAM_GET_DATA(AplParamInfoVersion);
	flag = convertVersionInfo(Value, Data1);
	if (false == flag) return NULL;

	{
		unsigned char Version[5];
		Version[0] = m_Content.version[0];
		Version[1] = m_Content.version[1];
		Version[2] = m_Content.version[2];
		Version[3] = m_Content.version[3];
		Version[4] = m_Content.version[4];
		sprintf(Data2, "Ver.%01d.%02d-%02d-%01d.%02d", Version[0], Version[1], Version[2], Version[3], Version[4]);
	}

	/* Layout */
	CtVLayout *pLayout = new CtVLayout();
	pLayout->addStretch(5);
	pLayout->addWidget(new CtLabel(Data1, fSet), AlignCenter, 2);
	pLayout->addWidget(new CtLabel(CtSize(50, 66), IC_SETTINGS_UPDATE_ARROW), 2);
	pLayout->addWidget(new CtLabel(Data2, fSet), AlignCenter, 2);
	pLayout->addStretch(5);

	return pLayout;
}

bool CtBuilderDialog::convertVersionInfo(int Value, char *Data)
{
	if (NULL == Data) return false;
	unsigned char Version[5] = {};

	Version[0] = (unsigned char)((Value & 0xFF000000) >> 24);
	Version[1] = (unsigned char)((Value & 0x00FF0000) >> 16);
	Version[2] = (unsigned char)((Value & 0x0000F000) >> 12);
	Version[3] = (unsigned char)((Value & 0x00000F00) >> 8);
	Version[4] = (unsigned char)((Value & 0x000000FF) >> 0);

	if (WindowID_Menu_VERSION == m_WindowId) {
		sprintf(Data, "%01d.%02d-%02d-%01d.%02d", Version[0], Version[1], Version[2], Version[3], Version[4]);
	}
	else {
		sprintf(Data, "Ver.%01d.%02d-%02d-%01d.%02d", Version[0], Version[1], Version[2], Version[3], Version[4]);
	}
	return true;
}
