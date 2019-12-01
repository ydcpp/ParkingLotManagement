#ifndef APPLICATIONWINDOW_HPP
#define APPLICATIONWINDOW_HPP

#include <QWidget>

class DatabaseManager;
class ParkYerim;

namespace Ui {
class ApplicationWindow;
}

class ApplicationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationWindow(DatabaseManager* dbmanager, QWidget *parent = nullptr);
    ~ApplicationWindow();

    void clearVehicleInStats();
    void clearVehicleOutStats();

private slots:
    void on_toolButton_quit_clicked();
    void showTime();

    void on_toolButton_vehicle_in_clicked();

    void on_toolButton_vehicle_out_clicked();

private:
    Ui::ApplicationWindow *ui;
    ParkYerim* m_parent = nullptr;
    DatabaseManager* m_dbmanager = nullptr;
};

#endif // APPLICATIONWINDOW_HPP
