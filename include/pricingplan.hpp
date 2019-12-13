#ifndef PRICINGPLAN_HPP
#define PRICINGPLAN_HPP

#include <QObject>

class PricingPlan : public QObject
{
    Q_OBJECT
public:
    explicit PricingPlan(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PRICINGPLAN_HPP
