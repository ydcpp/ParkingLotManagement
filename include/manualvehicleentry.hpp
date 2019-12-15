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
    explicit ManualVehicleEntry(DatabaseManager* dbmanager, QWidget *parent);
    ~ManualVehicleEntry();

signals:
    void decreaseCount();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ManualVehicleEntry *ui;
    DatabaseManager* m_dbmanager;

    bool validateForm();
};

#endif // MANUALVEHICLEENTRY_HPP
