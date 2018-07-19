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


      for(int i = 0; i < 5; ++i) {
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i,0,new QTableWidgetItem("one"));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem("two"));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem("three"));
      }
      ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
      ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
      ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
      ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

      popMenu = new QMenu(ui->tableWidget);
      QAction* pDeleteAction = new QAction("Delete",this);
      popMenu->addAction(pDeleteAction);
      connect(pDeleteAction,&QAction::triggered,this,&MainWindow::deleteItem);
      QAction* pAddAction = new QAction("Add",this);
      popMenu->addAction(pAddAction);
      connect(pAddAction,&QAction::triggered,this,&MainWindow::addItem);

      // table view setting
      ui->tableWidget2->setColumnCount(4);
      QStringList list;
      list << tr("one") << tr("two") << tr("three") << tr("four");

      // insert item
      for(int i = 0; i < 5; ++i) {
            ui->tableWidget2->insertRow(i);
            ui->tableWidget2->setItem(i,0,new QTableWidgetItem("one"));
            ui->tableWidget2->setItem(i,1,new QTableWidgetItem("two"));
            ui->tableWidget2->setItem(i,2,new QTableWidgetItem("three"));
            ui->tableWidget2->setItem(i,3,new QTableWidgetItem("four"));
      }
      // blod
      ui->tableWidget2->setHorizontalHeaderLabels(list);
      QFont font = ui->tableWidget2->font();
      font.setBold(true);
      ui->tableWidget2->horizontalHeader()->setFont(font);

      // other style
      ui->tableWidget2->horizontalHeader()->setStretchLastSection(true);//设置充满表宽度

      ui->tableWidget2->verticalHeader()->setDefaultSectionSize(50); //设置行高

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

 void MainWindow::deleteItem()
 {

     int index = ui->tableWidget->currentRow();
     ui->tableWidget->removeRow(index);
 }

 void MainWindow::addItem()
 {
     int count = ui->tableWidget->rowCount();

     ui->tableWidget->insertRow(count);
     ui->tableWidget->setItem(count,0,new QTableWidgetItem(QString("%1").arg(count)));
     ui->tableWidget->setItem(count,1,new QTableWidgetItem("two"));
     ui->tableWidget->setItem(count,2,new QTableWidgetItem("three"));

 }


 void MainWindow::open()
 {
     QMessageBox::information(this,QString::fromLocal8Bit("tip"),QString("打开文件"));
 }

void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    popMenu->exec(QCursor::pos());
}
