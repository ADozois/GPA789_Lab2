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
