

#include<iostream>

class Singleton
{

    public:
    static Singleton& Instance()
    {
        static Singleton  s_singleton;
        return s_singleton;
    }
    
    private:
    Singleton(){}
    Singleton(Singleton& another);
};

 int main()
{

    Singleton& s1 = Singleton::Instance();
    Singleton& s2 = Singleton::Instance();

	std::cout << "output tow Instance value is equal" << std::endl;
    std::cout << &s1 << std::endl;
    std::cout << &s2 << std::endl;
	
	return 0;
}