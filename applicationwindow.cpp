#include "applicationwindow.hpp"
#include "ui_applicationwindow.h"

#include <QMessageBox>

ApplicationWindow::ApplicationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplicationWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    for(QString s : m_params)
    {
        QList<QString> param = s.split(',' , QString::SkipEmptyParts);
        QString pName = param[0].trimmed();
        QString pValue = param[1].trimmed();
        m_assetPaths[pName] = pValue;
    }
    ui->toolButton_quit->setIcon(QIcon(m_assetPaths["icon_close"]));
}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
}

QMap<QString, QString> ApplicationWindow::getAssetPaths() const
{
    return m_assetPaths;
}

void ApplicationWindow::on_toolButton_quit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Çıkış", "Programı kapatmak istediğinizden emin misiniz?", QMessageBox::Yes|QMessageBox::Cancel);
    if(reply == QMessageBox::Yes){
        QApplication::quit();
    }
}
