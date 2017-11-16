/*
Widget comportant tous les widget nécessaire à la gestion des options du fichier de sortie et de ces options.
Les informations sur le dossier de sortie, le nom du fichier, l'extension et les options sont requeillit par ce widget pour être par la suite transmis à QBatchProcess.


Par: Antoine Dozois et Guillaume Chabot-Nobert
Pour le cours de: GPA789 - Analyse et conception orientées objet / Laboratoire 2
Le 16 novembre 2017

*/

#ifndef Q_FILE_MANAGER_H
#define Q_FILE_MANAGER_H

#include <QWidget>

class QExitFolderSelector;
class QFileExtensionManager;
class QExitFileName;
class QAdditionnalOption;

class QFileManager : public QWidget
{
	Q_OBJECT

public:
	QFileManager(QWidget * parent = nullptr);
	bool optionsValid(void);
	void showErrors(QStringList const & errorsList);
	bool wantStats(void);
	QString getFolder(void);
	QStringList getFile(void);
	QString getExtension(void);
	QString getFileName(void);
	int getPrefixName(void);


private:

	QExitFolderSelector * mExitFolderSelector;
	QFileExtensionManager * mFileExtensionManager;
	QExitFileName * mExitFileNameManager;
	QAdditionnalOption * mAdditionnalOptionBox;

};

#endif 
