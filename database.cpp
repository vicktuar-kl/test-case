#include "inventorycell.h"
#include "database.h"

// открытие базы данных
Database::Database() {
	m_DB = QSqlDatabase::addDatabase("QSQLITE");
	m_DB.setDatabaseName("database.db");
	m_DB.open();
}

// запрос на получение инфомрации о предмете itemType
// (пути к звуковому файлу и изображению)
Item* Database::itemSelect(const QString& itemType) {
	QSqlQuery query("SELECT icon_path, sound_path FROM item WHERE type = '" + itemType + "';");
	QString iconPath, soundPath;
	while (query.next()) {
		iconPath = query.value(0).toString();
		soundPath = query.value(1).toString();
	}
	return new Item(itemType, iconPath, soundPath);
}

// вставка в таблицу inventory текущего содержимого инвентаря
// (в какой ячейке, что и сколько)
bool Database::inventoryInsert(int row, int col, const QString& itemType, int number) {
	QSqlQuery query;
	QString strF = "INSERT INTO inventory (row, col, item_type, item_number)"
				   "VALUES (%1, %2, '%3', '%4');";
	QString str = strF.arg(row).arg(col).arg(itemType).arg(number);

	return query.exec(str);
}

// запрос содержимого конкретной ячейки из БД
// если такой ячейки в БД нет, то создаём пустую ячейку инвентаря
InventoryCell* Database::inventorySelect(int row, int col) {
	QSqlQuery query;
	QString itemType = "";
	int itemNumber = 0;
	QString str = "SELECT item_type, item_number FROM inventory WHERE row = %1 AND col = %2;";
	str = str.arg(row).arg(col);
	query.exec(str);
	while (query.next()) {
		itemType = query.value(0).toString();
		itemNumber = query.value(1).toInt();
	}
	if (itemNumber != 0) {
		Item* temp = itemSelect(itemType);
		return new InventoryCell(row, col, itemNumber, temp);
	} else {
		return new InventoryCell(row, col);
	}
}

// очистка таблицы inventory
bool Database::clearInventoryTable() {
	QSqlQuery query;
	return query.exec("DELETE FROM inventory;");
}

// количество записей в таблице tableName
int Database::countRecordsTable(const QString& tableName) {
	QSqlQuery query;
	QString str = "SELECT COUNT(*) FROM %1;";
	str = str.arg(tableName);
	int count = 0;
	query.exec(str);
	while (query.next())
		count = query.value(0).toInt();
	return count;
}

