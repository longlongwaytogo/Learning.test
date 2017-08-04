#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



GetTime::GetTime(QWidget *parent):QDialog(parent)
{
    this->resize(300,400);
    _label = new QLabel("label",this);
    _button = new QPushButton("getTime",this);
    _label->move(150,200);
    _button->move(125,300);

    /*Slot*/
    connect(_button,SIGNAL(clicked(bool)),this,SLOT(getCurrentTime()));

    // 自定义槽
    connect(this,SIGNAL(getData(QString)),_label,SLOT(setText(QString)));
}

GetTime::~GetTime()
{
    delete _label;
    delete _button;
}

void GetTime::getCurrentTime()
{
    emit  getData(QTime::currentTime().toString("hh.mm"));
}
