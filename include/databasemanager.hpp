#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>


class DatabaseManager
{
public:
    DatabaseManager(QString& dbpath);
    ~DatabaseManager();

    bool isConnected();

private:
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_HPP
