#include "mainwindow.h"

#include <QApplication>
#include <KernelCommon/Common.h>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int i = 0;
    i = KernelCommon::add(100, 200);
    std::cout << i << std::endl;
    MainWindow w;
    w.show();
    return a.exec();
}
