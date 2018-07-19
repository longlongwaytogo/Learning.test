#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

#include "swebengineview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    void resizeEvent(QResizeEvent *);

private slots:
    void onBackBtnClicked();

private:
    Ui::MainWindow *ui;
    SWebEngineView* view;

    QPushButton* m_backBtn;
    QLineEdit*   m_lineEdit;

};

#endif // MAINWINDOW_H
