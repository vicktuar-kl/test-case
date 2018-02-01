#include <QtWidgets>
#include "inventorycell.h"
#include "inventory.h"

// Настройка вннешего вида инвентаря и заполнение его виджетами ячеек
Inventory::Inventory(int size/* = 3*/, QWidget *parent/* = nullptr*/)
	: QTableWidget(parent), m_Size(size) {
	setMouseTracking(true);
	connect(this, SIGNAL(cellEntered(int,int)), this, SLOT(selectCellSlot(int,int)));

    createFormInterior();
	for (int i = 0; i < m_Size; ++i) {
		for (int j = 0; j < m_Size; ++j) {
			InventoryCell* tempCell = new InventoryCell(i, j);
			setCellWidget(i, j, tempCell);
			m_Cells.push_back(tempCell);
		}
	}
}

// Настройка внешнего вида таблицы
void Inventory::createFormInterior() {
	int size = 250;

	setColumnCount(m_Size);
	setRowCount(m_Size);
    horizontalHeader()->setCascadingSectionResizes(false);
    verticalHeader()->setCascadingSectionResizes(false);
    horizontalHeader()->hide();
    verticalHeader()->hide();

	verticalHeader()->setMinimumSectionSize(size);
	verticalHeader()->setMaximumSectionSize(size);
	verticalHeader()->setDefaultSectionSize(size);
	horizontalHeader()->setMinimumSectionSize(size);
	horizontalHeader()->setMaximumSectionSize(size);
	horizontalHeader()->setDefaultSectionSize(size);

    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    verticalHeader()->setSizePolicy(sizePolicy);
    horizontalHeader()->setSizePolicy(sizePolicy);

	setMinimumSize(size * m_Size, size * m_Size);
	setMaximumSize(size * m_Size, size * m_Size);
    setSizePolicy(sizePolicy);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setSelectionMode(QAbstractItemView::SingleSelection);
}

// слот, выделяющий ячейку
void Inventory::selectCellSlot(int row, int col)	{
	setCurrentCell(row, col);
}
