- configure_file: c++ define 配置设置

		configure_file(<input> <output>
               [COPYONLY] [ESCAPE_QUOTES] [@ONLY]
               [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])

		Copy a file to another location and modify its contents
- out put file type: c++ 输出文件类型

		CMAKE_ARCHIVE_OUTPUT_DIRECTORY: 静态lib
		CMAKE_LIBRARY_OUTPUT_DIRECTORY: DLL对应的导出库lib
		CMAKE_RUNTIME_OUTPUT_DIRECTORY: DLL 、exe
		