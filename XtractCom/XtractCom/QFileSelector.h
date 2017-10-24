#ifndef Q_FILE_SELECTOR_H
#define Q_FILE_SELECTOR_H



#include <QWidget>
#include "QEStringListModel.h"

class QFileExplorer;
class QPushButton;
class QListView;
class QLabel;


class QFileSelector : public QWidget
{
	Q_OBJECT

public:
	QFileSelector(QFileExplorer const & fileExplorer, QWidget * parent = nullptr);

	QStringList selectedFiles() const;
	int selectedFilesCount() const;

signals:
	void listChanged();

protected slots:
	void updateAddFileButtonText(int nFiles);
	void addSelectedFile();
	void removeSelectedFile();
	void removeAllFile();
	void updateGui();
	
protected:
	QFileExplorer const & mFileExplorer;

	QEStringListModel mSelectedFileModel;
	QListView * mSelectedFileView;
	
	QPushButton * mAddSelectedFiles;
	QPushButton * mRemoveSelectedFiles;
	QPushButton * mRemoveAllFiles;
	QLabel * mSelectedFileCounter;
};






#endif // Q_FILE_SELECTOR_H
