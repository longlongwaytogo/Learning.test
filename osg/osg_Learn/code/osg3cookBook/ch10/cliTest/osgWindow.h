#pragma once

namespace cliTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// osgWindow ժҪ
	/// </summary>
	public ref class osgWindow : public System::Windows::Forms::Form
	{
	public:
		osgWindow(void)
		{
			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
			//
		}

        void runThread();
        void initializeOSG();

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
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
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
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
