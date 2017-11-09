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
	QStringList boxIsValid(void);
	QString getFolder(void);


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