rem call param
@echo off
echo. & echo. & echo  --------------
call :loop Hello World!

pause>nul & goto :eof

:loop

echo %1

echo %2