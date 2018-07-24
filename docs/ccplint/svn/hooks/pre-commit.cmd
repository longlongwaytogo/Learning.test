REM 使用本模块，通过加载cpplint 进行文件规范检测，同时要求写入注释

REM 目标：输入的注释要遵照格式：
REM [模块名]操作日志，其中模块名不少于4个字符（或2个汉字），
REM 操作日志不少于10个字符（或5个汉字）

REM cpplint.py 需要使用python 2.7.3 版本

setlocal
set path =%path%;C:\MinGW\msys\1.0\bin;
set REPOS=%1
set TXN=%2
set SVNLOOK="svnlook.exe"

REM 注释检测
svnlook log "%REPOS%" -t "%TXN%" | findstr ".........." >nul
if %errorlevel% gtr 0 goto err

REM 文件检测
svnlook.exe -t %TXN% changed %REPOS%>svn.log

REM get fileName and call cpplint 
for /f "usebackq tokens=1,2" %%A in (`"svnlook.exe" changed -t %TXN% %REPOS%`) do ( 
	REM echo %%A >svn.log
	REM echo %%B >svn.log
	svnlook.exe cat -t "%TXN%" "%REPOS%" %%B >svn.log
	svnlook.exe cat -t "%TXN%" "%REPOS%" %%B >tmp\%%B

REM 获取文件扩展名
	REM set file=%%B
	REM set ext="cpp"
	REM for /f "tokens=2 delims=.,"  %%a in ( %file% ) do (
		REM set ext=%%a
	REM )
		"C:\Python27\ArcGIS10.2\python.exe" "I:\co\Learning.test.git\docs\ccplint\cpplint.py"	tmp\%%B 2>error.log
		"C:\Python27\ArcGIS10.2\python.exe" "I:\co\Learning.test.git\docs\ccplint\cpplint.py"	tmp\%%B 1>cpp_check_return.log
		findstr/C:"Total errors found: 0" cpp_check_return.log>nul
		if %errorlevel% equ 0 (
			echo "finded:"  
		) else ( 
			echo "--------------errorLevel:"1>&2 
			exit 1
		)
) 

if not %errorlevel% == 0 exit 1 

exit 0

:err 
echo ----------------------------------------------------------------------------------------------------------------------  >&2
echo 提交的日志必须大于10个字符  >&2
echo ----------------------------------------------------------------------------------------------------------------------  >&2
exit 1
