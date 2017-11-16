/*
Widget comportant les bouttons du troisi�me onglet, permettant d'avoir plus d'information sur diff�rents �l�ments de l'application.


Par: Antoine Dozois et Guillaume Chabot-Nobert
Pour le cours de: GPA789 - Analyse et conception orient�es objet / Laboratoire 2
Le 16 novembre 2017

*/

#ifndef Q_SUPPLEMENTS_H
#define Q_SUPPLEMENTS_H

#include <QWidget>
class QPushButton;
class QMessageBox;

class QSupplements : public QWidget
{
	Q_OBJECT
public:

	QSupplements(QWidget * parent = nullptr);

protected:
	QPushButton * mButtonXTractC;
	QPushButton * mButtonCpp;
	QPushButton * mButtonQt;
	QMessageBox * mMessageCpp;
	
protected slots:
	void showAboutXtractC();




};




#endif
