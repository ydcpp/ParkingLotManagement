#ifndef MANUALVEHICLEEXIT_HPP
#define MANUALVEHICLEEXIT_HPP

#include <QDialog>
#include <QDateTime>

class DatabaseManager;

namespace Ui {
class ManualVehicleExit;
}

class ManualVehicleExit : public QDialog
{
    Q_OBJECT

public:
    explicit ManualVehicleExit(DatabaseManager* dbmanager, QWidget *parent);
    ~ManualVehicleExit();

signals:
    void getCalculatedPrice(const qint64& minutes, const qint32& planid, float& out_price, QString& out_planName);
    void increaseCount();

private slots:
    void on_pushButton_query_clicked();

    void on_pushButton_completePayment_clicked();

private:
    Ui::ManualVehicleExit *ui;
    DatabaseManager* m_dbmanager;

    QString m_plate;
    QString m_color;
    QString m_type;
    QString m_model;
    qint32 m_vehicleID;
    qint32 m_paymentID;
    qint64 m_minutes;
    QDateTime m_entryDate;
    QString m_planName;
    float m_price;

    bool validateForm();
    void clearResults();
};

#endif // MANUALVEHICLEEXIT_HPP
