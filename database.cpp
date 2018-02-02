#include "inventorycell.h"
#include "database.h"

Database::Database() {
	m_DB = QSqlDatabase::addDatabase("QSQLITE");
	m_DB.setDatabaseName("data/database");
	m_DB.open();
}

Item* Database::itemSelect(QString itemType) {
	QSqlQuery query("SELECT icon_path, sound_path FROM item WHERE type = '" + itemType + "';");
	QString iconPath, soundPath;
	while (query.next()) {
		iconPath = query.value(0).toString();
		soundPath = query.value(1).toString();
	}
	return new Item(itemType, iconPath, soundPath);
}

bool Database::inventoryInsert(int row, int col, /*QString itemType,*/ int number) {
	QSqlQuery query;
	QString strF = "INSERT INTO inventory (row, col, item_type, item_number)"
				   "VALUES (%1, %2, 'apple', '%4');";
	QString str = strF.arg(row).arg(col).arg(number);

	return query.exec(str);
}

InventoryCell* Database::inventorySelect(int row, int col) {
	QSqlQuery query;
	QString itemType;
	int itemNumber;
	QString str = "SELECT item_type, item_number FROM inventory WHERE row = %1 AND col = %2;";
	str = str.arg(row).arg(col);
	if (query.exec(str)) {
		while (query.next()) {
			itemType = query.value(0).toString();
			itemNumber = query.value(1).toInt();
		}
		Item* temp = itemSelect(itemType);
		return new InventoryCell(row, col, itemNumber, temp);
	} else {
		return new InventoryCell(row, col);
	}
}

bool Database::clearInventoryTable() {
	QSqlQuery query;
	return query.exec("DELETE FROM inventory;");
}

int Database::countRecordsTable(QString tableName) {
	QSqlQuery query;
	QString str = "SELECT COUNT(*) FROM %1;";
	str = str.arg(tableName);
	int count = 0;
	query.exec(str);
	while (query.next())
		count = query.value(0).toInt();
	return count;
}

