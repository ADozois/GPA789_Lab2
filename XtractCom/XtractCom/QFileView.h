#ifndef Q_FILE_VIEW_H
#define Q_FILE_VIEW_H



#include <QTreeView>


class QFileView : public QTreeView
{
	Q_OBJECT

public:
	QFileView(QWidget * parent = nullptr) : QTreeView(parent) {}

protected:
	virtual void paintEvent(QPaintEvent * event) override;
};


#endif // Q_FILE_VIEW_H
