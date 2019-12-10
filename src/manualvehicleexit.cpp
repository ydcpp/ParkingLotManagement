#include "manualvehicleexit.hpp"
#include "ui_manualvehicleexit.h"

#include "databasemanager.hpp"

ManualVehicleExit::ManualVehicleExit(DatabaseManager* dbmanager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualVehicleExit)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    m_dbmanager = dbmanager;
}

ManualVehicleExit::~ManualVehicleExit()
{
    delete ui;
}
