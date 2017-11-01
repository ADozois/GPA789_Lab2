#include "QBatchProcess.h"
#include "QFileExplorer.h"
#include "QFileSelector.h"
#include <QGridLayout>


QBatchProcess::QBatchProcess(QFileExplorer const & fileExplorer, QWidget *parent)
	: QWidget(parent)
{
	mFileSelect = new QFileSelector(fileExplorer);
	QGridLayout * gridLayout = new QGridLayout;
	gridLayout->addWidget(mFileSelect);
	setLayout(gridLayout);
}

QBatchProcess::~QBatchProcess()
{
}
