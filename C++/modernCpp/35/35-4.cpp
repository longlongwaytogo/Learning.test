//35-4

template<class ...Args, class T>
class bar{};

bar<int,double, unsigned int> b1; // error , args not last 


// 35-3 
template<class T,class ...Args>
class bar1{};

bar1<int,double, unsigned int> b2; // ok

 
 