#ifndef OTOPARKINFO_HPP
#define OTOPARKINFO_HPP

#include <QObject>

class OtoparkInfo
{
public:
    OtoparkInfo(const QString& ip,const quint16& port,const qint32& id,const qint32& planid);
    ~OtoparkInfo();

    [[nodiscard]] QString getServerIP() const;
    void setServerIP(const QString& value);

    [[nodiscard]] quint16 getServerPort() const;
    void setServerPort(const quint16& value);

    [[nodiscard]] qint32 getServerOtoparkID() const;
    void setServerOtoparkID(const qint32& value);

    [[nodiscard]] qint32 getCurrentPlanID() const;
    void setCurrentPlanID(const qint32& value);

private:
    QString ServerIP;
    quint16 ServerPort;
    qint32 ServerOtoparkID;
    qint32 CurrentPlanID;
};

#endif // OTOPARKINFO_HPP
