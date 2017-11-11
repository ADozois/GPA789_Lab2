#include "XtractCom.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	XtractCom XtractApp;
	XtractApp.show();
	return a.exec();
}
