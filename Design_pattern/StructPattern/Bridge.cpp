// Bridge pattern
/* 
Bridge模式主要是解决多维度问题，什么意思呢？类似于n*m这个公式，n种具体实现和m种具体的实现，最多可以有n*m种组合方式。
下面这篇文章对Bridge模式讲解的通俗易懂，于是转了过来。

对于有两个变化维度（即两个变化的原因）的系统，一半采用桥接模式。桥接模式将继承关系转换为关联关系，从而降低了类与类之间的耦合，减少了代码编写量。


1．Bridge模式使用“对象间的组合关系”解耦了抽象和实现之间固有的绑定关系，使得抽象和实现可以沿着各自的维度来变化。
2．所谓抽象和实现沿着各自维度的变化，即“子类化”它们，得到各个子类之后，便可以任意它们，从而获得不同路上的不同汽车。
3．Bridge模式有时候类似于多继承方案，但是多继承方案往往违背了类的单一职责原则（即一个类只有一个变化的原因），复用性比较差。Bridge模式是比多继承方案更好的解决方法。
4．Bridge模式的应用一般在“两个非常强的变化维度”，有时候即使有两个变化的维度，但是某个方向的变化维度并不剧烈——换言之两个变化不会导致纵横交错的结果，并不一定要使用Bridge模式。
--------------------- 
作者：灬鬼谷灬 
来源：CSDN 
原文：https://blog.csdn.net/yo746862873/article/details/51441865 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/

/*
模式优缺点
桥接模式的优点
	分离抽象接口及其实现部分。 
	桥接模式有时类似于多继承方案，但是多继承方案违背了类的单一职责原则（即一个类只有一个变化的原因），复用性比较差，而且多继承结构中类的个数非常庞大，桥接模式是比多继承方案更好的解决方法。 
	桥接模式提高了系统的可扩充性，在两个变化维度中任意扩展一个维度，都不需要修改原有系统。 
	实现细节对客户透明，可以对用户隐藏实现细节。

桥接模式的缺点
	桥接模式的引入会增加系统的理解与设计难度，由于聚合关联关系建立在抽象层，要求开发者针对抽象进行设计与编程。
	桥接模式要求正确识别出系统中两个独立变化的维度，因此其使用范围具有一定的局限性。
模式适用环境

在以下情况下可以使用桥接模式：
	如果一个系统需要在构件的抽象化角色和具体化角色之间增加更多的灵活性，避免在两个层次之间建立静态的继承联系，通过桥接模式可以使它们在抽象层建立一个关联关系。
	抽象化角色和实现化角色可以以继承的方式独立扩展而互不影响，在程序运行时可以动态将一个抽象化子类的对象和一个实现化子类的对象进行组合，即系统需要对抽象化角色和实现化角色进行动态耦合。
	一个类存在两个独立变化的维度，且这两个维度都需要进行扩展。
	虽然在系统中使用继承是没有问题的，但是由于抽象化角色和具体化角色需要独立变化，设计要求需要独立管理这两者。
	对于那些不希望使用继承或因为多层次继承导致系统类的个数急剧增加的系统，桥接模式尤为适用。

*/
#include <iostream>

class Abstraction
{
public:
	virtual void Operation() = 0;
	virtual ~Abstraction(){}
};

class AbstractionImpl
{
	public:
		virtual void Operation() = 0; 
		virtual ~AbstractionImpl(){}
};

class ConcreteAbstractionImpl: public AbstractionImpl
{
	public:
	ConcreteAbstractionImpl(){}
	void Operation()
	{
		std::cout << "ConcreateAbstractionImpl Operation" << std::endl;
	}
};

class RefinedAbstraction :public Abstraction {
	public:
		RefinedAbstraction(AbstractionImpl* impl) {
			_impl = impl;
		}
		void Operation() {
			_impl->Operation();
		}
	private:
		AbstractionImpl* _impl;
};


int main()
{
	AbstractionImpl* pImpl = new ConcreteAbstractionImpl();
	RefinedAbstraction* pRefined = new RefinedAbstraction(pImpl);
	pRefined->Operation();
	
	delete pRefined;
	delete pImpl;
	
	return 0;
}