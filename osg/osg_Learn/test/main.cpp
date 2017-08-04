#include <iostream>
#include <osg/node>
#include <osgdb/readFile>
#include <osgViewer/Viewer>
using namespace std;

void main()
{
	osg::Node* pNode = osgDB::readNodeFile("cow.osg");
	osgViewer::Viewer viewer;
	viewer.setSceneData(pNode);
	cout << "start test" << endl;
	viewer.run();


}