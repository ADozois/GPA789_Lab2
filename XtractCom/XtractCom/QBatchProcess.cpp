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


const QString QBatchProcess::mInvalidFolderMessage{ "Impossible d'ouvrir le fichier de sortie.\nAttention, le chemin de dossier pourrait comporter des caractères spéciaux ou des espaces." };

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
		QBatchProcess::extractExitCode exitCode;
		int numberOfGoodFile{ 0 };
		QStringList files = mFileSelect->selectedFiles();
		int numberOfFile = files.size();		
		int index = mFileManager->getPrefixName();
		cleanList(files);
		for (auto const & file: files)
		{
			QString folder = retreiveFolder(file);
			exitCode = extract(file,folder, retreiveFileName(file, index), mFileManager->getExtension());
			if (exitCode == extractExitCode::failure)
			{
				break;
			}
			else if(exitCode == extractExitCode::succes){
				++numberOfGoodFile;
			}
			++index;
		}
		QString endMessage{ QString::number(numberOfGoodFile) + " fichier(s) a (ont) été traité(s) sur le(s) " + QString::number(numberOfFile) + " fichier(s) soumis." };
		showMessageBox(endMessage);
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

QBatchProcess::extractExitCode QBatchProcess::extract(QString fileName, QString folder, QString name, QString extension)
{
	QBatchProcess::extractExitCode exitCode{ extractExitCode::partialFailure };
	try
	{
		std::stringstream inputFile(fileName.toStdString());
		std::stringstream outputStream;
		std::ofstream outputFile(folder.toStdString() + name.toStdString() + extension.toStdString());
		if (outputFile.is_open())
		{
			mXtractC.setup(fileName.toStdString(), outputStream);
			mXtractC.process(mFileManager->wantStats());

			outputFile << outputStream.rdbuf();
			outputFile.close();
			exitCode=extractExitCode::succes;
		}
		else
		{
			throw 1;
		}
	}
	catch (XtractC::ParamException const & exception)
	{	
		showMessageBox(QString::fromStdString(exception.what()));
	}
	catch (XtractC::Exception const & exception) {
		showMessageBox(QString::fromStdString(exception.what()));
	}
	catch (exception const & exception) {
		showMessageBox(QString::fromStdString(exception.what()));
	}
	catch (int const & exception) {
		if (exception==1)
		{
			showMessageBox(mInvalidFolderMessage);
			exitCode = extractExitCode::failure;
		}
		
	}

	return exitCode;
	
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


void QBatchProcess::showMessageBox(QString const message)
{
	QMessageBox box;
	box.setInformativeText(message);
	box.setWindowIcon(QIcon(":/XtractCom/Icon"));
	box.exec();

}