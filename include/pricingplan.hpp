#ifndef PRICINGPLAN_HPP
#define PRICINGPLAN_HPP

#include <QObject>

class PricingPlan : public QObject
{
    Q_OBJECT
public:
    explicit PricingPlan(QObject *parent = nullptr);
    PricingPlan(const qint32& id, const QString& name, const float& pricePerHour,
                const float& lessthantwo,
                const float& twothree,
                const float& threefour,
                const float& fourfive,
                const float& fivesix,
                const float& sixseven,
                const float& seveneight,
                const float& eightten,
                const float& tentwelve,
                const float& morethantwelve);

    qint32 GetPlanID() const;
    QString GetPlanName() const;
    float GetPricePerHour() const;
    float Getlessthantwo() const;
    float Gettwothree() const;
    float Getthreefour() const;
    float Getfourfive() const;
    float Getfivesix() const;
    float Getsixseven() const;
    float Getseveneight() const;
    float Geteightten() const;
    float Gettentwelve() const;
    float Getmorethantwelve() const;
    void GetPricesPerHour(float& lessThanTwo, float& twoThree, float& threeFour, float& fourFive, float& fiveSix, float& sixSeven, float& sevenEight, float& eightTen, float& tenTwelve, float& moreThanTwelve);
    void SetPricesPerHour(const float& lessThanTwo, const float& twoThree, const float& threeFour, const float& fourFive, const float& fiveSix, const float& sixSeven, const float& sevenEight, const float& eightTen, const float& tenTwelve, const float& moreThanTwelve);
signals:

public slots:

    float CalculatePrice(const qint64& minutes);

private:
    qint32 m_planID;
    QString m_planName;
    float m_pricePerHour;
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

    float roundPrice(const float& price);
};

#endif // PRICINGPLAN_HPP
