#pragma once

#include <QtWidgets>

class MainMenu : public QWidget {
    Q_OBJECT
private:
	QPushButton* m_NewGame;
	QPushButton* m_Quit;

    void createFormInterior();

public:
	explicit MainMenu(QWidget* parent = nullptr);

signals:

public slots:
};
