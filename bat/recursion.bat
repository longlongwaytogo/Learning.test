REM %0表示循环运行bat 本身
@echo off

set /a var=%1+1

echo %var%

if %var% lss 100 (%0 %var%) else pause

