// osgPagedLOD

#include <osg/Node>
#include <osg/Group>
#include <osg/LOD>
#include <osg/PositionAttitudeTransform>

#include <iostream>
#include <osg/node>
#include <osgdb/readFile>
#include <osgViewer/Viewer>
using namespace std;

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
	cout << "start test" << endl;
	viewer.run();


}