//////////////////////////////////////////////////////////////////////////
// @destription:learn osg3.0Guide capture 4: geometry
// @author: longlongwaytogo
// @date: 2018/7/31
// @link: http://osg3.readthedocs.io/en/latest/ch04.html 

#include <iostream>

#include <gl/glut.h>

#include <osg/Shape>
#include <osg/Geode>
#include <osg/Node>
#include <osg/Group>
#include <osg/Array>
#include <osg/Vec3>
#include <osg/io_utils>
#include <osg/MatrixTransform>
#include <osg/TriangleFunctor>
#include <osgUtil/Tessellator>
#include <osgUtil/SmoothingVisitor>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>


osg::Geode* createGeode(osg::Vec3 pos);
osg::Geometry* createQuad(osg::Vec3 pos);
osg::Geometry* createOctahedron(osg::Vec3 pos);
osg::Geometry* createTessellatePolygon(osg::Vec3 pos,bool useTessellate = true);
osg::Geometry* createQuadStrip(osg::Vec3 pos);

struct FaceCollector
{
    void operator()( const osg::Vec3& v1, const osg::Vec3& v2,
        const osg::Vec3& v3, bool )
    {
        std::cout << "Face vertices: " << v1 << "; " << v2 << "; "
            << v3 << std::endl;
    }
};

class TeapotDrawable :public osg::Drawable
{
public:
    TeapotDrawable( float size=1.0f ) : _size(size) 
    {

    }
    TeapotDrawable( const TeapotDrawable& copy,
        const osg::CopyOp&
        copyop=osg::CopyOp::SHALLOW_COPY )
        : osg::Drawable(copy, copyop), _size(copy._size)

    {
    }

    virtual void drawImplementation(osg::RenderInfo& /*renderInfo*/) const 
    {
        glFrontFace( GL_CW );
        glutSolidTeapot( _size );
        glFrontFace( GL_CCW );
    }

     META_Object( osg, TeapotDrawable );

    /** Compute the bounding sphere around Drawables's geometry.*/
    virtual osg::BoundingSphere computeBound() const
    {
          osg::BoundingSphere bs( osg::Vec3(0, 0, 0), _size );
          return bs;
    }
    /** Compute the bounding box around Drawables's geometry.*/
    virtual osg::BoundingBox computeBoundingBox() const
    {
        osg::Vec3 min(-_size,-_size,-_size), max(_size, _size, _size);
        return osg::BoundingBox(min, max);
        
    }

private:
    float _size;

};

int main()
{
    osg::Group* root = new osg::Group;
    osgViewer::Viewer viewer;

    osg::Geode* geode = createGeode(osg::Vec3(0,0,0));
    geode->addDrawable(createQuad(osg::Vec3(-0.5,0,1.5)));
    geode->addDrawable(createOctahedron(osg::Vec3(-3,0,2)));
    geode->addDrawable(createTessellatePolygon(osg::Vec3(-3,0,4)));
    geode->addDrawable(createTessellatePolygon(osg::Vec3(0,0,4),false));

    osg::Geometry* pGeometry = createQuadStrip(osg::Vec3(3,0,4));
    osg::TriangleFunctor<FaceCollector> functor;
    pGeometry->accept( functor );
    geode->addDrawable(pGeometry);
   
    {  // user drawable
        osg::MatrixTransform* pMT = new osg::MatrixTransform;
        pMT->setMatrix(osg::Matrix::rotate(osg::PI_2,osg::Vec3(1,0,0)) * osg::Matrix::translate(osg::Vec3(3,0,2.5)));
        osg::Geode* pTeapotGeode = new osg::Geode;
        pMT->addChild(pTeapotGeode);
        pTeapotGeode->addDrawable(new TeapotDrawable());
        root->addChild(pMT);
    }
    root->addChild(geode);
    viewer.setSceneData(root);
    return viewer.run();
}

osg::Geode* createGeode(osg::Vec3 pos)
{
    osg::ref_ptr<osg::ShapeDrawable> shape1 = new osg::ShapeDrawable(new osg::Box(pos + osg::Vec3(-3.0f,0.0f,0.0f),2,2,1));
    osg::ref_ptr<osg::ShapeDrawable> shape2 = new osg::ShapeDrawable(new osg::Cone(pos + osg::Vec3(0.0f,0.0f,0.0f),1.0f,1.0f));
    osg::ref_ptr<osg::ShapeDrawable> shape3 = new osg::ShapeDrawable(new osg::Sphere(pos + osg::Vec3(3.0f,0.0f,0.0f),1.0));

    shape2->setColor(osg::Vec4(0.0f,0.0f,1.0f,1.0f));  
    shape3->setColor(osg::Vec4(1,0,0,1));

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(shape1);
    geode->addDrawable(shape2);
    geode->addDrawable(shape3);

    return geode.release();
}

osg::Geometry* createQuad(osg::Vec3 pos)
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back( pos + osg::Vec3(0.0f, 0.0f, 0.0f) );
    vertices->push_back( pos + osg::Vec3(1.0f, 0.0f, 0.0f) );
    vertices->push_back( pos + osg::Vec3(1.0f, 0.0f, 1.0f) );
    vertices->push_back( pos + osg::Vec3(0.0f, 0.0f, 1.0f) );

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back( osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f) );
    colors->push_back( osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) );
    colors->push_back( osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f) );
    colors->push_back( osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f) );

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back( osg::Vec3(0.0f,-1.0f, 0.0f) );

    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
    quad->setVertexArray( vertices.get() );
    quad->setNormalArray( normals.get() );
    quad->setNormalBinding( osg::Geometry::BIND_OVERALL );
    quad->setColorArray( colors.get() );
    quad->setColorBinding( osg::Geometry::BIND_PER_VERTEX );
    quad->addPrimitiveSet( new osg::DrawArrays(GL_QUADS, 0, 4) );

    return quad.release();
}
osg::Geometry* createOctahedron(osg::Vec3 pos)
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(6);
    
    (*vertices)[0].set( 0.0f, 0.0f, 1.0f);
    (*vertices)[1].set(-0.5f,-0.5f, 0.0f);
    (*vertices)[2].set( 0.5f,-0.5f, 0.0f);
    (*vertices)[3].set( 0.5f, 0.5f, 0.0f);
    (*vertices)[4].set(-0.5f, 0.5f, 0.0f);
    (*vertices)[5].set( 0.0f, 0.0f,-1.0f);

    for(int i = 0; i < 6; ++i)
        (*vertices)[i] += pos;

    osg::ref_ptr<osg::DrawElementsUInt> indices =
        new osg::DrawElementsUInt(GL_TRIANGLES, 24);
    (*indices)[0] = 0; (*indices)[1] = 1; (*indices)[2] = 2;
    (*indices)[3] = 0; (*indices)[4] = 2; (*indices)[5] = 3;
    (*indices)[6] = 0; (*indices)[7] = 3; (*indices)[8] = 4;
    (*indices)[9] = 0; (*indices)[10]= 4; (*indices)[11]= 1;
    (*indices)[12]= 5; (*indices)[13]= 2; (*indices)[14]= 1;
    (*indices)[15]= 5; (*indices)[16]= 3; (*indices)[17]= 2;
    (*indices)[18]= 5; (*indices)[19]= 4; (*indices)[20]= 3;
    (*indices)[21]= 5; (*indices)[22]= 1; (*indices)[23]= 4;

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray( vertices.get() );
    geom->addPrimitiveSet( indices.get() );
    osgUtil::SmoothingVisitor::smooth( *geom );

    return geom.release();

}   

osg::Geometry* createTessellatePolygon(osg::Vec3 pos,bool useTessellate)
{
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    osg::ref_ptr<osg::Vec3Array> vertics = new osg::Vec3Array;
    vertics->push_back( pos+ osg::Vec3(0.0f, 0.0f, 0.0f) );
    vertics->push_back( pos+ osg::Vec3(2.0f, 0.0f, 0.0f) );
    vertics->push_back( pos+ osg::Vec3(2.0f, 0.0f, 1.0f) );
    vertics->push_back( pos+ osg::Vec3(1.0f, 0.0f, 1.0f) );
    vertics->push_back( pos+ osg::Vec3(1.0f, 0.0f, 2.0f) );
    vertics->push_back( pos+ osg::Vec3(2.0f, 0.0f, 2.0f) );
    vertics->push_back( pos+ osg::Vec3(2.0f, 0.0f, 3.0f) );
    vertics->push_back( pos+ osg::Vec3(0.0f, 0.0f, 3.0f) );

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back( osg::Vec3(0.0,-1.0f, 0.0f) );
    geom->setVertexArray(vertics);
    geom->setNormalArray(normals);
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->addPrimitiveSet( new osg::DrawArrays(GL_POLYGON,0,8) );

    if(useTessellate)
    {
        osgUtil::Tessellator tessellator;
        tessellator.retessellatePolygons( *geom );
    }
    return geom.release();
}



osg::Geometry* createQuadStrip(osg::Vec3 pos)
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back( pos + osg::Vec3(0.0f, 0.0f, 0.0f) );
    vertices->push_back( pos + osg::Vec3(0.0f, 0.0f, 1.0f) );
    vertices->push_back( pos + osg::Vec3(1.0f, 0.0f, 0.0f) );
    vertices->push_back( pos + osg::Vec3(1.0f, 0.0f, 1.5f) );
    vertices->push_back( pos + osg::Vec3(2.0f, 0.0f, 0.0f) );
    vertices->push_back( pos + osg::Vec3(2.0f, 0.0f, 1.0f) );
    vertices->push_back( pos + osg::Vec3(3.0f, 0.0f, 0.0f) );
    vertices->push_back( pos + osg::Vec3(3.0f, 0.0f, 1.5f) );
    vertices->push_back( pos + osg::Vec3(4.0f, 0.0f, 0.0f) );
    vertices->push_back( pos + osg::Vec3(4.0f, 0.0f, 1.0f) );
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back( osg::Vec3(0.0f,-1.0f, 0.0f) );
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray( vertices.get() );
    geom->setNormalArray( normals.get() );
    geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
    geom->addPrimitiveSet( new osg::DrawArrays(GL_QUAD_STRIP, 0, 10) );

    return geom.release();
}