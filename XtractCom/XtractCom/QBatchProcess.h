/*
Widget comportant tous les éléments (widgets) permettant de faire l'extraction des commentaires de plusieurs fichiers.
Ce widget comporte aussi plusieurs widget permettant de définir les paramètres du fichier de sortie de l'extraction des commentaires.

Par: Antoine Dozois et Guillaume Chabot-Nobert
Pour le cours de: GPA789 - Analyse et conception orientées objet / Laboratoire 2
Le 16 novembre 2017

*/

#ifndef Q_BATCHPROCESS_H
#define Q_BATCHPROCESS_H



#include "XtractC.h"
#include <QWidget>

class QFileSelector;
class QFileExplorer;
class QFileManager;
class QPushButtonBox;


class QBatchProcess : public QWidget
{
	Q_OBJECT

public:
	QBatchProcess(QFileExplorer const & fileExplorer,QWidget *parent);
	~QBatchProcess()=default;

public slots:
	void generate(bool checked);
	void listChanged(void);
	
private:
	//Enum class pour différentier lorsque l'extraction du document réussit, échou à cause d'une erreur sur le fichier (avec XtractC) *partialFailure* ou échou car le fichier de sortie ne peut être lu *failure*.
	//Le code *failure* est nécessaire car les vérification faites sur le dossier de sortie dans le QFilemanager ne permette pas de détecter si le nom comporte des caractères spéciaux.
	//Ceux-ci semble être détecter seulement lorsqu'on essaie de créé un fichier dans ce dossier et la création échou.
	enum class extractExitCode{succes,partialFailure,failure};
	QFileSelector * mFileSelect;
	QFileManager * mFileManager;
	QPushButtonBox * mGenerateButton;
	XtractC mXtractC;

	

	bool checkGenerateValid(void);
	void cleanList(QStringList & filesList);
	QBatchProcess::extractExitCode extract(QString fileName, QString folder, QString name, QString extension);
	QString retreiveFolder(QString fileName);
	QString retreiveFileName(QString fileName, int index);
	void showMessageBox(QString const message);

	static const QString mInvalidFolderMessage;
};

#endif // !Q_BATCHPROCESS_H



