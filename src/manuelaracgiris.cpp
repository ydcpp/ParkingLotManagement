#include "manuelaracgiris.hpp"
#include "ui_manuelaracgiris.h"

ManuelAracGiris::ManuelAracGiris(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManuelAracGiris)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
}

ManuelAracGiris::~ManuelAracGiris()
{
    delete ui;
}
