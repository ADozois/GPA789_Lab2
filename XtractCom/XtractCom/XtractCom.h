#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XtractCom.h"

class QFileExplorer;
class QCppCommentViewer;
//class QTabWidget;

class XtractCom : public QMainWindow
{
	Q_OBJECT

public:
	XtractCom(QWidget *parent = Q_NULLPTR);

protected:
	QFileExplorer * mQFileExplorer;
	QCppCommentViewer * mQCppCommentViewer;
	QTabWidget * mTabExplorer;
	QTabWidget * mTabTask;


private:
	Ui::XtractComClass ui;
};
