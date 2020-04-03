#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <QObject>
#include <QTcpSocket>

class DatabaseManager;

class TCPClient : public QObject
{
    Q_OBJECT
public:
    static TCPClient* getInstance(QString hostip, qint16 port, qint32 remoteDBid, DatabaseManager* dbmanager);
    static void releaseInstance();

    void startConnection();
    void terminateConnection();
    QAbstractSocket::SocketState getCurrentSocketState();
    QString getLastError();


signals:
    void stateChanged(QAbstractSocket::SocketState socketState);
    void sendError(const QString& error);

private slots:
    void onReadyRead();
    void socketStateChanged(QAbstractSocket::SocketState socketState);
    void onSpotCounterDecreased();
    void onSpotCounterIncreased();
    void onConnected();

private:
    TCPClient(QString hostip, qint16 port, qint32 remoteDBid, DatabaseManager* dbmanager);
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
    void sendSynchRemainingSpot(qint32 value);

    static TCPClient* m_instance;
    static int _refCounter;
};

#endif // TCPCLIENT_HPP
