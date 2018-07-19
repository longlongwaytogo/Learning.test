#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_okBtn_clicked();
    void on_callJSBtn_clicked();

private:
    Ui::MainWindow *ui;
    WebObject* m_webObject;
};

#endif // MAINWINDOW_H
