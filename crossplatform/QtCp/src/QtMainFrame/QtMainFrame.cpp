#include "QtMainFrame.h"
#include<crossPlatformLib/crossPlatformLib.h>
#include<QMessageBox>

QtMainFrame::QtMainFrame(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    crossPlatformLib lib;

    int s = lib.add(1, 2);
    QMessageBox::information(NULL, "title", QString::number(s));
}
