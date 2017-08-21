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

	//�ðɣ����Ǽ�����ţ����ʵ��
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");
	//Ȼ����Ū���������ģ�ͳ���
	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("glider.osg");

	//����һ��ϸ�ڲ�νڵ�LOD
	osg::ref_ptr<osg::LOD> lode = new osg::LOD;
	//����ӽڵ㣬��0��30�ķ�Χ����ʾţ
	lode->addChild(node1.get(), 0.0f, 30.0f);
	//����ӽڵ㣬��30��100��ʱ����ʾ�����
	lode->addChild(node2.get(), 30.0f, 100.0f);

	//����һ��ϸ�ڲ�νڵ�LOD
	osg::ref_ptr<osg::LOD> lode1 = new osg::LOD;
	//���ð������ش�С���ж�
	lode1->setRangeMode(osg::LOD::PIXEL_SIZE_ON_SCREEN);
	//����ӽڵ㣬��0��30�ķ�Χ����ʾţ
	lode1->addChild(node1.get(), 0.0f, 1000.0f);
	//����ӽڵ㣬��30��100��ʱ����ʾ�����
	lode1->addChild(node2.get(), 1000.0f, 2000.0f);

	//����һ��λ�ñ任�ڵ�
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