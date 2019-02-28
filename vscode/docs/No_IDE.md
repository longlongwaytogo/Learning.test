
# IDE Leave away

1.  VS cmdline build
 link :[http://blog.csdn.net/cocoonyang/article/details/48135515](http://blog.csdn.net/cocoonyang/article/details/48135515)  
[https://msdn.microsoft.com/en-us/library/ms235639.aspx?__hstc=268264337.b1eb0ff78bc0ed98cf99c30d15c8cc53.1502846767912.1502846767912.1502846767912.1&__hssc=268264337.3.1502846767912&__hsfp=1555565217](https://msdn.microsoft.com/en-us/library/ms235639.aspx?__hstc=268264337.b1eb0ff78bc0ed98cf99c30d15c8cc53.1502846767912.1502846767912.1502846767912.1&__hssc=268264337.3.1502846767912&__hsfp=1555565217)

 在cmd命令行下使用VS Build Tools 编译运行C/C++源文件的方式：

The following tools can help you to build a C/C++ project on the command line[10] .

CL
Use the compiler (cl.exe) to compile and link source code files into apps, libraries, and DLLs.

Link
Use the linker (link.exe) to link compiled object files and libraries into apps and DLLs.

MSBuild (Visual C++)
Use MSBuild (msbuild.exe) to build Visual C++ projects and Visual Studio solutions. This is equivalent to running the Build project or Build Solution command in the Visual Studio IDE.

DEVENV
Use DEVENV (devenv.exe) combined with a command-line switch—for example, /Build or /Clean—to perform certain build commands without displaying the Visual Studio IDE.

NMAKE
Use NMAKE (nmake.exe) to automate tasks that build Visual C++ projects by using a traditional makefile.