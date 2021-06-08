/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactWindowDialog
*/


#ifndef __CtFactWindowDialog_H__
#define __CtFactWindowDialog_H__

#include "CtWindowCommon.h"
#include "CtContainerCtrlButton.h"

class CtFactWindowDialog : public CtWindowMain
{
public:
	typedef enum MessageType {
		MessageType_Version,
		MessageType_HourMeters,
		MessageType_Center,
		MessageType_End,
		MessageType_Max
	} MessageType;

	typedef struct MessageInfo {
		CtWindowID  id;
		MessageType type;
		short       line;
		char*       str;
		bool        ret;
	} MessageInfo;

public:
	CtFactWindowDialog();
	~CtFactWindowDialog();

    bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);

	static MessageInfo* getInfo(CtWindowID WindowID);

private:
	virtual CtWindow* createWindow();

	CtLayout* createVersion();
	CtLayout* createHourMeters();
	CtLayout* createCenterMessage();
	CtLayout* createEndMessage();

	bool destroyWindow();

	bool convertVersionInfo(int Value, char *Data);

private:

	CtWindow* m_pWin;

	static MessageInfo InfoTable[];

	MessageInfo* m_pInfo;

};

#endif
