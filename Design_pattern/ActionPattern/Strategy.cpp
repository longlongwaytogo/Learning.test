// Strategy pattern
/*
Strategy策略模式:定义一系列的算法,把每一个算法封装起来, 并且使它们可相互替换。本模式使得算法可独立于使用它的客户而变化。也称为政策模式(Policy)。

Strategy 与 State区别：
如果系统中某个类的某一行为存在多种实现方式，而且这些实现方式可以互换时使用策略模式，是算法一个维度的抽象。
如果系统中某个类的对象存在多种状态，不同状态下行为有差异，而且这些状态之间可以发生转换时使用状态模式。

Stragegy 与 Brige区别：
Bridge模式是两个维度的抽象，实现基类子类逻辑实现，通过抽象接口组合关联实现基类，在两个模块子类间进行桥接搭配统一接口。而Strategy模式调用方式没有抽象接口的，Strategy是一个维度的抽象。
--------------------- 
作者：Sam-Cen 
来源：CSDN 
原文：https://blog.csdn.net/blues1021/article/details/48384303 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/

#include <iostream>

class Strategy
{
public:
	virtual void Interface() = 0;
	virtual ~Strategy(){}
};

class ConCreateStrategyA : public Strategy
{
public:
	virtual void Interface()
	{
		std::cout << "ConCreateStrategyA::Interface..." << std::endl;
	}
};

class ConCreateStrategyB : public Strategy
{
public:
	virtual void Interface()
	{
		std::cout << "ConCreateStrategyB::Interface..." << std::endl;
	}
};

class Context 
{
public:
	Context(Strategy* sg)
	{
		_sg = sg;
	}
	
	void DoStrategy()
	{
		_sg->Interface();
	}
private:
	Strategy* _sg;
};

int main()
{
	ConCreateStrategyA* pStrategyA = new ConCreateStrategyA();
	Context* pContext = new Context(pStrategyA);
	pContext->DoStrategy();
	
	delete pStrategyA;
	delete pContext;
	
	return 0;
}