#include "TutorFramework.h"

TutorFramework::TutorFramework()
    : App3DFramework("Tutor1")
{
}

void TutorFramework::OnCreate()
{
    font_ = KlayGE::SyncLoadFont("gkai00mp.kfont");
}

void TutorFramework::DoUpdateOverlay()
{
    // ����ǰ��FPS��Ϣ������ַ����У��Ա���Ⱦ����Ļ��
    std::wostringstream stream;
    stream.precision(2);
    stream << std::fixed << this->FPS() << " FPS";

    // ʹ��֮ǰ����������������Ⱦ�ı���Ϣ��RenderText()���Խ��ܵĲ���������
    // X��Yλ�ã�KlayGE::Color��ɫ��std::wstring���͵��ַ������Լ������С
    font_->RenderText(0, 0, KlayGE::Color(1, 1, 0, 1), L"�Զ���������", 16);
    font_->RenderText(0, 18, KlayGE::Color(1, 1, 0, 1), stream.str(), 16);
}

KlayGE::uint32_t TutorFramework::DoUpdate(KlayGE::uint32_t pass)
{
    // ��ȡ��Ⱦ������󡣸���KlayGE.cfg�ļ����������ݣ�������ͨ��OpenGL����D3D11��ʵ��
    KlayGE::RenderEngine& re = KlayGE::Context::Instance().RenderFactoryInstance().RenderEngineInstance();
    re.CurFrameBuffer()->Clear(KlayGE::FrameBuffer::CBM_Color | KlayGE::FrameBuffer::CBM_Depth,
        KlayGE::Color(0.2f, 0.4f, 0.6f, 1), 1.0f, 0);

    KlayGE::Color clear_clr(0.2f, 0.4f, 0.6f, 1);
    if (KlayGE::Context::Instance().Config().graphics_cfg.gamma)
    {
        clear_clr.r() = 0.029f;
        clear_clr.g() = 0.133f;
        clear_clr.b() = 0.325f;
    }
    re.CurFrameBuffer()->Clear(KlayGE::FrameBuffer::CBM_Color | KlayGE::FrameBuffer::CBM_Depth, clear_clr, 1.0f, 0);
    return KlayGE::App3DFramework::URV_NeedFlush | KlayGE::App3DFramework::URV_Finished;
}
