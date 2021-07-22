#include "mainwindow.h"

#include <QApplication>

#include <commlib.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CommLib cb;
    bool bOK = cb.isOK();
    cb.Test();
    int dd = cb.add(10,20);
    w.show();
    return a.exec();
}
