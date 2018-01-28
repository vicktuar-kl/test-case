#include <QDebug>
#include <QFile>
#include "database.h"

DataBase::DataBase(QString tableName, strList tableFields, QString dbName/* = "Database"*/, QObject *parent/* = nullptr*/)
	: m_dbName(dbName), m_tableName(tableName), m_tableFields(tableFields), QObject(parent) {
	createConnection();
	createTable();
}

DataBase::~DataBase() { }

bool DataBase::createConnection() {
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName(m_dbName);
	m_db.setUserName("kluev");
	m_db.setHostName("localhost");
	m_db.setPassword("Zz123456");

	if (!m_db.open ()) {
		qDebug() << "Cannot open database: " << m_db.lastError();
		return false;
	}
	return true;
}

bool DataBase::createTable() {
//	QString str = "CREATE TABLE " + m_tableName + " (";
//	uint i = 0;
//	for (; i < m_tableFields.size() - 1; ++i) {
//		str += m_tableFields.at(i) + " VARCHAR(20), ";
//	}
//	str += m_tableFields.at(i) + " VARCHAR(20));";

	QString str = "CREATE TABLE test ("
				 // "number INTEGER PRIMARY KEY NOT NULL, "
				  "test_field VARCHAR(20)"
				  ");";

	QSqlQuery query(m_db);
	if (!query.exec(str)) {
		qDebug() << "Unable to create a table";
		qDebug() << str;
		return false;
	}
	return true;
}

bool DataBase::insert(strList values) {
	QString strF = "INSERT INTO " + m_tableName + " ( ";
	foreach (auto field, m_tableFields) {
		strF += field + ", ";
	}
	strF += " ) VALUES ( ";
	for (uint i = 1; i <= m_tableFields.size(); ++i) {
		strF += "'%" + QString::number(i) + "',";
	}
	strF += " );";

	QString str;
	foreach (auto value, values) {
		str = strF.arg(value);
	}

	qDebug() << str;
	return true;
}
