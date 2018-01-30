#pragma once

#include <QWidget>
#include "item.h"

class InventoryCell : public QWidget {
	Q_OBJECT
private:
	int m_Row;
	int m_Col;
	int m_Number;

	bool m_isSource;

	Item* m_Content;
	QLabel* m_NumberText;

	QPoint m_DragStart;
	void startDrag();

	void updateNumberText();

protected:
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;

public:
	explicit InventoryCell(QWidget* parent = nullptr);
	explicit InventoryCell(int row, int col, int number,
						   Item* item, bool isSource = false,
						   QWidget* parent = nullptr);

	void view();
	void setNumber(int number);
	int number() const;

	void setIsSource(bool isSource);

signals:

public slots:
};
