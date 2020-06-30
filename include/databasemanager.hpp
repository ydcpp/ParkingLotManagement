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

    [[nodiscard]] bool ValidateUserLogin(const QString& username, const QString& password, QString& errormsg, User** currentUser);
    [[nodiscard]] bool DeleteUser(const QString& username, QString& errmsg);
    [[nodiscard]] bool CreateUser(const QString& firstname, const QString& lastname, const QString& phone, const QString& username, const QString& password, const qint32& usertype, QString& errmsg);
    [[nodiscard]] bool NewVehicleEntry(const QString& plate, QString& errmsg, qint32& vehicleID, const QString& model="", const QString& type="", const QString& color="");
    [[nodiscard]] bool NewPaymentEntry(const qint32& vehicleID, const qint32& planID, QString& errmsg);
    [[nodiscard]] bool GetBillingResult(const QString& plate, QString& errmsg, qint32& out_paymentID, qint64& out_minutes, qint32& out_vehicleID, QDateTime& out_entryDate, qint32& out_planID);
    [[nodiscard]] bool CompletePayment(const qint32& vehicleID, const QDateTime& exitDate, const qint64& minutes, const float& price, QString& errmsg, QString payerName = "");
    [[nodiscard]] bool GetVehicleInformation(const qint32& vehicleID, QString& errmsg, QString& out_plate, QString& out_color, QString& out_type, QString& out_model);
    [[nodiscard]] bool GetPricingPlans(QVector<PricingPlan*>& out_plans, QString& errmsg);
    [[nodiscard]] bool CreateNewPricingPlan(const QString& name,const float& priceperhour,const float& lessthantwo, const float& twothree, const float& threefour, const float& fourfive, const float& fivesix, const float& sixseven, const float& seveneight, const float& eightten, const float& tentwelve, const float& morethantwelve, QVector<PricingPlan*>& out_plans, QString& errmsg);
    [[nodiscard]] bool DeletePricingPlan(const qint32& planID, QVector<PricingPlan*>& out_plans, QString& errmsg);
    [[nodiscard]] bool UpdatePricingPlan(const qint32& planID,const float& lessthantwo, const float& twothree, const float& threefour, const float& fourfive, const float& fivesix, const float& sixseven, const float& seveneight, const float& eightten, const float& tentwelve, const float& morethantwelve, QVector<PricingPlan*>& out_plans, QString& errmsg);
    [[nodiscard]] bool SetQueryModel_Employees(QSqlQueryModel* out_model, QString& errmsg);
    [[nodiscard]] bool SetQueryModel_Managers(QSqlQueryModel* out_model, QString& errmsg);
    [[nodiscard]] bool SetQUeryModel_Payments(QSqlQueryModel* out_model, QString& errmsg);
    [[nodiscard]] bool QueryMonthlyIncome(float& out_income, QString& errmsg);
    [[nodiscard]] bool QueryWeeklyIncome(float& out_income, QString& errmsg);
    [[nodiscard]] bool QueryDailyIncome(float& out_income, QString& errmsg);
    [[nodiscard]] bool SetQueryModel_TotalPaymentInfo(const qint32& vehicleID, QSqlQueryModel* out_model, QString& errmsg);
    [[nodiscard]] bool SetQueryModel_ListAllVehiclesInside(QSqlQueryModel* out_model, QString& errmsg);
    [[nodiscard]] bool GetVehicleInformationByPlate(const QString& plate, qint32& out_vehicleID, QString& out_color, QString& out_type, QString& out_model, QString& errmsg);
    [[nodiscard]] bool GetAllVehiclesInside();
    [[nodiscard]] bool ChangePassword(const qint32& accountID, const QString& oldPassword, const QString& newPassword, QString& errmsg);
    [[nodiscard]] qint32 QueryRemainingSpots(QString& errmsg);
    [[nodiscard]] bool SetRemainingSpotCount(const qint32& value, QString& out_errmsg);
    [[nodiscard]] bool isConnected();
    [[nodiscard]] bool SetOtoparkInfo(OtoparkInfo** out_otoparkInfo);
    [[nodiscard]] bool UpdateCurrentPricingPlan(const qint32& planid, QString& errmsg);
    [[nodiscard]] QMap<QString,qint32> getColors();
    [[nodiscard]] QMap<QString,qint32> getVehicleTypes();

    bool IncreaseRemainingSpot();
    bool DecreaseRemainingSpot();
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
