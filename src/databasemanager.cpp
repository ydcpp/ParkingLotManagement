#include "databasemanager.hpp"

DatabaseManager::DatabaseManager(QString dbpath)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(dbpath);
    database.open();
    getColorsFromDB();
    getVehicleTypesFromDB();
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

bool DatabaseManager::newVehicleEntry(QString plate, QString model, QString type, QString color, QString &errmsg, qint32 &vehicleID)
{
    QSqlQuery query;
    // check if vehicle already exists
    query.prepare("select ID from Vehicles where Plate = :plate");
    query.bindValue(":plate",plate);
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    if(query.next()){
        vehicleID = query.value(0).toInt();
        return true;
    }else{
        // create new vehicle entry
        query.clear();
        query.prepare("insert into Vehicles(Plate,Model,fk_colorID,fk_vehicleTypeID) values(:pl,:model,:colorid,:typeid)");
        query.bindValue(":pl",plate);
        query.bindValue(":model",model);
        query.bindValue(":colorid",m_colors[color]);
        query.bindValue(":typeid",m_vehicleTypes[type]);
        if(!query.exec()){
            errmsg = query.lastError().text();
            return false;
        }
        query.clear();
        query.exec("SELECT last_insert_rowid()");
        query.next();
        vehicleID = query.value(0).toInt();
        return true;
    }
}

bool DatabaseManager::newPaymentEntry(qint32 vehicleID, bool isNightPlan, QString& errmsg)
{
    QSqlQuery query;
    query.prepare("insert into Payments(fk_VehicleID,isNightPlan) values(:vid,:night)");
    query.bindValue(":vid",vehicleID);
    query.bindValue(":night",isNightPlan);
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::getBillingResult(QString plate, QString& errmsg, qint32& out_paymentID, qint64& out_minutes, qint32& out_vehicleID, QDateTime& out_entryDate)
{
    QSqlQuery query;
    qint32 vehicleID;
    query.prepare("select ID from Vehicles where Plate = :plate");
    query.bindValue(":plate",plate);
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    if(!query.next()){
        errmsg = "Bu plakalı araç sistemde bulunmamaktadır.";
        return false;
    }
    vehicleID = query.value(0).toInt();
    out_vehicleID = vehicleID;
    QDateTime entryDate;
    query.clear();
    query.prepare("select ID, VehicleEntryDate from Payments where fk_VehicleID = :vid and isPaymentComplete = false");
    query.bindValue(":vid",vehicleID);
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    if(!query.next()){
        errmsg = "Bu plakalı aracın ödenmemiş kaydı bulunmamaktadır.";
        return false;
    }else{
        out_paymentID = query.value(0).toInt();
        entryDate = query.value(1).toDateTime();
        out_entryDate = entryDate;
        out_minutes = entryDate.secsTo(QDateTime::currentDateTime())/60;
        return true;
    }
}

bool DatabaseManager::completePayment(qint32 vehicleID, QDateTime exitDate, float price, QString &errmsg, QString payerName)
{
    qint32 paymentID;
    QSqlQuery query;
    query.prepare("select Payments.ID from Payments left join Vehicles on Payments.fk_VehicleID = Vehicles.ID where Vehicles.ID = :vid and Payments.isPaymentComplete = false");
    query.bindValue(":vid",vehicleID);
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    if(!query.next()){
        errmsg = "Bu araca ait bir ücret kaydı bilgisi bulunamadı.";
        return false;
    }
    paymentID = query.value(0).toInt();
    query.clear();
    query.prepare("update Payments set PayerName = :payer, Price = :price, PaymentDate = :date, isPaymentComplete = true where ID = :pid");
    query.bindValue(":pid",paymentID);
    query.bindValue(":payer",payerName);
    query.bindValue(":price",price);
    query.bindValue(":date",exitDate.toString("yyyy-MM-dd HH:mm:ss"));
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::getVehicleInformation(qint32 vehicleID, QString& errmsg, QString& out_plate, QString& out_color, QString& out_type, QString& out_model)
{
    QSqlQuery query;
    query.prepare("select Plate, fk_colorID, fk_vehicleTypeID, Model from Vehicles where ID = :id");
    query.bindValue(":id",vehicleID);
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    if(!query.next()){
        errmsg = "Invalid vehicle ID";
        return false;
    }
    qint32 colorID;
    qint32 typeID;
    out_plate = query.value(0).toString();
    colorID = query.value(1).toInt();
    typeID = query.value(2).toInt();
    out_model = query.value(3).toString();
    query.clear();
    query.prepare("select Color from Colors where ID = :id");
    query.bindValue(":id",colorID);
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    query.next();
    out_color = query.value(0).toString();
    query.clear();
    query.prepare("select TypeName from VehicleTypes where ID = :id");
    query.bindValue(":id",typeID);
    if(!query.exec()){
        errmsg = query.lastError().text();
        return false;
    }
    query.next();
    out_type = query.value(0).toString();
    return true;
}


bool DatabaseManager::isConnected()
{
    return database.isOpen();
}

QMap<QString,qint32> DatabaseManager::getColors()
{
    return m_colors;
}

QMap<QString,qint32> DatabaseManager::getVehicleTypes()
{
    return m_vehicleTypes;
}

void DatabaseManager::getColorsFromDB()
{
    QSqlQuery query;
    query.exec("select * from Colors where id != 0");
    while(query.next()){
        qint32 colorID = query.value(0).toInt();
        QString color = query.value(1).toString();
        m_colors[color] = colorID;
    }
}

void DatabaseManager::getVehicleTypesFromDB()
{
    QSqlQuery query;
    query.exec("select * from VehicleTypes where id != 0");
    while(query.next()){
        qint32 typeID = query.value(0).toInt();
        QString type = query.value(1).toString();
        m_vehicleTypes[type] = typeID;
    }
}





