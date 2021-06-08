/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element: CtMenuButton
*/
#include "CtMenuButton.h"
#include "CtParamContents.h"
#include "CtEventInterface.h"
#include "CtHLayout.h"

#include "CtWindowDecorate.h"

void CtMenuButton::ctor()
{
	setClassType(CtClassType_MenuButton);

	m_bBack = false;
	m_bRightKeyAction = true;
	m_bInvalidMenu = false;
	m_ParamId = APL_PARAM_INVALID;
	m_SubItem = 0;
	m_SetParamId = APL_PARAM_INVALID;
	m_SetParamData = 0;
	m_WindowID = WindowID_MAX;
	m_OpenType = CtEventWindow::Close;
	m_FuncID = FuncID_MAX;
	m_ParamAction = Default;
	m_pParamBox = NULL;
	m_pContents = NULL;
	m_pFuncContents = NULL;

	bool bThumb = CtWindowDecorate::isThumbnail();
	unsigned char Transmittance   = bThumb ? 235 : 178;
	unsigned char InvalidLabel     = bThumb ? 70 : 120;
	unsigned char InvalidBackLabel = bThumb ? 65 : 90;

	BaseColor = CtColor(0, 0, 0, Transmittance);
	StrokeColor = CtColor::Green;
	LabelColor = CtColor::NoColor;

	FocusedBaseColor = CtColor(255, 216, 0, 255);
	FocusedStrokeColor = CtColor(255, 255, 255, 255);
	FocusedLabelColor = CtColor(0, 0, 0, 255);
	
	PressedBaseColor = CtColor(255, 216, 0, 255);
	PressedStrokeColor = CtColor(255, 255, 255, 255);
	PressedLabelColor = CtColor(0, 0, 0, 255);

	InvalidBaseColor = CtColor(0, 0, 0, Transmittance);
	InvalidStrokeColor = CtColor(0, 0, 0, Transmittance);
	InvalidLabelColor = CtColor(InvalidLabel, InvalidLabel, InvalidLabel, 255);

	BaseColorBack = CtColor(0, 0, 0, Transmittance);
	StrokeColorBack = CtColor(0, 0, 0, Transmittance);
	LabelColorBack = CtColor(142, 142, 142,255);

	FocusedBaseColorBack = CtColor(196, 176, 91, 255);
	FocusedStrokeColorBack = CtColor(142, 142, 142, 255);
	FocusedLabelColorBack = CtColor(0, 0, 0, 255);
	
	PressedBaseColorBack = CtColor(196, 176, 91, 255);
	PressedStrokeColorBack = CtColor(142, 142, 142, 255);
	PressedLabelColorBack = CtColor(0, 0, 0, 255);

	InvalidBaseColorBack = CtColor(0, 0, 0, Transmittance);
	InvalidStrokeColorBack = CtColor(0, 0, 0, Transmittance);
	InvalidLabelColorBack = CtColor(InvalidBackLabel, InvalidBackLabel, InvalidBackLabel, 255);

}

CtMenuButton::CtMenuButton(CtButton::Shape Shape) :
	CtButton(Shape)
{
	ctor();
}

CtMenuButton::CtMenuButton(const CtSize& Size, CtButton::Shape Shape) :
	CtButton(Size, Shape)
{
	ctor();
}

CtMenuButton::CtMenuButton(const CtRegion& Region, CtButton::Shape Shape) :
	CtButton(Region, Shape)
{
	ctor();
}

CtMenuButton::CtMenuButton(CtLabel * pLabel, CtButton::Shape Shape) :
	CtButton(pLabel, Shape)
{
	ctor();
}

CtMenuButton::CtMenuButton(CtLayout * pLayout, CtButton::Shape Shape) :
	CtButton(pLayout, Shape)
{
	ctor();
}

CtMenuButton::CtMenuButton(const CtSize & Size, CtLabel * pLabel, CtButton::Shape Shape) :
	CtButton(Size, pLabel, Shape)
{
	ctor();
}

CtMenuButton::CtMenuButton(const CtSize & Size, CtLayout * pLayout, CtButton::Shape Shape) :
	CtButton(Size, pLayout, Shape)
{
	ctor();
}

CtMenuButton::~CtMenuButton()
{
	if (m_pContents != NULL)	delete m_pContents;
	if (m_pFuncContents != NULL)	delete m_pFuncContents;
}

bool CtMenuButton::cancelFocus()
{
	bool bRet = false;
	
	bRet = CtButton::cancelFocus();
	
	if (m_pParamBox != NULL) {
		m_pParamBox->stopFlash();
		m_pParamBox = NULL;
	}
	return bRet;
}

bool CtMenuButton::onRelease()
{
	CtParamBox* pBox = NULL;
	
	CtButton::onRelease();
#if 1
	actionParam();
	actionFunction();
	actionLink();
	m_pParamBox = NULL;
#else
	if (m_pParamBox != NULL) {
		m_pParamBox->stopFlash();
	}
	if ((pBox = nextParamBox(m_pParamBox)) != NULL) {
		m_pParamBox = pBox;
		m_pParamBox->setWriteType(CtParamBox::None);
		m_pParamBox->startFlash(CtEventFlash::Freq_2Hz);
		
	} else {
		actionParam();
		actionFunction();
		actionLink();
		m_pParamBox = NULL;
	}
#endif	

	return true;
}


CtParamBox* CtMenuButton::nextParamBox(CtParamBox* pBox)
{
#if 0
	CtVector::Vector<CtWidget::Element*>* pElements = NULL;
	CtWidget* pNext = NULL;
	bool flag = false;

	if (((pElements = getElements()) == NULL) || (pElements->empty() == true))
		return NULL;
		
	for (int i = 0; i< pElements->size(); i++) {
		if ((*pElements)[i] == NULL) continue;
		if ((pNext = (*pElements)[i]->pWidget) == NULL) continue;
		
		if (pNext->isParamBox() == true) {
			if ((pBox == NULL) || (flag == true)) {
				return (CtParamBox*)pNext;
			}
			if (pBox == pNext) {
				flag = true;
			}
		}
	}
#endif
	return NULL;
}

bool CtMenuButton::handleParamEvent(const CtEventParam& Param)
{
	bool bRet = false;

	if (CtStackLabel::handleParamEvent(Param) == true)
		bRet = true;
	
	if (updateState() == true)		// State変化は自分で取らないとダメなので。。。
		bRet = true;
	
#if 0
	if ((m_pParamBox != NULL) &&
		(m_pParamBox->getParamID() == Param.getParamId()) &&
		(m_pParamBox->getParam() != Param.getParamVal())) {
		//		m_pParamBox->stopFlash();
		m_pParamBox = NULL;
		bRet = true;
	}
#endif	
	return bRet;
}

bool CtMenuButton::handleKeyEvent(const CtEventKey& Key)
{
	if (isFocused() != true) return false;
	if (isInvalid() == true) return false;
	
	if (CtButton::handleKeyEvent(Key) == true)
		return true;

	if (m_bRightKeyAction != true)
		return false;
	
	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_Right: {
		CtEventKey RightKey = CtEventKey(Key.getKeyAction(), CtEventKey::KeyCode_Enter, Key.getKeySource());
		return CtButton::handleKeyEvent(RightKey);
	}
	default:
		break;
	}
	
	return false;
}

void CtMenuButton::setStateInfo(const int ParamID, const int SubItem)
{
	m_ParamId = ParamID;
	m_SubItem = SubItem;

	updateState();
}

bool CtMenuButton::updateState()
{
	bool bRet = false;

	switch (getAttribute(m_ParamId, m_SubItem)) {
	case AttribInvalid:
		setVisible(true);
		setInvalid(true);
		bRet = true;
		break;
	case AttribInvisible:
		setVisible(false);
		setInvalid(false);
		bRet = true;
		break;
	case AttribVisible:
	default:
		setVisible(true);
		setInvalid(false);
		bRet = true;
		break;
	}
	return bRet;
}
		
void CtMenuButton::setParamAction(ParamAction Action)
{
	m_ParamAction = Action;
}

void CtMenuButton::setParamAction(ParamAction Action, const int ParamId, const int ParamData)
{
	m_ParamAction = Action;
	m_SetParamId = ParamId;
	m_SetParamData = ParamData;
}

CtMenuButton::Attribute CtMenuButton::getAttribute(int ParamId, int SubItem)
{
	AplParamService::AplParamMainItem* pMain = NULL;
	AplParamService::AplParamSubItem* pSub = NULL;
	
	if (ParamId == APL_PARAM_INVALID)
		return (m_bInvalidMenu != true) ? AttribVisible : AttribInvalid;
	
	if ((pMain = APL_PARAM()->getParamState(ParamId)) == NULL)
		return (m_bInvalidMenu != true) ? AttribVisible : AttribInvalid;

	switch (pMain->mState) {
	case AplParamState_VisibleValid:		/* 有効表示 */
		break;
	case AplParamState_VisibleInvalid:		/* 無効表示  */
		return AttribInvalid;
	case AplParamState_Invisible:			/* 非表示 */
		return AttribInvisible;
	default:
		break;
	}
	
	if (((pSub = pMain->sub_item) == NULL) || (SubItem == APL_PARAM_INVALID)) {
		return (m_bInvalidMenu != true) ? AttribVisible : AttribInvalid;
	}

	while (pSub->state != AplParamState_End) {
		if (pSub->value != SubItem) {
			pSub++;
			continue;
		}
		switch (pSub->state) {
		case AplParamState_VisibleValid:	
			return (m_bInvalidMenu != true) ? AttribVisible : AttribInvalid;
		case AplParamState_VisibleInvalid:
			return AttribInvalid;
		case AplParamState_Invisible:		
			return AttribInvisible;
		default:
			break;
		}
	}
		
	return (m_bInvalidMenu != true) ? AttribVisible : AttribInvalid;
}

bool CtMenuButton::actionParam()
{
	if (m_ParamAction == DontWrite)
		return false;
			
	if (m_pParamBox != NULL) {
		if ((m_ParamAction & EnterWrite) && (m_ParamAction & EnterCacheWrite)) {
			m_pParamBox->setParam(CtParamBox::All);
		} else if (m_ParamAction & EnterCacheWrite) {
			m_pParamBox->setParam(CtParamBox::Cache);
		} else if (m_ParamAction & EnterMasterWrite) {
			m_pParamBox->setParam(CtParamBox::Master);
		} else {
			return false;
		}
		
	} else if (m_SetParamId != APL_PARAM_INVALID) {
		if ((m_ParamAction & EnterWrite) && (m_ParamAction & EnterCacheWrite)) {
			APL_PARAM_SET_DATA(m_SetParamId, m_SetParamData);
		} else if (m_ParamAction & EnterCacheWrite) {
			APL_PARAM_SET_CACHE_DATA(m_SetParamId, m_SetParamData);
		} else if (m_ParamAction & EnterMasterWrite) {
			APL_PARAM_SET_MASTER_DATA(m_SetParamId, m_SetParamData);
		} else {
			return false;
		}
	}
	return true;
}

bool CtMenuButton::actionFunction()
{
	if (m_FuncID >= FuncID_MAX)
		return false;

	CtWindow * pWindow = getWindow();

	if (pWindow == NULL)
		return false;

	CtScreenSel Sel = pWindow->getScreenSel();
	CtWindowID winId = pWindow->getWindowID();
	
	if ((m_pParamBox != NULL) && (m_ParamAction == DontWrite)) {
		CtParamContents contents(m_WindowID,(AplParamEepromId)m_pParamBox->getParamID(), m_pParamBox->getParam());
		CtEventInterface::requestFuncCmd(Sel, winId, m_FuncID, &contents);
	}
	else if (m_pFuncContents != NULL) {
		CtEventInterface::requestFuncCmd(Sel, winId, m_FuncID, m_pFuncContents);
	}
	else {
		CtEventInterface::requestFuncCmd(Sel, winId, m_FuncID, NULL);
	}
	return false;
}

bool CtMenuButton::actionLink()
{
#if 1
	if (m_WindowID == WindowID_MAX)
		return false;
#endif
	
	CtWindow * pWindow = getWindow();

	if (pWindow == NULL)
		return false;

	CtScreenSel Sel = pWindow->getScreenSel();
	
	if ((m_pParamBox != NULL) && (m_ParamAction == DontWrite)) {
		if (m_pParamBox->isEdited() == true) {
			if (m_pContents == NULL) {
				CtParamContents contents(m_WindowID,(AplParamEepromId)m_pParamBox->getParamID(), m_pParamBox->getParam());
				CtEventInterface::requestWindowCmd(m_OpenType, Sel, m_WindowID, &contents, NULL, true);
			} else {
				CtEventInterface::requestWindowCmd(m_OpenType, Sel, m_WindowID, m_pContents, NULL, true);
			}
		}
	} else {
		CtEventInterface::requestWindowCmd(m_OpenType, Sel, m_WindowID, m_pContents, NULL, true);
	}
	
	return false;
}

bool CtMenuButton::setBack(bool bBack)
{
	bool bRet = false;
	
	if (m_bBack == bBack)
		return bRet;
	
	m_bBack = bBack;

	switch (m_State) {
	case StateNormal:
	case StateSilentFocused:
		if (styleNormal() == true)
			bRet = true;
		break;
	case StateFocused:
		if (styleFocused() == true)
			bRet = true;
		break;
	case StatePressed:
		if (stylePressed() == true)
			bRet = true;
		break;
	case StateInvalid:
		if (styleInvalid() == true)
			bRet = true;
		break;
	default:
		break;
	}
	
	return bRet;
}

bool CtMenuButton::styleNormal()
{
	setStroke(0);
	
	if (isBack() != true)
		return CtButton::styleNormal();

	return setColors(BaseColorBack, StrokeColorBack, LabelColorBack, LabelColorBack);
}

bool CtMenuButton::styleFocused()
{
	setStroke(BaseStrokeWidth);
	
	if (isBack() != true)
		return CtButton::styleFocused();

	return setColors(FocusedBaseColorBack, FocusedStrokeColorBack, FocusedLabelColorBack, FocusedStrokeColorBack);
}

bool CtMenuButton::stylePressed()
{
	setStroke(BaseStrokeWidth);
	
	if (isBack() != true)
		return CtButton::stylePressed();

	return setColors(PressedBaseColorBack, PressedStrokeColorBack, PressedLabelColorBack, PressedStrokeColorBack);
}

bool CtMenuButton::styleInvalid()
{
	setStroke(0);
	
	if (isBack() != true)
		return CtButton::styleInvalid();

	return setColors(InvalidBaseColorBack, InvalidStrokeColorBack, InvalidLabelColorBack, LabelColorBack);
}

bool CtMenuButton::setButtonBackColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke)
{
	this->BaseColorBack = Base;
	this->StrokeColorBack = Stroke;
	this->LabelColorBack = Label;
	return true;
}
bool CtMenuButton::setFocusedButtonBackColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke)
{
	this->FocusedBaseColorBack = Base;
	this->FocusedStrokeColorBack = Stroke;
	this->FocusedLabelColorBack = Label;
	return true;
}
bool CtMenuButton::setPressedButtonBackColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke)
{
	this->PressedBaseColorBack = Base;
	this->PressedStrokeColorBack = Stroke;
	this->PressedLabelColorBack = Label;
	return true;
}
bool CtMenuButton::setInvalidButtonBackColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke)
{
	this->InvalidBaseColorBack = Base;
	this->InvalidStrokeColorBack = Stroke;
	this->InvalidLabelColorBack = Label;
	return true;
}
