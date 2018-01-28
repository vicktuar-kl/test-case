#pragma once

#include <QtWidgets>

class WidgetMimeData : public QMimeData {
private:
	QWidget *m_wgt;

public:
	WidgetMimeData();
	virtual ~WidgetMimeData();

	static QString mimeType();

	void setWidget(QWidget *wgt);

	QWidget* widget() const;
};
