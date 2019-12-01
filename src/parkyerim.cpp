#include "parkyerim.hpp"
#include "ui_parkyerim.h"

ParkYerim::ParkYerim(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ParkYerim)
{
    ui->setupUi(this);

    // setting up asset paths
    for(QString s : m_params)
    {
        QList<QString> param = s.split(',' , QString::SkipEmptyParts);
        QString pName = param[0].trimmed();
        QString pValue = param[1].trimmed();
        m_assetPaths[pName] = pValue;
    }
    m_database = new DatabaseManager(m_assetPaths["database_path"]);
    if(!m_database->isConnected()){
        ui->label_status->setStyleSheet("color:red;");
        ui->label_status->setText("Veritabanına bağlanılamadı.");
        ui->pushButton->setEnabled(false);
    }
}

ParkYerim::~ParkYerim()
{
    delete ui;
    if(m_database) delete m_database;
    if(m_user) delete m_user;
}

QMap<QString, QString> ParkYerim::getAssetPaths()
{
    return m_assetPaths;
}


void ParkYerim::on_pushButton_clicked()
{
    if(validateLoginInfo()) launchProgram();
}

bool ParkYerim::validateLoginInfo()
{
    return true;
}

void ParkYerim::launchProgram()
{
    ApplicationWindow* appwindow = new ApplicationWindow(m_database,this);
    this->hide();
    appwindow->show();
}
