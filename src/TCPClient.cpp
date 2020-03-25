#include "TCPClient.hpp"

#include <QHostAddress>
#include <QString>
#include <QThread>
#include <QDebug>


TCPClient* TCPClient::m_instance(0);
int TCPClient::_refCounter = 0;

TCPClient::TCPClient(QString hostip, qint16 port)
    : m_hostip(hostip), m_port(port)
{
    connect(&m_socket, &QTcpSocket::readyRead, this, &TCPClient::onReadyRead);
    connect(&m_socket,&QTcpSocket::stateChanged,this,&TCPClient::socketStateChanged);
}

TCPClient::~TCPClient()
{
}


TCPClient* TCPClient::getInstance(QString hostip, qint16 port)
{
    if(!m_instance) m_instance = new TCPClient(hostip,port);
    ++_refCounter;
    return m_instance;
}

void TCPClient::releaseInstance()
{
    if(_refCounter == 0) return;
    --_refCounter;
    if(_refCounter == 0 && m_instance != nullptr){
        delete m_instance;
        m_instance = nullptr;
    }
}

void TCPClient::startConnection()
{
    m_socket.connectToHost(QHostAddress(m_hostip), m_port);
}

void TCPClient::terminateConnection()
{
    m_socket.disconnectFromHost();
}

void TCPClient::onReadyRead()
{
    m_receivedData = m_socket.readAll();
    qDebug() << m_receivedData;
    emit dataReceived(m_receivedData);
    //m_socket->write(QByteArray("ok !\n"));
}

void TCPClient::socketStateChanged(QAbstractSocket::SocketState socketState)
{
    emit stateChanged(socketState);
}


void TCPClient::sendData(QString data)
{
    if(m_socket.state() == QTcpSocket::UnconnectedState){
        qDebug() << "Socket is not connected.";
        return;
    }
    m_socket.write(data.toUtf8());
}

QString TCPClient::readData()
{
    if(m_socket.state() == QTcpSocket::UnconnectedState){
        qDebug() << "Socket is not connected.";
        return "";
    }
    return m_receivedData;
}
