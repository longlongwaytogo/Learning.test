@echo off
call "D:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" 
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:hello.exe
cl.exe %compilerflags% helloworld.cpp /link %linkerflags%