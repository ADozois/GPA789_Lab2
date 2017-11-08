#include "QFileManager.h"
#include "QExitFolderSelector.h"
#include "QFileExtensionManager.h"
#include <qvboxlayout>


QFileManager::QFileManager(QWidget * parent)
	: QWidget(parent)
{
	mExitFolderSelector = new QExitFolderSelector;
	mFileExtensionManager = new QFileExtensionManager("Extension du fichier de sortie","","Utiliser l'extension : XtractC ","Spécifier l'extension: ") ;
	QVBoxLayout * vLayout = new QVBoxLayout;

	vLayout->addWidget(mExitFolderSelector);
	vLayout->addWidget(mFileExtensionManager);
	setLayout(vLayout);




}