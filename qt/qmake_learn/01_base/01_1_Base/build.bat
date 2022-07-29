REM 需要在x64环境下的msvc编译器下运行，才可生成64编译配置项
qmake -o Makefile 01_1_Base.pro
nmake Debug REM  debug version
nmake Release REM Release version

REM nmake -f Makefile.Debug
REM nmake -f Makefile.Release

REM nmake all  REM  build all config 
REM https://zhangzhen.gitbook.io/qmake-learn/chuang-jian-xiang-mu-wen-jian
