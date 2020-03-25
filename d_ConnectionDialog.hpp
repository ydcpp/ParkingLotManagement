#ifndef D_CONNECTIONDIALOG_HPP
#define D_CONNECTIONDIALOG_HPP

#include <QDialog>
#include <QAbstractSocket>

class TCPClient;

namespace Ui {
class d_ConnectionDialog;
}

class d_ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit d_ConnectionDialog(QString ip, qint16 port, QWidget *parent = nullptr);
    ~d_ConnectionDialog();

private slots:
    void on_pushButton_send_clicked();
    void printReceivedData(QString);
    void socketStateUpdate(QAbstractSocket::SocketState socketState);

private:
    Ui::d_ConnectionDialog *ui;
    TCPClient* m_client = nullptr;

};

#endif // D_CONNECTIONDIALOG_HPP
