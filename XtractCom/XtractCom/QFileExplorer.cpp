#include "QFileExplorer.h"



#include <QTreeView>
#include "QFileView.h"
#include <QVBoxLayout>
#include <QSplitter>
#include <QLineEdit>
#include <QHeaderView>
#include <QItemSelection>

#include <QDebug>


QFileExplorer::QFileExplorer(QWidget * parent)
	: QWidget(parent)
{
	mPathModel.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	mPathView = new QTreeView;
	mPathView->setModel(&mPathModel);
	mPathView->setSelectionMode(QAbstractItemView::SingleSelection);
	mPathView->header()->hide();
	mPathView->hideColumn(1);
	mPathView->hideColumn(2);
	mPathView->hideColumn(3);

	mFileModel.setPathView(mPathView);
	mFileModel.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
	//mFileModel.setSuffixFilters({ "h", "hpp", "c", "cpp", "" }); // <- custom quick patch for limitations of nameFilters
																	//mFileModel.setNameFilters(QStringList() << "*.h" << "*.hpp" << "*.c" << "*.cpp" << "*."); // <- les dossiers ainsi que les fichiers sans extension sont grisés
	mFileView = new QFileView;
	mFileView->setModel(&mFileModel);
	setSelectionMode(mSelectionMode);

	QSplitter * splitter{ new QSplitter };
	splitter->addWidget(mPathView);
	splitter->addWidget(mFileView);
	splitter->setCollapsible(0, true);
	splitter->setCollapsible(1, false);

	mPathFileEdit = new QLineEdit;
	mPathFileEdit->setStyleSheet(mPathFileCssFormatConform);

	QVBoxLayout * mainLayout = new QVBoxLayout;
	mainLayout->addWidget(splitter);
	mainLayout->addWidget(mPathFileEdit);

	setLayout(mainLayout);

	connect(&mPathModel, &QFileSystemModel::directoryLoaded, this, &QFileExplorer::initPathSelection);
	connect(mPathView->selectionModel(), &QItemSelectionModel::currentChanged, this, &QFileExplorer::updateFileModelFromPath);
	connect(mFileView, &QTreeView::activated, this, &QFileExplorer::activateFile);
	connect(mFileView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &QFileExplorer::updateFromFileSelection);
	connect(mPathFileEdit, &QLineEdit::textChanged, this, &QFileExplorer::updatePathFileConfirmation);
	connect(mPathFileEdit, &QLineEdit::returnPressed, this, &QFileExplorer::setFromPathFile);
	connect(&mPathFileFormatTimer, &QTimer::timeout, this, &QFileExplorer::updatePathFileFormat);

	mPathModel.setRootPath(mInitialPath);
}
QItemSelectionModel const * QFileExplorer::itemSelectionModel() const 
{ 
	return mFileView->selectionModel(); 
}

void QFileExplorer::updatePathFileFromPath(QModelIndex const & current, QModelIndex const & previous)
{
	mPathFileEdit->setText(mPathModel.fileInfo(mPathView->currentIndex()).absoluteFilePath());
}
void QFileExplorer::updatePathFileFromFile(QModelIndex const & current, QModelIndex const & previous)
{
	mPathFileEdit->setText(mFileModel.fileInfo(mFileView->currentIndex()).absoluteFilePath());
}
void QFileExplorer::updatePathFileConfirmation(QString const & text)
{
	QFileInfo fileInfo(text);

	if (mPathFileFormatTimer.isActive()) {
		mPathFileFormatTimer.stop();
	}

	if (!fileInfo.isDir() && !fileInfo.isFile()) {
		mPathFileEdit->setStyleSheet(mPathFileCssFormatIntermediate);
	} else {
		mPathFileEdit->setStyleSheet(mPathFileCssFormatConform);
	}
}
void QFileExplorer::setFromPathFile()
{
	QString completeFileInfo{ mPathFileEdit->text() };
	QFileInfo fileInfo(completeFileInfo);

	if (mPathFileFormatTimer.isActive()) {
		mPathFileFormatTimer.stop();
	}

	if (fileInfo.isDir()) {
		setPath(completeFileInfo, true);
		mPathView->setFocus();
	} else if (fileInfo.isFile()) {
		setPath(fileInfo.absolutePath(), true);
		mFileView->setCurrentIndex(mFileModel.index(completeFileInfo));
		mFileView->setFocus();
	} else {
		mPathFileEdit->setStyleSheet(mPathFileCssFormatInvalid);
		mPathFileFormatCurrentTime = 0;
		mPathFileFormatTimer.start(mPathFileFormatTimeout);
	}
}
void QFileExplorer::updatePathFileFormat()
{
	mPathFileFormatCurrentTime += mPathFileFormatTimeout;
	if (mPathFileFormatCurrentTime <= mPathFileFormatDuration) {
		qreal ratioIntermediate{ static_cast<qreal>(mPathFileFormatCurrentTime) / static_cast<qreal>(mPathFileFormatDuration) };
		qreal ratioInvalid{ 1.0 - ratioIntermediate };
		QColor color { QColor(	ratioIntermediate * mPathFileCssFormatIntermediateColor.red() + ratioInvalid * mPathFileCssFormatInvalidColor.red(),
								ratioIntermediate * mPathFileCssFormatIntermediateColor.green() + ratioInvalid * mPathFileCssFormatInvalidColor.green(),
								ratioIntermediate * mPathFileCssFormatIntermediateColor.blue() + ratioInvalid * mPathFileCssFormatInvalidColor.blue())};
		QString colorTxt{ QString("border: 1px solid rgb(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue()) };
		mPathFileEdit->setStyleSheet(colorTxt);
	} else {
		mPathFileFormatTimer.stop();
	}
}

void QFileExplorer::initPathSelection(QString const & path)
{
	setPath(path, false);

	connect(mPathView->selectionModel(), &QItemSelectionModel::currentChanged, this, &QFileExplorer::updatePathFileFromPath);
	connect(mFileView->selectionModel(), &QItemSelectionModel::currentChanged, this, &QFileExplorer::updatePathFileFromFile);
	connect(&mPathModel, &QFileSystemModel::directoryLoaded, this, static_cast<void (QFileExplorer::*)(QString const &)>(&QFileExplorer::updateFileModel));
	disconnect(&mPathModel, &QFileSystemModel::directoryLoaded, this, &QFileExplorer::initPathSelection);
}

void QFileExplorer::updateFileModel(QString const & path)
{
	mFileView->setRootIndex(mFileModel.setRootPath(path));
}

void QFileExplorer::updateFileModelFromPath(QModelIndex const & current, QModelIndex const & previous)
{
	if (current.isValid()) {
		updateFileModel(mPathModel.fileInfo(current).absoluteFilePath());
	}
}

void QFileExplorer::activateFile(QModelIndex const & fileModelIndex)
{
	QFileInfo fileInfo{ mFileModel.fileInfo(fileModelIndex) };
	if (fileInfo.isDir()) {
		setPath(mFileModel.fileInfo(fileModelIndex).absoluteFilePath(), true);
		mPathView->setFocus();
	} else if (fileInfo.isFile()) {
		//... ?send signal to select file?
	}
}

void QFileExplorer::setPath(const QString & path, bool expand)
{
	QModelIndex pathModelIndex{ mPathModel.index(path) };
	mPathView->setCurrentIndex(pathModelIndex);

	if (expand) {
		mPathView->expand(pathModelIndex);
	}

	updateFileModel(path);
}

void QFileExplorer::setSelectionMode(SelectionMode selectionMode)
{ 
	mSelectionMode = selectionMode; 

	switch (mSelectionMode)
	{
		case SelectionMode::Single:
			mFileView->setSelectionMode(QAbstractItemView::SingleSelection); 
			if (mFileView->selectionModel()->selectedIndexes().size() > 1) {
				mFileView->setCurrentIndex(mFileView->selectionModel()->selectedIndexes()[0]);
			}
			break;
		case SelectionMode::Extended:
			mFileView->setSelectionMode(QAbstractItemView::ExtendedSelection);
			break;
	}
}

void QFileExplorer::updateFromFileSelection(QItemSelection const & selected, QItemSelection const & deselected)
{
	QStringList validFiles{ selectedFiles() };

	emit fileCountUpdated(validFiles.size());

	if (validFiles.size() > 0) {
		emit fileSelected(validFiles[0]);
	}

	if (validFiles.size() > 0) {
		emit filesSelected(validFiles);
	}


	//if (receivers(SIGNAL(fileCountUpdated(int))) > 0) {
	//	emit fileCountUpdated(validFiles.size());
	//}

	//if (validFiles.size() > 0 && receivers(SIGNAL(fileSelected(QString))) > 0) {
	//	emit fileSelected(validFiles[0]);
	//}

	//if (validFiles.size() > 0 && receivers(SIGNAL(filesSelected(QStringList))) > 0) {
	//	emit filesSelected(validFiles);
	//}
}

QStringList QFileExplorer::selectedItems() const
{
	QStringList items;

	QModelIndexList indexes{ mFileView->selectionModel()->selectedIndexes() };
	QModelIndexList::iterator i{ indexes.begin() };
	while (i != indexes.end()) {
		items << mFileModel.fileInfo(*i).absoluteFilePath();
		i += mColumnNbr;
	}

	return items;
}
QStringList QFileExplorer::selectedFiles() const
{
	QStringList validFiles{ selectedItems() };
	mFileModel.filterFiles(validFiles);
	return validFiles;
}
QString QFileExplorer::selectedFile() const
{
	QStringList validFiles{ selectedItems() };
	mFileModel.filterFiles(validFiles);

	if (validFiles.size() > 0) {
		return validFiles[0];
	}

	return QString();
}
