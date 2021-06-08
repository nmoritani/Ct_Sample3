/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/
#include "CtModeCheckNetwork.h"

CtModeCheckNetwork::CtModeCheckNetwork() :
	m_pAll(NULL)
{
}

CtModeCheckNetwork::~CtModeCheckNetwork()
{
}

CtLayout* CtModeCheckNetwork::createContainer()
{
	CtRecViewFontSet fset = CtRecViewFontSet();

	m_pAll = new CtLayout(CtColor::Trans);
	{
		CtVLayout* pV = new CtVLayout();
		pV->addStretch(1, ScreenLCD);
		CtHLayout* pNetWorkBlock = new CtHLayout();
		{
			pNetWorkBlock->addStretch(12);
			CtVLayout* pNetworkArea = new CtVLayout();
			{
				CtHLayout* pNetworkTitle = new CtHLayout();
				{
					pNetworkTitle->addStretch(8);
					CtHLayout* pH = new CtHLayout();
					{
						pH->addWidget(new CtLabel("-- ", fset), 3);
						pH->addWidget(new CtLabel(STR_ID_NO_10690, fset), 7);
						pH->addWidget(new CtLabel(" --", fset), 3);
						pNetworkTitle->addWidget(pH, 14);
					}
					pNetworkTitle->addStretch(19);
				}
				pNetworkArea->addWidget(pNetworkTitle, 1);

				CtHLayout* pDeviceSelLine = new CtHLayout();
				{
					pDeviceSelLine->addWidget(new CtLabel(STR_ID_NO_11538, fset), AlignLeft, 14);
					pDeviceSelLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pDeviceSelLine->addStretch(1);
					m_pDeviceSel = new CtLabel("", fset);
					pDeviceSelLine->addWidget(m_pDeviceSel, AlignLeft, 24);
				}
				pNetworkArea->addWidget(pDeviceSelLine, 1);

				CtHLayout* pNetworkFuncLine = new CtHLayout();
				{
					pNetworkFuncLine->addWidget(new CtLabel(STR_ID_NO_11501, fset), AlignLeft, 14);
					pNetworkFuncLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pNetworkFuncLine->addStretch(1);
					m_pNetWorkFunc = new CtLabel("", fset);
					pNetworkFuncLine->addWidget(m_pNetWorkFunc, AlignLeft, 24);
				}
				pNetworkArea->addWidget(pNetworkFuncLine, 1);

				m_pStrmFormatLine = new CtHLayout();
				{
					m_pStrmFormatLine->addWidget(new CtLabel(STR_ID_NO_11541, fset), AlignLeft, 14);
					m_pStrmFormatLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					m_pStrmFormatLine->addStretch(1);
					m_pStrmFormat = new CtLabel("", fset);
					m_pStrmFormatLine->addWidget(m_pStrmFormat, AlignLeft, 24);
				}
				pNetworkArea->addWidget(m_pStrmFormatLine, 1);

				m_pStrmDataTypeLine = new CtHLayout();
				{
					m_pStrmDataTypeLine->addWidget(new CtLabel(STR_ID_NO_11542, fset), AlignLeft, 14);
					m_pStrmDataTypeLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					m_pStrmDataTypeLine->addStretch(1);
					m_pStrmDataType = new CtLabel("", fset);
					m_pStrmDataTypeLine->addWidget(m_pStrmDataType, AlignLeft, 24);
				}
				pNetworkArea->addWidget(m_pStrmDataTypeLine, 1);

				CtHLayout* pIpRemoteLine = new CtHLayout();
				{
					pIpRemoteLine->addWidget(new CtLabel(STR_ID_NO_11476, fset), AlignLeft, 14);
					pIpRemoteLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pIpRemoteLine->addStretch(1);
					m_pIpRemote = new CtLabel("", fset);
					pIpRemoteLine->addWidget(m_pIpRemote, AlignLeft, 24);
				}
				pNetworkArea->addWidget(pIpRemoteLine, 1);

				CtHLayout* pIpAddressLine = new CtHLayout();
				{
					pIpAddressLine->addWidget(new CtLabel(STR_ID_NO_10835, fset), AlignLeft, 14);
					pIpAddressLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pIpAddressLine->addStretch(1);
					m_pIpAddress = new CtLabel("", fset);
					pIpAddressLine->addWidget(m_pIpAddress, AlignLeft, 24);
				}
				pNetworkArea->addWidget(pIpAddressLine, 1);
			}
			pNetWorkBlock->addWidget(pNetworkArea, 40);
			pNetWorkBlock->addStretch(1);
		}
		pV->addWidget(pNetWorkBlock, 7);
		pV->addStretch(5);
		pV->addStretch(1, ScreenLCD);
		m_pAll->addWidget(pV);
	}
	updateStrmFormat();
	updateStrmDataType();
	return m_pAll;
}

bool CtModeCheckNetwork::destroyWindow()
{
	return true;
}

bool CtModeCheckNetwork::startupContainer() {
	updateDeviceSel(APL_PARAM_GET_DATA(AplParamNetworkDeviceSel));
	updateNetWorkFunc(APL_PARAM_GET_DATA(AplParamNetworkFunc));
	updateStrmFormat();
	updateStrmDataType();
	updateIpRemote(APL_PARAM_GET_DATA(AplParamIpRemoteEnable));
	updateIpAddress();
	return true;
}

bool CtModeCheckNetwork::handleButtonEvent(const CtEventButton& Button)
{
	/* Release‚Å‚Ì‚İˆ— */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	return false;
}

bool CtModeCheckNetwork::handleKeyEvent(const CtEventKey& Key) {

	switch (Key.getKeyAction()) {
	case CtEventKey::Press:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_MmrMinus:
		case CtEventKey::KeyCode_MmrPlus:
		case CtEventKey::KeyCode_Up:
		case CtEventKey::KeyCode_Down:
		case CtEventKey::KeyCode_Right:
		case CtEventKey::KeyCode_Left:
		case CtEventKey::KeyCode_Enter:
		case CtEventKey::KeyCode_ManualFunction:
			return true;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return false;

}

bool CtModeCheckNetwork::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();
	bool bRet = false;
	switch (t_Id) {
	case AplParamNetworkDeviceSel:
		bRet |= updateDeviceSel(int_Data);/* pgr2711 */
		bRet |= updateIpAddress();/* pgr2711 */
		break;
	case AplParamNetworkFunc:
		bRet |= updateStrmFormat();/* pgr2711 */
		bRet |= updateStrmDataType();/* pgr2711 */
		bRet |= updateNetWorkFunc(int_Data);/* pgr2711 */
		break;
	case AplParamStreamingFormat:
	case AplParamNdiHxStreamingFormat:
		bRet |= updateStrmFormat();/* pgr2711 */
		break;
	case AplParamIpRemoteEnable:
		bRet |= updateIpRemote(int_Data);/* pgr2711 */
		break;
	case AplParamStreamingDataType:
		bRet |= updateStrmDataType();/* pgr2711 */
		break;
	case AplParamIpAddress:
	case AplParamLanIpAddressV6:
	case AplParamLanIpAddress:
	case AplParamIpAddressV6:
	case AplParamLanEnableIPv6:
	case AplParamEnableIPv6:
		bRet |= updateIpAddress();/* pgr2711 */
		break;
	default:
		return false;
		break;
	}
	return bRet;
}

bool CtModeCheckNetwork::updateDeviceSel(int int_Data) {
	switch (int_Data) {
	case APL_SYS_PARAM_NETWORK_DEVICE_SEL_LAN:
		return m_pDeviceSel->setStringID(STR_ID_NO_11539);
		break;
	case APL_SYS_PARAM_NETWORK_DEVICE_SEL_WLAN:
		return m_pDeviceSel->setStringID(STR_ID_NO_10834);
		break;
	case APL_SYS_PARAM_NETWORK_DEVICE_SEL_CELLULAR:
		return m_pDeviceSel->setText("Cellular");// Vup
		break;
	case APL_SYS_PARAM_NETWORK_DEVICE_SEL_OFF:
		return m_pDeviceSel->setStringID(STR_ID_NO_10792);
		break;
	default:
		return false;
		break;
	}
}

bool CtModeCheckNetwork::updateNetWorkFunc(int int_Data) {
	switch (int_Data) {
	case APL_SYS_PARAM_NETWORK_FUNC_FTP_CLIENT:
		return m_pNetWorkFunc->setText("FTP CLIENT");// Vup
		break;
	case APL_SYS_PARAM_NETWORK_FUNC_STREAMING:
		return m_pNetWorkFunc->setStringID(STR_ID_NO_11540);
		break;
	case APL_SYS_PARAM_NETWORK_FUNC_NDI_HX:
		return m_pNetWorkFunc->setStringID(STR_ID_NO_11283);
		break;
	case APL_SYS_PARAM_NETWORK_FUNC_OFF:
		return m_pNetWorkFunc->setStringID(STR_ID_NO_10792);
		break;
	default:
		return false;
		break;
	}
}

bool CtModeCheckNetwork::updateStrmFormat() {
	GDI_STRING_ID strId = STRING_ID_INVALID;
	int formatId = 0;

	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_STREAMING) {
		formatId = APL_PARAM_GET_DATA(AplParamStreamingFormat);
		switch (formatId) {
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_60_24M:strId = STR_ID_NO_11572; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_60_20M:strId = STR_ID_NO_11573; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_60_16M:strId = STR_ID_NO_11574; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_50_24M:strId = STR_ID_NO_11577; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_50_20M:strId = STR_ID_NO_11578; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_50_16M:strId = STR_ID_NO_11579; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_30_14M:strId = STR_ID_NO_11582; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_30_6M: strId = STR_ID_NO_11584; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_30_1M: strId = STR_ID_NO_11585; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_25_14M:strId = STR_ID_NO_11586; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_25_6M: strId = STR_ID_NO_11588; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_25_1M:	strId = STR_ID_NO_11589; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_24_14M:strId = STR_ID_NO_11590; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_24_6M:	strId = STR_ID_NO_11591; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_1080_24_1M: strId = STR_ID_NO_11592; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_60_14M:	strId = STR_ID_NO_11593; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_60_8M:	strId = STR_ID_NO_11595; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_60_3M:	strId = STR_ID_NO_11597; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_50_14M: strId = STR_ID_NO_11598; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_50_8M:	strId = STR_ID_NO_11600; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_50_3M:	strId = STR_ID_NO_11602; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_30_8M:	strId = STR_ID_NO_11603; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_30_2M:	strId = STR_ID_NO_11605; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_30_1M:	strId = STR_ID_NO_11606; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_25_8M:	strId = STR_ID_NO_11607; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_25_2M:	strId = STR_ID_NO_11609; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_25_1M:	strId = STR_ID_NO_11610; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_24_8M:	strId = STR_ID_NO_11611; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_24_2M:	strId = STR_ID_NO_11612; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_720_24_1M:	strId = STR_ID_NO_11613; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_360_30_4M:	strId = STR_ID_NO_11614; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_360_30_1_5M:strId = STR_ID_NO_11615; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_360_30_0_7M:strId = STR_ID_NO_11616; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_360_25_4M:	strId = STR_ID_NO_11617; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_360_25_1_5M:strId = STR_ID_NO_11618; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_360_25_0_7M:strId = STR_ID_NO_11619; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_360_24_4M:	strId = STR_ID_NO_11620; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_360_24_1_5M:strId = STR_ID_NO_11621; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_360_24_0_7M:strId = STR_ID_NO_11622; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_180_30_4M:	strId = STR_ID_NO_11623; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_180_30_1_5M:strId = STR_ID_NO_11624; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_180_30_0_5M:strId = STR_ID_NO_11625; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_180_25_4M:	strId = STR_ID_NO_11626; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_180_25_1_5M:strId = STR_ID_NO_11627; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_180_25_0_5M:strId = STR_ID_NO_11628; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_180_24_4M:	strId = STR_ID_NO_11629; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_180_24_1_5M:strId = STR_ID_NO_11630; break;
		case APL_SYS_PARAM_STREAMING_FORMAT_180_24_0_5M:strId = STR_ID_NO_11631; break;
		default:
			break;
		}
	}
	else if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
		formatId = APL_PARAM_GET_DATA(AplParamNdiHxStreamingFormat);
		switch (formatId) {
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_24M:	strId = STR_ID_NO_11572; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_16M:	strId = STR_ID_NO_11574; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_10M:	strId = STR_ID_NO_11575; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_8M:	strId = STR_ID_NO_11576; break;

		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_24M:	strId = STR_ID_NO_11577; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_16M:	strId = STR_ID_NO_11579; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_10M:	strId = STR_ID_NO_11580; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_8M:	strId = STR_ID_NO_11581; break;

		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_14M:	strId = STR_ID_NO_11582; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_10M:	strId = STR_ID_NO_11583; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_6M:	strId = STR_ID_NO_11584; break;

		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_14M:	strId = STR_ID_NO_11586; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_10M:	strId = STR_ID_NO_11587; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_6M:	strId = STR_ID_NO_11588; break;

		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_14M:	strId = STR_ID_NO_11593; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_10M:	strId = STR_ID_NO_11594; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_6M:	strId = STR_ID_NO_11596; break;

		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_14M:	strId = STR_ID_NO_11598; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_10M:	strId = STR_ID_NO_11599; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_6M:	strId = STR_ID_NO_11601; break;

		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_8M:	strId = STR_ID_NO_11603; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_4M:	strId = STR_ID_NO_11604; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_2M:	strId = STR_ID_NO_11605; break;

		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_8M:	strId = STR_ID_NO_11607; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_4M:	strId = STR_ID_NO_11608; break;
		case APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_2M:	strId = STR_ID_NO_11609; break;
		default:
			break;
		}
	}
	else {
		return m_pStrmFormatLine->setVisible(false);
	}
	m_pStrmFormatLine->setVisible(true);
	m_pStrmFormat->setStringID(strId);
	return true;
}

bool CtModeCheckNetwork::updateStrmDataType() {
	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) != APL_SYS_PARAM_NETWORK_FUNC_STREAMING) {
		return m_pStrmDataTypeLine->setVisible(false);
	}
	m_pStrmDataTypeLine->setVisible(true);
	switch (APL_PARAM_GET_DATA(AplParamStreamingDataType)) {
	case APL_SYS_PARAM_STREAMING_DATA_TYPE_GENERAL:
		return m_pStrmDataType->setStringID(STR_ID_NO_11543);
		break;
	case APL_SYS_PARAM_STREAMING_DATA_TYPE_P2CAST:
		return m_pStrmDataType->setText("P2CAST");// Vup
		break;
	case APL_SYS_PARAM_STREAMING_DATA_TYPE_LIVEU:
		return m_pStrmDataType->setText("LIVEU");// Vup
		break;
	case APL_SYS_PARAM_STREAMING_DATA_TYPE_TVU:
		return m_pStrmDataType->setText("TVU");// Vup
		break;
	default:
		return false;
		break;
	}
}

bool CtModeCheckNetwork::updateIpRemote(int int_Data) {
	switch (int_Data) {
	case APL_SYS_PARAM_SWITCH_ON:
		return m_pIpRemote->setStringID(STR_ID_NO_11544);;
		break;
	case APL_SYS_PARAM_SWITCH_OFF:
		return m_pIpRemote->setStringID(STR_ID_NO_11545);;
		break;
	default:
		return false;
		break;
	}
}


bool CtModeCheckNetwork::updateIpAddress() {
	unsigned char Data[AplParamIpAddress_Size];
	unsigned char DataV6[AplParamIpAddressV6_Size];
	char str[AplParamIpAddressV6_Size];
	memset(str, 0, sizeof(str));
	switch (APL_PARAM_GET_DATA(AplParamNetworkDeviceSel)) {
	case APL_SYS_PARAM_NETWORK_DEVICE_SEL_OFF:
		break;
	case APL_SYS_PARAM_NETWORK_DEVICE_SEL_LAN:
		//AplParamLanIpAddress
		//AplParamLanIpAddressV6
		if (APL_PARAM_GET_DATA(AplParamLanEnableIPv6) == APL_SYS_PARAM_SWITCH_ON) {
			APL_PARAM_GET_DATA_AREA(AplParamLanIpAddressV6, DataV6, AplParamIpAddressV6_Size);
			sprintf(str, "%s", DataV6);
			return m_pIpAddress->setText(str);
		}
		else {
			APL_PARAM_GET_DATA_AREA(AplParamLanIpAddress, Data, AplParamIpAddress_Size);
			sprintf(str, "%d.%d.%d.%d", Data[0], Data[1], Data[2], Data[3]);
			return m_pIpAddress->setText(str);
		}
		break;
	case APL_SYS_PARAM_NETWORK_DEVICE_SEL_WLAN:
		//AplParamIpAddress
		//AplParamIpAddressV6
		if (APL_PARAM_GET_DATA(AplParamEnableIPv6) == APL_SYS_PARAM_SWITCH_ON) {
			APL_PARAM_GET_DATA_AREA(AplParamIpAddressV6, DataV6, AplParamIpAddressV6_Size);
			sprintf(str, "%s", DataV6);
			return m_pIpAddress->setText(str);
		}
		else {
			APL_PARAM_GET_DATA_AREA(AplParamIpAddress, Data, AplParamIpAddress_Size);
			sprintf(str, "%d.%d.%d.%d", Data[0], Data[1], Data[2], Data[3]);
			return m_pIpAddress->setText(str);
		}
		break;
	case APL_SYS_PARAM_NETWORK_DEVICE_SEL_CELLULAR:
		return m_pIpAddress->setText("");
		break;
	default:
		return m_pIpAddress->setText("");
		break;
	}
	return false;
}
