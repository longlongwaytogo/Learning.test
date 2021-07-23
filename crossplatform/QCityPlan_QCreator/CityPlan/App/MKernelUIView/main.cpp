#if defined (_MSC_VER) && (_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"


#include <QApplication>
#include <kernelcommonuse.h>
#include <QMessageBox>
#include <string>
#include <QtDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    long long  d= add(100,200);
   QString val = QString::number(d);
    QMessageBox::information(NULL,  "info","100+200=" + val);

 QString str = QObject::tr("中文");
 qDebug() <<str;
 // KernelCommonUse kcu;
  //d = kcu.add(100,200);

    MainWindow w;
    w.show();
    return a.exec();
}
