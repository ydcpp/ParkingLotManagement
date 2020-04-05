#ifndef OTOPARKINFO_HPP
#define OTOPARKINFO_HPP

#include <QObject>

class OtoparkInfo
{
public:
    OtoparkInfo(const QString& ip,const quint16& port,const qint32& id,const qint32& planid);
    ~OtoparkInfo();

    QString getCameraDeviceInfo_in() const;
    void setCameraDeviceInfo_in(const QString& value);

    QString getCameraDeviceInfo_out() const;
    void setCameraDeviceInfo_out(const QString& value);

    QString getServerIP() const;
    void setServerIP(const QString& value);

    quint16 getServerPort() const;
    void setServerPort(const quint16& value);

    qint32 getServerOtoparkID() const;
    void setServerOtoparkID(const qint32& value);

    qint32 getCurrentPlanID() const;
    void setCurrentPlanID(const qint32& value);

private:
    QString ServerIP;
    quint16 ServerPort;
    qint32 ServerOtoparkID;
    qint32 CurrentPlanID;
    QString CameraDeviceInfo_in;
    QString CameraDeviceInfo_out;
};

#endif // OTOPARKINFO_HPP
