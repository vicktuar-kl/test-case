#pragma once

#include <QTableWidget>
#include "item.h"
#include "inventorycell.h"

class Inventory : public QTableWidget {
    Q_OBJECT
private:
	int m_Size;
	QVector<InventoryCell*> m_Cells;

    void createFormInterior();

protected:
//	virtual void dragEnterEvent(QDragEnterEvent* event) override;
//	virtual void dropEvent(QDropEvent* event) override;

public:
	explicit Inventory(int size = 3, QWidget* parent = nullptr);

	int size() const;

	friend class InventoryCell;

signals:

private slots:
	void selectCellSlot(int row, int col);
};
