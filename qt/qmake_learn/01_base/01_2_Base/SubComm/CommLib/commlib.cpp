#include "commlib.h"
#include <iostream>
CommLib::CommLib()
{
}

 float Add(float a, float b)
 {
     return a + b;
 }
 void CommLib::Test()
 {
     std::cout << "test " << std::endl;
 }

 bool CommLib::isOK()
 {
     return false;
 }
 
 CommLib::~CommLib()
 {

 }