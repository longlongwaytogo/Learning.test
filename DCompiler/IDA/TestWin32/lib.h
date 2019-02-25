

#include <vector>
#include <string>

 __declspec(dllexport)  int Add(int a, int b);

class  __declspec(dllexport)  TestA
{
public:
    TestA();
    ~TestA();
    void add(int* i);
   bool  clearAll();
   void setName(const std::string& name);
   std::string getInfo(int a, int b, const std::string& info);
private:
    int a1;
    std::string _name;
   std::vector<int*> _list;


};
