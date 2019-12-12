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
#include <QDateTime>
#include <QList>

#include "User.hpp"


class DatabaseManager
{
public:
    DatabaseManager(QString dbpath);
    ~DatabaseManager();

    bool validateUserLogin(QString username, QString password, QString& errormsg, User** currentUser);
    bool deleteUser(QString username, QString& errmsg);
    bool createUser(QString firstname, QString lastname, QString phone, QString username, QString password, qint32 usertype, QString& errmsg);
    bool newVehicleEntry(QString plate, QString model, QString type, QString color, QString& errmsg, qint32& vehicleID);
    bool newPaymentEntry(qint32 vehicleID, bool isNightPlan, QString& errmsg);
    bool getBillingResult(QString plate, QString& errmsg, qint32& out_paymentID, qint64& out_minutes, qint32& out_vehicleID, QDateTime& out_entryDate);
    bool completePayment(qint32 vehicleID, QDateTime exitDate, float price, QString& errmsg, QString payerName = "");
    bool getVehicleInformation(qint32 vehicleID, QString& errmsg, QString& out_plate, QString& out_color, QString& out_type, QString& out_model);

    bool isConnected();

    QMap<QString,qint32> getColors();
    QMap<QString,qint32> getVehicleTypes();

private:
    QSqlDatabase database;
    QMap<QString,qint32> m_colors;
    QMap<QString,qint32> m_vehicleTypes;

    void getColorsFromDB();
    void getVehicleTypesFromDB();
};

#endif // DATABASEMANAGER_HPP
