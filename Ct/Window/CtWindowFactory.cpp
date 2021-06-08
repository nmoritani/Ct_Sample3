/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtWindowFactory.h"
#include "CtWindows.h"
#include "CtWindowMain.h"
#include "CtFactWindowFactory.h"
#include "CtMenuWindowFactory.h"
#include "CtMessageWindowFactory.h"
#ifdef WIN32_GUI_SIM
#include "CtWorkWindowFactory.h"
#endif // WIN32

#if 0	// mori
#include "CtThumbNailDialog_DelAndCopy.h"
#endif

CtWindowMain* CtWindowFactory::create(CtScreenSel ScreenSel, CtWindowID id, CtWindowContents *pContents)
{
	CtWindowMain *pWin = NULL;

#ifdef WIN32_GUI_SIM
	if (pWin == NULL) pWin = CtWorkWindowFactory::create(id, pContents);
#endif // WIN32
	if (pWin == NULL) pWin = CtFactWindowFactory::create(id, pContents);
	if (pWin == NULL) pWin = CtMenuWindowFactory::create(id, pContents);
	if (pWin == NULL) pWin = CtMessageWindowFactory::create(id, pContents);
	if (pWin == NULL) {
		switch (id) {
		
		case Window_RecView:			pWin = new CtRecView2();						break;
		case Window_Rec_Mode_Check:		pWin = new CtRecViewModeCheck();				break;
		case Window_TouchNavi:			pWin = new CtRecTouchNavi();					break;

		case Window_ThumbNail:
		case Window_ThumbNail_Protect:
		case Window_ThumbNail_Delete:
		case Window_ThumbNail_Copy:
			pWin = new CtWindowThumbnail(pContents);		    	/* pgr0541 */  	    break;
		case Window_ThumbNailClip:		pWin = new CtWindowClipInfoMation();			break;

		case Window_PlayView:
		case Window_PlayView_RecCheck:
			pWin = new CtPlayView();                                                    break;
		case Window_View_Play_Message:	pWin = new CtViewPlayMessage();					break;
		// Updete Complete
		case WindowID_Menu_UPDATE_COMPLETE:
			pWin = new CtWindowUpdateComplete();
			break;

		// File Menu
		case WindowID_Menu_SCENE_FILE_LOAD:
		case WindowID_Menu_SETUP_FILE_LOAD:
		case WindowID_Menu_SETUP_FILE_LOAD_MEMORY:
		case WindowID_Menu_SCENE_FILE_SAVE:
		case WindowID_Menu_SETUP_FILE_SAVE:
		case WindowID_Menu_SETUP_FILE_SAVE_MEMORY:
			pWin = new CtWindow_FILE(pContents);   /* pgr0541 */
			break;
		case Window_Menu_SCENE_FILE_LOAD_SCENELIST:
			pWin = new CtWindow_SceneList(); 
			break;

		// Keyboard
		case WindowID_Menu_SCENE_FILE_SAVE_AS:
		case WindowID_Menu_SETUP_FILE_SAVE_AS:
		case Window_Menu_SCENE_FILE_SAVE_KEYBOARD:
		case Window_Menu_SETUP_FILE_SAVE_KEYBOARD:
		case WindowID_Menu_USER_ACCOUNT_PASSWORD:
			pWin = new CtWindow_Keyboard(pContents);     /* pgr0541 */
			break;

		// AreaSetting
		case Window_Area_Setting:
		case WindowID_Menu_AREA_SETTING:
			pWin = new CtAreaSetting(pContents);			/* pgr0541 */
			break;
		case Window_Area_Setting_Confirm:
		case WindowID_Menu_Area_Setting_Confirm:
			pWin = new CtAreaSettingConfirm(pContents);		/* pgr0541 */
			break;

		// NetWork
		case WindowID_Menu_NETWORK_INFRA_SELECT:
			pWin = new CtWindow_NETWORK(pContents);			/* pgr0541 */ 
			break;
		case WindowID_Menu_USER_ACCOUNT_DELETE:
			pWin = new CtWindow_NETWORK_USER(pContents);	/* pgr0541 */
			break;
		case WindowID_Menu_NETWORK_INFO_STATUS:
		case WindowID_Menu_NETWORK_INFO_LOG:
			pWin = new CtWindow_NETWORK_INFO(pContents);	/* pgr0541 */
			break;
		case Window_CopyComplete:		
		case Window_DeleteComplete:		
		case Window_DeleteCanceled:		
		case Window_CopyCanceled:		
		       pWin = new CtThumbNailDialog_Complete(pContents);	/* pgr0541 */   break;
		case Window_CopyConfirm:
		case Window_DeleteConfirm:
		       pWin = new CtThumbNailDialogConfirm(pContents);	/* pgr0541 */   break;
		case Window_Deleting:			pWin = new CtThumbNailDialog_DelAndCopy(pContents);     /* pgr0541 */   break;
		case Window_Copying:			pWin = new CtThumbNailDialog_DelAndCopy(pContents);     /* pgr0541 */   break;
#ifdef WIN32_GUI_SIM
	    case Window_Home:				pWin = new CtWindowHome();						break;
		case Window_Home_Audio_Top:     pWin = new CtWindowHome_AudioTop();				break;
		case Window_Home_ColorTop:		pWin = new CtWindowHome_ColorTop();				break;

		case Window_Home_EI_TOP:		pWin = new CtWindowHome_EITop();				break;
		case Window_Home_Fps_Top:		pWin = new CtWindowHome_FpsTop();				break;
		case Window_Home_Shutter_Top:	pWin = new CtWindowHome_ShutterTop();			break;
		case Window_Home_WB_Top:		pWin = new CtWindowHome_WBTop();				break;
#endif
		default:
			return NULL;
		}
	}
	if (pWin)
		pWin->setWindowID(id);
	return pWin;
}

void  CtWindowFactory::Destroy()
{
#if 0	// mori
	CtMenuWindowFactory::Destroy();
#endif
}
