 
@echo off
::根据后缀名自动判断
echo -----------------------------
echo  0:%0
echo  1:%1 
echo  2:%2
echo  3:%3
echo  4:%4
echo  5:%5
echo -----------------------------

 

set suffix=%4
set fileName=%3%4

 
if %suffix%==.c cls & goto gcc
if %suffix%==.cpp goto g++
if %suffix%==".cpp" cls & goto g++
if %suffix%==.java cls & goto java 
if %suffix%==.rb cls & goto rb 
if %suffix%==.test goto test
if %suffix%==.bat cls & goto bat
if %suffix%==.txt if %fileName%==CMakeLists.txt goto CMake 



:err

REM cls
echo 对不起，你的输入有误，请按任意键重新输入！
pause > nul
exit
:gcc
@echo off
title GCC
::cmd /k chdir /d %2
::@echo ===============切换到当前目录==============
cmd /c gcc -g -W -Wall %1 -o %2\%3
@echo ===============编译成功后开始运行==============
::cmd /k chdir /d %2
::@echo ===============切换到当前目录==============
cmd /c %2\%3
@echo ====================运行完毕====================
pause > nul
exit

:g++
@echo on
title G++
::cmd /c chdir /d %2
::@echo ===============切换到当前目录==============
cmd /c g++ -g -W -Wall -I"C:\\local\\boost_1_59_0"   -std=c++11 %1 -o %2\%3
@echo ===============编译成功后开始运行==============
::cmd /k chdir /d %2
::@echo ===============切换到当前目录==============
cmd /c %2\%3
@echo ====================运行完毕====================
pause > nul
exit
:java
@echo off
title JAVA
::cmd /k chdir /d %2
::@echo ===============切换到当前目录==============
javac -encoding UTF-8 %1
@echo ===============编译成功后开始运行=============
::cmd /k chdir /d %2
::@echo ===============切换到当前目录==============
java -cp %2 %3
@echo ====================运行完毕====================
pause > nul
exit

:rb
@echo off
title rb
::cmd /k chdir /d %2
::@echo ===============切换到当前目录==============
ruby %1
@echo ====================运行完毕====================
pause > nul
exit

:test
@echo %1 %2 %3 %4 
pause > nul
exit

:bat
cmd /c %2\%3

:CMake 
echo off
setlocal enabledelayedexpansion
set config=%~2\config.txt
set vs=""
set platform=""
echo %config%
if exist %config% (
	echo "find %config%"
	for /f "tokens=1-5 delims= " %%a in (%config%) do (
	 set vs="%%a %%b %%c %%d"
	 set platform="%%e"
	)
	REM set /P vs=<%config%
	echo current vs ersion:!vs!
) else (
 	echo "not find %config%" 
	REM set vs version
	echo ------------------------------------
	echo vs版本:
	echo ------------------------------------ 
	echo 0: Visual Studio 10 2010
	echo 1: Visual Studio 11 2012
	echo 2: Visual Studio 12 2013
	echo 3: Visual Studio 14 2015
	echo 4: Visual Studio 15 2017
	set /p version="选择版本:"
	echo !version!
	REM error expersion: echo %version%
	pause
	 if !version!==0 ( 
		set vs="Visual Studio 10 2010"
	 )
	if !version!==1 ( 
		set vs="Visual Studio 11 2012"
	)
	if !version!==2 (
	set vs="Visual Studio 12 2013"
	)
	if !version!==3 (
		set vs="Visual Studio 14 2015"
	)
	if !version!==4 (
		set vs="Visual Studio 15 2017"
	)
	if !vs!=="" (
		echo vs is  null。
		set vs="Visual Studio 11 2012"
	) 
	echo vs version is:!vs!
	REM set vs platform
	echo "选择平台 0:Win32 1:Win64,dufault:Win32"
	set /p platform_sel="platfom:"
	if !platform_sel!==0 (
		set platform="Win32"
	) else (
		if !platform_sel!==1 (
			set platform="Win64"
		) else (
			set platform="Win32"
		)
	)
	echo platform:------------!platform!
	echo -------------------------------
	echo write config "!vs!" to file:%config% 
    echo !vs:~1,-1! !platform:~1,-1!>%config% 
	
	echo -------------------------------
)


 echo vs-------------------:%vs%
 echo vs-------------------:!vs!
 echo platform -------------%platform%
 echo platform -------------!platform!
 REM pause
 REM echo : aaa:!vs:~1,-1!
 REM echo : aaa:%vs:~1,-1%
 REM echo : bbb: !platform:~1,-1!
 REM echo : bbb: %platform:~1,-1%
 REM echo %vs%
 set  vs_new=%vs:~1,-1%
 REM echo vs_new:%vs_new%----- 
 REM set vs_new2=!vs:~1,-1!
 REM echo vs_new2:%vs_new2%----
 set platform_new=%platform:~1,-1%
 if %platform_new%=="Win64" (
	set vs_set="%vs_new%%platform_new%"
) else (
	set vs_set="%vs_new%" 
)
 echo vs-setting: !vs_set!
 REM echo vs-setting: %vs_set% 

 REM if NOT EXIST "%~2\Build"  md "%~2\Build"
"C:\Program Files\CMake\bin\cmake.exe" %1 -G!vs_set!  
pause

endlocal



