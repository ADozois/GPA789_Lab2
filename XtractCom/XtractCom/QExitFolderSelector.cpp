#include "QExitFolderSelector.h"
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include <QGridLayout>
#include <qfiledialog.h>

const QString QExitFolderSelector::mGroupBoxName{ "Dossier de sortie" };
const QString QExitFolderSelector::mRadioButtonSourceFolderName{ "Utiliser le dossier source" };
const QString QExitFolderSelector::mRadioButtonNewFolderName{ "Spécifié un dossier de sortie" };
const QString QExitFolderSelector::mFolderPathLabelInit{ "No path selected" };
const QString QExitFolderSelector::mSelectButtonName{ "Sélectionner" };
const QString QExitFolderSelector::mNoFileSelectedText{ "No path selected" };

QExitFolderSelector::QExitFolderSelector(QWidget * parent)
	:QWidget(parent)
{

	mGroupBoxExitFolder = new QGroupBox(mGroupBoxName);
	mRadioButtonSourceFolder = new QRadioButton(mRadioButtonSourceFolderName);
	mRadioButtonNewFolder = new QRadioButton(mRadioButtonNewFolderName);
	mFolderPathLabel = new QLabel(mFolderPathLabelInit);
	mSelectButton = new QPushButton(mSelectButtonName);
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
		mFolderPathLabel->setText(mNoFileSelectedText);
	}
	else
	{
		mFolderPathLabel->setText(directory.toString());
	}


}

QStringList QExitFolderSelector::boxIsValid(void)
{
	return QStringList();
}
