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
    explicit ManualVehicleEntry(DatabaseManager* dbmanager, QWidget *parent = nullptr);
    ~ManualVehicleEntry();

private:
    Ui::ManualVehicleEntry *ui;
    DatabaseManager* m_dbmanager;
};

#endif // MANUALVEHICLEENTRY_HPP
