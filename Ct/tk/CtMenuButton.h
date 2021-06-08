/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtTextMenuButton
*/


#ifndef __CtMenuButton_H__
#define __CtMenuButton_H__

#include "CtButton.h"
#include "CtParamBox.h"
#include "CtWindow.h"
#include "CtWindowContents.h"
#include "CtEvent.h"


// ParamAction
//  Default: editÇ™Cache, enterÇ™Master
//  DontWrite: editÇ‡enterÇ‡èëÇ©Ç»Ç¢

class CtMenuButton : public CtButton {
public:
	enum ParamAction {
		DontWrite = 0x00,
		EditCacheWrite = 0x01,
		EditMasterWrite = 0x02,
		EnterCacheWrite = 0x10,
		EnterMasterWrite = 0x20,
		EditWrite = EditCacheWrite,
		EnterWrite = EnterMasterWrite,
		Default = 0x31
	};
	enum Attribute {
		AttribVisible,
		AttribInvisible,
		AttribInvalid,
	};

	CtMenuButton(CtButton::Shape Shape);
	CtMenuButton(const CtSize& Size, CtButton::Shape Shape = RoundRect);
	CtMenuButton(const CtRegion& Region, CtButton::Shape Shape = RoundRect);
	CtMenuButton(CtLabel *pLabel, CtButton::Shape Shape = RoundRect);
    CtMenuButton(CtLayout *pLayout, CtButton::Shape Shape = RoundRect);
	CtMenuButton(const CtSize& Size, CtLabel *pLabel, CtButton::Shape Shape = RoundRect);
    CtMenuButton(const CtSize& Size, CtLayout *pLayout, CtButton::Shape Shape = RoundRect);
	virtual ~CtMenuButton();
	
	void setStateInfo(const int ParamID, const int SubItem);
	void setParamAction(ParamAction Action);
	void setParamAction(ParamAction Action, const int ParamID, const int ParamData);
	void setFuncAction(CtFuncID _id, CtWindowContents* pContents = NULL);
	void setLinkAction(CtWindowID WindowID, CtEventWindow::WinCmd OpenType, CtWindowContents* pContents = NULL);
	void setInvalidMenu(bool bInbalid);

	void setRightKeyAction(bool bValid);
	
	bool isBack() const;
	bool setBack(bool bBack);

	bool isMenuButton() const;

	bool setButtonBackColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke = CtColor::NoColor);
	bool setFocusedButtonBackColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke = CtColor::NoColor);
	bool setPressedButtonBackColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke = CtColor::NoColor);
	bool setInvalidButtonBackColors(const CtColor& Base, const CtColor& Stroke, const CtColor& Label, const CtColor& LabelStroke = CtColor::NoColor);

	
protected:
	bool handleKeyEvent(const CtEventKey& Key);
	bool handleParamEvent(const CtEventParam& Param);
	bool cancelFocus();
	bool onRelease();

	CtParamBox* nextParamBox(CtParamBox *pBox);
	Attribute getAttribute(int ParamId, int SubItem);
	
	bool styleNormal();
	bool styleFocused();
	bool stylePressed();
	bool styleInvalid();

	void ctor();
	bool updateState();
	
	int						m_SetParamId;
	int						m_SetParamData;
	
	virtual bool actionParam();
	virtual bool actionFunction();
	virtual bool actionLink();
	
	bool					m_bBack;
	bool					m_bRightKeyAction;
	bool                    m_bInvalidMenu;
	int						m_ParamId;
	int						m_SubItem;
	
	CtWindowID				m_WindowID;
	CtEventWindow::WinCmd	m_OpenType;
	CtWindowContents*		m_pContents;
	CtFuncID				m_FuncID;
	CtWindowContents*		m_pFuncContents;
	ParamAction				m_ParamAction;

	CtParamBox*				m_pParamBox;

private:
	CtColor 		BaseColorBack;
	CtColor 		StrokeColorBack;
	CtColor 		LabelColorBack;
	
	CtColor 		FocusedBaseColorBack;
	CtColor 		FocusedStrokeColorBack;
	CtColor 		FocusedLabelColorBack;
	
	CtColor 		PressedBaseColorBack;
	CtColor 		PressedStrokeColorBack;
	CtColor 		PressedLabelColorBack;

	CtColor 		InvalidBaseColorBack;
	CtColor 		InvalidStrokeColorBack;
	CtColor 		InvalidLabelColorBack;

};

inline bool CtMenuButton::isBack() const
{
	return m_bBack;
}

inline void CtMenuButton::setFuncAction(CtFuncID _id, CtWindowContents* pContents)
{
	m_FuncID = _id;
	m_pFuncContents = pContents;
}

inline void CtMenuButton::setLinkAction(CtWindowID WindowID, CtEventWindow::WinCmd OpenType, CtWindowContents* pContents)
{
	m_WindowID = WindowID;
	m_OpenType = OpenType;
	m_pContents = pContents;
}

inline void CtMenuButton::setRightKeyAction(bool bValid)
{
	m_bRightKeyAction = bValid;
}

inline bool CtMenuButton::isMenuButton() const
{
	return true;
}

inline void CtMenuButton::setInvalidMenu(bool bInbalid)
{
	m_bInvalidMenu = bInbalid;
}

#endif
