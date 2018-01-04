# C++ STL
第一部分：（参考百度百科）

### 一、STL简介

STL（Standard Template Library，标准模板库)是惠普实验室开发的一系列软件的统称。它是由Alexander Stepanov、Meng Lee和David R Musser在惠普实验室工作时所开发出来的。现在虽说它主要出现在C++中，但在被引入C++之前该技术就已经存在了很长的一段时间。

> STL的代码从广义上讲分为三类：algorithm（算法）、container（容器）和iterator（迭代器），几乎所有的代码都采用了模板类和模版函数的方式，这相比于传统的由函数和类组成的库来说提供了更好的代码重用机会。
> 细分则主要由六大组件构成。这六大组件是：
容器（Container）、算法（algorithm）、迭代器（iterator）、仿函数（functor）、适配器（adapter）、配置器（allocator）。



1、容器（container）

容器可以分为三类即序列容器、关联容器和容器适配器。各类具体包含如下所示：

序列容器：vector、list、deque

关联容器：set、map、multiset、multimap

适配器容器：stack、queue、priority_queue


> 在C++标准中，STL被组织为下面的13个头文件:  
 
- algorithm	
- deque	
- functional	
- iterator	
- vector	
- list	
- map	
- memory	
- numeric	
- queue		
- set		
- stack		
- utility		  


### 二、算法

大家都能取得的一个共识是函数库对数据类型的选择对其可重用性起着至关重要的作用。举例来说，一个求方根的函数，在使用浮点数作为其参数类型的情况下的可重用性肯定比

使用整型作为它的参数类性要高。而C++通过模板的机制允许推迟对某些类型的选择，直到真正想使用模板或者说对模板进行特化的时候，STL就利用了这一点提供了相当多的有用

算法。它是在一个有效的框架中完成这些算法的——你可以将所有的类型划分为少数的几类，然后就可以在模版的参数中使用一种类型替换掉同一种类中的其他类型。

STL提供了大约100个实现算法的模版函数，比如算法for_each将为指定序列中的每一个元素调用指定的函数，stable_sort以你所指定的规则对序列进行稳定性排序等等。这样一来

，只要我们熟悉了STL之后，许多代码可以被大大的化简，只需要通过调用一两个算法模板，就可以完成所需要的功能并大大地提升效率。

 

算法部分主要由头文件<algorithm>，<numeric>和<functional>组成。

<algorithm>是所有STL头文件中最大的一个（尽管它很好理解），它是由一大堆模版函数组成的，可以认为每个函数在很大程度上都是独立的，其中常用到的功能范围涉及到比较、交换、查找、遍历操作、复制、修改、移除、反转、排序、合并等等。

 

<numeric>体积很小，只包括几个在序列上面进行简单数学运算的模板函数，包括加法和乘法在序列上的一些操作。

 

<functional>中则定义了一些模板类，用以声明函数对象。

 

### 三、容器

在实际的开发过程中，数据结构本身的重要性不会逊于操作于数据结构的算法的重要性，当程序中存在着对时间要求很高的部分时，数据结构的选择就显得更加重要。

经典的数据结构数量有限，但是我们常常重复着一些为了实现向量、链表等结构而编写的代码，这些代码都十分相似，只是为了适应不同数据的变化而在细节上有所出入。STL容器就为我们提供了这样的方便，它允许我们重复利用已有的实现构造自己的特定类型下的数据结构，通过设置一些模版类，STL容器对最常用的数据结构提供了支持，这些模板的参数允许我们指定容器中元素的数据类型，可以将我们许多重复而乏味的工作简化。

 

容器部分主要由头文件vector,list,deque,set,map,stack和queue组成。对于常用的一些容器和容器适配器（可以看作由其它容器实现的容器），可以通过下表总结一下它们和相应头文件的对应关系。

 
| name| description|
|-----|------------|
|向量(vector) | 连续存储的元素|
|列表(list)   | 由节点组成的双向链表，每个结点包含着一个元素|
|双队列(deque)| 连续存储的指向不同元素的指针所组成的数组|
|集合(set)    | 由节点组成的红黑树，每个节点都包含着一个元素，节点之间以某种作用于元素对的谓词排列，没有两个不同的元素能够拥有相同的次序|
|多重集合(multiset)| 允许存在两个次序相等的元素的集合|
|栈(stack)  | 后进先出的值的排列 |
|队列(queue)| 先进先出的执的排列 |
|优先队列(priority_queue)| 元素的次序是由作用于所存储的值对上的某种谓词决定的的一种队列|
|映射(map) | 由{键，值}对组成的集合，以某种作用于键对上的谓词排列 |
|多重映射(multimap) | 允许键对有相等的次序的映射|


### 四、迭代器


下面要说的迭代器从作用上来说是最基本的部分，可是理解起来比前两者都要费力一些。软件设计有一个基本原则，所有的问题都可以通过引进一个间接层来简化，这种简化在STL中就是用迭代器来完成的。

概括来说，迭代器在STL中用来将算法和容器联系起来，起着一种黏和剂的作用。几乎STL提供的所有算法都是通过迭代器存取元素序列进行工作的，每一个容器都定义了其本身所专有的迭代器，用以存取容器中的元素。


迭代器部分主要由头文件utility,iterator和memory组成。

**utility:**是一个很小的头文件，它包括了贯穿使用在STL中的几个模板的声明，

**iterator:**中提供了迭代器使用的许多方法，

而对于**memory**的描述则十分的困难，它以不同寻常的方式为容器中的元素分配存储空间，同时也为某些算法执行期间产生的临时对象提供机制,**memory**中的主要部分是模板类allocator，它负责产生所有容器中的默认分配器。

   > 对于之前不太了解STL的读者来说，上面的文字只是十分概括地描述了一下STL的框架，对您理解STL的机制乃至使用STL所起到的帮助微乎甚微，这不光是因为深入STL需要对C++的高级应用有比较全面的了解，更因为STL的三个部分算法、容器和迭代器三部分是互相牵制或者说是紧密结合的。从概念上讲最基础的部分是迭代器，可是直接学习迭代器会遇到许多抽象枯燥和繁琐的细节，然而不真正理解迭代器又是无法直接进入另两部分的学习的（至少对剖析源码来说是这样）。可以说，适应STL处理问题的方法是需要花费一定的时间的，但是以此为代价，STL取得了一种十分可贵的独立性，它通过迭代器能在尽可能少地知道某种数据结构的情况下完成对这一结构的运算，所以下决心钻研STL的朋友们千万不要被一时的困难击倒。其实STL运用的模式相对统一，只要适应了它，从一个STL工具到另一个工具，都不会有什么大的变化。

对于STL的使用，也普遍存在着两种观点。
- 第一种认为STL的最大作用在于充当经典的数据结构和算法教材，因为它的源代码涉及了许多具体实现方面的问题。
- 第二种则认为STL的初衷乃是为了简化设计，避免重复劳动，提高编程效率，因此应该是“应用至上”的，对于源代码则不必深究。

笔者则认为分析源代码和应用并不矛盾，通过分析源代码也能提高我们对其应用的理解，当然根据具体的目的也可以有不同的侧重。



### 第三部分：

50条忠告：（其中有几条觉得写的不够贴切，所以删了，发了余下的部分）

 

1.把C++当成一门新的语言学习；

2.看《Thinking In C++》，不要看《C++变成死相》；

3.看《The C++ Programming Language》和《Inside The C++ Object Model》,不要因为他们很难而我们自己是初学者所以就不看；

4.不要被VC、BCB、BC、MC、TC等词汇所迷惑——他们都是集成开发环境，而我们要学的是一门语言；

5.不要放过任何一个看上去很简单的小编程问题——他们往往并不那么简单，或者可以引伸出很多知识点；

6.会用Visual C++，并不说明你会C++；

7.学class并不难，template、STL、generic programming也不过如此——难的是长期坚持实践和不遗余力的博览群书；

8.如果不是天才的话，想学编程就不要想玩游戏——你以为你做到了，其实你的C++水平并没有和你通关的能力一起变高——其实可以时刻记住：学C++是为了编游戏的；

9.看Visual C++的书，是学不了C++语言的；  

16.把时髦的技术挂在嘴边，还不如把过时的技术记在心里；

18.学习编程最好的方法之一就是阅读源代码；

19.在任何时刻都不要认为自己手中的书已经足够了；

20.请阅读《The Standard C++ Bible》(中文版：标准C++宝典)，掌握C++标准；

21.看得懂的书，请仔细看；看不懂的书，请硬着头皮看；

22.别指望看第一遍书就能记住和掌握什么——请看第二遍、第三遍；

23.请看《Effective C++》和《More Effective C++》以及《Exceptional C++》；

24.不要停留在集成开发环境的摇篮上，要学会控制集成开发环境，还要学会用命令行方式处理程序；

25.和别人一起讨论有意义的C++知识点，而不是争吵XX行不行或者YY与ZZ哪个好；

26.请看《程序设计实践》，并严格的按照其要求去做；

27.不要因为C和C++中有一些语法和关键字看上去相同，就认为它们的意义和作用完全一样；

28.C++绝不是所谓的C的“扩充”——如果C++一开始就起名叫Z语言，你一定不会把C和Z语言联系得那么紧密；

29.请不要认为学过XX语言再改学C++会有什么问题——你只不过又在学一门全新的语言而已；

30.读完了《Inside The C++ Object Model》以后再来认定自己是不是已经学会了C++；

31.学习编程的秘诀是：编程，编程，再编程；

32.请留意下列书籍：《C++面向对象高效编程（C++ Effective Object-Oriented Software Construction）》《面向对象软件构造(Object-Oriented Software Construction)》《设计模式（Design Patterns）》《The Art of Computer Programming》； 

34.请把书上的程序例子亲手输入到电脑上实践，即使配套光盘中有源代码；

35.把在书中看到的有意义的例子扩充；

36.请重视C++中的异常处理技术，并将其切实的运用到自己的程序中；

37.经常回顾自己以前写过的程序，并尝试重写，把自己学到的新知识运用进去；

38.不要漏掉书中任何一个练习题——请全部做完并记录下解题思路；

39.C++语言和C++的集成开发环境要同时学习和掌握；

40.既然决定了学C++,就请坚持学下去，因为学习程序设计语言的目的是掌握程序设计技术，而程序设计技术是跨语言的；

41.就让C++语言的各种平台和开发环境去激烈的竞争吧，我们要以学习C++语言本身为主；

42.当你写C++程序写到一半却发现自己用的方法很拙劣时，请不要马上停手；请尽快将余下的部分粗略的完成以保证这个设计的完整性，然后分析自己的错误并重新设计和编写（参见43）；

43.别心急，设计C++的class确实不容易；自己程序中的class和自己的class设计水平是在不断的编程实践中完善和发展的；

44.决不要因为程序“很小”就不遵循某些你不熟练的规则——好习惯是培养出来的，而不是一次记住的；

45.每学到一个C++难点的时候，尝试着对别人讲解这个知识点并让他理解——你能讲清楚才说明你真的理解了；

46.记录下在和别人交流时发现的自己忽视或不理解的知识点；

47.请不断的对自己写的程序提出更高的要求,哪怕你的程序版本号会变成Version 100.XX；

48.保存好你写过的所有的程序——那是你最好的积累之一；

49.请不要做浮躁的人；

50.请热爱C++!

第四部分：

C++头文件一览 
C、传统 C++

#include <assert.h>　　　　设定插入点
#include <ctype.h>　　　　字符处理
#include <errno.h>　　　　 定义错误码
#include <float.h>　　　　浮点数处理
#include <fstream.h>　　　文件输入／输出
#include <iomanip.h>　　　 参数化输入／输出
#include <iostream.h>　　　数据流输入／输出
#include <limits.h>　　　　定义各种数据类型最值常量
#include <locale.h>　　　　定义本地化函数
#include <math.h>　　　　　定义数学函数
#include <stdio.h>　　　　定义输入／输出函数
#include <stdlib.h>　　　　定义杂项函数及内存分配函数
#include <string.h>　　　　字符串处理
#include <strstrea.h>　　　基于数组的输入／输出
#include <time.h>　　　　　定义关于时间的函数
#include <wchar.h>　　　　 宽字符处理及输入／输出
#include <wctype.h>　　　　宽字符分类

标准 C++　

#include <algorithm>　　　  通用算法
#include <bitset>　　　　　 位集容器
#include <cctype>
#include <cerrno>
#include <clocale>
#include <cmath>
#include <complex>　　　　 复数类
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>　　　　　 双端队列容器
#include <exception>　　　 异常处理类
#include <fstream>
#include <functional>　　　 定义运算函数（代替运算符）
#include <limits>
#include <list>　　　　　　 线性列表容器
#include <map>　　　　　　 映射容器
#include <iomanip>
#include <ios>　　　　　　基本输入／输出支持
#include <iosfwd>　　　　输入／输出系统使用的前置声明
#include <iostream>
#include <istream>　　　　 基本输入流
#include <ostream>　　　　 基本输出流
#include <queue>　　　　　  队列容器
#include <set>　　　　　　 集合容器
#include <sstream>　　　　 基于字符串的流
#include <stack>　　　　　 堆栈容器　　　　
#include <stdexcept>　　　 标准异常类
#include <streambuf>　　　底层输入／输出支持
#include <string>　　　　　字符串类
#include <utility>　　　　 通用模板类
#include <vector>　　　　 动态数组容器
#include <cwchar>
#include <cwctype>

C99 增加

#include <complex.h>　　复数处理
#include <fenv.h>　　　　浮点环境
#include <inttypes.h>　　整数格式转换
#include <stdbool.h>　　 布尔环境
#include <stdint.h>　　　整型环境
#include <tgmath.h>　　通用类型数学宏



[来源：https://www.cnblogs.com/shiyangxt/archive/2008/09/11/1289493.html](https://www.cnblogs.com/shiyangxt/archive/2008/09/11/1289493.html)



# part二：

##学习STL-介绍一下STL

从大学时就开始学习C++，到现在近5年的时间了却很少用到STL。现在想想真得是对不起这门语言，也对不起宝贵的五年光阴。我钟爱C++，所以一定要完全搞懂它，理解它。爱一个人的前提是要懂他（她），爱一门语言也是这样。郑重地向C++说声“对不起！”。我会把不懂你的方面慢慢弥补，做到真正懂你。为了更好地学习STL，我采用边学习，边总结，边写博客的方法，希望能够形成一个学习专栏。这样既可以便于自己随时翻阅，又可以分享给有需要的人。当然在博客中，我有可能会引用到其它大牛博友的文章。为了尊重原创，我会给出参考博文的链接地址。另外，如果大家在文章中发现错误，希望在评论下方给出提示建议。

Now，开始学习C++中重要的标准库STL。

STL简介
STL的原名是“Standard Template Library”，翻译过来就是标准模板库。STL是C++标准库的一个重要组成部分，主要由六大组件构成。这六大组件是：

容器（Container）、算法（algorithm）、迭代器（iterator）、仿函数（functor）、适配器（adapter）、配置器（allocator）。

### 1、容器（container）

容器可以分为三类即序列容器、关联容器和容器适配器。各类具体包含如下所示：

序列容器：vector、list、deque

关联容器：set、map、multiset、multimap

适配器容器：stack、queue、priority_queue

容器　	特性	所在头文件
向量vector	在常数时间访问和修改任意元素，在序列尾部进行插入和删除时，具有常数时间复杂度。对任意项的插入和删除的时间复杂度与到末尾的距离成正比，尤其对向量头的添加和删除代价比较高。	<vector>
双端队列deque	基本上与向量相同，不同点是，双端队列的两端插入和删除操作也是常量的时间复杂度。	<deque>
表list	对任意元素的访问与两端的距离成正比，但对某个位置上插入和删除时间复杂度为常数。	<list>
队列queue	插入只可以在尾部进行，删除、检索和修改只允许从头部进行。遵循FIFO的原则。	<queue>
栈stack	LIFO：先进后出原则。只允许在序列头部进行插入、删除、检索和修改操作，时间复杂度为常数。	<stack>
集合set	内部实现机制是红黑树，每个结点都包含一个元素，结点之间以某种作用于元素对的谓词排列，没有两个不同的元素能够拥有相同的次序，具有快速查找的功能。	<set>
多重集合multiset	和集合基本相同，但可以支持重复元素。	<set>
映射map	由(键，值)对组成的集合，以某种作用于键对上的谓词排序。具有快速查找特性。	<map>
多重映射multimap	支持一键对应多个值的特性，具有快速查找功能。	<map>
### 2、算法（Algorithm）

算法部分主要在头文件<algorithm>，<numeric>，<functional>中。<algoritm>是所有STL头文件中最大的一个，它是由一大堆模版函数组成的，可以认为每个函数在很大程度上都是独立的，其中常用到的功能范 围涉及到比较、交换、查找、遍历操作、复制、修改、移除、反转、排序、合并等等。<numeric>体积很小，只包括几个在序列上面进行简单数学运算的模板函数，包括加法和乘法在序列上的一些操作。<functional>中则定义了一些模板类，用以声明函数对象。

### 3、迭代器（Adapter）

迭代器是用类模板(class template)实现的.重载了* ,-> ,++ ,-- 等运算符。

迭代器分5种:输入迭代器、输出迭代器、 前面迭代器、双向迭代器、 随机访问迭代器。

输入迭代器：向前读（只允许读）；

输出迭代器：向前写（只允许写）；

前向迭代器：向前读写；

双向迭代器：向前后读写；

随机迭代器：随机读写；

### 4、仿函数（Functor）

仿函数用类模板实现，重载了符号"()"。仿函数，又或叫做函数对象，是STL六大组件之一；仿函数虽然小，但却极大的拓展了算法的功能，几乎所有的算法都有仿函数版本。

例如，查找算法find_if就是对find算法的扩展，标准的查找是两个元素相等就找到了，但是什么是相等在不同情况下却需要不同的定义，如地址相等，地址和邮编都相等，虽然这些相等的定义在变，但算法本身却不需要改变，这都多亏了仿函数。仿函数(functor)又称之为函数对象（function object），其实就是重载了()操作符的struct，没有什么特别的地方。

如以下代码定义了一个二元判断式functor：

复制代码
	struct IntLess
	{
	    bool operator()(int left, int right) const
	    {
	        return (left < right);
	    }
	};
复制代码
仿函数的优势：

1）仿函数比一般函数灵活。

2）仿函数有类型识别。可以用作模板参数。

3）执行速度上仿函数比函数和指针要更快。

在STL里仿函数最常用的就是作为函数的参数，或者模板的参数。

在STL里有自己预定义的仿函数，比如所有的运算符=，-，*，、比如'<'号的仿函数是less。

复制代码
        // TEMPLATE STRUCT less
	template<class _Ty = void>
	    struct less
	        : public binary_function<_Ty, _Ty, bool>
	    {    // functor for operator<
	    bool operator()(const _Ty& _Left, const _Ty& _Right) const
	        {    // apply operator< to operands
	        return (_Left < _Right);
	        }
	    };
复制代码
	less继承binary_function<_Ty,_Ty,bool>

复制代码
	template<class _Arg1, class _Arg2, class _Result>
	struct binary_function
	{ // base class for binary functions
	        typedef _Arg1 first_argument_type;
	        typedef _Arg2 second_argument_type;
	        typedef _Result result_type;
	};
复制代码
从定义中可以知道binary_function知识做了一些类型的声明，这样做就是为了方便安全，提高可复用性。

按照这个规则，我们也可以自定义仿函数：

复制代码
	template <typename type1,typename type2>
	class func_equal :public binary_function<type1,type2,bool>
	{
	        inline bool operator()(type1 t1,type2 t2) const//这里的const不能少
	        {
	                 return t1 == t2;//当然这里要overload==
	        }
	}
复制代码
之所以const关键字修饰函数，是因为const对象只能访问const修饰的函数。如果一个const对象想使用重载的()函数，编译过程就会报错。

小结一下：仿函数就是重载()的class，并且重载函数要有const修饰。自定义仿函数必须要继承binary_function（二元函数）或者unary_function（一元函数）。其中unary_function的定义如下：

	struct unary_function { 
	    typedef _A argument_type; 
	    typedef _R result_type; 
	};
### 5、适配器（Adapter）

适配器是用来修改其他组件接口的STL组件，是带有一个参数的类模板（这个参数是操作的值的数据类型）。STL定义了3种形式的适配器：容器适配器，迭代器适配器，函数适配器。

1）容器适配器：栈（stack）、队列(queue)、优先(priority_queue)。使用容器适配器，stack就可以被实现为基本容器类型（vector,dequeue,list）的适配。可以把stack看作是某种特殊的vctor,deque或者list容器，只是其操作仍然受到stack本身属性的限制。queue和priority_queue与之类似。容器适配器的接口更为简单，只是受限比一般容器要多。

2）迭代器适配器：修改为某些基本容器定义的迭代器的接口的一种STL组件。反向迭代器和插入迭代器都属于迭代器适配器，迭代器适配器扩展了迭代器的功能。

3）函数适配器：通过转换或者修改其他函数对象使其功能得到扩展。这一类适配器有否定器（相当于"非"操作）、绑定器、函数指针适配器。函数对象适配器的作用就是使函数转化为函数对象，或是将多参数的函数对象转化为少参数的函数对象。

例如：

在STL程序里，有的算法需要一个一元函数作参数，就可以用一个适配器把一个二元函数和一个数值，绑在一起作为一个一元函数传给算法。 

find_if(coll.begin(), coll.end(), bind2nd(greater <int>(), 42)); 
这句话就是找coll中第一个大于42的元素。 
greater <int>()，其实就是">"号，是一个2元函数 
bind2nd的两个参数，要求一个是2元函数，一个是数值，结果是一个1元函数。
bind2nd就是个函数适配器。

### 6、空间配置器（Allocator）

STL内存配置器为容器分配并管理内存。统一的内存管理使得STL库的可用性、可移植行、以及效率都有了很大的提升。

SGI-STL的空间配置器有2种，一种仅仅对c语言的malloc和free进行了简单的封装，而另一个设计到小块内存的管理等，运用了内存池技术等。在SGI-STL中默认的空间配置器是第二级的配置器。

SGI使用时std::alloc作为默认的配置器。

alloc把内存配置和对象构造的操作分开，分别由alloc::allocate()和::construct()负责，同样内存释放和对象析够操作也被分开分别由alloc::deallocate()和::destroy()负责。这样可以保证高效，因为对于内存分配释放和构造析够可以根据具体类型(type traits)进行优化。比如一些类型可以直接使用高效的memset来初始化或者忽略一些析构函数。对于内存分配alloc也提供了2级分配器来应对不同情况的内存分配。
第一级配置器直接使用malloc()和free()来分配和释放内存。第二级视情况采用不同的策略：当需求内存超过128bytes的时候，视为足够大，便调用第一级配置器；当需求内存小于等于128bytes的时候便采用比较复杂的memeory pool的方式管理内存。
无论allocal被定义为第一级配置器还是第二级，SGI还为它包装一个接口，使得配置的接口能够符合标准即把配置单位从bytes转到了元素的大小：
复制代码
	template<class T, class Alloc>
	class simple_alloc
	{
	public:
	     static T* allocate(size_t n)
	     {
	         return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
	     }
	 
	     static T* allocate(void)
	     {
	         return (T*) Alloc::allocate(sizeof(T));
	     }
	 
	     static void deallocate(T* p, size_t n)
	     {
	         if (0 != n) Alloc::deallocate(p, n * sizeof(T));
	     }
	 
	     static void deallocate(T* p)
	     {
	         Alloc::deallocate(p, sizeof(T));
	     }
	}   
复制代码
内存的基本处理工具，均具有commit或rollback能力。

复制代码
	template<class InputIterator, class ForwardIterator>
	ForwardIterator
	uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result);
	 
	template<class ForwardIterator, class T>
	void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x);
	 
	template<class ForwardIterator, class Size, class T>
	ForwardIterator
	uninitialized_fill_n(ForwardIterator first, ForwardIterator last, const T& x)
复制代码
泛型技术
泛型技术的实现方法有：模板、多态等。模板是编译时决定的，多态是运行时决定的，RTTI也是运行时确定的。

多态是依靠虚表在运行时查表实现的。比如一个类拥有虚方法，那么这个类的实例的内存起始地址就是虚表地址，可以把内存起始地址强制转换成int*，取得虚表，然后(int*)*(int*)取得虚表里的第一个函数的内存地址，然后强制转换成函数类型，即可调用来验证虚表机制。

泛型编程（Generic Programming，以下直接以GP称呼）是一种全新的程序设计思想，和OO，OB，PO这些为人所熟知的程序设计想法不同的是GP抽象度更高，基于GP设计的组件之间耦合度低，没有继承关系，所以其组件间的互交性和扩展性都非常高。我们都知道，任何算法都是作用在一种特定的数据结构上的，最简单的例子就是快速排序算法最根本的实现条件就是所排序的对象是存贮在数组里面，因为快速排序就是因为要用到数组的随机存储特性，即可以在单位时间内交换远距离的对象，而不只是相临的两个对象，而如果用链表去存储对象，由于在链表中取得对象的时间是线性的即O[n]，这样将使快速排序失去其快速的特点。也就是说，我们在设计一种算法的时候，我们总是先要考虑其应用的数据结构，比如数组查找，联表查找，树查找，图查找其核心都是查找，但因为作用的数据结构不同将有多种不同的表现形式。数据结构和算法之间这样密切的关系一直是我们以前的认识。泛型设计的根本思想就是想把算法和其作用的数据结构分离，也就是说，我们设计算法的时候并不去考虑我们设计的算法将作用于何种数据结构之上。泛型设计的理想状态是一个查找算法将可以作用于数组，联表，树，图等各种数据结构之上，变成一个通用的，泛型的算法。