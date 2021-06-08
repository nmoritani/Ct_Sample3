/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtBuilderKeyboard
 */

#include "CtBuilderKeyboard.h"
#include <stdlib.h>

CtBuilderKeyboard::CtBuilderKeyboard(CtWindowID id) :
	m_WindowId(id),
	m_pFileContents(NULL),
	m_info(NULL),
	m_pText(NULL),
	m_pKeyboard(NULL),
	m_pCaps(NULL),
	m_pBS(NULL),
	m_pRet(NULL),
	m_pKigou(NULL),
	m_pSpace(NULL),
	m_pLeft(NULL),
	m_pRight(NULL),
	m_pEnter(NULL)
{
	setClassType(CtClassType_Interface);
}
CtBuilderKeyboard::~CtBuilderKeyboard()
{
}
void CtBuilderKeyboard::setContents(CtWindowContents* pContents)
{
	m_pFileContents = (CtWindowContentsFileInfo*)pContents;
}


CtLayout* CtBuilderKeyboard::createLayout()
{
	m_info = CtKeyboardInfo::getKeyboardInfo(m_WindowId);
	if (m_info == NULL) {
		CtDebugPrint(CtDbg, "%s --- That WindowID is invalid ---\n", __PRETTY_FUNCTION__);
		return NULL;
	}

	/* Title */
	CtContainerMenuTitle* pTitle = new CtContainerMenuTitle(m_WindowId);

	/* Main */
	CtLayout *pMain = createController();

	CtColor color = CtMenuInfo::getMenuBackColor();

	CtVLayout *pAll = new CtVLayout(color);
	pAll->addContainer(pTitle, 79);
	pAll->addWidget(new CtLabel(CtSize(960, 2), CtColor::White), 2);
	pAll->addWidget(pMain, 640 - 79 - 2);

	return pAll;
}

CtLayout* CtBuilderKeyboard::createController()
{
	/* TextField */
	CtLayout *pTextField = createTextField();
	/* Keyboard */
	CtLayout *pKeyboard = createKeyboard();

	CtVLayout *pLayout = new CtVLayout();
	pLayout->addStretch(KEYBOARD_H_SIZE_SPACE1);
	pLayout->addWidget(pTextField, KEYBOARD_H_SIZE_TEXT);
	pLayout->addStretch(KEYBOARD_H_SIZE_SPACE2);
	pLayout->addWidget(pKeyboard, KEYBOARD_H_SIZE_KEYBOARD);
	pLayout->addStretch(KEYBOARD_H_SIZE_SPACE3);

	return pLayout;
}

CtLayout* CtBuilderKeyboard::createTextField()
{
	/* Name */
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignRight, CtColor::White);
//	fSet.setSize(39);
	CtLabel *pName = NULL;
	if (m_info->StringId != STR_ID_MAX_SIZE) {
		pName = new CtLabel(m_info->StringId, fSet);
	}
	else {
		pName = new CtLabel(m_info->str, fSet);
	}
	
	/* BackGround */
	CtLayout *pBackGround = createTextField_BackGround();

	CtHLayout *pLayout = new CtHLayout();
	pLayout->addWidget(pName, CtMargin(0,14), AlignRight, 216);
	pLayout->addWidget(pBackGround, 600);
	pLayout->addStretch(144);

	return pLayout;
}
CtLayout* CtBuilderKeyboard::createTextField_BackGround()
{
	/* Back */
	const CtStyle::CtProperty& prop = CtStyle::getProperty();
	CtLabel *pBack = new CtLabel(CtRect(prop.Button.Normal.Base, prop.Button.StrokeWidth, prop.Button.Normal.Stroke));

	/* Text */
	m_pText = createTextField_BackGround_Text();

	CtLayout *pBackGround = new CtLayout();
	pBackGround->addWidget(pBack);
	pBackGround->addWidget(m_pText);

	return pBackGround;
}
CtTextField* CtBuilderKeyboard::createTextField_BackGround_Text()
{
	char str[520] = { 0 };

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	GDI_FONT_STYLE fstyle = { 48, LOCALE_FX, ASPECT_RATIO_DEFAULT, AUTO_ADJUST_DISABLE, FONT_ATTRIBUTE_NORMAL, HALIGN_LEFT, VALIGN_DEFAULT };
	fSet.fontStyle = fstyle;

	getText(str);

	CtTextField *pText = new CtTextField(str, fSet);
	if (CtKeyboardInfo::KeyboardType_PassWord == m_info->Type) {
		pText->setInitParam('*'); /* “ü—Í•¶Žš‚ð '*' ‚Å•\‚· */
	}

	return pText;
}

CtLayout* CtBuilderKeyboard::createKeyboard()
{
	createOthersKey();

	m_pKeyboard = new CtStackLabel();
	// CreateSmall
	m_pKeyboard->addLabel(createLargeStr(), 0);
	// CreateLarge
	m_pKeyboard->addLabel(createSmallStr(), 1);
	// CreateSymbols
	m_pKeyboard->addLabel(createSymbols(), 2);
	// CreateSymbols2
	m_pKeyboard->addLabel(createSymbols2(), 3);

	CtLayout* pKeyboard = new CtLayout();
	pKeyboard->addWidget(m_pKeyboard);

	CtVLayout *pAllKeyboard = new CtVLayout();
	pAllKeyboard->addWidget(pKeyboard, 304);
	pAllKeyboard->addStretch(35);
	pAllKeyboard->addWidget(createFuncKey(), 78);

	return pAllKeyboard;
}
void CtBuilderKeyboard::createOthersKey()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	fSet.setSize(39);

	/* Caps */
	m_pCaps = new CtToggleButton(AutoSize, "Caps", fSet);
	/* BS */
	m_pBS = new CtButton(AutoSize, "BS", fSet);

	/* Ret */
	m_pRet = new CtButton(AutoSize, new CtLabel(CtSize(58, 58), IC_MENU_RETURN));
	/* Kigou */
	{
		CtVLayout* pV = new CtVLayout();
		pV->addWidget(new CtLabel("123", CtFontSet(FontTypeNormal_alignCenter, CtColor::White)), 1);
		pV->addWidget(new CtLabel("#+=", CtFontSet(FontTypeNormal_alignCenter, CtColor::White)), 1);
		m_pKigou = new CtToggleButton(AutoSize, pV);
	}
	/* Space */
	m_pSpace = new CtButton(AutoSize, new CtLabel(CtSize(104, 58), IC_MENU_KB_SPACE));
	/* Left */
	m_pLeft = new CtButton(AutoSize, new CtLabel(CtSize(104, 58), IC_MENU_KB_LEFT));
	/* Right */
	m_pRight = new CtButton(AutoSize, new CtLabel(CtSize(104, 58), IC_MENU_KB_RIGHT));
	/* Enter */
	m_pEnter = new CtButton(AutoSize, new CtLabel(STR_ID_ICON_ENT, fSet));

	switch (m_info->Type) {
	case CtKeyboardInfo::KeyboardType_PassWord:
		m_pSpace->setInvalid(true);
		m_pLeft->setInvalid(true);
		m_pRight->setInvalid(true);
		break;
	case CtKeyboardInfo::KeyboardType_Ip:
	case CtKeyboardInfo::KeyboardType_IpV6:
	case CtKeyboardInfo::KeyboardType_Number:
	case CtKeyboardInfo::KeyboardType_Alpha:
		m_pCaps->setInvalid(true);
		m_pKigou->setInvalid(true);
		m_pSpace->setInvalid(true);
		break;
	case CtKeyboardInfo::KeyboardType_FileName:
		m_pCaps->setInvalid(true);
		break;
	default:
		break;
	}
}

CtLayout* CtBuilderKeyboard::createLargeStr() {
	switch (m_info->Type) {
	case CtKeyboardInfo::KeyboardType_Ip:
	case CtKeyboardInfo::KeyboardType_IpV6:
	case CtKeyboardInfo::KeyboardType_Number:
		return new CtLayout();
	default:
		break;
	}
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	fSet.setSize(39);

	/* Line1 */
	CtHLayout *pLine1 = new CtHLayout();

	pLine1->addStretch(KEYBOARD_AREA_SPACE);

	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("Q", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("W", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("E", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("R", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("T", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("Y", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("U", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("I", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("O", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("P", fSet)), BUTTON_H);

	pLine1->addStretch(KEYBOARD_AREA_SPACE);

	/* Line2 */
	CtHLayout *pLine2 = new CtHLayout();

	pLine2->addStretch(KEYBOARD_AREA_SPACE2_1);

	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("A", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("S", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("D", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("F", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("G", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("H", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("J", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("K", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("L", fSet)), BUTTON_H);

	pLine2->addStretch(KEYBOARD_AREA_SPACE2_2);

	/* Line3 */
	CtHLayout *pLine3 = new CtHLayout();
	pLine3->addStretch(KEYBOARD_AREA_SPACE);
	pLine3->addWidget(m_pCaps, 124);

	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("Z", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("X", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("C", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("V", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("B", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("N", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("M", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);

	pLine3->addWidget(m_pBS, 124);
	pLine3->addStretch(KEYBOARD_AREA_SPACE);

	CtVLayout *pLayout = new CtVLayout();
	pLayout->addWidget(pLine1, 78);
	pLayout->addStretch(35);
	pLayout->addWidget(pLine2, 78);
	pLayout->addStretch(35);
	pLayout->addWidget(pLine3, 78);

	return pLayout;
}
CtLayout* CtBuilderKeyboard::createSmallStr() {
	switch (m_info->Type) {
	case CtKeyboardInfo::KeyboardType_FileName:
	case CtKeyboardInfo::KeyboardType_Ip:
	case CtKeyboardInfo::KeyboardType_IpV6:
	case CtKeyboardInfo::KeyboardType_Alpha:
	case CtKeyboardInfo::KeyboardType_Number:
		return new CtLayout();
	default:
		break;
	}
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	fSet.setSize(39);
	/* Line1 */
	CtHLayout *pLine1 = new CtHLayout();
	pLine1->addStretch(KEYBOARD_AREA_SPACE);

	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("q", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("w", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("e", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("r", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("t", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("y", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("u", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("i", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("o", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("p", fSet)), BUTTON_H);

	pLine1->addStretch(KEYBOARD_AREA_SPACE);

	/* Line2 */
	CtHLayout *pLine2 = new CtHLayout();
	pLine2->addStretch(KEYBOARD_AREA_SPACE2_1);

	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("a", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("s", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("d", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("f", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("g", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("h", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("j", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("k", fSet)), BUTTON_H);
	pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine2->addWidget(new CtButton(AutoSize, new CtLabel("l", fSet)), BUTTON_H);

	pLine2->addStretch(KEYBOARD_AREA_SPACE2_2);

	/* Line3 */
	CtHLayout *pLine3 = new CtHLayout();
	pLine3->addStretch(KEYBOARD_AREA_SPACE);
	pLine3->addWidget(m_pCaps, 124);

	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("z", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("x", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("c", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("v", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("b", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("n", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine3->addWidget(new CtButton(AutoSize, new CtLabel("m", fSet)), BUTTON_H);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);

	pLine3->addWidget(m_pBS, 124);
	pLine3->addStretch(KEYBOARD_AREA_SPACE);


	CtVLayout *pLayout = new CtVLayout();
	pLayout->addWidget(pLine1, 78);
	pLayout->addStretch(35);
	pLayout->addWidget(pLine2, 78);
	pLayout->addStretch(35);
	pLayout->addWidget(pLine3, 78);

	return pLayout;
}
CtLayout* CtBuilderKeyboard::createSymbols() {
	switch (m_info->Type) {
	case CtKeyboardInfo::KeyboardType_Alpha:
		return new CtLayout();
	default:
		break;
	}

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	fSet.setSize(39);
	/* Line1 */
	CtHLayout *pLine1 = new CtHLayout();

	pLine1->addStretch(KEYBOARD_AREA_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("1", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("2", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("3", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("4", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("5", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("6", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("7", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("8", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("9", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("0", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_SPACE);

	/* Line2 */
	CtHLayout *pLine2 = new CtHLayout();

	pLine2->addStretch(KEYBOARD_AREA_SPACE2_1);
	switch (m_info->Type) {
	case CtKeyboardInfo::KeyboardType_Number:
		for (int i = 0; i < 9; i++) {
			pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
			pLine2->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
		}
		break;
	case CtKeyboardInfo::KeyboardType_Ip:
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel(".", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		for (int i = 0; i < 8; i++) {
			pLine2->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
			pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		}
		break;
	case CtKeyboardInfo::KeyboardType_FileName:
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("#", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("=", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("_", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("@", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("!", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("-", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
		break;
	case CtKeyboardInfo::KeyboardType_IpV6:
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("a", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("b", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("c", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("d", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("e", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("f", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel(":", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
		break;
	default:
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("-", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("/", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel(":", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel(";", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("(", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel(")", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("$", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("&", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("@", fSet)), BUTTON_H);
		break;
	}
	pLine2->addStretch(KEYBOARD_AREA_SPACE2_2);

	/* Line3 */
	CtHLayout *pLine3 = new CtHLayout();
	pLine3->addStretch(KEYBOARD_AREA_SPACE);
	pLine3->addWidget(m_pCaps, 124);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);


	switch (m_info->Type) {
	case CtKeyboardInfo::KeyboardType_Number:
	case CtKeyboardInfo::KeyboardType_Ip:
	case CtKeyboardInfo::KeyboardType_IpV6:
	case CtKeyboardInfo::KeyboardType_FileName:
		for (int i = 0; i < 7; i++) {
			pLine3->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
			pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		}
		break;
	default:
		pLine3->addWidget(new CtButton(AutoSize, new CtLabel(".", fSet)), BUTTON_H);
		pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine3->addWidget(new CtButton(AutoSize, new CtLabel(",", fSet)), BUTTON_H);
		pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine3->addWidget(new CtButton(AutoSize, new CtLabel("?", fSet)), BUTTON_H);
		pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine3->addWidget(new CtButton(AutoSize, new CtLabel("!", fSet)), BUTTON_H);
		pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine3->addWidget(new CtButton(AutoSize, new CtLabel("'", fSet)), BUTTON_H);
		pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine3->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
		pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine3->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
		pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);

		break;
	}

	pLine3->addWidget(m_pBS, 124);
	pLine3->addStretch(KEYBOARD_AREA_SPACE);

	CtVLayout *pLayout = new CtVLayout();
	pLayout->addWidget(pLine1, 78);
	pLayout->addStretch(35);
	pLayout->addWidget(pLine2, 78);
	pLayout->addStretch(35);
	pLayout->addWidget(pLine3, 78);

	return pLayout;
}
CtLayout* CtBuilderKeyboard::createSymbols2() {
	switch (m_info->Type) {
	case CtKeyboardInfo::KeyboardType_Alpha:
	case CtKeyboardInfo::KeyboardType_Ip:
	case CtKeyboardInfo::KeyboardType_IpV6:
	case CtKeyboardInfo::KeyboardType_Number:
	case CtKeyboardInfo::KeyboardType_FileName:
		return new CtLayout();
	default:
		break;
	}

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	fSet.setSize(39);
	/* Line1 */
	CtHLayout *pLine1 = new CtHLayout();

	pLine1->addStretch(KEYBOARD_AREA_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("1", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("2", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("3", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("4", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("5", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("6", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("7", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("8", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("9", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	pLine1->addWidget(new CtButton(AutoSize, new CtLabel("0", fSet)), BUTTON_H);
	pLine1->addStretch(KEYBOARD_AREA_SPACE);

	/* Line2 */
	CtHLayout *pLine2 = new CtHLayout();

	pLine2->addStretch(KEYBOARD_AREA_SPACE2_1);
	switch (m_info->Type) {
	case CtKeyboardInfo::KeyboardType_Number:
		for (int i = 0; i < 9; i++) {
			pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
			pLine2->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
		}
		break;
	default:
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("_", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("#", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("%", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("|", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("[", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("]", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("*", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("+", fSet)), BUTTON_H);
		pLine2->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
		pLine2->addWidget(new CtButton(AutoSize, new CtLabel("=", fSet)), BUTTON_H);

		break;
	}
	pLine2->addStretch(KEYBOARD_AREA_SPACE2_2);

	/* Line3 */
	CtHLayout *pLine3 = new CtHLayout();
	pLine3->addStretch(KEYBOARD_AREA_SPACE);
	pLine3->addWidget(m_pCaps, 124);
	pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);

	for (int i = 0; i < 7; i++) {
		pLine3->addWidget(new CtLabel(AutoSize, CtRoundRect(CtColor(46, 46, 46, 0xff))), BUTTON_H);
		pLine3->addStretch(KEYBOARD_AREA_BUTTON_SPACE);
	}

	pLine3->addWidget(m_pBS, 124);
	pLine3->addStretch(KEYBOARD_AREA_SPACE);

	CtVLayout *pLayout = new CtVLayout();
	pLayout->addWidget(pLine1, 78);
	pLayout->addStretch(35);
	pLayout->addWidget(pLine2, 78);
	pLayout->addStretch(35);
	pLayout->addWidget(pLine3, 78);

	return pLayout;
}
CtLayout* CtBuilderKeyboard::createFuncKey()
{
	CtHLayout* pLayout = new CtHLayout();
	pLayout->addStretch(14);
	pLayout->addWidget(m_pRet, 78);
	pLayout->addStretch(64);
	pLayout->addWidget(m_pKigou, 124);
	pLayout->addStretch(35);
	pLayout->addWidget(m_pSpace, 124);
	pLayout->addStretch(35);
	pLayout->addWidget(m_pLeft, 124);
	pLayout->addStretch(35);
	pLayout->addWidget(m_pRight, 124);
	pLayout->addStretch(64);
	pLayout->addWidget(m_pEnter, 124);
	pLayout->addStretch(15);

	return pLayout;
}

void CtBuilderKeyboard::getText(char* str)
{
	if (str == NULL) { 
		str = "";
		return;
	}
	switch (m_info->Text) {
	case CtKeyboardInfo::TextType_Default:
		APL_PARAM_GET_DATA_AREA(m_info->ParamId, (unsigned char *)str, m_info->Size);
		str[m_info->Size] = 0;
		break;

	case CtKeyboardInfo::TextType_Number0:
		sprintf(str, "%0*d", m_info->Size, APL_PARAM_GET_DATA(m_info->ParamId));
		str[m_info->Size] = 0;
		break;

	case CtKeyboardInfo::TextType_Number:
		sprintf(str, "%d",  APL_PARAM_GET_DATA(m_info->ParamId));
		str[m_info->Size] = 0;
		break;

	case CtKeyboardInfo::TextType_Special:
	{
		AplParamEepromId tmpeep = AplParamSceneFileName1;
		switch (APL_PARAM_GET_DATA(AplParamSceneMode)) {
		case APL_SYS_PARAM_SCENE_MODE_1:   tmpeep = AplParamSceneFileName1;   break;
		case APL_SYS_PARAM_SCENE_MODE_2:   tmpeep = AplParamSceneFileName2;   break;
		case APL_SYS_PARAM_SCENE_MODE_3:   tmpeep = AplParamSceneFileName3;   break;
		case APL_SYS_PARAM_SCENE_MODE_4:   tmpeep = AplParamSceneFileName4;   break;
		case APL_SYS_PARAM_SCENE_MODE_5:   tmpeep = AplParamSceneFileName5;   break;
		case APL_SYS_PARAM_SCENE_MODE_6:   tmpeep = AplParamSceneFileName6;   break;
		default:   break;
		}
		APL_PARAM_GET_DATA_AREA(tmpeep, (unsigned char *)str, m_info->Size);
		str[m_info->Size] = 0;
		break;
	}

	case CtKeyboardInfo::TextType_Ip:
	{
		unsigned char IP[4] = { '0' };
		APL_PARAM_GET_DATA_AREA(m_info->ParamId, (unsigned char *)IP, 4);
		sprintf(str, "%d.%d.%d.%d", IP[0], IP[1], IP[2], IP[3]);
		break;
	}

	case CtKeyboardInfo::TextType_File:
		if (m_pFileContents == NULL)
			break;
		CtWindowContentsFileInfo::FileInfoListItr Itr;
		Itr = m_pFileContents->getFileInfoList().begin();

		if (Itr != NULL) {
			sprintf(str, "%s", (*(Itr + m_pFileContents->getCurrentIndex()))->getFileInfo().FileName);
		}
		str[m_info->Size] = 0;
		break;

	case CtKeyboardInfo::TextType_None:
		sprintf(str, "");
		break;
	default:
		break;
	}
}
