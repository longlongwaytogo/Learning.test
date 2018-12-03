#include <osgDB/ReadFile>
#include <osgDB/FileNameUtils>
#include <osgDB/ReaderWriter>
#include <osgUtil/Simplifier>
#include <osgViewer/Viewer>
#include <sstream>
#include <iostream>

class ReaderWriteSIMP : public osgDB::ReaderWriter
{
public:
	ReaderWriteSIMP(){ supportsExtension("simp","Simplification Pseudo-loader");}
	
	virtual const char* className() const{
		return "simplification pseudo-loader";
	}
	
	virtual bool acceptsExtension(const std::string& ext) const 
	{
		return osgDB::equalCaseInsensitive(ext,"simp");
	}
	
	virtual osgDB::ReaderWriter::ReadResult readNode(
	const std::string& fileName,
	const osgDB::ReaderWriter::Options* options) const;
	
};
