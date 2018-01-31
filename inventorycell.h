#pragma once

#include <QWidget>
#include "item.h"

class InventoryCell : public QWidget {
	Q_OBJECT
private:
	int m_Row;
	int m_Col;
	int m_Number;

	bool m_isSource;

	Item* m_Content;
	QLabel* m_NumberText;

	QPoint m_DragStart;

	void updateNumberText();
	void clearCell();

protected:
	// drag
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;

	// drop
	virtual void dragEnterEvent(QDragEnterEvent* event) override;
	virtual void dropEvent(QDropEvent* event) override;

public:
	explicit InventoryCell(bool isSource = false, QWidget* parent = nullptr);
	explicit InventoryCell(int row, int col, int number,
						   Item* item, bool isSource = false,
						   QWidget* parent = nullptr);
	explicit InventoryCell(int row, int col, QWidget* parent = nullptr);

	void view();
	void setNumber(int number);
	int number() const;
	Item* content() const;
	void setContent(Item* content);

signals:
	void selectInvCellSignal(int row, int col);

public slots:
	void actionWithItem();
};
