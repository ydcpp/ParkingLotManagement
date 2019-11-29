#include "parkyerim.hpp"
#include "ui_parkyerim.h"

ParkYerim::ParkYerim(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ParkYerim)
{
    ui->setupUi(this);
}

ParkYerim::~ParkYerim()
{
    delete ui;
}


void ParkYerim::on_pushButton_clicked()
{
    if(validateLoginInfo()) launchProgram();
}

bool ParkYerim::validateLoginInfo()
{
    return true;
}

void ParkYerim::launchProgram()
{
    if(appwindow) delete appwindow;
    appwindow = new ApplicationWindow();
    this->hide();
    appwindow->show();
}
