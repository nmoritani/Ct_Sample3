#pragma once
#include <resource.h>
#include <windows.h>
#include <stdio.h>
namespace simulator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Logo の概要
	/// </summary>
	public ref class Logo : public System::Windows::Forms::Form
	{
	public:
		Logo(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//m_Hwnd = reinterpret_cast<HWND>(this->Handle.ToPointer());
			//Process.GetCurrentProcess()
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~Logo()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::ComponentModel::IContainer^  components;
	public: virtual Void Logo::ShowDialog() {
		m_Hwnd  = static_cast<HWND>(this->Handle.ToPointer());
		SetTimer(m_Hwnd, IDC_TIMER_LOGO, 2500, NULL);
		Form::ShowDialog();
	}
	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Logo::typeid));
			this->SuspendLayout();
			// 
			// Logo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size(511, 261);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Logo";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Logo";
			this->TopMost = true;
			this->ResumeLayout(false);

		}
		HWND m_Hwnd;
	public:
		virtual Void Logo::WndProc(System::Windows::Forms::Message% msg) override {
			switch (msg.Msg) {
			case WM_TIMER:
			{
				if (msg.WParam == (IntPtr)IDC_TIMER_LOGO) {
					Hide();
					KillTimer(m_Hwnd, IDC_TIMER_LOGO);
				}
			}
			default:
				break;
			}
			Form::WndProc(msg);
		}
	};
#pragma endregion
}
