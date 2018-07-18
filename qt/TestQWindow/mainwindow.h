#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QAction>
#include <QKeySequence>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void  initUI();

    void addMenuItem(QAction* action,QString btnName,QString tip,QKeySequence::StandardKey key);


public slots:
    void open();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
