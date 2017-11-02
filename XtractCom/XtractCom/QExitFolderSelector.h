#ifndef Q_Exit_Folder_Selector_H
#define Q_Exit_Folder_Selector_H


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
protected:
	QGroupBox * mGroupBoxExitFolder;
	QPushButton * mSelectButton;
	QRadioButton * mRadioButtonSourceFolder;
	QRadioButton * mRadioButtonNewFolder;
	QLabel * mFolderPathLabel;

	protected slots:
	void getDirectoryPath();

};


#endif