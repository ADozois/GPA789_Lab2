#ifndef Q_GENERATION_LOT_H
#define Q_GENERATION_LOT_H

#include <QWidget>

class QFileSelector;
class QFileExplorer;
class QFileManager;
class QPushButtonBox;

class QBatchProcess : public QWidget
{
	Q_OBJECT

public:
	QBatchProcess(QFileExplorer const & fileExplorer,QWidget *parent);
	~QBatchProcess()=default;

public slots:
	void generate(bool checked);
	void listChanged(void);

private:
	QFileSelector * mFileSelect;
	QFileManager * mFileManager;
	QPushButtonBox * mGenerateButton;

	bool checkGenerateValid(void);
	void cleanList(QStringList & filesList);

};

#endif // !Q_GENERATION_LOT_H



