#pragma once

#include <QWidget>
#include <QTableWidget>
#include "item.h"

typedef unsigned int uint;
typedef QMap<uint, QPair<Item*, uint>> cellContent;

class Inventory : public QWidget {
    Q_OBJECT
private:
    uint m_Size;
    QTableWidget* m_InvetoryBoard;
    cellContent m_cellContent;

    void createFormInterior();

public:
    explicit Inventory(uint size = 3, QWidget *parent = nullptr);

    uint size() const;

signals:

public slots:
};
