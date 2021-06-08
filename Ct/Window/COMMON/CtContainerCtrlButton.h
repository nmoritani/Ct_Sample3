/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtContainerCtrlButton_H_
#define __CtContainerCtrlButton_H_

#include "CtWindowCommon.h"

#define WidgetID_OFFSET  (0xF000)
#define WidgetID_SET     (0xF000)
#define WidgetID_UP      (0xF001)
#define WidgetID_DOWN    (0xF002)
#define WidgetID_RET     (0xF003)

#define NormalColor     CtColor(0, 0, 0, (unsigned char)(255 * 0.4)), CtColor(134, 134, 134, (unsigned char)(255 * 0.4)), CtColor(212, 212, 212, (unsigned char)(255 * 0.4))
#define ThumbColor     (0xFFFC)

class CtContainerCtrlButton : public CtContainer{

private:
	typedef enum ButtonID {
		Button_Set,
		Button_Up,
		Button_Down,
		Button_Ret,
		Button_Max,
	}ButtonID;

	typedef struct ButtonInfo {
		bool			Valid;
		CtButton*       pButton;
	} ButtonInfo;



public :

	CtContainerCtrlButton(bool bSet, bool bUp, bool bDown, bool bRet);
	virtual ~CtContainerCtrlButton();

	virtual CtLayout* createContainer();
	virtual bool destroyContainer();

	bool setInvalid(int widgetID, bool bInvalid);
	void setFocusable(bool bFocusable);
	void setTrans(bool bTrans);
	void setTransColor(bool bTrans);

private:
	void ctor();

	CtButton* createButton(ButtonID id);

	GDI_IMAGE_ID getImage(ButtonID id);

	bool idErrCheck(ButtonID id);
private:
//	CtrlButtonInfo m_Info;
	ButtonInfo m_Info[Button_Max];

	bool m_bFocusable;
	bool m_bTrans;

	CtColor 		InvalidBaseColor;
	CtColor 		InvalidStrokeColor;
	CtColor 		InvalidLabelColor;

};

#endif
