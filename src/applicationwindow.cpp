#include "applicationwindow.hpp"
#include "ui_applicationwindow.h"

#include <QMessageBox>
#include <QTimer>
#include <QGraphicsScene>
#include <QPushButton>

#include <QDebug>


ApplicationWindow::ApplicationWindow(DatabaseManager* dbmanager, User* user, Logger* logger, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationWindow) , m_dbmanager(dbmanager), m_currentuser(user), m_logger(logger)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    initializeAssetPaths();
    setupIcons();
    if(m_dbmanager->SetOtoparkInfo(&m_otoparkInfo)){
        m_threadManager = ThreadManager::getInstance(this,ui->camera_vehicle_in,ui->camera_vehicle_out);
        SetupTCPConnection();
        setupCustomComponents();
    }else{
        statusMessageError("PROGRAM VERİLERİ DÜZGÜN YÜKLENEMEDİ, LÜTFEN PROGRAMI YENİDEN BAŞLATIN.",-1);
    }
}

ApplicationWindow::~ApplicationWindow()
{
    m_client->terminateConnection();
    m_client->releaseInstance();
    m_threadManager->ReleaseInstance();
    for(PricingPlan* plan : m_pricingPlans) if(plan) delete plan;
    if(m_otoparkInfo) delete m_otoparkInfo;
    delete ui;
}

void ApplicationWindow::ClearVehicleInStats()
{
    ui->lineEdit_in_plate->setText("");
    ui->lineEdit_in_color->setText("");
    ui->lineEdit_in_model->setText("");
    ui->lineEdit_in_type->setText("");
}

void ApplicationWindow::ClearVehicleOutStats()
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

QMap<QString, QString> ApplicationWindow::GetAssetPaths()
{
    return m_assetPaths;
}

DatabaseManager *ApplicationWindow::GetDBManager()
{
    return m_dbmanager;
}

User *ApplicationWindow::GetCurrentUser()
{
    return m_currentuser;
}

void ApplicationWindow::updateRemainingSpots(const qint32& value)
{
    m_remainingSpots = value;
    ui->lcdNumber_freespacecount->display(m_remainingSpots);
    if(m_remainingSpots <= 10) ui->lcdNumber_freespacecount->setStyleSheet("color:red;");
    else if(m_remainingSpots > 30) ui->lcdNumber_freespacecount->setStyleSheet("color:black;");
    else ui->lcdNumber_freespacecount->setStyleSheet("color:orange;");
}

void ApplicationWindow::increaseRemainingSpotCount()
{
    updateRemainingSpots(m_remainingSpots+1);
    m_dbmanager->IncreaseRemainingSpot();
}

void ApplicationWindow::decreaseRemainingSpotCount()
{
    updateRemainingSpots(m_remainingSpots-1);
    m_dbmanager->DecreaseRemainingSpot();
}

void ApplicationWindow::on_socketStateChanged(const QAbstractSocket::SocketState& socketState)
{
    ui->pushButton_reconnect->setVisible(false);
    QString status = "";
    switch (socketState) {
    case QAbstractSocket::ConnectedState:
        ui->label_connectionstatus->setStyleSheet("color:green;");
        ui->label_connectionstatus->setText("BAĞLANDI");
        break;
    case QAbstractSocket::UnconnectedState:
        ui->label_connectionstatus->setStyleSheet("color:red;");
        status += "BAĞLANTI KESİLDİ  (";
        status.append(m_client->getLastError());
        status.append(")");
        ui->label_connectionstatus->setText(status);
        ui->pushButton_reconnect->setVisible(true);
        break;
    default:
        ui->label_connectionstatus->setStyleSheet("color:orange;");
        ui->label_connectionstatus->setText(QVariant::fromValue(socketState).toString());
        break;
    }
}

void ApplicationWindow::onTCPErrorReceived(const QString& err)
{
    ui->label_connectionstatus->setStyleSheet("color:red;");
    ui->label_connectionstatus->setText(err);
}

void ApplicationWindow::onPricingPlansUpdated()
{
    for(PricingPlan* plan : m_pricingPlans){
        if(plan){
            delete plan;
            plan = nullptr;
        }
    }
    m_pricingPlans.clear();
    QString errmsg;
    if(!m_dbmanager->GetPricingPlans(m_pricingPlans,errmsg)) statusMessageError(errmsg,5000);
    else{
        for(PricingPlan* plan : m_pricingPlans){
            if(m_otoparkInfo->getCurrentPlanID() == plan->GetPlanID()){
                currentPricingPlan = plan;
                ui->label_currentPlan->setText(currentPricingPlan->GetPlanName());
                break;
            }
        }
        if(!currentPricingPlan) statusMessageError("Geçerli ücretlendirme planı veritabanında bulunamadı.",5000);
    }
}

void ApplicationWindow::getCalculatedPrice(const qint64& minutes, const qint32& planid, float& out_price, QString& out_PlanName)
{
    bool planFound = false;
    for(PricingPlan* plan : m_pricingPlans){
        if(planid == plan->GetPlanID()){
            planFound = true;
            out_PlanName = plan->GetPlanName();
            out_price = plan->CalculatePrice(minutes);
            break;
        }
    }
    if(!planFound){
        for(PricingPlan* plan : m_pricingPlans){
            if(plan->GetPlanID() == 0){
                out_PlanName = plan->GetPlanName();
                out_price = plan->CalculatePrice(minutes);
            }
        }
    }
}

void ApplicationWindow::statusMessageSuccess(const QString& text, const qint32& milliseconds)
{
    ui->label_status->setText(text);
    ui->label_status->setStyleSheet("color:green;");
    QTimer::singleShot(milliseconds,ui->label_status,[&](){
        ui->label_status->clear();
        ui->label_status->setStyleSheet("color:black;");
    });
}

void ApplicationWindow::statusMessageError(const QString& text, const qint32& milliseconds)
{
    ui->label_status->setText(text);
    ui->label_status->setStyleSheet("color:red;");
    QTimer::singleShot(milliseconds,ui->label_status,[&](){
        ui->label_status->clear();
        ui->label_status->setStyleSheet("color:black;");
    });
}

void ApplicationWindow::onCamDeviceUpdated_in(QVariant device)
{
    m_threadManager->updateCameraDevice_in(device);
}

void ApplicationWindow::onCamDeviceUpdated_out(QVariant device)
{
    m_threadManager->updateCameraDevice_out(device);
}

void ApplicationWindow::drawCamInput_vehicle_in(QPixmap pixmap)
{
    //pixmap = pixmap.scaled(ui->label_vehicle_in->width(),ui->label_vehicle_in->height());
    //ui->label_vehicle_in->setPixmap(pixmap);
}

void ApplicationWindow::drawCamInput_vehicle_out(QPixmap pixmap)
{
    //pixmap = pixmap.scaled(ui->label_vehicle_out->width(),ui->label_vehicle_out->height());
    //ui->label_vehicle_out->setPixmap(pixmap);
}

void ApplicationWindow::displayLicensePlateString_vehicle_in(const QString& plate)
{
    ui->lineEdit_in_plate->setText(plate);
}

void ApplicationWindow::displayLicensePlateString_vehicle_out(const QString& plate)
{
    ui->lineEdit_out_plate->setText(plate);
}

void ApplicationWindow::openCameraStream_in()
{
    ui->label_cam_in_status->setStyleSheet("color:green;");
    ui->label_cam_in_status->setText("Kamera açık");
    ui->camera_vehicle_in->setVisible(true);
    ui->pushButton_plakatani_in->setEnabled(true);
}

void ApplicationWindow::closeCameraStream_in()
{
    ui->label_cam_in_status->setStyleSheet("color:red;");
    ui->label_cam_in_status->setText("Kamera kapalı");
    ui->camera_vehicle_in->setVisible(false);
    ui->pushButton_plakatani_in->setEnabled(false);
}

void ApplicationWindow::openCameraStream_out()
{
    ui->label_cam_out_status->setStyleSheet("color:green;");
    ui->label_cam_out_status->setText("Kamera açık");
    ui->camera_vehicle_out->setVisible(true);
    ui->pushButton_plakatani_out->setEnabled(true);
}

void ApplicationWindow::closeCameraStream_out()
{
    ui->label_cam_out_status->setStyleSheet("color:red;");
    ui->label_cam_out_status->setText("Kamera kapalı");
    ui->camera_vehicle_out->setVisible(false);
    ui->pushButton_plakatani_out->setEnabled(false);
}


QList<PricingPlan *>& ApplicationWindow::GetPricingPlanList()
{
    return m_pricingPlans;
}

void ApplicationWindow::updateCurrentPlan(const qint32& planID)
{
    QString errormsg;
    if(!m_dbmanager->UpdateCurrentPricingPlan(planID,errormsg)){
        statusMessageError(errormsg,5000);
        return;
    }
    m_otoparkInfo->setCurrentPlanID(planID);
    for(PricingPlan* plan : m_pricingPlans){
        if(m_otoparkInfo->getCurrentPlanID() == plan->GetPlanID()){
            currentPricingPlan = plan;
            break;
        }
    }
    ui->label_currentPlan->setText(currentPricingPlan->GetPlanName());
}

OtoparkInfo* ApplicationWindow::getOtoparkInfo()
{
    return m_otoparkInfo;
}

void ApplicationWindow::on_toolButton_quit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Çıkış", "Programı kapatmak istediğinizden emin misiniz?", QMessageBox::Yes|QMessageBox::Cancel);
    if(reply == QMessageBox::Yes){
        emit terminateAllThreads();
        QApplication::quit();
    }
}

void ApplicationWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("HH:mm");
    if ((time.second() % 2) == 0) text[2] = ' ';
    ui->lcdNumber->display(text);
}

void ApplicationWindow::enableToggleCameraButton()
{
    ui->pushButton_toggleCameras->setEnabled(true);
}

void ApplicationWindow::on_toolButton_vehicle_in_clicked()
{
    m_window_vehicle_in = new ManualVehicleEntry(m_dbmanager,m_otoparkInfo->getCurrentPlanID(),this);
    connect(m_window_vehicle_in,&ManualVehicleEntry::decreaseCount,this,&ApplicationWindow::decreaseRemainingSpotCount);
    m_window_vehicle_in->exec();
}

void ApplicationWindow::on_toolButton_vehicle_out_clicked()
{
    m_window_vehicle_out = new ManualVehicleExit(m_dbmanager,this);
    connect(m_window_vehicle_out,&ManualVehicleExit::getCalculatedPrice,this,&ApplicationWindow::getCalculatedPrice);
    connect(m_window_vehicle_out,&ManualVehicleExit::increaseCount,this,&ApplicationWindow::increaseRemainingSpotCount);
    m_window_vehicle_out->exec();
}

void ApplicationWindow::initializeAssetPaths()
{
    // setting up asset paths
    for(QString s : m_params)
    {
        QList<QString> param = s.split(',' , QString::SkipEmptyParts);
        QString pName = param[0].trimmed();
        QString pValue = param[1].trimmed();
        m_assetPaths[pName] = pValue;
    }
}

void ApplicationWindow::setupIcons()
{
    // setting up icons
    ui->toolButton_quit->setIcon(QIcon(m_assetPaths["icon_close"]));
    ui->toolButton_settings->setIcon(QIcon(m_assetPaths["icon_settings"]));
    ui->toolButton_adminpanel->setIcon(QIcon(m_assetPaths["icon_adminpanel"]));
    ui->toolButton_vehicle_in->setIcon(QIcon(m_assetPaths["icon_vehicle_in"]));
    ui->toolButton_vehicle_out->setIcon(QIcon(m_assetPaths["icon_vehicle_out"]));
    ui->pushButton_search->setIcon(QIcon(m_assetPaths["icon_search"]));
    ui->pushButton_parkingSpots->setIcon(QIcon(m_assetPaths["icon_parkingspot"]));
    ui->pushButton_currentPlanDetails->setIcon(QIcon(m_assetPaths["icon_list"]));
    ui->pushButton_toggleCameras->setIcon(QIcon(m_assetPaths["icon_camera"]));
}

void ApplicationWindow::SetupTCPConnection()
{
    ui->pushButton_reconnect->setVisible(false);
    m_client = TCPClient::getInstance(m_otoparkInfo->getServerIP(),m_otoparkInfo->getServerPort(),m_otoparkInfo->getServerOtoparkID(),m_dbmanager);
    m_client->startConnection();
    connect(m_client,&TCPClient::stateChanged,this,&ApplicationWindow::on_socketStateChanged);
    connect(m_client,&TCPClient::sendError,this,&ApplicationWindow::onTCPErrorReceived);
    connect(m_client,&TCPClient::sig_successMessage,this,&ApplicationWindow::statusMessageSuccess);
    connect(m_client,&TCPClient::sig_errorMessage,this,&ApplicationWindow::statusMessageError);
}

void ApplicationWindow::setupCustomComponents()
{
    // setting up digital clock
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ApplicationWindow::showTime);
    timer->start(1000);
    showTime();

    // setting up admin panel button
    ui->label_user->setText(m_currentuser->getFirstName() + " " + m_currentuser->getLastName());
    if(m_currentuser->getUserType() < 2) ui->toolButton_adminpanel->setEnabled(false);

    // setting up pricing plans
    QString errmsg;
    if(!m_dbmanager->GetPricingPlans(m_pricingPlans,errmsg)) ui->label_status->setText(errmsg);
    else{
        for(PricingPlan* plan : m_pricingPlans){
            if(m_otoparkInfo->getCurrentPlanID() == plan->GetPlanID()){
                currentPricingPlan = plan;
                ui->label_currentPlan->setText(currentPricingPlan->GetPlanName());
                break;
            }
        }
        if(!currentPricingPlan) statusMessageError("Geçerli ücretlendirme planı veritabanında bulunamadı.",5000);
    }

    // setting up remaining spot count
    QString err;
    int spots = m_dbmanager->QueryRemainingSpots(err);
    if(spots == -1) qDebug() << err;
    else updateRemainingSpots(spots);
}


void ApplicationWindow::on_toolButton_adminpanel_clicked()
{
    m_window_admin = new AdminPanel(m_dbmanager,this);
    m_window_admin->show();
}

void ApplicationWindow::on_toolButton_settings_clicked()
{
    m_window_settings = new SettingsPanel(m_dbmanager,m_pricingPlans,this);
    connect(m_window_settings,&SettingsPanel::sig_PricingPlansUpdated,this,&ApplicationWindow::onPricingPlansUpdated);
    connect(m_window_settings,&SettingsPanel::sig_CamDeviceUpdated_in,this,&ApplicationWindow::onCamDeviceUpdated_in);
    connect(m_window_settings,&SettingsPanel::sig_CamDeviceUpdated_out,this,&ApplicationWindow::onCamDeviceUpdated_out);
    m_window_settings->exec();
}

void ApplicationWindow::on_pushButton_search_clicked()
{
    m_window_vehiclesearch = new VehicleSearch(m_dbmanager,this);
    m_window_vehiclesearch->exec();
}

void ApplicationWindow::on_pushButton_currentPlanDetails_clicked()
{
    if(!currentPricingPlan) return;
    m_window_currentplan = new CurrentPlanWindow(currentPricingPlan,this);
    m_window_currentplan->exec();
}

void ApplicationWindow::on_pushButton_parkingSpots_clicked()
{

}

void ApplicationWindow::on_pushButton_toggleCameras_clicked()
{
    if(!m_threadManager) return;
    ui->pushButton_toggleCameras->setEnabled(false);
    m_isCameraInputOn = !m_isCameraInputOn;
    if(m_isCameraInputOn){
        // toggle camera input on
        emit m_threadManager->startThreads();
        //m_threadManager->startCameraSystem();
        QTimer::singleShot(2000,this,&ApplicationWindow::enableToggleCameraButton);
    }else{
        // toggle camera input off
        emit stopAllThreads();
        QTimer::singleShot(2000,this,&ApplicationWindow::enableToggleCameraButton);

    }
}

void ApplicationWindow::on_pushButton_plakatani_in_clicked()
{
    emit recognizePlate_in();
}

void ApplicationWindow::on_pushButton_plakatani_out_clicked()
{
    emit recognizePlate_out();
}

void ApplicationWindow::on_pushButton_reconnect_clicked()
{
    if(!m_client) return;
    m_client->terminateConnection();
    m_client->startConnection();
}

