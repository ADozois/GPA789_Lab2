#include "QFileManager.h"
#include "QExitFolderSelector.h"
#include "QFileExtensionManager.h"
#include "QExitFileName.h"
#include <QVBoxLayout>
#include <QMessageBox>


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

bool QFileManager::optionsValid(void)
{
	QStringList errorsList;
	errorsList.append(mExitFileNameManager->boxIsValid());
	errorsList.append(mFileExtensionManager->boxIsValid());
	errorsList.append(mExitFolderSelector->boxIsValid());

	if (errorsList.isEmpty())
	{
		return true;
	}
	else {
		showErrors(errorsList);
		return false;
	}
}

void QFileManager::showErrors(QStringList const & errorsList)
{
	QMessageBox errorsBox;
	errorsBox.setText("Une erreur c'est produite");
	for (auto const error : errorsList)
	{
		errorsBox.setInformativeText("- " + error + "\n");
	}
	int result = errorsBox.exec();
	
}
