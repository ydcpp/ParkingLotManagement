#include "adminpanel.hpp"
#include "ui_adminpanel.h"

#include "databasemanager.hpp"

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
    m_model = new QSqlQueryModel();
    m_proxymodel = new QSortFilterProxyModel();
}

AdminPanel::~AdminPanel()
{
    delete ui;
    delete m_model;
    delete m_proxymodel;
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
    ui->label_tableheader->setText("");
    QString errormsg;
    if(!m_dbmanager->SetQueryModel_Employees(m_model,errormsg)){
        statusMessageError(errormsg,3000);
        return;
    }
    m_proxymodel->setSourceModel(m_model);
    ui->tableView->setModel(m_proxymodel);
    ui->label_tableheader->setText("Çalışanların Listesi");
}

void AdminPanel::on_pushButton_managers_clicked()
{
    ui->label_tableheader->setText("");
    QString errormsg;
    if(!m_dbmanager->SetQueryModel_Managers(m_model,errormsg)){
        statusMessageError(errormsg,3000);
        return;
    }
    m_proxymodel->setSourceModel(m_model);
    ui->tableView->setModel(m_proxymodel);
    ui->label_tableheader->setText("Yöneticilerin Listesi");
}

void AdminPanel::on_pushButton_newUser_clicked()
{
    window_yenikullanici = new NewUser(m_dbmanager,this);
    window_yenikullanici->exec();
}

void AdminPanel::updateStatusText(const QString& text, const qint32& milliseconds)
{
    ui->label_status->setText(text);
    ui->label_status->setStyleSheet("color:black;");
    QTimer::singleShot(milliseconds,ui->label_status,&QLabel::clear);
}

void AdminPanel::statusMessageSuccess(const QString& text, const qint32& milliseconds)
{
    ui->label_status->setText(text);
    ui->label_status->setStyleSheet("color:green;");
    QTimer::singleShot(milliseconds,ui->label_status,&QLabel::clear);
}

void AdminPanel::statusMessageError(const QString& text, const qint32& milliseconds)
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

void AdminPanel::on_pushButton_payments_clicked()
{
    ui->label_tableheader->setText("");
    QString errormsg;
    if(!m_dbmanager->SetQUeryModel_Payments(m_model,errormsg)){
        statusMessageError(errormsg,3000);
        return;
    }
    m_proxymodel->setSourceModel(m_model);
    ui->tableView->setModel(m_proxymodel);
    ui->tableView->setColumnWidth(0,70);
    ui->tableView->setColumnWidth(1,110);
    ui->tableView->setColumnWidth(2,90);
    ui->tableView->setColumnWidth(3,120);
    ui->tableView->setColumnWidth(4,120);
    ui->tableView->setColumnWidth(5,45);
    ui->tableView->setColumnWidth(6,65);
    ui->label_tableheader->setText("Yapılan Tüm Ödemelerin Listesi");
}
