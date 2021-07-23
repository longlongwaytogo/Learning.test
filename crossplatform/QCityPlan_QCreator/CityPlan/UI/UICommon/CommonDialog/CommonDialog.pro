QT -= gui

TEMPLATE = lib
DEFINES += COMMONDIALOG_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commondialog.cpp

HEADERS += \
    CommonDialog_global.h \
    commondialog.h

TRANSLATIONS += \
    CommonDialog_zh_CN.ts

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


CONFIG(debug, debug|release){
    DESTDIR =$$(CP_ROOT)/build/bin/debug
}else{
    DESTDIR =$$(CP_ROOT)/build/bin/release
}
