// Prototype 

#include <iostream>

class Prototype {
	public:
		virtual Prototype* Clone() = 0;
		virtual ~Prototype(){}
};

class ConcreatePrototype: public  Prototype {
public:
ConcreatePrototype() {}
	ConcreatePrototype(const ConcreatePrototype& ct)
	{
		std::cout << "ConcreatePrototype copy" << std::endl;
	}
	
	Prototype* Clone() {
		return new ConcreatePrototype();
	}
};

int main()
{
	Prototype* prototype = new ConcreatePrototype();
	std::cout << prototype << std::endl;
	Prototype* prototype1 = prototype->Clone();
	std::cout << prototype1 << std::endl;
	Prototype* prototype2 = prototype->Clone();
	std::cout << prototype2 << std::endl;
	
	delete prototype;
	delete prototype1;
	delete prototype2;
	return 0;
}