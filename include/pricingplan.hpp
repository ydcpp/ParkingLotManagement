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

    [[nodiscard]] qint32 GetPlanID() const;
    [[nodiscard]] QString GetPlanName() const;
    [[nodiscard]] float GetPricePerHour() const;
    [[nodiscard]] float Getlessthantwo() const;
    [[nodiscard]] float Gettwothree() const;
    [[nodiscard]] float Getthreefour() const;
    [[nodiscard]] float Getfourfive() const;
    [[nodiscard]] float Getfivesix() const;
    [[nodiscard]] float Getsixseven() const;
    [[nodiscard]] float Getseveneight() const;
    [[nodiscard]] float Geteightten() const;
    [[nodiscard]] float Gettentwelve() const;
    [[nodiscard]] float Getmorethantwelve() const;
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

    [[nodiscard]] float roundPrice(const float& price);
};

#endif // PRICINGPLAN_HPP
