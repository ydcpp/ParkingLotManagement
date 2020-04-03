#include "currentplanwindow.hpp"
#include "ui_currentplanwindow.h"

#include "pricingplan.hpp"
#include <QString>
#include <QDebug>

CurrentPlanWindow::CurrentPlanWindow(PricingPlan* currentplan, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurrentPlanWindow)
{
    ui->setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    if(currentplan){
        ui->label_planName->setText(currentplan->GetPlanName());
        currentplan->GetPricesPerHour(n_lessthantwo,n_twothree,n_threefour,n_fourfive,n_fivesix,n_sixseven,n_seveneight,n_eightten,n_tentwelve,n_morethantwelve);
        ShowPrices();
    }else{
        qDebug() << "current plan pointer is null";
    }
}

CurrentPlanWindow::~CurrentPlanWindow()
{
    delete ui;
}

void CurrentPlanWindow::on_pushButton_clicked()
{
    this->close();
}

void CurrentPlanWindow::ShowPrices()
{
    ui->lineEdit_n_lessthantwo->setText(QString().setNum(n_lessthantwo,'f',2));
    ui->lineEdit_n_twothree->setText(QString().setNum(n_twothree,'f',2));
    ui->lineEdit_n_threefour->setText(QString().setNum(n_threefour,'f',2));
    ui->lineEdit_n_fourfive->setText(QString().setNum(n_fourfive,'f',2));
    ui->lineEdit_n_fivesix->setText(QString().setNum(n_fivesix,'f',2));
    ui->lineEdit_n_sixseven->setText(QString().setNum(n_sixseven,'f',2));
    ui->lineEdit_n_seveneight->setText(QString().setNum(n_seveneight,'f',2));
    ui->lineEdit_n_eightten->setText(QString().setNum(n_eightten,'f',2));
    ui->lineEdit_n_tentwelve->setText(QString().setNum(n_tentwelve,'f',2));
    ui->lineEdit_n_morethantwelve->setText(QString().setNum(n_morethantwelve,'f',2));
}

