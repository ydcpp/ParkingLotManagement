#ifndef SETTINGSPANEL_HPP
#define SETTINGSPANEL_HPP

#include <QDialog>

#include <QMediaService>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraInfo>

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
    explicit SettingsPanel(DatabaseManager* dbmanager,QVector<PricingPlan*>& plans,ApplicationWindow *parent);
    ~SettingsPanel();

signals:
    void sig_PricingPlansUpdated();
    void sig_CamDeviceUpdated_in(QVariant camdata);
    void sig_CamDeviceUpdated_out(QVariant camdata);

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

    void on_pushButton_savecamera_in_clicked();


private slots:
    void loadUserData();
    void loadPlanList();
    void clearPriceList();
    void setErrorMessage(const QString& message);
    void setSuccessMessage(const QString& message);
    void setEditingEnabled(const bool& enabled);
    void loadCameraList();
    void on_comboBox_cam_in_activated(int index);

    void on_comboBox_cam_out_activated(int index);

private:
    Ui::SettingsPanel *ui;
    QVector<PricingPlan*> m_plans;
    DatabaseManager* m_dbmanager{nullptr};
    ApplicationWindow* m_parent{nullptr};
    QDoubleValidator* m_doublevalidator{nullptr};
    bool m_editingEnabled = false;
    QPixmap m_unlocked {QPixmap(":/Images/assets/images/open-lock-green.png")};
    QPixmap m_locked {QPixmap(":/Images/assets/images/closed-lock-red.png")};
    QList<QCameraInfo> m_availableCameras;
    QCamera* m_camera_in{nullptr};
    QCamera* m_camera_out{nullptr};

};

#endif // SETTINGSPANEL_HPP
