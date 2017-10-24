#include "QFileView.h"



#include <QPainter>



void QFileView::paintEvent(QPaintEvent * event)
{
	if (model() && model()->rowCount(rootIndex()) > 0) {
		QTreeView::paintEvent(event);
	} else {
		QPainter painter(viewport());
		QString text(tr("This folder is empty"));
		painter.setPen(QPalette().color(QPalette::Disabled, QPalette::WindowText));
		QRect textRect = painter.fontMetrics().boundingRect(text);
		textRect.moveCenter(viewport()->rect().center());
		painter.drawText(textRect, Qt::AlignCenter, text);
	}
}