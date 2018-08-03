# 使用CMAKE和vcpkg配置项目

1.vckpkg简介：

Vcpkg helps you manage C and C++ libraries on Windows, Linux and MacOS. This tool and ecosystem are constantly evolving; your involvement is vital to its success!


Vcpkg可帮助您管理Windows，Linux和MacOS上的C和C ++库。这个工具和生态系统在不断发展; 您的参与对其成功至关重要！

一句话：C++ 第三方库的管理工具(包括下载、编译、引用），此乃c++程序员的福音。  
具体如何使用vcpkg:可以参考[vcpkg官网](https://github.com/Microsoft/vcpkg)及以下链接：  
[Visual Studio开源库集成器Vcpkg全教程--利用Vcpkg轻松集成开源第三方库](https://blog.csdn.net/cjmqas/article/details/79282847#111-编译工具)


2. 可以使用命令行方式生成vc项目：

	- 编写好CMakelists.txt
	- 执行cmake命令：

		cmake .."-DCMAKE_TOOLCHAIN_FILE=D:\vcpkg-master\vcpkg\scripts\buildsystems\vcpkg.cmake" -G"Visual Studio 14" 

3. 使用CMake-GUI工具：

   - 编写cmakeLists.txt时，需要设置CMAKE_TOOLCHAIN_FILE变量。

	SET(CMAKE_TOOLCHAIN_FILE "D:\\vcpkg-master\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")

  - 执行CMake-GUI工具生成工程。
  
  - 注意：SET CMAKE_TOOLCHAIN_FILE 变量，必须放在：PROJECT命令之前，否则无法找到依赖库
