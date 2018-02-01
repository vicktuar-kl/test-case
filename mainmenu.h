#pragma once

#include <QtWidgets>

// ============================================================================
// Класс для главного меню, появляется первым, до нажатия кнопки новой игры
// все остальные виджеты блокированы

class MainMenu : public QWidget {
    Q_OBJECT
private:
	QPushButton* m_NewGame;		// Кнопка новой игры
	QPushButton* m_Exit;		// Кнопка выхода

	void createFormInterior();	// Компоновка кнопок

public:
	explicit MainMenu(QWidget* parent = nullptr);	// создание виджета и связывание сигналов кнопок со слотами
};
