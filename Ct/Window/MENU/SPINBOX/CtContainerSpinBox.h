/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */


#ifndef __CtContainerSpinBox_H__
#define __CtContainerSpinBox_H__

//#include "CtWindow.h"
#include "CtMenuInfoSpinBox.h"
#include "CtParamBox.h"
#include "CtContainerLevelBar.h"
#include "CtContainerCtrlButton.h"
#include "CtContainerMenuTitle.h"
#include "CtWindowContentsPressLevel.h"

class CtContainerSpinBox : public CtContainer
{
/*** 定数 ***************************************/
public:
protected:
private:

/*** メソッド ***********************************/
public:
	CtContainerSpinBox(CtWindowID id);
	virtual ~CtContainerSpinBox();
	virtual bool destroyContainer();

	virtual CtLayout* createContainer();

	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleParamEvent(const CtEventParam& Param);

	virtual bool startupContainer();

protected:
	virtual CtLayout* createLayout();
	virtual CtLayout* createMain();
	virtual CtLayout* createNormal();
	virtual CtLayout* createBar();
	virtual CtLayout* createLabel();
	virtual CtLayout* createLabelLayout();

	virtual bool executionUp();
	virtual bool executionDown();
	virtual bool executionRet(bool bDestructor = false);
	virtual bool executionSet();

	void executionWfmSet();
	void executionWfmRevert();

	virtual void checkInvalid();

private:
	int getStep();
	CtContainerLevelBar::LevelBarType getLevelBarType();
	
/*** メンバ   ***********************************/
public:

protected:
	CtWindowID      m_WindowID;

	CtMenuInfoSpinBox::CtMenuSpinBoxInfo* m_Info;
	CtWindowContentsPressLevel::ContentsPressLevel     m_Laval;

	CtContainerCtrlButton* m_pCtrl;
	bool            m_bPressMmr;
	bool            m_bPressBtn;
	CtParamBox*     m_pParamBox;
	short           m_LabelSize;

private:

};

#endif
