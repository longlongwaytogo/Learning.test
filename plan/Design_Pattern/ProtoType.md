## 1.原型模式（Protype)

## 1.1 什么是原型模式？

用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。这这个定义中，最重要的一个词是“拷贝”，也就是口头上的复制，而这个拷贝，也就是原型模式的精髓所在。

## 1.2 为什么要使用原型模式？
简单的来说，我们使用原型模式，就是为了创建对象。
## 1.3 使用场景：  


- 当我们的对象类型不是开始就能确定的，而这个类型是在运行期确定的话，那么我们通过这个类型的对象克隆出一个新的对象比较容易一些；

- 有的时候，我们需要一个对象在某个状态下的副本，此时，我们使用原型模式是最好的选择；例如：一个对象，经过一段处理之后，其内部的状态发生了变化；这个时候，我们需要一个这个状态的副本，如果直接new一个新的对象的话，但是它的状态是不对的，此时，可以使用原型模式，将原来的对象拷贝一个出来，这个对象就和之前的对象是完全一致的了；

- 当我们处理一些比较简单的对象时，并且对象之间的区别很小，可能就几个属性不同而已，那么就可以使用原型模式来完成，省去了创建对象时的麻烦了；

- 有的时候，创建对象时，构造函数的参数很多，而自己又不完全的知道每个参数的意义，就可以使用原型模式来创建一个新的对象，不必去理会创建的过程，让创建过程见鬼去吧。


**所以，在上述的的情况下，在设计的时候，适当的考虑一下原型模式，减少对应的工作量，减少程序的复杂度，提高效率。**


## 1.4 用UML类图表示原型模式
![Protype](res/protype.png)

- 继承自Prototype基类，并实现其Clone接口函数，实现 克制

## 1.5 代码：
	/*
	** FileName     : PrototypePatternDemo
	** Author       : Jelly Young
	** Date         : 2013/11/25
	** Description  : More information, please go to http://www.jellythink.com
	*/
	
	#include <iostream>
	using namespace std;
	
	//接口
	class Prototype
	{
	public :
		Prototype(){}
		virtual ~Prototype(){}
	
		virtual Prototype * Clone() = 0;
	};
	
	//实现
	class ConcretePrototype : public Prototype
	{
	public :
		ConcretePrototype():m_counter(0){}
		virtual ~ConcretePrototype(){}
	
		//拷贝构造函数
		ConcretePrototype( const ConcretePrototype & rhs)
		{
			m_counter = rhs .m_counter;
		}
	
		//复制自身
		virtual ConcretePrototype * Clone()
		{
			//调用拷贝构造函数
			return new ConcretePrototype (*this );
		}
	
	private :
		int m_counter;
	};
	
	int main(int argc , char **argv)
	{
		//生成对像
		ConcretePrototype * conProA = new ConcretePrototype ();
	
		//复制自身
		ConcretePrototype * conProB = conProA->Clone();
	
		delete conProA;
		conProA= NULL ;
	
		delete conProB;
		conProB= NULL ;
	
		return 0;
	}

link:   
[http://www.jellythink.com/archives/105]()  
[http://www.cnblogs.com/jiese/p/3164428.html]()  