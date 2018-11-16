//vertex_displacement.cpp

#include <osg/Geode>
#include <osg/Group>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Shader>
#include <osg/Program>

#include "comm/Comm.h"


const char* vs_code = {
    "uniform sampler2D defaultTex;\n"
    "varying float height;\n"
    "void main()\n"
    "{\n"
    "   vec2 uv = gl_MultiTexCoord0.xy;\n"
    "   vec4 color = texture2D(defaultTex, uv);\n"
    "   height = 0.3*color.x + 0.6*color.y + 0.1*color.z;\n"
    
    "  vec4 pos = gl_Vertex; \n"
    "  pos.z = pos.z + 100.0*height;\n" // 高度根据颜色生成，高度主要取决rgb各个分量的之和
    "  gl_Position = gl_ModelViewProjectionMatrix * pos;\n"
    "}\n"

};


const char* fragCode = {
    "varying float height;\n"
    "const vec4 lowerColor = vec4(0.1, 0.1, 0.1, 1.0);\n"
    "const vec4 higherColor = vec4(0.2, 1.0, 0.2, 1.0);\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = mix(lowerColor, higherColor, height);\n" // 颜色插值
    "}\n"
};

osg::Geometry* createGridGeometry( unsigned int colum, unsigned int row)
{
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(colum*row);
	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array(colum*row);
	
	for( unsigned int i = 0; i< row; ++i)
	{
		for( unsigned int j = 0; j < colum; ++j)
		{
			(*vertices)[i*colum + j].set(float(i),float(j),0.0f);
			(*texcoords)[i*colum +j].set(float(i)/float(row),float(j)/float(colum));
		}
	}
	
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setUseDisplayList(false);
	geom->setUseVertexBufferObjects(true);
	geom->setVertexArray(vertices.get());
	geom->setTexCoordArray(0,texcoords.get());
	
	for(unsigned int i = 0; i < row-1; ++i) 
	{
		osg::ref_ptr<osg::DrawElementsUInt> de = new osg::DrawElementsUInt(GL_QUAD_STRIP,colum*2);
		for(unsigned int j = 0; j < colum; ++j)
		{
			(*de)[j*2 + 0] = i * colum + j;
			(*de)[j*2 + 1] = (i+1) * colum + j;
		}
		geom->addPrimitiveSet(de.get());
		
	}
	geom->setInitialBound(osg::BoundingBox(-1.0f,-1.0f,-100.0f,1.0f,1.0f,100.0f));
	
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	texture->setImage(osgDB::readImageFile("Images/osg256.png"));
	texture->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::LINEAR);
	texture->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::LINEAR);
	geom->getOrCreateStateSet()->setTextureAttributeAndModes(0,texture.get());
	geom->getOrCreateStateSet()->addUniform(new osg::Uniform("defaultText",0));
	
	osg::ref_ptr<osg::Program> program = new osg::Program;
	program->addShader(new osg::Shader(osg::Shader::VERTEX,vs_code));
	program->addShader(new  osg::Shader(osg::Shader::FRAGMENT,fragCode));
	
	geom->getOrCreateStateSet()->setAttributeAndModes(program.get());
	return geom.release();
}

void main()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(createGridGeometry(512,512));
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	
	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(geode.get());
	
	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	viewer.run();
	
}