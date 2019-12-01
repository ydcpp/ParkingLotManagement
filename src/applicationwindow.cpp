#include "applicationwindow.hpp"
#include "ui_applicationwindow.h"

#include <QMessageBox>
#include <QTimer>
#include "parkyerim.hpp"

ApplicationWindow::ApplicationWindow(DatabaseManager* dbmanager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicationWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    m_parent = static_cast<ParkYerim*>(parent);
    m_dbmanager = dbmanager;

    // setting up icons
    ui->toolButton_quit->setIcon(QIcon(m_parent->getAssetPaths()["icon_close"]));
    ui->toolButton_settings->setIcon(QIcon(m_parent->getAssetPaths()["icon_settings"]));
    ui->toolButton_adminpanel->setIcon(QIcon(m_parent->getAssetPaths()["icon_adminpanel"]));

    // setting up digital clock
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ApplicationWindow::showTime);
    timer->start(1000);
    showTime();
}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
}

void ApplicationWindow::clearVehicleInStats()
{
    ui->lineEdit_in_plate->setText("");
    ui->lineEdit_in_color->setText("");
    ui->lineEdit_in_model->setText("");
    ui->lineEdit_in_type->setText("");
}

void ApplicationWindow::clearVehicleOutStats()
{
    ui->lineEdit_out_plate->setText("");
    ui->lineEdit_out_color->setText("");
    ui->lineEdit_out_model->setText("");
    ui->lineEdit_out_type->setText("");
    ui->lineEdit_out_parkLocation->setText("");
    ui->lineEdit_out_price->setText("");
    ui->dateTimeEdit_in->setDateTime(QDateTime(QDate(2000,1,1),QTime(0,0)));
    ui->dateTimeEdit_out->setDateTime(QDateTime(QDate(2000,1,1),QTime(0,0)));
}

void ApplicationWindow::on_toolButton_quit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Çıkış", "Programı kapatmak istediğinizden emin misiniz?", QMessageBox::Yes|QMessageBox::Cancel);
    if(reply == QMessageBox::Yes){
        QApplication::quit();
    }
}

void ApplicationWindow::showTime()
{
    QTime time = QTime::currentTime();
        QString text = time.toString("hh:mm");
        if ((time.second() % 2) == 0)
            text[2] = ' ';
        ui->lcdNumber->display(text);
}

void ApplicationWindow::on_toolButton_vehicle_in_clicked()
{
    clearVehicleInStats();
}

void ApplicationWindow::on_toolButton_vehicle_out_clicked()
{
    clearVehicleOutStats();
}
