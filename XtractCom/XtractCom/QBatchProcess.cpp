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
		QString folder = retreiveFolder(files.first());
		int index = mFileManager->getPrefixName();
		cleanList(files);
		for (auto const & file: files)
		{
			extract(file,folder, retreiveFileName(file, index), mFileManager->getExtension());
			++index;
		}
	}
	
}

void QBatchProcess::listChanged(void) {
	if (mFileSelect->selectedFilesCount() == 0) {
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

void QBatchProcess::extract(QString fileName, QString folder, QString name, QString extension)
{
	try
	{
		std::stringstream inputFile(fileName.toStdString());
		std::stringstream outputStream;
		std::ofstream outputFile(folder.toStdString() + name.toStdString() + extension.toStdString());
		
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

QString QBatchProcess::retreiveFolder(QString fileName)
{
	QString folder = mFileManager->getFolder();
	if (folder.isEmpty())
	{
		folder = QExitFolderSelector::getPathOfFilename(fileName) + "/";
	}
	else
	{
		folder = folder.append("/");
	}
	return folder;
}

QString QBatchProcess::retreiveFileName(QString fileName, int index)
{
	QString file;
	QFileInfo info(fileName);
	if (mFileManager->getFile().isEmpty())
	{
		file = QFileExtensionManager::removeExtension(info.fileName());
	}
	else
	{
		file = mFileManager->getFileName() + QString(std::to_string(index).c_str());
	}
	return file;
}
