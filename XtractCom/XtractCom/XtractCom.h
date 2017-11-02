#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_XtractCom.h"

class QFileExplorer;
class QCppCommentViewer;
class QSupplements;
class QBatchProcess;
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
	QBatchProcess * mBatchProcess;

	protected slots:
	void setFileExplorerMode(int index);



private:
	Ui::XtractComClass ui;


};