#include <QLayout>
#include <QDebug>
#include "inventory.h"

Inventory::Inventory(uint size/* = 3*/, QWidget *parent/* = nullptr*/)
    : m_Size(size), QWidget(parent) {
    m_InvetoryBoard = new QTableWidget(m_Size, m_Size);
    for (uint i = 0; i < m_Size; ++i) {
        for (uint j = 0; j < m_Size; ++j) {
            m_InvetoryBoard->setItem(i, j, new QTableWidgetItem);
            m_InvetoryBoard->item(i, j)->setSizeHint(QSize(250, 250));
        }
    }

    createFormInterior();
}

void Inventory::createFormInterior() {
    qDebug() << "Inventory";
}

uint Inventory::size() const {
    return m_Size;
}


QTableWidget *Inventory::invetoryBoard() const {
    return m_InvetoryBoard;
}


