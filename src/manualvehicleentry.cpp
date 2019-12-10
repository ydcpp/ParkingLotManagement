#include "manualvehicleentry.hpp"
#include "ui_manualvehicleentry.h"

#include "databasemanager.hpp"

ManualVehicleEntry::ManualVehicleEntry(DatabaseManager* dbmanager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualVehicleEntry)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    m_dbmanager = dbmanager;
}

ManualVehicleEntry::~ManualVehicleEntry()
{
    delete ui;
}
