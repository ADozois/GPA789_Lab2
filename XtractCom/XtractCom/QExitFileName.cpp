#include "QExitFileName.h"
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QSpinBox>
#include <qgridlayout.h>
#include <qvboxlayout>
#include <qhboxLayout>

const QString QExitFileName::mFilePrefixLabelInit{"Utiliser le même nom de fichier"};
const QString QExitFileName::mNumberingLabelInit{ "Débuter la numérotation à " };
const QString QExitFileName::mFileNameGroupBoxName{"Nom du fichier de sortie"};
const QString QExitFileName::mUseSameNameButtonInit{ "Utiliser le même nom de fichier" };
const QString QExitFileName::mUseNewNameButtonInit{ "Utiliser un nom de fichier avec numérotation automatique" };
const QString QExitFileName::mExitFileNameEmpty{ "Aucun nom de fichier de sortie spécifié." };


QExitFileName::QExitFileName(QWidget * parent)
	:QWidget(parent)
{
	//Widget creation and initialisation

	mFilePrefixLabel= new QLabel(mFilePrefixLabelInit);
	mNumberingLabel=new QLabel(mNumberingLabelInit);
	mFileNameGroupBox = new QGroupBox(mFileNameGroupBoxName);
	mUseSameNameButton = new QRadioButton(mUseSameNameButtonInit);
	mUseNewNameButton = new QRadioButton(mUseNewNameButtonInit);
	mNewName = new QLineEdit;
	

	//Spin box initialisation
	mSpinBox = new QSpinBox;
	mSpinBox->setRange(mSpinBoxMinValue, mSpinBoxMaxValue);

	//Widget placement inside 
	QHBoxLayout * subPart1Layout = new QHBoxLayout;
	subPart1Layout->addWidget(mFilePrefixLabel);
	subPart1Layout->addWidget(mNewName);

	QHBoxLayout * subPart2Layout = new QHBoxLayout;
	subPart2Layout->addWidget(mNumberingLabel);
	subPart2Layout->addWidget(mSpinBox);


	QVBoxLayout * mainGridLayout = new QVBoxLayout;
	mainGridLayout->addWidget(mUseSameNameButton);
	mainGridLayout->addWidget(mUseNewNameButton);
	mainGridLayout->addLayout(subPart1Layout);
	mainGridLayout->addLayout(subPart2Layout);

	//Put layout inside the GroupBox
	mFileNameGroupBox->setLayout(mainGridLayout);

	QGridLayout * finalLayout = new QGridLayout;
	finalLayout->addWidget(mFileNameGroupBox);
	setLayout(finalLayout);

	//Initial state of widget
	mUseSameNameButton->setChecked(true);
	mFilePrefixLabel->setEnabled(false);
	mNumberingLabel->setEnabled(false);
	mNewName->setEnabled(false);
	mSpinBox->setEnabled(false);

	//Define which option is available or not depending on radio button selected
	connect(mUseNewNameButton, &QRadioButton::toggled, mFilePrefixLabel, &QLabel::setEnabled);
	connect(mUseNewNameButton, &QRadioButton::toggled, mNumberingLabel, &QLabel::setEnabled);
	connect(mUseNewNameButton, &QRadioButton::toggled, mNewName, &QLineEdit::setEnabled);   
	connect(mUseNewNameButton, &QRadioButton::toggled, mSpinBox, &QSpinBox::setEnabled);

}

//Methode qui permet de vérifier la présence d'un nom si l'option de choix d'un nom personnalisé est coché.
QStringList QExitFileName::boxIsValid(void)
{
	QStringList mErrors;

	//Check which radio button is checked
	if (mUseNewNameButton->isChecked())
	{
		if (mNewName->text().isEmpty())
		{
			mErrors.append(mExitFileNameEmpty);
		}
	}
	return mErrors;
}

QStringList QExitFileName::getFileOptions(void)
{
	QStringList options;
	if (mUseSameNameButton->isChecked())
	{
		return options;
	}
	else {
		options.append(mNewName->text());
		options.append(mSpinBox->text());
		return options;
	}
}

QString QExitFileName::getFileName(void)
{
	return mNewName->text();
}

int QExitFileName::getPrefix(void)
{
	return mSpinBox->value();
}
