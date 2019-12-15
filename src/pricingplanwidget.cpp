#include "pricingplanwidget.hpp"
#include "ui_pricingplanwidget.h"

PricingPlanWidget::PricingPlanWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PricingPlanWidget)
{
    ui->setupUi(this);
}

PricingPlanWidget::~PricingPlanWidget()
{
    delete ui;
}
