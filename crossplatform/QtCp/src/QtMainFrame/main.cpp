#include "QtMainFrame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtMainFrame w;
    w.show();
    return a.exec();
}
