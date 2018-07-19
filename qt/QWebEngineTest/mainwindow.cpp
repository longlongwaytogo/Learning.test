#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    view = new SWebEngineView(this);
    QUrl url("http://www.baidu.com/");
    view->addUrl(url);
    view->load(url);
    view->show();

    m_backBtn = new QPushButton(this);
    m_backBtn->resize(100,30);
    m_backBtn->setText(tr("Back"));
    connect(m_backBtn,&QPushButton::clicked,this,&MainWindow::onBackBtnClicked);

    //m_lineEdit = new QLineEdit(this);


    showMaximized();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete view;
}



void MainWindow::resizeEvent(QResizeEvent *)
{
    view->resize(this->size());
}


void MainWindow::onBackBtnClicked()
{
    QList<QUrl>& list = view->getUrlList();
    QUrl currentUrl = view->url();
    int currentValue = -1;
    if(list.contains(currentUrl))
    {
        currentValue = list.indexOf(currentUrl);
        if(currentValue > 1)
        {
            view->load(list.at(currentValue-1));

        }
        else
        {
            //m_backBtn->setEnabled(false);
        }
    }
    else
    {
        view->addUrl(currentUrl);
        view->load(list.last());
    }

}
