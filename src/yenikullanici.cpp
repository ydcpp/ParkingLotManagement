#include "yenikullanici.hpp"
#include "ui_yenikullanici.h"

YeniKullanici::YeniKullanici(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YeniKullanici)
{
    ui->setupUi(this);
}

YeniKullanici::~YeniKullanici()
{
    delete ui;
}
