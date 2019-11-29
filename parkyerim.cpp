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

