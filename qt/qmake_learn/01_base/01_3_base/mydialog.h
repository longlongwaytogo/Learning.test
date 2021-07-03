#ifndef MYDLOG_H
#define MYDLOG_H


#include "ui_mydialog.h"

class MyDialog : public QDialog, public Ui_MyDialog
{
	Q_OBJECT
	public:
	MyDialog(QWidget* parent = 0);
};

#endif 