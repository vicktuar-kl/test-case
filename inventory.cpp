#include <QtWidgets>
#include "widgetmimedata.h"
#include "inventory.h"

Inventory::Inventory(uint size/* = 3*/, QWidget *parent/* = nullptr*/)
	: m_Size(size), QTableWidget(parent) {
	setDragEnabled(true);

    createFormInterior();
}

void Inventory::createFormInterior() {
	uint size = 270;

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

	for (uint i = 0; i < m_Size; ++i) {
		for (uint j = 0; j < m_Size; ++j) {
			InventoryCell* currentCell = new InventoryCell(i, j);
			setCellWidget(i, j, currentCell);
			connect(currentCell, SIGNAL(droppedItem(int,int)), this, SLOT(selectCell(int,int)));
		}
	}
}

uint Inventory::size() const {
    return m_Size;
}

void Inventory::selectCell(int row, int col) {	
	setCurrentCell(row, col);
	qDebug() << "(" << row << ", " << col << ") selected cell";
}
