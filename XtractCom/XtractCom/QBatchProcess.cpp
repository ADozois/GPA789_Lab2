#include "QBatchProcess.h"
#include "QFileExplorer.h"
#include "QFileSelector.h"
#include "QFileManager.h"
#include <QGridLayout>


QBatchProcess::QBatchProcess(QFileExplorer const & fileExplorer, QWidget *parent)
	: QWidget(parent)
{
	mFileSelect = new QFileSelector(fileExplorer);
	mFileManager = new QFileManager;
	QGridLayout * gridLayout = new QGridLayout;
	gridLayout->addWidget(mFileSelect,0,0);
	gridLayout->addWidget(mFileManager, 0, 1);
	setLayout(gridLayout);
}

QBatchProcess::~QBatchProcess()
{
}

bool QBatchProcess::checkGenerateValid(void)
{
	return true;
}


void QBatchProcess::generate(bool checked) {

}
