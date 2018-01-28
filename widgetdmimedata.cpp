#include "widgetmimedata.h"

WidgetMimeData::WidgetMimeData()
	: QMimeData() { }

/*virtual*/ WidgetMimeData::~WidgetMimeData() { }

/*static*/ QString WidgetMimeData::mimeType() {
	return "application/x-item";
}

void WidgetMimeData::setWidget(QWidget* wgt) {
	m_wgt = wgt;
	setData(mimeType(), QByteArray());
}

QWidget* WidgetMimeData::widget() const {
	return m_wgt;
}
