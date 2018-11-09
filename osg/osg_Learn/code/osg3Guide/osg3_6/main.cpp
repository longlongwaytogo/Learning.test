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
#include <osg/LOD>
#include <osg/Fog>
#include  <osg/blendFunc>
#include <osgUtil/Simplifier>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/StateAttribute>
#include <osg/PolygonMode>
#include <osg/MatrixTransform>


osg::Node* createLight(unsigned int num,
                       const osg::Vec3& pos,
                       const osg::Vec4& clr);


osg::Geometry* createQuat(osg::Vec3 pos, std::string image);
void main()
{
    osgViewer::Viewer viewer;
    osg::Group* root = new osg::Group;
    osg::Node* node1 = osgDB::readNodeFile("cow.osg");

    osg::MatrixTransform* transform1 = new osg::MatrixTransform;
    transform1->addChild(node1);

    osg::ref_ptr<osg::PolygonMode> pm = new osg::PolygonMode;
    pm->setMode(osg::PolygonMode::FRONT_AND_BACK,
        osg::PolygonMode::LINE);
    transform1->getOrCreateStateSet()->setAttribute( pm.get() );

    osg::MatrixTransform* transform2 = new osg::MatrixTransform;
    transform2->addChild(osgDB::readNodeFile("lz.osg"));

     root->addChild(transform1);
     root->addChild(transform2);
     
     if(0)
     {
         // fog 
         osg::ref_ptr<osg::Fog> fog = new osg::Fog;
         fog->setMode( osg::Fog::LINEAR );
         fog->setStart( 500.0f );
         fog->setEnd( 2500.0f );
         fog->setColor( osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f) );
         root->getOrCreateStateSet()->setAttributeAndModes(fog);
     }
  
     {

         // light

         osg::Node* light0 = createLight(
             0, osg::Vec3(-20.0f,0.0f,0.0f), osg::Vec4(
             1.0f,1.0f,0.0f,1.0f) );
         osg::Node* light1 = createLight(
             1, osg::Vec3(0.0f,-20.0f,0.0f), osg::Vec4(0.0f,1.0f,1.0f,1.0f)
             );

       
         root->getOrCreateStateSet()->setMode( GL_LIGHT0,
             osg::StateAttribute::ON );
         root->getOrCreateStateSet()->setMode( GL_LIGHT1,
             osg::StateAttribute::ON );
         root->addChild(light0);
         root->addChild(light1);


     }

     {

         // trasparent test 

         osg::ref_ptr<osg::Geode> geode = new osg::Geode;
         geode->addDrawable(createQuat(osg::Vec3(30,0,0),"Images/lz.rgb"));

     }
    viewer.setSceneData(root);
    viewer.realize();
    viewer.run();

}

osg::Geometry* createQuat(osg::Vec3 pos, std::string image)
{
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    osg::ref_ptr<osg::Vec3Array> vertics = new osg::Vec3Array;
    vertics->push_back(pos + osg::Vec3(-0.5f, 0.0f, -0.5f));
    vertics->push_back(pos + osg::Vec3( 0.5f, 0.0f, -0.5f));
    vertics->push_back(pos + osg::Vec3( 0.5f, 0.0f,  0.5f));
    vertics->push_back(pos + osg::Vec3(-0.5f, 0.0f,  0.5f));
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0,-1,0));
    osg::ref_ptr<osg::Vec2Array> coordinate = new osg::Vec2Array;
    coordinate->push_back(osg::Vec2(0.0f,0.0f));
    coordinate->push_back(osg::Vec2(0.0f,1.0f));
    coordinate->push_back(osg::Vec2(1.0f,1.0f));
    coordinate->push_back(osg::Vec2(1.0f,0.0f));
    geom->setVertexArray(vertics);
    geom->setTexCoordArray(0,coordinate.get());
    geom->setNormalArray(normals);
    geom->setVertexAttribBinding(0,osg::Geometry::BIND_OVERALL);
   // geom->setVertexAttribBinding(osg::Geometry::BIND_OVERALL);
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS,0,4));

    return geom.release();
}
osg::Node* createLight(unsigned int num,
                       const osg::Vec3& pos,
                       const osg::Vec4& clr)
{
    osg::ref_ptr<osg::Light> light = new osg::Light(num);
    light->setDiffuse(clr);
    
    osg::ref_ptr<osg::LightSource> source = new osg::LightSource;
    source->setLight(light);

    osg::ref_ptr<osg::MatrixTransform> sourceTransform = new osg::MatrixTransform;
    sourceTransform->addChild(source);
    sourceTransform->setMatrix(osg::Matrix::translate(pos));

    return sourceTransform.release();

}