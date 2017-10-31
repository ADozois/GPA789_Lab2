#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XtractCom.h"

class QFileExplorer;
class QCppCommentViewer;
class QSupplements;
class QGenerationLot;
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
	QSupplements * mSupplements;
	QGenerationLot * mGenerationLot;


private:
	Ui::XtractComClass ui;
};
