#ifndef APPLICATIONWINDOW_HPP
#define APPLICATIONWINDOW_HPP

#include "adminpanel.hpp"
#include "manualvehicleentry.hpp"
#include "manualvehicleexit.hpp"
#include "settingspanel.hpp"
#include "currentplanwindow.hpp"
#include "vehiclesearch.hpp"
#include "ThreadManager.hpp"
#include "TCPClient.hpp"

#include <QMainWindow>
#include <QMap>
#include <QString>

class ParkYerim;
class DatabaseManager;
class User;
class PricingPlan;
class Logger;


namespace Ui {
class ApplicationWindow;
}

class ApplicationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ApplicationWindow(DatabaseManager* dbmanager, User* user, Logger* logger, QWidget *parent = nullptr);
    ~ApplicationWindow();

    void ClearVehicleInStats();
    void ClearVehicleOutStats();
    QMap<QString, QString> GetAssetPaths();
    DatabaseManager* GetDBManager();
    User* GetCurrentUser();
    QList<PricingPlan*>& GetPricingPlanList();
    void updateCurrentPlan(qint32 planID);
    qint32 getCurrentPlanID() const;

signals:
    float getPricePlanCalculation(qint64 minutes);
    void terminateAllThreads();
    void stopAllThreads();
    void recognizePlate_in();
    void recognizePlate_out();

public slots:
    void openCameraStream_in();
    void closeCameraStream_in();
    void openCameraStream_out();
    void closeCameraStream_out();
    void drawCamInput_vehicle_in(QPixmap);
    void drawCamInput_vehicle_out(QPixmap);
    void displayLicensePlateString_vehicle_in(QString);
    void displayLicensePlateString_vehicle_out(QString);


private slots:
    void on_toolButton_quit_clicked();
    void showTime();
    void enableToggleCameraButton();
    void updateRemainingSpots(qint32);
    void increaseRemainingSpotCount();
    void decreaseRemainingSpotCount();
    void on_socketStateChanged(QAbstractSocket::SocketState socketState);
    void onTCPErrorReceived(const QString& err);
    void onPricingPlansUpdated();
    void getCalculatedPrice(const qint64& minutes, const qint32& planid, float& out_price, QString& out_planName);

    void on_toolButton_vehicle_in_clicked();

    void on_toolButton_vehicle_out_clicked();

    void on_toolButton_adminpanel_clicked();

    void on_toolButton_settings_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_currentPlanDetails_clicked();

    void on_pushButton_parkingSpots_clicked();

    void on_pushButton_toggleCameras_clicked();

    void on_pushButton_plakatani_in_clicked();

    void on_pushButton_plakatani_out_clicked();

    void on_pushButton_reconnect_clicked();


private:
    Ui::ApplicationWindow *ui;
    ParkYerim* m_parent = nullptr;
    DatabaseManager* m_dbmanager = nullptr;
    User* m_currentuser = nullptr;
    Logger* m_logger = nullptr;
    AdminPanel* m_window_admin = nullptr;
    ManualVehicleEntry* m_window_vehicle_in = nullptr;
    ManualVehicleExit* m_window_vehicle_out = nullptr;
    SettingsPanel* m_window_settings = nullptr;
    CurrentPlanWindow* m_window_currentplan = nullptr;
    VehicleSearch* m_window_vehiclesearch = nullptr;
    ThreadManager* m_threadManager = nullptr;
    TCPClient* m_client = nullptr;
    PricingPlan* currentPricingPlan = nullptr;

    qint32 m_remainingSpots = 0;
    QList<PricingPlan*> m_pricingPlans;
    qint32 m_currentPlanID = 0;
    QString m_serverAddress;
    qint32 m_serverPort;
    qint32 m_RemoteID;


    // camera settings
    bool m_isCameraInputOn = false;
    unsigned int m_vehicleInCameraDeviceIndex = 0;
    unsigned int m_vehicleOutCameraDeviceIndex = 1;

    void initializeAssetPaths();
    void setupIcons();
    void setupCustomComponents();


    QMap<QString, QString> m_assetPaths;

    // programda kullanılacak tüm asset'lerin adları ve dosya yolları burada girilmelidir.
    QList<QString> m_params = {
        "icon_close,        :/Images/assets/images/close.png",
        "icon_print,        :",
        "image_background,  :",
        "icon_settings,     :/Images/assets/images/settings.png",
        "icon_adminpanel,   :/Images/assets/images/adminpanel.png",
        "icon_vehicle_in,   :/Images/assets/images/add_vehicle.png",
        "icon_vehicle_out,  :/Images/assets/images/remove_vehicle.png",
        "icon_search,       :/Images/assets/images/search.png",
        "icon_list,         :/Images/assets/images/list.png",
        "icon_parkingspot,  :/Images/assets/images/parking-icon.png",
        "icon_camera,       :/Images/assets/images/security-camera.png"
    };
    void SetupTCPConnection();
};

#endif // APPLICATIONWINDOW_HPP
