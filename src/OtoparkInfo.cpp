#include "OtoparkInfo.hpp"

OtoparkInfo::OtoparkInfo(const QString& ip,const quint16& port,const qint32& id,const qint32& planid)
    : ServerIP(ip),ServerPort(port),ServerOtoparkID(id),CurrentPlanID(planid)
{

}

OtoparkInfo::~OtoparkInfo()
{

}

void OtoparkInfo::setServerIP(const QString& ip)
{
    ServerIP = ip;
}

void OtoparkInfo::setServerPort(const quint16& port)
{
    ServerPort = port;
}

void OtoparkInfo::setCurrentPlanID(const qint32& planid)
{
    CurrentPlanID = planid;
}


QString OtoparkInfo::getServerIP() const
{
    return ServerIP;
}

quint16 OtoparkInfo::getServerPort() const
{
    return ServerPort;
}


qint32 OtoparkInfo::getCurrentPlanID() const
{
    return CurrentPlanID;
}


qint32 OtoparkInfo::getServerOtoparkID() const
{
    return ServerOtoparkID;
}

void OtoparkInfo::setServerOtoparkID(const qint32& value)
{
    ServerOtoparkID = value;
}

