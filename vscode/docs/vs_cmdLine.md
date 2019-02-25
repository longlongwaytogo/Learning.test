#vs cmdline build
使用Visual Studio 的IDE,有时忍受不了它的占用内存太高，加载速度太慢。所以选择 cmdline 
## 1. devenv.exe\devenv.com

  1.1 Devenv 命令行  
  
  Devenv 允许您设置集成开发环境 (IDE) 的各个选项，以及从命令行生成、调试和部署项目。使用这些开关从脚本或 .bat 文件（如每夜生成的脚本）运行 IDE，或以特定配置启动 IDE,注意，命令行下请使用Devenv.com 否则无法输出日志信息。
  
  1.2 Devenv 开关语法  
  
	devenv 开关的语法规则与其他 DOS 命令行实用工具遵守的规则非常类似。   
	下列语法规则适用于所有 devenv 开关及其参数：
-  使用 devenv /? 命令可在“命令”窗口中显示所有可用的 devenv 开关的列表，同时显示其使用说明。
-  默认情况下，devenv 在命令行执行，不打开visual studio，该命令将开关传递给 devenv.com 实用工具。 
   devenv.com 实用工具用于通过标准系统流（如 stdout 和 stderr）传递输出，并在捕获输出时确定正确的 
    I/O 重定向（如重定向到 .txt 文件）。
-  以 devenv 开头的命令，在命令行执行，不打开visual studio。例如，devenv /fn verdana 命令将 Verdana 
指定为 IDE 的默认系统字体。 而以 devenv.exe 开头的命令可使用相同的开关，但会跳过 devenv.com 
实用工具将其直接发送给 devenv.exe 程序。

	1.3 编译项目： 
	 普通编译： devenv.com MyProject.sln /Build "Release|Win32"  
	 编译解决方案中的指定项目：devenv.com MyProject.sln /build "Release|Win32" /Project MyProject1 
## 2. msBuild.exe 
	MSBuild全称（Microsoft Build Engine）,是用于构建应用程序的平台。您可能不知道它，
	但是如果您在使用VS做开发，那么一定时时刻刻在使用它。因为是它在背后为你管理生成
	你的项目文件。当新建一个项目时，注意下项目文件夹中的*.*proj文件就是为MSBuild提供的，
	这是个文本文件，基于XML格式，里面包含有项目所包含的文件，生成配置，输出配置等信息。
	当把一个文件或者图片等添加到项目中，就会在这里添加一个描述，反之则删除一个描述信息；
	在项目属性页所做的配置也会在这里存储。
	
	示例：
		@echo on
		cd /d %~dp0
		"C:\Program Files (x86)\MSBuild\14.0\Bin\amd64\MSBuild.exe"  TestMSBuild.vcxproj /p:PlatformToolset=v140
