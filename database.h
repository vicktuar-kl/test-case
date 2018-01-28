#pragma once

#include <QObject>
#include <QtSql>

typedef unsigned int uint;
// не позорься! замени на QStringList
typedef QList<QString> strList;

class DataBase : public QObject {
    Q_OBJECT
private:
	QString m_dbName;
	QSqlDatabase m_db;
	QString m_tableName;
	strList m_tableFields;

	bool createConnection();
	bool createTable();

public:
	DataBase(QString tableName, strList tableFields, QString dbName = "Database", QObject *parent = nullptr);
	~DataBase();

	bool insert(strList values);

signals:

public slots:
};
