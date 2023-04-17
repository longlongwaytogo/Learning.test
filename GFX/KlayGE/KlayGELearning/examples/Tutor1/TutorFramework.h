// http://www.klayge.org/wiki/index.php/Tutor1_-_%E6%9E%84%E5%BB%BA%E8%87%AA%E5%B7%B1%E7%9A%84%E5%BA%94%E7%94%A8%E7%A8%8B%E5%BA%8F%E6%A1%86%E6%9E%B6
#include <KlayGE/KlayGE.hpp>
#include <KlayGE/App3D.hpp>
#include <KlayGE/ResLoader.hpp>
#include <KlayGE/Context.hpp>
#include <KlayGE/Font.hpp>
#include <KlayGE/RenderEngine.hpp>
#include <KlayGE/RenderFactory.hpp>
#include <KlayGE/FrameBuffer.hpp>
#include <KlayGE/UI.hpp>

#include <vector>
#include <sstream>

class TutorFramework : public KlayGE::App3DFramework
{
public:
	TutorFramework();
private:
	//virtual void InitObjects();
	virtual void OnCreate();
private:
	virtual void DoUpdateOverlay();
	virtual KlayGE::uint32_t DoUpdate(KlayGE::uint32_t pass);
	
	KlayGE::FontPtr font_;
};
