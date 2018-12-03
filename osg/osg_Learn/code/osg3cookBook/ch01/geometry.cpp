#include <iostream>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Drawable>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Shape>
void main()
{
    osgViewer::Viewer viewer;

    osg::ref_ptr<osg::Group> root = new osg::Group;

    osg::Geode* geode = new osg::Geode;
    geode->addChild(osgDB::readNodeFile("cow.osg"));
    geode->addDrawable(new osg::ShapeDrawable(new osg::Box()));

    root->addChild(geode);

    viewer.setSceneData(root.get());
    viewer.run();
    std::cout << "ok!" << std::endl;
}