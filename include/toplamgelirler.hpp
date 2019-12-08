#ifndef TOPLAMGELIRLER_HPP
#define TOPLAMGELIRLER_HPP

#include <QWidget>

namespace Ui {
class ToplamGelirler;
}

class ToplamGelirler : public QWidget
{
    Q_OBJECT

public:
    explicit ToplamGelirler(QWidget *parent = nullptr);
    ~ToplamGelirler();

private:
    Ui::ToplamGelirler *ui;
};

#endif // TOPLAMGELIRLER_HPP
