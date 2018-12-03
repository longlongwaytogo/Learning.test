#include <osg/Geometry>
#include <osg/Vec3>
#include <osg/Vec2>
#include <osg/Geometry>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osg/State>

#include <comm/comm.h>

#include <iostream>

#define COMPRESS_IMAGE 1

osg::Node* createQuad(int row ,int colum);

osg::Image* createImage(int w, int h);

void main()
{
	osg::Group* root = new osg::Group;
	
    int row = 20;
    int colum = 20;

	root->addChild(createQuad(row,colum));

	
	osgViewer::Viewer viewer;
	viewer.setSceneData(root);
    viewer.addEventHandler(new osgViewer::StatsHandler());
    // add the state manipulator
    viewer.addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );
	viewer.run();

}

osg::Image* createImage(int w, int h)
{
    osg::ref_ptr<osg::Image> image = new osg::Image;
    image->allocateImage(w,h,1,GL_RGB,GL_UNSIGNED_BYTE);
    unsigned char* data = image->data();
#if 1
   
    for(int i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
        {
            data[3*(i * h + j) + 0] = osgComm::RandValue(0.0,255.0);
            data[3*(i * h + j)+ 1] = osgComm::RandValue(0.0,255.0);
            data[3*(i * h + j) + 2] = osgComm::RandValue(0.0,255.0);

        }
    }

    
#else 
   
    for ( int y=0; y<h; ++y )
    {
        for ( int x=0; x<w; ++x )
        {
            *(data++) = osgComm::RandValue(0.0f, 255.0f);
            *(data++) = osgComm::RandValue(0.0f, 255.0f);
            *(data++) = osgComm::RandValue(0.0f, 255.0f);
        }
    }
#endif 
    return image.release();

}
osg::Node* createQuad(int row ,int colum)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	
   
	for(int x = 0; x < row; ++x)
	{
		for(int y = 0; y < colum; ++y)
		{
            osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
            tex->setImage(createImage(512,512));
            tex->setFilter(osg::Texture::MIN_FILTER,osg::Texture::NEAREST);
            tex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
            tex->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT);
            tex->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT);

#if COMPRESS_IMAGE
            tex->setInternalFormatMode(osg::Texture::USE_S3TC_DXT3_COMPRESSION);
            tex->setUnRefImageDataAfterApply(true);
#endif 
			osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
			osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array(4); //vertices
			osg::ref_ptr<osg::Vec3Array> na = new osg::Vec3Array(1);
			osg::ref_ptr<osg::Vec3Array> ca = new osg::Vec3Array(1);
			osg::ref_ptr<osg::Vec2Array> ta = new osg::Vec2Array(4);
			osg::Vec3 center(10*x,0,10*y);
			(*va)[0] = center + osg::Vec3(-10.45,0,-10.45);
			(*va)[1] = center + osg::Vec3( 10.45,0,-10.45);
			(*va)[2] = center + osg::Vec3( 10.45,0, 10.45);
			(*va)[3] = center + osg::Vec3(-10.45,0, 10.45);
			
			(*ta)[0] = osg::Vec2( -0.5, -0.5);
			(*ta)[1] = osg::Vec2(  0.5, -0.5);
			(*ta)[2] = osg::Vec2(  0.5,  0.5);
			(*ta)[3] = osg::Vec2( -0.5,  0.5);
		 
			
			(*na)[0] = osg::Vec3(0,-1,0);
			
			geom->setVertexArray(va.get());
			geom->setNormalArray(na.get());
			
			geom->setTexCoordArray(0,ta.get());
			geom->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);
			
			geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));
            geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,tex.get(),osg::StateAttribute::ON);
			geode->addDrawable(geom.get());	
		}
	}
	
	return geode.release();
}
