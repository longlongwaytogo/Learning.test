REM ��Ҫ��x64�����µ�msvc�����������У��ſ�����64����������
qmake -o Makefile 01_1_Base.pro
nmake Debug REM  debug version
nmake Release REM Release version

REM nmake -f Makefile.Debug
REM nmake -f Makefile.Release

REM nmake all  REM  build all config 
REM https://zhangzhen.gitbook.io/qmake-learn/chuang-jian-xiang-mu-wen-jian
