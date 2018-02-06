#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include "mainwindow.h"

// связывание сигнала clicked кнопки со слотами вызова главного меню и блокировки виджетов
MainWindow::MainWindow(QWidget *parent/* = nullptr*/)
    : QWidget(parent) {
	m_MainMenu = new MainMenu(this);
    m_Inventory = new Inventory;
	m_Source = new InventoryCell(true);
	m_ButtonMainMenu = new QPushButton("Главное меню");
	m_ButtonMainMenu->setMaximumWidth(400);

	connect(m_ButtonMainMenu, SIGNAL(clicked()), m_MainMenu, SLOT(show()));
	connect(m_ButtonMainMenu, SIGNAL(clicked()), this, SLOT(disable()));

    createFormInterior();
	disable();
}

// Компоновка виджетов главного окна
void MainWindow::createFormInterior() {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *subHLayout = new QHBoxLayout;
    QVBoxLayout *subVLayout = new QVBoxLayout;

    subVLayout->setMargin(15);
	m_Source->view();
	subVLayout->addWidget(m_Source);
	subVLayout->addWidget(m_ButtonMainMenu);

    subHLayout->setMargin(15);
    subHLayout->addWidget(m_Inventory);
    subHLayout->addLayout(subVLayout);

	mainLayout->addWidget(m_MainMenu);
	mainLayout->addLayout(subHLayout);

	setLayout(mainLayout);
}

// слоты для блокировки всех виджетов главного окна
void MainWindow::disable() {
	m_Inventory->setDisabled(true);
	m_Source->setDisabled(true);
	m_ButtonMainMenu->setDisabled(true);
}

// слоты для разблокировки всех виджетов главного окна
void MainWindow::enable() {
	m_Inventory->setDisabled(false);
	m_Source->setDisabled(false);
	m_ButtonMainMenu->setDisabled(false);
}
