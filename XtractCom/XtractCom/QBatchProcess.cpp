#include "QBatchProcess.h"
#include "QFileExplorer.h"
#include "QFileSelector.h"
#include "QFileManager.h"
#include "QPushButtonBox.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QFileInfo>


QBatchProcess::QBatchProcess(QFileExplorer const & fileExplorer, QWidget *parent)
	: QWidget(parent)
{
	mFileSelect = new QFileSelector(fileExplorer);
	mFileManager = new QFileManager;
	mGenerateButton = new QPushButtonBox();
	QGridLayout * gridLayout = new QGridLayout;
	gridLayout->addWidget(mFileSelect,0,0);
	gridLayout->addWidget(mFileManager, 0, 1);
	gridLayout->addWidget(mGenerateButton, 1, 1);
	
	setLayout(gridLayout);

	connect(mGenerateButton, &QPushButtonBox::clicked, this, &QBatchProcess::checkGenerateValid);
	connect(mFileSelect, &QFileSelector::listChanged, this, &QBatchProcess::listChanged);
}

bool QBatchProcess::checkGenerateValid(void)
{
	QStringList errors;
	errors = mFileManager->optionsValid();
	if (errors.isEmpty())
	{
		return true;
	}
	else {
		QMessageBox errorsBox;
		errorsBox.setText("Une erreur c'est produite");
		for (auto const error: errors)
		{
			errorsBox.setInformativeText("- " + error + "\n");
		}
		int result = errorsBox.exec();
		return false;
	}
}


void QBatchProcess::generate(bool checked) {
	if (checkGenerateValid())
	{
		cleanList(mFileSelect->selectedFiles());
	}
	
}

void QBatchProcess::listChanged(void) {
	if (mFileSelect->selectedFiles().isEmpty()) {
		mGenerateButton->disableButton(true);
	}
	else
	{
		mGenerateButton->enableButton(true);
	}
}

void QBatchProcess::cleanList(QStringList & filesList) {
	QFileInfo checkFile;
	int index = 0;
	for (auto const file : filesList)
	{
		checkFile.setFile(file);
		if (!checkFile.isFile()) {
			filesList.removeAt(index);
		}
		++index;
	}
}
