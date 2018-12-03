#include <osg/Geometry>
#include <osg/Vec3>
#include <osg/Geometry>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osg/State>

#include <comm/comm.h>

#include <iostream>
#define MERGE_GEOMETRY 1

#define USE_DISPLAYLIST 1


osg::Node* createTiles(int row ,int colum);

osg::Node* createTiles_merge(int row, int colum);

void main()
{
	osg::Group* root = new osg::Group;
	
    int row = 140;
    int colum = 140;

	#if MERGE_GEOMETRY 
	root->addChild(createTiles_merge(row,colum));
	#else 
		root->addChild(createTiles(row,colum));
	#endif
	
	osgViewer::Viewer viewer;
	viewer.setSceneData(root);
    viewer.addEventHandler(new osgViewer::StatsHandler());
    /*viewer.addEventHandler(new osgViewer::KeystoneHandler);*/
    // add the state manipulator
    viewer.addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );
	viewer.run();

}

osg::Node* createTiles(int row ,int colum)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	
	for(int x = 0; x < row; ++x)
	{
		for(int y = 0; y < colum; ++y)
		{
			osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
			osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array(4); //vertices
			osg::ref_ptr<osg::Vec3Array> na = new osg::Vec3Array(1);
			osg::ref_ptr<osg::Vec3Array> ca = new osg::Vec3Array(1);
			osg::Vec3 center(x,0,y);
			(*va)[0] = center + osg::Vec3(-0.45,0,-0.45);
			(*va)[1] = center + osg::Vec3( 0.45,0,-0.45);
			(*va)[2] = center + osg::Vec3( 0.45,0, 0.45);
			(*va)[3] = center + osg::Vec3(-0.45,0, 0.45);
			
			(*ca)[0] = osgComm::RandVector(0.0,1.0);
			(*na)[0] = osg::Vec3(0,-1,0);
			
			geom->setVertexArray(va.get());
			geom->setNormalArray(na.get());
			geom->setColorArray(ca.get());
			geom->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
			geom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
			geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));
			geode->addDrawable(geom.get());
#if  USE_DISPLAYLIST
#else
            geom->setUseDisplayList(false);
            geom->setUseVertexBufferObjects(true);
#endif 		
		}
	}
	
	return geode.release();
}

osg::Node* createTiles_merge(int row, int colum)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array(4 * row * colum); //vertices
	osg::ref_ptr<osg::Vec3Array> na = new osg::Vec3Array(row * colum);
	osg::ref_ptr<osg::Vec3Array> ca = new osg::Vec3Array( row * colum);

    

    geom->setVertexArray(va.get());
    geom->setNormalArray(na.get());
    geom->setColorArray(ca.get());
    geom->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
    geom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);

    int index_ = 0;
	for(int x = 0; x < row; ++x)
	{
		for(int y = 0; y < colum; ++y)
		{
			osg::Vec3 center(float(x),0,float(y));
            
            int index = x * colum + y;
           // std::cout << index <<",index_1:" << index_ << std::endl;
            index_++;
            (*va)[index* 4 + 0] = center + osg::Vec3(-0.45,0,-0.45);
            (*va)[index* 4 + 1] = center + osg::Vec3( 0.45,0,-0.45);
            (*va)[index* 4 + 2] = center + osg::Vec3( 0.45,0, 0.45);
            (*va)[index* 4 + 3] = center + osg::Vec3(-0.45,0, 0.45);
			(*na)[index] = osg::Vec3(0,-1,0);
			(*ca)[ index] = osgComm::RandVector(0.0,1.0);
			
			geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,index * 4,4));
#if  USE_DISPLAYLIST
#else
            geom->setUseDisplayList(false);
            geom->setUseVertexBufferObjects(true);
#endif 		
		}
	}
	geode->addDrawable(geom.get());
	return geode.release();
}