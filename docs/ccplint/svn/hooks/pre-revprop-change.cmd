REM �޸�ע�� 
setlocal
set REPOS=%1
set REV=%2
set USER=%3
set PROPNAME=%4
set ACTION=%5
if not "%ACTION%"=="M" goto refuse
if not "%PROPNAME%"=="svn:log" goto refuse
goto OK
:refuse
echo Cann't set %PROPNAME%/%ACTION%, only svn:log is allowed 1>&2
endlocal
exit 1
:OK
endlocal
exit 0