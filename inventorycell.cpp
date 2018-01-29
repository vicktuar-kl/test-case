#include "inventorycell.h"

InventoryCell::InventoryCell(QWidget *parent)
	: QWidget(parent), m_Quantity(0) {
	setMouseTracking(true);
}

void InventoryCell::createFormInterior() {
	QHBoxLayout* cellLayout = new QHBoxLayout;
	m_labelQuantityItems = new QLabel("");

	cellLayout->addWidget(m_Content, 0, Qt::AlignCenter | Qt::AlignRight);
	cellLayout->addWidget(m_labelQuantityItems, 0, Qt::AlignBottom | Qt::AlignLeft);

	setLayout(cellLayout);
	m_labelQuantityItems->setText(m_Quantity > 0 ? QString::number(m_Quantity) : "");
	m_labelQuantityItems->setStyleSheet("color: black");
}

/*virtual*/ void InventoryCell::mousePressEvent(QMouseEvent* event) /*override*/ {
	if (event->button() == Qt::RightButton) {
		--m_Quantity;
		if (m_Quantity == 0) {
			qDebug() << "Placeholder for deleting Item";
			m_Content->eat();
		update();
		}
	}
	QWidget::mousePressEvent(event);
}

void InventoryCell::update() {
	m_labelQuantityItems->setText(m_Quantity > 0 ? QString::number(m_Quantity) : "");
}

uint InventoryCell::quantity() const {
	return m_Quantity;
}

void InventoryCell::incQuantity() {
	++m_Quantity;
	update();
}

void InventoryCell::decQuantity() {
	--m_Quantity;
	update();
}

Item* InventoryCell::content() const {
	return m_Content;
}

void InventoryCell::setContent(Item* Content) {
	m_Content = Content;
	createFormInterior();
}
