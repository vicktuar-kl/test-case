#pragma once

#include <QtSql>
#include "item.h"
#include "inventorycell.h"

// ============================================================================
// Класс-обертка для создания запросов к БД

class Database {
public:
	Database();
	static Item* itemSelect(QString itemType);
	static bool inventoryInsert(int row, int col, /*QString itemType,*/ int number);
	static InventoryCell* inventorySelect(int row, int col);
	static bool clearInventoryTable();
	static int countRecordsTable(QString tableName);

private:
	QSqlDatabase m_DB;
};
