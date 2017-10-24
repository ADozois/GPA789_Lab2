#ifndef Q_FILE_EXPLORER_FILE_MODEL_H
#define Q_FILE_EXPLORER_FILE_MODEL_H



#include <QFileSystemModel>

class QTreeView;



class QFileExplorerFileModel : public QFileSystemModel
{
	Q_OBJECT

public:
	QFileExplorerFileModel(QObject * parent = nullptr) : QFileSystemModel(parent) {}

	virtual QVariant data(QModelIndex const & index, int role = Qt::DisplayRole) const override;
	virtual bool hasChildren(const QModelIndex &parent) const override;

	void setPathView(QTreeView const * pathView) { mPathView = pathView; }

	QStringList suffixFilters() const { return mSuffixFilters; }
	void setSuffixFilters(QStringList const & suffixFilters) { mSuffixFilters = suffixFilters; }

	void filterFiles(QStringList & files) const;

protected:
	QTreeView const * mPathView{ nullptr };
	QStringList mSuffixFilters;

	bool isFileAccepted(QFileInfo const & fileInfo) const;
};



#endif // Q_FILE_EXPLORER_FILE_MODEL_H
