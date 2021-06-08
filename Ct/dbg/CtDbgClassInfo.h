/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtDbgClassInfo
*/
#ifndef __CtDbgClassInfo__

#ifdef WIN32_GUI_SIM

#include <typeinfo.h>
#include "CtDebugPrint.h"
#define PRINT_CLASS_INFO(c) CtDebugPrint(CtDbg, "%-26s: %4d\n", typeid(c).name(), sizeof(c));
 
#else

 #define PRINT_CLASS_INFO(c)
 
#endif

#include "CtWindowCommon.h"
#include "CtGridView.h"
#include "CtMenuButton.h"
#include "CtParamContents.h"
#include "CtParamIcon.h"
#include "CtStackLabel.h"

class CtDbgClassInfo
{
public:
	static void printClassInfo();
	
private:
	CtDbgClassInfo(){};
	~CtDbgClassInfo(){};
};

void CtDbgClassInfo::printClassInfo()
{
	/// tk
	PRINT_CLASS_INFO(CtButton);
	PRINT_CLASS_INFO(CtColor);
	PRINT_CLASS_INFO(CtContainer);
	// tk - drawinfo
	PRINT_CLASS_INFO(CtDrawInfo);
	PRINT_CLASS_INFO(CtFill);
	PRINT_CLASS_INFO(CtString);
	PRINT_CLASS_INFO(CtDrawable);
	PRINT_CLASS_INFO(CtSVG);
	PRINT_CLASS_INFO(CtBitmap);
	PRINT_CLASS_INFO(CtLine);
	PRINT_CLASS_INFO(CtRect);
	PRINT_CLASS_INFO(CtRoundRect);
	PRINT_CLASS_INFO(CtEllipse);
	PRINT_CLASS_INFO(CtLabel);
	PRINT_CLASS_INFO(CtEventHandler);
	PRINT_CLASS_INFO(CtGridLayout);
	PRINT_CLASS_INFO(CtGridView);
	PRINT_CLASS_INFO(CtHLayout);
	PRINT_CLASS_INFO(CtLabel);
	PRINT_CLASS_INFO(CtLayout);
	PRINT_CLASS_INFO(CtLinkButton);
	PRINT_CLASS_INFO(CtListView);
	PRINT_CLASS_INFO(CtMenuButton);
	PRINT_CLASS_INFO(CtParamBox);
	PRINT_CLASS_INFO(CtParamContents);
	PRINT_CLASS_INFO(CtParamIcon);
	PRINT_CLASS_INFO(CtParamLabel);
	PRINT_CLASS_INFO(CtScrollBar);
	PRINT_CLASS_INFO(CtSlideLabel);
	PRINT_CLASS_INFO(CtStackLabel);
	PRINT_CLASS_INFO(CtStyle);
	PRINT_CLASS_INFO(CtTextField);
	// è»ó™
	PRINT_CLASS_INFO(CtVLayout);
	PRINT_CLASS_INFO(CtWidget);
	PRINT_CLASS_INFO(CtWindow);
	PRINT_CLASS_INFO(CtWindowContents);
	PRINT_CLASS_INFO(CtWindowMain);

	/// ws
	// ws - event
	PRINT_CLASS_INFO(CtMsg);
	PRINT_CLASS_INFO(CtEvent);
	PRINT_CLASS_INFO(CtEventWindow);
	PRINT_CLASS_INFO(CtEventWinInfoAccess);
	PRINT_CLASS_INFO(CtEventSys);
	PRINT_CLASS_INFO(CtEventKey);
	PRINT_CLASS_INFO(CtEventTouch);
	PRINT_CLASS_INFO(CtEventTouchSlide);
	PRINT_CLASS_INFO(CtEventTimer);
	PRINT_CLASS_INFO(CtEventParam);
	PRINT_CLASS_INFO(CtEventFlash);
	PRINT_CLASS_INFO(CtEventButton);
	PRINT_CLASS_INFO(CtEventWidget);
	PRINT_CLASS_INFO(CtEventFunc);
	PRINT_CLASS_INFO(CtEventDrawResult);
	PRINT_CLASS_INFO(CtEventRequest);

}

#endif

