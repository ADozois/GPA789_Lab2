#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XtractCom.h"

class XtractCom : public QMainWindow
{
	Q_OBJECT

public:
	XtractCom(QWidget *parent = Q_NULLPTR);

private:
	Ui::XtractComClass ui;
};
