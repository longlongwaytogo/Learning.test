#include <iostream>
#include <string>

#include <osg/Group>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osg/Geode>
#include <osgDB/ReadFile>



#include "comm/comm.h"

class SetShapeColorHandler :public osgComm::PickHander
{
    virtual void doUserOperations(const osgUtil::LineSegmentIntersector::Intersection& in)
    {
        if(in.nodePath.size() > 0)
        {
            osg::Geode* geode = dynamic_cast<osg::Geode*>(in.nodePath.back());
            if(geode)
            {
                osg::ShapeDrawable* shape = dynamic_cast<osg::ShapeDrawable*>(geode->getDrawable(0));
                if(shape)
                {
                    shape->setColor(osg::Vec4(1.0,1.0,1.0,2.0) - shape->getColor());
                }
            }
        }
    }
};


void main()
{

    std::cout << "start osg!" << std::endl;

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable( new osg::Sphere(osg::Vec3(0.0f, 0.0f,0.0f),1.0f));
    shape->setUseDisplayList(false);
    shape->setDataVariance(osg::Object::DYNAMIC);
    shape->setColor(osg::Vec4(0,0,1,1));
    geode->addDrawable(shape);

    osg::ref_ptr<osg::Geode> geode1 = dynamic_cast<osg::Geode*>(geode->clone(osg::CopyOp::SHALLOW_COPY));
    //osg::ShapeDrawable* shape1 = dynamic_cast<osg::ShapeDrawable*>(geode1->getDrawable(0));
    //shape1->setColor(osg::Vec4(0,0,1,1));

    osg::ref_ptr<osg::Geode> geode2 = dynamic_cast<osg::Geode*>(geode->clone(osg::CopyOp::DEEP_COPY_ALL));
   // osg::ShapeDrawable* shape2 = dynamic_cast<osg::ShapeDrawable*>(geode2->getDrawable(0));
   // shape2->setColor(osg::Vec4(0,0,1,1));

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(osgComm::createTranform(geode,osg::Vec3(0,0,0)));
    root->addChild(osgComm::createTranform(geode1,osg::Vec3(-2,0,0)));
    root->addChild(osgComm::createTranform(geode2,osg::Vec3(2,0,0)));

    osgViewer::Viewer viewer;
    viewer.setUpViewInWindow(0,0,800,600);
    viewer.setSceneData(root);
    viewer.addEventHandler( new SetShapeColorHandler);
    viewer.realize();
    viewer.run();

}