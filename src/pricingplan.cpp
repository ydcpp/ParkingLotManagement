#include "pricingplan.hpp"

PricingPlan::PricingPlan(QObject *parent) : QObject(parent)
{

}

PricingPlan::PricingPlan(qint32 id, QString name, float pricePerHour, float lessthantwo, float twothree, float threefour, float fourfive, float fivesix, float sixseven, float seveneight, float eightten, float tentwelve, float morethantwelve)
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

float PricingPlan::CalculatePrice(qint64 minutes)
{
    int hour = int(minutes)/60;
    if(hour < 2){
        return (float(minutes)/60.0f*m_pricePerHour*m_lessThanTwo);
    }else if(hour >= 12){
        return (float(minutes)/60.0f*m_pricePerHour*m_moreThanTwelve);
    }else{
        switch(hour){
        case 2:
            return (float(minutes)/60.0f*m_pricePerHour*m_TwoThree);
        case 3:
            return (float(minutes)/60.0f*m_pricePerHour*m_ThreeFour);
        case 4:
            return (float(minutes)/60.0f*m_pricePerHour*m_FourFive);
        case 5:
            return (float(minutes)/60.0f*m_pricePerHour*m_FiveSix);
        case 6:
            return (float(minutes)/60.0f*m_pricePerHour*m_SixSeven);
        case 7:
            return (float(minutes)/60.0f*m_pricePerHour*m_SevenEight);
        case 8:
            return (float(minutes)/60.0f*m_pricePerHour*m_EightTen);
        case 9:
            return (float(minutes)/60.0f*m_pricePerHour*m_EightTen);
        case 10:
            return (float(minutes)/60.0f*m_pricePerHour*m_TenTwelve);
        case 11:
            return (float(minutes)/60.0f*m_pricePerHour*m_TenTwelve);
        default:
            return (float(minutes)/60.0f*m_pricePerHour);
        }
    }
}
