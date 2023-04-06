#include "TutorFramework.h"

#include <iostream>
int main()
{
    std::string klaygePath = KLAYGE_ROOT;
    std::string klaygebinraryPath = KLAYGE_BINARY_ROOT;

    // 从KlayGE.cfg中读取配置信息。各个功能模块，诸如RenderFactory，AudioFactory等都会在这一过程中被初始化
    KlayGE::Context::Instance().LoadCfg(klaygebinraryPath + "./../KlayGE.cfg");

	KlayGE::ResLoader::Instance().AddPath(klaygePath +"/KlayGE/Samples/Media/Common");
	KlayGE::ResLoader::Instance().AddPath(klaygePath +"/KlayGE/Samples/Media");

    TutorFramework app;
    app.Create();
    app.Run();
	return 0;
}