/*
Widget permettant de choisir le dossier dans lequel les fichiers de sorties seront placé.
On peut choisir d'utiliser le fichier d'entré ou bien de choisir un autre fichier de sortie.


Par: Antoine Dozois et Guillaume Chabot-Nobert
Pour le cours de: GPA789 - Analyse et conception orientées objet / Laboratoire 2
Le 16 novembre 2017

*/

#ifndef Q_EXIT_FOLDER_SELECTOR_H
#define Q_EXIT_FOLDER_SELECTOR_H


#include <QWidget>
class QPushButton;
class QGroupBox;
class QRadioButton;
class QLabel;


class QExitFolderSelector : public QWidget
{
	Q_OBJECT


public:
	QExitFolderSelector(QWidget * parent = nullptr);
	QStringList boxIsValid(void);
	QString getFolder(void);
	
	static bool isDirectory(const QString & path);
	static QString getPathOfFilename(const QString & fileName);


protected:
	QGroupBox * mGroupBoxExitFolder;
	QPushButton * mSelectButton;
	QRadioButton * mRadioButtonSourceFolder;
	QRadioButton * mRadioButtonNewFolder;
	QLabel * mFolderPathLabel;


private:
	static const QString mGroupBoxName;
	static const QString mRadioButtonSourceFolderName;
	static const QString mRadioButtonNewFolderName;
	static const QString mFolderPathLabelInit;
	static const QString mSelectButtonName;
	static const QString mInvalidDirstoryText;

	protected slots:
	void getDirectoryPath();

};


#endif