/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */


#ifndef __CtContainerKeyboard_H__
#define __CtContainerKeyboard_H__

#include "CtWindowCommon.h"
#include "CtKeyboardInfo.h"
#include "CtWindowContentsFileInfo.h"
#include "CtBuilderKeyboard.h"

class CtContainerKeyboard : public CtContainer
{
public:
	CtContainerKeyboard(CtWindowID id);
	CtContainerKeyboard(CtWindowID id, CtWindowContents* pContents);
	virtual ~CtContainerKeyboard();
	bool destroyContainer();

	CtLayout* createContainer();

	virtual bool startupContainer();

	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleKeyEvent(const CtEventKey& Key);
private:

	CtLayout* createLayout();

	void updateKeyBoard();
	
	bool checkAddressFormat();
	void setEnterValid();
	bool isValid();
	void pushEnter();
	void link();

protected:

public:
private:
	CtWindowID      m_WindowID;

	CtWindowContentsFileInfo* m_pFileContents;
	CtKeyboardInfo::CtKeyboardInfoItem* m_Info;

	CtTextField*    m_pText;
	CtStackLabel*	m_pKeyboard;

	CtToggleButton* m_pCaps;
	CtButton*       m_pBS;
	CtButton*       m_pRet;
	CtToggleButton* m_pKigou;
	CtButton*       m_pSpace;
	CtButton*       m_pLeft;
	CtButton*       m_pRight;
	CtButton*       m_pEnter;

protected:

};

#endif
