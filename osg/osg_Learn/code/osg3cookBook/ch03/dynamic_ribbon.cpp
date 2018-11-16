// dynamic_ribbon.cpp
#include <osg/AnimationPath>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <comm/comm.h>

const unsigned int g_numPoints = 400;
const float g_halfWidth = 4.0f;

osg::Geometry* createRibbon(const osg::Vec3& colorRGB)
{
	osg::ref_ptr<osg::Geometry> geometry  = new osg::Geometry;
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(g_numPoints);
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(g_numPoints);
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(g_numPoints);

    osg::Vec3 origin = osg::Vec3(0.0f, 0.0f, 0.0f);
    osg::Vec3 normal = osg::Vec3(0.0f, 0.0f, 1.0f);

    for(unsigned int i = 0; i < g_numPoints-1; i+=2)
    {

        (*vertices)[i] = origin;(*vertices)[i+1] = origin;
        (*normals)[i] = normal; (*normals)[i+1] = normal;
        
        float alpha = sinf(osg::PI/2 * (float)i / (float)g_numPoints );
        (*colors)[i] = osg::Vec4(colorRGB,alpha);
        (*colors)[i+1] = osg::Vec4(colorRGB,alpha);

    }

    geometry->setVertexArray(vertices.get());
    geometry->setColorArray(colors.get());
    geometry->setNormalArray(normals.get());
    geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    geometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
    geometry->setUseDisplayList(false);
    geometry->setDataVariance(osg::Object::DYNAMIC);
    geometry->setUseVertexBufferObjects(true);
    geometry->addPrimitiveSet(new osg::DrawArrays(GL_QUAD_STRIP,0,g_numPoints));
    
    return geometry.release();
}

class TrailerCallback :public osg::NodeCallback
{

public:
    TrailerCallback(osg::Geometry* geometry):_geometry(geometry){}

    void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {

        osg::MatrixTransform* trans = static_cast<osg::MatrixTransform*>(node);
        if(trans)
        {

            osg::Matrix matrix = trans->getMatrix();
            osg::Vec3Array* vertices = static_cast<osg::Vec3Array*>(_geometry->getVertexArray());
            osg::Vec3Array* normals = static_cast<osg::Vec3Array*>(_geometry->getNormalArray());
            
            for( unsigned int i = 0; i < g_numPoints - 3; i+=2)
            {
                (*vertices)[i] = (*vertices)[i+2]; // 将带的后一个点赋值前后一个点
                (*vertices)[i+1] = (*vertices)[i+3];
                (*normals)[i] = (*normals)[i+2];
                (*normals)[i+1] = (*normals)[i+3];
            }
            //每次更新一组条带顶点，后续顶点随着时间推移而逐步更新
            (*vertices)[g_numPoints-2] = osg::Vec3(0.0f, -g_halfWidth,0.0f)* matrix;
            (*vertices)[g_numPoints-1] = osg::Vec3(0.0f,  g_halfWidth,0.0f)* matrix;
            vertices->dirty();

            osg::Vec3 normal = osg::Vec3(0.0f,0.0f,1.0f) * matrix;
            normal.normalize();
            (*normals)[g_numPoints-2] = normal;
            (*normals)[g_numPoints-1] = normal;
            normals->dirty();

            _geometry->dirtyBound();

        }

        traverse(node,nv);
    }
private:
    osg::ref_ptr<osg::Geometry> _geometry;
};


void main()
{
    osg::ref_ptr<osg::Group> root = new osg::Group;
    osg::ref_ptr<osg::Geometry> geometry = createRibbon(osg::Vec3(1.0f,0.0f,1.0f));
    osg::ref_ptr<osg::MatrixTransform> cessna = new osg::MatrixTransform;
    cessna->addChild(osgDB::readNodeFile("cessna.osg.0,0,90.rot"));
    cessna->addUpdateCallback(osgComm::createAnimationCallback(50.0,6.0f));
    cessna->addUpdateCallback(new TrailerCallback(geometry));

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geometry);
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
    geode->getOrCreateStateSet()->setMode(GL_BLEND,osg::StateAttribute::ON);
    geode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    
    root->addChild(geode);
    root->addChild(cessna.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.run();

}


