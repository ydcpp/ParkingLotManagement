#include "settingspanel.hpp"
#include "ui_settingspanel.h"


#include "databasemanager.hpp"


SettingsPanel::SettingsPanel(DatabaseManager* dbmanager, QList<PricingPlan*>& plans, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsPanel)
{
    ui->setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    m_dbmanager = dbmanager;
    m_plans = plans;
}

SettingsPanel::~SettingsPanel()
{
    delete ui;
}
