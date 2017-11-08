#ifndef Q_GENERATION_LOT_H
#define Q_GENERATION_LOT_H

#include <QWidget>

class QFileSelector;
class QFileExplorer;
class QFileManager;

class QBatchProcess : public QWidget
{
	Q_OBJECT

public:
	QBatchProcess(QFileExplorer const & fileExplorer,QWidget *parent);
	~QBatchProcess();

public slots:
void generate(bool checked);

private:
	QFileSelector * mFileSelect;
	QFileManager * mFileManager;

	bool checkGenerateValid(void);


};

#endif // !Q_GENERATION_LOT_H



