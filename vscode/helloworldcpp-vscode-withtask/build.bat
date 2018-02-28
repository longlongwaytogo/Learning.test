@echo off
call "E:\Program Files (x86)\vs2015\VC\vcvarsall.bat" x64     
set compilerflags=/Od /Zi /EHsc
set linkerflags=/OUT:hello.exe
cl.exe %compilerflags% helloworld.cpp /link %linkerflags%