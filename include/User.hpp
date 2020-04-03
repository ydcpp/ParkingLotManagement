#ifndef USER_HPP
#define USER_HPP

#include <QString>
#include <QDateTime>

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
    QString getUserType_string();
    QString getUsername() const;
    QString getFirstName() const;
    QString getLastName() const;
    qint32 getAccountID() const;
    QDateTime getDateCreated() const;
    QString getCurrentPassword() const;

    void updatePassword(QString pw);

    User(const QString& username, const QString& firstname, const QString& lastname, const qint32& accID, const qint32& usertype, const QDateTime& createDate, const QString& password);
    ~User();
private:
    QString m_username;
    QString m_firstName;
    QString m_lastName;
    QString m_password;
    qint32 m_accountID;
    QDateTime m_date;
    USERTYPES m_type;
};

#endif // USER_HPP
