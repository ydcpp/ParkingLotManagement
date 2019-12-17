#ifndef SETTINGSPANEL_HPP
#define SETTINGSPANEL_HPP

#include <QDialog>

class PricingPlan;
class DatabaseManager;
class ApplicationWindow;
class QDoubleValidator;

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

    void on_comboBox_existingplans_currentTextChanged(const QString &arg1);

    void on_comboBox_chooseplan_currentTextChanged(const QString &arg1);

    void on_pushButton_changepassword_clicked();

    void on_checkBox_copyexistingplan_stateChanged(int arg1);

    void on_pushButton_enablechange_clicked();

    void on_pushButton_setdefaultplan_clicked();

    void on_pushButton_saveplan_clicked();

    void on_pushButton_createnewplan_clicked();

    void on_comboBox_existingplans_2_currentTextChanged(const QString &arg1);

    void on_pushButton_deleteplan_clicked();

private:
    Ui::SettingsPanel *ui;
    QList<PricingPlan*> m_plans;
    DatabaseManager* m_dbmanager = nullptr;
    ApplicationWindow* m_parent = nullptr;
    QDoubleValidator* m_doublevalidator = nullptr;
    bool m_editingEnabled = false;
    QPixmap m_unlocked = QPixmap(":/Images/assets/images/open-lock-green.png");
    QPixmap m_locked = QPixmap(":/Images/assets/images/closed-lock-red.png");

    void loadUserData();
    void loadPlanList();
    void clearPriceList();
    void setErrorMessage(QString message);
    void setSuccessMessage(QString message);
    void setEditingEnabled(bool enabled);
};

#endif // SETTINGSPANEL_HPP
