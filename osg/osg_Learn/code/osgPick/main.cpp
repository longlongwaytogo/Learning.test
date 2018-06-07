// osgPagedLOD

#include <osg/Node>
#include <osg/Group>
#include <osg/LOD>
#include <osg/PositionAttitudeTransform>

#include <iostream>
#include <osg/node>
#include <osgdb/readFile>
#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>


using namespace std;

//
//osg::Vec3 DrawCallback::getPoint()
//{
//	osg::Vec3 vec3;
//
//	osg::ref_ptr<osgViewer::Viewer> viewer = dynamic_cast<osgViewer::Viewer *>(m_pAA);
//	osg::ref_ptr<osg::Camera> camera = viewer->getCamera();
//	osgViewer::Renderer *render = dynamic_cast<osgViewer::Renderer *>(camera->getRenderer());
//	osgUtil::SceneView *sceneView = render->getSceneView(0);
//
//	osg::Vec3 vScreen(m_pEA->getX(), m_pEA->getY(), 0);
//	osg::Vec3 window;
//	sceneView->projectWindowIntoObject(vScreen, window);
//
//	osg::Matrix mVPW = camera->getViewMatrix() * camera->getProjectionMatrix() * camera->getViewport()->computeWindowMatrix();
//	osg::Matrix invertVPW;
//	invertVPW.invert(mVPW);
//
//	vec3 = window * invertVPW;
//
//	return vec3;
//}

class PickHandler :public osgGA::GUIEventHandler
{
private:
	osgViewer::Viewer *m_pViewer;

public:
	PickHandler(osgViewer::Viewer *viewer) :m_pViewer(viewer)
	{
		

	}

	~PickHandler(void)
	{

	}

	//virtual bool handle(osgGA::Event* event, osg::Object* object, osg::NodeVisitor* nv)
	//{
	//	

	//	return false;
	//}

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
	
		switch (ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::PUSH):
		{
			if (ea.getButton() == 1)
			{
				pick(ea.getX(), ea.getY());
			}
			return true;
		}
		}

		return false;

	}

	void pick(float fX, float fY)
	{
		osgUtil::LineSegmentIntersector::Intersections intersections;
		if (m_pViewer->computeIntersections(fX, fY, intersections))
		{
			for (auto itr = intersections.begin(); itr != intersections.end(); ++itr)
			{
				if (!itr->nodePath.empty())
				{
					const osg::NodePath& np = itr->nodePath;
					for (int i = np.size() - 1; i >= 0; --i)
					{
						osg::Node* node = dynamic_cast<osg::Node *>(np[i]);
						if (NULL != node && node->getName().compare("cow") == 0)
						{
							//node->setNodeMask(0);
							//itr->getWorldIntersectPoint();//得到坐标
						}
					}
				}
			}
		}
	}

};

osg::ref_ptr<osg::Node> CreateNode()
{
	osg::ref_ptr<osg::Group> _root = new osg::Group;

	//好吧，我们继续拿牛来做实验
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");
	//然后再弄个滑翔机的模型出来
	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("glider.osg");

	//创建一个细节层次节点LOD
	osg::ref_ptr<osg::LOD> lode = new osg::LOD;
	//添加子节点，在0到30的范围内显示牛
	lode->addChild(node1.get(), 0.0f, 30.0f);
	//添加子节点，在30到100的时候显示滑翔机
	lode->addChild(node2.get(), 30.0f, 100.0f);

	//创建一个细节层次节点LOD
	osg::ref_ptr<osg::LOD> lode1 = new osg::LOD;
	//设置按照像素大小来判断
	lode1->setRangeMode(osg::LOD::PIXEL_SIZE_ON_SCREEN);
	//添加子节点，在0到30的范围内显示牛
	lode1->addChild(node1.get(), 0.0f, 1000.0f);
	//添加子节点，在30到100的时候显示滑翔机
	lode1->addChild(node2.get(), 1000.0f, 2000.0f);

	//创建一个位置变换节点
	osg::ref_ptr<osg::PositionAttitudeTransform> pat1 = new osg::PositionAttitudeTransform;
	pat1->setPosition(osg::Vec3(-20.0f, 0.0f, 0.0f));
	pat1->addChild(lode1.get());

	_root->addChild(lode.get());
	_root->addChild(pat1.get());

	return _root.get();
}


osg::ref_ptr<osg::Group> createPagedLOD()
{
	osg::ref_ptr<osg::PagedLOD> page = new osg::PagedLOD();
	page->setCenter(osg::Vec3(0.0f, 0.0f, 0.0f));

	page->setFileName(0, "cow.osg");
	page->setRange(0, 0.0f, 50.0f);

	page->setFileName(1, "glider.osg");
	page->setRange(1, 50.0f, 100.0f);


	page->setFileName(2, "cessna.osg");
	page->setRange(2, 100.0f, 200.0f);

	return page.get();
}

#define LOD_TEST 0
void main()
{
	
	osgViewer::Viewer viewer;

#if LOD_TEST 
	viewer.setSceneData(CreateNode().get());
#else
	viewer.setSceneData(createPagedLOD().get());
#endif 

	viewer.addEventHandler(new PickHandler(&viewer));

	cout << "start test" << endl;
	viewer.run();


}