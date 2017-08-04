#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <qlabel>
#include <qpushbutton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};


class GetTime : public QDialog
{
    Q_OBJECT
public:
    GetTime(QWidget *parent = 0);

    ~GetTime();
    /* 自定义槽 */
public slots:
    void getCurrentTime();

signals:
    /*声明信号 不需要实现 */
    void getData(QString);
private:
    QLabel* _label;
    QPushButton* _button;

};

#endif // MAINWINDOW_H
