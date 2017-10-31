#ifndef Q_GENERATION_LOT_H
#define Q_GENERATION_LOT_H

#include <QWidget>

class QFileSelector;
class QFileExplorer;

class QGenerationLot : public QWidget
{
	Q_OBJECT

public:
	QGenerationLot(QFileExplorer const & fileExplorer,QWidget *parent);
	~QGenerationLot();

private:
	QFileSelector * mFileSelect;

};

#endif // !Q_GENERATION_LOT_H



