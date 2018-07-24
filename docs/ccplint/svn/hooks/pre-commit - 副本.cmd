REM 目标：输入的注释要遵照格式：
REM [模块名]操作日志，其中模块名不少于4个字符（或2个汉字），
REM 操作日志不少于10个字符（或5个汉字）

REM findstr/C:"Total errors found: 0" cpp_check_return.log>nul
REM if %errorlevel% equ 0 (
  REM echo finded
  REM ) else (
  REM type "error.log" 1>&2
  REM echo not find
  REM pause
  REM exit 1
REM )

setlocal
 
set path =%path%;C:\MinGW\msys\1.0\bin;

 REM SET LOGMSG=`svnlook log -t "%TXN%" "%REPOS%"|wc -c`
 REM if $LOGMSG -lt 10 ( 
     REM echo $LOGMSG 1>&2
     REM echo -e "\nLog message is too short" 1>&2
     REM exit 1
	 REM )

 findstr/C:"Total errors found: 0" cpp_check_return.log>nul
	if %errorlevel% equ 0 (
	  echo finded
	   ) else (
	   REM type "error.log" 1>&2
	  REM exit 1
	)
	
set REPOS=%1
set TXN=%2
set SVNLOOK="svnlook.exe"
rem  此处不太严格， 因为把空格也算了
svnlook log "%REPOS%" -t "%TXN%" | findstr ".........." >nul
if %errorlevel% gtr 0 goto err

svnlook.exe -t %TXN% changed %REPOS%>svn.log
echo "file content:" >svn.log
svnlook cat -t  "TXN" "REPOS" >svn.log 


rem check that .resx files have svn:needs-lock property set 
 
rem %%A gets status, %%B gets file path for each line svnlook prints 
for /f "usebackq tokens=1,2" %%A in (`"svnlook.exe" changed -t %TXN% %REPOS%`) do ( 
	REM echo %%A >svn.log
	REM echo %%B >svn.log
	svnlook.exe cat -t "%TXN%" "%REPOS%" %%B >svn.log
	svnlook.exe cat -t "%TXN%" "%REPOS%" %%B >tmp\%%B
	REM err_log
	"C:\Python27\ArcGIS10.2\python.exe" "I:\co\Learning.test.git\docs\ccplint\cpplint.py"	tmp\%%B 2>error.log
	"C:\Python27\ArcGIS10.2\python.exe" "I:\co\Learning.test.git\docs\ccplint\cpplint.py"	tmp\%%B 1>cpp_check_return.log
	findstr/C:"Total errors found: 0" cpp_check_return.log>nul
	
	if %errorlevel% equ 0 (
	 echo " finded:"  
	  ) else (
	  echo " --------------errorLevel:" %errorlevel% 1>&2
	 REM  type "error.log" 1>&2
	  exit 1
	)

REM if findstr ".h"
  REM if not %%A==D ( 
    REM rem %%~xB extracts the extension from the path 
    REM if %%~xB == .resx ( 
      REM for /f "usebackq" %%C in (`"svnlook.exe" -t %TXN% propget %REPOS% svn:needs-lock %%B`) do ( 
        REM rem set PC_C=%%C 
        REM if not %%C == * ( 
          REM rem echo to stderr 
          REM echo %%B should have a svn:needs-lock=* property >&2 
          REM set error=1 
        REM ) 
      REM ) 
    REM ) 
  REM ) 
) 
if not %error% == 0 exit /b 1 

exit 0
REM cpplint 


SET FILES=svnlook changed -t "%TXN" "%REPOS" | awk '/^[AU]/ {print %NF}'


Set FILTERS="\.(cpp|c|h)$"

for FILE in %FILES%  do
   if echo $FILE | tr A-Z a-z | grep -Eq "$FILTERS"
   then
        CONTENT=$($SVNLOOK cat -t "$TXN" "$REPOS" "$FILE")
        MESSAGE=$"(echo "$CONTENT" | C:\Python27\ArcGIS10.2\python I:\co\Learning.test.git\docs\ccplintcpplint.py  --output=vs7 - 2>&1)"
        if [ $? -ne 0 ]; then
            echo  "file is $FILE" 1>&2
            echo  "$MESSAGE" 1>&2
            exit 1
        fi
    fi
done


exit 0

:err 
echo ----------------------------------------------------------------------------------------------------------------------  >&2
echo 提交的日志必须大于10个字符  >&2
echo ----------------------------------------------------------------------------------------------------------------------  >&2
exit 1
