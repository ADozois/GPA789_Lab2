#include "QExitFolderSelector.h"
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include <QGridLayout>

QExitFolderSelector::QExitFolderSelector(QWidget * parent)
	:QWidget(parent)
{

	mGroupBoxExitFolder = new QGroupBox("Dossier de sortie");
	mRadioButtonSourceFolder = new QRadioButton("Utiliser le dossier source");
	mRadioButtonNewFolder = new QRadioButton("Spécifié un dossier de sourtie");
	mFolderPathLabel = new QLabel("");
	mSelectButton = new QPushButton("Sélectionner");
	mRadioButtonSourceFolder->setChecked(true);
	mSelectButton->setEnabled(false);

	//connect(mRadioButtonSourceFolder, &QRadioButton::isChecked, mSelectButton, &QPushButton::setDisabled);
	//connect(mRadioButtonNewFolder, &QRadioButton::isChecked, mSelectButton, &QPushButton::setEnabled);
	connect(mRadioButtonSourceFolder, &QRadioButton::toggled, mRadioButtonNewFolder, &QRadioButton::setChecked);
	connect(mRadioButtonNewFolder, &QRadioButton::toggled, mRadioButtonSourceFolder, &QRadioButton::setChecked);

	QGridLayout * gridLayout = new QGridLayout;
	gridLayout->addWidget(mRadioButtonSourceFolder, 0, 0);
	gridLayout->addWidget(mRadioButtonNewFolder, 1, 0);
	gridLayout->addWidget(mFolderPathLabel, 2, 0);
	gridLayout->addWidget(mSelectButton, 1, 1);

	mGroupBoxExitFolder->setLayout(gridLayout);
	setLayout(gridLayout);

}