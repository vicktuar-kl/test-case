#pragma once

#include <QtWidgets>
#include "item.h"
#include "inventory.h"

class InventoryCell : public QWidget {
	Q_OBJECT
private:
	uint m_Quantity;
	Item* m_Content;
	QLabel* m_labelQuantityItems;

	void createFormInterior();
	void update();

protected:
	virtual void mousePressEvent(QMouseEvent* event) override;

public:
	explicit InventoryCell(QWidget* parent = nullptr);

	uint quantity() const;
	void incQuantity();
	void decQuantity();
	Item* content() const;
	void setContent(Item* Content);

signals:

public slots:
};
