#include "manuelaracgiris.hpp"
#include "ui_manuelaracgiris.h"

ManuelAracGiris::ManuelAracGiris(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManuelAracGiris)
{
    ui->setupUi(this);
}

ManuelAracGiris::~ManuelAracGiris()
{
    delete ui;
}
