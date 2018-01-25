#include <QLayout>
#include <QDebug>
#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent) {
    m_Start = new QPushButton("Start");
    m_Start->setMinimumWidth(400);
    m_Exit = new QPushButton("Exit");
    m_Exit->setMinimumWidth(400);

    createFormInterior();
}

void MainMenu::createFormInterior() {
    qDebug() << "Main Menu";
    QHBoxLayout *layout = new QHBoxLayout;

    layout->setMargin(15);
    layout->addWidget(m_Start, 0, Qt::AlignTop | Qt::AlignLeft);
    layout->addWidget(m_Exit, 0, Qt::AlignTop | Qt::AlignRight);

    setLayout(layout);
}



