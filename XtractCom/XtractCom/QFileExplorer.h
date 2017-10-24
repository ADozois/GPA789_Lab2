#ifndef Q_FILE_EXPLORER_H
#define Q_FILE_EXPLORER_H


#include <QWidget>
#include <QFileSystemModel>
#include <QTimer>
#include "QFileExplorerFileModel.h"

class QItemSelectionModel;
class QTreeView;
class QFileView;
class QLineEdit;
class QItemSelection;


class QFileExplorer : public QWidget
{
	Q_OBJECT

public:
	enum class SelectionMode { Single, Extended };

	QFileExplorer(QWidget * parent = nullptr);

	void setFileSuffixFilter(QStringList const & filter) { mFileModel.setSuffixFilters(filter); }
	void setSelectionMode(SelectionMode selectionMode);

	QStringList selectedItems() const;
	QStringList selectedFiles() const;
	QString selectedFile() const;

	QItemSelectionModel const * itemSelectionModel() const;

signals:
	void fileCountUpdated(int nFilesSelected);
	void fileSelected(QString file);
	void filesSelected(QStringList files);

protected slots:
	void initPathSelection(QString const & path);
	void updateFileModel(QString const & path);
	void updateFileModelFromPath(QModelIndex const & current, QModelIndex const & previous);
	void activateFile(QModelIndex const & pathModelIndex);
	void updateFromFileSelection(QItemSelection const & selected, QItemSelection const & deselected);
	void updatePathFileFromPath(QModelIndex const & current, QModelIndex const & previous);
	void updatePathFileFromFile(QModelIndex const & current, QModelIndex const & previous);
	void updatePathFileConfirmation(QString const & text);
	void setFromPathFile();
	void updatePathFileFormat();

protected:
	const int mColumnNbr{ 4 };
	SelectionMode mSelectionMode{ SelectionMode::Single };
	QString mInitialPath{ "c:/" };
	QFileSystemModel mPathModel;
	QFileExplorerFileModel mFileModel;
	QTreeView * mPathView{ nullptr };
	QFileView * mFileView{ nullptr };
	QLineEdit * mPathFileEdit{ nullptr };
	QTimer mPathFileFormatTimer;
	const int mPathFileFormatDuration{ 750 };
	const int mPathFileFormatTimeout{ 33 };
	int mPathFileFormatCurrentTime{ 0 };
	const QColor mPathFileCssFormatInvalidColor{ QColor(255, 0, 0) };
	const QColor mPathFileCssFormatConformColor{ QPalette().color(QPalette::Active, QPalette::Mid) }; 
	const QColor mPathFileCssFormatIntermediateColor{ QColor(255, 208, 127) }; // = rgb(255, 162, 0) at 50% saturation
	const QString mPathFileCssFormatConform{ QString("border: 1px solid rgb(%1, %2, %3)").arg(mPathFileCssFormatConformColor.red()).arg(mPathFileCssFormatConformColor.green()).arg(mPathFileCssFormatConformColor.blue()) };
	const QString mPathFileCssFormatInvalid{ QString("border: 1px solid rgb(%1, %2, %3)").arg(mPathFileCssFormatInvalidColor.red()).arg(mPathFileCssFormatInvalidColor.green()).arg(mPathFileCssFormatInvalidColor.blue()) };
	const QString mPathFileCssFormatIntermediate{ QString("border: 1px solid rgb(%1, %2, %3)").arg(mPathFileCssFormatIntermediateColor.red()).arg(mPathFileCssFormatIntermediateColor.green()).arg(mPathFileCssFormatIntermediateColor.blue()) };

	void setPath(const QString & path, bool expand = true);
};


#endif //Q_FILE_EXPLORER_H
