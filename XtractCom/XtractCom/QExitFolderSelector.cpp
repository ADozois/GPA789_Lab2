#include "QExitFolderSelector.h"
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>

const QString QExitFolderSelector::mGroupBoxName{ "Dossier de sortie" };
const QString QExitFolderSelector::mRadioButtonSourceFolderName{ "Utiliser le dossier source" };
const QString QExitFolderSelector::mRadioButtonNewFolderName{ "Spécifié un dossier de sortie" };
const QString QExitFolderSelector::mFolderPathLabelInit{ "Aucun dossier de sortie n'est sélectionné." };
const QString QExitFolderSelector::mSelectButtonName{ "Sélectionner" };
const QString QExitFolderSelector::mInvalidDirstoryText{ "Le dossier de sortie sélectionné n'existe plus ou ne permet pas l'écriture." };


QExitFolderSelector::QExitFolderSelector(QWidget * parent)
	:QWidget(parent)
{
	//Creation des éléments du widget
	mGroupBoxExitFolder = new QGroupBox(mGroupBoxName);
	mRadioButtonSourceFolder = new QRadioButton(mRadioButtonSourceFolderName);
	mRadioButtonNewFolder = new QRadioButton(mRadioButtonNewFolderName);
	mFolderPathLabel = new QLabel(mFolderPathLabelInit);
	mSelectButton = new QPushButton(mSelectButtonName);
	//Conditions initiales
	mRadioButtonSourceFolder->setChecked(true);
	mSelectButton->setEnabled(false);
	mFolderPathLabel->setVisible(false);
	//Connection des différents éléments du widget
	connect(mRadioButtonNewFolder, &QRadioButton::toggled, mSelectButton, &QPushButton::setEnabled);
	connect(mRadioButtonNewFolder, &QRadioButton::toggled, mFolderPathLabel, &QLabel::setVisible);
	connect(mSelectButton, &QPushButton::clicked, this, &QExitFolderSelector::getDirectoryPath);

	//Disposition des éléments dans le widget
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
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
		"/home",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);

	if (dir.isEmpty())
	{
		mFolderPathLabel->setText(mFolderPathLabelInit);
	}
	else
	{

		mFolderPathLabel->setText(dir);
	}


}


//Fonction qui valide que le fichier de sortie choisit est utilisable
QStringList QExitFolderSelector::boxIsValid(void)
{
	QStringList mErrors;

	//On regarde si on veux spécifié le dossier de sortie
	if (mRadioButtonNewFolder->isChecked())
	{
		QString text = mFolderPathLabel->text();
		
		if (!(QString::compare(mFolderPathLabel->text(), mFolderPathLabelInit)))
		{
			mErrors.append(mFolderPathLabelInit);
		}
		else
		{

			const QFileInfo outputDir(mFolderPathLabel->text());
			if ((!outputDir.exists()) || (!outputDir.isDir()) || (!outputDir.isWritable()))
			{
				mErrors.append(mInvalidDirstoryText);
			}
		}
	}

	return mErrors;
}

QString QExitFolderSelector::getFolder(void)
{
	QString emptyString;

	if (mRadioButtonNewFolder->isChecked())
	{
		return mFolderPathLabel->text();
	}
	else
	{
		return emptyString;
	}	
}

bool QExitFolderSelector::isDirectory(const QString & path)
{
	QDir dir(path);
	return dir.exists(path);
}

QString QExitFolderSelector::getPathOfFilename(const QString & fileName)
{
	return QFileInfo(fileName).absolutePath();
}
