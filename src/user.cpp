#include "User.hpp"

User::User(QString username, QString firstname, QString lastname, qint32 accID, qint32 usertype)
{
    m_username = username;
    m_firstName = firstname;
    m_lastName = lastname;
    m_accountID = accID;
    switch (usertype) {
    case 0:
        m_type = USER_NULL;
        break;
    case 1:
        m_type = USER_NORMAL;
        break;
    case 2:
        m_type = USER_MANAGER;
        break;
    case 3:
        m_type = USER_ADMIN;
        break;
    default:
        m_type = USER_NULL;
        break;
    }
}

User::~User()
{

}

User::USERTYPES User::getUserType()
{
    return m_type;
}

QString User::getUsername() const
{
    return m_username;
}

QString User::getFirstName() const
{
    return m_firstName;
}

QString User::getLastName() const
{
    return m_lastName;
}

qint32 User::getAccountID() const
{
    return m_accountID;
}
