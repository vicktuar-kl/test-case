#pragma once

#include <QtSql>
#include "item.h"
#include "inventorycell.h"

// ============================================================================
// Класс-обертка для создания запросов к БД

class Database {
public:
	Database();
	static Item* itemSelect(const QString& itemType);		// запрос на получение инфомрации о предмете itemType
	// вставка в таблицу inventory текущего содержимого инвентаря
	static bool inventoryInsert(int row, int col, const QString& itemType, int number);
	static InventoryCell* inventorySelect(int row, int col);	// запрос содержимого конкретной ячейки из БД
	static bool clearInventoryTable();							// очистка таблицы inventory
	static int countRecordsTable(const QString& tableName);		// количество записей в таблице tableName

private:
	QSqlDatabase m_DB;
};
