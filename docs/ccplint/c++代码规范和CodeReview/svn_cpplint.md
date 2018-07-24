# CPPLInt 和SVN共同使用：


使用cpplint 可以方便的进行检测c++代码规范，但怎么和svn进行结合使用呢，下面做简单介绍：

1. 打开VisualSVN Server Manager，选择要进行配置的库属性，找到到hooks设置，打开pre-commit 

2. 编写脚本：

2.1 设置变量：    
	
	    setlocal
		set path =%path%;C:\MinGW\msys\1.0\bin;
		set REPOS=%1
		set TXN=%2
		set SVNLOOK="svnlook.exe"

2.2 检测提交日志是否为空： 

		REM 注释检测
		svnlook log "%REPOS%" -t "%TXN%" | findstr ".........." >nul
		if %errorlevel% gtr 0 goto err
		
2.3 遍历修改的文件，调用cpplint.py

		for /f "usebackq tokens=1,2" %%A in (`"svnlook.exe" changed -t %TXN% %REPOS%`) do ( 
			REM echo %%A >svn.log
			REM echo %%B >svn.log
			svnlook.exe cat -t "%TXN%" "%REPOS%" %%B >svn.log
			svnlook.exe cat -t "%TXN%" "%REPOS%" %%B >tmp\%%B
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

2.4 判断错误，并退出 

			if not %errorlevel% == 0 exit 1 
			
			exit 0
			
			:err 
			echo ----------------------------------------------------------------------------------------------------------------------  >&2
			echo 提交的日志必须大于10个字符  >&2
			echo ----------------------------------------------------------------------------------------------------------------------  >&2
			exit 1



## reference:

[https://segmentfault.com/a/1190000004707915]()    
[https://www.aliyun.com/jiaocheng/487713.html]()  
[https://www.cnblogs.com/frydsh/archive/2012/12/27/2835249.html]()