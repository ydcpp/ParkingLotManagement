#ifndef USER_HPP
#define USER_HPP

#include <QString>


class User
{
public:
    enum USERTYPES {
        USER_NULL = 0,
        USER_NORMAL = 1,
        USER_MANAGER = 2,
        USER_ADMIN = 3
    };

    User::USERTYPES getUserType();
    QString getUsername() const;
    QString getFirstName() const;
    QString getLastName() const;
    qint32 getAccountID() const;

    User(QString username, QString firstname, QString lastname, qint32 accID, qint32 usertype);
    ~User();
private:
    QString m_username;
    QString m_firstName;
    QString m_lastName;
    qint32 m_accountID;
    USERTYPES m_type;
};

#endif // USER_HPP
