#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QObject>
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
#include <QVector>

#include "User.hpp"
#include "pricingplan.hpp"
#include "OtoparkInfo.hpp"

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    DatabaseManager();
    ~DatabaseManager();

    bool ValidateUserLogin(const QString& username, const QString& password, QString& errormsg, User** currentUser);
    bool DeleteUser(const QString& username, QString& errmsg);
    bool CreateUser(const QString& firstname, const QString& lastname, const QString& phone, const QString& username, const QString& password, const qint32& usertype, QString& errmsg);
    bool NewVehicleEntry(const QString& plate, QString& errmsg, qint32& vehicleID, const QString& model="", const QString& type="", const QString& color="");
    bool NewPaymentEntry(const qint32& vehicleID, const qint32& planID, QString& errmsg);
    bool GetBillingResult(const QString& plate, QString& errmsg, qint32& out_paymentID, qint64& out_minutes, qint32& out_vehicleID, QDateTime& out_entryDate, qint32& out_planID);
    bool CompletePayment(const qint32& vehicleID, const QDateTime& exitDate, const qint64& minutes, const float& price, QString& errmsg, QString payerName = "");
    bool GetVehicleInformation(const qint32& vehicleID, QString& errmsg, QString& out_plate, QString& out_color, QString& out_type, QString& out_model);
    bool GetPricingPlans(QVector<PricingPlan*>& out_plans, QString& errmsg);
    bool CreateNewPricingPlan(const QString& name,const float& priceperhour,const float& lessthantwo, const float& twothree, const float& threefour, const float& fourfive, const float& fivesix, const float& sixseven, const float& seveneight, const float& eightten, const float& tentwelve, const float& morethantwelve, QVector<PricingPlan*>& out_plans, QString& errmsg);
    bool DeletePricingPlan(const qint32& planID, QVector<PricingPlan*>& out_plans, QString& errmsg);
    bool UpdatePricingPlan(const qint32& planID,const float& lessthantwo, const float& twothree, const float& threefour, const float& fourfive, const float& fivesix, const float& sixseven, const float& seveneight, const float& eightten, const float& tentwelve, const float& morethantwelve, QVector<PricingPlan*>& out_plans, QString& errmsg);
    bool SetQueryModel_Employees(QSqlQueryModel* out_model, QString& errmsg);
    bool SetQueryModel_Managers(QSqlQueryModel* out_model, QString& errmsg);
    bool SetQUeryModel_Payments(QSqlQueryModel* out_model, QString& errmsg);
    bool QueryMonthlyIncome(float& out_income, QString& errmsg);
    bool QueryWeeklyIncome(float& out_income, QString& errmsg);
    bool QueryDailyIncome(float& out_income, QString& errmsg);
    bool SetQueryModel_TotalPaymentInfo(const qint32& vehicleID, QSqlQueryModel* out_model, QString& errmsg);
    bool SetQueryModel_ListAllVehiclesInside(QSqlQueryModel* out_model, QString& errmsg);
    bool GetVehicleInformationByPlate(const QString& plate, qint32& out_vehicleID, QString& out_color, QString& out_type, QString& out_model, QString& errmsg);
    bool GetAllVehiclesInside();
    bool ChangePassword(const qint32& accountID, const QString& oldPassword, const QString& newPassword, QString& errmsg);
    qint32 QueryRemainingSpots(QString& errmsg);
    bool SetRemainingSpotCount(const qint32& value, QString& out_errmsg);
    bool IncreaseRemainingSpot();
    bool DecreaseRemainingSpot();
    bool isConnected();
    bool SetOtoparkInfo(OtoparkInfo** out_otoparkInfo);
    bool UpdateCurrentPricingPlan(const qint32& planid, QString& errmsg);

    QMap<QString,qint32> getColors();
    QMap<QString,qint32> getVehicleTypes();
    void CreateDatabaseBackup();

signals:
    void sig_RemainingSpotIncreased();
    void sig_RemainingSpotDecreased();

private:
    QSqlDatabase database;
    QMap<QString,qint32> m_colors;
    QMap<QString,qint32> m_vehicleTypes;
    QFile m_file;
    const QString m_dbfilepath {"./assets/db/current/"};
    const QString m_dbbackuppath {"./assets/db/backups/"};
    const QString m_dbfilename {"parkyerimdb.sqlite"};
    const QString m_dbfile = m_dbfilepath + m_dbfilename;
    const QString m_dbResourcePath {":/Database/assets/database/parkyerimdb.sqlite"};
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
