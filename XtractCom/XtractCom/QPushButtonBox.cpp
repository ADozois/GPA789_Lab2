#include "QPushButtonBox.h"
#include <QPushButton>
#include <QHBoxLayout>

const QString QPushButtonBox::mButtonName{"Générer"};


QPushButtonBox::QPushButtonBox(QWidget *parent)
	: QWidget(parent)
{
	mPushButton = new QPushButton(mButtonName);
	QHBoxLayout * hLayout = new QHBoxLayout;
	hLayout->addStretch();
	hLayout->addWidget(mPushButton);
	setLayout(hLayout);

	connect(mPushButton, &QPushButton::clicked, this, &QPushButtonBox::buttonClicked);
}

void QPushButtonBox::buttonClicked(bool checked) {
	emit clicked(checked);
}

