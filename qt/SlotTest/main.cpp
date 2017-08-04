#include "mainwindow.h"
#include <QApplication>





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
   // w.show();
    GetTime gt;
    gt.show();

    return a.exec();
}
