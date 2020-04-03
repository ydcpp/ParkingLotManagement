#include "pricingplan.hpp"
#include "applicationwindow.hpp"

PricingPlan::PricingPlan(QObject *parent) : QObject(parent)
{

}

PricingPlan::PricingPlan(const qint32& id, const QString& name, const float& pricePerHour, const float& lessthantwo, const float& twothree, const float& threefour, const float& fourfive, const float& fivesix, const float& sixseven, const float& seveneight, const float& eightten, const float& tentwelve, const float& morethantwelve)
{
    m_planID = id;
    m_planName = name;
    m_pricePerHour = pricePerHour;
    m_lessThanTwo = lessthantwo;
    m_TwoThree = twothree;
    m_ThreeFour = threefour;
    m_FourFive = fourfive;
    m_FiveSix = fivesix;
    m_SixSeven = sixseven;
    m_SevenEight = seveneight;
    m_EightTen = eightten;
    m_TenTwelve = tentwelve;
    m_moreThanTwelve = morethantwelve;
}

qint32 PricingPlan::GetPlanID() const
{
    return m_planID;
}

QString PricingPlan::GetPlanName() const
{
    return m_planName;
}

float PricingPlan::GetPricePerHour() const
{
    return m_pricePerHour;
}

float PricingPlan::Getlessthantwo() const
{
    return m_lessThanTwo;
}

float PricingPlan::Gettwothree() const
{
    return m_TwoThree;
}

float PricingPlan::Getthreefour() const
{
    return  m_ThreeFour;
}

float PricingPlan::Getfourfive() const
{
    return m_FourFive;
}

float PricingPlan::Getfivesix() const
{
    return m_FiveSix;
}

float PricingPlan::Getsixseven() const
{
    return m_SixSeven;
}

float PricingPlan::Getseveneight() const
{
    return m_SevenEight;
}

float PricingPlan::Geteightten() const
{
    return m_EightTen;
}

float PricingPlan::Gettentwelve() const
{
    return m_TenTwelve;
}

float PricingPlan::Getmorethantwelve() const
{
    return m_moreThanTwelve;
}

void PricingPlan::GetPricesPerHour(float &lessThanTwo, float &twoThree, float &threeFour, float &fourFive, float &fiveSix, float &sixSeven, float &sevenEight, float &eightTen, float &tenTwelve, float &moreThanTwelve)
{
    lessThanTwo     = m_pricePerHour*m_lessThanTwo;
    twoThree        = m_pricePerHour*m_TwoThree;
    threeFour       = m_pricePerHour*m_ThreeFour;
    fourFive        = m_pricePerHour*m_FourFive;
    fiveSix         = m_pricePerHour*m_FiveSix;
    sixSeven        = m_pricePerHour*m_SixSeven;
    sevenEight      = m_pricePerHour*m_SevenEight;
    eightTen        = m_pricePerHour*m_EightTen;
    tenTwelve       = m_pricePerHour*m_TenTwelve;
    moreThanTwelve  = m_pricePerHour*m_moreThanTwelve;
}

void PricingPlan::SetPricesPerHour(const float& lessThanTwo, const float& twoThree, const float& threeFour, const float& fourFive, const float& fiveSix, const float& sixSeven, const float& sevenEight, const float& eightTen, const float& tenTwelve, const float& moreThanTwelve)
{
    m_lessThanTwo=lessThanTwo;
    m_TwoThree=twoThree;
    m_ThreeFour=threeFour;
    m_FourFive=fourFive;
    m_FiveSix=fiveSix;
    m_SixSeven=sixSeven;
    m_SevenEight=sevenEight;
    m_EightTen=eightTen;
    m_TenTwelve=tenTwelve;
    m_moreThanTwelve=moreThanTwelve;
}

float PricingPlan::CalculatePrice(const qint64& minutes)
{
    int hour = int(minutes)/60;
    if(hour < 2){
        return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_lessThanTwo);
    }else if(hour >= 12){
        return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_moreThanTwelve);
    }else{
        switch(hour){
        case 2:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_TwoThree);
        case 3:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_ThreeFour);
        case 4:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_FourFive);
        case 5:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_FiveSix);
        case 6:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_SixSeven);
        case 7:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_SevenEight);
        case 8:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_EightTen);
        case 9:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_EightTen);
        case 10:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_TenTwelve);
        case 11:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour*m_TenTwelve);
        default:
            return roundPrice(float(minutes)/60.0f*m_pricePerHour);
        }
    }
}

float PricingPlan::roundPrice(const float& price)
{
    return QString().setNum(price,'f',2).toFloat();
}
