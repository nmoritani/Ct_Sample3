/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtKeyboad
 */
#include "CtKeyboad.h"
#include "CtGridLayout.h"

CtKeyboad::CtKeyboad() :
	m_pText(),
	m_pKomoji(),
	m_pKigou(),
	m_pBS(),
	m_pRet(),
	m_pEnter(),
	m_pLeft(),
	m_pRight(),
	m_pSpace(),
	m_pKeyboad()
{
	setClassType(CtClassType_LayoutMain);
}


CtLayout* CtKeyboad::createContainer()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	GDI_FONT_STYLE fstyle = {48, LOCALE_EN, ASPECT_RATIO_DEFAULT, AUTO_ADJUST_DISABLE, FONT_ATTRIBUTE_NORMAL, HALIGN_LEFT, VALIGN_DEFAULT};
	fSet.fontStyle = fstyle;
	
	//	m_pText = new CtTextField("1234567890qawsedrftgyhujikolp;@:[]1234567890", fSet);
	m_pText = new CtTextField("1234567890q;", fSet);
	m_pText->setColor(CtColor::darkGreen);
	
	CtHLayout *pTitle = new CtHLayout();
	pTitle->addWidget(new CtLabel("Name:"), AlignRight, 1);
	pTitle->addWidget(m_pText, 3);
	pTitle->setColor(CtColor::darkBlue);
#if 0
	m_pKomoji = new CtButton("A-a");
	m_pKigou = new CtButton("123");
#else
	m_pKomoji = new CtToggleButton("A-a");
	m_pKigou = new CtToggleButton("123");
#endif
	m_pBS = new CtButton("BS");
	m_pRet = new CtButton(IC_MENU_RETURN);
	m_pEnter = new CtButton("Enter");
	m_pLeft = new CtButton(IC_MENU_KB_LEFT);
	m_pRight = new CtButton(IC_MENU_KB_RIGHT);
	m_pSpace = new CtButton(IC_MENU_KB_SPACE);

	int Col = 10;
	int Row = 3;


	m_pKeyboad = new CtStackLabel();
	
	CtGridLayout *pKey = new CtGridLayout(Row,Col);
	pKey->setElementsMargin(CtMargin(4,4,4,4));
	pKey->setWidget(new CtButton("Q"), 0, 0);
	pKey->setWidget(new CtButton("W"), 0, 1);
	pKey->setWidget(new CtButton("E"), 0, 2);
	pKey->setWidget(new CtButton("R"), 0, 3);
	pKey->setWidget(new CtButton("T"), 0, 4);
	pKey->setWidget(new CtButton("Y"), 0, 5);
	pKey->setWidget(new CtButton("U"), 0, 6);
	pKey->setWidget(new CtButton("I"), 0, 7);
	pKey->setWidget(new CtButton("O"), 0, 8);
	pKey->setWidget(new CtButton("P"), 0, 9);

	pKey->setWidget(new CtButton("A"), 1, 0);
	pKey->setWidget(new CtButton("S"), 1, 1);
	pKey->setWidget(new CtButton("D"), 1, 2);
	pKey->setWidget(new CtButton("F"), 1, 3);
	pKey->setWidget(new CtButton("G"), 1, 4);
	pKey->setWidget(new CtButton("H"), 1, 5);
	pKey->setWidget(new CtButton("J"), 1, 6);
	pKey->setWidget(new CtButton("K"), 1, 7);
	pKey->setWidget(new CtButton("L"), 1, 8);
	
	pKey->setWidget(m_pKomoji,         2, 1);
	pKey->setWidget(new CtButton("Z"), 2, 2);
	pKey->setWidget(new CtButton("X"), 2, 3);
	pKey->setWidget(new CtButton("C"), 2, 4);
	pKey->setWidget(new CtButton("V"), 2, 5);
	pKey->setWidget(new CtButton("B"), 2, 6);
	pKey->setWidget(new CtButton("N"), 2, 7);
	pKey->setWidget(new CtButton("M"), 2, 8);
	pKey->setWidget(m_pBS,             2, 9);
	m_pKeyboad->addLabel(pKey);

	pKey = new CtGridLayout(Row,Col);
	pKey->setElementsMargin(CtMargin(4,4,4,4));
	pKey->setWidget(new CtButton("q"), 0, 0);
	pKey->setWidget(new CtButton("w"), 0, 1);
	pKey->setWidget(new CtButton("e"), 0, 2);
	pKey->setWidget(new CtButton("r"), 0, 3);
	pKey->setWidget(new CtButton("t"), 0, 4);
	pKey->setWidget(new CtButton("y"), 0, 5);
	pKey->setWidget(new CtButton("u"), 0, 6);
	pKey->setWidget(new CtButton("i"), 0, 7);
	pKey->setWidget(new CtButton("o"), 0, 8);
	pKey->setWidget(new CtButton("p"), 0, 9);

	pKey->setWidget(new CtButton("a"), 1, 0);
	pKey->setWidget(new CtButton("s"), 1, 1);
	pKey->setWidget(new CtButton("d"), 1, 2);
	pKey->setWidget(new CtButton("f"), 1, 3);
	pKey->setWidget(new CtButton("g"), 1, 4);
	pKey->setWidget(new CtButton("h"), 1, 5);
	pKey->setWidget(new CtButton("j"), 1, 6);
	pKey->setWidget(new CtButton("k"), 1, 7);
	pKey->setWidget(new CtButton("l"), 1, 8);

	pKey->setWidget(m_pKomoji,         2, 1);
	pKey->setWidget(new CtButton("z"), 2, 2);
	pKey->setWidget(new CtButton("x"), 2, 3);
	pKey->setWidget(new CtButton("c"), 2, 4);
	pKey->setWidget(new CtButton("v"), 2, 5);
	pKey->setWidget(new CtButton("b"), 2, 6);
	pKey->setWidget(new CtButton("n"), 2, 7);
	pKey->setWidget(new CtButton("m"), 2, 8);
	pKey->setWidget(m_pBS,             2, 9);
	m_pKeyboad->addLabel(pKey);

	pKey = new CtGridLayout(Row, Col);
	pKey->setElementsMargin(CtMargin(4,4,4,4));
	pKey->setWidget(new CtButton("0"), 0, 0);
	pKey->setWidget(new CtButton("1"), 0, 1);
	pKey->setWidget(new CtButton("2"), 0, 2);
	pKey->setWidget(new CtButton("3"), 0, 3);
	pKey->setWidget(new CtButton("4"), 0, 4);
	pKey->setWidget(new CtButton("5"), 0, 5);
	pKey->setWidget(new CtButton("6"), 0, 6);
	pKey->setWidget(new CtButton("7"), 0, 7);
	pKey->setWidget(new CtButton("8"), 0, 8);
	pKey->setWidget(new CtButton("9"), 0, 9);

	pKey->setWidget(new CtButton("#"), 1, 0);
	pKey->setWidget(new CtButton("."), 1, 1);
	pKey->setWidget(new CtButton("="), 1, 2);
	pKey->setWidget(new CtButton("-"), 1, 3);
	pKey->setWidget(new CtButton("@"), 1, 4);
	pKey->setWidget(new CtButton("!"), 1, 5);
	pKey->setWidget(new CtLabel(CtRoundRect()), 1, 6);
	pKey->setWidget(new CtLabel(CtRoundRect()), 1, 7);
	pKey->setWidget(new CtLabel(CtRoundRect()), 1, 8);

	pKey->setWidget(m_pKomoji, 2, 1);
	pKey->setWidget(new CtLabel(CtRoundRect()), 2, 2);
	pKey->setWidget(new CtLabel(CtRoundRect()), 2, 3);
	pKey->setWidget(new CtLabel(CtRoundRect()), 2, 4);
	pKey->setWidget(new CtLabel(CtRoundRect()), 2, 5);
	pKey->setWidget(new CtLabel(CtRoundRect()), 2, 6);
	pKey->setWidget(new CtLabel(CtRoundRect()), 2, 7);
	pKey->setWidget(new CtLabel(CtRoundRect()), 2, 8);
	pKey->setWidget(m_pBS, 2, 9);
	m_pKeyboad->addLabel(pKey);
	
	CtHLayout *pControl = new CtHLayout();
    pControl->addStretch(1);
	pControl->addWidget(m_pRet);
	pControl->addWidget(m_pKigou);
	pControl->addWidget(m_pSpace);
	pControl->addWidget(m_pLeft);
	pControl->addWidget(m_pRight);
	pControl->addWidget(m_pEnter);
    pControl->addStretch(1);
    //	pControl->addWidget(new CtLabel(CtEllipse(CtColor::red, 2, CtColor::yellow)));
    //	pControl->addWidget(new CtLabel(CtFill(CtColor::red)));

	m_pBox = new CtVLayout();
	m_pBox->addWidget(pTitle, CtMargin(10,10,40,40), 1);
	m_pBox->addWidget(m_pKeyboad, CtMargin(10,10,40,40),4);
	m_pBox->addWidget(pControl, CtMargin(10,10,40,40), 1);
	m_pBox->setColor(CtColor::Black);
	
	return m_pBox;
}

bool CtKeyboad::destroyContainer()
{
	return true;
}

bool CtKeyboad::handleButtonEvent(const CtEventButton& Button)
{

	if( Button.getPressType() != CtEventButton::Release ){
		return false;
	}
	if (Button.getWidgetID() == m_pKomoji->getWidgetID()) {
#if 1
		if (m_pKomoji->isSelected() == true) {
			m_pKeyboad->index(1);
		} else {
			m_pKeyboad->index(0);
		}
		
	} else if (Button.getWidgetID() == m_pKigou->getWidgetID()) {
		if (m_pKigou->isSelected() == true) {
			m_pKeyboad->index(2);
		} else {
			m_pKeyboad->index(0);
		}
#endif
	} else if (Button.getWidgetID() == m_pSpace->getWidgetID()) {
		m_pText->insertChar(' ');
	} else if (Button.getWidgetID() == m_pLeft->getWidgetID()) {
		m_pText->backwardCursor();
		
	} else if (Button.getWidgetID() == m_pRight->getWidgetID()) {
		m_pText->forwardCursor();
		
	} else if (Button.getWidgetID() == m_pBS->getWidgetID()) {
		m_pText->deleteChar();
		
	} else {
		unsigned short * str;
		CtButton* pButton = (CtButton*)Button.getWidget();

		if (pButton->isLabel() == true) {
			if ((str = static_cast<CtLabel*>(pButton)->getText()) != NULL) {
				m_pText->insertChar((char)(str[0] & 0xff));
			}
		}
	}
	
	return true;
}

CtKeyboad::~CtKeyboad()
{
}

