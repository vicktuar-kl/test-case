#include "widgetmimedata.h"
#include "widgetdrag.h"

WidgetDrag::WidgetDrag(QWidget* dragSource/* = nullptr*/)
	: QDrag(dragSource) { }

void WidgetDrag::setWidget(QWidget* wgt) {
	WidgetMimeData* md = new WidgetMimeData;
	md->setWidget(wgt);
	setMimeData(md);
}
