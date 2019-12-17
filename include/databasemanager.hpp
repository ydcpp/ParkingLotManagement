#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QFileDevice>
#include <QDir>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QString>
#include <QDateTime>
#include <QList>

#include "User.hpp"
#include "pricingplan.hpp"


class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    bool ValidateUserLogin(QString username, QString password, QString& errormsg, User** currentUser);
    bool DeleteUser(QString username, QString& errmsg);
    bool CreateUser(QString firstname, QString lastname, QString phone, QString username, QString password, qint32 usertype, QString& errmsg);
    bool NewVehicleEntry(QString plate, QString model, QString type, QString color, QString& errmsg, qint32& vehicleID);
    bool NewPaymentEntry(qint32 vehicleID, QString& errmsg);
    bool GetBillingResult(QString plate, QString& errmsg, qint32& out_paymentID, qint64& out_minutes, qint32& out_vehicleID, QDateTime& out_entryDate);
    bool CompletePayment(qint32 vehicleID, QDateTime exitDate, qint64 minutes, float price, QString& errmsg, QString payerName = "");
    bool GetVehicleInformation(qint32 vehicleID, QString& errmsg, QString& out_plate, QString& out_color, QString& out_type, QString& out_model);
    bool GetPricingPlans(QList<PricingPlan*>& out_plans, QString& errmsg);
    bool CreateNewPricingPlan(QString name,float priceperhour,float lessthantwo, float twothree, float threefour, float fourfive, float fivesix, float sixseven, float seveneight, float eightten, float tentwelve, float morethantwelve, QList<PricingPlan*>& out_plans, QString& errmsg);
    bool DeletePricingPlan(qint32 planID, QList<PricingPlan*>& out_plans, QString& errmsg);
    bool UpdatePricingPlan(qint32 planID,float lessthantwo, float twothree, float threefour, float fourfive, float fivesix, float sixseven, float seveneight, float eightten, float tentwelve, float morethantwelve, QList<PricingPlan*>& out_plans, QString& errmsg);
    bool SetQueryModel_Employees(QSqlQueryModel* out_model, QString& errmsg);
    bool SetQueryModel_Managers(QSqlQueryModel* out_model, QString& errmsg);
    bool SetQUeryModel_Payments(QSqlQueryModel* out_model, QString& errmsg);
    bool QueryMonthlyIncome(float& out_income, QString& errmsg);
    bool QueryWeeklyIncome(float& out_income, QString& errmsg);
    bool QueryDailyIncome(float& out_income, QString& errmsg);
    bool SetQueryModel_TotalPaymentInfo(qint32 vehicleID, QSqlQueryModel* out_model, QString& errmsg);
    bool GetVehicleInformationByPlate(QString plate, qint32& out_vehicleID, QString& out_color, QString& out_type, QString& out_model, QString& errmsg);
    bool ChangePassword(qint32 accountID, QString oldPassword, QString newPassword, QString& errmsg);

    bool isConnected();

    QMap<QString,qint32> getColors();
    QMap<QString,qint32> getVehicleTypes();
    void CreateDatabaseBackup();

private:
    QSqlDatabase database;
    QMap<QString,qint32> m_colors;
    QMap<QString,qint32> m_vehicleTypes;
    QFile m_file;
    const QString m_dbfilepath = "./assets/db/current/";
    const QString m_dbbackuppath = "./assets/db/backups/";
    const QString m_dbfilename = "parkyerimdb.sqlite";
    const QString m_dbfile = m_dbfilepath + m_dbfilename;
    const QString m_dbResourcePath = ":/Database/Current/assets/database/parkyerimdb.sqlite";
    QString m_backupDBresourcepath;

    void getColorsFromDB();
    void getVehicleTypesFromDB();

    struct PaymentInfo{
        QDateTime date;
        float price;
        PaymentInfo(QDateTime d, float p){
            date = d;
            price = p;
        }
    };
};

#endif // DATABASEMANAGER_HPP
