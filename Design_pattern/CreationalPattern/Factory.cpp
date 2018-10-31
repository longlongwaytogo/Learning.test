// Factory Methord pattern
/*
Factory模式两个最重要的功能

（1）定义创建对象的接口，封装了对象的创建。

（2）使得具体化类的工作延迟到了子类中。
*/

#include <iostream>
class Product
{
public:
	virtual ~Product(){}
	virtual void Done() = 0;
	
};

class Factory
{
	public:
	virtual ~Factory(){}
	virtual Product* CreateProduct() = 0;
};

class ConcreateProductA : public Product
{
public:
	ConcreateProductA()
	{}
	void Done()
	{
		std::cout << "Product A do sth.." << std::endl;
	}
};

class FactoryA : public Factory
{
public:
	Product* CreateProduct()
	{
		return new ConcreateProductA();
	}
};

int main()
{
	FactoryA* pFactory = new FactoryA();
	Product* pProductA = pFactory->CreateProduct();
	pProductA->Done();
	
	delete pProductA;
	delete pFactory;
	
	return 0;
}
 