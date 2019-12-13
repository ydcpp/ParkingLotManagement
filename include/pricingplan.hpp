#ifndef PRICINGPLAN_HPP
#define PRICINGPLAN_HPP

#include <QObject>

class PricingPlan : public QObject
{
    Q_OBJECT
public:
    explicit PricingPlan(QObject *parent = nullptr);
    PricingPlan(qint32 id, QString name, float pricePerHour, float nightTimeMultiplier,
                float lessthantwo,
                float twothree,
                float threefour,
                float fourfive,
                float fivesix,
                float sixseven,
                float seveneight,
                float eightten,
                float tentwelve,
                float morethantwelve);

    qint32 GetPlanID() const;
    QString GetPlanName() const;
    float GetPricePerHour() const;
    float GetNightTimeMultiplier() const;

signals:

public slots:

    float CalculatePrice(qint64 minutes, bool isNight);

private:
    qint32 m_planID;
    QString m_planName;
    float m_pricePerHour;
    float m_NightTimeMultiplier;
    float m_lessThanTwo;
    float m_TwoThree;
    float m_ThreeFour;
    float m_FourFive;
    float m_FiveSix;
    float m_SixSeven;
    float m_SevenEight;
    float m_EightTen;
    float m_TenTwelve;
    float m_moreThanTwelve;
};

#endif // PRICINGPLAN_HPP
