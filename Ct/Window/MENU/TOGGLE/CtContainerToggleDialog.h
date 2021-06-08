/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */


#ifndef __CtContainerToggleDialog_H__
#define __CtContainerToggleDialog_H__

#include "CtMenuInfoToggleDialog.h"
#include "CtMenuInfo.h"

#include "CtContainerCtrlButton.h"


class CtContainerToggleDialog : public CtContainer
{
/*** 定数 ***************************************/
public:
protected:
	typedef struct ToggleButton {
		CtButton*		Button;
		CtStackLabel*   Stack;
		int             Data;
		int             Max;
		int             offset;
	} ToggleButton;

	typedef CtVector::Vector<ToggleButton> ToggleList;

private:

/*** メソッド ***********************************/
public:
	CtContainerToggleDialog(CtWindowID id);
	virtual ~CtContainerToggleDialog();
	virtual bool destroyContainer();
	inline void setWindowID(CtWindowID id);

	virtual CtLayout* createContainer();

	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleKeyEvent(const CtEventKey& Key);

protected:
	virtual CtLayout* createLayout();
	virtual CtLayout* createTitle();
	virtual CtLayout* createToggle();

	virtual void executionUpdate();
	virtual bool executionSet();
	virtual bool executionUp();
	virtual bool executionDown();
	virtual bool executionRet();
	virtual bool executionReset();

	void executionCheckData();
	void executionPrintDebug();

private:

/*** メンバ   ***********************************/
public:

protected:
	CtWindowID      m_WindowID;
	ToggleList      m_Toggle;
	int             m_CurSelect;
	bool            m_bPressMmr;
private:

};

inline void CtContainerToggleDialog::setWindowID(CtWindowID id)
{
	m_WindowID = id;
}


#endif
