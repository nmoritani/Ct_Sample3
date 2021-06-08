/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMenuBuilder
 */

#include "CtMenuBuilder.h"
#include "string_api.h"
#include "CtWindowDecorate.h"

CtMenuBuilder::CtMenuBuilder():
	m_TotalWidth(0),
	m_LabelWidth(0),
	m_ValueWidth(0),
	m_bArrow(false)
{
	setClassType(CtClassType_Interface);
}

CtMenuBuilder::~CtMenuBuilder()
{
}

CtListView* CtMenuBuilder::createMenuList(int num, bool bExit)
{
	CtMenuListView* pList = new CtMenuListView(num);

	CtMenuInfo::CtMenuWindowInfo* pInfo = CtMenuInfo::getWindowInfo(m_WindowId);

	setWidthSize();

	int current = 0;

	if (bExit) {
		pList->addWidget(createExitButton(), AlignLeft);
	}

	if (pInfo != NULL) {
		for (unsigned int i = 0; i < pInfo->child.num; i++) {
			CtMenuInfo::CtMenuButtonInfo* pButtonInfo = CtMenuInfo::getButtonInfo(pInfo->child.id[i]);
			
			CtButton* pButton = createMenuButton(pButtonInfo);
			if (pButton == NULL) {
				break;
			}
			pList->addWidget(pButton);

			if (pInfo->type == CtMenuInfo::WINDOW_TYPE_CHECKLIST) {
				if (pButtonInfo->exclution.value == APL_PARAM_GET_DATA(pButtonInfo->exclution.id)) {
					current = i+1;
				}
			}
		}
	}
	pList->setCurrentElement(current);

	/* LeftKeyAction */
	{
		if (CtMenuInfo::getHierarchy(m_WindowId) == 1) {
			pList->setLeftKeyAction(false);
		}
	}

	CtDebugPrint(CtDbg, "MenuLayout  Label  Value  Arrow \n");
	CtDebugPrint(CtDbg, "             %3d    %3d    %3d  \n", m_LabelWidth, m_ValueWidth, (m_bArrow ? 30 : 0));

	return pList;
}

CtButton* CtMenuBuilder::createExitButton()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor::White);

	CtHLayout* pLayout = new CtHLayout();
	pLayout->addWidget(new CtLabel(CtLine(LeftLine, 2, CtColor::White)), AlignLeft, 15);
	{
		CtVLayout* pLabel = new CtVLayout();
		pLabel->addStretch(10);
		pLabel->addWidget(new CtLabel(STR_ID_NO_10124, fSet), 70);
		pLabel->addStretch(20);
		pLayout->addWidget(pLabel, m_LabelWidth);
	}
	pLayout->addWidget(new CtLabel(CtLine(RightLine, 2, CtColor::White)), AlignRight, 10);
	CtMenuButton* pButton = new CtMenuButton(AutoSize, pLayout, CtButton::Rect);
	pButton->setLinkAction(WindowNone, (CtEventWindow::WinCmd)Close, NULL);
	pButton->setRightKeyAction(false);
	return pButton;
}

CtButton* CtMenuBuilder::createMenuButton(CtMenuInfo::CtMenuButtonInfo* pButtonInfo)
{
	if (pButtonInfo == NULL)return NULL;

	CtLayout* pLayout = createMenuButtonLayout(pButtonInfo);

	CtMenuButton* pButton = NULL;
	/* Button */
	{
		if (pButtonInfo->action.Type == CtMenuInfo::CtMenuAction_Switch) {
			pButton = new CtMenuCheckButton(AutoSize, pLayout, CtButton::Rect);
		}
		else {
			pButton = new CtMenuButton(AutoSize, pLayout, CtButton::Rect);
		}
	}

	/* FuncAction */
	{
		if (pButtonInfo->action.FuncID != FuncID_MAX) {
			pButton->setFuncAction(pButtonInfo->action.FuncID);
		}
	}

	/* ParamAction */
	{
		if (pButtonInfo->action.ParamID != AplParamIdMax) {
			switch (pButtonInfo->action.Type) {
			case CtMenuInfo::CtMenuAction_Switch:
				((CtMenuCheckButton*)pButton)->setParamAction(CtMenuCheckButton::Default, pButtonInfo->action.ParamID);
				break;
			case CtMenuInfo::CtMenuAction_Confirm:
				// ‰½‚à‚µ‚È‚¢
				break;
			default:
				pButton->setParamAction(CtMenuButton::Default, pButtonInfo->action.ParamID, pButtonInfo->action.SubItem);
				break;
			}
		}
	}

	/* LinkAction */
	{
		if (pButtonInfo->action.WindowID != WindowID_MAX) {
			switch (pButtonInfo->action.Type) {
			case CtMenuInfo::CtMenuAction_Default:
			{
				CtWindowContentsMenuPos* pContents = new CtWindowContentsMenuPos(m_WindowId, m_TotalWidth, m_OldWidth);
				pButton->setLinkAction(pButtonInfo->action.WindowID, pButtonInfo->action.OpenType, pContents);
				break;
			}
			case CtMenuInfo::CtMenuAction_Confirm:
			{
				if (pButtonInfo->action.SubItem == APL_PARAM_GET_DATA(pButtonInfo->action.ParamID)) {
					pButton->setLinkAction(WindowNone, CtEventWindow::Close, NULL);
				}
				else {
					CtWindowContentsDialogParamSet* pContents = new CtWindowContentsDialogParamSet(m_WindowId, pButtonInfo->action.ParamID, pButtonInfo->action.SubItem);
					pButton->setLinkAction(pButtonInfo->action.WindowID, pButtonInfo->action.OpenType, pContents);
				}
				break;
			}
			default:
				pButton->setLinkAction(pButtonInfo->action.WindowID, pButtonInfo->action.OpenType, NULL);
				break;
			}
		}
	}

	/* Exclution */
	{
		pButton->setStateInfo(pButtonInfo->exclution.id, pButtonInfo->exclution.value);
	}

	/* RightkeyAction */
	{
		if (!CtMenuInfo::checkArrow(pButtonInfo)) {
			pButton->setRightKeyAction(false);
		}
	}

	/* NotFocus */
	{
		if (pButtonInfo->type & CtMenuInfo::MenuButton_NotButton) {
			pButton->setInvalid(true);
			pButton->setInvalidMenu(true);
			bool bThumb = CtWindowDecorate::isThumbnail();
			unsigned char Transmittance = bThumb ? 235 : 178;

			CtColor InvalidBaseColor = CtColor(0, 0, 0, Transmittance);
			CtColor InvalidStrokeColor = CtColor::Green;
			CtColor InvalidLabelColor = CtColor::NoColor;

			CtColor InvalidBaseColorBack = CtColor(0, 0, 0, Transmittance);
			CtColor InvalidStrokeColorBack = CtColor(0, 0, 0, Transmittance);
			CtColor InvalidLabelColorBack = CtColor(142, 142, 142, 255);

			pButton->setInvalidButtonColors(InvalidBaseColor, InvalidStrokeColor, InvalidLabelColor);
			pButton->setInvalidButtonBackColors(InvalidBaseColorBack, InvalidStrokeColorBack, InvalidLabelColorBack);

		}
	}

	return pButton;

}

CtLayout* CtMenuBuilder::createMenuButtonLayout(CtMenuInfo::CtMenuButtonInfo* pButtonInfo)
{
	if (pButtonInfo == NULL)return NULL;

	/* Layout\’z                                                                   */
	/*  |--|- 47 or 0 -|- LabelWidth ------i--|- ValueWidth or 0 -|- 30 or 0 -|--|  */
	/*  |15|           |                   i10|                   |           |10|  */
	/*  |  | CheckBox  |   Label           i  |   Value           |   Arrow   |  |  */
	/*  |__|___________|___________________i__|___________________|___________|__|  */

	CtHLayout* pLayout = new CtHLayout();

	/* Stretch */
	{
		pLayout->addStretch(15);
	}

	/* CheckBox */
	{
		if (pButtonInfo->type & CtMenuInfo::MenuButton_CheckBox) {
			CtParamIcon* pIcon = new CtParamIcon(CtSize(32,32), IC_MENU_CHECK, CtColor::White);
			pIcon->setParam(pButtonInfo->exclution.id, pButtonInfo->exclution.value);
			pLayout->addWidget(pIcon,32);
			pLayout->addStretch(15);
		}
	}

	/* Label */
	{
		CtVLayout* pLabel = new CtVLayout();
		const CtFontSet& fSet = CtMenuInfo::getLabelFont(pButtonInfo);

		pLabel->addStretch(MENU_POP_TOP);
		if (pButtonInfo->type & CtMenuInfo::MenuButton_ParamLabel) {
			CtParamLabel* pParamLabel = new CtParamLabel(pButtonInfo->value.id, fSet);
			pParamLabel->setLabelType(CtParamLabel::TypeStrings);
			pParamLabel->setForm(pButtonInfo->str);
//			pParamLabel->setFontSet(fSet);
			pLabel->addWidget(pParamLabel, AlignLeft, MENU_POP_LABEL);
		}
		else {
			if (pButtonInfo->StringId != STR_ID_MAX_SIZE) {
				pLabel->addWidget(new CtLabel(pButtonInfo->StringId, fSet), AlignLeft, MENU_POP_LABEL);
			}
			else {
				pLabel->addWidget(new CtLabel(pButtonInfo->str, fSet), AlignLeft, MENU_POP_LABEL);
			}
		}
		pLabel->addStretch(MENU_POP_BOTTOM);
		pLayout->addWidget(pLabel, AlignLeft, m_LabelWidth);
		pLayout->addStretch(10);
	}

	/* Value */
	{
		if (pButtonInfo->type & CtMenuInfo::MenuButton_Value) {
			CtLayout* pValue = createMenuButtonLayout_Value(pButtonInfo);
			pLayout->addWidget(pValue, AlignCenter, m_ValueWidth);
		}
		else {
			pLayout->addStretch(m_ValueWidth);
		}
	}

	/* Arrow */
	{
		if (m_bArrow == true) {
			if (CtMenuInfo::checkArrow(pButtonInfo)){
				pLayout->addWidget(new CtLabel(CtSize(20, 20), IC_MENU_ARROW), AlignRight,30);
			}
			else {
				pLayout->addStretch(30);
			}
		}
	}

	/* Stretch */
	{
		pLayout->addStretch(10);
	}

	CtLayout* pButton = new CtLayout();
	pButton->addWidget(pLayout);
	pButton->addWidget(new CtLabel(CtLine(RightLine, 2, CtColor::White)), AlignRight);
	pButton->addWidget(new CtLabel(CtLine(LeftLine, 2, CtColor::White)), AlignLeft);

	return pButton;

}
CtLayout* CtMenuBuilder::createMenuButtonLayout_Value(CtMenuInfo::CtMenuButtonInfo* pInfo)
{
	CtVLayout* pLayout = new CtVLayout();
	
	if (pInfo == NULL) { return pLayout; }

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);

	pLayout->addStretch(MENU_POP_VTOP);
	switch (pInfo->value.type & CtMenuInfo::ValueType_Mask){
	case CtMenuInfo::ValueType_StackLabel:
	{
		CtParamBox* pParamBox = new CtParamBox(pInfo->value.id);
		pParamBox->setLabelType(CtParamLabel::TypeStacked);
		CtMenuInfo::CtMenuWindowInfo* pWindowInfo = CtMenuInfo::getWindowInfo(pInfo->action.WindowID);
		if (pWindowInfo == NULL)return NULL;

		for (unsigned int i = 0; i < pWindowInfo->child.num; i++) {
			if (pWindowInfo->child.id[i] == 0) {
				break;
			}
			CtMenuInfo::CtMenuButtonInfo* pButtonInfo = CtMenuInfo::getButtonInfo(pWindowInfo->child.id[i]);
			if (pButtonInfo == NULL)break;

			fSet = CtMenuInfo::getValueFont(pButtonInfo);

			if (pButtonInfo->StringId != STR_ID_MAX_SIZE) {
				pParamBox->addLabel(pButtonInfo->StringId, fSet, pButtonInfo->exclution.value);
			}
			else {
				pParamBox->addLabel(pButtonInfo->str, fSet, pButtonInfo->exclution.value);
			}
		}
		pLayout->addWidget(pParamBox, MENU_POP_VLABEL);
		break;
	}
	case CtMenuInfo::ValueType_Number:
	{
		CtParamLabel* pParamLabel = new CtParamLabel(pInfo->value.id, fSet);
//		pParamLabel->setFontSet(fSet);
		if (pInfo->value.plus) {
			pParamLabel->setRange(-1,1);
		}
		pParamLabel->setCorrection(0, pInfo->value.coef);
		pParamLabel->setLabelType(CtParamLabel::TypeNumeric);
		pParamLabel->setForm(pInfo->value.suffix);

		pLayout->addWidget(pParamLabel, MENU_POP_VLABEL);
		break;
	}
	case CtMenuInfo::ValueType_String:
	{
		CtParamLabel* pParamLabel = new CtParamLabel(pInfo->value.id, fSet);
		pParamLabel->setLabelType(CtParamLabel::TypeStrings);
		pParamLabel->setForm(pInfo->value.suffix);
//		pParamLabel->setFontSet(fSet);

		pLayout->addWidget(pParamLabel, MENU_POP_VLABEL);
		break;
	}
	case CtMenuInfo::ValueType_Special:
	case CtMenuInfo::ValueType_Omit:
	{
		CtContainerSpecialLabel* pContainew = new CtContainerSpecialLabel(pInfo);
		pLayout->addContainer(pContainew, MENU_POP_VLABEL);
		break;
	}
	case CtMenuInfo::ValueType_IpAddress:
	{
		CtParamLabel* pParamLabel = new CtParamLabel(pInfo->value.id, fSet);
		pParamLabel->setLabelType(CtParamLabel::TypeIP);
		pParamLabel->setForm(pInfo->value.suffix);

		pLayout->addWidget(pParamLabel, MENU_POP_VLABEL);
		break;
	}
	case CtMenuInfo::ValueType_Unknown:
	default:
		break;
	}
	pLayout->addStretch(MENU_POP_VBOTTOM);

	return pLayout;
	
}

void CtMenuBuilder::setWidthSize()
{
	CtMenuInfo::getMenuSize(m_WindowId, m_LabelWidth, m_ValueWidth, m_bArrow);
	CtMenuInfo::CtMenuWindowInfo* pInfo = CtMenuInfo::getWindowInfo(m_WindowId);

	m_TotalWidth += m_LabelWidth == 0 ? 0 : m_LabelWidth;	/* pgr0351 */
	m_TotalWidth += m_ValueWidth == 0 ? 0 : m_ValueWidth;	/* pgr0351 */

	m_TotalWidth += 35;
	if (pInfo->type == CtMenuInfo::WINDOW_TYPE_CHECKLIST) {
		m_TotalWidth += 47;
	}


	if (m_bArrow) {
		m_TotalWidth += 40;
	}

}
