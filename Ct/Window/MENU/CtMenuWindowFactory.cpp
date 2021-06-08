/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:            CtMenuWindowFactory
 */


#include "CtMenuWindowFactory.h"

CtWindowMain* CtMenuWindowFactory::create(CtWindowID id,  CtWindowContents *pContents)
{
    CtWindowMain *pWin = NULL;

	if (CtInterface::getInstance()->checkWindowCategory(id))
		return NULL;

	CtMenuInfo::CtMenuWindowType WindowType = CtMenuInfo::getWindowType(id);

	if (WindowType == CtMenuInfo::WINDOW_TYPE_MAX) {
		switch ((id & 0xFFFF0000)){
		case WindowCategory_MenuAreaSetting:
			// AreaSetting‚ÍCtWindowFactory‚Ås‚¤
			WindowType = CtMenuInfo::WINDOW_TYPE_MAX;
			break;
		case WindowCategory_Dialog:
			WindowType = CtMenuInfo::WINDOW_TYPE_DIALOG;
			break;
		case WindowCategory_Keyboard:
			WindowType = CtMenuInfo::WINDOW_TYPE_KEYBOARD;
			break;
		case WindowCategory_SpinBox:
			WindowType = CtMenuInfo::WINDOW_TYPE_SPINBOX;
			break;
		default:
			break;
		}
	}

    switch (WindowType) {
        case CtMenuInfo::WINDOW_TYPE_LIST:				pWin = new CtWindowMenu(pContents);                 break;    /* pgr0541 */
		case CtMenuInfo::WINDOW_TYPE_CHECKLIST:			pWin = new CtWindowMenu(pContents);                 break;    /* pgr0541 */
		case CtMenuInfo::WINDOW_TYPE_POPLIST:			pWin = new CtWindowMenu(pContents);                 break;    /* pgr0541 */
		case CtMenuInfo::WINDOW_TYPE_KEYBOARD:			pWin = new CtWindow_Keyboard(pContents);            break;    /* pgr0541 */
		case CtMenuInfo::WINDOW_TYPE_SPINBOX:			pWin = new CtWindow_SpinBox(id);                    break;
        case CtMenuInfo::WINDOW_TYPE_DIALOG:			pWin = new CtWindow_Dialog(id, pContents );			break;    /* pgr0541 */
        case CtMenuInfo::WINDOW_TYPE_WORLD:				pWin = new CtWindow_ToggleDialog(id);				break;
        case CtMenuInfo::WINDOW_TYPE_TIMESETTING:		pWin = new CtWindow_ToggleDialog(id);				break;
        case CtMenuInfo::WINDOW_TYPE_TC:				pWin = new CtWindow_ToggleDialog(id);				break;
        case CtMenuInfo::WINDOW_TYPE_UB:				pWin = new CtWindow_ToggleDialog(id);				break;
		case CtMenuInfo::WINDOW_TYPE_FILE:				pWin = new CtWindow_FILE(pContents);                break;    /* pgr0541 */
		case CtMenuInfo::WINDOW_TYPE_2LIST:				pWin = new CtWindow2ListMenu();		                break;
		default: return NULL;
    }
    pWin->setWindowID(id);
    return pWin;
}
