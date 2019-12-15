#include "vehiclesearch.hpp"
#include "ui_vehiclesearch.h"

#include "databasemanager.hpp"
#include "applicationwindow.hpp"

VehicleSearch::VehicleSearch(DatabaseManager* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VehicleSearch)
{
    ui->setupUi(this);
    dbmanager = db;
    m_model = new QSqlQueryModel();
    m_proxymodel = new QSortFilterProxyModel();

    // setting up icons
    ui->pushButton_search->setIcon(QIcon(static_cast<ApplicationWindow*>(parent)->GetAssetPaths()["icon_search"]));


}

VehicleSearch::~VehicleSearch()
{
    delete ui;
    delete m_model;
    delete m_proxymodel;
}

void VehicleSearch::on_pushButton_close_clicked()
{
    this->close();
}

void VehicleSearch::on_pushButton_search_clicked()
{
    clearVehicleInfo();
    QString plate = ui->lineEdit_search->text();
    QString model;
    QString type;
    QString color;
    qint32 vehicleID;
    QString errormsg;
    if(!dbmanager->GetVehicleInformationByPlate(plate,vehicleID,color,type,model,errormsg)){
        ui->label_error->setText(errormsg);
        return;
    }
    setVehicleInfo(plate,model,color,type);
    if(!dbmanager->SetQueryModel_TotalPaymentInfo(vehicleID,m_model,errormsg)){
        ui->label_error->setText(errormsg);
        return;
    }
    m_proxymodel->setSourceModel(m_model);
    ui->tableView->setModel(m_proxymodel);
    // setting up tableview
    ui->tableView->setColumnWidth(0,70);
    ui->tableView->setColumnWidth(1,120);
    ui->tableView->setColumnWidth(2,120);
    ui->tableView->setColumnWidth(3,50);
    ui->tableView->setColumnWidth(4,70);
    ui->tableView->setColumnWidth(5,80);
}

void VehicleSearch::clearVehicleInfo()
{
    m_model->clear();
    ui->label_error->clear();
    ui->lineEdit_plate->clear();
    ui->lineEdit_type->clear();
    ui->lineEdit_color->clear();
    ui->lineEdit_model->clear();
}

void VehicleSearch::setVehicleInfo(QString plate, QString model, QString color, QString type)
{
    ui->lineEdit_plate->setText(plate);
    ui->lineEdit_model->setText(model);
    ui->lineEdit_color->setText(color);
    ui->lineEdit_type->setText(type);
}
