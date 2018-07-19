#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebChannel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_webObject = new WebObject(this);

    ui->webView->load(QUrl("qrc:/index.html"));
    //重要设置
    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject("person",m_webObject);
    ui->webView->page()->setWebChannel(channel);

    connect(ui->btnOK,&QPushButton::clicked,this,&MainWindow::on_okBtn_clicked);
    connect(ui->btnCallJS,&QPushButton::clicked,this,&MainWindow::on_callJSBtn_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_okBtn_clicked()
{
    bool ok = false;

    QString name = ui->nameEdit->text().trimmed();
    int age = ui->ageEdit->text().trimmed().toInt(&ok,10);
    if(!ok)
    {
        age = 0;
    }

    m_webObject->setName(name);
    m_webObject->setAge(age);

}

void MainWindow::on_callJSBtn_clicked()
{
    QString strJs = ui->jsEdit->toPlainText();
    ui->webView->page()->runJavaScript(strJs);
}
