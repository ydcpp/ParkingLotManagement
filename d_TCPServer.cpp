#include "d_TCPServer.hpp"
#include "ui_d_TCPServer.h"



d_TCPServer::d_TCPServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::d_TCPServer)
{
    ui->setupUi(this);
    client = TCPClient::getInstance("",0,0);
    connect(client,&TCPClient::dataReceived,this,&d_TCPServer::on_datareceived);
}

d_TCPServer::~d_TCPServer()
{
    client->releaseInstance();
    delete ui;
}


void d_TCPServer::on_datareceived(QString data)
{
    ui->textEdit->setText(data);
}

void d_TCPServer::on_pushButton_clicked()
{
    client->sendData(ui->lineEdit_send->text());
}
