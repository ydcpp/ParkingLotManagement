#ifndef ADMINPANEL_HPP
#define ADMINPANEL_HPP

#include <QWidget>

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPanel(QWidget *parent = nullptr);
    ~AdminPanel();

private slots:

    void on_pushButton_close_clicked();

    void on_pushButton_employees_clicked();

    void on_pushButton_managers_clicked();

private:
    Ui::AdminPanel *ui;
};

#endif // ADMINPANEL_HPP
