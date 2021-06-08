/**
 *  Copyright (c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtWindow_TransitionTest.h"


CtWindow_TransitionTest::TransitionInfo CtWindow_TransitionTest::Table[] = {
	{ Window_Test_A_1_1,  "A 1-1",  1,  1 },
	{ Window_Test_A_1_2,  "A 1-2",  1,  2 },
	{ Window_Test_A_1_3,  "A 1-3",  1,  3 },
	{ Window_Test_A_2_1,  "A 2-1",  2,  1 },
	{ Window_Test_A_2_2,  "A 2-2",  2,  2 },
	{ Window_Test_A_2_3,  "A 2-3",  2,  3 },
	{ Window_Test_A_3_1,  "A 3-1",  3,  1 },
	{ Window_Test_A_3_2,  "A 3-2",  3,  2 },
	{ Window_Test_A_3_3,  "A 3-3",  3,  3 },
	{ Window_Test_B_1_1,  "B 1-1",  1,  1 },
	{ Window_Test_B_1_2,  "B 1-2",  1,  2 },
	{ Window_Test_B_1_3,  "B 1-3",  1,  3 },
	{ Window_Test_B_2_1,  "B 2-1",  2,  1 },
	{ Window_Test_B_2_2,  "B 2-2",  2,  2 },
	{ Window_Test_B_2_3,  "B 2-3",  2,  3 },
	{ Window_Test_B_3_1,  "B 3-1",  3,  1 },
	{ Window_Test_B_3_2,  "B 3-2",  3,  2 },
	{ Window_Test_B_3_3,  "B 3-3",  3,  3 },
};

CtWindow_TransitionTest::CtWindow_TransitionTest()
{
}
CtWindow_TransitionTest::~CtWindow_TransitionTest()
{
	destroyWindow();
}
bool CtWindow_TransitionTest::destroyWindow()
{
	return true;
}
CtWindow* CtWindow_TransitionTest::createWindow()
{
	m_pWin = new CtWindow();

	CtLayout* pLayout = createLayout();

	m_pWin->addWidget(pLayout);
	m_pWin->setName("WindowTest");

	return m_pWin;
}

CtWindow_TransitionTest::TransitionInfo* CtWindow_TransitionTest::getInfo(CtWindowID id)
{
	for (int Index = 0; Index < sizeof(Table) / sizeof(TransitionInfo); Index++) {
		if (id == Table[Index].WinId) {
			return &Table[Index];
		}
	}
	return NULL;
}

CtLayout* CtWindow_TransitionTest::createLayout()
{
	TransitionInfo* Info = getInfo(getWindowID());

	/* Label */
	CtLabel* pLabel = new CtLabel(Info->Str);

	/* Column */
	CtHLayout* pColumn = new CtHLayout();
	for (int i = 1; i <= 3; i++) {
		if (i == Info->Column) {
			pColumn->addWidget(pLabel, 1);
		}
		else {
			pColumn->addStretch(1);
		}
	}

	/* Row */
	CtVLayout* pRow = new CtVLayout();
	for (int i = 3; i >= 1; i--) {
		if (i == Info->Row) {
			pRow->addWidget(pColumn, 1);
		}
		else {
			pRow->addStretch(1);
		}
	}

	/* Layout */
	CtLayout* pLayout = new CtLayout(CtColor(ColorRGBA, 0x00000019, NULL));

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter_Top, CtColor::White);
	fSet.setSize(40);
	pLayout->addWidget(new CtLabel("Transition Test", fSet));
	pLayout->addWidget(pRow);

	return pLayout;
}

