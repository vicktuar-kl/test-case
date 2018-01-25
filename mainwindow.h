#pragma once

#include <QWidget>
#include "mainmenu.h"
#include "item.h"
#include "inventory.h"

class MainWindow : public QWidget {
    Q_OBJECT
private:
    MainMenu *m_MainMenu;
    Inventory *m_Inventory;
    Item *m_Item;

    void createFormInterior();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};
