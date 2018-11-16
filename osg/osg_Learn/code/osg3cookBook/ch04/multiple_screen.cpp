#include <osg/Camera>
#include <osg/Group>
#include <osg/GraphicsContext>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/CompositeViewer>

unsigned int defaultW = 800;
unsigned int defaultH = 600;

class ReStoreResolution
{

public:
    ReStoreResolution()
    {

    }
    ~ReStoreResolution()
    {
        osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
        if(wsi)
        {
           
            int numscreen = wsi->getNumScreens();
            for(int i = 0; i< numscreen; ++i)
                wsi->setScreenResolution(osg::GraphicsContext::ScreenIdentifier(i),defaultW,defaultH);
        }
    }
};
ReStoreResolution s_restore;

osgViewer::View* createView(int num)
{
    int width = 1920, height = 1440;
	osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
    if(wsi)
    {
        wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(num),defaultW,defaultH);
        wsi->setScreenResolution(osg::GraphicsContext::ScreenIdentifier(num),width,height);
    }

    osg::ref_ptr<osg::GraphicsContext::Traits> ts = new osg::GraphicsContext::Traits();
    ts->screenNum = num;
    ts->doubleBuffer = true;
    ts->windowDecoration = false;
    ts->sharedContext = 0;
    ts->width = width;
    ts->height = height;

    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(ts.get());
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setViewport(0,0,width,height);
    camera->setProjectionMatrixAsPerspective(30.0,GLdouble(width)/GLdouble(height),1.0,1000);
    camera->setGraphicsContext(gc.get());
    GLenum buffer = ts->doubleBuffer ? GL_BACK : GL_FRONT;
    camera->setReadBuffer(buffer);
    camera->setDrawBuffer(buffer);

    osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
    view->setCamera(camera);
    view->setCameraManipulator(new osgGA::TrackballManipulator());
    return view.release();
}


void main()
{
	osgViewer::CompositeViewer viewer;
	
	{
		osgViewer::View* view1 = createView(0);
		view1->setSceneData(osgDB::readNodeFile("cow.osg"));
		viewer.addView(view1);
	}
	
	/*{
		osgViewer::View* view2 = createView(1);
		view2->setSceneData(osgDB::readNodeFile("cessna.osg"));
		viewer.addView(view2);
	}*/
	
	viewer.run();
	
}