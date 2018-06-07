//���±��������ز�����operator,����������ʱ��operator()�����ݱ����ã�ע��  
//��Ҫ���traverse()��ʵ�ֽڵ�ļ������������Բο�src/osg/stateset.cpp,runUpdateCallBack()�еĵ��� 

#include <iostream>


#include <osg/Node>
#include <osg/NodeCallback>
#include <osgViewer/Viewer>
#include <osg/Drawable>
#include <osg/NodeVisitor>
#include <osgDB/ReaderWriter>
#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>


class UpdateCallback : public osg::NodeCallback  
{  
        virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)  
        {   
            std::cout<<"update callback - pre traverse"<<node<<std::endl;  
            traverse(node,nv);  
            std::cout<<"update callback - post traverse"<<node<<std::endl;  
        }  
};  
  
//��ѡ���������ز�����operator(),������ִ�м�ѡ�Ż�ʱ��operator()�����ã�ע��  
//��Ҫ���traverse()��ʵ�ֽڵ�ļ������������Բο�include/osgUtil/CullVisitor,  
//handle_cull_callbacks_and_traverse()�еĵ��ù��̡�  
class CullCallback : public osg::NodeCallback  
{  
        virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)  
        {   
            std::cout<<"cull callback - pre traverse"<<node<<std::endl;  
            traverse(node,nv);  
            std::cout<<"cull callback - post traverse"<<node<<std::endl;  
        }  
};  
  
//��������Ʊ���������drawImplementation(),����������л���ʱ�����������ݱ����ã�����  
//���޷�������ǰ�ļ�����״�����Բο�include/osg/Drawable,draw()�еĵ��ù���  
class DrawableDrawCallback : public osg::Drawable::DrawCallback  
{  
        virtual void drawImplementation(osg::RenderInfo& renderInfo,const osg::Drawable* drawable) const  
        {  
            std::cout<<"draw call back - pre drawImplementation"<<drawable<<std::endl;  
            drawable->drawImplementation(renderInfo);  
            std::cout<<"draw call back - post drawImplementation"<<drawable<<std::endl;  
        }  
};  
  
//��������±��������غ���update().�����������ʱ���亯�������á����Բο�  
//include/osgUtil/UpdateVisitor, handle_geode_callback()�еĵ��ù��̡�  
struct DrawableUpdateCallback : public osg::Drawable::UpdateCallback  
{  
    virtual void update(osg::NodeVisitor*, osg::Drawable* drawable)  
    {  
        std::cout<<"Drawable update callback "<<drawable<<std::endl;  
    }  
};  
  
//�������ѡ���������غ���cull������������м�ѡ�Ż�ʱ�����������ݱ����á����Բο�  
//src/osgutil/cullVisitor, apply(Geode&)�����еĵ��ù���  
struct DrawableCullCallback : public osg::Drawable::CullCallback  
{  
    /** do customized cull code.*/  
    virtual bool cull(osg::NodeVisitor*, osg::Drawable* drawable, osg::State* /*state*/) const  
    {  
        std::cout<<"Drawable cull callback "<<drawable<<std::endl;  
        return false;  
    }  
};  
  
class InsertCallbacksVisitor : public osg::NodeVisitor  
{  
  
   public:  
     
        InsertCallbacksVisitor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)  
        {  
        }  
          
        virtual void apply(osg::Node& node)  
        {  
             node.setUpdateCallback(new UpdateCallback());  
             node.setCullCallback(new CullCallback());  
             traverse(node);  
        }  
  
        virtual void apply(osg::Geode& geode)  
        {  
            geode.setUpdateCallback(new UpdateCallback());  
              
            //note, it makes no sense to attach a cull callback to the node  
            //at there are no nodes to traverse below the geode, only  
            //drawables, and as such the Cull node callbacks is ignored.  
            //If you wish to control the culling of drawables  
            //then use a drawable cullback...  
  
            for(unsigned int i=0;i<geode.getNumDrawables();++i)  
            {  
                geode.getDrawable(i)->setUpdateCallback(new DrawableUpdateCallback());  
                geode.getDrawable(i)->setCullCallback(new DrawableCullCallback());  
                geode.getDrawable(i)->setDrawCallback(new DrawableDrawCallback());  
            }  
        }  
          
        virtual void apply(osg::Transform& node)  
        {  
            apply((osg::Node&)node);  
        }  
};  
  
class MyReadFileCallback : public osgDB::Registry::ReadFileCallback  
{  
public:  
    virtual osgDB::ReaderWriter::ReadResult readNode(const std::string& fileName, const osgDB::ReaderWriter::Options* options)  
    {  
        std::cout<<"before readNode"<<std::endl;  
        // note when calling the Registry to do the read you have to call readNodeImplementation NOT readNode, as this will  
        // cause on infinite recusive loop.  
        osgDB::ReaderWriter::ReadResult result = osgDB::Registry::instance()->readNodeImplementation(fileName,options);  
        std::cout<<"after readNode"<<std::endl;  
        return result;  
    }  
};  
  
class CameraUpdateCallback : public osg::NodeCallback  
{  
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)  
    {   
        std::cout<<"Camera update callback - pre traverse"<<node<<std::endl;  
        traverse(node,nv);  
        std::cout<<"Camera update callback - post traverse"<<node<<std::endl;  
    }  
};  
  
class CameraEventCallback : public osg::NodeCallback  
{  
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)  
    {   
        std::cout<<"Camera event callback - pre traverse"<<node<<std::endl;  
        traverse(node,nv);  
        std::cout<<"Camera event callback - post traverse"<<node<<std::endl;  
    }  
};  
  
int main( int argc, char **argv )  
{  
    // use an ArgumentParser object to manage the program arguments.  
    osg::ArgumentParser arguments(&argc,argv);  
     
    // set the osgDB::Registy read file callback to catch all requests for reading files.  
    osgDB::Registry::instance()->setReadFileCallback(new MyReadFileCallback());  
     
    // initialize the viewer.  
    osgViewer::Viewer viewer;  
  
    // load the nodes from the commandline arguments.  
    osg::Node* rootnode = osgDB::readNodeFiles(arguments);  
  
    // if not loaded assume no arguments passed in, try use default mode instead.  
    if (!rootnode) rootnode = osgDB::readNodeFile("cow.osgt");  
  
    if (!rootnode)  
    {  
        osg::notify(osg::NOTICE)<<"Please specify a file on the command line"<<std::endl;  
  
        return 1;  
    }  
      
    // run optimization over the scene graph  
    osgUtil::Optimizer optimzer;  
    optimzer.optimize(rootnode);  
       
    // insert all the callbacks  
    InsertCallbacksVisitor icv;  
    rootnode->accept(icv);  
  
    viewer.getCamera()->setUpdateCallback(new CameraUpdateCallback());  
    viewer.getCamera()->setEventCallback(new CameraEventCallback());  
  
    // set the scene to render  
    viewer.setSceneData(rootnode);  
  
    return viewer.run();  
} 