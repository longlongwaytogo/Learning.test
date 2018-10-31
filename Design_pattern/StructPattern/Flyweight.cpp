// flyWeight.cpp

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Flyweight {
public:
	Flyweight(string state):_state(state) {}
	
	virtual void Operation(const string& state)
	{
		_state = state;
	}
	
	string& GetState() 
	{
		return _state;
	}
	virtual ~Flyweight(){}
private:
	string _state;
};

class ConcreateFlyweight :public Flyweight {
public:
	ConcreateFlyweight(string state):Flyweight(state){
		cout << "ConcreateFlyweight Build.." << state << endl;
	}
	
	void Operation(const string& state)
	{
		cout << "ConcreateFlyweight state:" << GetState() << "\\" << state << std::endl;
	}
};

class FlyweightFactory {
public:
	Flyweight* GetFlyweight(std::string key) {
		for( auto fly: _flys) {
			if(fly->GetState() == key) {
				cout << "alread create by users..." << endl;
				return fly;
			}
		}
		Flyweight* fly = new ConcreateFlyweight(key);
		_flys.push_back(fly);
		return fly;
	}
private:
	std::vector<Flyweight*> _flys;
};

int main() {
	FlyweightFactory* fc = new FlyweightFactory();
	Flyweight* fly1 = fc->GetFlyweight("hello");
	Flyweight* fly2 = fc->GetFlyweight("world");
	Flyweight* fly3 = fc->GetFlyweight("hello");
	
	delete fly1;
	delete fly2;
	//delete fly3; // fly3 == fly1
	delete fc;
	
	return 0;
}