#include <QDebug>
#include <QObject>
#include "myobject.h"

MyObject::MyObject():Object()
{
	std::cout << "MyObject::MyObject() \n";
}

MyObject::~MyObject()
{
	
	std::cout <<MyObject::~MyObject() \n";
}

