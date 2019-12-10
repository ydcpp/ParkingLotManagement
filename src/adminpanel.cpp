#include "adminpanel.hpp"
#include "ui_adminpanel.h"

#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>

AdminPanel::AdminPanel(DatabaseManager* dbmanager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPanel)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    ui->label_status->setText("");
    m_dbmanager = dbmanager;
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::keyPressEvent(QKeyEvent* e)
{
    if(e->key() != Qt::Key_Escape)
        QWidget::keyPressEvent(e);
    else {/* minimize is disabled */}
}

void AdminPanel::on_pushButton_close_clicked()
{
    this->close();
}

void AdminPanel::on_pushButton_employees_clicked()
{

}

void AdminPanel::on_pushButton_managers_clicked()
{

}

void AdminPanel::on_pushButton_newUser_clicked()
{
    window_yenikullanici = new NewUser(m_dbmanager,this);
    window_yenikullanici->exec();
}

void AdminPanel::updateStatusText(QString text, qint32 milliseconds)
{
    ui->label_status->setText(text);
    ui->label_status->setStyleSheet("color:black;");
    QTimer::singleShot(milliseconds,ui->label_status,&QLabel::clear);
}

void AdminPanel::statusMessageSuccess(QString text, qint32 milliseconds)
{
    ui->label_status->setText(text);
    ui->label_status->setStyleSheet("color:green;");
    QTimer::singleShot(milliseconds,ui->label_status,&QLabel::clear);
}

void AdminPanel::statusMessageError(QString text, qint32 milliseconds)
{
    ui->label_status->setText(text);
    ui->label_status->setStyleSheet("color:red;");
    QTimer::singleShot(milliseconds,ui->label_status,&QLabel::clear);
}

void AdminPanel::on_pushButton_deleteUser_clicked()
{
    window_kullaniciSil = new DeleteUser(m_dbmanager,this);
    window_kullaniciSil->exec();
}

void AdminPanel::on_pushButton_incomes_clicked()
{
    window_toplamGelirler = new TotalIncomes(m_dbmanager,this);
    window_toplamGelirler->exec();
}
