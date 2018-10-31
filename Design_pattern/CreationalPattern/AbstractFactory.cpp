// AbstractFactory  抽象工厂类

#include<iostream> 

// class ScrollBar
// {
	// ScrollBar()
	// {
		// std::cout << "construct ScrollBar" << std::endl;
	// }
// };


// class Window {
// public:
	// virtual ScrollBar* CreateScrolBar() =0;
	// virtual Window* CreateWindow() = 0;
// };


// class PMWindow: public Window {
// public:
 // ScrollBar* CreateScrolBar()
 // {
	 
 // }
 // Window* CreateWindow()  
 // {
	 
 // }
	
// }




// product 
class abstractproduct {
public:
	virtual ~abstractproduct(){}
	virtual void operation() = 0;
};

class producta: public abstractproduct {
public:
	void operation()
	{
		std::cout << "producta operation" << std::endl;
	}
};


class productb: public abstractproduct {
public:
	void operation()
	{
		std::cout << "productb operation" << std::endl;
	}
};

// factory

class abstractfactory {
public:
	virtual ~abstractfactory(){}
	virtual abstractproduct* createproducta() = 0;
	virtual abstractproduct* createproductb() = 0;
};

class concreatefactory :public abstractfactory {
public:
	concreatefactory(){}
	abstractproduct* createproducta()
	{
		return new producta();
	}
	abstractproduct* createproductb()
	{
		return new productb();
	}
};


int main()
{
	abstractfactory* factory = new concreatefactory();
	abstractproduct* producta = factory->createproducta();
	abstractproduct* productb = factory->createproductb();
	
	producta->operation();
	productb->operation();
	
	delete producta;
	delete productb;
	
	return 0;
}

