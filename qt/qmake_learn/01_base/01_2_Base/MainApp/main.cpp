#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <commlib.h>
#include <iostream>
#include <string>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    CommLib cb;
    int o = 10;
   // o = cb.add(10,15);
    bool bOk = cb.isOK();

    float b = Add(10.0f, 200.0f);
    qDebug() << "o:" << o << "\n";
    qDebug() << "b:" << b << "\n";
    return a.exec();
}
