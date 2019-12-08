#ifndef APPLICATIONWINDOW_HPP
#define APPLICATIONWINDOW_HPP

#include <QWidget>
#include <QMap>

class DatabaseManager;
class User;
class ParkYerim;


namespace Ui {
class ApplicationWindow;
}

class ApplicationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationWindow(DatabaseManager* dbmanager, User* user, QWidget *parent = nullptr);
    ~ApplicationWindow();

    void clearVehicleInStats();
    void clearVehicleOutStats();
    QMap<QString, QString> getAssetPaths();

private slots:
    void on_toolButton_quit_clicked();
    void showTime();

    void on_toolButton_vehicle_in_clicked();

    void on_toolButton_vehicle_out_clicked();

private:
    Ui::ApplicationWindow *ui;
    ParkYerim* m_parent = nullptr;
    DatabaseManager* m_dbmanager = nullptr;
    User* m_user = nullptr;

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
