#include <iostream>
#include <fstream>
#include <string>

#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/NodeCallback>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgDB/Registry>
#include <osgDB/ReaderWriter>
#include <openThreads/Mutex>
#include <OpenThreads/ScopedLock>

#include <comm/comm.h>

#define USE_OSGDB_CACHE 1

const std::string c_removeMark("Removable");

class ReadAndShareCallback :public osgDB::ReadFileCallback
{
	public:
	
	virtual osgDB::ReaderWriter::ReadResult readNode( const std::string& filename, const osgDB::Options* options )
	{
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_shareMutex);
		osg::Node* node = getNodeByName(filename);
		if(!node)
		{
			osgDB::ReaderWriter::ReadResult rr = osgDB::Registry::instance()->readNodeImplementation(filename,options);
			if(rr.success()) _nodeMap[filename] = rr.getNode();
			return rr;
		}
		else
			std::cout << "[STRING] The name: " <<  filename << " is already added to share map" << std::endl;
		return node;
	}
	void prune(int second )
	{
		if(second%5) return ;
		
		OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_shareMutex);
		for(auto i : _nodeMap)
		{
			if(i.second.valid())
			{
				if(i.second->referenceCount() <= 1)
				{
					std::cout <<"[REMOVING] The name " << i.first << " is removed from shared map" << std::endl;
					i.second = NULL;
				}
			}
			
		}
	}
	
	protected:
	osg::Node* getNodeByName( const std::string& filename)
	{
        for(auto i : _nodeMap)
        {
            if(i.first == filename)
                return _nodeMap[filename];
        }

		return NULL;
	}
	private:
		OpenThreads::Mutex _shareMutex;
		typedef std::map<std::string, osg::ref_ptr<osg::Node>> NodeMap;
		NodeMap _nodeMap;
};

class RemoveModelHandler :public osgComm::PickHandler
{
	public:
		RemoveModelHandler(ReadAndShareCallback* cb):_callback(cb){}
        
       
		virtual bool handle( const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*)
		{
			if(ea.getEventType() == osgGA::GUIEventAdapter::FRAME)
			{
				if(_callback.valid())
				{
					_callback->prune((int)ea.getTime());
				}
				
			}

          return osgComm::PickHandler::handle(ea,aa,NULL,NULL);
		}

		virtual void doUserOperations( const osgUtil::LineSegmentIntersector::Intersection& in)
		{
			/*for( const osg::NodePath::iterator itr = in.nodePath.begin();itr != in.nodePath.end(); ++itr)
				{
					if((*itr)->getName() == c_removeMark)
					{
						osg::Group* parent = (*itr)->getNumParents()>0?(*itr)->getParent(0):NULL;
						if(parent) parent->removeChild(*itr);
						break;
					}
				}*/
            for( osg::NodePath::const_iterator itr = in.nodePath.begin(); itr != in.nodePath.end(); ++itr)
            {
                if((*itr)->getName() == c_removeMark)
                {
                    osg::Group* parent = (*itr)->getNumParents()>0?(*itr)->getParent(0):NULL;
                    if(parent) parent->removeChild(*itr);
                    break;
                }
            }
		}
		
		osg::observer_ptr<ReadAndShareCallback> _callback;
};
void addFileLists(osg::Group* root, const std::string& file);

void main()
{
#if !USE_OSGDB_CACHE

	osg::ref_ptr<ReadAndShareCallback> rc = new ReadAndShareCallback;
	osgDB::Registry::instance()->setReadFileCallback(rc);
#endif 	
    osg::ref_ptr<osg::Group> root = new osg::Group;
  
    addFileLists(root.get(),"E:\\project\\osg\\book\\osgRecipes-master\\build\\cookbook\\chapter8\\Debug\\files.txt");


    osgViewer::Viewer viewer;
    viewer.setUpViewInWindow(10,10,800,800);
    viewer.setSceneData(root.get());
#if !USE_OSGDB_CACHE
	viewer.addEventHandler(new RemoveModelHandler(rc));
#endif 
    viewer.addEventHandler( new osgViewer::StatsHandler);
    viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getStateSet()));
    viewer.run();
}



void addFileLists(osg::Group* root, const std::string& file)
{
	std::fstream is(file.c_str());
	if(!is) return ;
	
	while(!is.eof())
	{
        osg::Vec3 pos;
		std::string name;
		is >> name >> pos[0] >> pos[1] >> pos[2];
		std::cout << name << std::endl;
        osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
#if USE_OSGDB_CACHE
        osg::ref_ptr<osgDB::Options> options = new osgDB::Options;
        options->setObjectCacheHint( osgDB::Options::CACHE_NODES );
        osg::Node* node = osgDB::readNodeFile(name, options.get());
        mt->addChild(node);
        std::cout << "name:" << name << "pointer:" << (void*)node << std::endl;
#else 
        mt->addChild(osgDB::readNodeFile(name));
#endif 
       
        mt->setMatrix(osg::Matrix::translate(pos));
        mt->setName(c_removeMark);
        root->addChild(mt);
	}
}