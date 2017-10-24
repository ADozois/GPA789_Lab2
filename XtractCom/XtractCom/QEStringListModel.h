#ifndef Q_ENHANCED_STRING_LIST_MODEL_H
#define Q_ENHANCED_STRING_LIST_MODEL_H



#include <QStringListModel>


class QEStringListModel : public QStringListModel
{
	Q_OBJECT

public:
	QEStringListModel(QObject * parent = nullptr) : QStringListModel(parent), mDuplicateAllowed{ true } {}

	void setDuplicateAllowed(bool allowed) { mDuplicateAllowed = allowed; }
	bool duplicateAllowed() const { return mDuplicateAllowed; }

	void append(QString const & string) {
		QString a = data(index(0), Qt::DisplayRole).toString();
		if (mDuplicateAllowed || (match(index(0), Qt::DisplayRole, string).size() == 0)) {
			insertRows(rowCount(), 1);
			setData(index(rowCount() - 1), string);
		}
	}

	void append(QStringList const & strings) {
		for (auto string : strings) {
			append(string);
		}
	}

	QEStringListModel & operator<<(QString const & string) {
		append(string);
		return *this;
	}

	QEStringListModel & operator<<(QStringList const & strings) {
		append(strings);
		return *this;
	}

private:
	bool mDuplicateAllowed;
};


#endif  // Q_ENHANCED_STRING_LIST_MODEL_H