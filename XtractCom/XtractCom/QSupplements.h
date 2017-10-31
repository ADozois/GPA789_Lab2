#ifndef Q_SUPPLEMENTS_H
#define Q_SUPPLEMENTS_H

#include <QWidget>
class QPushButton;
class QMessageBox;

class QSupplements : public QWidget
{
	Q_OBJECT
public:

	QSupplements(QWidget * parent = nullptr);

protected:
	QPushButton * mButtonXTractC;
	QPushButton * mButtonCpp;
	QPushButton * mButtonQt;
	QMessageBox * mMessageCpp;
	
protected slots:
	void showAboutXtractC();




};




#endif
