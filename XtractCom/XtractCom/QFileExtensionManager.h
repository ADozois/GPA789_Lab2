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
	QFileExtensionManager(QString const & boxName, QString const & extension, QString const & firstButton, QString const & secondButton, QWidget *parent = nullptr);
	~QFileExtensionManager();

	public slots:
	QString getExtension(void);

private:
	QGroupBox * mGroupBox;
	QRadioButton * mXtractExt;
	QRadioButton * mOtherExt;
	QLineEdit * mExtension;

	void widgetInitialization(void);
};


#endif // !Q_FiILE_EXTENSION_MANAGER



