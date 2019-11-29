#ifndef PARKYERIM_HPP
#define PARKYERIM_HPP

#include <QMainWindow>
#include "applicationwindow.hpp"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class ParkYerim; }
QT_END_NAMESPACE

class ParkYerim : public QMainWindow
{
    Q_OBJECT

public:
    ParkYerim(QWidget *parent = nullptr);
    ~ParkYerim();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ParkYerim *ui;
    ApplicationWindow* appwindow = nullptr;

    bool validateLoginInfo();
    void launchProgram();
};
#endif // PARKYERIM_HPP
