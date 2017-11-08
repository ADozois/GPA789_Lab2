#include "QExitFileName.h"
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QSpinBox>
#include <qgridlayout.h>
#include <qvboxlayout>
#include <qhboxLayout>

const QString mFilePrefixLabelInit{"Utiliser le m�me nom de fichier"};
const QString mNumberingLabelInit{"Utiliser un nom de fichier avec num�rotation automatique"};
const QString mFileNameGroupBoxName{"Nom du fichier de sortie"};
const QString mUseSameNameButtonInit{ "Utiliser le m�me nom de fichier" };
const QString mUseNewNameButtonInit{ "Utiliser un nom de fichier avec num�rotation automatique" };


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

	setLayout(mainGridLayout);


}