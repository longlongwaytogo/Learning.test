#include <osg/io_utils>
#include <osg/MatrixTransform>
#include <osg/ValueObject>
#include <osgDB/WriteFile>
#include <iostream>

class GetValueVisitor: public osg::ValueObject::GetValueVisitor
{
public:
	virtual void apply(bool value)
	{
		std::cout <<"Bool:" << value << std::endl;
	}
	
	virtual void apply( int value )
    { std::cout << "Integer: " << value << std::endl; }
    
    virtual void apply( const std::string& value )
    { std::cout << "String: " << value << std::endl; }
    
    virtual void apply( const osg::Matrix& value )
    { std::cout << "Matrix: " << value << std::endl; }
};

int main()
{
	osg::Matrix matrix;
	
	osg::ref_ptr<osg::MatrixTransform> node = new osg::MatrixTransform;
	node->setMatrix(matrix);
	node->setUserValue("Creator",std::string("longlongway"));
	node->setUserValue("NodeID", 100);
	node->setUserValue("IsMain",true);
	node->setUserValue("OriginMatrix",matrix);
	
	osgDB::writeNodeFile(*node, "result.osgx");
	
	osg::UserDataContainer* udc = node->getOrCreateUserDataContainer();
	for(unsigned int i = 0; i< udc->getNumUserObjects();++i)
	{
		osg::ValueObject* valueObj = dynamic_cast<osg::ValueObject*>(udc->getUserObject(i));
		if(valueObj)
		{
			GetValueVisitor gvv;
			valueObj->get(gvv);
			
		}
	}
	
}