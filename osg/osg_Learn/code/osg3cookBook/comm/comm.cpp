#include "comm.h"
#include <iostream>
#include <osg/MatrixTransform>
#include <osg/Matrix>
#include <osg/Vec3>
#include <osgViewer/Viewer>
#include <osgUtil/LineSegmentIntersector>

#include <io.h>
namespace osgComm
{
   
    std::string g_mediaPath;
    std::string& getMediaPath()
    {
       
        static bool bInit = false;
        if(!bInit)
        {
            std::string path = "code/osg3cookBook/data";
            std::string parentStr = "../";
            std::string parentPath = "";
            int i = 0;
            while(i < 5) // 5级别回溯，查找资源路径
            {
                std::string findPath = parentPath + path;
                if(_access(findPath.c_str(),0) == 0)
                {
                    g_mediaPath = findPath;
                    break;
                }
                parentPath += parentStr;
                i++;

            }
            g_mediaPath +="/";

            bInit = true;
        }
      return g_mediaPath;
        
    }

    osg::Camera* createHudCamera(double left, double right, double botton, double top) // opengl left corner is orign
    {
        osg::ref_ptr<osg::Camera> hudCamera = new osg::Camera;
        hudCamera->setClearMask(GL_DEPTH_BUFFER_BIT); // blend of scene
        hudCamera->setRenderOrder(osg::Camera::POST_RENDER);
        hudCamera->setAllowEventFocus(false);
        // hudCamera->setViewport(left,botton,right,top);
        hudCamera->setProjectionMatrix(osg::Matrix::ortho2D(left,right,botton,top));
        hudCamera->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
        hudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

        return hudCamera.release();
    }

    osgText::Text* createText(const osg::Vec3& pos,osgText::Font* font,const std::string& content,float size)
    {
        osg::ref_ptr<osgText::Text> text = new osgText::Text;
        text->setDataVariance(osg::Object::DYNAMIC);
        text->setPosition(pos);
        text->setFont(font);
        text->setText(content);
        text->setCharacterSize(size);
        text->setAxisAlignment(osgText::Text::XY_PLANE);

        return text.release();
    }

    osg::Node* createTranform(osg::Node* node,osg::Vec3& pos)
    {
        osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
        mt->addChild(node);
        mt->setMatrix(osg::Matrix::translate(pos));
        return mt.release();
    }

    osg::AnimationPath* createAnimationPath(float radius,float time)
    {
        osg::ref_ptr<osg::AnimationPath> animation = new osg::AnimationPath;
        animation->setLoopMode(osg::AnimationPath::LOOP);
        int numSamples = 32;
        float delta_yaw = 2 * osg::PI / (numSamples - 1);
        float delta_time = time / numSamples;

        for(int i = 0; i < numSamples; ++i)
        {
            float yaw =  delta_yaw * i;
            osg::Vec3 pos(sinf(yaw)* radius,cosf(yaw)* radius,0.0f);
            osg::Quat rot(-yaw,osg::Z_AXIS);
            animation->insert(delta_time * i, osg::AnimationPath::ControlPoint(pos,rot));
        }

        return animation.release();
    }

    osg::AnimationPathCallback* createAnimationCallback(float radius, float time)
    {
        osg::ref_ptr<osg::AnimationPath> path = createAnimationPath(radius,time);
        osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
        apcb->setAnimationPath( path.get() );
        return apcb.release();    
    }

    bool PickHandler::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*)
    {
        if(ea.getEventType() != osgGA::GUIEventAdapter::RELEASE || ea.getButton() != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON ||
            !(ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL) )
            return false;

        if(ea.getEventType() == osgGA::GUIEventAdapter::RELEASE && ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON && 
            ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL)
        {

            std::cout << "enter" << std::endl;
        }
        osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
        if(viewer)
        {
            osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = new osgUtil::LineSegmentIntersector(osgUtil::LineSegmentIntersector::WINDOW,ea.getX(),ea.getY());
            osgUtil::IntersectionVisitor iv(intersector.get());
            viewer->getCamera()->accept(iv);

            if(intersector->containsIntersections())
            {
                if ( intersector->containsIntersections() )
                {
                    const osgUtil::LineSegmentIntersector::Intersection& result = *(intersector->getIntersections().begin());
                    doUserOperations( result );
                }
            }
        }
        return false;
    }

 
    float RandValue(float min, float max)
    {
        return (min + rand())/(RAND_MAX + 1.0) *(max - min);
    }

    osg::Vec3 RandVector(float min, float max)
    {
       return  osg::Vec3(RandValue(min,max),RandValue(min,max),RandValue(min,max));
    }

    osg::Matrix RandMatrix(float min, float max)
    {
        osg::Vec3 pos = RandVector(min,max);
        osg::Vec3 rot = RandVector(-osg::PI,osg::PI);

       return osg::Matrix::rotate(rot[0],osg::X_AXIS,rot[1],osg::Y_AXIS,rot[2],osg::Z_AXIS) *
              osg::Matrix::translate(pos);

    }

}