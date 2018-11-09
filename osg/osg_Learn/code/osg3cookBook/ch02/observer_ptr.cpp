#include <iostream>
#include <string>

#include <osg/Group>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osg/NodeCallback>


#include "comm/comm.h"

class RemoveShapeHandler :public osgComm::PickHander
{
 
    virtual void doUserOperations(const osgUtil::LineSegmentIntersector::Intersection& in)
    {
        if(in.nodePath.size() > 0)
        {
            osg::Geode* geode = dynamic_cast<osg::Geode*>(in.nodePath.back());
            if(geode)
            {
                geode->removeDrawable(in.drawable.get());
            }
        }
    }
};

class ObserveShapeCallback: public osg::NodeCallback
{
public:
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        std::string content;
        if(_drawable1.valid()) content += "Drawable 1;";
        if(_drawable2.valid()) content += "Drawable 2;";
        if(_text.valid()) _text->setText(content);
		
  		traverse(node, nv);
    }

    osg::observer_ptr<osg::Drawable> _drawable1;
    osg::observer_ptr<osg::Drawable> _drawable2;
    osg::observer_ptr<osgText::Text> _text;

};


void main()
{

    std::cout << "start osg!" << std::endl;

    osg::ref_ptr<osgText::Font> font = osgText::readFontFile("fonts/arial.ttf");
    osg::ref_ptr<osgText::Text> text = osgComm::createText(osg::Vec3(50.0f,50.0f,0.0f),font,"",10.0f);
    osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
	textGeode->addDrawable(text.get());

	osg::ref_ptr<osg::Camera> hudCamera = osgComm::createHudCamera(0,800,0,600);
	hudCamera->addChild(textGeode.get());
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( new osg::ShapeDrawable( new osg::Box(osg::Vec3(-2.0f,0.0f,0.0f),1.0f)));
    geode->addDrawable( new osg::ShapeDrawable( new osg::Sphere(osg::Vec3(2.0f, 0.0f,0.0f),1.0f)));

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(geode);
    root->addChild(hudCamera);

    osg::ref_ptr<ObserveShapeCallback> callback = new ObserveShapeCallback();
    callback->_text = text;
    callback->_drawable1 = geode->getDrawable(0);
    callback->_drawable2 = geode->getDrawable(1);

    root->setUpdateCallback(callback.get());

    osgViewer::Viewer viewer;
    viewer.setUpViewInWindow(0,0,800,600);
    viewer.setSceneData(root);
    viewer.addEventHandler( new RemoveShapeHandler);
    viewer.realize();
    viewer.run();

}