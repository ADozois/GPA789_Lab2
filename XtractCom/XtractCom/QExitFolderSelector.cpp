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
	mRadioButtonNewFolder = new QRadioButton("Spécifié un dossier de sortie");
	mFolderPathLabel = new QLabel("");
	mSelectButton = new QPushButton("Sélectionner");
	mRadioButtonSourceFolder->setChecked(true);
	mSelectButton->setEnabled(false);

	connect(mRadioButtonNewFolder, &QRadioButton::toggled, mSelectButton, &QPushButton::setEnabled);

	QGridLayout * gridLayout = new QGridLayout;
	gridLayout->addWidget(mRadioButtonSourceFolder, 0, 0);
	gridLayout->addWidget(mRadioButtonNewFolder, 1, 0);
	gridLayout->addWidget(mFolderPathLabel, 2, 0);
	gridLayout->addWidget(mSelectButton, 1, 1);

	mGroupBoxExitFolder->setLayout(gridLayout);
	setLayout(gridLayout);

}