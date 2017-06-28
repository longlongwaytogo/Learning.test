# python利用swig调用C、C++编写的模块  
1. 下载swigwin,解压即可。
2. 编写c++代码如下：  
    源文件


		// main.cpp  
		#include<iostream>  
		#include"main.h"  
		using namespace std;  
		int compute(int a, int b)   
		{ 
		
			return a+b;
		
		}


	    
	  




    头文件

  		// main.h    
	    #ifndef _main_h_    
	    #define  _main_h_    
	    int compute(int a, int b);    
	    #endif




	定义文件

	    // main.i 
	    %module main 
	    %inline %{ 
	    #include "main.h" 
	    %}
	    int compute(int a,int b);
3. 将swigwin主目录添加到环境变量中去，打开cmd 切换到代码所在目录下，执行下面的命令：

    	swig -c++ -python main.i
这时候我们会看到在该目录下生成了两个文件main.py和main_wrap.cxx

4. 打开visual studio,新建Win32 Console Application工程，选择空项目，Application type选择DLL

5. 将我们的main.h 添加到头文件，将 main.cpp main_wrap.cxx 添加到源文件，将main.i添加到工程目录下
6. 包含python 的头文件和lib库  
****注意：****  
*必须保证本机安装的python操作系统支持的平台和VS生成的C++的dll的操作系统平台一致。*
7. 编译生成main.dll文件   改名为_main.pyd, 将main.py 和 _main.pyd 文件拷贝到另外一个文件夹test中测试，在test中新建test.py
代码如下：  

	    import main
	    
	    aa = main.compute(5,2)
	    
	    print(aa)

	命令行执行结果如下：  
	c:\C++>python test.py  
	7