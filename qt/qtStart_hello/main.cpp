#include "mainwindow.h"
#include <QApplication>

#include <QLabel.h>
#include <QPushButton>

#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>

void OpenFile()
{
    QString file_name = QFileDialog::getOpenFileName(this,
            tr("Open File"),
            "",
            "",
            0);
        if (!file_name.isNull())
        {
            //fileName是文件名
            osg::ref_ptr<osg::Node> scenenode = osgDB::readNodeFile(file_name.toStdString());
            setSceneData(scenenode);
            getCamera()->dirtyBound();
        }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QLabel *label = new QLabel("Hello, world!");
    label->show();

    QLabel *label2 = new QLabel("<h2><font color='red'>Hello</font>, world!<h2>");
    label2->show();

    QPushButton *button = new QPushButton("Quit");
    QObject::connect(button, SIGNAL(clicked()), &a, SLOT(quit()));

    QPushButton *openButton = new QPushButton("Open");
    QObject::connect(openButton, SIGNAL(clicked()), NULL, SLOT(openFile()));

    button->show();

    {
        QWidget *window = new QWidget;
        window->setWindowTitle("Enter you age");

        QSpinBox *spinBox = new QSpinBox;
        QSlider *slider = new QSlider;

        spinBox->setRange(0,130);
        slider->setRange(0,130);


        QObject::connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
         spinBox->setValue(35);

        QHBoxLayout *layout = new QHBoxLayout;
        QVBoxLayout * vLayout = new QVBoxLayout;
        vLayout->addWidget(spinBox);
        vLayout->addWidget(slider);
        window->setLayout(vLayout);

        window->show();

    }
    return a.exec();
}
