#include "QFileManager.h"
#include "QExitFolderSelector.h"
#include "QFileExtensionManager.h"
#include "QExitFileName.h"
#include "QAdditionnalOption.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <qicon.h>


QFileManager::QFileManager(QWidget * parent)
	: QWidget(parent)
{
	//Creation des �l�ments
	mExitFolderSelector = new QExitFolderSelector;
	mFileExtensionManager = new QFileExtensionManager;
	mExitFileNameManager = new QExitFileName;
	mAdditionnalOptionBox = new QAdditionnalOption;

	//Disposition des �l�ments
	QVBoxLayout * vLayout = new QVBoxLayout;

	vLayout->addWidget(mExitFolderSelector);
	vLayout->addWidget(mExitFileNameManager);
	vLayout->addWidget(mFileExtensionManager);
	vLayout->addWidget(mAdditionnalOptionBox);
	vLayout->addStretch();
	setLayout(vLayout);

}


//Fonction qui v�rifie la validit� de toutes les informations des widget la composant
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
	errorsBox.setWindowIcon(QIcon(":/XtractCom/Icon"));
	for (auto const error : errorsList)
	{

		finalMessage.append("- " + error + "\n");
	}
	errorsBox.setInformativeText(finalMessage);
	int result = errorsBox.exec();
	
}

bool QFileManager::wantStats(void)
{
	return mAdditionnalOptionBox->isChecked();
}

QString QFileManager::getFolder(void)
{
	return mExitFolderSelector->getFolder();
}

QStringList QFileManager::getFile(void)
{
	return mExitFileNameManager->getFileOptions();
}

QString QFileManager::getExtension(void)
{
	return mFileExtensionManager->getExtension();
}

QString QFileManager::getFileName(void)
{
	return mExitFileNameManager->getFileName();
}

int QFileManager::getPrefixName(void)
{
	return mExitFileNameManager->getPrefix();
}
