#include <QLayout>
#include <QDebug>
#include <QHeaderView>
#include "inventory.h"

Inventory::Inventory(uint size/* = 3*/, QWidget *parent/* = nullptr*/)
    : m_Size(size), QTableWidget(parent) {
    setColumnCount(m_Size);
    setRowCount(m_Size);
    for (uint i = 0; i < m_Size; ++i) {
        for (uint j = 0; j < m_Size; ++j) {
            setItem(i, j, new QTableWidgetItem);
            item(i, j)->setSizeHint(QSize(250, 250));
        }
    }

    createFormInterior();
}

void Inventory::createFormInterior() {
    qDebug() << "Inventory";
    horizontalHeader()->setCascadingSectionResizes(false);
    verticalHeader()->setCascadingSectionResizes(false);
    horizontalHeader()->hide();
    verticalHeader()->hide();

    verticalHeader()->setMinimumSectionSize(250);
    verticalHeader()->setMaximumSectionSize(250);
    verticalHeader()->setDefaultSectionSize(250);
    horizontalHeader()->setMinimumSectionSize(250);
    horizontalHeader()->setMaximumSectionSize(250);
    horizontalHeader()->setDefaultSectionSize(250);

    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    verticalHeader()->setSizePolicy(sizePolicy);
    horizontalHeader()->setSizePolicy(sizePolicy);

    setMinimumSize(252 * m_Size, 252 * m_Size);
    setSizePolicy(sizePolicy);
}

uint Inventory::size() const {
    return m_Size;
}
