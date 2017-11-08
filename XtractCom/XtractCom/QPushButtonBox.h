#pragma once

#include <QWidget>

class QPushButton;

class QPushButtonBox : public QWidget
{
	Q_OBJECT

public:
	QPushButtonBox(QWidget *parent=nullptr);
	~QPushButtonBox()=default;


signals:
	void clicked(bool checked);

public slots:
	void buttonClicked(bool checked);

	
private:
	QPushButton * mPushButton;

	static const QString mButtonName;
};
