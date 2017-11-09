#ifndef Q_ADDITIONNAL_OPTION_H
#define Q_ADDITIONNAL_OPTION_H


#include <QWidget>

class QGroupBox;
class QCheckBox;


class QAdditionnalOption : public QWidget
{
	Q_OBJECT

public:
	QAdditionnalOption(QWidget * parent = nullptr);

protected:
	QGroupBox * mGroupBoxOption;
	QCheckBox * mCheckBoxAddStats;

private:
	static const QString mGroupBoxName;
	static const QString mCheckBoxDescription;

};


#endif
