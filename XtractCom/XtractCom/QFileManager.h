#ifndef Q_FILE_MANAGER_H
#define Q_FILE_MANAGER_H

#include <QWidget>

class QExitFolderSelector;
class QFileExtensionManager;

class QFileManager : public QWidget
{
	Q_OBJECT

public:
	QFileManager(QWidget * parent = nullptr);

private:

	QExitFolderSelector * mExitFolderSelector;
	QFileExtensionManager * mFileExtensionManager;

};

#endif 
