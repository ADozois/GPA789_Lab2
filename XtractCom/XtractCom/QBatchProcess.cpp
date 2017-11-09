#include "QBatchProcess.h"
#include "QFileExplorer.h"
#include "QFileSelector.h"
#include "QFileManager.h"
#include "QPushButtonBox.h"
#include <QGridLayout>
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

	connect(mGenerateButton, &QPushButtonBox::clicked, this, &QBatchProcess::generate);
	connect(mFileSelect, &QFileSelector::listChanged, this, &QBatchProcess::listChanged);
}

bool QBatchProcess::checkGenerateValid(void)
{
	return mFileManager->optionsValid();
}


void QBatchProcess::generate(bool checked) {
	if (checkGenerateValid())
	{
		QStringList files = mFileSelect->selectedFiles();
		cleanList(files);
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
