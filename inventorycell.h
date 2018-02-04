#pragma once

#include <QWidget>
#include "item.h"

// ============================================================================
// Класс ячейки инвентаря, в котором реализован функционал Drag'n'Drop

class InventoryCell : public QWidget {
	Q_OBJECT	
public:
	explicit InventoryCell(bool isSource = true, QWidget* parent = nullptr);	// конструктор по-умолчанию, вечный генератор яблок
	explicit InventoryCell(int row, int col, int number,						// конструктор для создания заполненной ячейки
						   Item* item, bool isSource = false,
						   QWidget* parent = nullptr);
	explicit InventoryCell(int row, int col, QWidget* parent = nullptr);		// для заполнения инвентаря пустыми ячейками

	void view();						// компоновка виджета предмета и виджета отображения количества предметов

protected:
	// drag
	virtual void mouseMoveEvent(QMouseEvent* event) override;		// обработка перетаскивания предмета из ячейки
	virtual void mousePressEvent(QMouseEvent* event) override;		// на зажатие левой кнопки - вычисление позиции m_DragStart, на правую - действия с предметом (поедание яблок)

	// drop
	virtual void dragEnterEvent(QDragEnterEvent* event) override;	// При входе в зону сброса предмета, проверяем mime-type
	virtual void dropEvent(QDropEvent* event) override;				// "Принятие" предмета ячейкой и его отображение вместе с количеством

private:
	int m_Row;
	int m_Col;
	int m_Number;				// количество предметов в ячейке

	QSoundEffect m_SoundEffect;	// звуковой эффект для действия с предметом в инвентаре

	bool m_isSource;			// является ли ячейка бесконечным "источником" предметов

	Item* m_Content;			// содержимое ячейки
	QLabel* m_NumberText;		// Надпись для отображения количества предметов

	QPoint m_DragStart;			// Координаты начала перетаскивания предмета

	void updateNumberText();	// Обновление виджета отображения количества элементов
	void clearCell();			// "Опустошение" ячейки от её содержимого и очистка компоновки

public slots:
	void actionWithItem();				// слот для совершения действия над предметом в ячейке
};
