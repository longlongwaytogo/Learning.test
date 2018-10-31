/*Facade（外观）：模式的核心，被 Client 调用，知晓相关子系统的功能和责任。在正常情况下，它将所有从 Client 发来的请求委派到相应的子系统去，让子系统处理。
SubSystem（子系统）：可以同时有一个或者多个子系统，子系统可以是一个单独的类或类的集合。每个子系统都可以被 Client 直接调用，或者被 Facade 调用，它处理由 Facade 传过来的请求。子系统并不知道 Facade 的存在，对于子系统而言，Facade 仅仅是另外一个 Client 而已。
优缺点

优点：

对 Client 屏蔽子系统组件，减少了 Client 处理的对象数目，并使得子系统使用起来更加容易。通过引入外观模式，Client 的代码将变得很简单，与之关联的对象也很少。
实现了子系统与 Client 之间的松耦合关系，这使得子系统的组件变化不会影响到调用它的 Client，只需要调整 Facade 即可。
降低了大型软件系统中的编译依赖性，并简化了系统在不同平台之间的移植过程，因为编译一个子系统一般不需要编译所有其他的子系统。一个子系统的修改对其他子系统没有任何影响，而且子系统内部变化也不会影响到外观对象。
只是提供了一个访问子系统的统一入口，并不影响用户直接使用子系统类。
缺点：

不能很好地限制 Client 使用子系统类，如果对 Client 访问子系统类做太多的限制，则会减少可变性和灵活性。
在不引入抽象外观类的情况下，增加新的子系统可能需要修改 Facade 或 Client 的源代码，违背了“开闭原则”。
适用场景

当要为一个复杂子系统提供一个简单接口时。该接口可以满足大多数用户的需求，而且用户也可以越过外观类直接访问子系统。
Client 与多个子系统之间存在很大的依赖性。引入外观类将子系统与 Client 以及其他子系统解耦，可以提高子系统的独立性和可移植性。
在层次化结构中，可以使用外观模式定义系统中每一层的入口。层与层之间不直接产生联系，而通过外观类建立联系，降低层之间的耦合度
--------------------- 
作者：一去丶二三里 
来源：CSDN 
原文：https://blog.csdn.net/liang19890820/article/details/70850367 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/

#include <iostream>
using namespace std;

class SubSystem1 {
public:
	void Operation() {
		cout << "subSystem1 operation..." << endl;
	}
};

class SubSystem2 {
public:
	void Operation() {
		cout << "subsystem2 Operation..." << endl;
	}
};

class Facade {
public:
	Facade() {
		_sub1 = new SubSystem1();
		_sub2 = new SubSystem2();
	}
	
	~Facade() {
		delete _sub1;
		delete _sub2;
	}
	
	void OperationWraper()
	{
		_sub1->Operation();
		_sub2->Operation();
	}
	
private:
	SubSystem1* _sub1;
	SubSystem2* _sub2;
};

int main()
{
	Facade* facade = new Facade();
	facade->OperationWraper();
	
	delete facade;
	
	return 0;
}