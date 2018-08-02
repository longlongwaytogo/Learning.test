#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

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

void MainWindow::on_pushButton_clicked()
{

    //QMessageBox::information(this, QString::fromUtf8("提示"),QString::fromUtf8("这是一条信息提示"));
   // QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("这是一条信息提示"));
     QMessageBox::information(this, QStringLiteral("提示"),QStringLiteral("这是一条信息提示"));

}
