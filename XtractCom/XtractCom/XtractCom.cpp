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
	mGenerationLot = new QBatchProcess(mQFileExplorer, parent);

	//Create tabs
	mTabExplorer = new QTabWidget;
	mTabExplorer->addTab(mQFileExplorer, "Explorateur de fichier");
	mTabTask = new QTabWidget;
	mTabTask->addTab(mQCppCommentViewer, "Consultation");
	mTabTask->addTab(mGenerationLot, "Génération par lot");
	mTabTask->addTab(mSupplements, QString("Suppléments"));
	
	
	QSplitter * mainSplitter{ new QSplitter };
	mainSplitter->addWidget(mTabExplorer);
	mainSplitter->addWidget(mTabTask);
	mainSplitter->setCollapsible(0, false);
	mainSplitter->setCollapsible(1, false);

	setCentralWidget(mainSplitter);

	connect(mQFileExplorer, &QFileExplorer::fileSelected, mQCppCommentViewer, &QCppCommentViewer::setFile);
	connect(mQCppCommentViewer, &QCppCommentViewer::eventSignaled, ui.statusBar, &QStatusBar::showMessage);
}
