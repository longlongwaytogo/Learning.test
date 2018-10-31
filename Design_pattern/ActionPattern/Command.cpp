// Command.cpp
/*
Command：抽象命令类，一般是一个抽象类或者接口。在其中定义了命令的执行execute()、undo()等操作。
ConcreteCommand：具体命令类，实现了抽象命令类的方法，并且持有命令接受者的引用。具体执行方法时，调用接受者的相关操作。
Invoker：请求发送者，通过命令对象执行请求。针对抽象命令类编程，并不需要关心对应的命令如何执行，被谁执行。与抽象命令的关联关系也不固定，可以通过注入或者构造的方法或者采用XML和反射的方法来进行关联。
Reciver：请求接受者，执行请求的相关操作，对请求进行详细的业务处理。


1. 命令模式是通过命令发送者和命令执行者的解耦来完成对命令的具体控制的。

2. 命令模式是对功能方法的抽象，并不是对对象的抽象。

3. 命令模式是将功能提升到对象来操作，以便对多个功能进行一系列的处理以及封装。

*/

#include <iostream>
#include <string>
using namespace std;


class Command
{
public:
	virtual ~Command(){}
	virtual void Execute() = 0;
};

class Receiver
{
public:
	Receiver(){}
	void Action()
	{
			cout << "recevier action" << endl;
	}
};


class ConcreteCommand :public Command
{
public:
	ConcreteCommand(Receiver* recevier):_recevier(recevier){}
	
	void Execute()
	{
		_recevier->Action();
	}	
private:
	Receiver* _recevier;
};

class Invoker
{
public:
	Invoker(Command* cmd)
	{
		_cmd =cmd;
	}
	
	void Inoke()
	{
		_cmd->Execute();
	}
private:
	Command* _cmd;
};

int main()
{
	Receiver * rev = new Receiver();
	Command* cmd = new ConcreteCommand(rev);
	Invoker* inv = new Invoker(cmd);
	
	inv->Inoke();
	
	delete rev;
	delete cmd;
	delete inv;
	
	return 0;
}