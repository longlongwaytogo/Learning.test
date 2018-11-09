//////////////////////////////////////////////////////////////////////////
// @destription:learn osg3.0 Guide capture 5: scene graph 
// @author: longlongwaytogo
// @date: 2018/7/31
// @link: http://osg3.readthedocs.io/en/latest/ch05.html 

#include <iostream>
#include <string>

#include <osg/Geode>
#include <osg/Node>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/LOD>
#include <osgUtil/Simplifier>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

osg::Node* createLODNode( const osg::Vec3& pos );
osg::Group* createTransformNode(const osg::Vec3& pos);

class AnimatingSwitch: public osg::Switch
{

public:

    AnimatingSwitch():Switch(),_count(0){}

    AnimatingSwitch( const AnimatingSwitch& copy,
        const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY )
        : osg::Switch(copy, copyop), _count(copy._count) {}

    META_Node( osg, AnimatingSwitch );

    virtual void traverse( osg::NodeVisitor& nv )
    {
        if(!(++_count%60)) {
            setValue( 0, !getValue(0));
            setValue( 1, !getValue(1));
        }
    }

private:
    int _count;

};
void main()
{

    osgViewer::Viewer viewer;
    osg::Group* root = new osg::Group;
    osg::Node* node1 = osgDB::readNodeFile("cow.osg");

    osg::MatrixTransform* pMT1 = new osg::MatrixTransform;
    osg::MatrixTransform* pMT2 = new osg::MatrixTransform;
    osg::Node* pNode = osgDB::readNodeFile("cessna.osg");
    // root->addChild(node1);
    pMT1->setMatrix(osg::Matrix::translate(osg::Vec3(-45,0,0)));
    pMT2->setMatrix(osg::Matrix::translate(osg::Vec3(45,0,0)));

    pMT1->addChild(pNode);
    pMT2->addChild(pNode);

    osg::Group* pGroup = pMT2->asGroup();
    osg::Geode* pGeode = pMT2->asGeode();

    std::cout <<"Geode:" << pGeode <<",Group:" << pGroup << std::endl;  

  //  root->addChild(pMT1);
  //  root->addChild(pMT2);

    { // switch node test 
        osg::ref_ptr<osg::MatrixTransform> pMT3 = new osg::MatrixTransform;
        osg::ref_ptr<osg::Node> model1= osgDB::readNodeFile("cessna.osg");
        osg::ref_ptr<osg::Node> model2= osgDB::readNodeFile("cessnafire.osg");
        osg::ref_ptr<osg::Switch> sw = new osg::Switch;
       
        sw->addChild( model1.get(), false );
        sw->addChild( model2.get(), true );
        pMT3->addChild(sw);
        pMT3->setMatrix(osg::Matrix::translate(osg::Vec3(0,0,25)));
        root->addChild(pMT3);
        sw->setValue( 0, false );
        sw->setValue( 1, true );
     
    }

    {
        // Level-of-detail nodes 
       osg::ref_ptr<osg::LOD> lodNode = new osg::LOD;

        
       osg::ref_ptr<osg::Node> modelL2 = dynamic_cast<osg::Node*>(pNode->clone(osg::CopyOp::DEEP_COPY_ALL) );
       osg::ref_ptr<osg::Node> modelL1 = dynamic_cast<osg::Node*>(pNode->clone(osg::CopyOp::DEEP_COPY_ALL) );

      /*  osgUtil::Simplifier simplifier;
        simplifier.setSampleRatio( 0.5 );
        modelL2->accept( simplifier );
        simplifier.setSampleRatio( 0.1 );
        modelL1->accept( simplifier );*/

         lodNode->addChild( pNode, 0.0f, 20.0f );
        lodNode->addChild( modelL2, 20.0f, 500.0f );
        lodNode->addChild( modelL1, 500.0f, FLT_MAX );
        lodNode->setRange( 1, 0.0f, 500.0f );

        root->addChild(lodNode);
    }

    { // test AnimationSwitch 

        osg::ref_ptr<AnimatingSwitch> animatingSwitch = new AnimatingSwitch;
        osg::ref_ptr<osg::Node> pNode1 = osgDB::readNodeFile("cessna.osg");
        osg::ref_ptr<osg::Node> pNode2 = osgDB::readNodeFile("cessnafire.osg");
        osg::Group* pGroup1 = createTransformNode(osg::Vec3(20,0,40));
        osg::Group* pGroup2 = createTransformNode(osg::Vec3(-20,0,40));
        pGroup1->addChild(pNode1);
        pGroup2->addChild(pNode2);
        animatingSwitch->addChild(pGroup1,true);
        animatingSwitch->addChild(pGroup2,false);

        root->addChild(animatingSwitch);
    }
    viewer.setSceneData(root);
    viewer.realize();
    viewer.run();

}

osg::Node* createLODNode( const osg::Vec3& pos )
{
    osg::ref_ptr<osg::PagedLOD> pagedLOD = new osg::PagedLOD;
    osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
    mt->setMatrix( osg::Matrix::translate(pos) );
    mt->addChild( pagedLOD.get() );
    return mt.release();
}

osg::Group* createTransformNode(const osg::Vec3& pos)
{
    osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
    mt->setMatrix( osg::Matrix::translate(pos) );
    return mt.release();
}