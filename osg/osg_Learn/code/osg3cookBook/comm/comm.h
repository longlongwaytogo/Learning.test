#ifndef __OSG_COOKBOOK_COMM_H__
#define __OSG_COOKBOOK_COMM_H__

#include <osg/Camera>
#include <osg/Matrix>
#include <osg/NodeCallback>
#include <osgText/Text>
#include <osgText/Font>
#include <osgGA/GUIEventHandler>
#include <osg/AnimationPath>

namespace osgComm
{
    std::string& getMediaPath();

    osg::Camera* createHudCamera(double left, double right, double botton, double top); // opengl left corner is orign

    osgText::Text* createText(const osg::Vec3& pos,osgText::Font* font,const std::string& content,float size);

    osg::Node* createTranform(osg::Node* node,osg::Vec3& pos);

    /*
        radius: 动画运动半径； time: 周期
    */
    osg::AnimationPath* createAnimationPath(float radius,float time);

    osg::AnimationPathCallback* createAnimationCallback(float radius, float time);

    class PickHandler :public osgGA::GUIEventHandler
    {
    public:
        virtual void doUserOperations(const osgUtil::LineSegmentIntersector::Intersection& in) = 0;
        virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*);
    };

    float RandValue(float min, float max);

    osg::Vec3 RandVector(float min, float max);

    osg::Matrix RandMatrix(float min, float max);
}


#endif // __OSG_COOKBOOK_COMM_H__