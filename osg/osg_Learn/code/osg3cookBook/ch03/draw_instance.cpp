// Draw_Instance.cpp

#include <iostream>
#include <string>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/Program>
#include <osg/Shader>
#include <osg/Array>
#include <osg/Image>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

// gl_instanceID/256.0 计算出当前实例位于整个实例的位置，
// 整数部分是y方向的行数（处以256，即为百分比），小数部分是x方向百分比
const char* vertex_Shader = {
"uniform sampler2D defaultTex; \n"
"const float PI2 = 6.2831852; \n"
"void main() \n"
"{\n"
"	float r = float(gl_InstanceID)/256.0;\n"   
"   vec2 uv = vec2(fract(r),float(r)/256.0);\n"
"	vec4 pos = gl_Vertex + vec4(uv.s * 384.0,32.0 * sin(uv.s * PI2),uv.t * 384.0, 1.0);\n"
"   gl_FrontColor = texture2D(defaultTex,uv);\n"
"	gl_Position = gl_ModelViewProjectionMatrix * pos;\n"
"}"
};


osg::Drawable* createInstanceGeometry(int numInstance)
{
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
	osg::Vec3Array* vertices =  new osg::Vec3Array;
	vertices->push_back(osg::Vec3(-0.5, 0, -0.5));
	vertices->push_back(osg::Vec3( 0.5, 0, -0.5));
	vertices->push_back(osg::Vec3( 0.5, 0,  0.5));
	vertices->push_back(osg::Vec3(-0.5, 0,  0.5));
	
	geometry->setVertexArray(vertices);
	geometry->setUseDisplayList(false);
	geometry->setUseVertexBufferObjects(true);
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4,numInstance));
	geometry->setInitialBound( osg::BoundingBox(-1.0f,-32.0f,-1.0f, 192.0f, 32.0f, 192.0f) );
	
	osg::ref_ptr<osg::Image> img = osgDB::readImageFile("Images/osg256.png");
	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
	tex->setImage(img.get());
	tex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR );
	tex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR );
	geometry->getOrCreateStateSet()->setTextureAttributeAndModes(0,tex.get());
	geometry->getOrCreateStateSet()->addUniform(new osg::Uniform("defaultTex",0) );
	
	osg::ref_ptr<osg::Program> program = new osg::Program;
	program->addShader(new osg::Shader(osg::Shader::VERTEX,vertex_Shader) );
	geometry->getOrCreateStateSet()->setAttributeAndModes(program.get() );
	
	return geometry.release();
}

void main()
{
	osgViewer::Viewer viewer;
	viewer.setUpViewInWindow(10,10,900,700);
	osg::Geode* geode = new osg::Geode;
	geode->addDrawable( createInstanceGeometry(256*256) );
	viewer.setSceneData(geode);
	viewer.realize();
	viewer.run();

}

