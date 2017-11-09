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
	vLayout->addStretch();
	setLayout(vLayout);

}

bool QFileManager::optionsValid(void)
{
	QStringList errorsList;
	errorsList.append(mExitFolderSelector->boxIsValid());
	errorsList.append(mExitFileNameManager->boxIsValid());
	errorsList.append(mFileExtensionManager->boxIsValid());
	

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
	QString finalMessage;
	errorsBox.setText("Une erreur c'est produite");
	for (auto const error : errorsList)
	{

		finalMessage.append("- " + error + "\n");
	}
	errorsBox.setInformativeText(finalMessage);
	int result = errorsBox.exec();
	
}
