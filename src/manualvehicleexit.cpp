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
}

ManualVehicleExit::ManualVehicleExit(DatabaseManager* dbmanager, QWidget* parent, const QString& plate) :
    QDialog(parent),
    ui(new Ui::ManualVehicleExit)
{
    ui->setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    m_dbmanager = dbmanager;
    ui->lineEdit_plateQuery->setText(plate);
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
        QString platequery = ui->lineEdit_plateQuery->text();
        platequery = platequery.simplified();
        platequery = platequery.replace(" ","");
        platequery = platequery.toUpper();
        qint32 planID;
        if(!m_dbmanager->GetBillingResult(platequery,errormsg,m_paymentID,m_minutes,m_vehicleID,m_entryDate,planID)){
            ui->label_result->setStyleSheet("color:red;");
            ui->label_result->setText(errormsg);
            return;
        }
        if(!m_dbmanager->GetVehicleInformation(m_vehicleID,errormsg,m_plate,m_color,m_type,m_model)){
            ui->label_result->setStyleSheet("color:red;");
            ui->label_result->setText(errormsg);
            return;
        }
        emit getCalculatedPrice(m_minutes,planID,m_price,m_planName);
        QTime parkingTime = QTime(0,0).addSecs(60*int(m_minutes));
        // displaying the bill
        ui->lineEdit_plate->setText(m_plate);
        ui->lineEdit_color->setText(m_color);
        ui->lineEdit_type->setText(m_type);
        ui->lineEdit_model->setText(m_model);
        ui->dateTimeEdit_entryDate->setDateTime(m_entryDate);
        ui->dateTimeEdit_exitDate->setDateTime(QDateTime::currentDateTime());
        ui->lineEdit_totalminutes->setText(parkingTime.toString("HH:mm"));
        ui->lineEdit_plan->setText(m_planName);
        ui->lineEdit_price->setText(QString::number(m_price));
        ui->pushButton_completePayment->setEnabled(true);
    }
}

void ManualVehicleExit::on_pushButton_completePayment_clicked()
{
    ui->pushButton_completePayment->setEnabled(false);
    QString errormsg;
    if(!m_dbmanager->CompletePayment(m_vehicleID,QDateTime::currentDateTime(),m_minutes,m_price,errormsg)){
        ui->label_result->setStyleSheet("color:red;");
        ui->label_result->setText(errormsg);
        ui->pushButton_completePayment->setEnabled(true);
    }else{
        ui->label_result->setStyleSheet("color:green;");
        ui->label_result->setText("ÖDEME TAMAMLANDI.");
        emit increaseCount();
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
