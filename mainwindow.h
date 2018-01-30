#pragma once

#include <QtWidgets>
#include "mainmenu.h"
#include "item.h"
#include "inventory.h"
#include "inventorycell.h"

class MainWindow : public QWidget {
    Q_OBJECT
private:
	MainMenu* m_MainMenu;
	Inventory* m_Inventory;
	InventoryCell* m_Source;
	QPushButton* m_ButtonMainMenu;

    void createFormInterior();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void disable();
	void enable();
};
