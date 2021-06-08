
#include "CtContainerSpecialLabel.h"


CtContainerSpecialLabel::CtContainerSpecialLabel(CtMenuInfo::CtMenuButtonInfo* pInfo):
	m_pLabel(NULL),
	m_pLayout(NULL),
	m_pStack(NULL),
	m_pInfo(pInfo)
{
}
CtContainerSpecialLabel::~CtContainerSpecialLabel()
{
	destroyContainer();
}
bool CtContainerSpecialLabel::destroyContainer()
{
	return true;
}

CtLayout* CtContainerSpecialLabel::createContainer()
{
	CtLayout* pLabel =  createLabel();

	CtLayout *pLayout = new CtLayout();
	pLayout->addWidget(pLabel);

	return pLayout;
}
bool CtContainerSpecialLabel::handleParamEvent(const CtEventParam& Param)
{
	bool bRet = false;
	int t_Id = Param.getParamId();

	switch (t_Id) {
	case AplParamDisplayIndicatorAllHide:
	case AplParamDisplayIndicatorMarker:
	case AplParamDisplayIndicatorTextMemo:
	case AplParamDisplayIndicatorProxy:
	{
		bRet = updateLabel_Indicator();
		break;
	}
	case AplParamSceneMode:
		bRet = updateLabel_FileSelect();
		break;
	case AplParamSceneChromaLevel:
		bRet = updateLabel_ChromaLevel();
		break;
	case AplParamSceneSyncScanType:
	case AplParamSceneSyncScanSecValue:
	case AplParamSceneSyncScanDegValue:
		bRet = updateLabel_SynchroScan();
		break;
	default:
		if (m_pInfo->value.id == t_Id) {
			if ((m_pInfo->value.type & CtMenuInfo::ValueType_Mask) == CtMenuInfo::ValueType_Omit) {
				bRet = updateLabel_Omit();
			}
		}
		break;
	}
	return bRet;
}

CtLayout* CtContainerSpecialLabel::createLabel()
{
	CtLayout* pLayout = new CtLayout();
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);

	if ((m_pInfo->value.type & CtMenuInfo::ValueType_Mask ) == CtMenuInfo::ValueType_Omit) {
		m_pLabel = new CtLabel("", fSet);
		pLayout->addWidget(m_pLabel);
		updateLabel_Omit();
		return pLayout;
	}



	switch (m_pInfo->exclution.id){
	case AplParamThumbDisplayMenu:
		switch (m_pInfo->exclution.value) {
		case APL_SYS_PARAM_THUMB_DISPLAY_MENU_INDICATOR:
			fSet.setLanguageId(CtLanguage::getLanguageID());
			m_pLabel = new CtLabel("", fSet);
			pLayout->addWidget(m_pLabel);
			updateLabel_Indicator();
			break;
		default:
			break;
		}
		break;
	case AplParamSceneFileMenu:
		switch (m_pInfo->exclution.value) {
		case APL_SYS_PARAM_SCENE_FILE_MENU_SELECT:
		{
			m_pStack = new CtStackLabel();

			CtMenuInfo::CtMenuWindowInfo* pWindowInfo = CtMenuInfo::getWindowInfo(m_pInfo->action.WindowID);
			if (pWindowInfo == NULL)return NULL;

			for (unsigned int i = 0; i < pWindowInfo->child.num; i++) {
				if (pWindowInfo->child.id[i] == 0) {
					break;
				}
				CtMenuInfo::CtMenuButtonInfo* pButtonInfo = CtMenuInfo::getButtonInfo(pWindowInfo->child.id[i]);
				if (pButtonInfo == NULL)break;

				// 設定値はAplParamSceneFileName固定で行う（シーンごとのAplParamはUpdate更新が来ない）
				CtParamLabel* pParamLabel = new CtParamLabel(AplParamSceneFileName, fSet);
				pParamLabel->setLabelType(CtParamLabel::TypeStrings);
				pParamLabel->setForm(pButtonInfo->str);
//				pParamLabel->setFontSet(fSet);
				m_pStack->addLabel(pParamLabel, CtMargin(0), AlignLeft, pButtonInfo->exclution.value);
			}
			pLayout->addWidget(m_pStack);
			updateLabel_FileSelect();
			break;
		}
		case APL_SYS_PARAM_SCENE_FILE_MENU_SYNC_SCAN:
		{
			CtParamLabel* pParamLabel = NULL;
			m_pStack = new CtStackLabel();

			pParamLabel = new CtParamLabel(AplParamSceneSyncScanSecValue, fSet);
			pParamLabel->setLabelType(CtParamLabel::TypeNumeric);
			pParamLabel->setForm("1/%.1f");
			pParamLabel->setCorrection(0, 0.1F);
			//			pParamLabel->setFontSet(fSet);
			m_pStack->addLabel(pParamLabel, 0);

			pParamLabel = new CtParamLabel(AplParamSceneSyncScanDegValue, fSet);
			pParamLabel->setLabelType(CtParamLabel::TypeNumeric);
			pParamLabel->setForm("%0.1fd");
			pParamLabel->setCorrection(0, 0.1F);
//			pParamLabel->setFontSet(fSet);
			m_pStack->addLabel(pParamLabel, 1);

			pLayout->addWidget(m_pStack);
			updateLabel_SynchroScan();

			break;
		}
		case APL_SYS_PARAM_SCENE_FILE_MENU_CHROMA_LEVEL: {
			CtParamLabel* pLabel = new CtParamLabel(m_pInfo->value.id, fSet);
			pLabel->setLabelType(CtParamLabel::TypeNumeric);
//			pLabel->setFontSet(fSet);
			pLabel->setRange(-1, 1);
			pLabel->setCorrection(0, m_pInfo->value.coef);
			pLabel->setForm(m_pInfo->value.suffix);

			m_pStack = new CtStackLabel();
			m_pStack->addLabel(pLabel, 0);
			m_pStack->addLabel(new CtLabel(STR_ID_NO_10009, fSet), 1);

			pLayout->addWidget(m_pStack);

			updateLabel_ChromaLevel();
			break;
		}
		default:
			break;
		}
		break;
	default:
		break;
	}
	return pLayout;
}

bool CtContainerSpecialLabel::updateLabel_Omit()
{
	char dat[520] = { NULL };
	char str[20] = { NULL };
	int s_count = 0;
	AplParamService::AplParamMainItem* AplParamItem = NULL;
	if ((AplParamItem = APL_PARAM()->getParamState(m_pInfo->value.id)) != NULL) {
		APL_PARAM_GET_DATA_AREA(m_pInfo->value.id, (unsigned char*)dat, AplParamItem->size);

		for (int len = 0; dat[len]; len++) {
			if (len >= 15) {                /* pgr0360 */
				str[s_count++] = '.';
				str[s_count++] = '.';
				str[s_count++] = '.';
				break;
			}
			str[s_count++] = dat[len];
		}
		str[s_count++] = '\0';
	}
	m_pLabel->setText(str);

	return true;
}
bool CtContainerSpecialLabel::updateLabel_Indicator()
{
	if (m_pInfo->exclution.id != AplParamThumbDisplayMenu || m_pInfo->exclution.value != APL_SYS_PARAM_THUMB_DISPLAY_MENU_INDICATOR) return false;

	bool indicator1 = (APL_PARAM_GET_DATA(AplParamDisplayIndicatorAllHide) == APL_SYS_PARAM_SWITCH_ON);
	bool indicator2 = (APL_PARAM_GET_DATA(AplParamDisplayIndicatorMarker) == APL_SYS_PARAM_SWITCH_ON);
	bool indicator3 = (APL_PARAM_GET_DATA(AplParamDisplayIndicatorTextMemo) == APL_SYS_PARAM_SWITCH_ON);
	bool indicator4 = (APL_PARAM_GET_DATA(AplParamDisplayIndicatorProxy) == APL_SYS_PARAM_SWITCH_ON);

	if (indicator1) {
		m_pLabel->setStringID(STR_ID_NO_11012);
	}
	else {
		if (indicator2) {
			if (indicator3 || indicator4) {
				int s_count = 0;
				unsigned short str[200] = { 0 };
				const unsigned short *pStr = GDI_GetString(CtLanguage::getLanguageID(), STR_ID_NO_11013);
				if (pStr != NULL) {
					for (int len = 0; pStr[len]; len++) {
						str[s_count++] = pStr[len];
					}
					str[s_count++] = ',';
					str[s_count++] = ' ';
					for (int len = 0; len < 3; len++) {
						str[s_count++] = '.';
					}
				}

				m_pLabel->setText(str);
			}
			else {
				m_pLabel->setStringID(STR_ID_NO_11013);
			}
		}
		else if (indicator3) {
			if (indicator4) {
				int s_count = 0;
				unsigned short str[200] = { 0 };
				const unsigned short *pStr = GDI_GetString(CtLanguage::getLanguageID(), STR_ID_NO_11004);
				if (pStr != NULL) {
					for (int len = 0; pStr[len]; len++) {
						str[s_count++] = pStr[len];
					}
					str[s_count++] = ',';
					str[s_count++] = ' ';
					for (int len = 0; len < 3; len++) {
						str[s_count++] = '.';
					}
				}
				m_pLabel->setText(str);
			}
			else {
				m_pLabel->setStringID(STR_ID_NO_11004);
			}
		}
		else if (indicator4) {
			m_pLabel->setStringID(STR_ID_NO_11014);
		}
		else {
			m_pLabel->setText("---");
		}
	}

	return true;
}
bool CtContainerSpecialLabel::updateLabel_ChromaLevel()
{
	if (m_pInfo->exclution.id != AplParamSceneFileMenu || m_pInfo->exclution.value != APL_SYS_PARAM_SCENE_FILE_MENU_CHROMA_LEVEL) return false;

	signed char value = APL_PARAM_GET_DATA(AplParamSceneChromaLevel);

	if (value == -100) {
		m_pStack->index(1);
	}
	else {
		m_pStack->index(0);
	}

	return true;
}
bool CtContainerSpecialLabel::updateLabel_FileSelect()
{
	if (m_pInfo->exclution.id != AplParamSceneFileMenu || m_pInfo->exclution.value != APL_SYS_PARAM_SCENE_FILE_MENU_SELECT) return false;

	int value = APL_PARAM_GET_DATA(AplParamSceneMode);

	m_pStack->index(value);

	return true;
}
bool CtContainerSpecialLabel::updateLabel_SynchroScan()
{
	if (m_pInfo->exclution.id != AplParamSceneFileMenu || m_pInfo->exclution.value != APL_SYS_PARAM_SCENE_FILE_MENU_SYNC_SCAN) return false;

	int value = APL_PARAM_GET_DATA(AplParamSceneSyncScanType);

	if (value == APL_SYS_PARAM_SYNC_SCAN_TYPE_SEC) {
		m_pStack->index(0);
	}
	else {
		m_pStack->index(1);
	}
	return true;
}
