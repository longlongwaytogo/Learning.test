#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QAction>
#include <QKeySequence>
#include <QMenu>


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
    void deleteItem();
    void addItem();
public slots:
    void open();
private slots:
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    QMenu          *popMenu;
};

#endif // MAINWINDOW_H
