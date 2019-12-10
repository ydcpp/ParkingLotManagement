#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlQueryModel>
#include <QString>

#include "User.hpp"


class DatabaseManager
{
public:
    DatabaseManager(QString dbpath);
    ~DatabaseManager();

    bool validateUserLogin(QString username, QString password, QString& errormsg, User** currentUser);
    bool deleteUser(QString username, QString& errmsg);
    bool createUser(QString firstname, QString lastname, QString phone, QString username, QString password, qint32 usertype, QString& errmsg);

    bool isConnected();

private:
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_HPP
