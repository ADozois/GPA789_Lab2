#include "QBatchProcess.h"
#include "QFileExplorer.h"
#include "QFileSelector.h"
#include "QFileManager.h"
#include "QPushButtonBox.h"
#include "QExitFolderSelector.h"
#include "QFileExtensionManager.h"
#include <QGridLayout>
#include <QFileInfo>
#include <QMessageBox>

#include <sstream>
#include <iostream>




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
		int index = mFileManager->getFile().at(1).toInt();
		cleanList(files);
		for (auto const & file: files)
		{
			extract(file, index);
			++index;
		}
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

void QBatchProcess::extract(QString fileName, int index)
{
	QString folder, file, extension;
	QStringList fileOptions;
	QFileInfo info(fileName);
	folder = mFileManager->getFolder();
	fileOptions = mFileManager->getFile();
	extension = mFileManager->getExtension();
	if (folder.isEmpty())
	{
		folder = QExitFolderSelector::getPathOfFilename(fileName) + "/";
	}
	else
	{
		folder = folder + "/";
	}
	if (fileOptions.isEmpty())
	{
		file = info.fileName();
		file = QFileExtensionManager::removeExtension(file);
	}
	else
	{
		file = fileOptions.at(0) + QString(std::to_string(index).c_str());
	}

	try
	{
		std::stringstream inputFile(fileName.toStdString());
		std::stringstream outputStream;
		std::ofstream outputFile(folder.toStdString() + file.toStdString() + extension.toStdString());
		
		mXtractC.setup(fileName.toStdString(), outputStream);
		mXtractC.process(mFileManager->wantStats());

		outputFile << outputStream.rdbuf();
		outputFile.close();
	}
	catch (XtractC::ParamException const & exception)
	{	
		QMessageBox box;
		box.setInformativeText(QString::fromStdString(exception.what()));
		box.exec();
	}
	catch (XtractC::Exception const & exception) {
		QMessageBox box;
		box.setInformativeText(QString::fromStdString(exception.what()));
		box.exec();
	}
	catch (exception const & exception) {
		QMessageBox box;
		box.setInformativeText(QString::fromStdString(exception.what()));
		box.exec();
	}

	
}
