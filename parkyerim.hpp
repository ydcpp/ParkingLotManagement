#ifndef PARKYERIM_HPP
#define PARKYERIM_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ParkYerim; }
QT_END_NAMESPACE

class ParkYerim : public QMainWindow
{
    Q_OBJECT

public:
    ParkYerim(QWidget *parent = nullptr);
    ~ParkYerim();

private:
    Ui::ParkYerim *ui;
};
#endif // PARKYERIM_HPP
