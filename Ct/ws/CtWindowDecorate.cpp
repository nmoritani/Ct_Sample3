/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtDraw
*/


#include "CtWindowDecorate.h"
#include "CtInterface.h"
#include "CtTimeMesure.h"

bool CtWindowDecorate::requestDecorate(WindowArray* pWindows, int Screen)
{
	unsigned long time = CtGetTime();
	bool bRet = false;

	if (pWindows == NULL)
		return false;

	if (pWindows->empty() == true)
		return false;

	{
		if (decorateInvisible(pWindows, Screen))
			bRet = true;

		if (decorateMenu(pWindows, Screen))
			bRet = true;
	}

//	CtDebugPrint(CtDbg, "CtWindowDecorate  Ret = %s  Screen = %d  Time = %ld\n", bRet ? "true " : "false", Screen, CtGetTime() - time);
	return bRet;
}

bool CtWindowDecorate::decorateInvisible(WindowArray* pWindows, int Screen)
{
	if (pWindows == NULL) return false;
	bool bRet = false;
	CtWindowMain *pCur, *pNext;

	/********************************************************************/
	/* 表示非表示操作                                                   */
	/********************************************************************/
	for (int i = 0; i < pWindows->size(); i++) {
		if ((pCur = (*pWindows)[i]) == NULL)
			continue;

		/* WindowID別 */
		switch (pCur->getWindowID()) {
		case Window_RecView:
		{
			bool bVisible = true;
			for (int j = i + 1; j < pWindows->size(); j++) {
				if ((pNext = (*pWindows)[j]) == NULL)
					continue;

				if (isInvisibleCheck_RecView(pNext) == true)
					bVisible = false;
			}
			if (setVisible(pCur, bVisible))
				bRet = true;

			break;
		}
		default:
			break;
		}


		/* ClassType別 */
		switch (pCur->getClassType()) {
		case CtClassType_WindowMenuList:
		case CtClassType_WindowSpinBox:
		case CtClassType_WindowToggleDialog:
		case CtClassType_WindowDialog:
		case CtClassType_WindowKeyboard:
		case CtClassType_WindowFILE:
		case CtClassType_WindowNETWORK:
		case CtClassType_WindowNETWORK_USER:
		case CtClassType_WindowNETWORK_INFO:
		case CtClassType_WindowFACT:
		case CtClassType_WindowMenu2List:
		{
			bool bVisible = true;
			for (int j = i + 1; j < pWindows->size(); j++) {
				if ((pNext = (*pWindows)[j]) == NULL)
					continue;

				if (isInvisibleCheck_Menu(pNext) == true)
					bVisible = false;
			}
			if (setVisible(pCur, bVisible))
				bRet = true;

			break;
		}

		case CtClassType_WindowMessageDialog:
		{
			bool bVisible = true;
			for (int j = i + 1; j < pWindows->size(); j++) {
				if ((pNext = (*pWindows)[j]) == NULL)
					continue;

				switch (pNext->getClassType()) {
				case CtClassType_WindowMessageDialog:
					bVisible = false;
					break;
				default:
					break;
				}
			}
			if (setVisible(pCur, bVisible))
				bRet = true;

			break;
		}

		case CtClassType_WindowMessageTelop:
		{
			bool bVisible = true;
			for (int j = i + 1; j < pWindows->size(); j++) {
				if ((pNext = (*pWindows)[j]) == NULL)
					continue;

				switch (pNext->getClassType()) {
				case CtClassType_WindowMessageDialog:
				case CtClassType_WindowMessageTelop:
					bVisible = false;
					break;
				default:
					break;
				}
			}
			if (setVisible(pCur, bVisible))
				bRet = true;

			break;
		}

		default:
			break;
		}
	}

	return bRet;
}

bool CtWindowDecorate::decorateMenu(WindowArray* pWindows, int Screen)
{
	if (pWindows == NULL) return false;

	bool bRet = false;
	CtWindowMenu *pCur, *pNext;

	/********************************************************************/
	/* メニューずらし操作                                               */
	/********************************************************************/
	for (int i = 0; i < pWindows->size(); i++) {
		if ((pCur = (CtWindowMenu*)(*pWindows)[i]) == NULL)
			continue;

		switch (pCur->getClassType()) {
		case CtClassType_WindowMenuList:
			// 非表示にしている場合は何も行わない
			if (pCur->isVisible() == false)
				break;

			pCur->setVisible(true);
			if ((i + 1 < pWindows->size()) && ((pNext = (CtWindowMenu*)(*pWindows)[i + 1]) != NULL)) {
				if (pNext->getClassType() == CtClassType_WindowMenuList) {
					CtRegion R = pCur->getRegion(Screen);
					CtRegion a = pNext->getListRegion(Screen);
					R.width = (short)(a.x - R.x);
					pCur->setWindowClip(R, Screen);
					pCur->setBack(true);
					bRet = true;
				}
			}
			else {
				pCur->setBack(false);
				pCur->setWindowClip(CtRegion(0, 0, 0, 0), Screen);
			}
			break;

		default:
			break;
		}
	}

	return bRet;
}

bool CtWindowDecorate::setVisible(CtWindowMain* pWin, bool bVisible)
{
	if ((pWin != NULL) && (pWin->setVisible(bVisible)) == true) {
		return true;
	}
	return false;
}

bool CtWindowDecorate::isInvisibleCheck_RecView(CtWindowMain* pNext)
{
	if (pNext == NULL)return false;

	switch (pNext->getClassType()) {
	case CtClassType_WindowSpinBox:
	case CtClassType_WindowToggleDialog:
	case CtClassType_WindowDialog:
	case CtClassType_WindowKeyboard:
	case CtClassType_WindowFILE:
	case CtClassType_WindowNETWORK:
	case CtClassType_WindowNETWORK_USER:
	case CtClassType_WindowNETWORK_INFO:
	case CtClassType_WindowFACT:
	case CtClassType_WindowMenu2List:
	case CtClassType_WindowAreaSetting:
	case CtClassType_WindowMenuList:
	case CtClassType_WindowMessageDialog:
		return true;
	default:
		break;
	}
	return false;
}

bool CtWindowDecorate::isInvisibleCheck_Menu(CtWindowMain* pNext)
{
	if (pNext == NULL)return false;

	switch (pNext->getClassType()) {
	case CtClassType_WindowMenuList:
		break;
	case CtClassType_WindowSpinBox:
	case CtClassType_WindowToggleDialog:
	case CtClassType_WindowDialog:
	case CtClassType_WindowKeyboard:
	case CtClassType_WindowFILE:
	case CtClassType_WindowNETWORK:
	case CtClassType_WindowNETWORK_USER:
	case CtClassType_WindowNETWORK_INFO:
	case CtClassType_WindowFACT:
	case CtClassType_WindowMenu2List:
		return true;
	default:
		break;
	}
	return false;
}

bool CtWindowDecorate::isThumbnail(int Screen)
{
	CtScreenSel screen = Screen == 0 ? ScreenLCD : ScreenLOUT;

	if (WindowNone != CtInterface::getInstance()->checkDrawWindowID(screen, WindowCategory_Thumbnail)) {
		return true;
	}

	return false;
}
