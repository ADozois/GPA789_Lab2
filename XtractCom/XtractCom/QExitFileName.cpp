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


QExitFileName::QExitFileName(QWidget * parent)
	:QWidget(parent)
{
	//Widget creation and initialisation

	QLabel * mFilePrefixLabel= new QLabel(mFilePrefixLabelInit);
	QLabel *mNumberingLabel=new QLabel(mNumberingLabelInit);
	QGroupBox *	mFileNameGroupBox = new QGroupBox(mFileNameGroupBoxName);
	QRadioButton * mUseSameNameButton = new QRadioButton(mUseSameNameButtonInit);
	QRadioButton * mUseNewNameButton = new QRadioButton(mUseNewNameButtonInit);
	QLineEdit * mNewName = new QLineEdit;
	

	//Spin box initialisation
	QSpinBox *	mStartNumberingBox = new QSpinBox;
	mStartNumberingBox->setRange(mSpinBoxMinValue, mSpinBoxMaxValue);

	//Widget placement inside 
	QHBoxLayout * subPart1Layout = new QHBoxLayout;
	subPart1Layout->addWidget(mFilePrefixLabel);
	subPart1Layout->addWidget(mNewName);

	QHBoxLayout * subPart2Layout = new QHBoxLayout;
	subPart2Layout->addWidget(mNumberingLabel);
	subPart2Layout->addWidget(mStartNumberingBox);


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
	mStartNumberingBox->setEnabled(false);

	//Define which option is available or not depending on radio button selected
	connect(mUseNewNameButton, &QRadioButton::toggled, mFilePrefixLabel, &QLabel::setEnabled);
	connect(mUseNewNameButton, &QRadioButton::toggled, mNumberingLabel, &QLabel::setEnabled);
	connect(mUseNewNameButton, &QRadioButton::toggled, mNewName, &QLineEdit::setEnabled);   
	connect(mUseNewNameButton, &QRadioButton::toggled, mStartNumberingBox, &QSpinBox::setEnabled);

}