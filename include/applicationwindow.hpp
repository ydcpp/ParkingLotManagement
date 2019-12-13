#ifndef APPLICATIONWINDOW_HPP
#define APPLICATIONWINDOW_HPP

#include "adminpanel.hpp"
#include "manualvehicleentry.hpp"
#include "manualvehicleexit.hpp"
#include "settingspanel.hpp"

#include <QWidget>
#include <QMap>

class ParkYerim;
class DatabaseManager;
class User;
class PricingPlan;

namespace Ui {
class ApplicationWindow;
}

class ApplicationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationWindow(DatabaseManager* dbmanager, User* user, QWidget *parent = nullptr);
    ~ApplicationWindow();

    void ClearVehicleInStats();
    void ClearVehicleOutStats();
    QMap<QString, QString> GetAssetPaths();
    DatabaseManager* GetDBManager();

    QList<PricingPlan*> GetPricingPlanList();

public slots:
    float calculatePrice(qint64 minutes, bool isNight, QString& currentplan);

private slots:
    void on_toolButton_quit_clicked();
    void showTime();

    void on_toolButton_vehicle_in_clicked();

    void on_toolButton_vehicle_out_clicked();

    void on_toolButton_adminpanel_clicked();

    void on_toolButton_settings_clicked();

signals:
    float getPricePlanCalculation(qint64 minutes, bool isNight);

private:
    Ui::ApplicationWindow *ui;
    ParkYerim* m_parent = nullptr;
    DatabaseManager* m_dbmanager = nullptr;
    User* m_user = nullptr;
    AdminPanel* m_window_admin = nullptr;
    ManualVehicleEntry* m_window_vehicle_in = nullptr;
    ManualVehicleExit* m_window_vehicle_out = nullptr;
    SettingsPanel* m_window_settings = nullptr;
    QList<PricingPlan*> m_pricingPlans;
    qint32 m_currentPlanID = 0;
    PricingPlan* currentPricingPlan = nullptr;
    bool m_isNight = false;

    void initializeAssetPaths();
    void setupIcons();
    void setupCustomComponents();


    QMap<QString, QString> m_assetPaths;

    // programda kullanılacak tüm asset'lerin adları ve dosya yolları burada girilmelidir.
    QList<QString> m_params = {
        "icon_close,        ./assets/images/close.png",
        "icon_print,        ./assets/images/settings.png",
        "image_background,  ./assets/images/background.jpg",
        "icon_settings,     ./assets/images/settings.png",
        "icon_adminpanel,   ./assets/images/adminpanel.png",
        "icon_vehicle_in,   ./assets/images/add_vehicle.png",
        "icon_vehicle_out,  ./assets/images/remove_vehicle.png"
    };
};

#endif // APPLICATIONWINDOW_HPP
