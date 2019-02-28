
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <osgQt/GraphicsWindowQt>
#include <QVBoxLayout>
#include <QApplication>

// 创建qt图形窗口
osg::Camera* createGraphicsWindow(int x, int y, int w, int h)
{
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = false;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	
	//return new osgQt::GraphicsWindowQt(traits.get());
    osg::Camera* camera = new osg::Camera;
    camera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
    // 设置渲染器清除色
    camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
    // 图形输出设置当前视口
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    // 标识摄像机在世界坐标系下的位置
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0f, 10000.0f);

    return camera;

}

//// 创建QtWidget视口
class ViewerWidget: public QWidget
{
public:
    ViewerWidget(osg::Camera* camera, osg::Node* scene):QWidget()
    {
        _viewer.setCamera(camera);
        _viewer.setSceneData(scene);
        _viewer.addEventHandler(new osgViewer::StatsHandler);
        _viewer.setCameraManipulator(new osgGA::TrackballManipulator);
        _viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);

        QVBoxLayout* layout = new QVBoxLayout;

        osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(camera->getGraphicsContext());
        if (gw)
        {
            QVBoxLayout* layout = new QVBoxLayout;
            layout->addWidget(gw->getGLWidget());
            setLayout(layout);
        }
        connect(&_timer, SIGNAL(timeout()),this,SLOT(update()));
        _timer.start(40);

    }
protected:
    virtual void paintEvent(QPaintEvent* event)
    {
        _viewer.frame();
    }

    osgViewer::Viewer _viewer;
    QTimer _timer;
};

int main(int argc, char** argv)
{
	
	QApplication app(argc,argv);
	osg::Camera* camera = createGraphicsWindow(50,50,640,480);

	osg::Node* scene = osgDB::readNodeFile("cow.osg");
	ViewerWidget* widget = new ViewerWidget(camera, scene);
	widget->setGeometry(100,100,800,600);
	widget->show();
	return app.exec();
	
}