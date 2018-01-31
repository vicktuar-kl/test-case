#include <QLayout>
#include <QDebug>
#include "mainmenu.h"

MainMenu::MainMenu(QWidget* parent/* = nullptr*/)
	: QWidget(parent) {
	m_NewGame = new QPushButton("Новая Игра");
	m_Quit = new QPushButton("Выход");
	m_NewGame->setMinimumWidth(400);
	m_Quit->setMinimumWidth(400);

	connect(m_NewGame, SIGNAL(clicked()), this, SLOT(hide()));
	connect(m_NewGame, SIGNAL(clicked()), parent, SLOT(enable()));
	connect(m_Quit, SIGNAL(clicked()), qApp, SLOT(quit()));

	createFormInterior();
}

void MainMenu::createFormInterior() {
    QHBoxLayout *layout = new QHBoxLayout;

	layout->addWidget(m_NewGame, 0, Qt::AlignTop | Qt::AlignHCenter);
	layout->addStretch();
	layout->addWidget(m_Quit, 0, Qt::AlignTop | Qt::AlignHCenter);

    setLayout(layout);
}



