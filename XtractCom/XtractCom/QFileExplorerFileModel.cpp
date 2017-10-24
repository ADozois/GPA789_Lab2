#include "QFileExplorerFileModel.h"



#include <QTreeView>
#include <QPalette>



bool QFileExplorerFileModel::isFileAccepted(QFileInfo const & fileInfo) const
{
	if (mSuffixFilters.size() == 0) {
		return true;
	}

	if (fileInfo.isFile() && mSuffixFilters.contains(fileInfo.suffix(), Qt::CaseInsensitive)) {
		return true;
	}

	return false;
}
void QFileExplorerFileModel::filterFiles(QStringList & files) const
{
	QStringList::iterator i{ files.begin() };

	while (i != files.end()) {
		QFileInfo fileInfo{ *i }; 
		if (isFileAccepted(fileInfo)) {
			++i;
		} else {
			i = files.erase(i);
		}
	}
}
QVariant QFileExplorerFileModel::data(QModelIndex const & index, int role) const
{
	if (role == Qt::ForegroundRole) {
		if (index.isValid()) {
			QFileInfo fileInformation(fileInfo(index).absoluteFilePath());
			if (fileInformation.isFile() && !isFileAccepted(fileInformation)) {
				return QVariant(QPalette().color(QPalette::Disabled, QPalette::WindowText));
				// to do : the associated icon should look disabled too
			}
		}
	}

	return QFileSystemModel::data(index, role);
}
bool QFileExplorerFileModel::hasChildren(const QModelIndex &parent) const
{
	if (!mPathView) {
		return QFileSystemModel::hasChildren(parent);
	}

	return (parent.data().toString() == mPathView->currentIndex().data().toString());
}



