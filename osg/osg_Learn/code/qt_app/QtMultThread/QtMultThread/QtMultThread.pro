#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T14:46:40
#
#-------------------------------------------------


QT       += core gui widget opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMultThread
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qgraphicwindow.cpp

HEADERS  += mainwindow.h \
    qgraphicwindow.h

FORMS    += mainwindow.ui





INCLUDEPATH += E:/project/osg/OpenSceneGraph-3.4.0/include
INCLUDEPATH += E:/project/osg/OpenSceneGraph-3.4.0/qt_ms/include
INCLUDEPATH += $$PWD/E:/project/osg/OpenSceneGraph-3.4.0/include
INCLUDEPATH += $$PWD/E:/project/osg/OpenSceneGraph-3.4.0/qt_ms/include
DEPENDPATH += $$PWD/E:/project/osg/OpenSceneGraph-3.4.0/qt_ms/include
DEPENDPATH += $$PWD/E:/project/osg/OpenSceneGraph-3.4.0/include


win64:CONFIG(release, debug|release):
else:win64:CONFIG(debug, debug|release):
    LIBS += -LE:/project/osg/OpenSceneGraph-3.4.0/qt_ms/lib -losgd -losgViewerd -losgDBd -losgUtild -losgWidgetd -losgSimd -losgTerraind -losgFXd -losgTextd \
                                        -losgShadowd -losgManipulatord -lOpenThreadsd -losgViewerd -losgGAd -losgQtd -losgVolumed
    #LIBS += -LD:/Qt/Qt5.6.1/5.6/msvc2015_64/lib/ -lQt5Cored -lQt5Guid -lQt5Widgetsd -lQt5OpenGLd



 #LIBS += -LE:/project/osg/OpenSceneGraph-3.4.0/qt_ms/lib/ -losgd -losgDBd -losgGAd -losgUtild -losgViewerd -losgQtd




