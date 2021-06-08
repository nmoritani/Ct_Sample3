/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMessageWindowFactory
 */

#include "CtMessageWindowFactory.h"
#include "CtMessageInfo.h"
#include "CtWindow_Message.h"
#include "CtWindow_Common_Message.h"

CtWindowMain* CtMessageWindowFactory::create(CtWindowID id,  CtWindowContents *pContents)
{
	CtWindowMain *pWin = NULL;

	if (CtMessageInfo::chackWindow(id)) {
		pWin = new CtWindow_Message(id, pContents);  /* pgr0541 */
	}

#if 0
	switch (id) {
	case Window_CommonMessage:
		pWin = new CtWindow_Common_Message(pContents);  /* pgr0541 */
		break;

	case Window_WizardMessage:
		pWin = new CtWindow_Wizard_Message(pContents);  /* pgr0541 */
		break;

	default:
		break;
	}
#endif

	if (pWin != NULL) {
		pWin->setWindowID(id);
	}

	return pWin;
}
