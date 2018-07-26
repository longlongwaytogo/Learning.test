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


// ������ģ��
osg::ref_ptr<osg::Node> createShape()
{
	// ��������
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	float radius = 0.08f;
	float height = 0.1f;
	osg::TessellationHints* hints = new osg::TessellationHints;
	hints->setDetailRatio(0.5f);
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius), hints));
	return geode.release();
}
// ������Ⱦ�������
osg::Camera* createCamera(int x, int y, int w, int h)
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	 // ����һ��Ƕ�봰�ڵı�����ֻҪ���д��ڱ���ʹ�ô˶����������
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = false;// �Ƿ���ʾ���ڵ�������Ĭ��Ϊfalse����ʾ 
	traits->x = x;	// ������ʾ��x����
	traits->y = y;	// ������ʾ��y����
	traits->width = w;	// ���ô��ڵĿ��
	traits->height = h;	// ���ô��ڵĸ߶�
	traits->doubleBuffer = true;	// �����µ�ͼ�δ����Ƿ�ʹ��˫�������� 
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	// ����ͼ����ϵͳ�ĳ����ӿڣ����ṩ��ͳһ��ͼ���豸��������������ʵ����Ⱦ����͵ײ��豸�Ľ���
	camera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
	// ������Ⱦ�����ɫ
	camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
	// ͼ��������õ�ǰ�ӿ�
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	// ��ʶ���������������ϵ�µ�λ��
	camera->setProjectionMatrixAsPerspective(
		30.0f, static_cast<double>(traits->width) /	static_cast<double>(traits->height), 1.0f, 10000.0f);
	return camera.release();
}

class ViewerWidget : public QWidget
{
public:
	ViewerWidget(osg::Camera* camera, osg::Group* scene)
	{
		_viewer.setCamera(camera);   // �������ӵ���Ⱦ����
		_viewer.setSceneData(scene); // ��ģ����ӵ���Ⱦ����
		_viewer.addEventHandler(new osgViewer::StatsHandler);
		// �����Ǵ�������Ⱦ����һЩ����
		_viewer.setCameraManipulator(new osgGA::TrackballManipulator);
		_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);// ����Ϊ���߳� ,���߳�ִ��ʧ�� 
		_viewer.addEventHandler(new osgGA::StateSetManipulator(_viewer.getCamera()->getOrCreateStateSet()));
		// ���ڴ�С�仯�¼�
		_viewer.addEventHandler(new osgViewer::WindowSizeHandler);
		// ���һЩ����״̬����
		_viewer.addEventHandler(new osgViewer::StatsHandler);
		// ��ʵ˵gw����Ҫ��ʾ�Ĵ���
		osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(camera->getGraphicsContext());
		if (gw)
		{
			QVBoxLayout* layout = new QVBoxLayout;
			layout->addWidget(gw->getGLWidget());
			setLayout(layout);
		}
		connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
		_timer.start(2);// ������ʱ�������źź���Ӧ�Ĳۺ���
	}

protected:
	virtual void paintEvent(QPaintEvent* event)
	{
		_viewer.frame();//ʵʱ������Ⱦ
	} 
	osgViewer::Viewer _viewer;//����һ����Ⱦ��
	QTimer _timer;//����һ����ʱ��
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