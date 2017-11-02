#include "QExitFolderSelector.h"
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include <QGridLayout>
#include <qfiledialog.h>

QExitFolderSelector::QExitFolderSelector(QWidget * parent)
	:QWidget(parent)
{

	mGroupBoxExitFolder = new QGroupBox("Dossier de sortie");
	mRadioButtonSourceFolder = new QRadioButton("Utiliser le dossier source");
	mRadioButtonNewFolder = new QRadioButton("Spécifié un dossier de sortie");
	mFolderPathLabel = new QLabel("No path selected");
	mSelectButton = new QPushButton("Sélectionner");
	mRadioButtonSourceFolder->setChecked(true);
	mSelectButton->setEnabled(false);

	connect(mRadioButtonNewFolder, &QRadioButton::toggled, mSelectButton, &QPushButton::setEnabled);
	connect(mSelectButton, &QPushButton::clicked, this, &QExitFolderSelector::getDirectoryPath);

	QGridLayout * gridLayout = new QGridLayout;
	gridLayout->addWidget(mRadioButtonSourceFolder, 0, 0);
	gridLayout->addWidget(mRadioButtonNewFolder, 1, 0);
	gridLayout->addWidget(mFolderPathLabel, 2, 0);
	gridLayout->addWidget(mSelectButton, 1, 1);

	mGroupBoxExitFolder->setLayout(gridLayout);

	QGridLayout * finalLayout = new QGridLayout;
	finalLayout->addWidget(mGroupBoxExitFolder);
	setLayout(finalLayout);

}

void QExitFolderSelector::getDirectoryPath()
{
	QUrl directory = QFileDialog::getExistingDirectoryUrl();

	if (directory.isEmpty())
	{
		mFolderPathLabel->setText("No path selected");
	}
	else
	{
		mFolderPathLabel->setText(directory.toString());
	}


}