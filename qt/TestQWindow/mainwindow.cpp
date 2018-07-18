#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initUI()
{
    QAction* pOpenAction = new QAction(QIcon(":/open-docs"), tr("&Open..."), this);
    addMenuItem(pOpenAction,tr("&Open"),tr("打开文件"),QKeySequence::Open);
      connect(pOpenAction,&QAction::triggered, this, &MainWindow::open);

   /*
    *  QAction* openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);
    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    */


}

 void MainWindow::addMenuItem(QAction* action,QString btnName,QString tip,QKeySequence::StandardKey key)
 {
     action->setShortcuts(key);
     action->setStatusTip(tip);

     QMenu *pMenuItem = menuBar()->addMenu(btnName);
     pMenuItem->addAction(action);

     QToolBar *toolBar = addToolBar(btnName);
     toolBar->addAction(action);


 }


 void MainWindow::open()
 {
     QMessageBox::information(this,QString::fromLocal8Bit("tip"),QString("打开文件"));
 }
