// Interpreter.cpp
/*
       Interpreter模式也叫解释器模式，是由GoF提出的23种设计模式中的一种。Interpreter是行为模式之一，它是一种特殊的设计模式，它建立一个解释器，对于特定的计算机程序设计语言，用来解释预先定义的文法。
	   
	   适用场景： 1.当有一个语言需要解释执行，并且你可将该语言中的句子表示为一个抽象语法树，可以使用解释器模式。而当存在以下情况时该模式效果最好
        2.该文法的类层次结构变得庞大而无法管理。此时语法分析程序生成器这样的工具是最好的选择。他们无需构建抽象语法树即可解释表达式，这样可以节省空间而且还可能节省时间。
        3.效率不是一个关键问题，最高效的解释器通常不是通过直接解释语法分析树实现的，而是首先将他们装换成另一种形式，例如，正则表达式通常被装换成状态机，即使在这种情况下，转换器仍可用解释器模式实现，该模式仍是有用的
		
*/

#include <iostream>
#include <string>
using namespace std;

class Context {};

class Expression {
public:
	virtual ~Expression() {}
	virtual void Interpret(const Context& ctx) = 0;
};

class TernimalExpression :public Expression {
public:
	TernimalExpression(const string& statement) {
		_statement = statement;
	}
	
	void Interpret(const Context& ctx) {
		cout << this->_statement << " -- TernimalExpression" << endl;
	}
private:
	string _statement;
};

class NonTerminalExpression :public Expression {
public:
	NonTerminalExpression(Expression* expression, int times) {
		_expression = expression;
		_times = times;
	}
	void Interpret(const Context& ctx) {
		for(int i = 0; i < _times; ++i)
		{
			_expression->Interpret(ctx);
		}
	}
private:
	Expression* _expression;
	int _times;
};

int main()
{
	Context* c = new Context();
	Expression* tp = new TernimalExpression("echo");
	Expression* ntp = new NonTerminalExpression(tp,4);
	ntp->Interpret(*c);
	
	delete ntp;
	delete tp;
	delete c;
	
	return 0;
}

