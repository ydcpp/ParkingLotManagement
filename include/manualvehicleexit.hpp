#ifndef MANUALVEHICLEEXIT_HPP
#define MANUALVEHICLEEXIT_HPP

#include <QDialog>



class DatabaseManager;

namespace Ui {
class ManualVehicleExit;
}

class ManualVehicleExit : public QDialog
{
    Q_OBJECT

public:
    explicit ManualVehicleExit(DatabaseManager* dbmanager, QWidget *parent = nullptr);
    ~ManualVehicleExit();

private:
    Ui::ManualVehicleExit *ui;
    DatabaseManager* m_dbmanager;
};

#endif // MANUALVEHICLEEXIT_HPP
