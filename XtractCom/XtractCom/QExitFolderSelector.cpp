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
const QString QExitFolderSelector::mFolderPathLabelInit{ "Aucun dossier de sortie n'est sélectionné." };
const QString QExitFolderSelector::mSelectButtonName{ "Sélectionner" };


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
	mFolderPathLabel->setVisible(false);
	connect(mRadioButtonNewFolder, &QRadioButton::toggled, mSelectButton, &QPushButton::setEnabled);
	connect(mRadioButtonNewFolder, &QRadioButton::toggled, mFolderPathLabel, &QLabel::setVisible);
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
		mFolderPathLabel->setText(mFolderPathLabelInit);
	}
	else
	{
		mFolderPathLabel->setText(directory.toString());
	}


}

QStringList QExitFolderSelector::boxIsValid(void)
{
	QStringList mErrors;

	//On regarde si on veux spécifié le pdossier de sortie
	if (mRadioButtonNewFolder->isChecked())
	{
		QString text = mFolderPathLabel->text();
		QFileInfo checkDirectory;
		if (!(QString::compare(mFolderPathLabel->text(), mFolderPathLabelInit)))
		{
			mErrors.append(mFolderPathLabelInit);
		}
		else
		{
			//On valide que le folder existe toujours
			checkDirectory.setFile(mFolderPathLabel);
			if (!checkFile.isDir()) {
				mErrors.append(mFolderPathLabelInit);
			}
		}
	}

	return mErrors;
}

QString QExitFolderSelector::getFolder(void)
{
	

	if (mRadioButtonNewFolder->isChecked())
	{
		return mFolderPathLabel->text();
	}
	else
	{
		return QFileDialog::getExistingDirectoryUrl();
	}	
}
