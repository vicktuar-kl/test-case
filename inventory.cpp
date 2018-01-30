#include <QtWidgets>
#include "inventorycell.h"
#include "inventory.h"

Inventory::Inventory(uint size/* = 3*/, QWidget *parent/* = nullptr*/)
	: m_Size(size), QTableWidget(parent) {
	setAcceptDrops(true);
	setDragDropOverwriteMode(true);
	setDragDropMode(QAbstractItemView::InternalMove);
	viewport()->setAcceptDrops(true);
	setDropIndicatorShown(true);

    createFormInterior();
}

void Inventory::createFormInterior() {
	uint size = 250;

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
}

void Inventory::dragEnterEvent(QDragEnterEvent* event) {
	if (event->mimeData()->hasFormat("application/x-item")) {
		event->acceptProposedAction();
	} else {
		event->ignore();
	}
}

void Inventory::dropEvent(QDropEvent* event) {
	if (event->mimeData()->hasFormat("application/x-item")) {
		QModelIndex index = indexAt(event->pos());
		QByteArray data = event->mimeData()->data("application/x-item");
		QDataStream dataStream(&data, QIODevice::ReadOnly);

		// TODO: передавать Item и количество
		QString picture;
		QString type;
		int number;

		dataStream >> picture >> type >> number;

		InventoryCell* tempCell = new InventoryCell(index.row(), index.column(),
													   number, );

		setCellWidget(index.row(), index.column(), tempCell);
		m_Cells.push_back(tempCell);
	} else {
		event->ignore();
	}
}

uint Inventory::size() const {
    return m_Size;
}
