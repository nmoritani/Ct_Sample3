/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_004
 */


#include "CtWindow_004.h"
#include "CtParamBox.h"
#include "CtMenuButton.h"
#include "CtAplParam.h"

CtWindow* CtWindow_004::createWindow()
{
	//CtDebugPrint(CtDbg, " CreateWindow ID:%d ---\n", id);

	CtVLayout* pLayout = new CtVLayout();
	CtParamBox *pLabel = NULL;

	CtMenuButton* pButton = NULL;
	pButton = new CtMenuButton(CtSize(800,60), new CtLabel("Contrast1: "));
	pLabel = new CtParamBox(AplParamLcdContrast);
	pLabel->setRange(0,10);
	pLabel->setForm("This is [%d]Hz");
	pButton->setTop(pLabel, AlignRight);
	pLayout->addWidget(pButton, AlignLeft);
	
	pButton = new CtMenuButton(CtSize(800,60), new CtLabel("Contrast2: "));
	pLabel = new CtParamBox(AplParamSuperGainSet);
	pLabel->setForm("%dPercent");
	pLabel->setRange(0,10);
	pButton->setTop(pLabel);
	pLabel = new CtParamBox(AplParamJpegImageInfo1_SdHdr);
	pLabel->setForm("ZZZ [%d]%");
	pLabel->setRange(0,20);
	pButton->setTop(pLabel, AlignRight);
	pLayout->addWidget(pButton, AlignLeft);

	
	pButton = new CtMenuButton(CtSize(800,60), new CtLabel("Contrast3: "));
	pLabel = new CtParamBox(AplParamJpegImageInfo1_SdHdr);
	pLabel->addLabel("HDR_OFF", 1, 0);
	pLabel->addLabel("HDR_LOW", 10, 3);
	pLabel->addLabel("HDR_HIGH", 11, 5);
	pLabel->addLabel("DRS_OFF", 5, 8);
	pLabel->addLabel("DRS_LOW", 7, 9);
	pLabel->addLabel("DRS_HIGH", 3, 10);
	
	pButton->setTop(pLabel);
	pLayout->addWidget(pButton, AlignLeft);
	
#if 0
	CtMenuButton* pMButton = NULL;
	pMButton = new CtMenuButton(CtSize(400,60), new CtLabel("Test Item"));
	
	pLabel = new CtParamBox(CtSize(400,60), AplParamVar);
	pLabel->setForm("This is [%d]Hz");
	pLabel->setRange(0, 10);
	pMButton->addWidget(pLabel);
	pLayout->addWidget(pMButton, AlignLeft);
	
	pLabel = new CtParamBox(CtSize(400,60), AplParamGammaPro);
	pLabel->setForm("ZZZ [%d]%");
	pLabel->setRange(0, 20);
	pLayout->addWidget(pLabel, AlignLeft);
#endif
	
	pLabel = new CtParamBox(CtSize(400,60), AplParamBlackGamma);
	pLayout->addWidget(pLabel, AlignLeft);
	m_pWin = new CtWindow(CtColor::darkGreen);
	m_pWin->addWidget(pLayout);
	
	return m_pWin;
}

CtWindow_004::CtWindow_004(CtWindowContents *pContents)
{
}

CtWindow_004::~CtWindow_004()
{
	destroyWindow();
}

bool CtWindow_004::destroyWindow()
{
	return true;
}

bool CtWindow_004::handleTouchEvent(const CtEventTouch& Touch)
{
	return false;
}
bool CtWindow_004::handleButtonEvent(const CtEventButton& Button) {
	switch (Button.getTimLv()) {
		case CtEventButton::Level_Invalid:
			if (Button.getPressType() == CtEventButton::ShortPress) {
				CtDebugPrint(CtDbg, "ShortPress\n");
			}
			else if (Button.getPressType() == CtEventButton::LongPress) {
				CtDebugPrint(CtDbg, "LongPress\n");
			}
			else if (Button.getPressType() == CtEventButton::RepeatPress) {
				CtDebugPrint(CtDbg, "RepeatPress\n");
			}
			else if (Button.getPressType() == CtEventButton::Release) {
				CtDebugPrint(CtDbg, "Release\n");
			}
			CtDebugPrint(CtDbg, "Long Press Level Invalid\n");
			break;
		case CtEventButton::Level_Default:
			// LongPressÇ‹Ç≈
			if (Button.getPressType() == CtEventButton::ShortPress) {
				CtDebugPrint(CtDbg, "ShortPress\n");
			}
			else if (Button.getPressType() == CtEventButton::LongPress) {
				CtDebugPrint(CtDbg, "LongPress\n");
			}
			else if (Button.getPressType() == CtEventButton::RepeatPress) {
				CtDebugPrint(CtDbg, "RepeatPress\n");
			}
			else if (Button.getPressType() == CtEventButton::Release) {
				CtDebugPrint(CtDbg, "Release\n");
			}
			CtDebugPrint(CtDbg, "Long Press Level Default\n");
			break;
		case CtEventButton::Level1:
			// LongPresså„
			if (Button.getPressType() == CtEventButton::ShortPress) {
				CtDebugPrint(CtDbg, "ShortPress\n");
			}
			else if (Button.getPressType() == CtEventButton::LongPress) {
				CtDebugPrint(CtDbg, "LongPress\n");
			}
			else if (Button.getPressType() == CtEventButton::RepeatPress) {
				CtDebugPrint(CtDbg, "RepeatPress\n");
			}
			else if (Button.getPressType() == CtEventButton::Release) {
				CtDebugPrint(CtDbg, "Release\n");
			}
			CtDebugPrint(CtDbg, "Long Press Level 1. LongPress\n");
			break;
		case CtEventButton::Level2:
			// Ç≥ÇÁÇ…LongPresså„
			if (Button.getPressType() == CtEventButton::ShortPress) {
				CtDebugPrint(CtDbg, "ShortPress\n");
			}
			else if (Button.getPressType() == CtEventButton::LongPress) {
				CtDebugPrint(CtDbg, "LongPress\n");
			}
			else if (Button.getPressType() == CtEventButton::RepeatPress) {
				CtDebugPrint(CtDbg, "RepeatPress\n");
			}
			else if (Button.getPressType() == CtEventButton::Release) {
				CtDebugPrint(CtDbg, "Release\n");
			}
			CtDebugPrint(CtDbg, "Long Press Level 2\n");
			break;
		case CtEventButton::Level3:
			// Ç≥ÇÁÇ…Ç≥ÇÁÇ…LongPresså„
			if (Button.getPressType() == CtEventButton::ShortPress) {
				CtDebugPrint(CtDbg, "ShortPress\n");
			}
			else if (Button.getPressType() == CtEventButton::LongPress) {
				CtDebugPrint(CtDbg, "LongPress\n");
			}
			else if (Button.getPressType() == CtEventButton::RepeatPress) {
				CtDebugPrint(CtDbg, "RepeatPress\n");
			}
			else if (Button.getPressType() == CtEventButton::Release) {
				CtDebugPrint(CtDbg, "Release\n");
			}
			CtDebugPrint(CtDbg, "Long Press Level 3\n");
			break;
		default:
			CtDebugPrint(CtDbg, "Long Press Level ÇΩÇ©Ç¢ÅIÇﬂÇ¡ÇøÇ·ÇΩÇ©Ç¢ÅI\n");
			break;
		}

	return false;
}
bool CtWindow_004::handleKeyEvent(const CtEventKey& Key) {
	//if (Key.getKeyCode() == CtEventKey::KeyCode_DialPressUp) {
	//	CtDebugPrint(CtDbg, "Dial Press Up\n");
	//	switch (Key.getTimLv()) {
	//	case Invalid:
	//		break;
	//	case CtEventKey::Level_Default:
	//		// LongPressÇ‹Ç≈
	//		CtDebugPrint(CtDbg, "Long Press Level Default\n");
	//		break;
	//	case CtEventKey::Level1:
	//		// LongPresså„
	//		CtDebugPrint(CtDbg, "Long Press Level 1. LongPress\n");
	//		break;
	//	case CtEventKey::Level2:
	//		// Ç≥ÇÁÇ…LongPresså„
	//		CtDebugPrint(CtDbg, "Long Press Level 2\n");
	//		break;
	//	case CtEventKey::Level3:
	//	default:
	//		// Ç≥ÇÁÇ…Ç≥ÇÁÇ…LongPresså„
	//		CtDebugPrint(CtDbg, "Long Press Level 3\n");
	//		break;
	//	}
	//}
	//else if (Key.getKeyCode() == CtEventKey::KeyCode_DialPressDown) {
	//	CtDebugPrint(CtDbg, "Dial Press Down\n");
	//	switch (Key.getTimLv()) {
	//	case CtEventKey::Level_Default:
	//		// âüâ∫íºå„
	//		CtDebugPrint(CtDbg, "Long Press Level 0 == Long Press Timer\n");
	//		break;
	//	case CtEventKey::Level1:
	//		// LongPresså„
	//		CtDebugPrint(CtDbg, "Long Press Level 1\n");
	//		break;
	//	case CtEventKey::Level2:
	//		// Ç≥ÇÁÇ…LongPresså„
	//		CtDebugPrint(CtDbg, "Long Press Level 2\n");
	//		break;
	//	case CtEventKey::Level3:
	//		// Ç≥ÇÁÇ…Ç≥ÇÁÇ…LongPresså„
	//		CtDebugPrint(CtDbg, "Long Press Level 3\n");
	//		break;
	//	}
	//}
	return false;
}