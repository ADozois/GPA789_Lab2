#include "QFileSelector.h"


#include "QFileExplorer.h"
#include <QItemSelectionModel>

#include <QPushButton>
#include <QListView>
#include <QLabel>
#include <QHBoxLayout>
#include <QGroupBox>



QFileSelector::QFileSelector(QFileExplorer const & fileExplorer, QWidget * parent)
	:	QWidget(parent), 
		mFileExplorer{ fileExplorer }
{
	mSelectedFileModel.setDuplicateAllowed(false);

	mSelectedFileView = new QListView;
	mSelectedFileView->setModel(&mSelectedFileModel);
	mSelectedFileView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	mSelectedFileView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	mAddSelectedFiles = new QPushButton;
	mRemoveSelectedFiles = new QPushButton("Retirer le(s) fichier(s) sélectionné(s)");
	mRemoveAllFiles = new QPushButton("Retirer tous");
	
	mSelectedFileCounter = new QLabel;
	QPalette palette(mSelectedFileCounter->palette());
	palette.setColor(QPalette::WindowText, palette.color(QPalette::Mid));
	mSelectedFileCounter->setPalette(palette);
	mSelectedFileCounter->setAlignment(Qt::AlignRight | Qt::AlignTop);
	QVBoxLayout *fileCounterLayout = new QVBoxLayout;
	fileCounterLayout->setSpacing(0);
	fileCounterLayout->addWidget(mSelectedFileView);
	fileCounterLayout->addWidget(mSelectedFileCounter);

	QGroupBox * insertionGroupBox = new QGroupBox("Insertion à partir de l'explorateur de fichiers");
	QHBoxLayout * insertionLayout = new QHBoxLayout;
	insertionLayout->addWidget(mAddSelectedFiles);
	insertionLayout->addStretch();
	insertionGroupBox->setLayout(insertionLayout);

	QGroupBox * suppressionGroupBox = new QGroupBox("Gestion de la liste de fichiers");
	QHBoxLayout *suppressionLayout = new QHBoxLayout;
	suppressionLayout->addWidget(mRemoveSelectedFiles);
	suppressionLayout->addWidget(mRemoveAllFiles);
	suppressionLayout->addStretch();
	suppressionGroupBox->setLayout(suppressionLayout);

	QVBoxLayout * mainLayout = new QVBoxLayout;
	mainLayout->addWidget(insertionGroupBox);
	mainLayout->addLayout(fileCounterLayout);
	mainLayout->addWidget(suppressionGroupBox);

	setLayout(mainLayout);

	layout()->setMargin(0);

	connect(&mFileExplorer, &QFileExplorer::fileCountUpdated, this, &QFileSelector::updateAddFileButtonText);
	connect(mAddSelectedFiles, &QPushButton::clicked, this, &QFileSelector::addSelectedFile);
	connect(mRemoveSelectedFiles, &QPushButton::clicked, this, &QFileSelector::removeSelectedFile);
	connect(mRemoveAllFiles, &QPushButton::clicked, this, &QFileSelector::removeAllFile);
	connect(mSelectedFileView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &QFileSelector::updateGui);

	updateAddFileButtonText(0);
	updateGui();
}

void QFileSelector::updateAddFileButtonText(int nFiles)
{
	switch (nFiles) {
		case 0:
			mAddSelectedFiles->setText("Aucun fichier conforme");
			mAddSelectedFiles->setEnabled(false);
			break;
		case 1:
			mAddSelectedFiles->setText("Ajouter le fichier sélectionné");
			mAddSelectedFiles->setEnabled(true);
			break;
		default:
			mAddSelectedFiles->setText(QString("Ajouter les %1 fichiers sélectionnés").arg(nFiles));
			mAddSelectedFiles->setEnabled(true);
			break;
	}
}

void QFileSelector::updateGui()
{
	int nSelectedFiles{ mSelectedFileView->selectionModel()->selectedIndexes().size() };	
	switch (nSelectedFiles) {
		case 0:
			mRemoveSelectedFiles->setText("Aucun fichier sélectionné");
			break;
		case 1:
			mRemoveSelectedFiles->setText("Retirer le fichier sélectionné");
			break;
		default:
			mRemoveSelectedFiles->setText(QString("Retirer les %1 fichiers sélectionnés").arg(nSelectedFiles));
			break;
	}

	switch (selectedFilesCount()) {
		case 0:
			mSelectedFileCounter->setText("Aucun fichier à traiter");
			break;
		case 1:
			mSelectedFileCounter->setText("1 fichier à traiter");
			break;
		default:
			mSelectedFileCounter->setText(QString::number(mSelectedFileModel.rowCount()) + " fichiers à traiter");
			break;
	}

	mRemoveSelectedFiles->setEnabled(mSelectedFileModel.rowCount() > 0 && nSelectedFiles > 0);
	mRemoveAllFiles->setEnabled(mSelectedFileModel.rowCount() > 0);
}

void QFileSelector::addSelectedFile()
{
	mSelectedFileModel << mFileExplorer.selectedFiles();

	updateGui();
	emit listChanged();
}

void QFileSelector::removeSelectedFile()
{
	QModelIndexList list = mSelectedFileView->selectionModel()->selectedIndexes();

	if (list.size() == 0) {
		return;
	}

	qSort(list.begin(), list.end(), [](QModelIndex const & index1, QModelIndex const & index2)->bool { return index1.row() > index2.row(); });

	foreach(auto index, list) {
		if (!index.isValid()) return;
		mSelectedFileModel.removeRow(index.row());
	}

	updateGui();
	emit listChanged();
}

void QFileSelector::removeAllFile()
{
	mSelectedFileModel.removeRows(0, mSelectedFileModel.rowCount());

	updateGui();
	emit listChanged();
}

QStringList QFileSelector::selectedFiles() const 
{
	return mSelectedFileModel.stringList();
}

int QFileSelector::selectedFilesCount() const
{
	return mSelectedFileModel.rowCount();
}

