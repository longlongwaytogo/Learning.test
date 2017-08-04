#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/qlabel.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QLabel *label = new QLabel("Hello, world!");
          label->show();
    return app.exec();
}
