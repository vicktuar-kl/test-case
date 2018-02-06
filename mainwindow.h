#pragma once

#include <QtWidgets>
#include "mainmenu.h"
#include "item.h"
#include "inventory.h"
#include "inventorycell.h"

// ============================================================================
// Класс для компоновки всех виджетов, главное окно

class MainWindow : public QWidget {
    Q_OBJECT
private:
	MainMenu* m_MainMenu;			// Виджет главного меню
	Inventory* m_Inventory;			// таблица инвентаря
	InventoryCell* m_Source;		// источник предметов
	QPushButton* m_ButtonMainMenu;	// кнопка вызова главног меню

	void createFormInterior();		// компоновка виджетов

public:
	MainWindow(QWidget *parent = 0);	// связывание сигнала clicked кнопки со слотами вызова главного меню и блокировки виджетов

public slots:
	// слоты для блокировки/разблокировки всех виджетов главного окна
	void disable();
	void enable();
};
