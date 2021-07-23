#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtMainFrame.h"

class QtMainFrame : public QMainWindow
{
    Q_OBJECT

public:
    QtMainFrame(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtMainFrameClass ui;
};
