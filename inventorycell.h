#pragma once

#include <QtWidgets>
#include "item.h"
#include "inventory.h"

class InventoryCell : public QWidget {
	Q_OBJECT
private:
	int m_Row;
	int m_Col;
	uint m_Quantity;
	Item* m_Content;
	QLabel* m_labelQuantityItems;

	QPoint m_DragStart;

	void createFormInterior();
	void updateLabel();
	void startDrag();

protected:
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void dragEnterEvent(QDragEnterEvent* event) override;
	virtual void dropEvent(QDropEvent* event) override;

public:
	explicit InventoryCell(int row, int col, QWidget* parent = nullptr);

	uint quantity() const;
	void incQuantity();
	void decQuantity();
	Item* content() const;
	void setQuantity(const uint& Quantity);
	void setContent(Item* Content);
	bool isEmpty();

signals:
	void droppedItem(int row, int col);

public slots:
};
