cd /d %~dp0
call "D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat"  amd64
rem call %comspec% /k ""D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat"" amd64
cmake -G"NMake Makefiles"

pause