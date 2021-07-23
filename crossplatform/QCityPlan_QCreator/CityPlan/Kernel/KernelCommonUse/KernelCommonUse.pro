CONFIG -= qt

TEMPLATE = lib
DEFINES += KERNELCOMMONUSE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    kernelcommonuse.cpp

HEADERS += \
    KernelCommonUse_global.h \
    kernelcommonuse.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


#CONFIG(debug, debug|release){
#    DESTDIR =$$(CP_ROOT)/bin/debug
#}else{
#    DESTDIR =$$(CP_ROOT)/bin/release
#}
