#include "QFileExtensionManager.h"
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QGridLayout>

QFileExtensionManager::QFileExtensionManager(QString const & boxName, QString const & extension, QString const & firstButton, QString const & secondButton, QWidget *parent)
	: QWidget(parent)
{
	mGroupBox = new QGroupBox(boxName);
	mXtractExt = new QRadioButton(firstButton);
	mOtherExt = new QRadioButton(secondButton);
	mExtension = new QLineEdit(extension);	
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
	return mExtension->text();
}
