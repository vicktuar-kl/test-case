#pragma once

#include <QTableWidget>
#include "item.h"

typedef unsigned int uint;

class Inventory : public QTableWidget {
    Q_OBJECT
private:
    uint m_Size;

	friend class InventoryCell;

    void createFormInterior();
	void cellFilling();

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
	virtual void dropEvent(QDropEvent *event) override;

public:
    explicit Inventory(uint size = 3, QWidget *parent = nullptr);

    uint size() const;

signals:

public slots:
	void selectCell(int row, int col);
};

class InventoryCell : public QWidget {
	Q_OBJECT
private:
	uint m_Quantity;
	Item* m_Content;

	void createFormInterior();

public:
	explicit InventoryCell(QWidget *parent = nullptr);

	uint quantity() const;
	void setQuantity(const uint& Quantity);
	Item* content() const;
	void setContent(Item* Content);

signals:

public slots:
};
