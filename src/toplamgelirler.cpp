#include "toplamgelirler.hpp"
#include "ui_toplamgelirler.h"

ToplamGelirler::ToplamGelirler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToplamGelirler)
{
    ui->setupUi(this);
}

ToplamGelirler::~ToplamGelirler()
{
    delete ui;
}
