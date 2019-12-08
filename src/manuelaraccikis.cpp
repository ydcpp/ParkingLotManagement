#include "manuelaraccikis.hpp"
#include "ui_manuelaraccikis.h"

ManuelAracCikis::ManuelAracCikis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManuelAracCikis)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
}

ManuelAracCikis::~ManuelAracCikis()
{
    delete ui;
}
