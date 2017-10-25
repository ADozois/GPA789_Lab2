#include "QSupplements.h"
#include <qpushbutton.h>
#include <QGridLayout>
#include <Qapplication>

QSupplements::QSupplements(QWidget * parent)
	:QWidget(parent)
{
	mButtonXTractC = new QPushButton(QString("À propos de XtractC"));

	mButtonCpp = new QPushButton(QString("À propos du langage C++"));

	mButtonQt = new QPushButton(QString("À propos de Qt"));

	connect(mButtonQt, &QPushButton::clicked, this, &QApplication::aboutQt);

	QGridLayout * gridLayout = new QGridLayout;
	gridLayout->addWidget(mButtonXTractC, 0, 0);
	gridLayout->addWidget(mButtonCpp, 1, 0);
	gridLayout->addWidget(mButtonQt, 2, 0);

	gridLayout->setAlignment(Qt::AlignRight|Qt::AlignBottom);

	setLayout(gridLayout);

}