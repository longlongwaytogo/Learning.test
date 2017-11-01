#include <iostream>
#include <osg/node>
#include <osgdb/readFile>
#include <osgViewer/Viewer>
using namespace std;

//void main()
//{
//	osg::Node* pNode = osgDB::readNodeFile("cow.osg");
//	osgViewer::Viewer viewer;
//	viewer.setSceneData(pNode);
//	cout << "start test" << endl;
//	viewer.run();
//
//
//}

#include <iostream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Group>
#include <osg/Node>
#include <osgFX/Scribe>
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector>

#pragma comment(lib,"E:\\project\\osg\\OpenSceneGraph-3.4.0\\solution2012_x64\\lib\\osgFXd.lib")
class CPickHandler :public osgGA::GUIEventHandler
{
public:
	CPickHandler(osgViewer::Viewer * viewer) :mViewer(viewer) {};
	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &&aa)
	{
		switch (ea.getEventType())
		{
			// PUSH, button down
		case osgGA::GUIEventAdapter::PUSH:
			// 1,left button push
			if (ea.getButton() == 1)
			{
				Pick(ea.getX(), ea.getY());
			}
			return true;
		}
		return false;
	}
protected:
	void Pick(float x, float y)
	{
		osgUtil::LineSegmentIntersector::Intersections intersections;
		if (mViewer->computeIntersections(x, y, intersections))
		{
			for (osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
				hitr != intersections.end();
				++hitr)
			{
				if (!hitr->nodePath.empty() && !(hitr->nodePath.back()->getName().empty()))
				{
					const osg::NodePath &np = hitr->nodePath;
					for (int i = np.size() - 1; i >= 0; --i)
					{
						osgFX::Scribe *sc = dynamic_cast<osgFX::Scribe *> (np[i]);
						if (sc != NULL)
						{
							if (sc->getNodeMask() != 0)
								sc->setNodeMask(0);
						}
					}
				}

			}
		}
	}
	osgViewer::Viewer *mViewer;
};

// argc: the number of argv
// argv: an array of arguments,
//       args[0] always is the path and name of the program itself.
int main(int argc, char** argv)
{

	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group>  root = new osg::Group();
	root->addChild(osgDB::readNodeFile("cessna.osg"));
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile("cow.osg");

	osg::ref_ptr<osgFX::Scribe> sc = new osgFX::Scribe();
	int nszie = sc->getNumChildren();

	sc->addChild(cow.get());

	root->addChild(cow.get());
	root->addChild(sc.get());

	viewer->setSceneData(root.get());

	viewer->addEventHandler(new CPickHandler(viewer.get()));

	viewer->realize();
	viewer->run();

}

