/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtWindow_001.h"
#include "CtFastCounter.h"
#include "CtFastContainerAudioLevel_View.h"


GDI_IMAGE_ID test_svg = IC_MENU_SET;

CtWindow* CtWindow_001::createWindow()
{
	CtWindow *pWin = new CtWindow();
	CtLabel *pLabel0 = NULL;
	CtLabel *pLabel1 = NULL;
	CtLabel *pLabel2 = NULL;
	CtLabel *pLabel3 = NULL;
	CtLabel *pLabel4 = NULL;
	CtLabel *pLabel5 = NULL;
	CtLabel *pLabel6 = NULL;
	CtHLayout *pLayout = new CtHLayout();
	CtVLayout *btnLayout = new CtVLayout();
	CtHLayout *imgHLayout0 = new CtHLayout();
	CtHLayout *imgHLayout1 = new CtHLayout();
	CtHLayout *imgHLayout2 = new CtHLayout();
	CtHLayout *imgHLayout3= new CtHLayout();
	CtVLayout *imgVLayout = new CtVLayout();
	
	//char* bigstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* bigstr = "ê›íËÇƒÇ∑ÇƒÇ∑AaAAabbb";
	char* smallstr = "abcdefghijklmnopqrstuvwxyz";
	CtFontSet fSet1 = CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::White);
	fSet1.setSize(20);

	CtFontSet fSet2, fSet3, fSet4, fSet5, fSet6, fSet7, fSet8, fSet9, fSet10, fSet11, fSet12, fSet13, fSet14, fSet15;
	CtFontSet fontList[TEST_ALIGN_MAX] = { fSet2, fSet3, fSet4, fSet5, fSet6, fSet7, fSet8, fSet9, fSet10, fSet11, fSet12};
	for (int k = 0; k < TEST_ALIGN_MAX; k++)
	{
		fontList[k] = CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::White);
		fontList[k].setSize(20);
		fontList[k].setAlign(testAlign[k]);
	}

	CtLabel *bigLabel = new CtLabel(bigstr, fSet1);
	CtLabel *smallLabel = new CtLabel(smallstr, fSet1);
	CtButton* test_button2 = new CtButton(CtSize(300, 50), bigLabel);
	CtButton* test_button3 = new CtButton(CtSize(300, 50), smallLabel);
	CtHLayout *strbigLayout1 = new CtHLayout(CtColor::Black);
	strbigLayout1->addWidget(new CtLabel(bigstr, fSet1));
	CtHLayout *strsmallLayout1 = new CtHLayout(CtColor::Black);
	strsmallLayout1->addWidget(new CtLabel(smallstr, fSet1));

	m_pstr_name = new CtStackLabel();
	m_pstr1 = new CtStackLabel();
	m_pstr2 = new CtStackLabel();
	m_pstr3 = new CtStackLabel();
	m_pstr4 = new CtStackLabel();

	CtLabel *bigLabel2, *bigLabel3;
	CtLabel *smallLabel2, *smallLabel3;
	for (int j = 0; j < TEST_ALIGN_MAX; j++)
	{
		m_pstr_name->addLabel(testAlign_name[j]);

		bigLabel2 = new CtLabel(bigstr, fontList[j]);
		smallLabel2 = new CtLabel(smallstr, fontList[j]);
		m_pstr1->addLabel(bigLabel2);
		m_pstr2->addLabel(smallLabel2);
		bigLabel3 = new CtLabel(bigstr, fontList[j]);
		smallLabel3 = new CtLabel(smallstr, fontList[j]);
		m_pstr3->addLabel(bigLabel3);
		m_pstr4->addLabel(smallLabel3);
	}
	CtButton* test_button4 = new CtButton(CtSize(300, 50), m_pstr1);
	CtButton* test_button5 = new CtButton(CtSize(300, 50), m_pstr2);
	CtHLayout *strbigLayout2 = new CtHLayout(CtColor::Black);
	strbigLayout2->addWidget(m_pstr3);
	CtHLayout *strsmallLayout2 = new CtHLayout(CtColor::Black);
	strsmallLayout2->addWidget(m_pstr4);

	m_pImage0 = new CtStackLabel();
	m_pImage1 = new CtStackLabel();
	m_pImage2 = new CtStackLabel();
	m_pImage3 = new CtStackLabel();
	m_pImage4 = new CtStackLabel();
	m_pImage5 = new CtStackLabel();
	m_pImage6 = new CtStackLabel();

	for (int i = 0;i < GDI_IMAGE_ID_MAX; i++)
		{
			pLabel0 = new CtLabel((GDI_IMAGE_ID)i);
			m_pImage0->addLabel(pLabel0);
			pLabel1 = new CtLabel((GDI_IMAGE_ID)i);
			m_pImage1->addLabel(pLabel1);
			pLabel2 = new CtLabel((GDI_IMAGE_ID)i);
			m_pImage2->addLabel(pLabel2);
			pLabel3 = new CtLabel((GDI_IMAGE_ID)i);
			m_pImage3->addLabel(pLabel3);
			pLabel4 = new CtLabel((GDI_IMAGE_ID)i);
			m_pImage4->addLabel(pLabel4);
			pLabel5 = new CtLabel((GDI_IMAGE_ID)i);
			m_pImage5->addLabel(pLabel5);
			pLabel6 = new CtLabel((GDI_IMAGE_ID)i);
			m_pImage6->addLabel(pLabel6);
		}
	m_pImage0->setAutoAdjust(false);
	m_pImage1->setAspectRatio(AspectRatio_Default);
	m_pImage2->setAspectRatio(AspectRatio_Original);
	m_pImage3->setAspectRatio(AspectRatio_Same);
	m_pImage4->setAspectRatio(AspectRatio_Wide);
	m_pImage5->setAspectRatio(AspectRatio_Narrow);
	m_pImage6->setAspectRatio(AspectRatio_Special);

	CtHLayout *SVGLayout = new CtHLayout();
	CtButton *setAutoAdjustBtn = new CtButton(CtSize(150, 50), "AutoAdjust");
	setAutoAdjustBtn->setWidgetID(901);
	SVGLayout->addWidget(setAutoAdjustBtn);
	CtButton *setAspectRatioBtn = new CtButton(CtSize(150, 50), "AspectRatio");
	setAspectRatioBtn->setWidgetID(902);
	SVGLayout->addWidget(setAspectRatioBtn);
	CtButton *setAlignBtn = new CtButton(CtSize(150, 50), "Align");
	setAlignBtn->setWidgetID(903);
	SVGLayout->addWidget(setAlignBtn);
	btnLayout->addWidget(SVGLayout);

	m_pSetAutoAdjust = new CtStackLabel();
	m_pSetAspectRatio = new CtStackLabel();
	m_pSetAlign = new CtStackLabel();
	CtFontSet fsvg = CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::magenta);
	fsvg.setSize(20);
	int cnt;
	for (cnt = 0; cnt < TEST_AUTO_ADJUST_MAX; cnt++)
	{
		m_pSetAutoAdjust->addLabel(testAutoAdjust_name[cnt], fsvg);
	}
	for (cnt = 0; cnt < TEST_ASPECT_RATION_MAX; cnt++)
	{
		m_pSetAspectRatio->addLabel(testAspectRatio_name[cnt], fsvg);
	}
	for (cnt = 0; cnt < TEST_ALIGN_MAX; cnt++)
	{
		m_pSetAlign->addLabel(testAlign_name[cnt], fsvg);
	}
	CtHLayout *SVGNameLayout = new CtHLayout();
	SVGNameLayout->setColor(CtColor::darkgray);
	SVGNameLayout->addWidget(m_pSetAutoAdjust);
	SVGNameLayout->addWidget(m_pSetAspectRatio);
	SVGNameLayout->addWidget(m_pSetAlign);
	btnLayout->addWidget(SVGNameLayout);

	CtHLayout *testSvgLayout = new CtHLayout();
	testSvgLayout->setColor(CtColor::deepskyblue);
	CtHLayout *intestSvgLayout = new CtHLayout();
	intestSvgLayout->setColor(CtColor::darkBlue);
	testSvgLabel = new CtLabel(test_svg);
	testSvgLayout->addStretch(2);
	intestSvgLayout->addWidget(testSvgLabel);
	testSvgLayout->addWidget(intestSvgLayout);
	testSvgLayout->addStretch(2);
	btnLayout->addWidget(testSvgLayout);


	CtHLayout *svgLayout = new CtHLayout();
	CtHLayout *LinsvgLayout = new CtHLayout();
	LinsvgLayout->setColor(CtColor::darkBlue);
	CtLabel *LsvgLabel = new CtLabel(IC_PRESET);
	LsvgLabel->setAlign(AlignLeft);
	LinsvgLayout->addWidget(LsvgLabel);
	CtHLayout *TinsvgLayout = new CtHLayout();
	TinsvgLayout->setColor(CtColor::darkgreen);
	CtLabel *TsvgLabel = new CtLabel(IC_BATT_LV5);
	TsvgLabel->setAlign(AlignTop);
	TinsvgLayout->addWidget(TsvgLabel);
	CtHLayout *RinsvgLayout = new CtHLayout();
	RinsvgLayout->setColor(CtColor::darkcyan);
	CtLabel *RsvgLabel = new CtLabel(IC_PRESET);
	RsvgLabel->setAlign(AlignRight);
	RinsvgLayout->addWidget(RsvgLabel);
	CtHLayout *BinsvgLayout = new CtHLayout();
	BinsvgLayout->setColor(CtColor::darkmagenta);
	CtLabel *BsvgLabel = new CtLabel(IC_BATT_LV5);
	BsvgLabel->setAlign(AlignBottom);
	BinsvgLayout->addWidget(BsvgLabel);

	svgLayout->addWidget(LinsvgLayout);
	svgLayout->addWidget(TinsvgLayout);
	svgLayout->addWidget(RinsvgLayout);
	svgLayout->addWidget(BinsvgLayout);
	svgLayout->addStretch(1);
	btnLayout->addWidget(svgLayout);
	CtHLayout *strnameLayout = new CtHLayout();
	strnameLayout->setColor(CtColor::darkgray);
	CtButton* test_button_str = new CtButton(CtSize(150, 50), "STR_TEST");
	test_button_str->setWidgetID(223);
	strnameLayout->addWidget(test_button_str);
	strnameLayout->addWidget(m_pstr_name);
	btnLayout->addWidget(strnameLayout);
	btnLayout->addWidget(test_button4);
	btnLayout->addWidget(strbigLayout2);
	btnLayout->addWidget(test_button5);
	btnLayout->addWidget(strsmallLayout2);

	pLayout->addWidget(btnLayout);

	CtHLayout *pLayout0 = new CtHLayout();
	pLayout0->addWidget(m_pImage0);
	pLayout0->setColor(CtColor::darkMagenta);
	CtHLayout *pLayout1 = new CtHLayout();
	pLayout1->addWidget(m_pImage1);
	pLayout1->setColor(CtColor::darkMagenta);
	CtHLayout *pLayout2 = new CtHLayout();
	pLayout2->addWidget(m_pImage2);
	pLayout2->setColor(CtColor::darkMagenta);

	CtHLayout *pLayout3 = new CtHLayout();
	pLayout3->addWidget(m_pImage3);
	pLayout3->setColor(CtColor::darkMagenta);
	CtHLayout *pLayout4 = new CtHLayout();
	pLayout4->addWidget(m_pImage4);
	pLayout4->setColor(CtColor::darkMagenta);

	CtHLayout *pLayout5 = new CtHLayout();
	pLayout5->addWidget(m_pImage5);
	pLayout5->setColor(CtColor::darkMagenta);
	CtHLayout *pLayout6 = new CtHLayout();
	pLayout6->addWidget(m_pImage6);
	pLayout6->setColor(CtColor::darkMagenta);

	CtFontSet fpri = CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::Red);
	fpri.setSize(20);
	fpri.setAlign(AlignLeft);
	CtHLayout *priHLayout0 = new CtHLayout();
	priHLayout0->setColor(CtColor::darkgray);
	priHLayout0->addStretch(1);
	priHLayout0->addWidget(new CtLabel("AutoAdjust:false", fpri), 2);
	priHLayout0->addStretch(2);
	CtHLayout *priHLayout1 = new CtHLayout();
	priHLayout1->setColor(CtColor::darkgray);
	priHLayout1->addStretch(1);
	priHLayout1->addWidget(new CtLabel("AspectRatio_Default", fpri), 2);
	priHLayout1->addWidget(new CtLabel("AspectRatio_Original", fpri), 2);
	CtHLayout *priHLayout2 = new CtHLayout();
	priHLayout2->setColor(CtColor::darkgray);
	priHLayout2->addStretch(1);
	priHLayout2->addWidget(new CtLabel("AspectRatio_Same", fpri), 2);
	priHLayout2->addWidget(new CtLabel("AspectRatio_Wide", fpri), 2);
	CtHLayout *priHLayout3 = new CtHLayout();
	priHLayout3->setColor(CtColor::darkgray);
	priHLayout3->addStretch(1);
	priHLayout3->addWidget(new CtLabel("AspectRatio_Narrow", fpri), 2);
	priHLayout3->addWidget(new CtLabel("AspectRatio_Special", fpri), 2);

	imgHLayout0->addStretch(1);
	imgHLayout0->addWidget(pLayout0);
	imgHLayout0->addStretch(3);

	imgHLayout1->addStretch(1);
	imgHLayout1->addWidget(pLayout1);
	imgHLayout1->addStretch(1);
	imgHLayout1->addWidget(pLayout2);
	imgHLayout1->addStretch(1);

	imgHLayout2->addStretch(1);
	imgHLayout2->addWidget(pLayout3);
	imgHLayout2->addStretch(1);
	imgHLayout2->addWidget(pLayout4);
	imgHLayout2->addStretch(1);

	imgHLayout3->addStretch(1);
	imgHLayout3->addWidget(pLayout5);
	imgHLayout3->addStretch(1);
	imgHLayout3->addWidget(pLayout6);
	imgHLayout3->addStretch(1);

	CtHLayout *svgAlignLayout = new CtHLayout();
	CtButton* chang_btn = new CtButton(CtSize(150, 50), "Change");
	chang_btn->setWidgetID(333);
	svgAlignLayout->addWidget(chang_btn);
	m_svgAlignName = new CtStackLabel();
	for (int s = 0; s < TEST_ALIGN_MAX; s++)
	{
		m_svgAlignName->addLabel(testAlign_name[s]);
	}
	svgAlignLayout->addWidget(m_svgAlignName);

	CtButton* test_button1 = new CtButton(CtSize(150, 50), "SVG_TEST");
	test_button1->setWidgetID(123);
	imgVLayout->addWidget(test_button1);

	imgVLayout->addWidget(svgAlignLayout);
	imgVLayout->addWidget(priHLayout0);
	imgVLayout->addWidget(imgHLayout0);
	imgVLayout->addWidget(priHLayout1);
	imgVLayout->addWidget(imgHLayout1);
	imgVLayout->addWidget(priHLayout2);
	imgVLayout->addWidget(imgHLayout2);
	imgVLayout->addWidget(priHLayout3);
	imgVLayout->addWidget(imgHLayout3);
	pLayout->addWidget(imgVLayout);

	pWin->addWidget(pLayout);

	initDisplay();

	CtDebugPrint(CtDbg, "========================== [%d]\n", GDI_IMAGE_ID_MAX);
	CtDebugPrint(CtDbg, "size of CtWidget:%d\n", sizeof(CtWidget));
	CtDebugPrint(CtDbg, "size of CtLabel:%d\n", sizeof(CtLabel));
	CtDebugPrint(CtDbg, "size of CtStackLabel:%d\n", sizeof(CtStackLabel));
	CtDebugPrint(CtDbg, "size of CtButton:%d\n", sizeof(CtButton));
	CtDebugPrint(CtDbg, "size of CtLayout:%d\n", sizeof(CtLayout));
	CtDebugPrint(CtDbg, "==========================\n");
	
	return pWin;
}

CtWindow_001::CtWindow_001(CtWindowContents *pContents)
{
	m_pFlash = NULL;
	m_pScreen = NULL;
	flag = 0;
	timer = 1000;
}

CtWindow_001::~CtWindow_001()
{
}

bool CtWindow_001::destroyWindow()
{
	return true;
}
#include "CtTimeMesure.h"
unsigned long tim1, tim2;

bool CtWindow_001::handleButtonEvent(const CtEventButton& Button)
{
	bool bRet = false;
	int cur, max;

	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	switch (Button.getWidgetID()) {
	case 123:
	{
		if (CtTimer::getInstance()->isActTimerId(123, this) == true) {
			CtTimer::getInstance()->stopCyclic(123, this);
		}
		else {
			CtTimer::getInstance()->startCyclic(123, timer, this);
		}
	}
	break;
	case 223:
	{
		if (CtTimer::getInstance()->isActTimerId(223, this) == true) {
			CtTimer::getInstance()->stopCyclic(223, this);
		}
		else {
			CtTimer::getInstance()->startCyclic(223, timer, this);
		}
	}
	break;
	case 333:
	{
		cur = m_svgAlignName->getIndex();
		max = m_svgAlignName->getIndexMax();
		if (cur == max)
		{
			cur = 0;
		}
		else
		{
			cur++;
		}
		updateAlign(cur);
		bRet = true;
	}
	break;
	case 901:
		cur = m_pSetAutoAdjust->getIndex();
		max = m_pSetAutoAdjust->getIndexMax();
		if (cur == max)
		{
			cur = 0;
		}
		else
		{
			cur++;
		}
		m_pSetAutoAdjust->index(cur);
		testSvgLabel->setAutoAdjust(testAutoAdjust[cur]);
		bRet = true;
		break;
	case 902:
		cur = m_pSetAspectRatio->getIndex();
		max = m_pSetAspectRatio->getIndexMax();
		if (cur == max)
		{
			cur = 0;
		}
		else
		{
			cur++;
		}
		m_pSetAspectRatio->index(cur);
		testSvgLabel->setAspectRatio(testAspectRatio[cur]);
		bRet = true;
		break;
	case 903:
		cur = m_pSetAlign->getIndex();
		max = m_pSetAlign->getIndexMax();
		if (cur == max)
		{
			cur = 0;
		}
		else
		{
			cur++;
		}
		m_pSetAlign->index(cur);
		testSvgLabel->setAlign(testAlign[cur]);
		bRet = true;
		break;
	default:
		break;
	}
	return bRet;
}


bool CtWindow_001::handleTimerEvent(const CtEventTimer& Timer) {
	int cur, max;

	switch (Timer.getTimeUid()) {
	case 123:
		cur = m_pImage0->getIndex();
		max = m_pImage0->getIndexMax();
		if (cur == max)
			{
				cur = 0;
				if (CtTimer::getInstance()->isActTimerId(123, this) == true) {
					CtTimer::getInstance()->stopCyclic(123, this);
				}
			}
		else
			{
				cur++;
				CtTimer::getInstance()->startCyclic(123, timer, this);
			}
		updateImage(cur);
		return true;
	case 223:
		cur = m_pstr1->getIndex();
		max = m_pstr1->getIndexMax();
		if (cur == max)
		{
			cur = 0;
			if (CtTimer::getInstance()->isActTimerId(223, this) == true) {
				CtTimer::getInstance()->stopCyclic(223, this);
			}
		}
		else
		{
			cur++;
			CtTimer::getInstance()->startCyclic(223, timer, this);
		}
		updateStr(cur);
		return true;
	default:
		return false;
		break;
	}
	return false;
}

void CtWindow_001::updateImage(int id){
	m_pImage0->index(id);
    m_pImage1->index(id);
	m_pImage2->index(id);
	m_pImage3->index(id);
	m_pImage4->index(id);
	m_pImage5->index(id);
	m_pImage6->index(id);

}

void CtWindow_001::updateStr(int id) {
	m_pstr1->index(id);
	m_pstr2->index(id);
	m_pstr3->index(id);
	m_pstr4->index(id);
	m_pstr_name->index(id);
}

void CtWindow_001::updateAlign(int id) {
	m_svgAlignName->index(id);
	m_pImage0->setAlign(testAlign[id]);
	m_pImage1->setAlign(testAlign[id]);
	m_pImage2->setAlign(testAlign[id]);
	m_pImage3->setAlign(testAlign[id]);
	m_pImage4->setAlign(testAlign[id]);
	m_pImage5->setAlign(testAlign[id]);
	m_pImage6->setAlign(testAlign[id]);
}

void CtWindow_001::initDisplay(){

	updateImage(0);
	updateStr(0);
	updateAlign(0);
}
