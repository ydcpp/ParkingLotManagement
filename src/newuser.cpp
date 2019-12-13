#include "newuser.hpp"
#include "ui_newuser.h"

#include "databasemanager.hpp"

#include <QTimer>

NewUser::NewUser(DatabaseManager* dbmanager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUser)
{
    ui->setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    m_dbmanager = dbmanager;
}

NewUser::~NewUser()
{
    delete ui;
}

void NewUser::on_pushButton_submit_clicked()
{
    ui->label_status->setText("");

    if(validateForm()){
        QString errormsg;
        if(m_dbmanager->CreateUser(ui->lineEdit_firstname->text(),
                                    ui->lineEdit_lastname->text(),
                                    ui->lineEdit_phone->text(),
                                    ui->lineEdit_username->text(),
                                    ui->lineEdit_password->text(),
                                    ui->comboBox_usertypes->currentIndex(),
                                    errormsg)){
            ui->pushButton_submit->setEnabled(false);
            ui->pushButton_cancel->setEnabled(false);
            ui->label_status->setStyleSheet("color:green;");
            ui->label_status->setText("Yeni kullanıcı kaydı eklendi.");
            QTimer::singleShot(2000,this,&QDialog::close);
        }else{
            ui->label_status->setStyleSheet("color:red;");
            ui->label_status->setText(errormsg);
        }
    }
}

void NewUser::on_pushButton_cancel_clicked()
{
    this->close();
}

bool NewUser::validateForm()
{
    if(ui->lineEdit_firstname->text().isEmpty()){
        ui->label_status->setText("Ad boş bırakılamaz.");
        return false;
    }
    if(ui->lineEdit_lastname->text().isEmpty()){
        ui->label_status->setText("Soyad boş bırakılamaz.");
        return false;
    }
    if(ui->lineEdit_phone->text().length() != 10){
        ui->label_status->setText("Lütfen 'TELEFON' alanına 10 haneli bir telefon numarası girin.");
        return false;
    }
    if(ui->lineEdit_username->text().isEmpty()){
        ui->label_status->setText("Kullanıcı Adı alanı boş bırakılamaz.");
        return false;
    }
    if(ui->lineEdit_password->text().isEmpty()){
        ui->label_status->setText("Şifre alanı boş bırakılamaz.");
        return false;
    }else if(ui->lineEdit_password->text() != ui->lineEdit_repeatpassword->text()){
        ui->label_status->setText("Şifre tekrarı geçersiz.");
        return false;
    }
    return true;
}
