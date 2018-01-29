#include <QLayout>
#include <QDebug>
#include "mainmenu.h"

MainMenu::MainMenu(QWidget* parent/* = nullptr*/)
	: QWidget(parent) {
    m_Start = new QPushButton("Start");
	m_Exit = new QPushButton("Exit");
    m_Start->setMinimumWidth(400);
    m_Exit->setMinimumWidth(400);

	connect(m_Start, SIGNAL(clicked()), this, SLOT(hide()));
	connect(m_Start, SIGNAL(clicked()), parent, SLOT(enable()));
	connect(m_Exit, SIGNAL(clicked()), qApp, SLOT(quit()));

	createFormInterior();
}

void MainMenu::createFormInterior() {
    qDebug() << "Main Menu";
    QHBoxLayout *layout = new QHBoxLayout;

	layout->addWidget(m_Start, 0, Qt::AlignTop | Qt::AlignHCenter);
	layout->addStretch();
	layout->addWidget(m_Exit, 0, Qt::AlignTop | Qt::AlignHCenter);

    setLayout(layout);
}



