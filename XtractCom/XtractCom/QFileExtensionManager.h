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



