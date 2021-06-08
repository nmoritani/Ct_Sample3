/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowController
 */

#ifndef __CtWindowController_H__
#define __CtWindowController_H__

#include "CtClass.h"
#include "Ct.h"
#include "CtWidget.h"
#include "CtDraw.h"
#include "CtTimer.h"
#include "CtWindowDecorate.h"

class CtWindowController : public CtObject
{
public:
	virtual ~CtWindowController();
	static CtWindowController* getInstance();
	
	// Window�Ǘ�
	typedef CtList::list<CtWindowMain*> WindowList;
	CtWindowMain* createWindow(CtScreenSel ScreenSel, CtWindowID id, CtWindowContents *pContents);
	
	CtWindowMain* getCurrentWindow(int Screen) const;
	CtWindowMain* getRootWindow(int Screen) const;
	CtWindowMain* getWindow(int Screen, CtWindowID id) const;
	CtWindowMain* getDrawWindow(int Screen, CtWindowID id) const;
	
	// �R�[���o�b�N�Ǘ�
	void registerWindowFunc(CtWindowID id_win, CtFuncID id_func, CtWindowFunc func);
	void unregisterWindowFunc(CtFuncID id_func);
	bool notifyWindowFunc(CtScreenSel ScreenSel, CtWindowID id_win, CtFuncID id_func, CtWindowContents* pContents);

	// ���̑�API����
	void setNotifyFunc(CtNotifyFunc func);
	void setScreen(CtScreenSel ScreenSel);
	CtScreenSel getScreen(void) const;
	CtScreenInfo getScreenInfo(CtScreenSel ScreenSel) const;
		
	bool handleFrameSync(unsigned long FrameCount);
	
private:
	static CtWindowController* m_pInstance;
	static const int m_PopupWindowLimit		= 20;				//!< PopupWindow�ő吔
	static const int m_ChangeWindowLimit	= 30;				//!< ChangeWindow�ő吔
	CtWindowList *m_WindowList[CT_SCREEN_NUM];					//!< �eSCREEN�p�E�B���h�E���X�g
	CtScreenSel m_ScreenOut;									//!< �e�X�N���[���̗L��/�������
	CtDraw *m_pDraw;											//!< Draw�N���X�C���X�^���X
	CtTimer *m_pTimer;											//!< Timer�N���X�C���X�^���X
	CtNotifyFunc m_Notify;										//!< ��ʃu���b�N�ւ̃R�[���o�b�N�֐�
	struct CtWindowFuncTable {
		CtWindowID id;
		CtWindowFunc func;
	} m_FuncList[FuncID_MAX];									//!< Function�e�[�u��
	
	CtObserverParamService *m_pParamIf;					//!< �p�����[�^�T�[�r�X�C���X�^���X

	CtWidget::RegionArray	m_Invalidates;
	CtWidget::RegionArray	m_InvalidatesFast;
	
	typedef CtVector::Vector<CtWindowMain*> WindowArray;
	WindowArray				m_CurrentAll;
	WindowArray				m_Current[CT_SCREEN_NUM];
	int						m_VisiblePos[CT_SCREEN_NUM];

	bool					m_bBanFrameOperation;
	
	// �R���X�g���N�^
	CtWindowController();

	// Window�Ǘ�
	CtWindowList* getWindowList(int Screen) const;
	void destroyWindow(CtScreenSel ScreenSel, CtWindowMain* pWindow);

	// ��ʑJ��
	bool changeWindow(int Screen, CtWindowID id, CtWindowContents* pContents, CtWindowMain* pWindow = NULL, bool bUpdate = true);
	bool popupWindow(int Screen, CtWindowID id, CtWindowContents* pContents, CtWindowMain* pWindow = NULL, bool bUpdate = true);
	bool swapWindow(int Screen, CtWindowID id, CtWindowContents* contents, CtWindowMain* pWindow = NULL, bool bUpdate = true);
	bool returnWindow(int Screen, CtWindowID id = WindowNone, bool bUpdate = true);
	bool closeWindow(int Screen, CtWindowID id = WindowNone, bool bUpdate = true);
	bool removeWindow(int Screen, CtWindowID id, bool bUpdate = true);

	// �R���e���c�Ǘ�
	bool updateContents(CtScreenSel ScreenSel, CtWindowID id);

	// ��ʕ`��
	bool readyWindow(CtWindowMain* pWindow);
	bool getInvalidates(int Screen, CtWidget::RegionArray& invalidateArray);
	bool drawScreen(int Screen, int delay);
	bool clearScreen(int Screen, int delay);
	bool drawScreenFast(int Screen);
	
	int getDrawStart(int Screen);
	bool banFrameOperation(bool bBan);
	//int	(CtScreenSel ScreenSelBit);
public:
	// �C�x���g����
	void putEvent(CtEvent& Event);
	bool KeyEvent(const CtEventKey& Key);
	bool WindowEvent(const CtEventWindow& Event);
	bool WinInfoEvent(const CtEventWinInfoAccess& Event);
	bool TouchEvent(const CtEventTouch& Touch);
	bool TimerEvent(const CtEventTimer& Timer);
	bool ParamEvent(const CtEventParam& Param);
	bool FlashEvent(const CtEventFlash& Flash);
	bool ButtonEvent(const CtEventButton& Button);
	bool WidgetEvent(const CtEventWidget& Widget);
	bool FuncEvent(const CtEventFunc& Event);
	bool DrawResultEvent(const CtEventDrawResult& Event);
	bool RequestEvent(const CtEventRequest& Request);
};

#endif

