#include "databasemanager.hpp"


DatabaseManager::DatabaseManager(QString dbpath)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(dbpath);
    database.open();
}


DatabaseManager::~DatabaseManager()
{
    if(database.isOpen()) database.close();
}

bool DatabaseManager::validateUserLogin(QString username, QString password, QString& errormsg, User** currentUser)
{
    if(!isConnected()) return false;
    else{
        QSqlQuery query;
        query.prepare("SELECT * FROM Accounts WHERE Username == :usr");
        query.bindValue(":usr",username);
        // 1
        if(!query.exec()){
            errormsg = "1: " + query.lastError().text();
            return false;
        }
        if(!query.next()){
            errormsg = "Hatalı kullanıcı adı.";
            return false;
        }else{
            query.clear();
            query.prepare("SELECT Password FROM Accounts WHERE Username == :usr");
            query.bindValue(":usr",username);
            //2
            if(!query.exec()){
                errormsg = "2: " + query.lastError().text();
                return false;
            }
            query.next();
            if(password != query.value(0).toString()){
                errormsg = "Hatalı şifre.";
                return false;
            }else{
                QString firstname;
                QString lastname;
                qint32 accountID;
                qint32 accType;
                query.clear();
                query.prepare("SELECT Person.FirstName, Person.LastName, Accounts.ID, Accounts.AccountType FROM Person"
                              " LEFT JOIN Accounts ON Person.ID = Accounts.fk_PersonID"
                              " WHERE Accounts.Username = :usr");
                query.bindValue(":usr",username);
                // 3
                if(!query.exec()){
                    errormsg = "3: " + query.lastError().text();
                    return false;
                }
                query.next();
                firstname = query.value(0).toString();
                lastname = query.value(1).toString();
                accountID = query.value(2).toInt();
                accType = query.value(3).toInt();
                *currentUser = new User(username,firstname,lastname,accountID,accType);
                return true;
            }
        }
    }
}

bool DatabaseManager::isConnected()
{
    return database.isOpen();
}
