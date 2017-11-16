/*
Widget permettant de choisir l'extension du fichier de sortie.


Par: Antoine Dozois et Guillaume Chabot-Nobert
Pour le cours de: GPA789 - Analyse et conception orientées objet / Laboratoire 2
Le 16 novembre 2017

*/

#ifndef Q_FiILE_EXTENSION_MANAGER
#define Q_FiILE_EXTENSION_MANAGER

#include <QWidget>

class QGroupBox;
class QRadioButton;
class QLineEdit;

class QFileExtensionManager : public QWidget
{
	Q_OBJECT

public:
	QFileExtensionManager(QWidget *parent = nullptr);
	~QFileExtensionManager()=default;
	QString getExtension(void);
	QStringList boxIsValid(void);

	static QString removeExtension(QString & fileName);

private:
	QGroupBox * mGroupBox;
	QRadioButton * mXtractExt;
	QRadioButton * mOtherExt;
	QLineEdit * mExtension;

	static const QString mDefaultExt;
	static const QString mBoxName;
	static const QString mFirstButtonName;
	static const QString mSecondButtonName;
	static const QString mExtEmpty;
	
	void widgetInitialization(void);
};


#endif // !Q_FiILE_EXTENSION_MANAGER



