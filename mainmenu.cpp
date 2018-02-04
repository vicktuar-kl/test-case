#include <QLayout>
#include "mainmenu.h"

// создание виджета и связывание сигналов кнопок со слотами
MainMenu::MainMenu(QWidget* parent/* = nullptr*/)
	: QWidget(parent) {
	m_NewGame = new QPushButton("Новая игры");
	m_Exit = new QPushButton("Выход");
	m_NewGame->setMinimumWidth(400);
    m_Exit->setMinimumWidth(400);

	connect(m_NewGame, SIGNAL(clicked()), this, SLOT(hide()));
	connect(m_NewGame, SIGNAL(clicked()), parent, SLOT(enable()));
	connect(m_Exit, SIGNAL(clicked()), qApp, SLOT(quit()));

	createFormInterior();
}

// Компоновка кнопок на виджете
void MainMenu::createFormInterior() {
    QHBoxLayout *layout = new QHBoxLayout;

	layout->addWidget(m_NewGame, 0, Qt::AlignTop | Qt::AlignHCenter);
	layout->addStretch();
	layout->addWidget(m_Exit, 0, Qt::AlignTop | Qt::AlignHCenter);

    setLayout(layout);
}



