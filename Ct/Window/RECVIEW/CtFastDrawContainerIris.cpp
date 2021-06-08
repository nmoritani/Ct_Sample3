/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtFastDrawContainerIris
 */
#include "CtFastDrawContainerIris.h"
#include <stdlib.h>

#ifdef WIN32_GUI_SIM
static int m_value = 0;
#endif

CtFastDrawContainerIris::CtFastDrawContainerIris()
{
	setClassType(CtClassType_LayoutMain);
	memset(m_pLabel, 0, sizeof(m_pLabel));
}

CtLayout* CtFastDrawContainerIris::createContainer()
{
	m_pAll = new CtHLayout();
	m_pAutoIris = new CtLabel();
	m_pAll->addWidget(m_pAutoIris, 4);

	const char* OpenChars = "OPEN";
	const char* CloseChars = "CLOSE";

	for (int i = 0; i < IrisDigit; i++) {
		m_pLabel[i] = new CtStackLabel();
		m_pLabel[i]->setFastDraw(true);

		char pText[IrisParts_Max+1] = "0123456789F.-+ **";

		CtRecViewFontSet fSet = CtRecViewFontSet();

		pText[IrisParts_Close] = (i < CloseDigit) ? CloseChars[i] : NULL;	/* pgr0351 */// 先頭5桁は "CLOSE" を追加
		pText[IrisParts_Open] = (i < OpenDigit) ? OpenChars[i] : NULL;		/* pgr0351 */// 先頭4桁は "OPEN" を追加

		m_pLabel[i]->addLabels(pText, fSet);

		m_pAll->addWidget(m_pLabel[i], 1);
		m_pLabel[i]->index(IrisParts_Space);
	}
	// 起動時のちら見え対策
	//m_pAll->setVisible(false);

	return m_pAll;
}

bool CtFastDrawContainerIris::destroyContainer()
{
	return true;
}

CtFastDrawContainerIris::~CtFastDrawContainerIris() {}

bool CtFastDrawContainerIris::startupContainer() {
	m_IrisLensValid = APL_PARAM_GET_DATA(AplParamIrisLensValid) == APL_SYS_PARAM_SWITCH_ON;
	m_AutoIrisLevel = APL_PARAM_GET_DATA(AplParamAutoIrisLevelEffectAdjust);/* pgr0351 */
	m_bAutoIrisDisp = APL_PARAM_GET_DATA(AplParamSceneAutoIrisLevel) == APL_SYS_PARAM_SWITCH_ON;
	m_Type = getDispMode();
	return updateAutoIrisIcon();
}

bool CtFastDrawContainerIris::handleParamEvent(const CtEventParam& Param) {
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();
	if (t_Id == AplParamAutoIrisDispMode
		|| t_Id == AplParamIrisLensValid) {
		return updateAutoIrisIcon();
	}
	else if (t_Id == AplParamAutoIrisLevelEffectAdjust) {
		m_AutoIrisLevel = int_Data;/* pgr0351 */
	}
	else if (t_Id == AplParamSceneAutoIrisLevel) {
		m_bAutoIrisDisp = (int_Data == APL_SYS_PARAM_SWITCH_ON);
	}
	else if (t_Id == AplParamIRRec) {
		return updateAutoIrisIcon();
	}

	return false;
}

bool CtFastDrawContainerIris::updateFastDraw()
{
	IrisDispType prev_type = m_Type;
	m_Type = getDispMode();

#ifdef WIN32_GUI_SIM
	m_value++;
	if (m_value > 0xFFFF) {
		m_value = 0;
	}
	int value = m_value;
#else
	int value = APL_PARAM_GET_DATA(AplParamIrisVal);
#endif
	int rank_100, rank_10, rank_1;

	/* 10の位 */
	rank_100 = value / 100;
	rank_100 = rank_100 % 10;

	/* 1の位 */
	rank_10 = value / 10;
	rank_10 = rank_10 % 10;

	/* 少数点以下の位 */
	rank_1 = value % 10;

	/* Open表示 */
	if (m_Type == IrisDispType_Open) {
		for (int i = 0; i < IrisDigit; i++) {
			m_pLabel[i]->index((i < OpenDigit) ? IrisParts_Open : IrisParts_Space);
		}
		/* CLOSE 表示*/
	}
	else if (m_Type == IrisDispType_Close) {
		for (int i = 0; i < IrisDigit; i++) {
			m_pLabel[i]->index((i < CloseDigit) ? IrisParts_Close : IrisParts_Space);
		}
		/* 消去 */
	}
	else if (m_Type == IrisDispType_Nodisp) {
		for (int i = 0; i < IrisDigit; i++) {
			m_pLabel[i]->index(IrisParts_Space);
		}
	}
	else {
		int i = 0;
		/* F(左寄せ) */
		if (rank_100 != 0) {
			// 2桁のみ
			m_pLabel[i++]->index(IrisParts_F);
			m_pLabel[i++]->index(rank_100);
			m_pLabel[i++]->index(rank_10);
			m_pLabel[i++]->index(IrisParts_Space);
		}
		else {
			// 整数部小数部の第1位
			m_pLabel[i++]->index(IrisParts_F);
			m_pLabel[i++]->index(rank_10);
			m_pLabel[i++]->index(IrisParts_dot);
			m_pLabel[i++]->index(rank_1);
		}
		/* Auto */
		if (m_Type == IrisDispType_Auto) {
			// AutoIris目標値 右詰
			//AplParamSceneAutoIrisLevelEffectAdjust
			if (m_bAutoIrisDisp) {
				IrisPartsNumber Num_10 = (IrisPartsNumber)abs(m_AutoIrisLevel / 10);
				IrisPartsNumber Num_1 = (IrisPartsNumber)abs(m_AutoIrisLevel % 10);

				if (m_AutoIrisLevel < 0) {
					if (Num_10 == 0) {
						m_pLabel[i++]->index(IrisParts_Space);
						m_pLabel[i++]->index(IrisParts_Minus);
					}
					else {
						m_pLabel[i++]->index(IrisParts_Minus);
						m_pLabel[i++]->index(Num_10);
					}
					m_pLabel[i++]->index(Num_1);
					
				}else if(m_AutoIrisLevel == 0){
					m_pLabel[i++]->index(IrisParts_Space);
					m_pLabel[i++]->index(IrisParts_Space);
					m_pLabel[i++]->index(Num_1);
				}
				else {
					if (Num_10 == 0) {
						m_pLabel[i++]->index(IrisParts_Space);
						m_pLabel[i++]->index(IrisParts_Plus);
					}
					else {
						m_pLabel[i++]->index(IrisParts_Plus);
						m_pLabel[i++]->index(Num_10);
					}
					m_pLabel[i++]->index(Num_1);
				}
			}
			else {
				m_pLabel[i++]->index(IrisParts_Space);
				m_pLabel[i++]->index(IrisParts_Space);
				m_pLabel[i++]->index(IrisParts_Space);
			}
		}

		for (int padding = i; padding < IrisDigit; padding++) {
			m_pLabel[padding]->index(IrisParts_Space);
		}
	}

	return true;
}

CtFastDrawContainerIris::IrisDispType CtFastDrawContainerIris::getDispMode()
{
	IrisDispType type = IrisDispType_Max;

#ifdef WIN32_GUI_SIM
	if (m_IrisLensValid) {
		type = IrisDispType_Nodisp;
	}
	else {
		switch (m_value) {
		case 0xFFFF:
			type = IrisDispType_Close;
			break;
		case 0xFFFE:
			type = IrisDispType_Nodisp;
			break;
		case 0x0000:
			type = IrisDispType_Open;
			break;
		default:
			if (APL_PARAM_GET_DATA(AplParamAutoIrisDispMode) != APL_SYS_PARAM_AUTO_IRIS_MODE_OFF) {
				type = IrisDispType_Auto;
			}
			else {
				type = IrisDispType_Manual;
			}
			break;
		}
	}
#else

	if (m_IrisLensValid) {
		type = IrisDispType_Nodisp;
	}
	else {
		switch (APL_PARAM_GET_DATA(AplParamIrisVal)) {
		case 0xFFFF:
			type = IrisDispType_Close;
			break;
		case 0xFFFE:
			type = IrisDispType_Nodisp;
			break;
		case 0x0000:
			type = IrisDispType_Open;
			break;
		default:
			if (APL_PARAM_GET_DATA(AplParamAutoIrisDispMode) != APL_SYS_PARAM_AUTO_IRIS_MODE_OFF) {
				type = IrisDispType_Auto;
			}
			else {
				type = IrisDispType_Manual;
			}
			break;
		}
	}
#endif
	return type;
}
bool CtFastDrawContainerIris::updateAutoIrisIcon() {
	bool bDisp = true, bUpdate = false;
	switch (APL_PARAM_GET_DATA(AplParamAutoIrisDispMode))
	{
	case APL_SYS_PARAM_AUTO_IRIS_MODE_OFF:
		bDisp = false;
		break;
	case APL_SYS_PARAM_AUTO_IRIS_MODE_STD:
		bUpdate = m_pAutoIris->setImage(IC_OSD_A_IRIS_STD);
		break;
	case APL_SYS_PARAM_AUTO_IRIS_MODE_BACK:
		bUpdate = m_pAutoIris->setImage(IC_OSD_A_IRIS_BACK);
		break;
	case APL_SYS_PARAM_AUTO_IRIS_MODE_SPOT:
		bUpdate = m_pAutoIris->setImage(IC_OSD_A_IRIS_SPOT);
		break;
	default:
		break;
	}
	if (APL_PARAM_GET_DATA(AplParamIrisLensValid) == APL_SYS_PARAM_SWITCH_OFF) {
		m_IrisLensValid = true;
		bDisp = false;
	}
	else {
		m_IrisLensValid = false;
	}
	if (APL_PARAM_GET_DATA(AplParamIRRec) == APL_SYS_PARAM_SWITCH_ON) {
		bDisp = false;
	}
	bUpdate |= m_pAutoIris->setVisible(bDisp);/* pgr2711 */
	return bUpdate;
}
