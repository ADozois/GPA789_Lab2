#include "XtractCom.h"
#include "QFileExplorer.h"
#include "QCppCommentViewer.h"
#include <qsplitter.h>

XtractCom::XtractCom(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//Set the icon on the main window
	setWindowIcon(QIcon(":/XtractCom/Icon"));

	//Creation de QfileExplorer

	mQFileExplorer = new QFileExplorer;
	mQCppCommentViewer = new QCppCommentViewer;
	static QStringList cppLanguageSuffix{ "c", "cpp", "cxx", "h", "hpp", "hxx", "" };

	mQFileExplorer->setFileSuffixFilter(cppLanguageSuffix);
	mQCppCommentViewer->setFileSuffixFilter(cppLanguageSuffix);

	//Create tabs
	mTabExplorer = new QTabWidget;
	mTabExplorer->addTab(mQFileExplorer, "Explorateur de fichier");
	mTabTask = new QTabWidget;
	mTabTask->addTab(mQCppCommentViewer, "Consultation");
	//
	//mTabTask->addTab(newwidget, "Génération par lot");
	//mTabTask->addTab(newwidget, "Suppléments");


	QSplitter * mainSplitter{ new QSplitter };
	mainSplitter->addWidget(mTabExplorer);
	mainSplitter->addWidget(mTabTask);
	mainSplitter->setCollapsible(0, false);
	mainSplitter->setCollapsible(1, false);

	setCentralWidget(mainSplitter);

	connect(mQFileExplorer, &QFileExplorer::fileSelected, mQCppCommentViewer, &QCppCommentViewer::setFile);
	//connect(mQCppCommentViewer, &QCppCommentViewer::eventSignaled, statusBar, &QStatusBar::showMessage);
}
