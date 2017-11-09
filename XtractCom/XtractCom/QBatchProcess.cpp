#include "QBatchProcess.h"
#include "QFileExplorer.h"
#include "QFileSelector.h"
#include "QFileManager.h"
#include "QPushButtonBox.h"
#include <QGridLayout>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>


#include <sstream>




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
		for (auto const & file: files)
		{
			extract(file);
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

void QBatchProcess::extract(QString fileName)
{
	QString folder, file, extension;
	QStringList fileOptions;
	folder = mFileManager->getFolder();
	fileOptions = mFileManager->getFile();
	extension = mFileManager->getExtension();
	if (folder == "No path selected")
	{
		folder = QFileDialog::getExistingDirectoryUrl().toString();
	}
	if (fileOptions.isEmpty())
	{
		file = fileName;
	}
	else
	{
		file = fileOptions.at(0) + fileOptions.at(1);
	}

	try
	{
		std::stringstream inputFile(fileName.toStdString());
		std::stringstream outputFile(folder.toStdString() + file.toStdString() + extension.toStdString());

		Xtract.setup(inputFile, outputFile);
		Xtract.process(false);
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
