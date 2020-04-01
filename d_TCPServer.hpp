#ifndef D_TCPSERVER_HPP
#define D_TCPSERVER_HPP

#include <QDialog>

#include "TCPClient.hpp"

namespace Ui {
class d_TCPServer;
}

class d_TCPServer : public QDialog
{
    Q_OBJECT

public:
    explicit d_TCPServer(QWidget *parent = nullptr);
    ~d_TCPServer();

private slots:
    void on_datareceived(QString);

    void on_pushButton_clicked();

private:
    Ui::d_TCPServer *ui;
    TCPClient* client;
};

#endif // D_TCPSERVER_HPP
