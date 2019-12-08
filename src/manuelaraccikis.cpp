#include "manuelaraccikis.hpp"
#include "ui_manuelaraccikis.h"

ManuelAracCikis::ManuelAracCikis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManuelAracCikis)
{
    ui->setupUi(this);
}

ManuelAracCikis::~ManuelAracCikis()
{
    delete ui;
}
