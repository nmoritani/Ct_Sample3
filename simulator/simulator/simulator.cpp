// simulator.cpp : メイン プロジェクト ファイルです。
#include "stdafx.h"

#include <stdlib.h>
#include <iostream>
#include "stdlib.h"
#include "gdi.h"
#include "Wrapper.h"

#include "CtWindowIDString.h"
#include "AplParamIDString.h"
#include "MovieForm.h"
#include "smDebugSerial.h"

using namespace simulator;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#if 0	//メモリリークしたら以下のような感じでリークしている番号を入れると開始時に指定位置でブレークできる
	_CrtSetBreakAlloc(238);
#endif

#endif

	// コントロールが作成される前に、Windows XP ビジュアル効果を有効にします
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// メイン ウィンドウを作成して、実行します
	Application::Run(gcnew MovieForm());
	return 0;
}

Void MovieForm::WndProc(System::Windows::Forms::Message% msg) {
	switch (msg.Msg) {
	case WM_COMMAND:
		if (msg.WParam == (IntPtr)IDC_TREE_DATA) {
			//printf("Tree Data Create Fin");
			updateTreeData();
		}
		break;
	case WM_USER_END_THREAD:
	{
		int waitCnt = 0;
		if (msg.WParam == (IntPtr)IDC_CMD_LINE) {
			// CmdLineModeの終了
			if (m_CmdLineThread != NULL) {
				while (WaitForSingleObject(m_CmdLineThread, 100) == WAIT_TIMEOUT) {
					if (waitCnt > 20) {
						// 2000ms以上のWaitは強制削除
						TerminateThread(m_CmdLineThread, false);
						break;
					}
					waitCnt++;
				}
				CloseHandle(m_CmdLineThread);
				m_CmdLineThread = NULL;
			}
			if (m_CmdLineHelperThread != NULL) {
				while (WaitForSingleObject(m_CmdLineHelperThread, 100) == WAIT_TIMEOUT) {
					if (waitCnt > 20) {
						// 2000ms以上のWaitは強制削除
						TerminateThread(m_CmdLineHelperThread, false);
						break;
					}
					waitCnt++;
				}
				CloseHandle(m_CmdLineHelperThread);
				m_CmdLineHelperThread = NULL;
			}

			HWND hwnd = reinterpret_cast<HWND>(Handle.ToPointer());
			SetForegroundWindow(hwnd);
			System::Console::Title = "Mode::LogMode";
		}
		else if (msg.WParam == (IntPtr)IDC_LOG_PLAY) {
			// LogPlayerの終了
			if (m_LogPlayerThread != NULL) {
				while (WaitForSingleObject(m_LogPlayerThread, 100) == WAIT_TIMEOUT) {
					if (waitCnt > 20) {
						// 2000ms以上のWaitは強制削除
						TerminateThread(m_LogPlayerThread, false);
						break;
					}
					waitCnt++;
				}
				CloseHandle(m_LogPlayerThread);
				m_LogPlayerThread = NULL;

				bool findMsg = false;
				MSG msg;
				while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE | PM_QS_INPUT) == TRUE) {
					// Sim無効中のボタン操作を削除
				}
				// SimForm有効化
				EnableWindow(m_SimHWnd, SW_SHOW);
			}
		}
		return;
	}
	break;
	case WM_TIMER:
	{
		if (msg.WParam == (IntPtr)IDC_TIMER_MOUSE_DOWN) {
			// マウス移動イベント
			if (m_IsMouseDown) {
				m_dbgCmd->rqCmndSysTouch(getScreenId(), ID_SYS_TOUCH, ID_TCH_MV, m_MouseX, m_MouseY);
			}
		}
	}
	default:
		break;
	}
	Form::WndProc(msg);
}
static BOOL s_draw_task_stop;

System::Void MovieForm::MovieForm_Shown(System::Object^  sender, System::EventArgs^  e) {
	//先にフォームを再描画して表示する
	UpdateWindow(reinterpret_cast<HWND>(Handle.ToPointer()));
}

System::Void MovieForm::MovieForm_Load(System::Object^  sender, System::EventArgs^  e) {
	float scale = 1;
	if (cbox_Scale->SelectedItem != nullptr) {
		scale = float::Parse((String^)cbox_Scale->SelectedItem);
	}

	//// LCD/LOUT向けコントロールのサイズ初期化
	int lcd_w = (int)(m_ScreenLCD_Width * scale);
	int lcd_h = (int)(m_ScreenLCD_Height * scale);
	int lout_w = (int)(m_ScreenLOUT_Width * scale);
	int lout_h = (int)(m_ScreenLOUT_Height * scale);

	picbox_LCD->Width = lcd_w;
	picbox_LCD->Height = lcd_h;

	picbox_RectLCD->Width = lcd_w;
	picbox_RectLCD->Height = lcd_h;

	picbox_LOUT->Width = lout_w;
	picbox_LOUT->Height = lout_h;

	panel_LCD->Size = picbox_LCD->Size;
	panel_LOUT->Size = picbox_LOUT->Size;

	// 矩形描画用初期化
	// 背景を透過させるために矩形描画用の親をイメージ用pictureboxに変更
	this->picbox_RectLCD->Parent = this->picbox_LCD;
	m_RectImageLcd = gcnew Bitmap(m_ScreenLCD_Width, m_ScreenLCD_Height);
	this->picbox_RectLCD->Image = m_RectImageLcd;
}

FILE* s_console_out;

Void MovieForm::ExecDraw(bool isLcd)
{
	PictureBox ^pbox = isLcd ? picbox_LCD : picbox_LOUT;
	array<int> ^data = isLcd ? m_ImageBufLcd : m_ImageBufLout;
	Bitmap ^bmp = (Bitmap^)pbox->Image;

#if 0 // 計測処理
	Stopwatch ^s = gcnew Stopwatch();
	s->Start();
#endif

	// m_ImageBufXXXからpicbox_XXX->Imageへコピーして画像更新
	BitmapData ^bmpdata = bmp->LockBits(System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height), ImageLockMode::WriteOnly, PixelFormat::Format32bppRgb);
	Marshal::Copy(data, 0, bmpdata->Scan0, data->Length);
	bmp->UnlockBits(bmpdata);
	pbox->Invalidate();

#if 0 // 計測処理
	s->Stop();
	Debug::WriteLine("time (ms) " + s->ElapsedMilliseconds);
#endif
}

void MovieForm::DrawCallbackLcd(int w, int h, void* data)
{
	DrawCallback(w, h, data, true);
}

void MovieForm::DrawCallbackLout(int w, int h, void* data)
{
	DrawCallback(w, h, data, false);
}
delegate Void UpdateDrawDelegate(bool isLcd);
void MovieForm::DrawCallback(int w, int h, void* data, bool isLcd)
{
	// 透過を考慮しつつImageバッファへコピー
	pin_ptr<int> srcPixel = (int*)data;
	pin_ptr<int> dstPixel = &(isLcd ? m_ImageBufLcd[0] : m_ImageBufLout[0]);
	pin_ptr<int> bgPixel = &(isLcd ? m_BackGroundImageBufLcd[0] : m_BackGroundImageBufLout[0]);

	for (int i = 0; i < h * w; i++) {
		unsigned char *src = (unsigned char*)(srcPixel + i);	// BGRA

		switch (src[3]) {
		case 0x00:
			// 透明色 => 背景を描画
			dstPixel[i] = bgPixel[i];
			break;
		case 0xff:
			// 透過なし => 前景を描画
			dstPixel[i] = srcPixel[i];
			break;
		default:
			// 透過あり => αブレンド
		{
			unsigned char *dst = (unsigned char*)(dstPixel + i);
			unsigned char *bg = (unsigned char*)(bgPixel + i);
			float dst_alpha, src_alpha;	// 0～1

			src_alpha = src[3] / 255.0f;
			dst_alpha = 1.0f - src_alpha;

			dst[0] = (unsigned char)(src[0] * src_alpha) + (unsigned char)(bg[0] * dst_alpha);
			dst[1] = (unsigned char)(src[1] * src_alpha) + (unsigned char)(bg[0] * dst_alpha);
			dst[2] = (unsigned char)(src[2] * src_alpha) + (unsigned char)(bg[0] * dst_alpha);
		}
		break;
		}
	}

	array<Object^>^args = gcnew array<Object^>(1);
	args[0] = isLcd;

	// コントロールへの適用はUIスレッドで実施
	Invoke(gcnew UpdateDrawDelegate(this, &MovieForm::ExecDraw), args);
}

Void MovieForm::createImageBuffer(Bitmap ^src, array<int> ^%dst)
{
	// src画像メモリのロック
	BitmapData ^dstbmpdata = src->LockBits(System::Drawing::Rectangle(0, 0, src->Width, src->Height), ImageLockMode::ReadOnly, PixelFormat::Format32bppRgb);

	// イメージデータ用配列
	dst = gcnew array<int>(src->Width * src->Height);

	// コピー
	Marshal::Copy(dstbmpdata->Scan0, dst, 0, dst->Length);

	// メモリアンロック
	src->UnlockBits(dstbmpdata);
}

Void MovieForm::InitImage()
{
	// 背景画像ロード
	String ^bgpath = ".\\image\\background_lcd.jpg";
	if (System::IO::File::Exists(bgpath)) {
		picbox_LCD->Image = Image::FromFile(bgpath);
	}
	bgpath = ".\\image\\background_lout.jpg";
	if (System::IO::File::Exists(bgpath)) {
		picbox_LOUT->Image = Image::FromFile(bgpath);
	}

	// LCD画像の初期化
	Bitmap ^lcdbmp = (Bitmap^)picbox_LCD->Image;

	createImageBuffer(lcdbmp, m_ImageBufLcd);
	createImageBuffer(lcdbmp, m_BackGroundImageBufLcd);

	// LOUT画像の初期化
	Bitmap ^loutbmp = (Bitmap^)picbox_LOUT->Image;

	createImageBuffer(loutbmp, m_ImageBufLout);
	createImageBuffer(loutbmp, m_BackGroundImageBufLout);
}
#include <new>
Void MovieForm::Init()
{
	AplParamService::getInstance()->initialize();
	initParamID();
	initWindowID();
	m_SimHWnd = reinterpret_cast<HWND>(Handle.ToPointer());

	// 設定ファイル読み込み
	readSetting();

	if (chk_Box_Logo->Checked != true) {
		m_Logo = gcnew Logo();
		m_Logo->ShowDialog();
	}

	::AllocConsole();
	freopen_s(&s_console_out, "CONOUT$", "w", stdout);	// 標準出力の割り当て
	freopen_s(&s_console_out, "CONIN$", "r", stdin);	// 標準入力の割り当て
	System::Console::Title = "Mode::LogMode";

	smDebugPrintf(1, "GUI Simulator - start\n");

	Ct_Init();
	
	s_draw_task_stop = FALSE;
	m_CmdLineThread = NULL;
	m_CmdLineHelperThread = NULL;
	m_LogPlayerThread = NULL;

	InitImage();

	m_cWrapperLcd.Create();
	m_cWrapperLout.Create();
	m_cWrapperLcd.SetDrawDelegate(gcnew DrawDelegate(this, &MovieForm::DrawCallbackLcd));
	m_cWrapperLout.SetDrawDelegate(gcnew DrawDelegate(this, &MovieForm::DrawCallbackLout));

	m_dbgCmd = new CtDbgCmndAdapter();
	m_dbgCmd->rqCmndCtInit();

	m_MouseX = 0;
	m_MouseY = 0;


	picbox_LCD->Focus();
}

Void MovieForm::Finish()
{
	if (m_Logo) delete m_Logo;
	KillTimer(m_SimHWnd, IDC_TIMER_LOGO);
	KillTimer(m_SimHWnd, IDC_TIMER_MOUSE_DOWN);
	int waitCnt = 0;
	if (m_CmdLineThread != NULL) {
		while (WaitForSingleObject(m_CmdLineThread, 100) == WAIT_TIMEOUT) {
			if (waitCnt > 10) {
				TerminateThread(m_CmdLineThread, false);
				break;
			}
			waitCnt++;
		}
		CloseHandle(m_CmdLineThread);
		m_CmdLineThread = NULL;
	}
	if (m_LogPlayerThread != NULL) {
		while (WaitForSingleObject(m_LogPlayerThread, 100) == WAIT_TIMEOUT) {
			if (waitCnt > 10) {
				// 2000ms以上のWaitは強制削除
				TerminateThread(m_LogPlayerThread, false);
				break;
			}
			waitCnt++;
		}
		CloseHandle(m_LogPlayerThread);
		m_LogPlayerThread = NULL;

		bool findMsg = false;
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE | PM_QS_INPUT) == TRUE) {
			// Sim無効中のボタン操作を削除
		}
		EnableWindow(m_SimHWnd, SW_SHOW);
	}
	m_SimHWnd = NULL;

	GDI_Terminate();	//GDI終了

	smDebugPrintf(1, "GUI Simulator - finish\n");

	Ct_Term();

	delete AplParamService::getInstance();
	if (m_dbgCmd != NULL) delete m_dbgCmd;

	if (s_console_out != NULL) {
		fclose(s_console_out);
		s_console_out = NULL;
	}
	::FreeConsole();

	m_cWrapperLcd.Delete();
	m_cWrapperLout.Delete();
}

Void MovieForm::Update()
{
	m_cWrapperLcd.Update();
	m_cWrapperLout.Update();
}

char MovieForm::getScreenId()
{
	switch (cbox_ScreenType->SelectedIndex) {
	case 0:		return ID_LCD;	// LCD
	case 1:		return ID_LOUT;	// LOUT
	default:	break;
	}
	return ID_SCRN_ALL;		// ALL
}

/////////////////★★★★★★★★★★★★ ID_WIN_TRANS ★★★★★★★★★★★★/////////////////
System::Void MovieForm::btn_ChangeWindow_Click(System::Object^  sender, System::EventArgs^  e) {
	m_dbgCmd->rqCmndWindowTrans(getScreenId(), ID_WIND, ID_CHANGE, getSelectedWindowID());
}

System::Void MovieForm::btn_ReturnWindow_Click(System::Object^  sender, System::EventArgs^  e) {
	System::Windows::Forms::Button^ btn = (System::Windows::Forms::Button^)sender;
	unsigned int windowid = WindowNone;
	if (chkbox_winid->Checked) {
		windowid = getSelectedWindowID();
	}
	m_dbgCmd->rqCmndWindowTrans(getScreenId(), ID_WIND, ID_RETURN, windowid);
}

System::Void MovieForm::btn_PopupWindow_Click(System::Object^  sender, System::EventArgs^  e) {
	m_dbgCmd->rqCmndWindowTrans(getScreenId(), ID_WIND, ID_POPUP, getSelectedWindowID());
}

System::Void MovieForm::btn_CloseWindow_Click(System::Object^  sender, System::EventArgs^  e) {
	System::Windows::Forms::Button^ btn = (System::Windows::Forms::Button^)sender;
	unsigned int windowid = WindowNone;
	if (chkbox_winid->Checked) {
		windowid = getSelectedWindowID();
	}
	m_dbgCmd->rqCmndWindowTrans(getScreenId(), ID_WIND, ID_CLOSE, windowid);
}

System::Void MovieForm::btn_SwapWindow_Click(System::Object^  sender, System::EventArgs^  e) {
	m_dbgCmd->rqCmndWindowTrans(getScreenId(), ID_WIND, ID_SWAP, getSelectedWindowID());
}

System::Void MovieForm::btn_RemoveWindow_Click(System::Object^  sender, System::EventArgs^  e) {
	System::Windows::Forms::Button^ btn = (System::Windows::Forms::Button^)sender;
	unsigned int windowid = WindowNone;
	if (chkbox_winid->Checked) {
		windowid = getSelectedWindowID();
	}

	m_dbgCmd->rqCmndWindowTrans(getScreenId(), ID_WIND, ID_REMOVE, windowid);
}

/////////////////★★★★★★★★★★★★ ID_REF_INFO ★★★★★★★★★★★★/////////////////
System::Void MovieForm::btn_GetRoot_Click(System::Object^  sender, System::EventArgs^  e) {
	m_dbgCmd->rqCmndRefInfo(getScreenId(), ID_REF_INFO, ID_ROOT, ID_INVALID);
}

System::Void MovieForm::btn_GetCurrent_Click(System::Object^  sender, System::EventArgs^  e) {
	m_dbgCmd->rqCmndRefInfo(getScreenId(), ID_REF_INFO, ID_CRNT, ID_INVALID);
}

System::Void MovieForm::btn_ShowOutline_Click(System::Object^  sender, System::EventArgs^  e) {
	treeV_Widget->Nodes->Clear();
	m_dbgCmd->rqCmndRefInfo(getScreenId(), ID_REF_INFO, ID_OUTLINE, (unsigned int)m_SimHWnd);
}

System::Void MovieForm::btn_ClassInfo_Click(System::Object^  sender, System::EventArgs^  e) {
	m_dbgCmd->rqCmndRefInfo(getScreenId(), ID_REF_INFO, ID_CLASSINFO, ID_INVALID);
}

System::Void MovieForm::btn_MemInfo_Click(System::Object^  sender, System::EventArgs^  e) {
	m_dbgCmd->rqCmndRefInfo(getScreenId(), ID_REF_INFO, ID_MEMINFO, ID_INVALID);
}

unsigned int MovieForm::getKeySource() {
	if (radbtn_Deck->Checked) {
		return ID_DECK;
	}
	else if (radbtn_Grip->Checked) {
		return ID_GRIP;
	}
	else if (rdbtn_Rop->Checked) {
		return ID_Controller;
	}
	else {
		return ID_DECK;
	}
}

System::Void MovieForm::MovieForm::VirtualKeyUpEvent(unsigned short key) {
	m_dbgCmd->rqCmndSysKey(getScreenId(), ID_SYS_KEY, ID_DECK, ID_KEY_RLS, key);
}

System::Void MovieForm::MovieForm::VirtualKeyDownEvent(unsigned short key) {
	m_dbgCmd->rqCmndSysKey(getScreenId(), ID_SYS_KEY, ID_DECK, ID_KEY_PRS, key);
}

System::Void MovieForm::MovieForm::VirtualMouseWheelEvent(int line) {
	unsigned short keyCode = (0 <= line) ? ID_KEY_DIAL_UP : ID_KEY_DIAL_DOWN;
	VirtualMovieKey(true, ID_DECK, keyCode);
	/* Release 取れないので強制的に発行してやる (実機と同じ動作となるようエミュレート) */
	VirtualMovieKey(false, ID_DECK, keyCode);
}

System::Void MovieForm::MovieForm::VirtualMovieKey(bool isPress, unsigned char keyType, unsigned short keyCode) {
	unsigned char ActType = isPress ? ID_KEY_PRS : ID_KEY_RLS;
	m_dbgCmd->rqCmndSysKey(getScreenId(), ID_SYS_KEY, keyType, ActType, keyCode);
}

System::Boolean MovieForm::MoveMouseCursor(KeyEventArgs^ e) {
	Point p = System::Windows::Forms::Cursor::Position;

	switch (e->KeyCode) {
	case Keys::Up:		p.Y--;	break;
	case Keys::Down:	p.Y++;	break;
	case Keys::Right:	p.X++;	break;
	case Keys::Left:	p.X--;	break;
	default:
		return false;
	}

	System::Windows::Forms::Cursor::Position = p;

	return true;
}

System::Boolean MovieForm::isIgnoreKeyEvent() {
	// ret TRUE : 画面へKEY EVENTを送らない
	if (cbox_ParamID->Focused == true
		|| cbox_ParamDef->Focused == true
		|| cbox_WindowName->Focused == true
		|| cbox_ScreenType->Focused == true)
	{
		return true;
	}

	if (cbox_Scale->Focused
		|| tBox_ParamValue->Focused
		|| tbox_Rect_height->Focused
		|| tbox_Rect_width->Focused
		|| tbox_Rect_x->Focused
		|| tbox_Rect_y->Focused
		|| treeV_Widget->Focused)
	{
		return true;
	}
	return false;
}

bool MovieForm::ProcessDialogKey(System::Windows::Forms::Keys key) {
	if (isIgnoreKeyEvent()) {
		return false;
	}

	switch (key) {
	case Keys::Up:		VirtualKeyDownEvent(ID_KEY_UP);		break;
	case Keys::Down:	VirtualKeyDownEvent(ID_KEY_DOWN);	break;
	case Keys::Right:	VirtualKeyDownEvent(ID_KEY_RIGHT);	break;
	case Keys::Left:	VirtualKeyDownEvent(ID_KEY_LEFT);	break;
	case Keys::Return:	VirtualKeyDownEvent(ID_KEY_EXIT);	break;
	default:
		break;
	}
	return true;
}

System::Void MovieForm::MovieForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (isIgnoreKeyEvent()) {
		e->Handled = false;
		return;
	}

	switch (e->KeyCode) {
	case Keys::Up:		VirtualKeyDownEvent(ID_KEY_UP);		break;
	case Keys::Down:	VirtualKeyDownEvent(ID_KEY_DOWN);	break;
	case Keys::Right:	VirtualKeyDownEvent(ID_KEY_RIGHT);	break;
	case Keys::Left:	VirtualKeyDownEvent(ID_KEY_LEFT);	break;
	case Keys::Return:	VirtualKeyDownEvent(ID_KEY_EXIT);	break;
	default:
		break;
	}
	e->Handled = true;
}

System::Void MovieForm::MovieForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (isIgnoreKeyEvent()) {
		e->Handled = false;
		return;
	}

	switch (e->KeyCode) {
	case Keys::Up:		VirtualKeyUpEvent(ID_KEY_UP);		break;
	case Keys::Down:	VirtualKeyUpEvent(ID_KEY_DOWN);		break;
	case Keys::Right:	VirtualKeyUpEvent(ID_KEY_RIGHT);	break;
	case Keys::Left:	VirtualKeyUpEvent(ID_KEY_LEFT);		break;
	case Keys::Return:	VirtualKeyUpEvent(ID_KEY_EXIT);		break;
	default:
		break;
	}
	e->Handled = true;
}

System::Void MovieForm::chkLockSw_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	unsigned char key = (chkLockSw->Checked) ? ID_KEY_LOCK_ON : ID_KEY_LOCK_OFF;
	VirtualMovieKey(true, getKeySource(), key);
}
System::Void MovieForm::button_up_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	//上ボタン
	VirtualMovieKey(false, getKeySource(), ID_KEY_UP);
}
System::Void MovieForm::button_right_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	//右ボタン
	VirtualMovieKey(false, getKeySource(), ID_KEY_RIGHT);
}
System::Void MovieForm::button_left_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	//左ボタン
	VirtualMovieKey(false, getKeySource(), ID_KEY_LEFT);
}
System::Void MovieForm::button_down_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	//下ボタン
	VirtualMovieKey(false, getKeySource(), ID_KEY_DOWN);
}
System::Void MovieForm::button_enter_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	//ENTERキー
	VirtualMovieKey(false, getKeySource(), ID_KEY_ENTER);
}
System::Void MovieForm::buttonMenu_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(false, getKeySource(), ID_KEY_MENU);
}
System::Void MovieForm::buttonHome_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(false, getKeySource(), ID_KEY_HOME);
}
System::Void MovieForm::buttonThumb_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(false, getKeySource(), ID_KEY_MODE);
}
System::Void MovieForm::buttonExit_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(false, getKeySource(), ID_KEY_EXIT);
}
System::Void MovieForm::button_up_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(true, getKeySource(), ID_KEY_UP);
}
System::Void MovieForm::button_right_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(true, getKeySource(), ID_KEY_RIGHT);
}
System::Void MovieForm::button_left_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(true, getKeySource(), ID_KEY_LEFT);
}
System::Void MovieForm::button_down_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(true, getKeySource(), ID_KEY_DOWN);
}
System::Void MovieForm::button_enter_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(true, getKeySource(), ID_KEY_ENTER);
}
System::Void MovieForm::buttonMenu_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(true, getKeySource(), ID_KEY_MENU);
}
System::Void MovieForm::buttonHome_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(true, getKeySource(), ID_KEY_HOME);
}
System::Void MovieForm::buttonThumb_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(true, getKeySource(), ID_KEY_MODE);
}
System::Void MovieForm::buttonExit_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	VirtualMovieKey(true, getKeySource(), ID_KEY_EXIT);
}
System::Void MovieForm::picbox_LCD_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	unsigned short keycode = e->Delta < 0 ? ID_KEY_DIAL_DOWN : ID_KEY_DIAL_UP;
	m_dbgCmd->rqCmndSysKey(getScreenId(), ID_SYS_KEY, ID_DECK, ID_KEY_PRS, keycode);
	m_dbgCmd->rqCmndSysKey(getScreenId(), ID_SYS_KEY, ID_DECK, ID_KEY_RLS, keycode);
}
//////////////////////////////////★★★★★★★★★★★★ID_SYS_TOUCH★★★★★★★★★★★★//////////////////////////////////
System::Windows::Forms::MouseEventArgs^ MovieForm::AdjustMousePosition(System::Windows::Forms::MouseEventArgs^ e) {
	ComboBox^ cb = cbox_Scale;
	if (cb->SelectedIndex == -1) {
		return e;
	}
	float scale = float::Parse((String^)cb->SelectedItem);
	return gcnew MouseEventArgs(e->Button, e->Clicks, (int)(e->X / scale), (int)(e->Y / scale), e->Delta);
}
System::Void MovieForm::picbox_LCD_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	picbox_LCD->Focus();
	e = AdjustMousePosition(e);
	POINT p = { e->X, e->Y };
	m_IsMouseDown = true;
	
	m_dbgCmd->rqCmndSysTouch(getScreenId(), ID_SYS_TOUCH, ID_TCH_PRS, p.x, p.y);
	// 長押し対応
	SetTimer(m_SimHWnd, IDC_TIMER_MOUSE_DOWN, 100, NULL);
	m_MouseX = p.x;
	m_MouseY = p.y;
}

System::Void MovieForm::picbox_LCD_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	e = AdjustMousePosition(e);
	POINT p = { e->X, e->Y };
	USHORT data[2] = { (USHORT)p.x, (USHORT)p.y };

	m_dbgCmd->rqCmndSysTouch(getScreenId(), ID_SYS_TOUCH, ID_TCH_RLS, p.x, p.y);
	m_IsMouseDown = false;
	KillTimer(m_SimHWnd, IDC_TIMER_MOUSE_DOWN);
	m_MouseX = p.x;
	m_MouseY = p.y;
}

System::Void MovieForm::picbox_LCD_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
	POINT p = { 0, 0 };
	if (m_IsMouseDown) {
		m_dbgCmd->rqCmndSysTouch(getScreenId(), ID_SYS_TOUCH, ID_TCH_RLS, p.x, p.y);
	}
	m_IsMouseDown = false;
	KillTimer(m_SimHWnd, IDC_TIMER_MOUSE_DOWN);
	m_MouseX = p.x;
	m_MouseY = p.y;
}

System::Void MovieForm::picbox_LCD_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	// オリジナル座標へ変換
	e = AdjustMousePosition(e);
	int x = 0, y = 0;
	int maxX = picbox_LCD->Image->Size.Width;
	int maxY = picbox_LCD->Image->Size.Height;

	if (e->X < 0) {
		x = 0;
	}
	else if (e->X >= maxX) {
		x = maxX - 1;
	}
	else {
		x = e->X;
	}
	if (e->Y < 0) {
		y = 0;
	}
	else if (e->Y >= maxY) {
		y = maxY - 1;
	}
	else {
		y = e->Y;
	}
	POINT p = { x, y };
	// カーソル位置の色取得
	Bitmap ^bmp = (Bitmap^)picbox_LCD->Image;
	BitmapData ^data = bmp->LockBits(System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height), ImageLockMode::ReadOnly, PixelFormat::Format32bppRgb);
	int pixel = Marshal::ReadInt32(data->Scan0, (y * bmp->Width + x) * 4);
	bmp->UnlockBits(data);
	byte r = (pixel >> 16) & 0xff;
	byte g = (pixel >> 8) & 0xff;
	byte b = (pixel >> 0) & 0xff;
	// タイトルの座標更新
	if (!this->TextOrigin) {
		this->TextOrigin = gcnew String(this->Text);
	}
	this->Text = this->TextOrigin + String::Format(" - [X:{0}, Y:{1}] [R:{2}, G:{3}, B:{4}, {5:X6}]", x, y, r, g, b, (pixel & 0x00FFFFFF));
	// マウス移動イベント
	if (m_IsMouseDown)m_dbgCmd->rqCmndSysTouch(getScreenId(), ID_SYS_TOUCH, ID_TCH_MV, p.x, p.y);
	m_MouseX = p.x;
	m_MouseY = p.y;
}

//////////////////////////////////★★★★★★★★★★★★ ID_APL_PARAM ★★★★★★★★★★★★//////////////////////////////////
System::Void MovieForm::btn_paramset_click(System::Object^  sender, System::EventArgs^  e) {
	int paramId = getSelectedAplParam();
	int paramValue = 0;
	int size = AplParamService::getInstance()->getSize(paramId);

	switch (APL_PARAM()->getParamDataType((UINT)paramId)) {
	case AplParamInitialType_Number:
	{
		if (cbox_ParamDef->Text == "") {
			return;
		}
		paramValue = Convert::ToInt32(cbox_ParamDef->Text);
		m_dbgCmd->rqCmndAplParam(ID_INVALID, ID_APL_PARAM, ID_PARAM_NUM, paramId, paramValue);
	}
	break;
	case AplParamInitialType_String:
	{
		if (tBox_ParamValue->Text->Length <= 0 || tBox_ParamValue->Text == "") return;
		char* data = (char*)(void*)Marshal::StringToHGlobalAnsi(tBox_ParamValue->Text);

		unsigned char* value = (unsigned char*)malloc(size);
		for (int i = 0; i < size; i++) {
			value[i] = data[i];
		}

		m_dbgCmd->rqCmndAplParam(ID_INVALID, ID_APL_PARAM, ID_PARAM_STRING, paramId, (int)value);
		Marshal::FreeHGlobal(IntPtr(data));
	}
	break;
	case AplParamInitialType_Ip:
	{
		if (tBox_ParamValue->Text->Length <= 0 || tBox_ParamValue->Text == "") return;
		unsigned char* data = (unsigned char*)malloc(size);
		array<String^>^ pos = tBox_ParamValue->Text->Split('.');
		int x[100];
		if (pos->Length <= AplParamService::getInstance()->getSize(paramId)) {
			for (int i = 0; i < pos->Length; i++) {
				if (int::TryParse(pos[i], x[i])) {
					data[i] = x[i];
				}
			}
		}
		m_dbgCmd->rqCmndAplParam(ID_INVALID, ID_APL_PARAM, ID_PARAM_IP, paramId, (int)data);
	}
	break;
	default:
		break;
	}
}

unsigned int MovieForm::getSelectedWindowID()
{
	int index = m_WindowIdList->IndexOf((String^)cbox_WindowName->SelectedItem);
	unsigned int winId = (unsigned int)CtWindowIDString::getWindowID(index);
	return winId;
}

unsigned int MovieForm::getSelectedAplParam()
{
	return m_AplParamList->IndexOf((String^)cbox_ParamID->SelectedItem);
}

System::Void MovieForm::initWindowID()
{
	m_WindowIdList = gcnew List<String^>();

	for (int i = 0; i < WINDOWID_MAX_NUM; i++) {
		const char* name = CtWindowIDString::getString(i);

		if (strcmp(name, "Unknown") == 0) {
			m_WindowIdList->Add(String::Format("Window_{0:D3}", i));
		}
		else {
			m_WindowIdList->Add(gcnew String(name));
		}
	}

	for (int i = 0; i < m_WindowIdList->Count; i++) {
		cbox_WindowName->Items->Add(m_WindowIdList[i]);
	}

	cbox_WindowName->SelectedIndex = 0;
}

System::Void MovieForm::initParamID()
{
	m_AplParamList = gcnew List<String^>();

	for (int i = 0; i < AplParamIdMax; i++) {
		const char* name = AplParamIDString::getString(i);

		if (strcmp(name, "Unknown") == 0) {
			m_AplParamList->Add(String::Format("{0:D3}", i));
		}
		else {
			m_AplParamList->Add(gcnew String(name));
		}
	}

	for (int i = 0; i < m_AplParamList->Count; i++) {
		cbox_ParamID->Items->Add(m_AplParamList[i]);
	}

	cbox_ParamID->SelectedIndex = 0;
}

System::Void MovieForm::btn_DrawRect_Click(System::Object^  sender, System::EventArgs^  e) {
	int x = int::Parse(tbox_Rect_x->Text);
	int y = int::Parse(tbox_Rect_y->Text);
	int w = int::Parse(tbox_Rect_width->Text) - 1;
	int h = int::Parse(tbox_Rect_height->Text) - 1;

	DrawRectangleToScreenLCD(x, y, w, h);
}

System::Void MovieForm::DrawRectangleToScreenLCD(int x, int y, int w, int h) {
	PictureBox ^p = picbox_RectLCD;
	Graphics ^g = Graphics::FromImage(p->Image);

	g->DrawRectangle(Drawing::Pens::Red, System::Drawing::Rectangle(x, y, w, h));
	p->Invalidate();
}

System::Void MovieForm::btn_DrawReset_Click(System::Object^  sender, System::EventArgs^  e) {

	PictureBox ^p = picbox_RectLCD;
	Graphics ^g = Graphics::FromImage(p->Image);

	g->CompositingMode = System::Drawing::Drawing2D::CompositingMode::SourceCopy;
	g->FillRectangle(Drawing::Brushes::Transparent, System::Drawing::Rectangle(0, 0, m_ScreenLCD_Width, m_ScreenLCD_Height));
	p->Invalidate();
}

System::Void MovieForm::cbox_Disp_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	picbox_LCD->Visible = cbox_LCD->Checked;
	picbox_LOUT->Visible = cbox_LOUT->Checked;
}

System::Void MovieForm::btnSave_LCD_Click(System::Object^  sender, System::EventArgs^  e) {
	SaveImage("LCD_", picbox_LCD->Image);
}

System::Void MovieForm::btnSave_LOUT_Click(System::Object^  sender, System::EventArgs^  e) {
	SaveImage("LOUT_", picbox_LOUT->Image);
}

System::Void MovieForm::SaveImage(String^ header, Image ^source) {
	ImageFormat ^format = ImageFormat::Jpeg;
	String ^ext = ".jpg";
	String ^output = ".\\save\\";

	// format(jpg/bmp)の決定
	if (radbtnSave_BMP->Checked) {
		format = ImageFormat::Bmp;
		ext = ".bmp";
	}

	// 出力先dir作成
	System::IO::Directory::CreateDirectory(output);

	// filenameの決定
	for (int i = 0; i < 9999; i++) {
		String ^filename = output + header + i.ToString("0000") + ext;
		if (!System::IO::File::Exists(filename)) {
			source->Save(filename, format);
			return;
		}
	}
}

System::Void MovieForm::cbox_Scale_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
	ComboBox ^cb = (ComboBox^)sender;
	if (cb->SelectedIndex != -1) {
		float scale = float::Parse((String^)cb->SelectedItem);

		int lcd_w = (int)(m_ScreenLCD_Width * scale);
		int lcd_h = (int)(m_ScreenLCD_Height * scale);
		int lout_w = (int)(m_ScreenLOUT_Width * scale);
		int lout_h = (int)(m_ScreenLOUT_Height * scale);

		picbox_LCD->Width = lcd_w;
		picbox_LCD->Height = lcd_h;

		picbox_RectLCD->Width = lcd_w;
		picbox_RectLCD->Height = lcd_h;

		picbox_LOUT->Width = lout_w;
		picbox_LOUT->Height = lout_h;
	}
}

System::Void MovieForm::cbox_WindowName_TextUpdate(System::Object^  sender, System::EventArgs^  e) {
	ComboBox ^cb = (ComboBox^)sender;

	int start = cb->SelectionStart;
	int length = cb->SelectionLength;
	String ^text = cb->Text->ToUpper();

	cb->Items->Clear();

	for (int i = 0; i < m_WindowIdList->Count; i++) {
		bool add = true;

		if (cb->Text->Length >= 2) {
			add = m_WindowIdList[i]->ToUpper()->Contains(text);
		}

		if (add) {
			cbox_WindowName->Items->Add(m_WindowIdList[i]);
		}
	}

	cb->SelectionStart = start;
	cb->SelectionLength = length;
	cb->DroppedDown = true;
	Cursor = Cursor;	// マウスカーソル消失対策
}
System::Void MovieForm::cbox_ParamID_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	// 前回表示クリア
	cbox_ParamDef->Items->Clear();

	int id = getSelectedAplParam();
	AplParamService::AplParamSubItem* subItem = (AplParamService::AplParamSubItem*)APL_PARAM()->getParamSubItem(id);
	if (subItem == NULL) {
		// Index等のSubItem定義がNullの場合はValueTextのSetから実行させる
		tBox_ParamValue->Enabled = true;
		cbox_ParamDef->Items->Clear();
		cbox_ParamDef->Enabled = false;
		return;
	}

	switch (APL_PARAM()->getParamDataType(id)) {
	case AplParamInitialType_Number:
		for (int i = 0; AplParamState_End != subItem[i].state; i++) {
			cbox_ParamDef->Items->Add(i);
		}
		cbox_ParamDef->SelectedIndex = APL_PARAM()->getData(id);
		cbox_ParamDef->Enabled = true;
		tBox_ParamValue->Clear();
		tBox_ParamValue->Enabled = false;
		break;
	default:
		tBox_ParamValue->Enabled = true;
		cbox_ParamDef->Enabled = false;
		break;
	}
}

System::Void MovieForm::cbox_ParamID_TextUpdate(System::Object^  sender, System::EventArgs^  e) {
	ComboBox ^cb = (ComboBox^)sender;

	int start = cb->SelectionStart;
	int length = cb->SelectionLength;
	String ^text = cb->Text->ToUpper();

	cb->Items->Clear();

	for (int i = 0; i < m_AplParamList->Count; i++) {
		bool add = true;

		if (cb->Text->Length >= 2) {
			add = m_AplParamList[i]->ToUpper()->Contains(text);
		}

		if (add) {
			cbox_ParamID->Items->Add(m_AplParamList[i]);
		}
	}

	cb->SelectionStart = start;
	cb->SelectionLength = length;
	cb->DroppedDown = true;
	Cursor = Cursor;	// マウスカーソル消失対策
}

System::Void MovieForm::btn_NextWind_Click(System::Object^  sender, System::EventArgs^  e) {
	// 次のWindowIDへ
	if (cbox_WindowName->Items->Count <= cbox_WindowName->SelectedIndex + 1) {
		return;
	}
	cbox_WindowName->SelectedIndex++;
	cbox_WindowName->Focus();
	// Popup
	m_dbgCmd->rqCmndWindowTrans(getScreenId(), ID_WIND, ID_SWAP, getSelectedWindowID());
}

System::Void MovieForm::btn_PrevWind_Click(System::Object^  sender, System::EventArgs^  e) {
	// 次のWindowIDへ
	if (0 < cbox_WindowName->SelectedIndex - 1) {
		cbox_WindowName->SelectedIndex = cbox_WindowName->SelectedIndex - 1;
	}
	else {
		return;
	}
	cbox_WindowName->Focus();
	// Popup
	m_dbgCmd->rqCmndWindowTrans(getScreenId(), ID_WIND, ID_SWAP, getSelectedWindowID());

}

System::Void MovieForm::btn_ReadLog_Click(System::Object^  sender, System::EventArgs^  e) {
	DWORD dwThreadId;
	if (m_LogPlayerThread == NULL) {
		//ファイルを開くダイアログの作成 
		OpenFileDialog^ dlg = gcnew OpenFileDialog;
		//ファイルフィルタ 
		dlg->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
		dlg->Title = "LogFile名";
		System::String^ dirPath = ".\\saveLog";
		if (IO::Directory::Exists(dirPath)) {
			// 出力先dir作成
			dlg->InitialDirectory = ".\\saveLog";
		}
		else {
			dlg->InitialDirectory = ".\\";
		}

		//ダイアログの表示 （Cancelボタンがクリックされた場合は何もしない）
		if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::Cancel) return;
		CtLogPlayer::thrdAtt.filePath = dlg->FileName;
		CtLogPlayer::thrdAtt.hWnd = m_SimHWnd;
		EnableWindow(m_SimHWnd, SW_HIDE);
		m_LogPlayerThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)beginReadLogThread, NULL, 0, &dwThreadId);
	}
}

System::Void MovieForm::saveSetting() {

	String^ filePath = ".simrc";
	using System::IO::FileStream;
	using System::IO::FileMode;
	using System::IO::StreamWriter;
	using namespace System::Text;
	StreamWriter^ fout;
	try {
		fout = gcnew StreamWriter(filePath, false, Encoding::GetEncoding("Shift_JIS"));
	}
	catch (Exception^ e) {
		Console::WriteLine("The process failed: " + e->Message);
		return;
	}

	char str[50] = { 0 };
	System::String^ string;
	// 1:Scale
	sprintf(str, "%d", cbox_Scale->SelectedIndex);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 2:Lout出力
	sprintf(str, "%d", cbox_LOUT->Checked);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 3:WinID-Check
	sprintf(str, "%d", chkbox_winid->Checked);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 4:WinID
	sprintf(str, "%d", m_WindowIdList->IndexOf((String^)cbox_WindowName->SelectedItem));
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 5:
	sprintf(str, "%d", cbox_ScreenType->SelectedIndex);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 6:
	sprintf(str, "%d", radbtnSave_JPG->Checked);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 7:
	sprintf(str, "%d", radbtnSave_BMP->Checked);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 8
	sprintf(str, "%d", radbtn_Deck->Checked);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 9
	sprintf(str, "%d", rdbtn_Rop->Checked);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 10
	sprintf(str, "%d", radbtn_Grip->Checked);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 11
	int ParamIndex = m_AplParamList->IndexOf((String^)cbox_ParamID->SelectedItem);
	sprintf(str, "%d", ParamIndex);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	// 12
	fout->WriteLine(cbox_ParamDef->Text);

	// 13
	fout->WriteLine(tBox_ParamValue->Text);

	// 14
	fout->WriteLine(tbox_Rect_x->Text);

	// 15
	fout->WriteLine(tbox_Rect_y->Text);

	// 16
	fout->WriteLine(tbox_Rect_y->Text);

	// 17
	fout->WriteLine(tbox_Rect_height->Text);

	// 18
	//fout->WriteLine(listbox_RectHistory->Text);

	// 19:chk_Box_Logo
	sprintf(str, "%d", chk_Box_Logo->Checked);
	string = gcnew String(str);
	fout->WriteLine(string);
	delete string;

	fout->Close();
}

System::Void MovieForm::readSetting() {
	String^ filePath = ".\\.simrc";
	using System::IO::StreamReader;
	StreamReader^ fin;
	try {
		fin = gcnew StreamReader(filePath);
	}
	catch (Exception^ e) {
		Console::WriteLine("The process failed: " + e->Message);
		//		fin->Close();
		return;
	}
	// 抜き出し
	// Scale
	String ^ s = fin->ReadLine();
	if (s != nullptr) {
		cbox_Scale->SelectedIndex = INT::Parse(s);
	}

	// LOUT
	s = fin->ReadLine();
	if (s != nullptr) {
		cbox_LOUT->Checked = BOOL::Parse(s) ? true : false;
	}

	// WinID-Check
	s = fin->ReadLine();
	if (s != nullptr) {
		chkbox_winid->Checked = BOOL::Parse(s) ? true : false;
	}

	// WinID
	s = fin->ReadLine();
	if (s != nullptr) {
		cbox_WindowName->SelectedIndex = INT::Parse(s);
	}

	// 
	s = fin->ReadLine();
	if (s != nullptr) {
		cbox_ScreenType->SelectedIndex = INT::Parse(s);
	}

	// 
	s = fin->ReadLine();
	if (s != nullptr) {
		radbtnSave_JPG->Checked = BOOL::Parse(s) ? true : false;
	}

	// 
	s = fin->ReadLine();
	if (s != nullptr) {
		radbtnSave_BMP->Checked = BOOL::Parse(s) ? true : false;
	}

	// 7
	s = fin->ReadLine();
	if (s != nullptr) {
		radbtn_Deck->Checked = BOOL::Parse(s) ? true : false;
	}

	// 8
	s = fin->ReadLine();
	if (s != nullptr) {
		rdbtn_Rop->Checked = BOOL::Parse(s) ? true : false;
	}

	// 9
	s = fin->ReadLine();
	if (s != nullptr) {
		radbtn_Grip->Checked = BOOL::Parse(s) ? true : false;
	}

	// 10
	s = fin->ReadLine();
	if (s != nullptr) {
		cbox_ParamID->SelectedIndex = INT::Parse(s);
	}

	// 11
	s = fin->ReadLine();
	if (s != nullptr) {
		cbox_ParamDef->Text = s;
	}

	// 12
	s = fin->ReadLine();
	if (s != nullptr) {
		tBox_ParamValue->Text = s;
	}

	// 14
	s = fin->ReadLine();
	if (s != nullptr) {
		tbox_Rect_x->Text = s;
	}

	// 15
	s = fin->ReadLine();
	if (s != nullptr) {
		tbox_Rect_y->Text = s;
	}

	// 16
	s = fin->ReadLine();
	if (s != nullptr) {
		tbox_Rect_width->Text = s;
	}

	// 17
	s = fin->ReadLine();
	if (s != nullptr) {
		tbox_Rect_height->Text = s;
	}

	// 18
	//s = fin->ReadLine();
	if (s != nullptr) {
		//	listbox_RectHistory->Text = s;
	}
	// 19
	s = fin->ReadLine();
	if (String::IsNullOrEmpty(s) != true) {
		chk_Box_Logo->Checked = BOOL::Parse(s) ? true : false;
	}

	fin->Close();
}

System::Void MovieForm::chk_Dial_Enter_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (chk_Dial_Enter->Checked) {
		chk_Dial_Enter->Text = "押下中";
		VirtualMovieKey(true, getKeySource(), ID_KEY_DIAL_FUNC);
	}
	if (!chk_Dial_Enter->Checked) {
		chk_Dial_Enter->Text = "Enter";
		VirtualMovieKey(false, getKeySource(), ID_KEY_DIAL_FUNC);
	}
}

bool MovieForm::createList(int _Index) {
	// reset
	listV_Widget->Items->Clear();

	CtDbgWidgetTree* pTree = CtDbgWidgetTree::getInstance();
	CtDbgWidgetTree::CtDbgWidgetTreeData* pTreeData = pTree->getTreeData(_Index);

	if (pTreeData == NULL) return false;
	String^ str = nullptr;
	char c_str[40];
	ListViewItem^ listItem;

	// Item名称
	listItem = gcnew ListViewItem("深度");
	// Item内容
	sprintf(c_str, "%d", pTreeData->depth);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("WidgetAddress");
	// Item内容
	sprintf(c_str, "0x%08X", pTreeData->widgetAdr);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("WidgetType");
	// Item内容
	sprintf(c_str, "%s", pTreeData->WidgetType);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("Size");
	listV_Widget->Items->Add(listItem);
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("X");
	// Item内容
	sprintf(c_str, "%d", pTreeData->Size_x);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("Y");
	// Item内容
	sprintf(c_str, "%d", pTreeData->Size_y);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("Region");
	listV_Widget->Items->Add(listItem);
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("X");
	// Item内容
	sprintf(c_str, "%d", pTreeData->region_x);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("Y");
	// Item内容
	sprintf(c_str, "%d", pTreeData->region_y);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("Width");
	// Item内容
	sprintf(c_str, "%d", pTreeData->region_w);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("Height");
	// Item内容
	sprintf(c_str, "%d", pTreeData->region_h);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("Screen設定");
	// Item内容
	sprintf(c_str, "%d", pTreeData->screen);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("表示フラグ");
	// Item内容
	sprintf(c_str, "%s", pTreeData->visible ? "TRUE" : "FALSE");
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("透過設定");
	// Item内容
	sprintf(c_str, "%s", pTreeData->trans ? "TRUE" : "FALSE");
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	// Item名称
	listItem = gcnew ListViewItem("ParentWidgetAddress");
	// Item内容
	sprintf(c_str, "0x%08X", pTreeData->ParentWidgetAdr);
	str = gcnew String(c_str);
	listItem->SubItems->Add(str);
	listV_Widget->Items->Add(listItem);
	delete str;
	delete listItem;

	return true;
}

int searchTreeIndex(String^ str) {
	CtDbgWidgetTree* pTree = CtDbgWidgetTree::getInstance();
	int endIndex = pTree->getTreeDataSize();
	CtDbgWidgetTree::CtDbgWidgetTreeData* pTreeData;

	for (int index = 0; index <= endIndex; index++) {
		pTreeData = pTree->getTreeData(index);
		char c_str[40] = "";
		sprintf(c_str, "%s (%08X)", pTreeData->WidgetType, pTreeData->widgetAdr);
		String^ string = gcnew String(c_str);
		if (str->CompareTo(string) == 0) {
			return index;
		}
	}
	return ++endIndex;
}

System::Void MovieForm::treeV_Widget_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
	//listV_Widgetの更新
	createList(searchTreeIndex(e->Node->Text));
}
System::Void MovieForm::treeV_Widget_NodeMouseClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right) {
		int index = searchTreeIndex(e->Node->Text);
		CtDbgWidgetTree::CtDbgWidgetTreeData* pTreeData = CtDbgWidgetTree::getInstance()->getTreeData(index);
		if (pTreeData == NULL) return;
		// Draw pTreeData
		DrawRectangleToScreenLCD(pTreeData->region_x, pTreeData->region_y, pTreeData->region_w, pTreeData->region_h);
		treeV_Widget->SelectedNode = e->Node;
		treeV_Widget->Focus();
	}
}

void createTree(TreeNode^ pParent, int _depth, int& _index) {
	CtDbgWidgetTree* pTree = CtDbgWidgetTree::getInstance();
	int endIndex = pTree->getTreeDataSize();
	TreeNode^ child = nullptr;

	for (_index; _index <= endIndex; ) {
		CtDbgWidgetTree::CtDbgWidgetTreeData* pTreeData = pTree->getTreeData(_index);
		if (pTreeData == NULL) return;
		if (_depth == pTreeData->depth) {
			// 同階層
			char str[40] = "";
			sprintf(str, "%s (%08X)", pTreeData->WidgetType, pTreeData->widgetAdr);
			String^ string = gcnew String(str);

			child = gcnew TreeNode(string);
			pParent->Nodes->Add(child);
			_index++;
		}
		else if (_depth < pTreeData->depth) {
			createTree(child, pTreeData->depth, _index);
			if ((pTreeData = pTree->getTreeData(_index)) == NULL) return;
			if (pTreeData->depth == 0) return; // Screenが違う
		}
		else if (_depth > pTreeData->depth) {
			// 親階層
			return;
		}
	}
}

bool MovieForm::updateTreeData() {
	CtDbgWidgetTree* pTree = CtDbgWidgetTree::getInstance();
	int endIndex = pTree->getTreeDataSize();

	TreeNode^ RootLcd = gcnew TreeNode("LCD");
	TreeNode^ RootLout = gcnew TreeNode("LOUT");

	int _depth = 0;
	int index = 0;
	treeV_Widget->Nodes->Add(RootLcd);
	createTree(RootLcd, _depth, index);

	_depth = 0;
	treeV_Widget->Nodes->Add(RootLout);
	createTree(RootLout, _depth, index);

	return true;
}
