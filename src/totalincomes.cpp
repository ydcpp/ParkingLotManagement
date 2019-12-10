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
}

TotalIncomes::~TotalIncomes()
{
    delete ui;
}

void TotalIncomes::on_pushButton_close_clicked()
{
    this->close();
}
