// Composite
/*
组合模式（Composite Pattern）组合多个对象形成树形结构以表示具有“整体-部分”关系的层次结构。组合模式对单个对象（即：叶子构件）和组合对象（即：容器构件）的使用具有一致性，组合模式又被称为“整体-部分”（Part-Whole）模式，属于对象结构型模式。
*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Component {
public:
	virtual void Operation() {}
	
	virtual void Add(const Component* com) {}
	virtual void Remove(const Component* com) {}
	virtual Component* GetChild(int index) { return 0;}
	
	virtual ~Component(){}
};

class Composite :public Component
{
public:
	void Add(const Component* com)
	{
		//_coms.push_back(com);
		_coms.push_back(const_cast<Component*>(com));
	}
	//void Add(Component* com) {
	//	_coms.push_back(com);
	//}
	//
	void remove(const Component* com)
	{
		/*_coms.pop_back();*/
	}

	Component* GetChild(int index)
	{
		if((index >= 0) && (index < _coms.size()))
			return _coms.at(index);
		else
			return nullptr;
	}
	
	void Operation()
	{
		for(auto com :_coms)
			com->Operation();
	}
	
private:
	std::vector<Component*> _coms;
	
};

class Leaf :public Component
{
	public:
		void Operation() {
			cout << "Leaf::Operation..." << endl;
		}
};

int main()
{	
	Leaf* leaf = new Leaf();
	leaf->Operation();
	Composite* composite = new Composite();
	composite->Add(leaf);
	composite->Operation();
	Component* leaf_ = composite->GetChild(0);
	leaf_->Operation();
	
	delete leaf;
	delete composite;
	
	// 右值引用是对临时对象的引用
	int&& i = 1;
	std::cout << "i:" << i << std::endl;
	int b = 2;
	i = 2;
	std::cout << "i:" << i << std::endl;
	return 0;
}

