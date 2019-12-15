#ifndef PRICINGPLANWIDGET_HPP
#define PRICINGPLANWIDGET_HPP

#include <QWidget>

namespace Ui {
class PricingPlanWidget;
}

class PricingPlanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PricingPlanWidget(QWidget *parent);
    ~PricingPlanWidget();

private:
    Ui::PricingPlanWidget *ui;
};

#endif // PRICINGPLANWIDGET_HPP
