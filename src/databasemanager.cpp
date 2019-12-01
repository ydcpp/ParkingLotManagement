#include "databasemanager.hpp"


DatabaseManager::DatabaseManager(QString& dbpath)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(dbpath);
    database.open();
}


DatabaseManager::~DatabaseManager()
{
    if(database.isOpen()) database.close();
}

bool DatabaseManager::isConnected()
{
    return database.isOpen();
}
