#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent/* = nullptr*/)
    : QWidget(parent) {
    m_MainMenu = new MainMenu;
    m_Inventory = new Inventory;
    m_Item = new Item(":/apple.jpg", "Apple");

    createFormInterior();
}

MainWindow::~MainWindow() {

}

void MainWindow::createFormInterior() {
    qDebug() << "Main Window";
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *subHLayout = new QHBoxLayout;
    QVBoxLayout *subVLayout = new QVBoxLayout;

    subVLayout->setMargin(15);
    subVLayout->addWidget(m_Item);
    subVLayout->addWidget(new QPushButton("PLACEHOLDER"));

    subHLayout->setMargin(15);
    subHLayout->addWidget(m_Inventory);
    subHLayout->addLayout(subVLayout);

    mainLayout->addWidget(m_MainMenu);
    mainLayout->addLayout(subHLayout);

    setLayout(mainLayout);
}
