CONFIG -= qt

TEMPLATE = vclib
DEFINES += COMMLIB_LIBRARY

CONFIG += c++11 build_all

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commlib.cpp

HEADERS += \
    CommLib_global.h \
    commlib.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

message($${CONFIG})
