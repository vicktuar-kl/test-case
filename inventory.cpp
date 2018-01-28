#include <QtWidgets>
#include "widgetmimedata.hpp"
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

    createFormInterior();
}

void Inventory::createFormInterior() {
    qDebug() << "Inventory";
	setColumnCount(m_Size);
	setRowCount(m_Size);
    horizontalHeader()->setCascadingSectionResizes(false);
    verticalHeader()->setCascadingSectionResizes(false);
    horizontalHeader()->hide();
    verticalHeader()->hide();

	verticalHeader()->setMinimumSectionSize(260);
	verticalHeader()->setMaximumSectionSize(260);
	verticalHeader()->setDefaultSectionSize(260);
	horizontalHeader()->setMinimumSectionSize(260);
	horizontalHeader()->setMaximumSectionSize(260);
	horizontalHeader()->setDefaultSectionSize(260);

    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    verticalHeader()->setSizePolicy(sizePolicy);
    horizontalHeader()->setSizePolicy(sizePolicy);

	setMinimumSize(260 * m_Size, 260 * m_Size);
	setMaximumSize(260 * m_Size, 260 * m_Size);
    setSizePolicy(sizePolicy);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	for (uint i = 0; i < m_Size; ++i) {
		for (uint j = 0; j < m_Size; ++j) {
			setCellWidget(i, j, new InventoryCell);
		}
	}
}

/*virtual*/ void Inventory::dragEnterEvent(QDragEnterEvent *event) /*override*/ {
	if (event->mimeData()->hasFormat(WidgetMimeData::mimeType())) {
        event->acceptProposedAction();
	}
}

/*virtual*/ void Inventory::dropEvent(QDropEvent *event) /*override*/ {
	const WidgetMimeData* md =
			dynamic_cast<const WidgetMimeData*>(event->mimeData());
	if (md) {
		Item* droppedItem = dynamic_cast<Item*>(md->widget());
		InventoryCell* currentCell = new InventoryCell;
		currentCell->setContent(droppedItem);
		setCellWidget(0, 0, currentCell);
		qDebug() << "Dropped!";
	}
}

uint Inventory::size() const {
    return m_Size;
}

InventoryCell::InventoryCell(QWidget *parent)
	: m_Quantity(0), QWidget(parent) {
}

void InventoryCell::createFormInterior() {
	QHBoxLayout* cellLayout = new QHBoxLayout;
	QLabel* quantityItems = new QLabel("");

	cellLayout->addWidget(m_Content, 0, Qt::AlignCenter | Qt::AlignRight);
	cellLayout->addWidget(quantityItems, 0, Qt::AlignBottom | Qt::AlignLeft);

	setLayout(cellLayout);
	quantityItems->setText(QString::number(m_Quantity));
}

uint InventoryCell::quantity() const {
	return m_Quantity;
}

void InventoryCell::setQuantity(const uint& Quantity) {
	m_Quantity = Quantity;
}

Item* InventoryCell::content() const {
	return m_Content;
}

void InventoryCell::setContent(Item* Content) {
	m_Content = Content;
	createFormInterior();
}

void Inventory::selectCell(int row, int col) {
	setCurrentCell(row, col);
}
