#ifndef Q_EXIT_FILE_NAME_H
#define Q_EXIT_FILE_NAME_H
#include <QWidget>

class QLabel;
class QGroupBox;
class QRadioButton;
class QLineEdit;
class QSpinBox;


class QExitFileName : public QWidget
{
	Q_OBJECT

public:
	QExitFileName(QWidget *parent);

private:
	QLabel * mFilePrefixLabel;
	QLabel * mNumberingLabel;
	QGroupBox * mFileNameGroupBox;
	QRadioButton * mUseSameNameButton;
	QRadioButton * mUseNewNameButton;
	QLineEdit * mNewName;
	QSpinBox * mStartNumberingBox;

};





#endif
