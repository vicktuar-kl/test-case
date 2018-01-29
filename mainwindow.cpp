#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent/* = nullptr*/)
    : QWidget(parent) {
	//showFullScreen();
	m_MainMenu = new MainMenu(this);
    m_Inventory = new Inventory;
    m_Item = new Item(":/apple.jpg", "Apple");
	m_Item->setDisabled(true);
	m_ButtonMainMenu = new QPushButton("Main Menu");
	m_ButtonMainMenu->setMaximumWidth(400);

	connect(m_ButtonMainMenu, SIGNAL(clicked()), m_MainMenu, SLOT(show()));
	connect(m_ButtonMainMenu, SIGNAL(clicked()), this, SLOT(disable()));

    createFormInterior();
	disable();
}

MainWindow::~MainWindow() {

}

void MainWindow::createFormInterior() {
    qDebug() << "Main Window";
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *subHLayout = new QHBoxLayout;
    QVBoxLayout *subVLayout = new QVBoxLayout;

    subVLayout->setMargin(15);
	subVLayout->addWidget(m_Item, 0, Qt::AlignCenter);
	subVLayout->addWidget(m_ButtonMainMenu);

    subHLayout->setMargin(15);
    subHLayout->addWidget(m_Inventory);
    subHLayout->addLayout(subVLayout);

	mainLayout->addWidget(m_MainMenu);
	mainLayout->addLayout(subHLayout);

	setLayout(mainLayout);
}

void MainWindow::disable() {
	m_Inventory->setDisabled(true);
	m_Item->setDisabled(true);
	m_ButtonMainMenu->setDisabled(true);
}

void MainWindow::enable() {
	m_Inventory->setDisabled(false);
	m_Item->setDisabled(false);
	m_ButtonMainMenu->setDisabled(false);
}
