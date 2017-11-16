/*
Widget comportant un ensemble d'option supplémentaires a prendre en compte lors de l'extraction des commentaires.
Options présentes:
Affichage ou non des statistiques dans le fichier de sortie

Par: Antoine Dozois et Guillaume Chabot-Nobert
Pour le cours de: GPA789 - Analyse et conception orientées objet / Laboratoire 2
Le 16 novembre 2017

*/


#ifndef Q_ADDITIONNAL_OPTION_H
#define Q_ADDITIONNAL_OPTION_H

#include <QWidget>

class QGroupBox;
class QCheckBox;


class QAdditionnalOption : public QWidget
{
	Q_OBJECT

public:
	QAdditionnalOption(QWidget * parent = nullptr);
	bool isChecked(void);

protected:
	QGroupBox * mGroupBoxOption;
	QCheckBox * mCheckBoxAddStats;

private:
	static const QString mGroupBoxName;
	static const QString mCheckBoxDescription;

};


#endif
