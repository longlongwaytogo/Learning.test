# Qt中文字符乱码

## 一、 背景：
学习Qt有一段时间，但对QString和中文字符之间出现的乱码特别头疼，查了好多资料，在这做个整理。
## 二、 字符编码

- Qt Creator的编辑器默认使用UTF-8（代码页65001）编码来读取文本文件
- Visual Studio保存文件时默认采用的是本地编码，对于简体中文的Windows操作系统，这个编码就是GB2312（代码页936）
- MSVC在编译时，会根据源代码文件有无BOM来定义源码字符集。如果有BOM，则按BOM解释识别编码；如果没有，则使用本地字符集，对于简体中文的Windows操作系统就是GB2312。那么，当MSVC遇到一个没有BOM的UTF-8编码的文件时，它通常会把文件看作GB2312的来处理。如果文件全是英文没有问题，但如果包含中文，编译器就会出现误读。

## 三、 案例讲解

#### 1. 编译错误：
  
**1.1开发环境**：QtCreator + VS2015编译环境 
 
**1.2编码:**       

  - 创建一个QtWidget工程
  - 添加一个按钮触发
  - 编写如下代码：
		
			QMessageBox::information(this, "提示","这是一条信息提示");

**1.3提示错误：**
	     
			mainwindow.cpp:21: error: C2001: 常量中有换行符
			mainwindow.cpp:23: error: C2059: 语法错误:“}”

**1.4分析：**    

  - 创建Qt工程，默认使用UTF-8 无BOM标记的文本格式。  
  - 当前字符串中为被当作非法字符处理 
 
**1.5原因：**
 由于微软的vs2015编译器执行编译处理UTF-8中的非ascii码，使用带有BOM格式的文本文件才可以正确解析，所以编译出错。
**1.6解决办法：** 
 修改当前文档为UTF-8 + BOM标记。 

**1.6执行编译和运行:**   
  编译通过，没有错误，运行程序，出现乱码：   
![](res/QtString_1.png)

**1.7分析：** 

   Qt 当前编码为UTF-8格式，但QString内部为Unicode编码，所以需要进行转换，修改代码为：  

		QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("这是一条信息提示"));

	 或：     
		QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("这是一条信息提示"));

其他信息可参考以下链接：    
[qt5 中文乱码解决](https://blog.csdn.net/jacke121/article/details/78373448)   
[Qt5.5.1中文乱码解决办法](https://blog.csdn.net/jh1513/article/details/52331973)  
[MSVC中C++ UTF8中文编码处理探究](https://www.cnblogs.com/Esfog/p/MSVC_UTF8_CHARSET_HANDLE.html)
[vs2015:/utf-8选项解决UTF-8 without BOM 源码中文输出乱码问题](https://blog.csdn.net/10km/article/details/80203286)