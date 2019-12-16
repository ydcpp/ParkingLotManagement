#ifndef SETTINGSPANEL_HPP
#define SETTINGSPANEL_HPP

#include <QDialog>

class PricingPlan;
class DatabaseManager;
class ApplicationWindow;

namespace Ui {
class SettingsPanel;
}

class SettingsPanel : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsPanel(DatabaseManager* dbmanager,QList<PricingPlan*>& plans,ApplicationWindow *parent);
    ~SettingsPanel();

private slots:

    void on_pushButton_cancel_clicked();

private:
    Ui::SettingsPanel *ui;
    QList<PricingPlan*> m_plans;
    DatabaseManager* m_dbmanager = nullptr;

};

#endif // SETTINGSPANEL_HPP
