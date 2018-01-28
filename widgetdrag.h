#pragma once

#include <QtWidgets>

class WidgetDrag : public QDrag {
public:
	WidgetDrag(QWidget* dragSource = nullptr);
	void setWidget(QWidget* wgt);
};
