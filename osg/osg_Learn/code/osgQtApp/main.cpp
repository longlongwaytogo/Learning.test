#include <iostream>

#include <QtCore>
#include <QtWidgets>
#include <QGLWidget>
#include <QApplication>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osgDB/ReadFile>
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>


// 创建球模型
osg::ref_ptr<osg::Node> createShape()
{
	// 几何组结点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	float radius = 0.08f;
	float height = 0.1f;
	osg::TessellationHints* hints = new osg::TessellationHints;
	hints->setDetailRatio(0.5f);
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius), hints));
	return geode.release();
}
// 创建渲染器的相机
osg::Camera* createCamera(int x, int y, int w, int h)
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	 // 声明一个嵌入窗口的变量，只要是有窗口必须使用此对象进行设置
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = false;// 是否显示窗口的描述，默认为false不显示 
	traits->x = x;	// 设置显示的x坐标
	traits->y = y;	// 设置显示的y坐标
	traits->width = w;	// 设置窗口的宽度
	traits->height = h;	// 设置窗口的高度
	traits->doubleBuffer = true;	// 创建新的图形窗口是否使用双缓冲特性 
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	// 任意图形子系统的抽象层接口，它提供了统一的图形设备操作函数，用来实现渲染结果和底层设备的交互
	camera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
	// 设置渲染器清除色
	camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
	// 图形输出设置当前视口
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	// 标识摄像机在世界坐标系下的位置
	camera->setProjectionMatrixAsPerspective(
		30.0f, static_cast<double>(traits->width) /	static_cast<double>(traits->height), 1.0f, 10000.0f);
	return camera.release();
}

class ViewerWidget : public QWidget
{
public:
	ViewerWidget(osg::Camera* camera, osg::Group* scene)
	{
		_viewer.setCamera(camera);   // 将相机添加到渲染器中
		_viewer.setSceneData(scene); // 将模型添加到渲染器中
		_viewer.addEventHandler(new osgViewer::StatsHandler);
		// 以下是创建了渲染器的一些操作
		_viewer.setCameraManipulator(new osgGA::TrackballManipulator);
		_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);// 创建为单线程 ,多线程执行失败 
		_viewer.addEventHandler(new osgGA::StateSetManipulator(_viewer.getCamera()->getOrCreateStateSet()));
		// 窗口大小变化事件
		_viewer.addEventHandler(new osgViewer::WindowSizeHandler);
		// 添加一些常用状态设置
		_viewer.addEventHandler(new osgViewer::StatsHandler);
		// 其实说gw就是要显示的窗口
		osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(camera->getGraphicsContext());
		if (gw)
		{
			QVBoxLayout* layout = new QVBoxLayout;
			layout->addWidget(gw->getGLWidget());
			setLayout(layout);
		}
		connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
		_timer.start(2);// 关联定时器计满信号和响应的槽函数
	}

protected:
	virtual void paintEvent(QPaintEvent* event)
	{
		_viewer.frame();//实时进行渲染
	} 
	osgViewer::Viewer _viewer;//创建一个渲染器
	QTimer _timer;//创建一个定时器
};
int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	osg::Camera* camera = createCamera(50, 50, 640, 480);
	osg::Group * scene = new osg::Group();
	scene->addChild(createShape().get());

	ViewerWidget* widget = new ViewerWidget(camera, scene);
	widget->setGeometry(100, 100, 1024, 768);
	widget->show();
	return app.exec();
}