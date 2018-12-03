#include <osg/Group>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <iostream>
#include <sstream>
#include <osg/Node>

#include <osgDB/ReadFile>
#include <osgDB/FileNameUtils>
#include <osgDB/ReaderWriter>
#include <osgUtil/Simplifier>
#include <osgViewer/Viewer>
#include <sstream>
#include <iostream>

#include "SIMP_ReaderWriter.h"


//class ReaderWriteSIMP : public osgDB::ReaderWriter
//{
//public:
//    ReaderWriteSIMP(){ supportsExtension("simp","Simplification Pseudo-loader");}
//
//    virtual const char* className() const{
//        return "simplification pseudo-loader";
//    }
//
//    virtual bool acceptsExtension(const std::string& ext) const 
//    {
//        return osgDB::equalCaseInsensitive(ext,"simp");
//    }
//
//    virtual ReadResult readNode(
//        const std::string& fileName,
//        const osgDB::ReaderWriter::Options* options) const
//    {
//        std::string ext = osgDB::getLowerCaseFileExtension(fileName);
//        if(!acceptsExtension(ext))
//            return ReadResult::FILE_NOT_HANDLED;
//
//        double ratio = 1.0;
//        if(options)
//        {
//            std::stringstream ss(options->getOptionString());
//            ss >> ratio;
//        }
//
//        osg::Node* scene = osgDB::readNodeFile(
//            osgDB::getNameLessExtension(fileName));
//        if(scene)
//        {
//            osgUtil::Simplifier simplifier(ratio);
//            scene->accept(simplifier);
//        }
//        return scene;
//
//    }
//
//};
    REGISTER_OSGPLUGIN(simp,ReaderWriteSIMP)


int main(int argc, char** agrv)
{
    std::string ratio ="0.2";

	osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile("cow.osg.simp",new osgDB::Options(ratio));
	
	
	osgViewer::Viewer viewer;
	viewer.setSceneData(scene);
	viewer.run();
	return 0;
}
