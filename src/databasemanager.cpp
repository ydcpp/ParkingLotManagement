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

bool DatabaseManager::deleteUser(QString username, QString& errmsg)
{
    if(!database.open()) return false;
    QSqlQuery query;
    query.prepare("select * from Accounts where Username = :usr");
    query.bindValue(":usr",username);
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    if(!query.next()){
        errmsg = "Böyle bir kullanıcı adı bulunmamaktadır.";
        return false;
    }else{
        query.clear();
        query.prepare("delete from Accounts where Username = :usr");
        query.bindValue(":usr",username);
        if(!query.exec()){
            errmsg = query.lastError().text();
            return false;
        }
        return true;
    }
}

bool DatabaseManager::createUser(QString firstname, QString lastname, QString phone, QString username, QString password, qint32 usertype, QString &errmsg)
{
    QSqlQuery query;
    query.prepare("insert into Person (FirstName,LastName) values(:fn,:ln)");
    query.bindValue(":fn",firstname);
    query.bindValue(":ln",lastname);
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    query.clear();
    query.exec("SELECT last_insert_rowid()");
    query.next();
    qint32 userID = query.value(0).toInt();
    query.clear();
    query.prepare("insert into Phones (PhoneNumber,fk_PersonID) values (:phone,:userID)");
    query.bindValue(":phone",phone);
    query.bindValue(":userID",userID);
    if(!query.exec()){
        errmsg = query.lastError().text();
        query.prepare("delete from Person where ID = :id");
        query.bindValue(":id",userID);
        query.exec();
        return false;
    }
    query.clear();
    query.prepare("insert into Accounts (Username,Password,AccountType,fk_PersonID) values (:usr,:pw,:type,:pid)");
    query.bindValue(":usr",username);
    query.bindValue(":pw",password);
    query.bindValue(":type",usertype);
    query.bindValue(":pid",userID);
    if(!query.exec()){
        query.prepare("delete from Person where ID = :id");
        query.bindValue(":id",userID);
        query.exec();
        return false;
    }
    return true;
}

bool DatabaseManager::isConnected()
{
    return database.isOpen();
}





