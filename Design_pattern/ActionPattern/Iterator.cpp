/*
、Iterator 迭代器设计模式
    迭代器设计模式的作用可以提供一种方法顺序访问一个聚合对象中各个元素，而又不暴露该对象的内部表示。
    迭代器模式有三个重要作用：
    1、支持以不同的方式遍历集合
        根据我们生成的迭代器的实现不同，可以采用不同的遍历方式。
    2、迭代器简化了集合接口。有了迭代器的遍历接口，集合不再需要类似的接口，也不再关注具体的遍历实现。
    3、在同一集合中可以有多个遍历。每个迭代器保持着自己的遍历状态，所以一个集合同时可以进行多个遍历。
二、示例程序：    
--------------------- 
作者：无德皇叔 
来源：CSDN 
原文：https://blog.csdn.net/qq_28334711/article/details/70768626 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/

//Iterator.cpp

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Iterator;
typedef int Object;

class Aggregate
{
public:
	Aggregate(){}
	virtual ~Aggregate(){}
	virtual Object GetItem(int idx) = 0;
	virtual int GetSize() = 0;
};

class ConcreteAggregate: public Aggregate
{
public:
	enum{SIZE= 3};
	ConcreteAggregate()
	{
		for(int i = 0; i < SIZE; ++i)
		{
			_objs[i] = i;
		}
	}
	Object GetItem(int idx)
	{
		if(idx < this->GetSize())
		{
			return _objs[idx];
		}
		else
		{
			return -1;
		}
	}
	
	int GetSize() { return SIZE;}
private:
	Object _objs[SIZE];
};

class Iterator
{
public:
	Iterator()
	{
	}
	
	virtual ~Iterator(){}
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual Object CurrentItem() = 0;
};

class ConcreteIterator :public Iterator
{
public:
	ConcreteIterator(Aggregate* agg,int idx)
	{
		_agg = agg; _idx = idx;
	}
	
	void First()
	{
		_idx = 0;
	}
	void Next()
	{
		if(_idx < _agg->GetSize())
			_idx++;
		// if(idx >= SIZE)
			// idx = 0;
	}
	
	bool IsDone()
	{
		 return (_idx == _agg->GetSize());
	}
	Object CurrentItem()
	{
		return _agg->GetItem(_idx);
	}
private:
	Aggregate* _agg;
	int _idx;
};

int main()
{
	Aggregate* agg = new ConcreteAggregate();
	Iterator* itr = new ConcreteIterator(agg,0);
	for(; !itr->IsDone(); itr->Next())
	{
		cout << itr->CurrentItem() <<endl;
	}
	
	delete itr;
	delete agg;
	
	return 0;
}