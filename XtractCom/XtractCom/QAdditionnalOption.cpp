#include "QAdditionnalOption.h"
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qgridLayout>


const QString QAdditionnalOption::mGroupBoxName{ "Option de traitement" };
const QString QAdditionnalOption::mCheckBoxDescription{ "Inclure les statistiques" };

QAdditionnalOption::QAdditionnalOption(QWidget *parent)
	: QWidget(parent)
{
	mGroupBoxOption = new QGroupBox(mGroupBoxName);
	mCheckBoxAddStats = new QCheckBox(mCheckBoxDescription);

	//Widget placement 

	QGridLayout * gridLayout = new QGridLayout;
	gridLayout->addWidget(mCheckBoxAddStats);
	mGroupBoxOption->setLayout(gridLayout);

	QGridLayout * mainGridLayout = new QGridLayout;
	mainGridLayout->addWidget(mGroupBoxOption);
	setLayout(mainGridLayout);


}