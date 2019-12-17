#include "settingspanel.hpp"
#include "ui_settingspanel.h"


#include "databasemanager.hpp"
#include "applicationwindow.hpp"

#include <QTimer>
#include <QDoubleValidator>


SettingsPanel::SettingsPanel(DatabaseManager* dbmanager, QList<PricingPlan*>& plans, ApplicationWindow *parent) :
    QDialog(parent),
    ui(new Ui::SettingsPanel)
{
    ui->setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    m_dbmanager = dbmanager;
    m_plans = plans;
    m_parent = parent;
    loadUserData();
    loadPlanList();
    ui->label_changeicon->setPixmap(m_locked.scaled(ui->label_changeicon->width(),ui->label_changeicon->height()));
}

SettingsPanel::~SettingsPanel()
{
    delete ui;
}

void SettingsPanel::on_comboBox_existingplans_currentTextChanged(const QString &arg1)
{

}

void SettingsPanel::on_comboBox_chooseplan_currentTextChanged(const QString &arg1)
{
    ui->pushButton_setdefaultplan->setEnabled(false);
    ui->groupBox_newplan->setEnabled(false);
    if(arg1 == "Yeni Plan Ekle"){
        ui->groupBox_newplan->setEnabled(true);
        clearPriceList();
        return;
    }
    if(arg1 == "Seçiniz..."){
        clearPriceList();
        return;
    }
    for(PricingPlan* plan : m_parent->GetPricingPlanList()){
        if(plan->GetPlanName() == arg1){
            ui->label_currentplanname->setText(arg1);
            float lessthantwo, twothree, threefour, fourfive, fivesix, sixseven, seveneight, eightten, tentwelve, morethantwelve;
            plan->GetPricesPerHour(lessthantwo, twothree, threefour, fourfive, fivesix, sixseven, seveneight, eightten, tentwelve, morethantwelve);
            ui->doubleSpinBox_lessthantwo->setValue(lessthantwo);
            ui->doubleSpinBox_twothree->setValue(twothree);
            ui->doubleSpinBox_threefour->setValue(threefour);
            ui->doubleSpinBox_fourfive->setValue(fourfive);
            ui->doubleSpinBox_fivesix->setValue(fivesix);
            ui->doubleSpinBox_sixseven->setValue(sixseven);
            ui->doubleSpinBox_seveneight->setValue(seveneight);
            ui->doubleSpinBox_eightten->setValue(eightten);
            ui->doubleSpinBox_tentwelve->setValue(tentwelve);
            ui->doubleSpinBox_morethantwelve->setValue(morethantwelve);
            if(plan->GetPlanID() != m_parent->getCurrentPlanID()) ui->pushButton_setdefaultplan->setEnabled(true);
            return;
        }
    }
}

void SettingsPanel::loadUserData()
{
    ui->lineEdit_username->setText(m_parent->GetCurrentUser()->getUsername());
    ui->lineEdit_firstname->setText(m_parent->GetCurrentUser()->getFirstName());
    ui->lineEdit_lastname->setText(m_parent->GetCurrentUser()->getLastName());
    ui->lineEdit_datecreated->setText(m_parent->GetCurrentUser()->getDateCreated().toString());
}

void SettingsPanel::loadPlanList()
{
    QStringList planlist;
    for(PricingPlan* plan : m_parent->GetPricingPlanList()){
        planlist.append(plan->GetPlanName());
    }
    ui->comboBox_existingplans->clear();
    ui->comboBox_existingplans->addItem("Seçiniz...");
    ui->comboBox_existingplans->addItems(planlist);
    ui->comboBox_existingplans->setEnabled(false);
    ui->checkBox_copyexistingplan->setChecked(false);
    ui->comboBox_chooseplan->clear();
    ui->comboBox_chooseplan->addItem("Seçiniz...");
    ui->comboBox_chooseplan->addItems(planlist);
    ui->comboBox_chooseplan->addItem("Yeni Plan Ekle");
}

void SettingsPanel::clearPriceList()
{
    ui->doubleSpinBox_lessthantwo->clear();
    ui->doubleSpinBox_twothree->clear();
    ui->doubleSpinBox_threefour->clear();
    ui->doubleSpinBox_fourfive->clear();
    ui->doubleSpinBox_fivesix->clear();
    ui->doubleSpinBox_sixseven->clear();
    ui->doubleSpinBox_seveneight->clear();
    ui->doubleSpinBox_eightten->clear();
    ui->doubleSpinBox_tentwelve->clear();
    ui->doubleSpinBox_morethantwelve->clear();
    ui->doubleSpinBox_newplanprice->clear();
}

void SettingsPanel::setErrorMessage(QString message)
{
    ui->label_status->setStyleSheet("color:red;");
    ui->label_status->setText(message);
    QTimer::singleShot(3000,ui->label_status,&QLabel::clear);
}

void SettingsPanel::setSuccessMessage(QString message)
{
    ui->label_status->setStyleSheet("color:green;");
    ui->label_status->setText(message);
    QTimer::singleShot(3000,ui->label_status,&QLabel::clear);
}

void SettingsPanel::setEditingEnabled(bool enabled)
{
    m_editingEnabled = enabled;
    ui->doubleSpinBox_lessthantwo->setReadOnly(!enabled);
    ui->doubleSpinBox_twothree->setReadOnly(!enabled);
    ui->doubleSpinBox_threefour->setReadOnly(!enabled);
    ui->doubleSpinBox_fourfive->setReadOnly(!enabled);
    ui->doubleSpinBox_fivesix->setReadOnly(!enabled);
    ui->doubleSpinBox_sixseven->setReadOnly(!enabled);
    ui->doubleSpinBox_seveneight->setReadOnly(!enabled);
    ui->doubleSpinBox_eightten->setReadOnly(!enabled);
    ui->doubleSpinBox_tentwelve->setReadOnly(!enabled);
    ui->doubleSpinBox_morethantwelve->setReadOnly(!enabled);
    if(enabled) ui->label_changeicon->setPixmap(m_unlocked.scaled(ui->label_changeicon->width(),ui->label_changeicon->height()));
    else ui->label_changeicon->setPixmap(m_locked.scaled(ui->label_changeicon->width(),ui->label_changeicon->height()));
}

void SettingsPanel::on_pushButton_changepassword_clicked()
{
    // form validation
    if(ui->lineEdit_acc_currentpw->text() != m_parent->GetCurrentUser()->getCurrentPassword()){
        setErrorMessage("Hatalı şifre.");
        return;
    }
    if(ui->lineEdit_acc_newpw->text().isEmpty()){
        setErrorMessage("Yeni şifreyi girin");
        return;
    }
    if(ui->lineEdit_acc_newpw->text() != ui->lineEdit_acc_newpwrepeat->text()){
        setErrorMessage("Şifre tekrarı yanlış girildi.");
        return;
    }
    // database password change update
    QString errormsg;
    QString oldpw = m_parent->GetCurrentUser()->getCurrentPassword();
    QString newpw = ui->lineEdit_acc_newpw->text();
    qint32 accountID = m_parent->GetCurrentUser()->getAccountID();
    if(!m_dbmanager->ChangePassword(accountID,oldpw,newpw,errormsg)){
        ui->label_status->setText(errormsg);
        return;
    }
    // User instance password update
    m_parent->GetCurrentUser()->updatePassword(newpw);
    setSuccessMessage("Şifre değiştirildi.");
}

void SettingsPanel::on_checkBox_copyexistingplan_stateChanged(int arg1)
{
    if(arg1) ui->comboBox_existingplans->setEnabled(true);
    else ui->comboBox_existingplans->setEnabled(false);
}

void SettingsPanel::on_pushButton_enablechange_clicked()
{
    setEditingEnabled(!m_editingEnabled);
}

void SettingsPanel::on_pushButton_setdefaultplan_clicked()
{
    for(PricingPlan* plan : m_parent->GetPricingPlanList()){
        if(ui->label_currentplanname->text() == plan->GetPlanName()){
            m_parent->updateCurrentPlan(plan->GetPlanID());
            ui->pushButton_setdefaultplan->setEnabled(false);
            return;
        }
    }
}

void SettingsPanel::on_pushButton_saveplan_clicked()
{
    clearPriceList();
}
