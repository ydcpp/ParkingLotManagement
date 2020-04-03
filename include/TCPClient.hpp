#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <QObject>
#include <QTcpSocket>

class DatabaseManager;

class TCPClient : public QObject
{
    Q_OBJECT
public:
    static TCPClient* getInstance(const QString& hostip, const qint16& port, const qint32& remoteDBid, DatabaseManager* dbmanager);
    static void releaseInstance();

    void startConnection();
    void terminateConnection();
    QAbstractSocket::SocketState getCurrentSocketState();
    QString getLastError();


signals:
    void stateChanged(const QAbstractSocket::SocketState& socketState);
    void sendError(const QString& error);

private slots:
    void onReadyRead();
    void socketStateChanged(QAbstractSocket::SocketState socketState);
    void onSpotCounterDecreased();
    void onSpotCounterIncreased();
    void onConnected();

private:
    TCPClient(const QString& hostip, const qint16& port, const qint32& remoteDBid, DatabaseManager* dbmanager);
    ~TCPClient();
    DatabaseManager* m_dbmanager;
    QString m_hostip;
    qint16 m_port;
    QTcpSocket m_socket;
    QByteArray m_receivedData;
    qint32 m_remoteID;
    bool isHostReady = false;

    void sendData(const QString& data);
    void analyzeReceivedMessage(QString receivedMessage);
    void sendSynchRemainingSpot(const qint32& value);

    static TCPClient* m_instance;
    static int _refCounter;
};

#endif // TCPCLIENT_HPP
