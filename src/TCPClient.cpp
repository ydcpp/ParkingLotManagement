#include "TCPClient.hpp"

#include <QHostAddress>
#include <QString>
#include <QThread>

#include "databasemanager.hpp"

#include <QDebug>


TCPClient* TCPClient::m_instance {0};
quint32 TCPClient::_refCounter {0};

TCPClient::TCPClient(const QString& hostip, const qint16& port, const qint32& remoteDBid, DatabaseManager* dbmanager)
    : m_dbmanager(dbmanager), m_hostip(hostip), m_port(port), m_remoteID(remoteDBid)
    //: m_dbmanager(dbmanager), m_hostip("localhost"), m_port(port), m_remoteID(remoteDBid)
{
    connect(&m_socket, &QTcpSocket::readyRead, this, &TCPClient::onReadyRead);
    connect(&m_socket,&QTcpSocket::stateChanged,this,&TCPClient::socketStateChanged);
    connect(&m_socket,&QTcpSocket::connected,this,&TCPClient::onConnected);
    connect(m_dbmanager,&DatabaseManager::sig_RemainingSpotIncreased,this,&TCPClient::onSpotCounterIncreased);
    connect(m_dbmanager,&DatabaseManager::sig_RemainingSpotDecreased,this,&TCPClient::onSpotCounterDecreased);
}


TCPClient* TCPClient::getInstance(const QString& hostip, const qint16& port, const qint32& remoteDBid, DatabaseManager* dbmanager)
{
    if(!m_instance) m_instance = new TCPClient(hostip,port,remoteDBid,dbmanager);
    _refCounter++;
    return m_instance;
}

void TCPClient::releaseInstance()
{
    if(_refCounter == 0) return;
    _refCounter--;
    if(_refCounter == 0 && m_instance != nullptr){
        delete m_instance;
        m_instance = nullptr;
    }
}

void TCPClient::startConnection()
{
    m_socket.connectToHost(m_hostip, m_port);
}

void TCPClient::terminateConnection()
{
    m_socket.disconnectFromHost();
}

void TCPClient::onReadyRead()
{
    m_receivedData = m_socket.readAll();
    analyzeReceivedMessage(m_receivedData);
}

void TCPClient::socketStateChanged(QAbstractSocket::SocketState socketState)
{
    emit stateChanged(socketState);
}

void TCPClient::onSpotCounterDecreased()
{
    QString msg = QString::number(m_remoteID) + ";2";
    sendData(msg);
}

void TCPClient::onSpotCounterIncreased()
{
    QString msg = QString::number(m_remoteID) + ";1";
    sendData(msg);
}

void TCPClient::onConnected()
{

}


void TCPClient::sendData(const QString& data)
{
    if(m_socket.state() == QTcpSocket::UnconnectedState){
        qDebug() << "Socket is not connected.";
        return;
    }
    if(!isHostReady){
        qDebug() << "Host is not ready.";
        return;
    }
    m_socket.write(data.toUtf8());
}

void TCPClient::analyzeReceivedMessage(QString receivedMessage)
{
    QString raw = receivedMessage;
    if(receivedMessage == "999"){
        isHostReady = true;
        QString errmsg;
        int remainingspots = m_dbmanager->QueryRemainingSpots(errmsg);
        if(remainingspots == -1){
            emit sig_errorMessage("TCP Client: Local database error." + errmsg,5000);
            return;
        }
        sendSynchRemainingSpot(remainingspots);
        return;
    }
    receivedMessage = receivedMessage.simplified();
    receivedMessage = receivedMessage.replace(" ","");
    QStringList msgParts = receivedMessage.split(';');
    if(msgParts.isEmpty()) return;
    else{
        if(msgParts[0] == "0"){
            qDebug() << raw;
            return;
        }else{
            QString errormsg;
            int state = msgParts[1].toInt();
            switch (state) {
            case 0:
                qDebug() << msgParts[2];
                break;
            case 1:
            case 2:
                if(msgParts[2].toInt() != m_dbmanager->QueryRemainingSpots(errormsg)){
                    qDebug() << "Returned value is not synched.Starting synchronize procedure...";
                    sendSynchRemainingSpot(m_dbmanager->QueryRemainingSpots(errormsg));
                }
                break;
            case 3:
                if(msgParts[2].toInt() != m_dbmanager->QueryRemainingSpots(errormsg)){
                    emit sendError("Uzak sunucu ile veritabanı eşleşmesi başarısız, lütfen programı yeniden başlatın.");
                }else{
                    emit sig_successMessage("Successfuly synched with remote host database.",4000);
                }
                break;
            default:
                emit sig_errorMessage("TCP Conenction Error: Received invalid action code.",5000);
                break;
            }
        }
    }
}


QAbstractSocket::SocketState TCPClient::getCurrentSocketState()
{
    return m_socket.state();
}

QString TCPClient::getLastError()
{
    return m_socket.errorString();
}

void TCPClient::sendSynchRemainingSpot(const qint32& value)
{
    QString msg = QString::number(m_remoteID) + ";3;" + QString::number(value);
    sendData(msg);
}
