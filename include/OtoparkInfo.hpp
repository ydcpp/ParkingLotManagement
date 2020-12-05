#ifndef OTOPARKINFO_HPP
#define OTOPARKINFO_HPP

#include <QObject>

class OtoparkInfo
{
public:
    OtoparkInfo(const qint32& planid);
    ~OtoparkInfo();

    [[nodiscard]] qint32 getCurrentPlanID() const;
    void setCurrentPlanID(const qint32& value);

private:
    qint32 CurrentPlanID;
};

#endif // OTOPARKINFO_HPP
