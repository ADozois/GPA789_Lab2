#include "QFileExtensionManager.h"
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QGridLayout>
#include <stdexcept>

const QString QFileExtensionManager::mDefaultExt{"Xtract"};
const QString QFileExtensionManager::mBoxName{"Extension du fichier de sortie"};
const QString QFileExtensionManager::mFirstButtonName{"Utiliser l'extension: Xtract"};
const QString QFileExtensionManager::mSecondButtonName{ "Spécifier l'extension" };
const QString QFileExtensionManager::mExtEmpty{ "L'extension est vide" };


QFileExtensionManager::QFileExtensionManager(QWidget *parent)
	: QWidget(parent)
{
	//Creation des éléments du widget
	mGroupBox = new QGroupBox(mBoxName);
	mXtractExt = new QRadioButton(mFirstButtonName);
	mOtherExt = new QRadioButton(mSecondButtonName);
	mExtension = new QLineEdit();

	//Disposition des éléments dans le widget
	QGridLayout * grid = new QGridLayout;
	QBoxLayout * layout = new QBoxLayout(QBoxLayout::Up);
	grid->addWidget(mXtractExt, 0, 0);
	grid->addWidget(mOtherExt, 1, 0);
	grid->addWidget(mExtension, 1, 1);
	mGroupBox->setLayout(grid);
	layout->addWidget(mGroupBox);
	setLayout(layout);

	//Initialisation des éléments
	widgetInitialization();
	
	//Connection entre les éléments
	connect(mXtractExt, &QRadioButton::clicked, mExtension, &QLineEdit::setDisabled);
	connect(mOtherExt, &QRadioButton::clicked, mExtension, &QLineEdit::setEnabled);

}

void QFileExtensionManager::widgetInitialization(void)
{
	mXtractExt->click();
	mExtension->setDisabled(true);
}

QString QFileExtensionManager::getExtension(void) {
	if (mXtractExt->isChecked())
	{
		return "." + mDefaultExt;
	}
	else {
		return "." + mExtension->text();
	}		
}


//Fonction de validation de l'extension entrée (extension présente si nécessaire)
QStringList QFileExtensionManager::boxIsValid(void)
{
	QStringList mErrors;
	if (mOtherExt->isChecked())
	{
		if (mExtension->text().isEmpty()) {
			mErrors.append(mExtEmpty);
		}
	}
	return mErrors;
}

QString QFileExtensionManager::removeExtension(QString & fileName)
{
	QString file;
	return file = fileName.section(".", 0, 0) + "_" + fileName.section(".", 1, -1);
}
