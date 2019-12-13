#include "totalincomes.hpp"
#include "ui_totalincomes.h"

#include "databasemanager.hpp"
#include <QDateTime>

TotalIncomes::TotalIncomes(DatabaseManager* dbmanager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TotalIncomes)
{
    ui->setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    m_dbmanager = dbmanager;
    ui->label_lastupdate->setText(QDateTime::currentDateTime().toString("dd.MM.yyyy - HH:mm"));
    ui->lineEdit_monthly->setText(QString().setNum(GetMonthlyIncomeAmount(),'f',2));
    ui->lineEdit_weekly->setText(QString().setNum(GetWeeklyIncomeAmount(),'f',2));
    ui->lineEdit_daily->setText(QString().setNum(GetDailyIncomeAmount(),'f',2));
}

TotalIncomes::~TotalIncomes()
{
    delete ui;
}

float TotalIncomes::GetMonthlyIncomeAmount()
{
    QString errormsg;
    float income;
    if(!m_dbmanager->QueryMonthlyIncome(income,errormsg)){
        ui->label_error->setText(errormsg);
        return 0.0f;
    }
    return income;
}

float TotalIncomes::GetWeeklyIncomeAmount()
{
    QString errormsg;
    float income;
    if(!m_dbmanager->QueryWeeklyIncome(income,errormsg)){
        ui->label_error->setText(errormsg);
        return 0.0f;
    }
    return income;
}

float TotalIncomes::GetDailyIncomeAmount()
{
    QString errormsg;
    float income;
    if(!m_dbmanager->QueryDailyIncome(income,errormsg)){
        ui->label_error->setText(errormsg);
        return 0.0f;
    }
    return income;
}

void TotalIncomes::on_pushButton_close_clicked()
{
    this->close();
}
