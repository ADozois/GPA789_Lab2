#include "QFileExtensionManager.h"
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QGridLayout>
#include <stdexcept>

QFileExtensionManager::QFileExtensionManager(QString const & boxName, QString const & firstButton, QString const & secondButton, QWidget *parent)
	: QWidget(parent),
	mDefaultExt{"Xtract"}
{
	mGroupBox = new QGroupBox(boxName);
	mXtractExt = new QRadioButton(firstButton);
	mOtherExt = new QRadioButton(secondButton);
	mExtension = new QLineEdit();	
	QGridLayout * grid = new QGridLayout;
	QBoxLayout * layout = new QBoxLayout(QBoxLayout::Up);
	grid->addWidget(mXtractExt, 0, 0);
	grid->addWidget(mOtherExt, 1, 0);
	grid->addWidget(mExtension, 1, 1);
	mGroupBox->setLayout(grid);
	layout->addWidget(mGroupBox);
	setLayout(layout);

	widgetInitialization();
	
	connect(mXtractExt, &QRadioButton::clicked, mExtension, &QLineEdit::setDisabled);
	connect(mOtherExt, &QRadioButton::clicked, mExtension, &QLineEdit::setEnabled);

}

QFileExtensionManager::~QFileExtensionManager()
{
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
		if (mExtension->text().isEmpty())
		{
			throw std::invalid_argument("L'extension spécifié est invalide");
		}
		else
		{
			return "." + mExtension->text();
		}
	}
}
