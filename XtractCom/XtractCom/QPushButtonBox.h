/*
Widget comportant le boutton permettant de lancé le processus d'extraction des commentaires.
Cette classe est nécessaire afin d'avoir un meilleur controle du click du boutton et de son état "Enable" ou non.


Par: Antoine Dozois et Guillaume Chabot-Nobert
Pour le cours de: GPA789 - Analyse et conception orientées objet / Laboratoire 2
Le 16 novembre 2017

*/

#ifndef Q_PUSH_BUTTON_BOX_H
#define Q_PUSH_BUTTON_BOX_H

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
	void enableButton(bool state);
	void disableButton(bool state);


	
private:
	QPushButton * mPushButton;

	static const QString mButtonName;
};
#endif