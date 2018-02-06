#pragma once

#include <QTableWidget>
#include "item.h"
#include "inventorycell.h"

// ============================================================================
// Класс инвентаря, содержит виджеты ячеек InventoryCell

class Inventory : public QTableWidget {
    Q_OBJECT

public:
	explicit Inventory(int size = 3, QWidget* parent = nullptr);

	virtual ~Inventory();

private:
	int m_Size;		// размер инвентаря, инвентарь квадратный
	QVector<InventoryCell*> m_Cells;

	void createFormInterior();	// Настройка внешнего вида виджета
};
