#pragma once

#pragma warning(disable:4115)	/* named type definition in parentheses (this comes from a visual studio include file) */
#include <windows.h>
#include <msclr/gcroot.h>
#include <iostream>
#include <resource.h>

// For Simu
#include "SysIf.h"
#include "AplParamService.h"
#include "Logo.h"

// For Dbg
#include "CtCmdLine.h"
#include "CtLogPlayer.h"
#include "CtDbgCmndAdapter.h"
#include "CtDbgWidgetTree.h"

namespace simulator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::Diagnostics;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// MovieForm の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class MovieForm : public System::Windows::Forms::Form
	{
	public:
		MovieForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			Init();
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MovieForm()
		{
			saveSetting();
			Finish();
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  grpbx_shrcut;
	private: System::Windows::Forms::Button^  btn_sc_Clip;
	private: System::Windows::Forms::Button^  btn_sc_Play;
	private: System::Windows::Forms::GroupBox^  grpbx_refInfo;
	private: System::Windows::Forms::Button^  btn_Variety5;
	private: System::Windows::Forms::Button^  btn_PrevWind;
	private: System::Windows::Forms::Button^  btn_ClsInfo;
	private: System::Windows::Forms::Button^  btn_MemInfo;

	private: System::Windows::Forms::CheckBox^  chk_Dial_Enter;
	private: System::Windows::Forms::Button^  btn_variety8;
	private: System::Windows::Forms::Button^  btn_variety6;
	private: System::Windows::Forms::Button^  btn_variety7;
	private: System::Windows::Forms::Button^  btn_Setting;













	private: System::Windows::Forms::Button^  button_Info_Mode;
	private: System::Windows::Forms::TabControl^  tab_Ctrl_Sim;

	private: System::Windows::Forms::TabPage^  Controller;
	private: System::Windows::Forms::TabPage^  WidgetExplorer;
	private: System::Windows::Forms::SplitContainer^  split_Cont_Widget_Exp;


	private: System::Windows::Forms::TabPage^  Support;
	private: System::Windows::Forms::GroupBox^  gBox_pictSave;

	private: System::Windows::Forms::RadioButton^  radbtnSave_BMP;
	private: System::Windows::Forms::RadioButton^  radbtnSave_JPG;
	private: System::Windows::Forms::Button^  btnSave_LOUT;
	private: System::Windows::Forms::Button^  btnSave_LCD;
	private: System::Windows::Forms::SplitContainer^  split_Ctnr_Exp;
	private: System::Windows::Forms::TreeView^  treeV_Widget;
	private: System::Windows::Forms::ListView^  listV_Widget;
	private: System::Windows::Forms::ColumnHeader^  ラベル;
	private: System::Windows::Forms::ColumnHeader^  データ;
	private: System::Windows::Forms::PictureBox^  picbox_RectLCD;
	private: System::Windows::Forms::TabPage^  CommandCtrl;
	private: System::Windows::Forms::CheckBox^  chk_Box_Logo;
	private: System::Windows::Forms::GroupBox^  gBox_Save;
	private: System::Windows::Forms::GroupBox^  gBox_SimSetting;
	private: System::Windows::Forms::Label^  treeV_text;



	protected:
	internal: CtDbgCmndAdapter* m_dbgCmd;
	private:
		void Init(void);
		void Finish(void);
		void Update(void);
		void DrawCallbackLcd(int w, int h, void* data);
		void DrawCallbackLout(int w, int h, void* data);
		void DrawCallback(int w, int h, void* data, bool isLcd);
		void ExecDraw(bool isLcd);
		void InitImage();
		void createImageBuffer(Bitmap ^src, array<int> ^%dst);
		unsigned int getKeySource();
		bool updateTreeData();
		bool createList(int _Index);

		const static int m_ScreenLCD_Width = ScreenConfig[0].Size.width;
		const static int m_ScreenLCD_Height = ScreenConfig[0].Size.height;
		const static int m_ScreenLOUT_Width = ScreenConfig[1].Size.width;
		const static int m_ScreenLOUT_Height = ScreenConfig[1].Size.height;

		CWrapperLcd m_cWrapperLcd;
		CWrapperLout m_cWrapperLout;
		static bool s_isInit = FALSE;
		static int s_kurupon_index = 0;
		bool m_IsIgnoreKeyEvent;
		array<int> ^m_BackGroundImageBufLcd;
		array<int> ^m_BackGroundImageBufLout;
		array<int> ^m_ImageBufLcd;
		array<int> ^m_ImageBufLout;
		Bitmap ^m_RectImageLcd;
		bool m_IsMouseDown;

		String ^TextOrigin;
		List<String^>^ m_WindowIdList;
		List<String^>^ m_AplParamList;
		HANDLE m_CmdLineThread;
		HANDLE m_CmdLineHelperThread;
		HANDLE m_LogPlayerThread;
		HWND m_SimHWnd;
		int m_MouseX, m_MouseY;
		Logo^ m_Logo;
	private: System::Windows::Forms::Button^  btn_ChangeWindow;
	private: System::Windows::Forms::Button^  btn_PopupWindow;
	private: System::Windows::Forms::Button^  btn_ReturnWindow;
	private: System::Windows::Forms::Button^  btn_CloseWindow;
	private: System::Windows::Forms::Label^  lblWindowID;
	private: System::Windows::Forms::Label^  lblScreen;
	private: System::Windows::Forms::ComboBox^  cbox_WindowName;
	private: System::Windows::Forms::ComboBox^  cbox_ScreenType;
	private: System::Windows::Forms::Button^  btn_DrawRect;
	private: System::Windows::Forms::TextBox^  tbox_Rect_x;
	private: System::Windows::Forms::TextBox^  tbox_Rect_y;
	private: System::Windows::Forms::TextBox^  tbox_Rect_width;
	private: System::Windows::Forms::TextBox^  tbox_Rect_height;
	private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::GroupBox^  gBoxOutLine;




	private: System::Windows::Forms::Button^  btn_DrawDelete;
	private: System::Windows::Forms::Button^  btn_SwapWindow;
	private: System::Windows::Forms::Button^  btn_GetCurrent;
	private: System::Windows::Forms::Button^  btn_GetRoot;
	private: System::Windows::Forms::GroupBox^  gBoxDeck;
	private: System::Windows::Forms::Button^  buttonExit;
	private: System::Windows::Forms::Button^  btn_Thumb;
	private: System::Windows::Forms::Button^  btn_Home;
	private: System::Windows::Forms::Button^  btn_Menu;

	private: System::Windows::Forms::Button^  btn_dial_plus;
	private: System::Windows::Forms::Button^  btn_User3;
	private: System::Windows::Forms::Button^  btn_User2;
	private: System::Windows::Forms::Button^  btn_User1;
	private: System::Windows::Forms::Button^  btn_dial_minus;
	private: System::Windows::Forms::Button^  btn_User9;
	private: System::Windows::Forms::Button^  btn_User8;
	private: System::Windows::Forms::Button^  btn_User7;
	private: System::Windows::Forms::Button^  btn_User6;
	private: System::Windows::Forms::Button^  btn_User5;
	private: System::Windows::Forms::Button^  btn_User4;

	private: System::Windows::Forms::GroupBox^  gbox_WindowControll;
	private: System::Windows::Forms::Button^  btn_ShowOutline;
	private: System::Windows::Forms::CheckBox^  chkLockSw;
	private: System::Windows::Forms::GroupBox^  gBox_AplParam;
	private: System::Windows::Forms::Button^  btn_paramSet;
	private: System::Windows::Forms::Label^  lblParamID;
	private: System::Windows::Forms::ComboBox^  cbox_ParamDef;
	private: System::Windows::Forms::ComboBox^  cbox_ParamID;
	private: System::Windows::Forms::TextBox^  tBox_ParamValue;
	private: System::Windows::Forms::Label^  lblParamValue;
	private: System::Windows::Forms::Label^  lblParamDef;
	private: System::Windows::Forms::PictureBox^  picbox_LCD;
	private: System::Windows::Forms::CheckBox^  cbox_LCD;
	private: System::Windows::Forms::CheckBox^  cbox_LOUT;
	private: System::Windows::Forms::PictureBox^  picbox_LOUT;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::Button^  button_up;
	private: System::Windows::Forms::Button^  button_left;
	private: System::Windows::Forms::Button^  button_right;
	private: System::Windows::Forms::Button^  button_down;
	private: System::Windows::Forms::Button^  button_enter;

	private: System::Windows::Forms::Panel^  panel_LCD;
	private: System::Windows::Forms::Panel^  panel_LOUT;

	private: System::Windows::Forms::ComboBox^  cbox_Scale;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  btn_LogPlay;
	private: System::Windows::Forms::GroupBox^  LogPlayer;
	private: System::Windows::Forms::Button^  btn_NextWind;
	private: System::Windows::Forms::Button^  btn_ConsoleClear;
	private: System::Windows::Forms::Button^  btn_SaveLog;
	private: System::Windows::Forms::CheckBox^  chkbox_winid;
	private: System::Windows::Forms::Button^  btn_RemoveWindow;
	private: System::Windows::Forms::RadioButton^  radbtn_Deck;
	private: System::Windows::Forms::RadioButton^  radbtn_Grip;
	private: System::Windows::Forms::CheckBox^  chk_Shift;
	private: System::Windows::Forms::RadioButton^  rdbtn_Rop;
	private: System::Windows::Forms::Button^  btn_variety;
	private: System::Windows::Forms::Button^  btn_variety4;
	private: System::Windows::Forms::Button^  btn_variety3;
	private: System::Windows::Forms::Button^  btn_variety2;
	private: System::Windows::Forms::Button^  btn_sc_Info;
	private: System::Windows::Forms::Button^  btn_sc_Thumb;
	private: System::Windows::Forms::Button^  btn_sc_Home;
	private: System::Windows::Forms::Button^  btn_sc_Menu;
	private: System::Windows::Forms::Button^  btn_sc_View;
	private: System::Windows::Forms::GroupBox^  grpbox_keysrc;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  btn_ReadLog;
	private: System::Windows::Forms::Button^  btn_CmdLine;
	private: System::Windows::Forms::GroupBox^  grpbox_Dial;

	private: System::ComponentModel::IContainer^  components;
			 /// <summary>
			 /// 必要なデザイナ変数です。
			 /// </summary>


#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// デザイナ サポートに必要なメソッドです。このメソッドの内容を
			 /// コード エディタで変更しないでください。
			 /// </summary>
			 void InitializeComponent(void)
			 {
					 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MovieForm::typeid));
					 this->button_up = (gcnew System::Windows::Forms::Button());
					 this->button_left = (gcnew System::Windows::Forms::Button());
					 this->button_right = (gcnew System::Windows::Forms::Button());
					 this->button_down = (gcnew System::Windows::Forms::Button());
					 this->button_enter = (gcnew System::Windows::Forms::Button());
					 this->btn_ChangeWindow = (gcnew System::Windows::Forms::Button());
					 this->btn_PopupWindow = (gcnew System::Windows::Forms::Button());
					 this->btn_ReturnWindow = (gcnew System::Windows::Forms::Button());
					 this->btn_CloseWindow = (gcnew System::Windows::Forms::Button());
					 this->lblScreen = (gcnew System::Windows::Forms::Label());
					 this->lblWindowID = (gcnew System::Windows::Forms::Label());
					 this->cbox_WindowName = (gcnew System::Windows::Forms::ComboBox());
					 this->cbox_ScreenType = (gcnew System::Windows::Forms::ComboBox());
					 this->btn_DrawRect = (gcnew System::Windows::Forms::Button());
					 this->tbox_Rect_x = (gcnew System::Windows::Forms::TextBox());
					 this->tbox_Rect_y = (gcnew System::Windows::Forms::TextBox());
					 this->tbox_Rect_width = (gcnew System::Windows::Forms::TextBox());
					 this->tbox_Rect_height = (gcnew System::Windows::Forms::TextBox());
					 this->label1 = (gcnew System::Windows::Forms::Label());
					 this->gBoxOutLine = (gcnew System::Windows::Forms::GroupBox());
					 this->btn_DrawDelete = (gcnew System::Windows::Forms::Button());
					 this->btn_ShowOutline = (gcnew System::Windows::Forms::Button());
					 this->btn_SwapWindow = (gcnew System::Windows::Forms::Button());
					 this->gBoxDeck = (gcnew System::Windows::Forms::GroupBox());
					 this->button_Info_Mode = (gcnew System::Windows::Forms::Button());
					 this->grpbox_Dial = (gcnew System::Windows::Forms::GroupBox());
					 this->chk_Dial_Enter = (gcnew System::Windows::Forms::CheckBox());
					 this->btn_dial_minus = (gcnew System::Windows::Forms::Button());
					 this->btn_dial_plus = (gcnew System::Windows::Forms::Button());
					 this->grpbox_keysrc = (gcnew System::Windows::Forms::GroupBox());
					 this->rdbtn_Rop = (gcnew System::Windows::Forms::RadioButton());
					 this->radbtn_Grip = (gcnew System::Windows::Forms::RadioButton());
					 this->radbtn_Deck = (gcnew System::Windows::Forms::RadioButton());
					 this->btn_User9 = (gcnew System::Windows::Forms::Button());
					 this->btn_User8 = (gcnew System::Windows::Forms::Button());
					 this->chk_Shift = (gcnew System::Windows::Forms::CheckBox());
					 this->btn_User7 = (gcnew System::Windows::Forms::Button());
					 this->chkLockSw = (gcnew System::Windows::Forms::CheckBox());
					 this->btn_User6 = (gcnew System::Windows::Forms::Button());
					 this->btn_User5 = (gcnew System::Windows::Forms::Button());
					 this->btn_User4 = (gcnew System::Windows::Forms::Button());
					 this->buttonExit = (gcnew System::Windows::Forms::Button());
					 this->btn_Menu = (gcnew System::Windows::Forms::Button());
					 this->btn_Thumb = (gcnew System::Windows::Forms::Button());
					 this->btn_User3 = (gcnew System::Windows::Forms::Button());
					 this->btn_Home = (gcnew System::Windows::Forms::Button());
					 this->btn_User2 = (gcnew System::Windows::Forms::Button());
					 this->btn_User1 = (gcnew System::Windows::Forms::Button());
					 this->btn_variety4 = (gcnew System::Windows::Forms::Button());
					 this->btn_variety3 = (gcnew System::Windows::Forms::Button());
					 this->btn_variety2 = (gcnew System::Windows::Forms::Button());
					 this->btn_variety = (gcnew System::Windows::Forms::Button());
					 this->label2 = (gcnew System::Windows::Forms::Label());
					 this->cbox_Scale = (gcnew System::Windows::Forms::ComboBox());
					 this->cbox_LOUT = (gcnew System::Windows::Forms::CheckBox());
					 this->cbox_LCD = (gcnew System::Windows::Forms::CheckBox());
					 this->gbox_WindowControll = (gcnew System::Windows::Forms::GroupBox());
					 this->chkbox_winid = (gcnew System::Windows::Forms::CheckBox());
					 this->btn_PrevWind = (gcnew System::Windows::Forms::Button());
					 this->btn_RemoveWindow = (gcnew System::Windows::Forms::Button());
					 this->btn_NextWind = (gcnew System::Windows::Forms::Button());
					 this->btn_sc_View = (gcnew System::Windows::Forms::Button());
					 this->btn_sc_Info = (gcnew System::Windows::Forms::Button());
					 this->btn_sc_Thumb = (gcnew System::Windows::Forms::Button());
					 this->btn_sc_Home = (gcnew System::Windows::Forms::Button());
					 this->btn_GetCurrent = (gcnew System::Windows::Forms::Button());
					 this->btn_GetRoot = (gcnew System::Windows::Forms::Button());
					 this->btn_sc_Menu = (gcnew System::Windows::Forms::Button());
					 this->gBox_AplParam = (gcnew System::Windows::Forms::GroupBox());
					 this->tBox_ParamValue = (gcnew System::Windows::Forms::TextBox());
					 this->lblParamValue = (gcnew System::Windows::Forms::Label());
					 this->lblParamDef = (gcnew System::Windows::Forms::Label());
					 this->lblParamID = (gcnew System::Windows::Forms::Label());
					 this->cbox_ParamDef = (gcnew System::Windows::Forms::ComboBox());
					 this->cbox_ParamID = (gcnew System::Windows::Forms::ComboBox());
					 this->btn_paramSet = (gcnew System::Windows::Forms::Button());
					 this->picbox_LCD = (gcnew System::Windows::Forms::PictureBox());
					 this->picbox_LOUT = (gcnew System::Windows::Forms::PictureBox());
					 this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
					 this->panel_LCD = (gcnew System::Windows::Forms::Panel());
					 this->picbox_RectLCD = (gcnew System::Windows::Forms::PictureBox());
					 this->panel_LOUT = (gcnew System::Windows::Forms::Panel());
					 this->btn_LogPlay = (gcnew System::Windows::Forms::Button());
					 this->LogPlayer = (gcnew System::Windows::Forms::GroupBox());
					 this->btn_CmdLine = (gcnew System::Windows::Forms::Button());
					 this->btn_ReadLog = (gcnew System::Windows::Forms::Button());
					 this->btn_SaveLog = (gcnew System::Windows::Forms::Button());
					 this->btn_ConsoleClear = (gcnew System::Windows::Forms::Button());
					 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
					 this->btn_variety8 = (gcnew System::Windows::Forms::Button());
					 this->btn_variety6 = (gcnew System::Windows::Forms::Button());
					 this->btn_variety7 = (gcnew System::Windows::Forms::Button());
					 this->btn_Variety5 = (gcnew System::Windows::Forms::Button());
					 this->grpbx_shrcut = (gcnew System::Windows::Forms::GroupBox());
					 this->btn_sc_Clip = (gcnew System::Windows::Forms::Button());
					 this->btn_sc_Play = (gcnew System::Windows::Forms::Button());
					 this->grpbx_refInfo = (gcnew System::Windows::Forms::GroupBox());
					 this->btn_MemInfo = (gcnew System::Windows::Forms::Button());
					 this->btn_ClsInfo = (gcnew System::Windows::Forms::Button());
					 this->btn_Setting = (gcnew System::Windows::Forms::Button());
					 this->tab_Ctrl_Sim = (gcnew System::Windows::Forms::TabControl());
					 this->Controller = (gcnew System::Windows::Forms::TabPage());
					 this->WidgetExplorer = (gcnew System::Windows::Forms::TabPage());
					 this->split_Cont_Widget_Exp = (gcnew System::Windows::Forms::SplitContainer());
					 this->split_Ctnr_Exp = (gcnew System::Windows::Forms::SplitContainer());
					 this->treeV_Widget = (gcnew System::Windows::Forms::TreeView());
					 this->listV_Widget = (gcnew System::Windows::Forms::ListView());
					 this->ラベル = (gcnew System::Windows::Forms::ColumnHeader());
					 this->データ = (gcnew System::Windows::Forms::ColumnHeader());
					 this->treeV_text = (gcnew System::Windows::Forms::Label());
					 this->CommandCtrl = (gcnew System::Windows::Forms::TabPage());
					 this->Support = (gcnew System::Windows::Forms::TabPage());
					 this->gBox_SimSetting = (gcnew System::Windows::Forms::GroupBox());
					 this->chk_Box_Logo = (gcnew System::Windows::Forms::CheckBox());
					 this->gBox_Save = (gcnew System::Windows::Forms::GroupBox());
					 this->gBox_pictSave = (gcnew System::Windows::Forms::GroupBox());
					 this->radbtnSave_BMP = (gcnew System::Windows::Forms::RadioButton());
					 this->radbtnSave_JPG = (gcnew System::Windows::Forms::RadioButton());
					 this->btnSave_LOUT = (gcnew System::Windows::Forms::Button());
					 this->btnSave_LCD = (gcnew System::Windows::Forms::Button());
					 this->gBoxOutLine->SuspendLayout();
					 this->gBoxDeck->SuspendLayout();
					 this->grpbox_Dial->SuspendLayout();
					 this->grpbox_keysrc->SuspendLayout();
					 this->gbox_WindowControll->SuspendLayout();
					 this->gBox_AplParam->SuspendLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picbox_LCD))->BeginInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picbox_LOUT))->BeginInit();
					 this->flowLayoutPanel1->SuspendLayout();
					 this->panel_LCD->SuspendLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picbox_RectLCD))->BeginInit();
					 this->panel_LOUT->SuspendLayout();
					 this->LogPlayer->SuspendLayout();
					 this->groupBox2->SuspendLayout();
					 this->grpbx_shrcut->SuspendLayout();
					 this->grpbx_refInfo->SuspendLayout();
					 this->tab_Ctrl_Sim->SuspendLayout();
					 this->Controller->SuspendLayout();
					 this->WidgetExplorer->SuspendLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->split_Cont_Widget_Exp))->BeginInit();
					 this->split_Cont_Widget_Exp->Panel1->SuspendLayout();
					 this->split_Cont_Widget_Exp->Panel2->SuspendLayout();
					 this->split_Cont_Widget_Exp->SuspendLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->split_Ctnr_Exp))->BeginInit();
					 this->split_Ctnr_Exp->Panel1->SuspendLayout();
					 this->split_Ctnr_Exp->Panel2->SuspendLayout();
					 this->split_Ctnr_Exp->SuspendLayout();
					 this->CommandCtrl->SuspendLayout();
					 this->Support->SuspendLayout();
					 this->gBox_SimSetting->SuspendLayout();
					 this->gBox_Save->SuspendLayout();
					 this->gBox_pictSave->SuspendLayout();
					 this->SuspendLayout();
					 // 
					 // button_up
					 // 
					 this->button_up->Location = System::Drawing::Point(77, 45);
					 this->button_up->Name = L"button_up";
					 this->button_up->Size = System::Drawing::Size(60, 23);
					 this->button_up->TabIndex = 4;
					 this->button_up->Text = L"↑";
					 this->button_up->UseVisualStyleBackColor = true;
					 this->button_up->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_up_MouseDown);
					 this->button_up->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_up_MouseUp);
					 // 
					 // button_left
					 // 
					 this->button_left->Location = System::Drawing::Point(11, 74);
					 this->button_left->Name = L"button_left";
					 this->button_left->Size = System::Drawing::Size(60, 23);
					 this->button_left->TabIndex = 5;
					 this->button_left->Text = L"←";
					 this->button_left->UseVisualStyleBackColor = true;
					 this->button_left->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_left_MouseDown);
					 this->button_left->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_left_MouseUp);
					 // 
					 // button_right
					 // 
					 this->button_right->Location = System::Drawing::Point(143, 74);
					 this->button_right->Name = L"button_right";
					 this->button_right->Size = System::Drawing::Size(60, 23);
					 this->button_right->TabIndex = 7;
					 this->button_right->Text = L"→";
					 this->button_right->UseVisualStyleBackColor = true;
					 this->button_right->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_right_MouseDown);
					 this->button_right->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_right_MouseUp);
					 // 
					 // button_down
					 // 
					 this->button_down->Location = System::Drawing::Point(77, 103);
					 this->button_down->Name = L"button_down";
					 this->button_down->Size = System::Drawing::Size(60, 23);
					 this->button_down->TabIndex = 6;
					 this->button_down->Text = L"↓";
					 this->button_down->UseVisualStyleBackColor = true;
					 this->button_down->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_down_MouseDown);
					 this->button_down->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_down_MouseUp);
					 // 
					 // button_enter
					 // 
					 this->button_enter->Location = System::Drawing::Point(77, 74);
					 this->button_enter->Name = L"button_enter";
					 this->button_enter->Size = System::Drawing::Size(60, 23);
					 this->button_enter->TabIndex = 3;
					 this->button_enter->Text = L"Enter";
					 this->button_enter->UseVisualStyleBackColor = true;
					 this->button_enter->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_enter_MouseDown);
					 this->button_enter->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_enter_MouseUp);
					 // 
					 // btn_ChangeWindow
					 // 
					 this->btn_ChangeWindow->Location = System::Drawing::Point(220, 39);
					 this->btn_ChangeWindow->Name = L"btn_ChangeWindow";
					 this->btn_ChangeWindow->Size = System::Drawing::Size(60, 23);
					 this->btn_ChangeWindow->TabIndex = 4;
					 this->btn_ChangeWindow->Text = L"change";
					 this->btn_ChangeWindow->UseVisualStyleBackColor = true;
					 this->btn_ChangeWindow->Click += gcnew System::EventHandler(this, &MovieForm::btn_ChangeWindow_Click);
					 // 
					 // btn_PopupWindow
					 // 
					 this->btn_PopupWindow->Location = System::Drawing::Point(220, 63);
					 this->btn_PopupWindow->Name = L"btn_PopupWindow";
					 this->btn_PopupWindow->Size = System::Drawing::Size(60, 23);
					 this->btn_PopupWindow->TabIndex = 5;
					 this->btn_PopupWindow->Text = L"popup";
					 this->btn_PopupWindow->UseVisualStyleBackColor = true;
					 this->btn_PopupWindow->Click += gcnew System::EventHandler(this, &MovieForm::btn_PopupWindow_Click);
					 // 
					 // btn_ReturnWindow
					 // 
					 this->btn_ReturnWindow->Location = System::Drawing::Point(282, 39);
					 this->btn_ReturnWindow->Name = L"btn_ReturnWindow";
					 this->btn_ReturnWindow->Size = System::Drawing::Size(60, 23);
					 this->btn_ReturnWindow->TabIndex = 6;
					 this->btn_ReturnWindow->Text = L"return";
					 this->btn_ReturnWindow->UseVisualStyleBackColor = true;
					 this->btn_ReturnWindow->Click += gcnew System::EventHandler(this, &MovieForm::btn_ReturnWindow_Click);
					 // 
					 // btn_CloseWindow
					 // 
					 this->btn_CloseWindow->Location = System::Drawing::Point(282, 63);
					 this->btn_CloseWindow->Name = L"btn_CloseWindow";
					 this->btn_CloseWindow->Size = System::Drawing::Size(60, 23);
					 this->btn_CloseWindow->TabIndex = 7;
					 this->btn_CloseWindow->Text = L"close";
					 this->btn_CloseWindow->UseVisualStyleBackColor = true;
					 this->btn_CloseWindow->Click += gcnew System::EventHandler(this, &MovieForm::btn_CloseWindow_Click);
					 // 
					 // lblScreen
					 // 
					 this->lblScreen->AutoSize = true;
					 this->lblScreen->Location = System::Drawing::Point(7, 89);
					 this->lblScreen->Name = L"lblScreen";
					 this->lblScreen->Size = System::Drawing::Size(40, 12);
					 this->lblScreen->TabIndex = 0;
					 this->lblScreen->Text = L"Screen";
					 // 
					 // lblWindowID
					 // 
					 this->lblWindowID->AutoSize = true;
					 this->lblWindowID->Location = System::Drawing::Point(4, 63);
					 this->lblWindowID->Name = L"lblWindowID";
					 this->lblWindowID->Size = System::Drawing::Size(54, 12);
					 this->lblWindowID->TabIndex = 0;
					 this->lblWindowID->Text = L"WindowID";
					 // 
					 // cbox_WindowName
					 // 
					 this->cbox_WindowName->DropDownHeight = 500;
					 this->cbox_WindowName->DropDownWidth = 300;
					 this->cbox_WindowName->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							 static_cast<System::Byte>(128)));
					 this->cbox_WindowName->FormattingEnabled = true;
					 this->cbox_WindowName->IntegralHeight = false;
					 this->cbox_WindowName->Location = System::Drawing::Point(67, 63);
					 this->cbox_WindowName->Name = L"cbox_WindowName";
					 this->cbox_WindowName->Size = System::Drawing::Size(121, 19);
					 this->cbox_WindowName->TabIndex = 0;
					 this->cbox_WindowName->TextUpdate += gcnew System::EventHandler(this, &MovieForm::cbox_WindowName_TextUpdate);
					 // 
					 // cbox_ScreenType
					 // 
					 this->cbox_ScreenType->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							 static_cast<System::Byte>(128)));
					 this->cbox_ScreenType->FormattingEnabled = true;
					 this->cbox_ScreenType->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"LCD", L"LOUT", L"ALL" });
					 this->cbox_ScreenType->Location = System::Drawing::Point(67, 86);
					 this->cbox_ScreenType->Name = L"cbox_ScreenType";
					 this->cbox_ScreenType->Size = System::Drawing::Size(79, 17);
					 this->cbox_ScreenType->TabIndex = 1;
					 // 
					 // btn_DrawRect
					 // 
					 this->btn_DrawRect->Location = System::Drawing::Point(17, 43);
					 this->btn_DrawRect->Name = L"btn_DrawRect";
					 this->btn_DrawRect->Size = System::Drawing::Size(64, 23);
					 this->btn_DrawRect->TabIndex = 5;
					 this->btn_DrawRect->Text = L"DrawRect";
					 this->btn_DrawRect->UseVisualStyleBackColor = true;
					 this->btn_DrawRect->Click += gcnew System::EventHandler(this, &MovieForm::btn_DrawRect_Click);
					 // 
					 // tbox_Rect_x
					 // 
					 this->tbox_Rect_x->Location = System::Drawing::Point(18, 116);
					 this->tbox_Rect_x->MaxLength = 3;
					 this->tbox_Rect_x->Name = L"tbox_Rect_x";
					 this->tbox_Rect_x->Size = System::Drawing::Size(40, 19);
					 this->tbox_Rect_x->TabIndex = 0;
					 this->tbox_Rect_x->Text = L"0";
					 // 
					 // tbox_Rect_y
					 // 
					 this->tbox_Rect_y->Location = System::Drawing::Point(64, 116);
					 this->tbox_Rect_y->MaxLength = 3;
					 this->tbox_Rect_y->Name = L"tbox_Rect_y";
					 this->tbox_Rect_y->Size = System::Drawing::Size(40, 19);
					 this->tbox_Rect_y->TabIndex = 1;
					 this->tbox_Rect_y->Text = L"0";
					 // 
					 // tbox_Rect_width
					 // 
					 this->tbox_Rect_width->Location = System::Drawing::Point(110, 116);
					 this->tbox_Rect_width->MaxLength = 3;
					 this->tbox_Rect_width->Name = L"tbox_Rect_width";
					 this->tbox_Rect_width->Size = System::Drawing::Size(40, 19);
					 this->tbox_Rect_width->TabIndex = 2;
					 this->tbox_Rect_width->Text = L"0";
					 // 
					 // tbox_Rect_height
					 // 
					 this->tbox_Rect_height->Location = System::Drawing::Point(156, 116);
					 this->tbox_Rect_height->MaxLength = 3;
					 this->tbox_Rect_height->Name = L"tbox_Rect_height";
					 this->tbox_Rect_height->Size = System::Drawing::Size(40, 19);
					 this->tbox_Rect_height->TabIndex = 3;
					 this->tbox_Rect_height->Text = L"0";
					 // 
					 // label1
					 // 
					 this->label1->AutoSize = true;
					 this->label1->Location = System::Drawing::Point(18, 98);
					 this->label1->Name = L"label1";
					 this->label1->Size = System::Drawing::Size(175, 12);
					 this->label1->TabIndex = 0;
					 this->label1->Text = L"    x          y       width    height";
					 // 
					 // gBoxOutLine
					 // 
					 this->gBoxOutLine->Controls->Add(this->btn_DrawDelete);
					 this->gBoxOutLine->Controls->Add(this->btn_ShowOutline);
					 this->gBoxOutLine->Controls->Add(this->label1);
					 this->gBoxOutLine->Controls->Add(this->btn_DrawRect);
					 this->gBoxOutLine->Controls->Add(this->tbox_Rect_height);
					 this->gBoxOutLine->Controls->Add(this->tbox_Rect_x);
					 this->gBoxOutLine->Controls->Add(this->tbox_Rect_width);
					 this->gBoxOutLine->Controls->Add(this->tbox_Rect_y);
					 this->gBoxOutLine->Location = System::Drawing::Point(3, 5);
					 this->gBoxOutLine->Name = L"gBoxOutLine";
					 this->gBoxOutLine->Size = System::Drawing::Size(271, 150);
					 this->gBoxOutLine->TabIndex = 7;
					 this->gBoxOutLine->TabStop = false;
					 this->gBoxOutLine->Text = L"OutLine解析";
					 // 
					 // btn_DrawDelete
					 // 
					 this->btn_DrawDelete->Location = System::Drawing::Point(17, 68);
					 this->btn_DrawDelete->Name = L"btn_DrawDelete";
					 this->btn_DrawDelete->Size = System::Drawing::Size(64, 23);
					 this->btn_DrawDelete->TabIndex = 6;
					 this->btn_DrawDelete->Text = L"ClearRect";
					 this->btn_DrawDelete->UseVisualStyleBackColor = true;
					 this->btn_DrawDelete->Click += gcnew System::EventHandler(this, &MovieForm::btn_DrawReset_Click);
					 // 
					 // btn_ShowOutline
					 // 
					 this->btn_ShowOutline->Location = System::Drawing::Point(17, 18);
					 this->btn_ShowOutline->Name = L"btn_ShowOutline";
					 this->btn_ShowOutline->Size = System::Drawing::Size(96, 23);
					 this->btn_ShowOutline->TabIndex = 2;
					 this->btn_ShowOutline->Text = L"Outline読み込み";
					 this->btn_ShowOutline->UseVisualStyleBackColor = true;
					 this->btn_ShowOutline->Click += gcnew System::EventHandler(this, &MovieForm::btn_ShowOutline_Click);
					 // 
					 // btn_SwapWindow
					 // 
					 this->btn_SwapWindow->Location = System::Drawing::Point(343, 39);
					 this->btn_SwapWindow->Name = L"btn_SwapWindow";
					 this->btn_SwapWindow->Size = System::Drawing::Size(60, 23);
					 this->btn_SwapWindow->TabIndex = 8;
					 this->btn_SwapWindow->Text = L"swap";
					 this->btn_SwapWindow->UseVisualStyleBackColor = true;
					 this->btn_SwapWindow->Click += gcnew System::EventHandler(this, &MovieForm::btn_SwapWindow_Click);
					 // 
					 // gBoxDeck
					 // 
					 this->gBoxDeck->Controls->Add(this->button_Info_Mode);
					 this->gBoxDeck->Controls->Add(this->grpbox_Dial);
					 this->gBoxDeck->Controls->Add(this->grpbox_keysrc);
					 this->gBoxDeck->Controls->Add(this->btn_User9);
					 this->gBoxDeck->Controls->Add(this->btn_User8);
					 this->gBoxDeck->Controls->Add(this->chk_Shift);
					 this->gBoxDeck->Controls->Add(this->btn_User7);
					 this->gBoxDeck->Controls->Add(this->chkLockSw);
					 this->gBoxDeck->Controls->Add(this->btn_User6);
					 this->gBoxDeck->Controls->Add(this->btn_User5);
					 this->gBoxDeck->Controls->Add(this->btn_User4);
					 this->gBoxDeck->Controls->Add(this->buttonExit);
					 this->gBoxDeck->Controls->Add(this->btn_Menu);
					 this->gBoxDeck->Controls->Add(this->btn_Thumb);
					 this->gBoxDeck->Controls->Add(this->btn_User3);
					 this->gBoxDeck->Controls->Add(this->btn_Home);
					 this->gBoxDeck->Controls->Add(this->btn_User2);
					 this->gBoxDeck->Controls->Add(this->btn_User1);
					 this->gBoxDeck->Controls->Add(this->button_up);
					 this->gBoxDeck->Controls->Add(this->button_enter);
					 this->gBoxDeck->Controls->Add(this->button_right);
					 this->gBoxDeck->Controls->Add(this->button_left);
					 this->gBoxDeck->Controls->Add(this->button_down);
					 this->gBoxDeck->Location = System::Drawing::Point(3, 117);
					 this->gBoxDeck->Name = L"gBoxDeck";
					 this->gBoxDeck->Size = System::Drawing::Size(493, 131);
					 this->gBoxDeck->TabIndex = 5;
					 this->gBoxDeck->TabStop = false;
					 this->gBoxDeck->Text = L"KeyController";
					 // 
					 // button_Info_Mode
					 // 
					 this->button_Info_Mode->Location = System::Drawing::Point(11, 103);
					 this->button_Info_Mode->Name = L"button_Info_Mode";
					 this->button_Info_Mode->Size = System::Drawing::Size(60, 23);
					 this->button_Info_Mode->TabIndex = 22;
					 this->button_Info_Mode->Text = L"MODE";
					 this->button_Info_Mode->UseVisualStyleBackColor = true;
					 this->button_Info_Mode->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_Info_Mode_MouseDown);
					 this->button_Info_Mode->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::button_Info_Mode_MouseUp);
					 // 
					 // grpbox_Dial
					 // 
					 this->grpbox_Dial->Controls->Add(this->chk_Dial_Enter);
					 this->grpbox_Dial->Controls->Add(this->btn_dial_minus);
					 this->grpbox_Dial->Controls->Add(this->btn_dial_plus);
					 this->grpbox_Dial->Location = System::Drawing::Point(219, 18);
					 this->grpbox_Dial->Name = L"grpbox_Dial";
					 this->grpbox_Dial->Size = System::Drawing::Size(70, 112);
					 this->grpbox_Dial->TabIndex = 9;
					 this->grpbox_Dial->TabStop = false;
					 this->grpbox_Dial->Text = L"Dial";
					 // 
					 // chk_Dial_Enter
					 // 
					 this->chk_Dial_Enter->Appearance = System::Windows::Forms::Appearance::Button;
					 this->chk_Dial_Enter->BackColor = System::Drawing::SystemColors::WindowFrame;
					 this->chk_Dial_Enter->ForeColor = System::Drawing::SystemColors::HighlightText;
					 this->chk_Dial_Enter->Location = System::Drawing::Point(4, 47);
					 this->chk_Dial_Enter->Name = L"chk_Dial_Enter";
					 this->chk_Dial_Enter->Size = System::Drawing::Size(60, 23);
					 this->chk_Dial_Enter->TabIndex = 10;
					 this->chk_Dial_Enter->Text = L"Enter";
					 this->chk_Dial_Enter->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 this->chk_Dial_Enter->UseVisualStyleBackColor = false;
					 this->chk_Dial_Enter->CheckedChanged += gcnew System::EventHandler(this, &MovieForm::chk_Dial_Enter_CheckedChanged);
					 // 
					 // btn_dial_minus
					 // 
					 this->btn_dial_minus->BackColor = System::Drawing::SystemColors::WindowFrame;
					 this->btn_dial_minus->ForeColor = System::Drawing::SystemColors::HighlightText;
					 this->btn_dial_minus->Location = System::Drawing::Point(4, 76);
					 this->btn_dial_minus->Name = L"btn_dial_minus";
					 this->btn_dial_minus->Size = System::Drawing::Size(60, 23);
					 this->btn_dial_minus->TabIndex = 3;
					 this->btn_dial_minus->Text = L"-";
					 this->btn_dial_minus->UseVisualStyleBackColor = false;
					 this->btn_dial_minus->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_dial_minus_MouseDown);
					 this->btn_dial_minus->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_dial_minus_MouseUp);
					 // 
					 // btn_dial_plus
					 // 
					 this->btn_dial_plus->BackColor = System::Drawing::SystemColors::WindowFrame;
					 this->btn_dial_plus->ForeColor = System::Drawing::SystemColors::HighlightText;
					 this->btn_dial_plus->Location = System::Drawing::Point(4, 18);
					 this->btn_dial_plus->Name = L"btn_dial_plus";
					 this->btn_dial_plus->Size = System::Drawing::Size(60, 23);
					 this->btn_dial_plus->TabIndex = 1;
					 this->btn_dial_plus->Text = L"+";
					 this->btn_dial_plus->UseVisualStyleBackColor = false;
					 this->btn_dial_plus->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_dial_plus_MouseDown);
					 this->btn_dial_plus->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_dial_plus_MouseUp);
					 // 
					 // grpbox_keysrc
					 // 
					 this->grpbox_keysrc->Controls->Add(this->rdbtn_Rop);
					 this->grpbox_keysrc->Controls->Add(this->radbtn_Grip);
					 this->grpbox_keysrc->Controls->Add(this->radbtn_Deck);
					 this->grpbox_keysrc->Location = System::Drawing::Point(60, 13);
					 this->grpbox_keysrc->Name = L"grpbox_keysrc";
					 this->grpbox_keysrc->Size = System::Drawing::Size(159, 30);
					 this->grpbox_keysrc->TabIndex = 2;
					 this->grpbox_keysrc->TabStop = false;
					 this->grpbox_keysrc->Text = L"KeySource";
					 // 
					 // rdbtn_Rop
					 // 
					 this->rdbtn_Rop->AutoSize = true;
					 this->rdbtn_Rop->Location = System::Drawing::Point(61, 10);
					 this->rdbtn_Rop->Name = L"rdbtn_Rop";
					 this->rdbtn_Rop->Size = System::Drawing::Size(43, 16);
					 this->rdbtn_Rop->TabIndex = 1;
					 this->rdbtn_Rop->TabStop = true;
					 this->rdbtn_Rop->Text = L"Rop";
					 this->rdbtn_Rop->UseVisualStyleBackColor = true;
					 // 
					 // radbtn_Grip
					 // 
					 this->radbtn_Grip->AutoSize = true;
					 this->radbtn_Grip->Location = System::Drawing::Point(109, 10);
					 this->radbtn_Grip->Name = L"radbtn_Grip";
					 this->radbtn_Grip->Size = System::Drawing::Size(44, 16);
					 this->radbtn_Grip->TabIndex = 2;
					 this->radbtn_Grip->TabStop = true;
					 this->radbtn_Grip->Text = L"Grip";
					 this->radbtn_Grip->UseVisualStyleBackColor = true;
					 // 
					 // radbtn_Deck
					 // 
					 this->radbtn_Deck->AutoSize = true;
					 this->radbtn_Deck->Checked = true;
					 this->radbtn_Deck->Location = System::Drawing::Point(6, 10);
					 this->radbtn_Deck->Name = L"radbtn_Deck";
					 this->radbtn_Deck->Size = System::Drawing::Size(49, 16);
					 this->radbtn_Deck->TabIndex = 0;
					 this->radbtn_Deck->TabStop = true;
					 this->radbtn_Deck->Text = L"Deck";
					 this->radbtn_Deck->UseVisualStyleBackColor = true;
					 // 
					 // btn_User9
					 // 
					 this->btn_User9->Location = System::Drawing::Point(428, 100);
					 this->btn_User9->Name = L"btn_User9";
					 this->btn_User9->Size = System::Drawing::Size(60, 23);
					 this->btn_User9->TabIndex = 21;
					 this->btn_User9->Text = L"USER9";
					 this->btn_User9->UseVisualStyleBackColor = true;
					 this->btn_User9->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User9_MouseDown);
					 this->btn_User9->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User9_MouseUp);
					 // 
					 // btn_User8
					 // 
					 this->btn_User8->Location = System::Drawing::Point(362, 100);
					 this->btn_User8->Name = L"btn_User8";
					 this->btn_User8->Size = System::Drawing::Size(60, 23);
					 this->btn_User8->TabIndex = 17;
					 this->btn_User8->Text = L"USER8";
					 this->btn_User8->UseVisualStyleBackColor = true;
					 this->btn_User8->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User8_MouseDown);
					 this->btn_User8->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User8_MouseUp);
					 // 
					 // chk_Shift
					 // 
					 this->chk_Shift->AutoSize = true;
					 this->chk_Shift->Location = System::Drawing::Point(6, 36);
					 this->chk_Shift->Name = L"chk_Shift";
					 this->chk_Shift->Size = System::Drawing::Size(48, 16);
					 this->chk_Shift->TabIndex = 1;
					 this->chk_Shift->Text = L"Shift";
					 this->chk_Shift->UseVisualStyleBackColor = true;
					 // 
					 // btn_User7
					 // 
					 this->btn_User7->Location = System::Drawing::Point(296, 100);
					 this->btn_User7->Name = L"btn_User7";
					 this->btn_User7->Size = System::Drawing::Size(60, 23);
					 this->btn_User7->TabIndex = 13;
					 this->btn_User7->Text = L"USER7";
					 this->btn_User7->UseVisualStyleBackColor = true;
					 this->btn_User7->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User7_MouseDown);
					 this->btn_User7->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User7_MouseUp);
					 // 
					 // chkLockSw
					 // 
					 this->chkLockSw->AutoSize = true;
					 this->chkLockSw->Location = System::Drawing::Point(6, 18);
					 this->chkLockSw->Name = L"chkLockSw";
					 this->chkLockSw->Size = System::Drawing::Size(48, 16);
					 this->chkLockSw->TabIndex = 0;
					 this->chkLockSw->Text = L"Lock";
					 this->chkLockSw->UseVisualStyleBackColor = true;
					 this->chkLockSw->CheckedChanged += gcnew System::EventHandler(this, &MovieForm::chkLockSw_CheckedChanged);
					 // 
					 // btn_User6
					 // 
					 this->btn_User6->Location = System::Drawing::Point(362, 71);
					 this->btn_User6->Name = L"btn_User6";
					 this->btn_User6->Size = System::Drawing::Size(60, 23);
					 this->btn_User6->TabIndex = 16;
					 this->btn_User6->Text = L"USER6";
					 this->btn_User6->UseVisualStyleBackColor = true;
					 this->btn_User6->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User6_MouseDown);
					 this->btn_User6->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User6_MouseUp);
					 // 
					 // btn_User5
					 // 
					 this->btn_User5->Location = System::Drawing::Point(296, 71);
					 this->btn_User5->Name = L"btn_User5";
					 this->btn_User5->Size = System::Drawing::Size(60, 23);
					 this->btn_User5->TabIndex = 12;
					 this->btn_User5->Text = L"USER5";
					 this->btn_User5->UseVisualStyleBackColor = true;
					 this->btn_User5->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User5_MouseDown);
					 this->btn_User5->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User5_MouseUp);
					 // 
					 // btn_User4
					 // 
					 this->btn_User4->Location = System::Drawing::Point(362, 42);
					 this->btn_User4->Name = L"btn_User4";
					 this->btn_User4->Size = System::Drawing::Size(60, 23);
					 this->btn_User4->TabIndex = 15;
					 this->btn_User4->Text = L"USER4";
					 this->btn_User4->UseVisualStyleBackColor = true;
					 this->btn_User4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User4_MouseDown);
					 this->btn_User4->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User4_MouseUp);
					 // 
					 // buttonExit
					 // 
					 this->buttonExit->Location = System::Drawing::Point(143, 103);
					 this->buttonExit->Name = L"buttonExit";
					 this->buttonExit->Size = System::Drawing::Size(60, 23);
					 this->buttonExit->TabIndex = 8;
					 this->buttonExit->Text = L"EXIT";
					 this->buttonExit->UseVisualStyleBackColor = true;
					 this->buttonExit->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::buttonExit_MouseDown);
					 this->buttonExit->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::buttonExit_MouseUp);
					 // 
					 // btn_Menu
					 // 
					 this->btn_Menu->Location = System::Drawing::Point(428, 13);
					 this->btn_Menu->Name = L"btn_Menu";
					 this->btn_Menu->Size = System::Drawing::Size(60, 23);
					 this->btn_Menu->TabIndex = 18;
					 this->btn_Menu->Text = L"MENU";
					 this->btn_Menu->UseVisualStyleBackColor = true;
					 this->btn_Menu->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_Menu_MouseDown);
					 this->btn_Menu->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_Menu_MouseUp);
					 // 
					 // btn_Thumb
					 // 
					 this->btn_Thumb->Location = System::Drawing::Point(428, 71);
					 this->btn_Thumb->Name = L"btn_Thumb";
					 this->btn_Thumb->Size = System::Drawing::Size(60, 23);
					 this->btn_Thumb->TabIndex = 20;
					 this->btn_Thumb->Text = L"Thumb.";
					 this->btn_Thumb->UseVisualStyleBackColor = true;
					 this->btn_Thumb->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_Thumb_MouseDown);
					 this->btn_Thumb->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_Thumb_MouseUp);
					 // 
					 // btn_User3
					 // 
					 this->btn_User3->Location = System::Drawing::Point(296, 42);
					 this->btn_User3->Name = L"btn_User3";
					 this->btn_User3->Size = System::Drawing::Size(60, 23);
					 this->btn_User3->TabIndex = 11;
					 this->btn_User3->Text = L"USER3";
					 this->btn_User3->UseVisualStyleBackColor = true;
					 this->btn_User3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User3_MouseDown);
					 this->btn_User3->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User3_MouseUp);
					 // 
					 // btn_Home
					 // 
					 this->btn_Home->Location = System::Drawing::Point(428, 42);
					 this->btn_Home->Name = L"btn_Home";
					 this->btn_Home->Size = System::Drawing::Size(60, 23);
					 this->btn_Home->TabIndex = 19;
					 this->btn_Home->Text = L"HOME";
					 this->btn_Home->UseVisualStyleBackColor = true;
					 this->btn_Home->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_Home_MouseDown);
					 this->btn_Home->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_Home_MouseUp);
					 // 
					 // btn_User2
					 // 
					 this->btn_User2->Location = System::Drawing::Point(362, 13);
					 this->btn_User2->Name = L"btn_User2";
					 this->btn_User2->Size = System::Drawing::Size(60, 23);
					 this->btn_User2->TabIndex = 14;
					 this->btn_User2->Text = L"USER2";
					 this->btn_User2->UseVisualStyleBackColor = true;
					 this->btn_User2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User2_MouseDown);
					 this->btn_User2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User2_MouseUp);
					 // 
					 // btn_User1
					 // 
					 this->btn_User1->Location = System::Drawing::Point(296, 13);
					 this->btn_User1->Name = L"btn_User1";
					 this->btn_User1->Size = System::Drawing::Size(60, 23);
					 this->btn_User1->TabIndex = 10;
					 this->btn_User1->Text = L"USER1";
					 this->btn_User1->UseVisualStyleBackColor = true;
					 this->btn_User1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User1_MouseDown);
					 this->btn_User1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::btn_User1_MouseUp);
					 // 
					 // btn_variety4
					 // 
					 this->btn_variety4->Location = System::Drawing::Point(51, 38);
					 this->btn_variety4->Name = L"btn_variety4";
					 this->btn_variety4->Size = System::Drawing::Size(39, 23);
					 this->btn_variety4->TabIndex = 3;
					 this->btn_variety4->Text = L"Var4";
					 this->btn_variety4->UseVisualStyleBackColor = true;
					 this->btn_variety4->Click += gcnew System::EventHandler(this, &MovieForm::btn_variety4_Click);
					 // 
					 // btn_variety3
					 // 
					 this->btn_variety3->Location = System::Drawing::Point(51, 12);
					 this->btn_variety3->Name = L"btn_variety3";
					 this->btn_variety3->Size = System::Drawing::Size(39, 23);
					 this->btn_variety3->TabIndex = 2;
					 this->btn_variety3->Text = L"Var3";
					 this->btn_variety3->UseVisualStyleBackColor = true;
					 this->btn_variety3->Click += gcnew System::EventHandler(this, &MovieForm::btn_variety3_Click);
					 // 
					 // btn_variety2
					 // 
					 this->btn_variety2->Location = System::Drawing::Point(6, 38);
					 this->btn_variety2->Name = L"btn_variety2";
					 this->btn_variety2->Size = System::Drawing::Size(39, 23);
					 this->btn_variety2->TabIndex = 1;
					 this->btn_variety2->Text = L"Var2";
					 this->btn_variety2->UseVisualStyleBackColor = true;
					 this->btn_variety2->Click += gcnew System::EventHandler(this, &MovieForm::btn_variety2_Click);
					 // 
					 // btn_variety
					 // 
					 this->btn_variety->Location = System::Drawing::Point(6, 12);
					 this->btn_variety->Name = L"btn_variety";
					 this->btn_variety->Size = System::Drawing::Size(39, 23);
					 this->btn_variety->TabIndex = 0;
					 this->btn_variety->Text = L"Var1";
					 this->btn_variety->UseVisualStyleBackColor = true;
					 this->btn_variety->Click += gcnew System::EventHandler(this, &MovieForm::btn_variety_Click);
					 // 
					 // label2
					 // 
					 this->label2->AutoSize = true;
					 this->label2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 9));
					 this->label2->Location = System::Drawing::Point(114, 20);
					 this->label2->Name = L"label2";
					 this->label2->Size = System::Drawing::Size(11, 12);
					 this->label2->TabIndex = 0;
					 this->label2->Text = L"x";
					 // 
					 // cbox_Scale
					 // 
					 this->cbox_Scale->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
					 this->cbox_Scale->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							 static_cast<System::Byte>(128)));
					 this->cbox_Scale->FormattingEnabled = true;
					 this->cbox_Scale->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"0.5", L"0.75", L"1.0", L"1.5", L"2.0" });
					 this->cbox_Scale->Location = System::Drawing::Point(131, 15);
					 this->cbox_Scale->Name = L"cbox_Scale";
					 this->cbox_Scale->Size = System::Drawing::Size(42, 17);
					 this->cbox_Scale->TabIndex = 2;
					 this->cbox_Scale->SelectedValueChanged += gcnew System::EventHandler(this, &MovieForm::cbox_Scale_SelectedValueChanged);
					 // 
					 // cbox_LOUT
					 // 
					 this->cbox_LOUT->Appearance = System::Windows::Forms::Appearance::Button;
					 this->cbox_LOUT->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							 static_cast<System::Byte>(128)));
					 this->cbox_LOUT->Location = System::Drawing::Point(61, 13);
					 this->cbox_LOUT->Name = L"cbox_LOUT";
					 this->cbox_LOUT->Size = System::Drawing::Size(48, 19);
					 this->cbox_LOUT->TabIndex = 1;
					 this->cbox_LOUT->Text = L"LOUT";
					 this->cbox_LOUT->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 this->cbox_LOUT->UseVisualStyleBackColor = true;
					 this->cbox_LOUT->CheckedChanged += gcnew System::EventHandler(this, &MovieForm::cbox_Disp_CheckedChanged);
					 // 
					 // cbox_LCD
					 // 
					 this->cbox_LCD->Appearance = System::Windows::Forms::Appearance::Button;
					 this->cbox_LCD->Checked = true;
					 this->cbox_LCD->CheckState = System::Windows::Forms::CheckState::Checked;
					 this->cbox_LCD->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							 static_cast<System::Byte>(128)));
					 this->cbox_LCD->Location = System::Drawing::Point(7, 13);
					 this->cbox_LCD->Name = L"cbox_LCD";
					 this->cbox_LCD->Size = System::Drawing::Size(48, 19);
					 this->cbox_LCD->TabIndex = 0;
					 this->cbox_LCD->Text = L"LCD";
					 this->cbox_LCD->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 this->cbox_LCD->UseVisualStyleBackColor = true;
					 this->cbox_LCD->CheckedChanged += gcnew System::EventHandler(this, &MovieForm::cbox_Disp_CheckedChanged);
					 // 
					 // gbox_WindowControll
					 // 
					 this->gbox_WindowControll->Controls->Add(this->chkbox_winid);
					 this->gbox_WindowControll->Controls->Add(this->label2);
					 this->gbox_WindowControll->Controls->Add(this->btn_PrevWind);
					 this->gbox_WindowControll->Controls->Add(this->cbox_Scale);
					 this->gbox_WindowControll->Controls->Add(this->btn_RemoveWindow);
					 this->gbox_WindowControll->Controls->Add(this->cbox_LOUT);
					 this->gbox_WindowControll->Controls->Add(this->cbox_LCD);
					 this->gbox_WindowControll->Controls->Add(this->btn_NextWind);
					 this->gbox_WindowControll->Controls->Add(this->btn_ChangeWindow);
					 this->gbox_WindowControll->Controls->Add(this->btn_ReturnWindow);
					 this->gbox_WindowControll->Controls->Add(this->btn_PopupWindow);
					 this->gbox_WindowControll->Controls->Add(this->btn_SwapWindow);
					 this->gbox_WindowControll->Controls->Add(this->cbox_ScreenType);
					 this->gbox_WindowControll->Controls->Add(this->btn_CloseWindow);
					 this->gbox_WindowControll->Controls->Add(this->lblScreen);
					 this->gbox_WindowControll->Controls->Add(this->lblWindowID);
					 this->gbox_WindowControll->Controls->Add(this->cbox_WindowName);
					 this->gbox_WindowControll->Location = System::Drawing::Point(3, 6);
					 this->gbox_WindowControll->Name = L"gbox_WindowControll";
					 this->gbox_WindowControll->Size = System::Drawing::Size(413, 105);
					 this->gbox_WindowControll->TabIndex = 2;
					 this->gbox_WindowControll->TabStop = false;
					 this->gbox_WindowControll->Text = L"WindowControl";
					 // 
					 // chkbox_winid
					 // 
					 this->chkbox_winid->AutoSize = true;
					 this->chkbox_winid->Location = System::Drawing::Point(7, 41);
					 this->chkbox_winid->Name = L"chkbox_winid";
					 this->chkbox_winid->Size = System::Drawing::Size(73, 16);
					 this->chkbox_winid->TabIndex = 2;
					 this->chkbox_winid->Text = L"WindowID";
					 this->chkbox_winid->UseVisualStyleBackColor = true;
					 // 
					 // btn_PrevWind
					 // 
					 this->btn_PrevWind->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							 static_cast<System::Byte>(128)));
					 this->btn_PrevWind->Location = System::Drawing::Point(220, 13);
					 this->btn_PrevWind->Name = L"btn_PrevWind";
					 this->btn_PrevWind->Size = System::Drawing::Size(60, 23);
					 this->btn_PrevWind->TabIndex = 10;
					 this->btn_PrevWind->Text = L"PrevWind";
					 this->btn_PrevWind->UseVisualStyleBackColor = true;
					 this->btn_PrevWind->Click += gcnew System::EventHandler(this, &MovieForm::btn_PrevWind_Click);
					 // 
					 // btn_RemoveWindow
					 // 
					 this->btn_RemoveWindow->Location = System::Drawing::Point(343, 63);
					 this->btn_RemoveWindow->Name = L"btn_RemoveWindow";
					 this->btn_RemoveWindow->Size = System::Drawing::Size(60, 23);
					 this->btn_RemoveWindow->TabIndex = 9;
					 this->btn_RemoveWindow->Text = L"remove";
					 this->btn_RemoveWindow->UseVisualStyleBackColor = true;
					 this->btn_RemoveWindow->Click += gcnew System::EventHandler(this, &MovieForm::btn_RemoveWindow_Click);
					 // 
					 // btn_NextWind
					 // 
					 this->btn_NextWind->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
							 static_cast<System::Byte>(128)));
					 this->btn_NextWind->Location = System::Drawing::Point(281, 13);
					 this->btn_NextWind->Name = L"btn_NextWind";
					 this->btn_NextWind->Size = System::Drawing::Size(60, 23);
					 this->btn_NextWind->TabIndex = 3;
					 this->btn_NextWind->Text = L"NextWind";
					 this->btn_NextWind->UseVisualStyleBackColor = true;
					 this->btn_NextWind->Click += gcnew System::EventHandler(this, &MovieForm::btn_NextWind_Click);
					 // 
					 // btn_sc_View
					 // 
					 this->btn_sc_View->Location = System::Drawing::Point(162, 13);
					 this->btn_sc_View->Name = L"btn_sc_View";
					 this->btn_sc_View->Size = System::Drawing::Size(70, 20);
					 this->btn_sc_View->TabIndex = 4;
					 this->btn_sc_View->Text = L"View";
					 this->btn_sc_View->UseVisualStyleBackColor = true;
					 this->btn_sc_View->Click += gcnew System::EventHandler(this, &MovieForm::btn_sc_View_Click);
					 // 
					 // btn_sc_Info
					 // 
					 this->btn_sc_Info->Location = System::Drawing::Point(84, 39);
					 this->btn_sc_Info->Name = L"btn_sc_Info";
					 this->btn_sc_Info->Size = System::Drawing::Size(70, 20);
					 this->btn_sc_Info->TabIndex = 3;
					 this->btn_sc_Info->Text = L"INFO";
					 this->btn_sc_Info->UseVisualStyleBackColor = true;
					 this->btn_sc_Info->Click += gcnew System::EventHandler(this, &MovieForm::btn_sc_Info_Click);
					 // 
					 // btn_sc_Thumb
					 // 
					 this->btn_sc_Thumb->Location = System::Drawing::Point(85, 13);
					 this->btn_sc_Thumb->Name = L"btn_sc_Thumb";
					 this->btn_sc_Thumb->Size = System::Drawing::Size(70, 20);
					 this->btn_sc_Thumb->TabIndex = 2;
					 this->btn_sc_Thumb->Text = L"THUMB";
					 this->btn_sc_Thumb->UseVisualStyleBackColor = true;
					 this->btn_sc_Thumb->Click += gcnew System::EventHandler(this, &MovieForm::btn_sc_Thumb_Click);
					 // 
					 // btn_sc_Home
					 // 
					 this->btn_sc_Home->Location = System::Drawing::Point(8, 39);
					 this->btn_sc_Home->Name = L"btn_sc_Home";
					 this->btn_sc_Home->Size = System::Drawing::Size(70, 20);
					 this->btn_sc_Home->TabIndex = 1;
					 this->btn_sc_Home->Text = L"HOME";
					 this->btn_sc_Home->UseVisualStyleBackColor = true;
					 this->btn_sc_Home->Click += gcnew System::EventHandler(this, &MovieForm::btn_sc_Home_Click);
					 // 
					 // btn_GetCurrent
					 // 
					 this->btn_GetCurrent->Location = System::Drawing::Point(8, 44);
					 this->btn_GetCurrent->Name = L"btn_GetCurrent";
					 this->btn_GetCurrent->Size = System::Drawing::Size(61, 23);
					 this->btn_GetCurrent->TabIndex = 1;
					 this->btn_GetCurrent->Text = L"GetCrnt";
					 this->btn_GetCurrent->UseVisualStyleBackColor = true;
					 this->btn_GetCurrent->Click += gcnew System::EventHandler(this, &MovieForm::btn_GetCurrent_Click);
					 // 
					 // btn_GetRoot
					 // 
					 this->btn_GetRoot->Location = System::Drawing::Point(8, 18);
					 this->btn_GetRoot->Name = L"btn_GetRoot";
					 this->btn_GetRoot->Size = System::Drawing::Size(61, 23);
					 this->btn_GetRoot->TabIndex = 0;
					 this->btn_GetRoot->Text = L"GetRoot";
					 this->btn_GetRoot->UseVisualStyleBackColor = true;
					 this->btn_GetRoot->Click += gcnew System::EventHandler(this, &MovieForm::btn_GetRoot_Click);
					 // 
					 // btn_sc_Menu
					 // 
					 this->btn_sc_Menu->Location = System::Drawing::Point(8, 13);
					 this->btn_sc_Menu->Name = L"btn_sc_Menu";
					 this->btn_sc_Menu->Size = System::Drawing::Size(70, 20);
					 this->btn_sc_Menu->TabIndex = 0;
					 this->btn_sc_Menu->Text = L"MENU";
					 this->btn_sc_Menu->UseVisualStyleBackColor = true;
					 this->btn_sc_Menu->Click += gcnew System::EventHandler(this, &MovieForm::btn_sc_Menu_Click);
					 // 
					 // gBox_AplParam
					 // 
					 this->gBox_AplParam->Controls->Add(this->tBox_ParamValue);
					 this->gBox_AplParam->Controls->Add(this->lblParamValue);
					 this->gBox_AplParam->Controls->Add(this->lblParamDef);
					 this->gBox_AplParam->Controls->Add(this->lblParamID);
					 this->gBox_AplParam->Controls->Add(this->cbox_ParamDef);
					 this->gBox_AplParam->Controls->Add(this->cbox_ParamID);
					 this->gBox_AplParam->Controls->Add(this->btn_paramSet);
					 this->gBox_AplParam->Location = System::Drawing::Point(3, 332);
					 this->gBox_AplParam->Name = L"gBox_AplParam";
					 this->gBox_AplParam->Size = System::Drawing::Size(311, 132);
					 this->gBox_AplParam->TabIndex = 6;
					 this->gBox_AplParam->TabStop = false;
					 this->gBox_AplParam->Text = L"AplParam";
					 // 
					 // tBox_ParamValue
					 // 
					 this->tBox_ParamValue->Location = System::Drawing::Point(6, 105);
					 this->tBox_ParamValue->MaxLength = 24;
					 this->tBox_ParamValue->Name = L"tBox_ParamValue";
					 this->tBox_ParamValue->Size = System::Drawing::Size(208, 19);
					 this->tBox_ParamValue->TabIndex = 2;
					 // 
					 // lblParamValue
					 // 
					 this->lblParamValue->AutoSize = true;
					 this->lblParamValue->Location = System::Drawing::Point(6, 90);
					 this->lblParamValue->Name = L"lblParamValue";
					 this->lblParamValue->Size = System::Drawing::Size(122, 12);
					 this->lblParamValue->TabIndex = 4;
					 this->lblParamValue->Text = L"Value(Num,文字,IPなど)";
					 // 
					 // lblParamDef
					 // 
					 this->lblParamDef->AutoSize = true;
					 this->lblParamDef->Location = System::Drawing::Point(4, 53);
					 this->lblParamDef->Name = L"lblParamDef";
					 this->lblParamDef->Size = System::Drawing::Size(58, 12);
					 this->lblParamDef->TabIndex = 2;
					 this->lblParamDef->Text = L"Def(enum)";
					 // 
					 // lblParamID
					 // 
					 this->lblParamID->AutoSize = true;
					 this->lblParamID->Location = System::Drawing::Point(4, 15);
					 this->lblParamID->Name = L"lblParamID";
					 this->lblParamID->Size = System::Drawing::Size(16, 12);
					 this->lblParamID->TabIndex = 0;
					 this->lblParamID->Text = L"ID";
					 // 
					 // cbox_ParamDef
					 // 
					 this->cbox_ParamDef->FormattingEnabled = true;
					 this->cbox_ParamDef->Location = System::Drawing::Point(4, 68);
					 this->cbox_ParamDef->Name = L"cbox_ParamDef";
					 this->cbox_ParamDef->Size = System::Drawing::Size(210, 20);
					 this->cbox_ParamDef->TabIndex = 1;
					 // 
					 // cbox_ParamID
					 // 
					 this->cbox_ParamID->FormattingEnabled = true;
					 this->cbox_ParamID->Location = System::Drawing::Point(4, 30);
					 this->cbox_ParamID->Name = L"cbox_ParamID";
					 this->cbox_ParamID->Size = System::Drawing::Size(210, 20);
					 this->cbox_ParamID->TabIndex = 0;
					 this->cbox_ParamID->SelectedIndexChanged += gcnew System::EventHandler(this, &MovieForm::cbox_ParamID_SelectedIndexChanged);
					 this->cbox_ParamID->TextUpdate += gcnew System::EventHandler(this, &MovieForm::cbox_ParamID_TextUpdate);
					 // 
					 // btn_paramSet
					 // 
					 this->btn_paramSet->Location = System::Drawing::Point(223, 105);
					 this->btn_paramSet->Name = L"btn_paramSet";
					 this->btn_paramSet->Size = System::Drawing::Size(54, 23);
					 this->btn_paramSet->TabIndex = 6;
					 this->btn_paramSet->Text = L"Set";
					 this->btn_paramSet->UseVisualStyleBackColor = true;
					 this->btn_paramSet->Click += gcnew System::EventHandler(this, &MovieForm::btn_paramset_click);
					 // 
					 // picbox_LCD
					 // 
					 this->picbox_LCD->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picbox_LCD.BackgroundImage")));
					 this->picbox_LCD->Cursor = System::Windows::Forms::Cursors::Hand;
					 this->picbox_LCD->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picbox_LCD.Image")));
					 this->picbox_LCD->Location = System::Drawing::Point(1, 1);
					 this->picbox_LCD->Margin = System::Windows::Forms::Padding(0);
					 this->picbox_LCD->Name = L"picbox_LCD";
					 this->picbox_LCD->Size = System::Drawing::Size(960, 640);
					 this->picbox_LCD->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
					 this->picbox_LCD->TabIndex = 48;
					 this->picbox_LCD->TabStop = false;
					 this->picbox_LCD->Tag = L"1";
					 this->picbox_LCD->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::picbox_LCD_MouseDown);
					 this->picbox_LCD->MouseLeave += gcnew System::EventHandler(this, &MovieForm::picbox_LCD_MouseLeave);
					 this->picbox_LCD->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::picbox_LCD_MouseMove);
					 this->picbox_LCD->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::picbox_LCD_MouseUp);
					 this->picbox_LCD->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MovieForm::picbox_LCD_MouseWheel);
					 // 
					 // picbox_LOUT
					 // 
					 this->picbox_LOUT->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picbox_LOUT.BackgroundImage")));
					 this->picbox_LOUT->Cursor = System::Windows::Forms::Cursors::No;
					 this->picbox_LOUT->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picbox_LOUT.Image")));
					 this->picbox_LOUT->Location = System::Drawing::Point(1, 1);
					 this->picbox_LOUT->Margin = System::Windows::Forms::Padding(0);
					 this->picbox_LOUT->Name = L"picbox_LOUT";
					 this->picbox_LOUT->Size = System::Drawing::Size(960, 540);
					 this->picbox_LOUT->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
					 this->picbox_LOUT->TabIndex = 49;
					 this->picbox_LOUT->TabStop = false;
					 this->picbox_LOUT->Tag = L"1";
					 this->picbox_LOUT->Visible = false;
					 // 
					 // flowLayoutPanel1
					 // 
					 this->flowLayoutPanel1->AutoSize = true;
					 this->flowLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					 this->flowLayoutPanel1->Controls->Add(this->panel_LCD);
					 this->flowLayoutPanel1->Controls->Add(this->panel_LOUT);
					 this->flowLayoutPanel1->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
					 this->flowLayoutPanel1->Location = System::Drawing::Point(513, 5);
					 this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
					 this->flowLayoutPanel1->Size = System::Drawing::Size(967, 1194);
					 this->flowLayoutPanel1->TabIndex = 8;
					 // 
					 // panel_LCD
					 // 
					 this->panel_LCD->AutoSize = true;
					 this->panel_LCD->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					 this->panel_LCD->Controls->Add(this->picbox_RectLCD);
					 this->panel_LCD->Controls->Add(this->picbox_LCD);
					 this->panel_LCD->Location = System::Drawing::Point(3, 3);
					 this->panel_LCD->Name = L"panel_LCD";
					 this->panel_LCD->Size = System::Drawing::Size(961, 641);
					 this->panel_LCD->TabIndex = 0;
					 // 
					 // picbox_RectLCD
					 // 
					 this->picbox_RectLCD->BackColor = System::Drawing::Color::Transparent;
					 this->picbox_RectLCD->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
					 this->picbox_RectLCD->Cursor = System::Windows::Forms::Cursors::Hand;
					 this->picbox_RectLCD->Enabled = false;
					 this->picbox_RectLCD->Location = System::Drawing::Point(0, 0);
					 this->picbox_RectLCD->Margin = System::Windows::Forms::Padding(0);
					 this->picbox_RectLCD->Name = L"picbox_RectLCD";
					 this->picbox_RectLCD->Size = System::Drawing::Size(960, 640);
					 this->picbox_RectLCD->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
					 this->picbox_RectLCD->TabIndex = 52;
					 this->picbox_RectLCD->TabStop = false;
					 // 
					 // panel_LOUT
					 // 
					 this->panel_LOUT->AutoSize = true;
					 this->panel_LOUT->Controls->Add(this->picbox_LOUT);
					 this->panel_LOUT->Location = System::Drawing::Point(3, 650);
					 this->panel_LOUT->Name = L"panel_LOUT";
					 this->panel_LOUT->Size = System::Drawing::Size(961, 541);
					 this->panel_LOUT->TabIndex = 1;
					 // 
					 // btn_LogPlay
					 // 
					 this->btn_LogPlay->Location = System::Drawing::Point(6, 13);
					 this->btn_LogPlay->Name = L"btn_LogPlay";
					 this->btn_LogPlay->Size = System::Drawing::Size(69, 23);
					 this->btn_LogPlay->TabIndex = 0;
					 this->btn_LogPlay->Text = L"LogPlay";
					 this->btn_LogPlay->UseVisualStyleBackColor = true;
					 this->btn_LogPlay->Click += gcnew System::EventHandler(this, &MovieForm::btn_LogPlay_Click);
					 // 
					 // LogPlayer
					 // 
					 this->LogPlayer->Controls->Add(this->btn_CmdLine);
					 this->LogPlayer->Controls->Add(this->btn_ReadLog);
					 this->LogPlayer->Controls->Add(this->btn_SaveLog);
					 this->LogPlayer->Controls->Add(this->btn_LogPlay);
					 this->LogPlayer->Controls->Add(this->btn_ConsoleClear);
					 this->LogPlayer->Location = System::Drawing::Point(16, 18);
					 this->LogPlayer->Name = L"LogPlayer";
					 this->LogPlayer->Size = System::Drawing::Size(80, 167);
					 this->LogPlayer->TabIndex = 0;
					 this->LogPlayer->TabStop = false;
					 this->LogPlayer->Text = L"ModeSelect";
					 // 
					 // btn_CmdLine
					 // 
					 this->btn_CmdLine->Location = System::Drawing::Point(6, 67);
					 this->btn_CmdLine->Name = L"btn_CmdLine";
					 this->btn_CmdLine->Size = System::Drawing::Size(69, 23);
					 this->btn_CmdLine->TabIndex = 2;
					 this->btn_CmdLine->Text = L"CmdLine";
					 this->btn_CmdLine->UseVisualStyleBackColor = true;
					 this->btn_CmdLine->Click += gcnew System::EventHandler(this, &MovieForm::btn_CmdLine_Click);
					 // 
					 // btn_ReadLog
					 // 
					 this->btn_ReadLog->Location = System::Drawing::Point(6, 40);
					 this->btn_ReadLog->Name = L"btn_ReadLog";
					 this->btn_ReadLog->Size = System::Drawing::Size(69, 23);
					 this->btn_ReadLog->TabIndex = 1;
					 this->btn_ReadLog->Text = L"ReadLog";
					 this->btn_ReadLog->UseVisualStyleBackColor = true;
					 this->btn_ReadLog->Click += gcnew System::EventHandler(this, &MovieForm::btn_ReadLog_Click);
					 // 
					 // btn_SaveLog
					 // 
					 this->btn_SaveLog->Location = System::Drawing::Point(5, 134);
					 this->btn_SaveLog->Name = L"btn_SaveLog";
					 this->btn_SaveLog->Size = System::Drawing::Size(69, 23);
					 this->btn_SaveLog->TabIndex = 4;
					 this->btn_SaveLog->Text = L"SaveLog";
					 this->btn_SaveLog->UseVisualStyleBackColor = true;
					 this->btn_SaveLog->Click += gcnew System::EventHandler(this, &MovieForm::btn_SaveLog_Click);
					 // 
					 // btn_ConsoleClear
					 // 
					 this->btn_ConsoleClear->Location = System::Drawing::Point(5, 107);
					 this->btn_ConsoleClear->Name = L"btn_ConsoleClear";
					 this->btn_ConsoleClear->Size = System::Drawing::Size(69, 23);
					 this->btn_ConsoleClear->TabIndex = 3;
					 this->btn_ConsoleClear->Text = L"ClearCnsl";
					 this->btn_ConsoleClear->UseVisualStyleBackColor = true;
					 this->btn_ConsoleClear->Click += gcnew System::EventHandler(this, &MovieForm::btn_ConsoleClear_Click);
					 // 
					 // groupBox2
					 // 
					 this->groupBox2->Controls->Add(this->btn_variety8);
					 this->groupBox2->Controls->Add(this->btn_variety6);
					 this->groupBox2->Controls->Add(this->btn_variety7);
					 this->groupBox2->Controls->Add(this->btn_Variety5);
					 this->groupBox2->Controls->Add(this->btn_variety);
					 this->groupBox2->Controls->Add(this->btn_variety4);
					 this->groupBox2->Controls->Add(this->btn_variety2);
					 this->groupBox2->Controls->Add(this->btn_variety3);
					 this->groupBox2->Location = System::Drawing::Point(316, 254);
					 this->groupBox2->Name = L"groupBox2";
					 this->groupBox2->Size = System::Drawing::Size(184, 72);
					 this->groupBox2->TabIndex = 9;
					 this->groupBox2->TabStop = false;
					 this->groupBox2->Text = L"Varieties";
					 // 
					 // btn_variety8
					 // 
					 this->btn_variety8->Location = System::Drawing::Point(141, 38);
					 this->btn_variety8->Name = L"btn_variety8";
					 this->btn_variety8->Size = System::Drawing::Size(39, 23);
					 this->btn_variety8->TabIndex = 11;
					 this->btn_variety8->Text = L"Var8";
					 this->btn_variety8->UseVisualStyleBackColor = true;
					 this->btn_variety8->Click += gcnew System::EventHandler(this, &MovieForm::btn_variety8_Click);
					 // 
					 // btn_variety6
					 // 
					 this->btn_variety6->Location = System::Drawing::Point(96, 38);
					 this->btn_variety6->Name = L"btn_variety6";
					 this->btn_variety6->Size = System::Drawing::Size(39, 23);
					 this->btn_variety6->TabIndex = 5;
					 this->btn_variety6->Text = L"Var6";
					 this->btn_variety6->UseVisualStyleBackColor = true;
					 this->btn_variety6->Click += gcnew System::EventHandler(this, &MovieForm::btn_variety6_Click);
					 // 
					 // btn_variety7
					 // 
					 this->btn_variety7->Location = System::Drawing::Point(141, 12);
					 this->btn_variety7->Name = L"btn_variety7";
					 this->btn_variety7->Size = System::Drawing::Size(39, 23);
					 this->btn_variety7->TabIndex = 10;
					 this->btn_variety7->Text = L"Var7";
					 this->btn_variety7->UseVisualStyleBackColor = true;
					 this->btn_variety7->Click += gcnew System::EventHandler(this, &MovieForm::btn_variety7_Click);
					 // 
					 // btn_Variety5
					 // 
					 this->btn_Variety5->Location = System::Drawing::Point(96, 12);
					 this->btn_Variety5->Name = L"btn_Variety5";
					 this->btn_Variety5->Size = System::Drawing::Size(39, 23);
					 this->btn_Variety5->TabIndex = 4;
					 this->btn_Variety5->Text = L"Var5";
					 this->btn_Variety5->UseVisualStyleBackColor = true;
					 this->btn_Variety5->Click += gcnew System::EventHandler(this, &MovieForm::btn_Variety5_Click);
					 // 
					 // grpbx_shrcut
					 // 
					 this->grpbx_shrcut->Controls->Add(this->btn_sc_Clip);
					 this->grpbx_shrcut->Controls->Add(this->btn_sc_Play);
					 this->grpbx_shrcut->Controls->Add(this->btn_sc_View);
					 this->grpbx_shrcut->Controls->Add(this->btn_sc_Menu);
					 this->grpbx_shrcut->Controls->Add(this->btn_sc_Info);
					 this->grpbx_shrcut->Controls->Add(this->btn_sc_Home);
					 this->grpbx_shrcut->Controls->Add(this->btn_sc_Thumb);
					 this->grpbx_shrcut->Location = System::Drawing::Point(3, 254);
					 this->grpbx_shrcut->Name = L"grpbx_shrcut";
					 this->grpbx_shrcut->Size = System::Drawing::Size(311, 72);
					 this->grpbx_shrcut->TabIndex = 8;
					 this->grpbx_shrcut->TabStop = false;
					 this->grpbx_shrcut->Text = L"ShortCut(Change)";
					 // 
					 // btn_sc_Clip
					 // 
					 this->btn_sc_Clip->Location = System::Drawing::Point(236, 39);
					 this->btn_sc_Clip->Name = L"btn_sc_Clip";
					 this->btn_sc_Clip->Size = System::Drawing::Size(70, 20);
					 this->btn_sc_Clip->TabIndex = 6;
					 this->btn_sc_Clip->Text = L"Clip";
					 this->btn_sc_Clip->UseVisualStyleBackColor = true;
					 this->btn_sc_Clip->Click += gcnew System::EventHandler(this, &MovieForm::btn_sc_Clip_Click);
					 // 
					 // btn_sc_Play
					 // 
					 this->btn_sc_Play->Location = System::Drawing::Point(160, 39);
					 this->btn_sc_Play->Name = L"btn_sc_Play";
					 this->btn_sc_Play->Size = System::Drawing::Size(70, 20);
					 this->btn_sc_Play->TabIndex = 5;
					 this->btn_sc_Play->Text = L"Play";
					 this->btn_sc_Play->UseVisualStyleBackColor = true;
					 this->btn_sc_Play->Click += gcnew System::EventHandler(this, &MovieForm::btn_sc_Play_Click);
					 // 
					 // grpbx_refInfo
					 // 
					 this->grpbx_refInfo->BackColor = System::Drawing::Color::WhiteSmoke;
					 this->grpbx_refInfo->Controls->Add(this->btn_MemInfo);
					 this->grpbx_refInfo->Controls->Add(this->btn_ClsInfo);
					 this->grpbx_refInfo->Controls->Add(this->btn_GetRoot);
					 this->grpbx_refInfo->Controls->Add(this->btn_GetCurrent);
					 this->grpbx_refInfo->Location = System::Drawing::Point(419, 332);
					 this->grpbx_refInfo->Name = L"grpbx_refInfo";
					 this->grpbx_refInfo->Size = System::Drawing::Size(80, 132);
					 this->grpbx_refInfo->TabIndex = 3;
					 this->grpbx_refInfo->TabStop = false;
					 this->grpbx_refInfo->Text = L"RefInfo";
					 // 
					 // btn_MemInfo
					 // 
					 this->btn_MemInfo->Location = System::Drawing::Point(8, 96);
					 this->btn_MemInfo->Name = L"btn_MemInfo";
					 this->btn_MemInfo->Size = System::Drawing::Size(61, 23);
					 this->btn_MemInfo->TabIndex = 4;
					 this->btn_MemInfo->Text = L"MemInfo";
					 this->btn_MemInfo->UseVisualStyleBackColor = true;
					 this->btn_MemInfo->Click += gcnew System::EventHandler(this, &MovieForm::btn_MemInfo_Click);
					 // 
					 // btn_ClsInfo
					 // 
					 this->btn_ClsInfo->Location = System::Drawing::Point(8, 70);
					 this->btn_ClsInfo->Name = L"btn_ClsInfo";
					 this->btn_ClsInfo->Size = System::Drawing::Size(61, 23);
					 this->btn_ClsInfo->TabIndex = 3;
					 this->btn_ClsInfo->Text = L"ClassInfo";
					 this->btn_ClsInfo->UseVisualStyleBackColor = true;
					 this->btn_ClsInfo->Click += gcnew System::EventHandler(this, &MovieForm::btn_ClassInfo_Click);
					 // 
					 // btn_Setting
					 // 
					 this->btn_Setting->Location = System::Drawing::Point(132, 36);
					 this->btn_Setting->Name = L"btn_Setting";
					 this->btn_Setting->Size = System::Drawing::Size(64, 23);
					 this->btn_Setting->TabIndex = 17;
					 this->btn_Setting->Text = L"各種設定";
					 this->btn_Setting->UseVisualStyleBackColor = true;
					 this->btn_Setting->Click += gcnew System::EventHandler(this, &MovieForm::btn_saveSetting_Click);
					 // 
					 // tab_Ctrl_Sim
					 // 
					 this->tab_Ctrl_Sim->Controls->Add(this->Controller);
					 this->tab_Ctrl_Sim->Controls->Add(this->WidgetExplorer);
					 this->tab_Ctrl_Sim->Controls->Add(this->CommandCtrl);
					 this->tab_Ctrl_Sim->Controls->Add(this->Support);
					 this->tab_Ctrl_Sim->Location = System::Drawing::Point(3, 5);
					 this->tab_Ctrl_Sim->Name = L"tab_Ctrl_Sim";
					 this->tab_Ctrl_Sim->SelectedIndex = 0;
					 this->tab_Ctrl_Sim->Size = System::Drawing::Size(510, 544);
					 this->tab_Ctrl_Sim->TabIndex = 18;
					 // 
					 // Controller
					 // 
					 this->Controller->BackColor = System::Drawing::Color::WhiteSmoke;
					 this->Controller->Controls->Add(this->grpbx_shrcut);
					 this->Controller->Controls->Add(this->grpbx_refInfo);
					 this->Controller->Controls->Add(this->groupBox2);
					 this->Controller->Controls->Add(this->gBox_AplParam);
					 this->Controller->Controls->Add(this->gbox_WindowControll);
					 this->Controller->Controls->Add(this->gBoxDeck);
					 this->Controller->Location = System::Drawing::Point(4, 22);
					 this->Controller->Name = L"Controller";
					 this->Controller->Padding = System::Windows::Forms::Padding(3);
					 this->Controller->Size = System::Drawing::Size(502, 518);
					 this->Controller->TabIndex = 0;
					 this->Controller->Text = L"Controller";
					 // 
					 // WidgetExplorer
					 // 
					 this->WidgetExplorer->BackColor = System::Drawing::Color::Gainsboro;
					 this->WidgetExplorer->Controls->Add(this->split_Cont_Widget_Exp);
					 this->WidgetExplorer->Location = System::Drawing::Point(4, 22);
					 this->WidgetExplorer->Name = L"WidgetExplorer";
					 this->WidgetExplorer->Padding = System::Windows::Forms::Padding(3);
					 this->WidgetExplorer->Size = System::Drawing::Size(502, 518);
					 this->WidgetExplorer->TabIndex = 1;
					 this->WidgetExplorer->Text = L"WidgetExplorer";
					 // 
					 // split_Cont_Widget_Exp
					 // 
					 this->split_Cont_Widget_Exp->Dock = System::Windows::Forms::DockStyle::Fill;
					 this->split_Cont_Widget_Exp->Location = System::Drawing::Point(3, 3);
					 this->split_Cont_Widget_Exp->Name = L"split_Cont_Widget_Exp";
					 this->split_Cont_Widget_Exp->Orientation = System::Windows::Forms::Orientation::Horizontal;
					 // 
					 // split_Cont_Widget_Exp.Panel1
					 // 
					 this->split_Cont_Widget_Exp->Panel1->Controls->Add(this->split_Ctnr_Exp);
					 // 
					 // split_Cont_Widget_Exp.Panel2
					 // 
					 this->split_Cont_Widget_Exp->Panel2->BackColor = System::Drawing::Color::WhiteSmoke;
					 this->split_Cont_Widget_Exp->Panel2->Controls->Add(this->treeV_text);
					 this->split_Cont_Widget_Exp->Panel2->Controls->Add(this->gBoxOutLine);
					 this->split_Cont_Widget_Exp->Size = System::Drawing::Size(496, 512);
					 this->split_Cont_Widget_Exp->SplitterDistance = 353;
					 this->split_Cont_Widget_Exp->SplitterWidth = 1;
					 this->split_Cont_Widget_Exp->TabIndex = 0;
					 // 
					 // split_Ctnr_Exp
					 // 
					 this->split_Ctnr_Exp->Dock = System::Windows::Forms::DockStyle::Fill;
					 this->split_Ctnr_Exp->Location = System::Drawing::Point(0, 0);
					 this->split_Ctnr_Exp->Name = L"split_Ctnr_Exp";
					 // 
					 // split_Ctnr_Exp.Panel1
					 // 
					 this->split_Ctnr_Exp->Panel1->Controls->Add(this->treeV_Widget);
					 // 
					 // split_Ctnr_Exp.Panel2
					 // 
					 this->split_Ctnr_Exp->Panel2->Controls->Add(this->listV_Widget);
					 this->split_Ctnr_Exp->Size = System::Drawing::Size(496, 353);
					 this->split_Ctnr_Exp->SplitterDistance = 273;
					 this->split_Ctnr_Exp->TabIndex = 0;
					 // 
					 // treeV_Widget
					 // 
					 this->treeV_Widget->Dock = System::Windows::Forms::DockStyle::Fill;
					 this->treeV_Widget->Location = System::Drawing::Point(0, 0);
					 this->treeV_Widget->Name = L"treeV_Widget";
					 this->treeV_Widget->Size = System::Drawing::Size(273, 353);
					 this->treeV_Widget->TabIndex = 0;
					 this->treeV_Widget->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MovieForm::treeV_Widget_AfterSelect);
					 this->treeV_Widget->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &MovieForm::treeV_Widget_NodeMouseClick);
					 // 
					 // listV_Widget
					 // 
					 this->listV_Widget->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
					 this->listV_Widget->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->ラベル, this->データ });
					 this->listV_Widget->Dock = System::Windows::Forms::DockStyle::Fill;
					 this->listV_Widget->GridLines = true;
					 this->listV_Widget->Location = System::Drawing::Point(0, 0);
					 this->listV_Widget->MultiSelect = false;
					 this->listV_Widget->Name = L"listV_Widget";
					 this->listV_Widget->Size = System::Drawing::Size(219, 353);
					 this->listV_Widget->TabIndex = 0;
					 this->listV_Widget->UseCompatibleStateImageBehavior = false;
					 this->listV_Widget->View = System::Windows::Forms::View::Details;
					 // 
					 // ラベル
					 // 
					 this->ラベル->Text = L"ラベル";
					 this->ラベル->Width = 80;
					 // 
					 // データ
					 // 
					 this->データ->Text = L"データ";
					 this->データ->Width = 150;
					 // 
					 // treeV_text
					 // 
					 this->treeV_text->AutoSize = true;
					 this->treeV_text->Location = System::Drawing::Point(287, 19);
					 this->treeV_text->Name = L"treeV_text";
					 this->treeV_text->Size = System::Drawing::Size(194, 12);
					 this->treeV_text->TabIndex = 8;
					 this->treeV_text->Text = L"※ツリーノードを右クリックでOutLine表示";
					 // 
					 // CommandCtrl
					 // 
					 this->CommandCtrl->Controls->Add(this->LogPlayer);
					 this->CommandCtrl->Location = System::Drawing::Point(4, 22);
					 this->CommandCtrl->Name = L"CommandCtrl";
					 this->CommandCtrl->Size = System::Drawing::Size(502, 518);
					 this->CommandCtrl->TabIndex = 3;
					 this->CommandCtrl->Text = L"CommandCtrl";
					 this->CommandCtrl->UseVisualStyleBackColor = true;
					 // 
					 // Support
					 // 
					 this->Support->BackColor = System::Drawing::Color::WhiteSmoke;
					 this->Support->Controls->Add(this->gBox_SimSetting);
					 this->Support->Controls->Add(this->gBox_Save);
					 this->Support->Location = System::Drawing::Point(4, 22);
					 this->Support->Name = L"Support";
					 this->Support->Size = System::Drawing::Size(502, 518);
					 this->Support->TabIndex = 2;
					 this->Support->Text = L"Support";
					 // 
					 // gBox_SimSetting
					 // 
					 this->gBox_SimSetting->Controls->Add(this->chk_Box_Logo);
					 this->gBox_SimSetting->Location = System::Drawing::Point(5, 137);
					 this->gBox_SimSetting->Name = L"gBox_SimSetting";
					 this->gBox_SimSetting->Size = System::Drawing::Size(347, 143);
					 this->gBox_SimSetting->TabIndex = 19;
					 this->gBox_SimSetting->TabStop = false;
					 this->gBox_SimSetting->Text = L"Setting";
					 // 
					 // chk_Box_Logo
					 // 
					 this->chk_Box_Logo->AutoSize = true;
					 this->chk_Box_Logo->Location = System::Drawing::Point(6, 18);
					 this->chk_Box_Logo->Name = L"chk_Box_Logo";
					 this->chk_Box_Logo->Size = System::Drawing::Size(103, 16);
					 this->chk_Box_Logo->TabIndex = 18;
					 this->chk_Box_Logo->Text = L"LOGOを出さない";
					 this->chk_Box_Logo->UseVisualStyleBackColor = true;
					 // 
					 // gBox_Save
					 // 
					 this->gBox_Save->Controls->Add(this->gBox_pictSave);
					 this->gBox_Save->Controls->Add(this->btn_Setting);
					 this->gBox_Save->Location = System::Drawing::Point(5, 3);
					 this->gBox_Save->Name = L"gBox_Save";
					 this->gBox_Save->Size = System::Drawing::Size(347, 128);
					 this->gBox_Save->TabIndex = 4;
					 this->gBox_Save->TabStop = false;
					 this->gBox_Save->Text = L"Save";
					 // 
					 // gBox_pictSave
					 // 
					 this->gBox_pictSave->Controls->Add(this->radbtnSave_BMP);
					 this->gBox_pictSave->Controls->Add(this->radbtnSave_JPG);
					 this->gBox_pictSave->Controls->Add(this->btnSave_LOUT);
					 this->gBox_pictSave->Controls->Add(this->btnSave_LCD);
					 this->gBox_pictSave->Location = System::Drawing::Point(6, 18);
					 this->gBox_pictSave->Name = L"gBox_pictSave";
					 this->gBox_pictSave->Size = System::Drawing::Size(120, 88);
					 this->gBox_pictSave->TabIndex = 4;
					 this->gBox_pictSave->TabStop = false;
					 this->gBox_pictSave->Text = L"Picture";
					 // 
					 // radbtnSave_BMP
					 // 
					 this->radbtnSave_BMP->AutoSize = true;
					 this->radbtnSave_BMP->Location = System::Drawing::Point(6, 69);
					 this->radbtnSave_BMP->Name = L"radbtnSave_BMP";
					 this->radbtnSave_BMP->Size = System::Drawing::Size(47, 16);
					 this->radbtnSave_BMP->TabIndex = 3;
					 this->radbtnSave_BMP->Text = L"BMP";
					 this->radbtnSave_BMP->UseVisualStyleBackColor = true;
					 // 
					 // radbtnSave_JPG
					 // 
					 this->radbtnSave_JPG->AutoSize = true;
					 this->radbtnSave_JPG->Checked = true;
					 this->radbtnSave_JPG->Location = System::Drawing::Point(6, 47);
					 this->radbtnSave_JPG->Name = L"radbtnSave_JPG";
					 this->radbtnSave_JPG->Size = System::Drawing::Size(45, 16);
					 this->radbtnSave_JPG->TabIndex = 2;
					 this->radbtnSave_JPG->TabStop = true;
					 this->radbtnSave_JPG->Text = L"JPG";
					 this->radbtnSave_JPG->UseVisualStyleBackColor = true;
					 // 
					 // btnSave_LOUT
					 // 
					 this->btnSave_LOUT->Location = System::Drawing::Point(62, 18);
					 this->btnSave_LOUT->Name = L"btnSave_LOUT";
					 this->btnSave_LOUT->Size = System::Drawing::Size(50, 23);
					 this->btnSave_LOUT->TabIndex = 1;
					 this->btnSave_LOUT->Text = L"LOUT";
					 this->btnSave_LOUT->UseVisualStyleBackColor = true;
					 this->btnSave_LOUT->Click += gcnew System::EventHandler(this, &MovieForm::btnSave_LOUT_Click);
					 // 
					 // btnSave_LCD
					 // 
					 this->btnSave_LCD->Location = System::Drawing::Point(6, 18);
					 this->btnSave_LCD->Name = L"btnSave_LCD";
					 this->btnSave_LCD->Size = System::Drawing::Size(50, 23);
					 this->btnSave_LCD->TabIndex = 0;
					 this->btnSave_LCD->Text = L"LCD";
					 this->btnSave_LCD->UseVisualStyleBackColor = true;
					 this->btnSave_LCD->Click += gcnew System::EventHandler(this, &MovieForm::btnSave_LCD_Click);
					 // 
					 // MovieForm
					 // 
					 this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
					 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
					 this->AutoSize = true;
					 this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
					 this->BackColor = System::Drawing::SystemColors::Window;
					 this->ClientSize = System::Drawing::Size(1486, 1061);
					 this->Controls->Add(this->tab_Ctrl_Sim);
					 this->Controls->Add(this->flowLayoutPanel1);
					 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
					 this->KeyPreview = true;
					 this->MaximizeBox = false;
					 this->MinimizeBox = false;
					 this->Name = L"MovieForm";
					 this->Text = L"GUI Simulator";
					 this->Load += gcnew System::EventHandler(this, &MovieForm::MovieForm_Load);
					 this->Shown += gcnew System::EventHandler(this, &MovieForm::MovieForm_Shown);
					 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MovieForm::MovieForm_KeyDown);
					 this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MovieForm::MovieForm_KeyUp);
					 this->gBoxOutLine->ResumeLayout(false);
					 this->gBoxOutLine->PerformLayout();
					 this->gBoxDeck->ResumeLayout(false);
					 this->gBoxDeck->PerformLayout();
					 this->grpbox_Dial->ResumeLayout(false);
					 this->grpbox_keysrc->ResumeLayout(false);
					 this->grpbox_keysrc->PerformLayout();
					 this->gbox_WindowControll->ResumeLayout(false);
					 this->gbox_WindowControll->PerformLayout();
					 this->gBox_AplParam->ResumeLayout(false);
					 this->gBox_AplParam->PerformLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picbox_LCD))->EndInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picbox_LOUT))->EndInit();
					 this->flowLayoutPanel1->ResumeLayout(false);
					 this->flowLayoutPanel1->PerformLayout();
					 this->panel_LCD->ResumeLayout(false);
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picbox_RectLCD))->EndInit();
					 this->panel_LOUT->ResumeLayout(false);
					 this->LogPlayer->ResumeLayout(false);
					 this->groupBox2->ResumeLayout(false);
					 this->grpbx_shrcut->ResumeLayout(false);
					 this->grpbx_refInfo->ResumeLayout(false);
					 this->tab_Ctrl_Sim->ResumeLayout(false);
					 this->Controller->ResumeLayout(false);
					 this->WidgetExplorer->ResumeLayout(false);
					 this->split_Cont_Widget_Exp->Panel1->ResumeLayout(false);
					 this->split_Cont_Widget_Exp->Panel2->ResumeLayout(false);
					 this->split_Cont_Widget_Exp->Panel2->PerformLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->split_Cont_Widget_Exp))->EndInit();
					 this->split_Cont_Widget_Exp->ResumeLayout(false);
					 this->split_Ctnr_Exp->Panel1->ResumeLayout(false);
					 this->split_Ctnr_Exp->Panel2->ResumeLayout(false);
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->split_Ctnr_Exp))->EndInit();
					 this->split_Ctnr_Exp->ResumeLayout(false);
					 this->CommandCtrl->ResumeLayout(false);
					 this->Support->ResumeLayout(false);
					 this->gBox_SimSetting->ResumeLayout(false);
					 this->gBox_SimSetting->PerformLayout();
					 this->gBox_Save->ResumeLayout(false);
					 this->gBox_pictSave->ResumeLayout(false);
					 this->gBox_pictSave->PerformLayout();
					 this->ResumeLayout(false);
					 this->PerformLayout();

			 }
#pragma endregion
	public: virtual Void WndProc(System::Windows::Forms::Message% msg) override;
			virtual bool MovieForm::ProcessDialogKey(System::Windows::Forms::Keys key) override;
	private: System::Void MovieForm_Shown(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MovieForm_Load(System::Object^  sender, System::EventArgs^  e);
	private: char getScreenId();
			 //★★★★★★★★★★★★ ID_WIN_TRANS ★★★★★★★★★★★★
	private: System::Void btn_ChangeWindow_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_ReturnWindow_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_PopupWindow_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_CloseWindow_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_SwapWindow_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_RemoveWindow_Click(System::Object^  sender, System::EventArgs^  e);
			 //★★★★★★★★★★★★ ID_REF_INFO ★★★★★★★★★★★★
	private: System::Void btn_GetRoot_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_GetCurrent_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_ShowOutline_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_ClassInfo_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_MemInfo_Click(System::Object^  sender, System::EventArgs^  e);
			 //★★★★★★★★★★★★ ID_APL_PARAM ★★★★★★★★★★★
			 //★★★★★★★★★★★★ ID_SYS_KEY ★★★★★★★★★★★★
			 void MovieForm::VirtualKeyUpEvent(unsigned short key);
			 void MovieForm::VirtualKeyDownEvent(unsigned short key);
			 void MovieForm::VirtualMouseWheelEvent(int line);
			 void MovieForm::VirtualMovieKey(bool isPress, unsigned char keyType, unsigned short keyCode);
			 bool MoveMouseCursor(KeyEventArgs^ e);
			 bool isIgnoreKeyEvent();
			 System::Void MovieForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
			 System::Void MovieForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
			 System::Void chkLockSw_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
			 // Up
	private: System::Void button_up_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void button_right_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void button_left_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void button_down_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void button_enter_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void buttonMenu_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void buttonHome_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void buttonThumb_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
	private: System::Void buttonExit_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 // Down
			 System::Void button_up_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void button_right_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void button_left_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void button_down_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void button_enter_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void buttonMenu_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void buttonHome_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void buttonThumb_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void buttonExit_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void picbox_LCD_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 //★★★★★★★★★★★★ID_SYS_TOUCH★★★★★★★★★★★★
			 System::Windows::Forms::MouseEventArgs^ AdjustMousePosition(System::Windows::Forms::MouseEventArgs^ e);
			 System::Void picbox_LCD_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void picbox_LCD_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 System::Void picbox_LCD_MouseLeave(System::Object^  sender, System::EventArgs^  e);
			 System::Void picbox_LCD_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e);
			 /////////////////★★★★★★★★★★★★ SIMU FUNC ★★★★★★★★★★★★/////////////////
			 unsigned int MovieForm::getSelectedWindowID();
			 unsigned int MovieForm::getSelectedAplParam();
			 System::Void MovieForm::initWindowID();
			 System::Void MovieForm::initParamID();
			 System::Void MovieForm::btn_DrawRect_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void MovieForm::DrawRectangleToScreenLCD(int x, int y, int w, int h);
			 System::Void MovieForm::btn_DrawReset_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void MovieForm::cbox_Disp_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
			 System::Void MovieForm::btnSave_LCD_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void MovieForm::btnSave_LOUT_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void MovieForm::SaveImage(String^ header, Image ^source);
			 System::Void MovieForm::cbox_Scale_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e);
			 System::Void MovieForm::cbox_WindowName_TextUpdate(System::Object^  sender, System::EventArgs^  e);
			 System::Void MovieForm::cbox_ParamID_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
			 System::Void MovieForm::cbox_ParamID_TextUpdate(System::Object^  sender, System::EventArgs^  e);
			 System::Void MovieForm::btn_NextWind_Click(System::Object^  sender, System::EventArgs^  e);
			 System::Void MovieForm::btn_PrevWind_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_User1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_USER1);
	}
	private: System::Void btn_User1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_USER1);
	}
	private: System::Void btn_User2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_USER2);
	}
	private: System::Void btn_User2_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_USER2);
	}
	private: System::Void btn_User3_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_USER3);
	}
	private: System::Void btn_User3_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_USER3);
	}
	private: System::Void btn_User4_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_USER4);
	}
	private: System::Void btn_User4_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_USER4);
	}
	private: System::Void btn_User5_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_USER5);
	}
	private: System::Void btn_User5_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_USER5);
	}
	private: System::Void btn_User6_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_USER6);
	}
	private: System::Void btn_User6_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_USER6);
	}
	private: System::Void btn_User7_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_USER7);
	}
	private: System::Void btn_User7_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_USER7);
	}
	private: System::Void btn_User8_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_USER8);
	}
	private: System::Void btn_User8_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_USER8);
	}
	private: System::Void btn_User9_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_USER9);
	}
	private: System::Void btn_User9_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_USER9);
	}
	private: System::Void btn_Menu_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_MENU);
	}
	private: System::Void btn_Menu_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_MENU);
	}
	private: System::Void btn_Home_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_HOME);
	}
	private: System::Void btn_Home_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_HOME);
	}
	private: System::Void btn_Thumb_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_MODE);
	}
	private: System::Void btn_Thumb_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_MODE);
	}
			 //★★★★★★★★★★★★ ID_SHRT_CUT ★★★★★★★★★★★★
	private: System::Void btn_sc_Menu_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndShrtCut(getScreenId(), ID_SHRT_CUT, ID_SHRT_MENU, ID_INVALID);
	}
	private: System::Void btn_sc_Home_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndShrtCut(getScreenId(), ID_SHRT_CUT, ID_SHRT_HOME, ID_INVALID);
	}
	private: System::Void btn_sc_Thumb_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndShrtCut(getScreenId(), ID_SHRT_CUT, ID_SHRT_THUM, ID_INVALID);
	}
	private: System::Void btn_sc_View_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndShrtCut(getScreenId(), ID_SHRT_CUT, ID_SHRT_VIEW, ID_INVALID);
	}
	private: System::Void btn_sc_Info_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndShrtCut(getScreenId(), ID_SHRT_CUT, ID_SHRT_INFO, ID_INVALID);
	}
	private: System::Void btn_sc_Play_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndShrtCut(getScreenId(), ID_SHRT_CUT, ID_SHRT_PLAY, ID_INVALID);
	}
	private: System::Void btn_sc_Clip_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndShrtCut(getScreenId(), ID_SHRT_CUT, ID_SHRT_CLIP, ID_INVALID);
	}
			 //★★★★★★★★★★★★ SETTING SAVE ★★★★★★★★★★★★
			 System::Void saveSetting();
			 System::Void readSetting();
	private:
		//★★★★★★★★★★★★ LOG FUNC ★★★★★★★★★★★★
		System::Void btn_ReadLog_Click(System::Object^  sender, System::EventArgs^  e);
	private:
	private: System::Void btn_SaveLog_Click(System::Object^  sender, System::EventArgs^  e) {
		CtLogPlayer logPlayer;
		logPlayer.saveLog();
	}
	private: System::Void btn_ConsoleClear_Click(System::Object^  sender, System::EventArgs^  e) {
		Console::Clear();
	}
	private: System::Void btn_LogPlay_Click(System::Object^  sender, System::EventArgs^  e) {
		DWORD dwThreadId;
		if (m_LogPlayerThread == NULL) {
			EnableWindow(m_SimHWnd, SW_HIDE);
			m_LogPlayerThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)beginLogPlayThread, m_SimHWnd, 0, &dwThreadId);
		}
	}

	private: System::Void btn_CmdLine_Click(System::Object^  sender, System::EventArgs^  e) {
		DWORD dwThreadId;
		m_CmdLineThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)beginCmdLineThread, m_SimHWnd, 0, &dwThreadId);
	}
	private: System::Void btn_paramset_click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_dial_minus_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_DIAL_DOWN);
	}
	private: System::Void btn_dial_minus_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_DIAL_DOWN);
	}
	private: System::Void btn_dial_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_DIAL_FUNC);
	}
	private: System::Void btn_dial_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_DIAL_FUNC);
	}
	private: System::Void btn_dial_plus_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_DIAL_UP);
	}
	private: System::Void btn_dial_plus_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_DIAL_UP);
	}
	private: System::Void btn_variety_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndVarietyFunc(getScreenId(), ID_VAR_FUNC, ID_VAR_FUNC_1, ID_INVALID);
	}
	private: System::Void btn_variety2_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndVarietyFunc(getScreenId(), ID_VAR_FUNC, ID_VAR_FUNC_2, ID_INVALID);
	}
	private: System::Void btn_variety3_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndVarietyFunc(getScreenId(), ID_VAR_FUNC, ID_VAR_FUNC_3, ID_INVALID);
	}
	private: System::Void btn_variety4_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndVarietyFunc(getScreenId(), ID_VAR_FUNC, ID_VAR_FUNC_4, ID_INVALID);
	}
	private: System::Void btn_Variety5_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndVarietyFunc(getScreenId(), ID_VAR_FUNC, ID_VAR_FUNC_5, ID_INVALID);
	}
	private: System::Void btn_variety6_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndVarietyFunc(getScreenId(), ID_VAR_FUNC, ID_VAR_FUNC_6, ID_INVALID);
	}
	private: System::Void btn_variety7_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndVarietyFunc(getScreenId(), ID_VAR_FUNC, ID_VAR_FUNC_7, ID_INVALID);
	}
	private: System::Void btn_variety8_Click(System::Object^  sender, System::EventArgs^  e) {
		m_dbgCmd->rqCmndVarietyFunc(getScreenId(), ID_VAR_FUNC, ID_VAR_FUNC_8, ID_INVALID);
	}
	private: System::Void chk_Dial_Enter_CheckedChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btn_saveSetting_Click(System::Object^  sender, System::EventArgs^  e) {
		saveSetting();
	}
	private: System::Void button_Info_Mode_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(true, getKeySource(), ID_KEY_DISP_MODE);
	}
	private: System::Void button_Info_Mode_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		VirtualMovieKey(false, getKeySource(), ID_KEY_DISP_MODE);
	}
	private: System::Void treeV_Widget_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
	private: System::Void treeV_Widget_NodeMouseClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e);

};
}
