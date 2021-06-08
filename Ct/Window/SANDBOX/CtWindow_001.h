/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_001
 */


#ifndef __CtWindow_001_H__
#define __CtWindow_001_H__

#include "CtWindowCommon.h"
#include "CtTimer.h"

class CtWindow_001 : public CtWindowMain
{
public:
#define TEST_ALIGN_MAX 11
#define TEST_AUTO_ADJUST_MAX 2
#define TEST_ASPECT_RATION_MAX 6

	CtWindow_001(CtWindowContents *pContents);
	~CtWindow_001();

	bool handleButtonEvent(const CtEventButton& Button);
	bool handleTimerEvent(const CtEventTimer& Timer);

private:
	CtWindow* createWindow();
	bool destroyWindow();
	int m_TimerState;
	CtLayout *m_pLayout1;
	CtLayout *m_pLayout2;
	CtWidget* m_pFlash;
	CtWidget* m_pScreen;
	int flag;
	int timer;
	int svg_align;
	CtAlign AlignTopLeft = (CtAlign)(AlignTop | AlignLeft);
	CtAlign AlignTopRight = (CtAlign)(AlignTop | AlignRight);
	CtAlign AlignBottomLeft = (CtAlign)(AlignBottom | AlignLeft);
	CtAlign AlignBottomRight = (CtAlign)(AlignBottom | AlignRight);

	CtAlign testAlign[TEST_ALIGN_MAX] = { AlignVCenter, AlignTop, AlignBottom, AlignHCenter, AlignLeft, AlignRight, AlignCenter,
		AlignTopLeft, AlignTopRight, AlignBottomLeft, AlignBottomRight };
	char *testAlign_name[TEST_ALIGN_MAX] = { "AlignVCenter", "AlignTop", "AlignBottom", "AlignHCenter", "AlignLeft", "AlignRight", "AlignCenter",
		"AlignTopLeft", "AlignTopRight", "AlignBottomLeft", "AlignBottomRight" };
	bool testAutoAdjust[TEST_AUTO_ADJUST_MAX] = { true, false };
	char *testAutoAdjust_name[TEST_AUTO_ADJUST_MAX] = {"true", "false"};
	CtAspectRatio testAspectRatio[TEST_ASPECT_RATION_MAX] = { AspectRatio_Default, AspectRatio_Original, AspectRatio_Same, AspectRatio_Wide, AspectRatio_Narrow, AspectRatio_Special };
	char *testAspectRatio_name[TEST_ASPECT_RATION_MAX] = {"AspectRatio_Default", "AspectRatio_Original", "AspectRatio_Same", "AspectRatio_Wide", "AspectRatio_Narrow", "AspectRatio_Special"};

protected:
	void updateImage(int id);
	void updateStr(int id);
	void updateAlign(int id);

	void initDisplay();

	CtLabel *test_x;

	CtLabel *testSvgLabel;

	CtStackLabel* m_pstr_name;
	CtStackLabel* m_pstr1;
	CtStackLabel* m_pstr2;
	CtStackLabel* m_pstr3;
	CtStackLabel* m_pstr4;

	CtStackLabel* m_svgAlignName;
	CtStackLabel* m_pImageAlign;
	CtStackLabel* m_pImage0;
	CtStackLabel* m_pImage1;
	CtStackLabel* m_pImage2;
	CtStackLabel* m_pImage3;
	CtStackLabel* m_pImage4;
	CtStackLabel* m_pImage5;
	CtStackLabel* m_pImage6;

	CtStackLabel* m_pSetAutoAdjust;
	CtStackLabel* m_pSetAspectRatio;
	CtStackLabel* m_pSetAlign;

};
#endif
