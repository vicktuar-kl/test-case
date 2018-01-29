#pragma once

#include <QTableWidget>
#include "item.h"
#include "inventorycell.h"

typedef unsigned int uint;

class Inventory : public QTableWidget {
    Q_OBJECT
private:
    uint m_Size;

    void createFormInterior();
	void cellFilling();

protected:
//	virtual void dragEnterEvent(QDragEnterEvent* event) override;
//	virtual void dropEvent(QDropEvent* event) override;

public:
	explicit Inventory(uint size = 3, QWidget* parent = nullptr);

    uint size() const;

signals:

public slots:
	void selectCell(int row, int col);
};
