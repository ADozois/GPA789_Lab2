#include "XtractCom.h"
#include "QFileExplorer.h"
#include "QCppCommentViewer.h"
#include "QSupplements.h"
#include "QBatchProcess.h"
#include <qsplitter.h>


XtractCom::XtractCom(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Set the icon on the main window
	setWindowIcon(QIcon(":/XtractCom/Icon"));

	static QStringList cppLanguageSuffix{ "c", "cpp", "cxx", "h", "hpp", "hxx", "" };
	//Creation de QfileExplorer
	mQFileExplorer = new QFileExplorer;
	mQFileExplorer->setFileSuffixFilter(cppLanguageSuffix);
	//Creation du cpp comment viewer
	mQCppCommentViewer = new QCppCommentViewer;
	mQCppCommentViewer->setFileSuffixFilter(cppLanguageSuffix);

	//Creation du supplements
	mSupplements = new QSupplements;

	//Creation du generation lot
	mBatchProcess = new QBatchProcess(mQFileExplorer, parent);



	//Create tabs
	mTabExplorer = new QTabWidget;
	mTabExplorer->addTab(mQFileExplorer, "Explorateur de fichier");
	mTabTask = new QTabWidget;
	mTabTask->addTab(mQCppCommentViewer, "Consultation");
	mTabTask->addTab(mBatchProcess, "Génération par lot");
	mTabTask->addTab(mSupplements, QString("Suppléments"));

	connect(mTabTask, &QTabWidget::tabBarClicked, this, &XtractCom::setFileExplorerMode);


	QSplitter * mainSplitter{ new QSplitter };
	mainSplitter->addWidget(mTabExplorer);
	mainSplitter->addWidget(mTabTask);
	mainSplitter->setCollapsible(0, false);
	mainSplitter->setCollapsible(1, false);

	setCentralWidget(mainSplitter);

	connect(mQFileExplorer, &QFileExplorer::fileSelected, mQCppCommentViewer, &QCppCommentViewer::setFile);
	connect(mQCppCommentViewer, &QCppCommentViewer::eventSignaled, ui.statusBar, &QStatusBar::showMessage);
}


void XtractCom::setFileExplorerMode(int index)
{
	switch (index)
	{
	case 0: mQFileExplorer->setSelectionMode(QFileExplorer::SelectionMode::Single);
		break;
	case 1: mQFileExplorer->setSelectionMode(QFileExplorer::SelectionMode::Extended);
		break;
	case 2: mQFileExplorer->setSelectionMode(QFileExplorer::SelectionMode::Single);
		break;
	default:  mQFileExplorer->setSelectionMode(QFileExplorer::SelectionMode::Single);
		break;
	}
}