#include "QGenerationLot.h"
#include "QFileExplorer.h"
#include "QFileSelector.h"
#include <QGridLayout>


QGenerationLot::QGenerationLot(QFileExplorer const & fileExplorer, QWidget *parent)
	: QWidget(parent)
{
	mFileSelect = new QFileSelector(fileExplorer);
	QGridLayout * gridLayout = new QGridLayout;
	//Creation des bouttons
	gridLayout->addWidget(mFileSelect);
	setLayout(gridLayout);
}

QGenerationLot::~QGenerationLot()
{
}
