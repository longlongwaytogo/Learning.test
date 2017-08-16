cd /d %~dp0
call "D:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\vcvarsall.bat" amd64 

nmake
pause