QT += core gui

greaterThan(QT_MAJOR_VERSION,4) QT += widgets


TEMPLATE = app
HEADERS = mainwindow.h 
SOURCES +=\
main.cpp\
mainwindow.cpp
FORMS += \
    mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SubComm/CommLib/release/ -lCommLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SubComm/CommLib/debug/ -lCommLib
else:unix: LIBS += -L$$OUT_PWD/../SubComm/CommLib/ -lCommLib

INCLUDEPATH += $$PWD/../SubComm/CommLib
DEPENDPATH += $$PWD/../SubComm/CommLib
