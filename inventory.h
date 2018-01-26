#pragma once

#include <QTableWidget>
#include "item.h"

typedef unsigned int uint;
typedef QMap<uint, QPair<Item*, uint>> cellContent;

class Inventory : public QTableWidget {
    Q_OBJECT
private:
    uint m_Size;
    cellContent m_cellContent;

    void createFormInterior();

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dropEvent(QDropEvent *event);

public:
    explicit Inventory(uint size = 3, QWidget *parent = nullptr);

    uint size() const;

signals:

public slots:
};
