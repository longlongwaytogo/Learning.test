//http://www.klayge.org/wiki/index.php/Tutor2_-_%E6%B8%B2%E6%9F%93%E5%87%A0%E4%BD%95%E4%BD%93%E6%95%B0%E6%8D%AE
#include <KlayGE/KlayGE.hpp>
#include <KlayGE/App3D.hpp>
#include <KlayGE/ResLoader.hpp>
#include <KlayGE/Context.hpp>
#include <KlayGE/Font.hpp>
#include <KlayGE/RenderableHelper.hpp>
#include <KlayGE/RenderEngine.hpp>
#include <KlayGE/RenderFactory.hpp>
#include <KlayGE/FrameBuffer.hpp>
#include <KlayGE/SceneManager.hpp>
#include <KlayGE/SceneNode.hpp>
#include <KlayGE/Mesh.hpp>
#include <KlayGE/CameraController.hpp>
#include <KlayGE/RenderEffect.hpp>
#include <KlayGE/Camera.hpp>

#include <vector>
#include <sstream>

class TutorFramework : public KlayGE::App3DFramework
{
public:
	TutorFramework();
protected:
	virtual void OnCreate();
private:
	virtual void DoUpdateOverlay();
	virtual KlayGE::uint32_t DoUpdate(KlayGE::uint32_t pass);

	KlayGE::TrackballCameraController tbController_;// 使用轨迹球控制器来控制相机，浏览场景
	KlayGE::FontPtr font_;
	// 使用SceneObjectHelper来管理场景中的对象
	KlayGE::SceneNodePtr renderableBox_;
	KlayGE::SceneNodePtr renderableFile_;
	KlayGE::SceneNodePtr renderableMesh_;
	KlayGE::SceneNodePtr renderableAxis_;
};
//从静态网格模型StaticMesh派生得到一个用户类，用于构建来自顶点数据或者文件的几何体对象：
class RenderPolygon : public KlayGE::StaticMesh
{
public:
	explicit RenderPolygon(std::wstring_view name);
	void DoBuildMeshInfo(KlayGE::RenderModel const& model) override;
};

//从静态网格模型StaticMesh派生得到一个用户类，用于构建来自顶点数据或者文件的几何体对象：
class RenderLine : public KlayGE::StaticMesh
{
public:
	explicit RenderLine(std::wstring_view name);
	void DoBuildMeshInfo(KlayGE::RenderModel const& model) override;
};