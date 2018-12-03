#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgUtil/DelaunayTriangulator>
#include <osgViewer/Viewer>
#include <osgUtil/DelaunayTriangulator>
#include <osgGA/StateSetManipulator>



int main( int argc, char** argv)
{
	osg::ref_ptr<osg::Group> root = new osg::Group;
	
	 osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array(9);
    (*va)[0].set(-5.0f,-5.0f, 0.4f);
    (*va)[1].set( 1.0f,-5.6f, 0.0f);
    (*va)[2].set( 5.0f,-4.0f,-0.5f);
    (*va)[3].set(-6.2f, 0.0f, 4.2f);
    (*va)[4].set(-1.0f,-0.5f, 4.8f);
    (*va)[5].set( 4.3f, 1.0f, 3.0f);
    (*va)[6].set(-4.8f, 5.4f, 0.3f);
    (*va)[7].set( 0.6f, 5.1f,-0.8f);
    (*va)[8].set( 5.2f, 4.5f, 0.1f);
	
	osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = new osgUtil::DelaunayTriangulator;
	dt->setInputPointArray(va.get());
	dt->setOutputNormalArray(new osg::Vec3Array());
	dt->triangulate();
	
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
	geometry->setVertexArray(dt->getInputPointArray());
	geometry->setNormalArray(dt->getOutputNormalArray());
	geometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	geometry->addPrimitiveSet(dt->getTriangles());
	osg::ref_ptr<osg::Geode> geode= new osg::Geode;
	geode->addDrawable(geometry.get());
	
	root->addChild(geode.get());
	
	
	osgViewer::Viewer viewer;
    viewer.addEventHandler(new osgGA::StateSetManipulator( viewer.getCamera()->getStateSet()));
	viewer.setSceneData(root.get());
    viewer.run();


	return  0;
}
