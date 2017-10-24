#include "XtractCom.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	XtractCom w;
	w.show();
	return a.exec();
}
