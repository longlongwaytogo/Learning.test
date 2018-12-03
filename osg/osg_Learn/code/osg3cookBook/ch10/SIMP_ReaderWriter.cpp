
#include "SIMP_ReaderWriter.h"

#include <osgDB/ReaderWriter>

osgDB::ReaderWriter::ReadResult ReaderWriteSIMP::readNode(
    const std::string& fileName,
    const osgDB::ReaderWriter::Options* options) const
{
	std::string ext = osgDB::getLowerCaseFileExtension(fileName);
	if(!acceptsExtension(ext))
		return ReadResult::FILE_NOT_HANDLED;
		
		double ratio = 1.0;
		if(options)
		{
			std::stringstream ss(options->getOptionString());
			ss >> ratio;
		}
		
		osg::Node* scene = osgDB::readNodeFile(
		osgDB::getNameLessExtension(fileName));
		if(scene)
		{
			osgUtil::Simplifier simplifier(ratio);
			scene->accept(simplifier);
		}
		return scene;
		
}
	

REGISTER_OSGPLUGIN(simp,ReaderWriteSIMP)
