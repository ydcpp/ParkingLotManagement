#ifndef USER_HPP
#define USER_HPP

#include <QString>


class User
{
public:
    User();
    ~User();

    enum USERTYPES {
        USER_NORMAL = 1,
        USER_MANAGER = 2,
        USER_ADMIN = 3
    };

    User::USERTYPES getUserType();

private:
    QString m_username;
    QString m_firstName;
    QString m_lastName;
    USERTYPES m_type;
};

#endif // USER_HPP
