
#include <iostream>
#include <string>
#include <map>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/Plane>
#include <osg/Texture2D>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/FirstPersonManipulator>

#include <osg/NodeCallback>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <fstream>
#include <sstream>

#include "comm/comm.h"

#define USE_CULLCALLBACK 1

typedef std::pair<int,int> CellIndex;
typedef std::map<CellIndex,int> CellMap;
CellMap g_mazeMap;

osg::Geode* getOrCreatePlane();

osg::Geode* getOrCreateBox();

osg::Node* createMaze( const std::string& file );

osg::NodePathList g_list;

 class MazeCullCallback: public  osg::NodeCallback
 {
 public:
     virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
     {
         osg::Vec3 eye = nv->getEyePoint();
         osg::Vec3 center = node->getBound().center();

         g_list = node->getParentalNodePaths();
         osg::Matrix l2w = osg::computeLocalToWorld(g_list[0]);
         
         eye = eye * l2w ;
         center = center * l2w;

         CellIndex indexEye, indexNode;

         if(getCellIndex(indexEye,eye) && getCellIndex(indexNode,center)) // 节点和眼睛是否在迷宫中
         {
             traverse(node,nv);
         }
     }

     bool getCellIndex(CellIndex& index, const osg::Vec3& pos)
     {
         index.first = int(pos[0] + 0.5f);
         index.second = int(pos[1] + 0.5f);

        auto itr = g_mazeMap.find(index);
        if(itr != g_mazeMap.end() && itr->second == 0)
            return true;
        return false;

     }

 };

class MazeManipulator :public osgGA::FirstPersonManipulator
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa, osg::NodeVisitor* nv)
	{

        osg::Matrix lastMatrix = getMatrix();
        bool ok = osgGA::FirstPersonManipulator::handle(ea,aa);
        if(ea.getEventType() == osgGA::GUIEventAdapter::FRAME || ea.getEventType() == osgGA::GUIEventAdapter::SCROLL)
        {
            osg::Matrix matrix = getMatrix();
            osg::Vec3 pos = matrix.getTrans();

            if(pos[2] != 0.5f) // fix the player height
            {
                pos[2] = 0.5f;
                matrix.setTrans(pos);
                setByMatrix(matrix);
            }

            CellIndex index(int(pos[0] + 0.5f),int(pos[1] + 0.5f));
            CellMap::iterator itr = g_mazeMap.find(index);
            if(itr == g_mazeMap.end()) // outside the maze
                setByMatrix(lastMatrix);
            else if(itr->second != 0) // don't intersect with walls 
                setByMatrix(lastMatrix);

            return ok;
        }
		return false;
	}
};

int main(int argc, char** argv)
{
	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->getOrCreateStateSet()->setMode(GL_NORMALIZE,osg::StateAttribute::ON);
	root->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

    root->addChild(createMaze("maze.txt"));
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("dumptruck.osg");
   
    for(int i = 0; i < 2000; ++i)
    {
        float x = osgComm::RandValue(0.5,6.0);
        float y = osgComm::RandValue(0.6,6.0);
        float z = osgComm::RandValue(0.1,1.0);

        osg::ref_ptr<osg::Group> parent = new osg::Group;
        osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
        trans->addChild(model);
        trans->setMatrix(osg::Matrix::scale(0.001,0.001,0.001) * osg::Matrix::translate(x,y,z));
       

#ifdef USE_CULLCALLBACK
        parent->setCullCallback( new MazeCullCallback );
#endif
        parent->addChild( trans.get() );
        root->addChild( parent.get() );

    }
  

    

    osgViewer::Viewer viewer;

    viewer.setUpViewInWindow(100,100,1024,768);
    viewer.addEventHandler(new osgViewer::StatsHandler);
    osg::ref_ptr<MazeManipulator> manipulator = new MazeManipulator;
    manipulator->setHomePosition( osg::Vec3(6.0f, 0.0f, 0.5f), osg::Vec3(6.0f, 1.0f, 0.5f), osg::Z_AXIS );
    viewer.setCameraManipulator(manipulator);

    viewer.setSceneData(root.get());
    return viewer.run();


}

osg::Geode* getOrCreatePlane()
{
    osg::ref_ptr<osg::Geometry> plane = osg::createTexturedQuadGeometry(osg::Vec3(-0.5,-0.5,0),osg::X_AXIS,osg::Y_AXIS);
    osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
    tex->setImage(osgDB::readImageFile("Images/skin.tga"));
    plane->getOrCreateStateSet()->setTextureAttributeAndModes(0,tex.get(),osg::StateAttribute::ON);
    osg::ref_ptr<osg::Geode> node = new osg::Geode;
    node->addDrawable(plane);
    return node.release();
}

osg::Geode* getOrCreateBox()
{

    osg::ref_ptr<osg::Geode> box = new osg::Geode;
    osg::ref_ptr<osg::ShapeDrawable> geom = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0,0.0,0.50),1.0));
    box->addDrawable(geom.get());
    osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
    tex->setImage(osgDB::readImageFile("Images/Brick-Std-Orange.TGA"));
    box->getOrCreateStateSet()->setTextureAttributeAndModes(0,tex.get(),osg::StateAttribute::ON);

    return box.release();
}

osg::Node* createMaze(const std::string& file)
{
    std::cout << osgComm::getMediaPath() << std::endl;
    std::string fileName = osgComm::getMediaPath() + file;

    std::fstream fs(fileName.c_str());

    if(!fs) return NULL;
    int row = 0;
   
    while(!fs.eof())
    {
        int col = 0;
        std::string info;
        std::getline(fs,info);
        std::stringstream ss(info);
      
        while(!ss.eof())
        {
            int val = 0;
            ss >> val;
            g_mazeMap[CellIndex(row,col)] = val;
            std::cout << val << " ";
            col ++;
        }
        std::cout << std::endl;
        row++;
    }
    
    if(g_mazeMap.size()>0)
    {
        osg::ref_ptr<osg::Group> mazeRoot = new osg::Group;
       
        for(auto itr : g_mazeMap)
        {
             osg::ref_ptr<osg::MatrixTransform> translate = new osg::MatrixTransform;
            if(itr.second == 0)
            {
                 translate->addChild(getOrCreatePlane());
            }
            else
            {
                translate->addChild(getOrCreateBox());
            }
       
            translate->setMatrix( osg::Matrix::translate(itr.first.first,itr.first.second,0));
            mazeRoot->addChild(translate.get());
        }
        return mazeRoot.release();
    }
    return NULL;
}