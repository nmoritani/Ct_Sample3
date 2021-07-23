/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_002
 */


#include "CtWindow_002.h"

static CtHLayout *createStringLayout(CtFontSet fSet)
{
	fSet.setSize(30);
    //	fSet.fontStyle.noUseCache = true;

#if 0	//太字の動作確認
	fSet.setEdgeColor(CtColor::White);
	fSet.edgeWidth = 10;
#endif
#if 0	//縁取りの動作確認
	fSet.setEdgeColor(CtColor::Black);
	fSet.edgeWidth = 10;
#endif

	CtHLayout *pLayout001 = new CtHLayout();
	pLayout001->addWidget(new CtLabel("abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ", fSet), 0, AlignBottom, 50);
	return pLayout001;
}

CtWindow* CtWindow_002::createWindow()
{
	//CtDebugPrint(CtDbg, " CreateWindow ID:%d ---\n", id);

	CtWindow* pWin = new CtWindow();

	unsigned short test1[] = { 0x30D3, 0x30C3, 0x30C8, 0x30DE, 0x30C3, 0x30D7, 0x30D5, 0x30A9, 0x30F3, 0x30C8, 0x306E, 0x6F22, 0x5B57, 0x63CF, 0x753B, 0x3067, 0x3059, 0x3088, 0x0000 };
	CtHLayout *pLayout000 = new CtHLayout();
	CtFontSet fSet = CtFontSet(CtColor::White);
	fSet.setFontAttribute(FontTypeMono);
	fSet.setSize(40);
	fSet.setLocale(LOCALE_JP);
    //	fSet.fontStyle.noUseCache = true;

	pLayout000->addWidget(new CtLabel(test1, fSet), 0, AlignBottom, 27);


	CtFontSet fSet0 = CtFontSet(FontTypeMono_Bottom, CtColor::White);
	CtFontSet fSet1 = CtFontSet(FontTypeMono_Bottom, CtColor::White);
	CtFontSet fSet2 = CtFontSet(FontTypeMono_Bottom, CtColor::White);
	CtFontSet fSet3 = CtFontSet(FontTypeMono_Bottom, CtColor::White);
	CtFontSet fSet4 = CtFontSet(FontTypeMono_Bottom, CtColor::White);
	CtFontSet fSet5 = CtFontSet(FontTypeMono_Bottom, CtColor::White);
	CtFontSet fSet6 = CtFontSet(FontTypeMono_Bottom, CtColor::White);
	CtFontSet fSet7 = CtFontSet(FontTypeMono_Bottom, CtColor::White);
	CtFontSet fSet8 = CtFontSet(FontTypeMono_Bottom, CtColor::White);
	CtFontSet fSet9 = CtFontSet(FontTypeMono_Bottom, CtColor::White);
	CtFontSet fSet10 = CtFontSet(FontTypeMono_Bottom, CtColor::White);

	fSet0.setLocale(LOCALE_EN);
	fSet1.setLocale(LOCALE_JP);
	fSet2.setLocale(LOCALE_SC);
	fSet3.setLocale(LOCALE_TC);
	fSet4.setLocale(LOCALE_KR);
	fSet5.setLocale(LOCALE_AR);
	fSet6.setLocale(LOCALE_TH);
	fSet7.setLocale(LOCALE_HI);
	fSet8.setLocale(LOCALE_EN2);
	fSet9.setLocale(LOCALE_IC);
	fSet10.setLocale(LOCALE_FX);

	CtVLayout *pLayoutAll = new CtVLayout();
	pLayoutAll->addWidget(pLayout000);
	pLayoutAll->addWidget(createStringLayout(fSet0));
	pLayoutAll->addWidget(createStringLayout(fSet1));
	pLayoutAll->addWidget(createStringLayout(fSet2));
	pLayoutAll->addWidget(createStringLayout(fSet3));
	pLayoutAll->addWidget(createStringLayout(fSet4));
	pLayoutAll->addWidget(createStringLayout(fSet5));
	pLayoutAll->addWidget(createStringLayout(fSet6));
	pLayoutAll->addWidget(createStringLayout(fSet7));
	pLayoutAll->addWidget(createStringLayout(fSet8));
	pLayoutAll->addWidget(createStringLayout(fSet9));
	pLayoutAll->addWidget(createStringLayout(fSet10));
	pWin->addWidget(pLayoutAll);

    pWin->setColor(CtColor::darkolivegreen);

	return pWin;
}

CtWindow_002::CtWindow_002(CtWindowContents *pContents)
{
}

CtWindow_002::~CtWindow_002()
{
}



