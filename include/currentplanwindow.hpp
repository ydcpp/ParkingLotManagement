#ifndef CURRENTPLANWINDOW_HPP
#define CURRENTPLANWINDOW_HPP

#include <QDialog>



class PricingPlan;

namespace Ui {
class CurrentPlanWindow;
}

class CurrentPlanWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CurrentPlanWindow(PricingPlan* currentplan, QWidget *parent);
    ~CurrentPlanWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CurrentPlanWindow *ui;

    float n_lessthantwo;
    float n_twothree;
    float n_threefour;
    float n_fourfive;
    float n_fivesix;
    float n_sixseven;
    float n_seveneight;
    float n_eightten;
    float n_tentwelve;
    float n_morethantwelve;

    void SetPrices();
};

#endif // CURRENTPLANWINDOW_HPP
