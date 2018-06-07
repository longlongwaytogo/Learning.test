# osg Nofity 
###osg底层支持调试信息输出，主要功能包括：    

- 日志的分级输出     

- 日志的重定向输出  

- 日志的dbgView输出


##1. 分级输出： 

		osg::setNotifyLevel(osg::INFO);
 
##2. 重定向输出，默认输出到consle控制台：  
   定义全局对象： 

		static std::ofstream g_log("out.log");  

	设置日志重定向：  

		std::ostream& os = osg::notify(osg::INFO);
		os.rdbuf(g_log.rdbuf());

##3. dbgView输出：
	
		osg::WinDebugNotifyHandler* pWin32Handler = new osg::WinDebugNotifyHandler();
		osg::setNotifyHandler(pWin32Handler);