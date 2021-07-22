@echo off
REM Run.bat
REM cmd /c C:/Run.bat $(FULL_CURRENT_PATH)

setlocal enabledelayedexpansion
::echo 输出 %1 此文件被调用时输入参数  这里就是 $(FULL_CURRENT_PATH) 所指的文件路径
::echo  %1
::系统默认编码 设置 这是cmd语法 可以百度了解
::chcp 65001
::chcp 936
:: 设置字符串变量 具体意思可以参考 cmd语法 和前面的相关信息
set "FILE_PATH=%1"
set "FILE1_TYPE=.bat"
set "FILE2_TYPE=.c"
set "FILE3_TYPE=.py"
set "FILE_DIR=%~dp1"
set "FILE_NAME=%~n1"
set "FILE_EXT=%~x1"
set "FILE_FULLNAME=%~nx1"
set "FILE_PATH_NO_EXT=%~dpn1"

:: if语句 如果是 bat文件 然后执行的操作
if !FILE_EXT! equ !FILE1_TYPE! (
REM echo .bat
:: 直接运行
echo on
call !FILE_PATH!
echo off

)
:: if语句 如果是 c文件 然后执行的操作
if !FILE_EXT! equ !FILE2_TYPE! (
echo .c
: 到文件目录里面区 cd跳转目录 (bat语法 这里都是bat语法)
cd /d !FILE_DIR!
@echo on
:: 使用gcc编译文件
gcc !FILE_FULLNAME! -o !FILE_NAME!.exe
@echo off
:: 直接执行文件
!FILE_NAME!.exe

)
if !FILE_EXT! equ !FILE3_TYPE! (
echo .py
:: cmd语法 直接编译文件
python !FILE_PATH!)

pause
