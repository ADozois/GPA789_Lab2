#include "QGenerationLot.h"
#include "QFileExplorer.h"
#include "QFileSelector.h"
#include "QExitFolderSelector.h"
#include <QGridLayout>


QGenerationLot::QGenerationLot(QFileExplorer const & fileExplorer, QWidget *parent)
	: QWidget(parent)
{
	mFileSelect = new QFileSelector(fileExplorer);
	QGridLayout * gridLayout = new QGridLayout;
	//Creation des bouttons
	mGroupExitFolderSelector = new QExitFolderSelector;
	gridLayout->addWidget(mFileSelect,0,0);
	gridLayout->addWidget(mGroupExitFolderSelector,1,0);
	setLayout(gridLayout);
}

QGenerationLot::~QGenerationLot()
{
}
