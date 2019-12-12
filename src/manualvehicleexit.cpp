#include "manualvehicleexit.hpp"
#include "ui_manualvehicleexit.h"

#include "databasemanager.hpp"
#include "applicationwindow.hpp"
#include <QTimer>

ManualVehicleExit::ManualVehicleExit(DatabaseManager* dbmanager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualVehicleExit)
{
    ui->setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    m_dbmanager = dbmanager;
    connect(this,&ManualVehicleExit::getCalculatedPrice,static_cast<ApplicationWindow*>(parent),&ApplicationWindow::calculatePrice);
}

ManualVehicleExit::~ManualVehicleExit()
{
    delete ui;
}

void ManualVehicleExit::on_pushButton_query_clicked()
{
    clearResults();
    if(validateForm()){
        QString errormsg;
        // query plate number,get vehicle id to m_vehicleID, get the info and calculate price
        if(!m_dbmanager->getBillingResult(ui->lineEdit_plateQuery->text(),errormsg,m_paymentID,m_minute,m_vehicleID,m_entryDate)){
            ui->label_result->setStyleSheet("color:red;");
            ui->label_result->setText(errormsg);
            return;
        }
        if(!m_dbmanager->getVehicleInformation(m_vehicleID,errormsg,m_plate,m_color,m_type,m_model)){
            ui->label_result->setStyleSheet("color:red;");
            ui->label_result->setText(errormsg);
            return;
        }
        m_price = getCalculatedPrice(m_minute,m_currentPlan);
        // displaying the bill
        ui->lineEdit_plate->setText(m_plate);
        ui->lineEdit_color->setText(m_color);
        ui->lineEdit_type->setText(m_type);
        ui->lineEdit_model->setText(m_model);
        ui->dateTimeEdit_entryDate->setDateTime(m_entryDate);
        ui->dateTimeEdit_exitDate->setDateTime(QDateTime::currentDateTime());
        ui->lineEdit_totalminutes->setText(QString::number(m_minute) + "  dk.");
        ui->lineEdit_plan->setText(m_currentPlan);
        ui->lineEdit_price->setText(QString().setNum(m_price,'g',2));
        ui->pushButton_completePayment->setEnabled(true);
    }
}

void ManualVehicleExit::on_pushButton_completePayment_clicked()
{
    ui->pushButton_completePayment->setEnabled(false);
    QString errormsg;
    if(!m_dbmanager->completePayment(m_vehicleID,QDateTime::currentDateTime(),m_price,errormsg)){
        ui->label_result->setStyleSheet("color:red;");
        ui->label_result->setText(errormsg);
        ui->pushButton_completePayment->setEnabled(true);
    }else{
        ui->label_result->setStyleSheet("color:green;");
        ui->label_result->setText("ÖDEME TAMAMLANDI.");
        QTimer::singleShot(2000,this,&QDialog::close);
    }
}

bool ManualVehicleExit::validateForm()
{
    if(ui->lineEdit_plateQuery->text().isEmpty()) return false;
    else return true;
}

void ManualVehicleExit::clearResults()
{
    ui->label_result->clear();
    ui->lineEdit_plate->clear();
    ui->lineEdit_color->clear();
    ui->lineEdit_type->clear();
    ui->lineEdit_model->clear();
    ui->dateTimeEdit_entryDate->setDateTime(QDateTime(QDate(2000,1,1),QTime(0,0)));
    ui->dateTimeEdit_exitDate->setDateTime(QDateTime(QDate(2000,1,1),QTime(0,0)));
    ui->lineEdit_totalminutes->clear();
    ui->lineEdit_plan->clear();
    ui->lineEdit_price->clear();
    ui->pushButton_completePayment->setEnabled(false);
}
