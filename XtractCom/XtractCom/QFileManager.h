#ifndef Q_FILE_MANAGER_H
#define Q_FILE_MANAGER_H

#include <QWidget>

class QExitFolderSelector;
class QFileExtensionManager;
class QExitFileName;

class QFileManager : public QWidget
{
	Q_OBJECT

public:
	QFileManager(QWidget * parent = nullptr);
	bool optionsValid(void);
	void showErrors(QStringList const & errorsList);

private:

	QExitFolderSelector * mExitFolderSelector;
	QFileExtensionManager * mFileExtensionManager;
	QExitFileName * mExitFileNameManager;

};

#endif 
