/*
Widget principale comprenant tous les éléments de l'applications placé dans divers onglets.


Par: Antoine Dozois et Guillaume Chabot-Nobert
Pour le cours de: GPA789 - Analyse et conception orientées objet / Laboratoire 2
Le 16 novembre 2017

*/

#ifndef Q_XTRACTCOM_H
#define Q_XTRACTCOM_H

#include <QtWidgets/QMainWindow>
#include "ui_XtractCom.h"

class QFileExplorer;
class QCppCommentViewer;
class QSupplements;
class QBatchProcess;

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

#endif