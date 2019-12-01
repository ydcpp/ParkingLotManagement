#ifndef PARKYERIM_HPP
#define PARKYERIM_HPP

#include <QMainWindow>
#include <QMap>
#include <QString>

#include "applicationwindow.hpp"
#include "databasemanager.hpp"
#include "User.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class ParkYerim; }
QT_END_NAMESPACE

class ParkYerim : public QMainWindow
{
    Q_OBJECT

public:
    ParkYerim(QWidget *parent = nullptr);
    ~ParkYerim();

    QMap<QString, QString> getAssetPaths();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ParkYerim *ui;
    DatabaseManager* m_database = nullptr;
    User* m_user = nullptr;

    bool validateLoginInfo();
    void launchProgram();

    QMap<QString, QString> m_assetPaths;

    // programda kullanılacak tüm asset'lerin adları ve dosya yolları burada girilmelidir.
    QList<QString> m_params = {
        "database_path,     ./assets/database/parkyerimdb.sqlite",
        "icon_close,        ./assets/images/close.png",
        "icon_print,        ./assets/images/settings.png",
        "image_background,  ./assets/images/background.jpg",
        "icon_settings,     ./assets/images/settings.png",
        "icon_adminpanel,   ./assets/images/adminpanel.png"
    };
};
#endif // PARKYERIM_HPP
