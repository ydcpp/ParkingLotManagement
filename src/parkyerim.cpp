#include "parkyerim.hpp"
#include "ui_parkyerim.h"

#include <QTime>
#include <QDebug>

ParkYerim::ParkYerim(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ParkYerim)
{
    ui->setupUi(this);
    initializeDatabase();
    QPixmap pix(":/Images/ParkYerimDesktop.ico");
    ui->label_image->setPixmap(pix.scaled(ui->label_image->width(),ui->label_image->height(),Qt::KeepAspectRatio));
#define SKIP_LOGIN 0
#if SKIP_LOGIN
    launchDebugMode();
#endif
}

ParkYerim::~ParkYerim()
{
    delete ui;
    delete m_database;
    if(m_user) delete m_user;
}

void ParkYerim::on_pushButton_clicked()
{
    ui->label_login_err->setText("");
    if(validateLoginInfo()) launchProgram();
}

bool ParkYerim::validateLoginInfo()
{
    QString username = ui->lineEdit_user->text();
    QString password = ui->lineEdit_password->text();
    QString errormessage;
    if(!m_database->ValidateUserLogin(username,password,errormessage, &m_user)){
        ui->label_login_err->setText(errormessage);
        return false;
    }else return true;
}

void ParkYerim::launchProgram()
{
    ApplicationWindow* appwindow = new ApplicationWindow(m_database,m_user);
    this->hide();
    appwindow->show();
}

void ParkYerim::launchDebugMode()
{
    m_user = new User("admin","debug","mode",1,3,QDateTime(),"admin");
    ApplicationWindow* appwindow = new ApplicationWindow(m_database,m_user);
    this->hide();
    appwindow->show();
}

void ParkYerim::initializeDatabase()
{
    // initialize database instance
    m_database = new DatabaseManager();
    if(!m_database->isConnected()){
        ui->label_login_err->setStyleSheet("color:red;");
        ui->label_login_err->setText("Veritabanına bağlanılamadı.");
        ui->pushButton->setEnabled(false);
    }
}
