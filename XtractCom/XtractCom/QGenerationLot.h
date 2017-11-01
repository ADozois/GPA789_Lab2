#ifndef Q_GENERATION_LOT_H
#define Q_GENERATION_LOT_H

#include <QWidget>

class QFileSelector;
class QFileExplorer;
class QExitFolderSelector;

class QGenerationLot : public QWidget
{
	Q_OBJECT

public:
	QGenerationLot(QFileExplorer const & fileExplorer,QWidget *parent);
	~QGenerationLot();

private:
	QFileSelector * mFileSelect;
	QExitFolderSelector * mGroupExitFolderSelector;

};

#endif // !Q_GENERATION_LOT_H



