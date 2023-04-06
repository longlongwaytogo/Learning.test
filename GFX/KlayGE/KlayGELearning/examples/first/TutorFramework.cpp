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
    // 将当前的FPS信息输出到字符串中，以备渲染到屏幕上
    std::wostringstream stream;
    stream.precision(2);
    stream << std::fixed << this->FPS() << " FPS";

    // 使用之前构建的新字体来渲染文本信息，RenderText()可以接受的参数包括：
    // X，Y位置，KlayGE::Color颜色，std::wstring类型的字符串，以及字体大小
    font_->RenderText(0, 0, KlayGE::Color(1, 1, 0, 1), L"自定义框架例子", 16);
    font_->RenderText(0, 18, KlayGE::Color(1, 1, 0, 1), stream.str(), 16);
}

KlayGE::uint32_t TutorFramework::DoUpdate(KlayGE::uint32_t pass)
{
    // 获取渲染引擎对象。根据KlayGE.cfg文件的配置内容，它可能通过OpenGL或者D3D11来实现
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
