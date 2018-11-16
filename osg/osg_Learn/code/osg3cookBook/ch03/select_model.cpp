// select_model.cpp
#include <osg/Group>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osg/MatrixTransform>
#include <osg/Matrix>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/SmoothingVisitor>
#include "comm/comm.h"
#include <osgFX/Cartoon>

const osg::Vec4 normalColor(1.0f, 1.0f, 1.0f, 1.0f);
const osg::Vec4 selectedColor(1.0f, 0.0f, 0.0f, 0.5f);

class SelectPicker :public osgComm::PickHandler
{
	public:
	virtual void doUserOperations(const osgUtil::LineSegmentIntersector::Intersection& in)
	{
		osg::Geometry* geometry = dynamic_cast<osg::Geometry*>(in.drawable.get());
        if(geometry == _lastSelected)
        {
            return ;
        }
        else if(geometry != NULL)
        {
            setSelectColor(_lastSelected.get(),normalColor);
            setSelectColor(geometry,selectedColor);
            _lastSelected = geometry;
        }
        else
        {

        }
	}

    void setSelectColor(osg::Geometry* geometry,const osg::Vec4& color)
    {
        if(!geometry) return;
        osg::Vec4Array* colors = static_cast<osg::Vec4Array*>(geometry->getColorArray());
        if(colors && colors->size()>0)
        {

            colors->front() = color;
            colors->dirty();
        }
    }
private:
    osg::ref_ptr<osg::Geometry> _lastSelected;
};

osg::Geometry* createSimpleGeometry()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(8);
    (*vertices)[0].set(-0.5f,-0.5f,-0.5f);
    (*vertices)[1].set( 0.5f,-0.5f,-0.5f);
    (*vertices)[2].set( 0.5f, 0.5f,-0.5f);
    (*vertices)[3].set(-0.5f, 0.5f,-0.5f);
    (*vertices)[4].set(-0.5f,-0.5f, 0.5f);
    (*vertices)[5].set( 0.5f,-0.5f, 0.5f);
    (*vertices)[6].set( 0.5f, 0.5f, 0.5f);
    (*vertices)[7].set(-0.5f, 0.5f, 0.5f);

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(1);
    (*colors)[0] = normalColor;

    osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_QUADS, 24);
    (*indices)[0] = 0; (*indices)[1] = 1; (*indices)[2] = 2; (*indices)[3] = 3;
    (*indices)[4] = 4; (*indices)[5] = 5; (*indices)[6] = 6; (*indices)[7] = 7;
    (*indices)[8] = 0; (*indices)[9] = 1; (*indices)[10]= 5; (*indices)[11]= 4;
    (*indices)[12]= 1; (*indices)[13]= 2; (*indices)[14]= 6; (*indices)[15]= 5;
    (*indices)[16]= 2; (*indices)[17]= 3; (*indices)[18]= 7; (*indices)[19]= 6;
    (*indices)[20]= 3; (*indices)[21]= 0; (*indices)[22]= 4; (*indices)[23]= 7;

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setDataVariance( osg::Object::DYNAMIC );
    geom->setUseDisplayList( false );
    geom->setUseVertexBufferObjects( true );
    geom->setVertexArray( vertices.get() );
    geom->setColorArray( colors.get() );
    geom->setColorBinding( osg::Geometry::BIND_OVERALL );
    geom->addPrimitiveSet( indices.get() );

    osgUtil::SmoothingVisitor::smooth( *geom );
    return geom.release();
}

void main()
{
	osg::ref_ptr<osg::Group> root = new osg::Group;
	
    osg::Geode* geode = new osg::Geode;
    osg::ref_ptr<osg::Geometry> geometry = createSimpleGeometry();

    geode->getOrCreateStateSet()->setMode( GL_BLEND, osg::StateAttribute::ON );
    geode->getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    geode->addDrawable(geometry);

	osg::MatrixTransform* trans1 = new osg::MatrixTransform;
	osg::MatrixTransform* trans2 = new osg::MatrixTransform;
	
	trans1->addChild(geode);
	trans2->addChild(static_cast<osg::Node*>(geode->clone(osg::CopyOp::DEEP_COPY_ALL)));
	
	trans1->setMatrix(osg::Matrix::translate(osg::Vec3(-3,0,0)));
	trans2->setMatrix(osg::Matrix::translate(osg::Vec3( 3,0,0)));
    root->addChild(trans1);
	root->addChild(trans2);
	
	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
    viewer.addEventHandler(new SelectPicker());
	viewer.run();
}