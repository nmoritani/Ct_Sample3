/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_006
 */

#include "CtWindow_006.h"
#include "CtParamLabel.h"
#include "CtLanguage.h"
#include "string_api.h"

#include "CtContainerCtrlButton.h"
#include "CtMenuButton.h"
#include "CtMenuListView.h"
#include "CtContainerPlayViewProgress.h"

CtWindow_006::CtWindow_006(CtWindowContents *pContents) :
	m_Index(-1),
	m_pTest(NULL),
	m_pLabel1_ButtonColorTest2(NULL),
	m_pLabel2_ButtonColorTest2(NULL)
{
}

bool CtWindow_006::startupWindow()
{
	startupWindow_ButtonColorTest2();
	return true;
}

bool CtWindow_006::handleButtonEvent(const CtEventButton& Button)
{
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	return m_pTest->index(Button.getWidgetID() - IndexOffset);

	return true;
}

CtWindow* CtWindow_006::createWindow()
{
	m_pTest = new CtStackLabel();
	CtVLayout* pVLayout = new CtVLayout();

	pVLayout->addWidget(createButton());
	m_pTest->addLabel(createRectTest());

	pVLayout->addWidget(createButton());
	m_pTest->addLabel(createLanguageTest3());

	pVLayout->addWidget(createButton());
	m_pTest->addLabel(createLanguageTest());

	pVLayout->addWidget(createButton());
	m_pTest->addLabel(createLanguageTest2());

	pVLayout->addWidget(createButton());
	m_pTest->addLabel(createCtrlButtonTest());

	pVLayout->addWidget(createButton());
	m_pTest->addLabel(createCtLineTest());

	pVLayout->addWidget(createButton());
	m_pTest->addLabel(createCtFontSetTest());

	pVLayout->addWidget(createButton());
	m_pTest->addLabel(createProgressBarTest());

	pVLayout->addWidget(createButton());
	m_pTest->addLabel(createButtonColorTest());

	pVLayout->addWidget(createButton());
	m_pTest->addLabel(createButtonColorTest2());

	CtHLayout* pLayout = new CtHLayout();
	pLayout->addWidget(pVLayout, 58);
	pLayout->addStretch(2);
	pLayout->addWidget(m_pTest, 900);

	CtWindow* pWin = new CtWindow();
	pWin->addWidget(pLayout);

	return pWin;
}

CtButton* CtWindow_006::createButton()
{
	m_Index++;
	char Name[5] = { 0 };

	sprintf(Name, "%d", m_Index);

	CtButton* pButton = new CtButton(AutoSize, Name);
	pButton->setWidgetID(m_Index + IndexOffset);
	pButton->setFocusable(false);
	return pButton;
}

CtLayout* CtWindow_006::createButtonColorTest2()
{
	CtLabel* pLabel1 = new CtLabel(IC_THUMBNAIL_DELETE, CtColor::Red);
	CtLabel* pLabel2 = new CtLabel(IC_THUMBNAIL_DELETE);
	CtLabel* pLabel3 = new CtLabel();
	CtLabel* pLabel4 = new CtLabel();
	CtLabel* pLabel5 = new CtLabel();
	CtLabel* pLabel6 = new CtLabel();
	m_pLabel1_ButtonColorTest2 = new CtLabel();
	m_pLabel2_ButtonColorTest2 = new CtLabel();

	pLabel2->setColor(CtColor::Red);

	pLabel3->setImage(IC_THUMBNAIL_DELETE, CtColor::Red, CtColor::NoColor);

	pLabel4->setImage(IC_THUMBNAIL_DELETE);
	pLabel4->setColor(CtColor::Red);

	CtVLayout* pV = new CtVLayout();
	pV->addStretch(1);
	pV->addWidget(new CtButton(AutoSize, pLabel1), 2);
	pV->addStretch(1);
	pV->addWidget(new CtButton(AutoSize, pLabel2), 2);
	pV->addStretch(1);
	pV->addWidget(new CtButton(AutoSize, pLabel3), 2);
	pV->addStretch(1);
	pV->addWidget(new CtButton(AutoSize, pLabel4), 2);
	pV->addStretch(1);
	pV->addWidget(new CtButton(AutoSize, pLabel5), 2);
	pV->addStretch(1);
	pV->addWidget(new CtButton(AutoSize, pLabel6), 2);
	pV->addStretch(1);
	pV->addWidget(new CtButton(AutoSize, m_pLabel1_ButtonColorTest2), 2);
	pV->addStretch(1);
	pV->addWidget(new CtButton(AutoSize, m_pLabel2_ButtonColorTest2), 2);
	pV->addStretch(1);

	pLabel5->setImage(IC_THUMBNAIL_DELETE, CtColor::Red, CtColor::NoColor);

	pLabel6->setImage(IC_THUMBNAIL_DELETE);
	pLabel6->setColor(CtColor::Red);


	CtHLayout* pH = new CtHLayout();
	pH->addStretch(1);
	pH->addWidget(pV, 1);
	pH->addStretch(1);

	return pH;
}
bool CtWindow_006::startupWindow_ButtonColorTest2()
{
	m_pLabel1_ButtonColorTest2->setImage(IC_THUMBNAIL_DELETE, CtColor::Red, CtColor::NoColor);

	m_pLabel2_ButtonColorTest2->setImage(IC_THUMBNAIL_DELETE);
	m_pLabel2_ButtonColorTest2->setColor(CtColor::Red);
	return true;
}
CtLayout* CtWindow_006::createRectTest()
{
	char* str = "[AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA]\nBBBB\nBB\nCCCCC\nDD\nEEEE\nFFFF\nFFFF\n[GGGGG]";
//	char* str = "[AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA]";//55


    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::White);
    //fSet.setLocale(LOCALE_FX);
    fSet.setSize(20);

    CtSize Size;
    fSet.getStringSize(Size, str);

    CtDebugPrint(CtDbg, "Size %d %d\n", Size.width, Size.height);

    CtVLayout* pV = NULL;

	char str2[30] = { 0 };
	sprintf(str2, "Size: W=%d H=%d", Size.width, Size.height);


    pV = new CtVLayout(CtColor::Black);
	pV->addWidget(new CtLabel(str, fSet), 45);
	pV->addStretch(1);
	pV->addWidget(new CtLabel(str2, fSet), 4);

    return pV;
}
CtLayout* CtWindow_006::createButtonColorTest()
{
	CtLayout* pLayout = new CtLayout();
	pLayout->addWidget(new CtLabel("AAAA"));

	CtButton* pButton1 = new CtButton(AutoSize, pLayout);
	CtButton* pButton2 = new CtButton(AutoSize, new CtLabel("BBBB"));
	CtButton* pButton3 = new CtButton(AutoSize, new CtLabel("CCCC"));

    //pButton3->setButtonColors(CtColor::White, CtColor(134, 134, 134, 0xff), CtColor::NoColor);
    pButton3->setFocusedButtonColors(CtColor::Blue, CtColor(134, 134, 134, 0xff), CtColor::NoColor);



	CtVLayout* pV = new CtVLayout();
	pV->addStretch(1);
	pV->addWidget(pButton1, 1);
	pV->addStretch(1);
	pV->addWidget(pButton2, 1);
	pV->addStretch(1);
	pV->addWidget(pButton3, 1);
	pV->addStretch(1);

	CtHLayout* pH = new CtHLayout();
	pH->addStretch(1);
	pH->addWidget(pV, 1);
	pH->addStretch(1);

	return pH;
}
CtLayout* CtWindow_006::createLanguageTest3()
{
//	unsigned short* str;

	CtVLayout* pV = new CtVLayout();
	CtVLayout* pV2 = new CtVLayout();
	CtVLayout* pV3 = new CtVLayout();

	struct table {
		GDI_STRING_ID strid;
		LANGUAGE_ID language;
		FONT_LOCALE locae;
	};

	table STR[3] = {
		{ STR_ID_JAPANESE, LANGUAGE_ID_JA ,LOCALE_JP },
		{ STR_ID_ENGLISH,  LANGUAGE_ID_UE ,LOCALE_EN },
		{ STR_ID_CHINESE,  LANGUAGE_ID_SC ,LOCALE_SC },
	};

	// STR_ID_NO_10598 ƒIƒvƒVƒ‡ƒ“ OPTION 

	for (int i = 0; i < 3; i++) {
		CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor::Black);
		fSet.setSize(39);
		fSet.setLanguageId(STR[i].language);
		fSet.setLocale(STR[i].locae);

		unsigned short* str1 = GDI_GetString(LANGUAGE_ID_JA, STR_ID_NO_10598);
		unsigned short* str2 = GDI_GetString(LANGUAGE_ID_UE, STR_ID_NO_10598);
		unsigned short* str3 = GDI_GetString(LANGUAGE_ID_SC, STR_ID_NO_10598);


		pV->addWidget(new CtLabel(str1, fSet), 1);
		pV->addWidget(new CtLabel(str2, fSet), 1);
		pV->addWidget(new CtLabel(str3, fSet), 1);
		//str = GDI_GetString(STR[i].language, STR_ID_NO_10598);
		//pV2->addWidget(new CtLabel(str, fSet), 1);

		//CtSize size;
		//fSet.getStringSize(size, STR_ID_NO_10598);
		//char num[5] = "";
		//sprintf(num, "%d", size.width);
		//pV3->addWidget(new CtLabel(num, fSet), 1);
	}
	CtHLayout* pH = new CtHLayout(CtColor::White);
	pH->addWidget(pV, 1);
	//pH->addWidget(pV2, 1);
	//pH->addWidget(pV3, 1);
	return pH;
}
CtLayout* CtWindow_006::createProgressBarTest()
{
	CtVLayout* pLayout = new CtVLayout();
#define ColorProgressBase	CtColor(ColorRGBA, 0xd4d4d4ff, NULL)
#define ColorProgressBar	CtColor(ColorRGBA, 0x66e300ff, NULL)

#define ProgressBarBase		CtMargin(3,12)
#define ProgressBarBar		CtMargin(5,14)


	CtRect BarRect = CtRect(ColorProgressBar, 0, ColorProgressBar);
	CtRect BaseRect = CtRect(ColorProgressBase, 2, CtColor(ColorRGBA, 0x000000ff, NULL));

	CtContainerPlayViewProgress* pProgress = new CtContainerPlayViewProgress(
		                                                                     CT_FRAME_TYPE_PROGRESS_BAR,
		                                                                     BaseRect,
		                                                                     BarRect,
		                                                                     new CtLabel(IC_OSD_SLIDER_BTN),
		                                                                     ProgressBarBase,
		                                                                     ProgressBarBar);

	pLayout->addStretch(3);
	pLayout->addContainer(pProgress,1);
	pLayout->addStretch(3);

	return pLayout;
}
CtLayout* CtWindow_006::createLanguageTest2()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
	fSet.setLanguageId(CtLanguage::getLanguageID());

	CtVLayout* pV = new CtVLayout(CtColor::Black);
	pV->addStretch(1);
	pV->addWidget(new CtLabel(STR_ID_NO_10124, fSet), 3);
	pV->addStretch(1);

	{
		CtHLayout* pH = new CtHLayout();
		CtMenuButton* pButton = NULL;
		pH->addStretch(1);
		{
			fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
			fSet.setLanguageId(LANGUAGE_ID_JA);
			pButton = new CtMenuButton(AutoSize, new CtLabel(STR_ID_JAPANESE, fSet), CtButton::Rect);
			pButton->setParamAction(CtMenuButton::Default, AplParamLanguage, APL_SYS_PARAM_LANGUAGE_JAPANESE);
			pButton->setFocusable(false);
			pH->addWidget(pButton);
		}
		pH->addStretch(1);
		{
			fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
			fSet.setLanguageId(LANGUAGE_ID_UE);
			pButton = new CtMenuButton(AutoSize, new CtLabel(STR_ID_ENGLISH, fSet), CtButton::Rect);
			pButton->setParamAction(CtMenuButton::Default, AplParamLanguage, APL_SYS_PARAM_LANGUAGE_ENGLISH);
			pButton->setFocusable(false);
			pH->addWidget(pButton);
		}
		pH->addStretch(1);
		{
			fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
			fSet.setLanguageId(LANGUAGE_ID_SC);
			pButton = new CtMenuButton(AutoSize, new CtLabel(STR_ID_CHINESE, fSet), CtButton::Rect);
			pButton->setParamAction(CtMenuButton::Default, AplParamLanguage, APL_SYS_PARAM_LANGUAGE_SCHINESE);
			pButton->setFocusable(false);
			pH->addWidget(pButton);
		}
		pH->addStretch(1);
		pV->addWidget(pH,1);
	}
	pV->addStretch(1);


	return pV;
}
CtLayout* CtWindow_006::createCtrlButtonTest()
{
	CtContainerCtrlButton* pCtrl = new CtContainerCtrlButton(true,true,true,true);

//	pCtrl->setFocusable(true);




	CtLayout* pLayout = new CtLayout();
	pLayout->addContainer(pCtrl);

	return pLayout;
}
CtLayout* CtWindow_006::createLanguageTest()
{
	unsigned short* str;

	CtVLayout* pV = new CtVLayout();
	CtVLayout* pV2 = new CtVLayout();
	CtVLayout* pV3 = new CtVLayout();

	struct table {
		GDI_STRING_ID strid;
		LANGUAGE_ID language;
	};

	table STR[3] = {
		{ STR_ID_JAPANESE,   LANGUAGE_ID_JA },
		{ STR_ID_ENGLISH,    LANGUAGE_ID_UE },
		{ STR_ID_CHINESE,    LANGUAGE_ID_SC },
//		{ STR_ID_SPANISH,    LANGUAGE_ID_SP },
//		{ STR_ID_FRENCH,     LANGUAGE_ID_FR },
//		{ STR_ID_GERMAN,     LANGUAGE_ID_GE },
//		{ STR_ID_ITALIAN,    LANGUAGE_ID_IT },
//		{ STR_ID_RUSSIAN,    LANGUAGE_ID_RU },
//		{ STR_ID_DUTCH,      LANGUAGE_ID_DU },
//		{ STR_ID_TURKISH,    LANGUAGE_ID_TU },
//		{ STR_ID_SWEDISH,    LANGUAGE_ID_SW },
//		{ STR_ID_POLISH,     LANGUAGE_ID_PO },
//		{ STR_ID_CZECH,      LANGUAGE_ID_CZ },
//		{ STR_ID_HUNGARIAN,  LANGUAGE_ID_HU }, 
	};

	for (int i = 0; i < 3; i++) {
		CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor::Black);
		fSet.setSize(39);
		fSet.setLanguageId(STR[i].language);

		pV->addWidget(new CtLabel(STR_ID_NO_10598, fSet), 1);
		str = GDI_GetString(STR[i].language, STR_ID_NO_10598);
		pV2->addWidget(new CtLabel(str, fSet), 1);

		CtSize size;
		fSet.getStringSize(size, STR_ID_NO_10598);
		char num[5] = "";
		sprintf(num, "%d", size.width);
		pV3->addWidget(new CtLabel(num, fSet), 1);
	}
	CtHLayout* pH = new CtHLayout(CtColor::White);
	pH->addWidget(pV, 1);
	pH->addWidget(pV2, 1);
	pH->addWidget(pV3, 1);
	return pH;
}
CtLayout* CtWindow_006::createCtLineTest()
{
	CtVLayout* pV = new CtVLayout();
	CtLayout* pLayout = NULL;

	pV->addStretch(1);

	pLayout = new CtLayout(CtSize(400, 80), CtColor(CtColor::Red));
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 5, CtColor::Black)));
	pLayout->addWidget(new CtLabel(CtLine(UpperLine, 5, CtColor::Black)));
	pV->addWidget(pLayout, 2);
	pV->addStretch(1);

	pLayout = new CtLayout(CtSize(400, 80), CtColor(CtColor::Red));
	pLayout->addWidget(new CtLabel(CtLine(LeftLine, 5, CtColor::Black)));
	pLayout->addWidget(new CtLabel(CtLine(RightLine, 5, CtColor::Black)));
	pV->addWidget(pLayout, 2);
	pV->addStretch(1);

	pLayout = new CtLayout(CtSize(400, 80), CtColor(CtColor::Red));
	pLayout->addWidget(new CtLabel(CtLine(TopLeftSlashLine, 5, CtColor::Black)));
	pLayout->addWidget(new CtLabel(CtLine(TopRightSlashLine, 5, CtColor::Black)));
	pV->addWidget(pLayout, 2);
	pV->addStretch(1);

	pLayout = new CtLayout(CtSize(400, 80), CtColor(CtColor::Red));
	pLayout->addWidget(new CtLabel(CtLine(LeftLine, 5, CtColor::Black)));
	pLayout->addWidget(new CtLabel(CtLine(RightLine, 5, CtColor::Black)));
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 5, CtColor::Black)));
	pLayout->addWidget(new CtLabel(CtLine(UpperLine, 5, CtColor::Black)));
	pLayout->addWidget(new CtLabel(CtLine(TopLeftSlashLine, 5, CtColor::Black)));
	pLayout->addWidget(new CtLabel(CtLine(TopRightSlashLine, 5, CtColor::Black)));
	pV->addWidget(pLayout, 2);
	pV->addStretch(1);

	return pV;
}
CtLayout* CtWindow_006::createCtFontSetTest()
{
	CtFontSet fSetL = CtFontSet(FontTypeNormal, CtColor::White);
	fSetL.setSize(30);
	CtFontSet fSetC = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	fSetC.setSize(30);
	CtFontSet fSetR = CtFontSet(FontTypeNormal_alignRight, CtColor::White);
	fSetR.setSize(30);
	CtFontSet fSetA = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
	fSetA.setSize(30);
	CtFontSet fSetB = CtFontSet(FontTypeBold_alignCenter, CtColor::White);
	fSetB.setSize(30);
	fSetB.setStrokeWidth(1);

	CtHLayout* pH = NULL;
	CtLabel* pLabel = NULL;
	CtParamLabel* pParam = NULL;
	CtVLayout* pV = new CtVLayout(CtColor::Black);
	CtLayout* pLayout = NULL;

#if 1
	pV->addWidget(new CtLabel("FontTypeNormal", fSetL), 1);
	pV->addWidget(new CtLabel("FontTypeNormal_alignCenter", fSetC), 1);
	pV->addWidget(new CtLabel("FontTypeNormal_alignRight", fSetR), 1);
#endif
#if 1
	pV->addWidget(new CtLabel("FontTypeNormal AlignLeft", fSetL), AlignLeft, 1);
	pV->addWidget(new CtLabel("FontTypeNormal_alignCenter AlignLeft", fSetC), AlignLeft, 1);
	pV->addWidget(new CtLabel("FontTypeNormal_alignRight AlignLeft", fSetR), AlignLeft, 1);
	pV->addWidget(new CtLabel("FontTypeNormal AlignCenter", fSetL), AlignCenter, 1);
	pV->addWidget(new CtLabel("FontTypeNormal_alignCenter AlignCenter", fSetC), AlignCenter, 1);
	pV->addWidget(new CtLabel("FontTypeNormal_alignRight AlignCenter", fSetR), AlignCenter, 1);
	pV->addWidget(new CtLabel("FontTypeNormal AlignRight", fSetL), AlignRight, 1);
	pV->addWidget(new CtLabel("FontTypeNormal_alignCenter AlignRight", fSetC), AlignRight, 1);
	pV->addWidget(new CtLabel("FontTypeNormal_alignRight AlignRight", fSetR), AlignRight, 1);
#endif
#if 1
	pV->addWidget(new CtLabel("FontTypeNormal_alignAuto AlignLeft", fSetA), AlignLeft, 1);
	pV->addWidget(new CtLabel("FontTypeNormal_alignAuto AlignCenter", fSetA), AlignCenter, 1);
	pV->addWidget(new CtLabel("FontTypeNormal_alignAuto AlignRight", fSetA), AlignRight, 1);
#endif
#if 1
	pH = new CtHLayout();
	pH->addWidget(new CtLabel("Left", fSetL), 1);
	pH->addWidget(new CtLabel("Center", fSetC), 1);
	pH->addWidget(new CtLabel("Right", fSetR), 1);
	pV->addWidget(pH, 1);
#endif
#if 1
	pH = new CtHLayout();
	pH->addWidget(new CtLabel("Auto Left", fSetA), AlignLeft, 1);
	pH->addWidget(new CtLabel("Auto Center", fSetA), AlignCenter, 1);
	pH->addWidget(new CtLabel("Auto Right", fSetA), AlignRight, 1);
	pV->addWidget(pH, 1);
#endif
#if 1
	//	pLabel = new CtLabel("CtLabel FontTypeBold", fSetB);
	pParam = new CtParamLabel(AplParamSceneFileName, fSetB);
	pParam->setLabelType(CtParamLabel::TypeStrings);
	pParam->setForm("CtParamLabel FontTypeBold %s");
	pH = new CtHLayout();
	//	pH->addWidget(pLabel, 1);
	pH->addWidget(pParam, 1);
	pV->addWidget(pH, 1);
#endif

	return pV;
}
