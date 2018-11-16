#include <osg/Camera>
#include <osg/Group>
#include <osg/GraphicsContext>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
 
 
 
osg::Camera* createSlaveCamera(int x, int y, int width, int height)
{
 
    osg::ref_ptr<osg::GraphicsContext::Traits> ts = new osg::GraphicsContext::Traits();
    ts->screenNum = 0;
    ts->x = x;
    ts->y = y;
    ts->doubleBuffer = true;
    ts->windowDecoration = false;
    ts->sharedContext = 0;
    ts->width = width;
    ts->height = height;

    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(ts.get());
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setViewport(0,0,width,height);
    camera->setProjectionMatrixAsPerspective(30.0,GLdouble(width )/GLdouble(height),1.0,1000);
    camera->setGraphicsContext(gc.get());
    GLenum buffer = ts->doubleBuffer ? GL_BACK : GL_FRONT;
    camera->setReadBuffer(buffer);
    camera->setDrawBuffer(buffer);

    return camera.release();
}


void main(int argc, char** argv)
{
	int totalWidth = 1024;
	int totalHeight = 768;
	osg::ArgumentParser arguments(&argc, argv);
	arguments.read("--total-width", totalWidth);
	arguments.read("--total-height", totalHeight);
	
	int numColums = 3; 
	int numRows = 3;
	
	arguments.read("--num-colums",numColums);
	arguments.read("--num-rows", numRows);
	
	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile("cessna.osg");
	
	osgViewer::Viewer viewer;

	int tileWidth = totalWidth / numColums;
	int tileHeight = totalHeight / numRows;
	
	for(int i = 0; i < numColums; ++i)
	{
		for(int j = 0; j < numRows; ++j)
		{
			osg::Camera* camera = createSlaveCamera(
			tileWidth*j, totalHeight - tileHeight*(1+i),tileWidth-1,tileHeight-1);
			
			osg::Matrix projoffset = 
			osg::Matrix::scale(numColums,numRows,1.0) * 
			osg::Matrix::translate(numColums- 1- 2*j, numRows - 1- 2*i,0.0);
			viewer.addSlave(camera,projoffset,osg::Matrix(),true);
		}
	}
	
	viewer.setSceneData(scene);	
	viewer.run();
	
}