#include "kullanicisil.hpp"
#include "ui_kullanicisil.h"

KullaniciSil::KullaniciSil(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KullaniciSil)
{
    ui->setupUi(this);
}

KullaniciSil::~KullaniciSil()
{
    delete ui;
}
