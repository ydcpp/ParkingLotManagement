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
    [[nodiscard]] QAbstractSocket::SocketState getCurrentSocketState();
    [[nodiscard]] QString getLastError();

signals:
    void stateChanged(const QAbstractSocket::SocketState& socketState);
    void sendError(const QString& error);
    void sig_successMessage(const QString& text, const qint32& milliseconds);
    void sig_errorMessage(const QString& text, const qint32& milliseconds);

private slots:
    void onReadyRead();
    void socketStateChanged(QAbstractSocket::SocketState socketState);
    void onSpotCounterDecreased();
    void onSpotCounterIncreased();
    void onConnected();
    void sendData(const QString& data);
    void analyzeReceivedMessage(QString receivedMessage);
    void sendSynchRemainingSpot(const qint32& value);

private:
    TCPClient(const QString& hostip, const qint16& port, const qint32& remoteDBid, DatabaseManager* dbmanager);
    DatabaseManager* m_dbmanager;
    QString m_hostip;
    qint16 m_port;
    QTcpSocket m_socket;
    QByteArray m_receivedData;
    qint32 m_remoteID;
    bool isHostReady {false};

    static TCPClient* m_instance;
    static quint32 _refCounter;
};

#endif // TCPCLIENT_HPP
