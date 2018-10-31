// Builder pattern
//将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示
/*
Builder负责Product类对象的具体过程构建，Director负责指导Build，要求Builder按照其指定的顺序去完成Produt的构造。最后通过Builder返回建造后的结果。网上有人对此种模式进行了形象的类比。

（转）

简单地说，就好象我要一座房子住，可是我不知道怎么盖（简单的砌墙，层次较低），也不知道怎么样设计（建几个房间，几个门好看，层次较高），于是我需要找一帮民工，他们会砌墙，还得找个设计师，他知道怎么设计，我还要确保民工听设计师的领导，而设计师本身也不干活，光是下命令，这里砌一堵墙，这里砌一扇门，这样民工开始建设，最后，我可以向民工要房子了。在这个过程中，设计师是什么也没有，除了他在脑子里的设计和命令，所以要房子也是跟民工要，记住了！
*/

#include <iostream>
class Product {
public:
	Product()
	{
		std::cout << "Product " << std::endl;
	}
	void Done()
	{
		std::cout <<"product done" << std::endl;
	}
};

// Builder
class Builder {
public:
	virtual ~Builder(){}
	virtual void BuildPartA() = 0;
	virtual void BuildPartB() = 0;
	virtual void BuildPartC() = 0;
	virtual Product* GetProduct() = 0;
};

class ConcreateBuilder: public Builder {
public:
	void BuildPartA() {
		std::cout << "build part A" << std::endl;
	}
	
	void BuildPartB() {
		std::cout << "build part B" << std::endl;
	}
	
	void BuildPartC() {
		std::cout << "build part C" << std::endl;
	}
	
	Product* GetProduct()
	{
		return new Product();
	}
};

class Director {
public:
	Director(Builder* pBuilder) {
		_builder = pBuilder;
	}
	
	void Constroct() {
		_builder->BuildPartA();
		_builder->BuildPartB();
		_builder->BuildPartC();
	}
	
private:
	Builder* _builder;
};

int main()
{
	Builder* pBuilder = new ConcreateBuilder();  // 工人
	Director* pDirector = new Director(pBuilder); // 设计师
	
	pDirector->Constroct(); // 设计师指挥工人建造
	Product* product = pBuilder->GetProduct();  // 工人完成建造
	product->Done();
	
	delete pDirector;
	delete pBuilder;
	delete product;
	
	
	return 0;
}