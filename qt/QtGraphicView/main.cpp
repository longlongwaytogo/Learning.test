#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();


    QGraphicsScene scene;
    scene.addLine(0,0,100,100);

    QGraphicsView view(&scene);
    view.setWindowTitle("test graphics view");
    view.resize(500,500);
    view.show();
    return a.exec();
}
