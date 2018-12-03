#include <osg/Texture>
#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgUtil/PrintVisitor>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>


#include "comm/comm.h"

int main(int argc, char** argv)
{
	osg::ArgumentParser arguments(&argc,argv);
	
	osg::ref_ptr<osg::Node> root = osgDB::readNodeFiles(arguments);
	osg::Texture::getTextureObjectManager(0)->setMaxTexturePoolSize(64000);
	
	osgViewer::Viewer viewer;
    viewer.setUpViewInWindow(100,100,1024,768);

	
	osgDB::DatabasePager* pager = viewer.getDatabasePager();
	pager->setDoPreCompile(true);
	pager->setTargetMaximumNumberOfPageLOD(10);
	
	viewer.setSceneData(root.get());
	viewer.addEventHandler(new osgViewer::StatsHandler);
	
	return viewer.run();
	
	

}