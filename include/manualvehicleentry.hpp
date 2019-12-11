#ifndef MANUALVEHICLEENTRY_HPP
#define MANUALVEHICLEENTRY_HPP

#include <QDialog>


class DatabaseManager;

namespace Ui {
class ManualVehicleEntry;
}

class ManualVehicleEntry : public QDialog
{
    Q_OBJECT

public:
    explicit ManualVehicleEntry(DatabaseManager* dbmanager, bool isNightPlan, QWidget *parent = nullptr);
    ~ManualVehicleEntry();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ManualVehicleEntry *ui;
    DatabaseManager* m_dbmanager;
    bool m_nightplan = false;

    bool validateForm();
};

#endif // MANUALVEHICLEENTRY_HPP
