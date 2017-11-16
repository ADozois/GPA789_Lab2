/*
Widget permettant de choisir d'utiliser le nom du fichier comme fichier de sortie ou un nom personalisé.
Celui-ci permet aussi de définir l'index de départ du nom de fichier personalisé.


Par: Antoine Dozois et Guillaume Chabot-Nobert
Pour le cours de: GPA789 - Analyse et conception orientées objet / Laboratoire 2
Le 16 novembre 2017

*/

#ifndef Q_EXIT_FILE_NAME_H
#define Q_EXIT_FILE_NAME_H
#include <QWidget>

class QLabel;
class QGroupBox;
class QRadioButton;
class QLineEdit;
class QSpinBox;


class QExitFileName : public QWidget
{
	Q_OBJECT

public:
	QExitFileName(QWidget *parent=nullptr);
	QStringList boxIsValid(void);
	QStringList getFileOptions(void);
	QString getFileName(void);
	int getPrefix(void);


protected:
	QLabel * mFilePrefixLabel;
	QLabel * mNumberingLabel;
	QGroupBox * mFileNameGroupBox;
	QRadioButton * mUseSameNameButton;
	QRadioButton * mUseNewNameButton;
	QLineEdit * mNewName;
	QSpinBox * mSpinBox;

private:

	static const QString mFilePrefixLabelInit;
	static const QString mNumberingLabelInit;
	static const QString mFileNameGroupBoxName;
	static const QString mUseSameNameButtonInit;
	static const QString mUseNewNameButtonInit;
	static const QString mExitFileNameEmpty;
	static const int mSpinBoxMaxValue{ 999 };
	static const int mSpinBoxMinValue{ 0 };
};





#endif
