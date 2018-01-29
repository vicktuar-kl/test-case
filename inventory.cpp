#include <QtWidgets>
#include "widgetmimedata.h"
#include "inventory.h"

Inventory::Inventory(uint size/* = 3*/, QWidget *parent/* = nullptr*/)
	: m_Size(size), QTableWidget(parent) {

	setAcceptDrops(true);
	setDragDropOverwriteMode(true);
	setDragDropMode(QAbstractItemView::InternalMove);
	viewport()->setAcceptDrops(true);
	setDropIndicatorShown(true);

	setMouseTracking(true);

	connect(this, SIGNAL(cellEntered(int,int)), this, SLOT(selectCell(int, int)));
	connect(this, SIGNAL(cellActivated(int,int)), this, SLOT(selectCell(int, int)));

    createFormInterior();
}

void Inventory::createFormInterior() {
    qDebug() << "Inventory";
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
			setCellWidget(i, j, new InventoryCell); // connect signal droppedItem with slot InventoryCell::setItem
		}
	}
}

/*virtual*/ void Inventory::dragEnterEvent(QDragEnterEvent *event) /*override*/ {
	if (event->mimeData()->hasFormat(WidgetMimeData::mimeType())) {
        event->acceptProposedAction();
	}
	QTableWidget::dragEnterEvent(event);
}

/*virtual*/ void Inventory::dropEvent(QDropEvent *event) /*override*/ {
	qDebug() << "Dropped!";
	const WidgetMimeData* md =
			dynamic_cast<const WidgetMimeData*>(event->mimeData());
	if (md) {
		Item* droppedItem = dynamic_cast<Item*>(md->widget());
		InventoryCell* currentCell = dynamic_cast<InventoryCell*>(cellWidget(m_SelectedRow, m_SelectedCol));
		if (currentCell->quantity() == 0) {
			currentCell->setContent(droppedItem);
		}
		currentCell->incQuantity();
	}
	QTableWidget::dropEvent(event);
}

uint Inventory::size() const {
    return m_Size;
}

void Inventory::selectCell(int row, int col) {	
	m_SelectedRow = row;
	m_SelectedCol = col;
	if (this->hasFocus()) {
		setCurrentCell(m_SelectedRow, m_SelectedCol);
		qDebug() << "(" << m_SelectedRow << ", " << m_SelectedCol << ") selected cell";
	}
}
