// Proxy pattern

/*
代理模式（Proxy Pattern），就是一个类可以代表另一个类的功能。这种类型的设计模式属于结构性模式。

为了使代理类和被代理类有相同的功能，通常实现同一个接口。

作用：为对象A提供一种代理用来控制这个对象A

主要解决问题： 在直接访问对象时带来的问题，比如对象在不同的进程（即跨进程），对象在远程服务器上等。对象由于某些原因，直接去访问会给使用者或者系统结构带来很多麻烦（创建对象消耗很大，某些操作需要安全控制/权限问题）等，因此我们在访问这个对象时加上一个对此对象的访问层（即代理类）。
--------------------- 
作者：石头_ 
来源：CSDN 
原文：https://blog.csdn.net/qq475703980/article/details/81211560 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
#include <iostream>

class Object
{
public:
	void Request()
	{
		std::cout <<"Object Request" << std::endl;
	}
};

class ObjectProxy
{
public:
	ObjectProxy(Object* obj):_obj(obj)
	{
	}
	
	void Request()
	{
		_obj->Request();
	}
private:
	Object* _obj;
};


int main()
{
	
	Object* pObj = new Object;
	ObjectProxy* pProxy = new ObjectProxy(pObj);
	pProxy->Request();
	
	delete pProxy;
	delete pObj;
	
	return 0;
}