
// State Pattern 
/* 在实际开发中，我们经常会遇到这种情况；一个对象有多种状态，在每一个状态下，都会有不同的行为。那么在代码中我们经常是这样实现的。
typedef enum tagState
{
     state0,
     state1,
     state2
}State;

void Action(State actionState)
{
     if (actionState == state0)
     {
          // DoSomething
     }
     else if (actionState == state1)
     {
          // DoSomething
     }
     else if (actionState == state2)
     {
          // DoSomething
     }
     else
     {
          // DoSomething
     }
}
  但对于扩展很不利，如果有新的状态，我们就需要对Action函数进行修改。状态模式消除了分支语句，
  就像工厂模式消除了简单工厂模式的分支语句一样，将状态处理分散到各个状态子类中去，每个子类集中处理一种状态，
   这样就使得状态的处理和转换清晰明确。
 */
#include <iostream>
using namespace std;

class State;
class ConcreteStateB;
class ConcreteStateA;

class Context {
public:
    Context(State* st);
    void OperationInterface();
    void OperationChangeState();
private:
    friend class State;
    bool ChangeState(State* st);    //  
    State* _st;
};

class State {
public:
    virtual void OperationChangeState(Context*) = 0;
    virtual void OperationInterface(Context*) = 0;
    virtual ~State() { }
protected:
    bool ChangeState(Context* con, State *st) {
        con->ChangeState(st);
        return true;
    }
};

class ConcreteStateA :public State {
public:
    ConcreteStateA();
    void OperationChangeState(Context* con);

    void OperationInterface(Context* con);
};





class ConcreteStateB :public State {
public:
    void OperationChangeState(Context* con) {
        OperationInterface(con);
        this->ChangeState(con, new ConcreteStateA());
    }

    void OperationInterface(Context* con) {
        cout << "ConcreteStateB::OperationInterface..." << endl;
    }
};

void ConcreteStateA::OperationChangeState(Context* con) {
    OperationInterface(con);
    this->ChangeState(con, new ConcreteStateB());
}

ConcreteStateA::ConcreteStateA() :State()
{

}
void ConcreteStateA::OperationInterface(Context* con) {
    cout << "ConcreteStateA::OperationInterface..." << endl;
}
Context::Context(State* st) {
    _st = st;
}

void Context::OperationInterface() {
    _st->OperationInterface(this);
}

void Context::OperationChangeState() {
    _st->OperationChangeState(this);
}

bool Context::ChangeState(State* st) {
    if (_st)
    {
        delete _st;
    }
    _st = st;
    return true;
}

int main() {
    State *st = new ConcreteStateA();
    Context *con = new Context(st);
    con->OperationChangeState();
    con->OperationChangeState();
    con->OperationChangeState();
    con->OperationChangeState();
    con->OperationChangeState();

    delete con;
    delete st;

    return 0;
}
