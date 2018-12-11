#include "mainwindow.h"
#include <QApplication>

#include <osg/Node>
#include <osgDB/ReadFile>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    osg::Node* scene = osgDB::readNodeFile("cow.osg");


    w.show();

    return a.exec();
}
