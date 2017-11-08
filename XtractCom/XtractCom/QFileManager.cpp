#include "QFileManager.h"
#include "QExitFolderSelector.h"
#include "QFileExtensionManager.h"
#include "QExitFileName.h"
#include <qvboxlayout>


QFileManager::QFileManager(QWidget * parent)
	: QWidget(parent)
{
	mExitFolderSelector = new QExitFolderSelector;
	mFileExtensionManager = new QFileExtensionManager;
	mExitFileNameManager = new QExitFileName;
	QVBoxLayout * vLayout = new QVBoxLayout;

	vLayout->addWidget(mExitFolderSelector);
	vLayout->addWidget(mExitFileNameManager);
	vLayout->addWidget(mFileExtensionManager);
	setLayout(vLayout);




}

QStringList QFileManager::optionsValid(void)
{
	QStringList errorsList;
	errorsList.append(mExitFileNameManager->boxIsValid());
	errorsList.append(mFileExtensionManager->boxIsValid());
	errorsList.append(mExitFolderSelector->boxIsValid());
	return errorsList;
}
