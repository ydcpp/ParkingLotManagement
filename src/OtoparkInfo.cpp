#include "OtoparkInfo.hpp"

OtoparkInfo::OtoparkInfo(const qint32& planid)
    : CurrentPlanID(planid)
{

}

OtoparkInfo::~OtoparkInfo()
{

}

void OtoparkInfo::setCurrentPlanID(const qint32& planid)
{
    CurrentPlanID = planid;
}

qint32 OtoparkInfo::getCurrentPlanID() const
{
    return CurrentPlanID;
}

