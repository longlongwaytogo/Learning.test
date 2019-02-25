#include <iostream>
#define QFORMINTERNAL_NAMESPACE
using namespace std;
#include <QtWidgets/QDialog>
#include <QtWidgets/QApplication>
#include <QtUiTools/QUiLoader>
#include <qtCore/QFile>
#include <qtcore/QString>
#include <QtWidgets/QLayout>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QDialog w;
	QUiLoader loader;
//	QFile file("calculator.ui");
	//file.open(QFile::ReadOnly);
	//QWidget *formWidget = loader.load(&file, &w);
	//file.close();
	/*if(0)
	{
		QUiLoader loader;
		QFile file("calculator.ui");
		file.open(QFile::ReadOnly);
		QWidget *formWidget = loader.load(&file, &w);
		file.close();
		QMetaObject::connectSlotsByName(&w);
		QVBoxLayout *layout = new QVBoxLayout;
		layout->addWidget(formWidget);
		w.setLayout(layout);
		w.setWindowTitle(("Calculator Builder"));
	}*/
	w.show();

	return a.exec();
    cout << "Hello World!" << endl;
    return 0;
}
