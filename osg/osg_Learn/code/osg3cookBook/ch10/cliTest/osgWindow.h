#pragma once

namespace cliTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// osgWindow 摘要
	/// </summary>
	public ref class osgWindow : public System::Windows::Forms::Form
	{
	public:
		osgWindow(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

        void runThread();
        void initializeOSG();

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~osgWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
            this->SuspendLayout();
            // 
            // osgWindow
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(660, 349);
            this->Name = L"osgWindow";
            this->Text = L"osgWindow";
            this->Load += gcnew System::EventHandler(this, &osgWindow::osgWindow_Load);
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void osgWindow_Load(System::Object^  sender, System::EventArgs^  e) {

                 initializeOSG();
             }
    };

      
}
