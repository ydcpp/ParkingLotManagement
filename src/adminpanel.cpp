#include "adminpanel.hpp"
#include "ui_adminpanel.h"

AdminPanel::AdminPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPanel)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::on_pushButton_close_clicked()
{
    this->close();
}

void AdminPanel::on_pushButton_employees_clicked()
{

}

void AdminPanel::on_pushButton_managers_clicked()
{

}

