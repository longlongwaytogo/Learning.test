ѧϰ�ο���
https://github.com/carl-wang-cn/demo.git/cmake  <<CMake practise>>
https://github.com/wzpan/cmake-demo.git     <<Cmake ����ʵս>>

t1:
PROJECT/MESSAGE/ADD_EXECUTABLE ���� PROJECT_BINARY_DIR��PROJECT_SOURCE_DIR����ѧϰ
t2:
ADD_SUBDIRECTORY��AUX_SOURCE_DIRECTORY ���� EXECUTABLE_OUTPUT_PATH(���·������) ���� ѧϰ
t3:
ADD_LIBRARY ����ʹ�ã�
# ��ӵ����⣬�Զ������ HELLO_SHARED_EXPORTS �꣬���Դ����п����ж��������
ADD_LIBRARY(HELLO_SHARED SHARED ${SRC_LIST}) 
ADD_LIBRARY(HELLO_STATIC STATIC ${SRC_LIST})
# �������lib����
SET_TARGET_PROPERTIES(HELLO_STATIC PROPERTIES OUTPUT_NAME "HELLO_static")
SET_TARGET_PROPERTIES(HELLO_SHARED PROPERTIES OUTPUT_NAME "HELLO")
t4:
TARGET_LINK_LIBRARIES �����ⲿ�⣻ LINK_DIRECTORIES ����ⲿ��Ŀ¼��INCLUDE_DIRECTORIES �ⲿͷ�ļ�����·��
t5: 
CMAKE_MODULE_PATH������module·����FIND_PACKAGE ʹ�ã�FindCURL.cmake ��д��find_xx����ʹ��
t6: 
find���ܼ�ǿѵ��
t7: 
configure_file ����� foreach����\ CheckFunctionExists�÷�
link�� http://hahack.com/codes/cmake/
�����ص㣺
configure_file �÷�
#cmakedefine �귭��� �����һЩϸ����Ҫע�⣺
��һ�α���(����)�� #cmakedefine USE_OPTION --> #define USE_OPTION
�ڶ��α��루ż������  #cmakedefine USE_OPTION -->/* #undef USE_OPTION */

t8:��װ\����\��
link:https://gitlab.kitware.com/cmake/cmake/tree/master/Tests/Tutorial
link:http://hahack.com/codes/cmake/
CMAKEִ�а�װ�������ǣ�
cmakelists.txt ��д��װ�ű�
cmakelists.txt �������ã�������cmake_install.cmake �ű��ļ�
�����ڿ���̨��ִ�� cmake.exe -p cmake_install.cmake ִ�а�װ
���ʹ��gui��������vs�Ĺ��̣��ᵥ���и�install�Ĺ��̣����̵����ɺ��¼���ִ��cmake.exe -p cmake_install.cmake ����

���ʹ��nmake���ɹ��̺�ִ�а�װ�ű���Ҫ����nmake install�����ᰲװ��ָ��Ŀ¼��

SET(CMAKE_INSTALL_PREFIX "D:\\T8") �������ð�װ·������������Ҫ�� install����֮ǰ������Ч����

test���Ҳ�����ɶ�Ӧ��.cmake �ű�������vs��Ŀ��������test���̣������ɺ��¼������иýű��ű� 
��C:\Program Files\CMake\bin\ctest.exe  ctest.exe Ĭ�ϵ���CTestTestfile.cmake �ű���

t9���汾�� ��װ��
������װ������Ҫ��װNSIS������߽��д��
����ű���Ҳ��ͨ����������
���ɶ����ư�װ����	
cpack -C CPackConfig.cmake
����Դ�밲װ����
cpack -C CPackSourceConfig.cmake

t10 ����Դ�ļ���




find_package ���ϣ�http://blog.csdn.net/bytxl/article/details/50637277

command ��   http://blog.csdn.net/kl222/article/details/8258811