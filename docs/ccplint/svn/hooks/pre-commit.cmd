REM ʹ�ñ�ģ�飬ͨ������cpplint �����ļ��淶��⣬ͬʱҪ��д��ע��

REM Ŀ�꣺�����ע��Ҫ���ո�ʽ��
REM [ģ����]������־������ģ����������4���ַ�����2�����֣���
REM ������־������10���ַ�����5�����֣�

REM cpplint.py ��Ҫʹ��python 2.7.3 �汾

setlocal
set path =%path%;C:\MinGW\msys\1.0\bin;
set REPOS=%1
set TXN=%2
set SVNLOOK="svnlook.exe"

REM ע�ͼ��
svnlook log "%REPOS%" -t "%TXN%" | findstr ".........." >nul
if %errorlevel% gtr 0 goto err

REM �ļ����
svnlook.exe -t %TXN% changed %REPOS%>svn.log

REM get fileName and call cpplint 
for /f "usebackq tokens=1,2" %%A in (`"svnlook.exe" changed -t %TXN% %REPOS%`) do ( 
	REM echo %%A >svn.log
	REM echo %%B >svn.log
	svnlook.exe cat -t "%TXN%" "%REPOS%" %%B >svn.log
	svnlook.exe cat -t "%TXN%" "%REPOS%" %%B >tmp\%%B

REM ��ȡ�ļ���չ��
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
echo �ύ����־�������10���ַ�  >&2
echo ----------------------------------------------------------------------------------------------------------------------  >&2
exit 1
