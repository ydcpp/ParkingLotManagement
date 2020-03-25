#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <QObject>
#include <QTcpSocket>


class TCPClient : public QObject
{
    Q_OBJECT
public:
    static TCPClient* getInstance(QString hostip, qint16 port);
    static void releaseInstance();

    void startConnection();
    void terminateConnection();
    void sendData(QString data);
    QString readData();

signals:
    void dataReceived(QString);
    void stateChanged(QAbstractSocket::SocketState socketState);

private slots:
    void onReadyRead();
    void socketStateChanged(QAbstractSocket::SocketState socketState);

private:
    TCPClient(QString hostip, qint16 port);
    ~TCPClient();
    QString m_hostip;
    qint16 m_port;
    QTcpSocket m_socket;
    QByteArray m_receivedData;

    static TCPClient* m_instance;
    static int _refCounter;
};

#endif // TCPCLIENT_HPP
