#include "d_ConnectionDialog.hpp"
#include "ui_d_ConnectionDialog.h"
#include "TCPClient.hpp"

#include <QString>

d_ConnectionDialog::d_ConnectionDialog(QString ip, qint16 port,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::d_ConnectionDialog)
{
    ui->setupUi(this);
    m_client = TCPClient::getInstance(ip,port);
    connect(m_client,&TCPClient::dataReceived,this,&d_ConnectionDialog::printReceivedData);
    connect(m_client,&TCPClient::stateChanged,this,&d_ConnectionDialog::socketStateUpdate);
    m_client->startConnection();
}

d_ConnectionDialog::~d_ConnectionDialog()
{
    m_client->releaseInstance();
    delete ui;
}

void d_ConnectionDialog::on_pushButton_send_clicked()
{
    QString data = ui->lineEdit_out->text();
    m_client->sendData(data);
    ui->lineEdit_out->setText("");
}

void d_ConnectionDialog::printReceivedData(QString data)
{
    ui->textEdit->setText(data);
}

void d_ConnectionDialog::socketStateUpdate(QAbstractSocket::SocketState socketState)
{
    if(socketState == QAbstractSocket::ConnectedState){
        ui->label_status->setStyleSheet("color:green;");
        ui->label_status->setText(QVariant::fromValue(socketState).toString());
        ui->pushButton_send->setEnabled(true);
    }else{
        ui->label_status->setStyleSheet("color:orange;");
        ui->label_status->setText(QVariant::fromValue(socketState).toString());
        ui->pushButton_send->setEnabled(false);
    }

}
