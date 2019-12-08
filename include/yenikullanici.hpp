#ifndef YENIKULLANICI_HPP
#define YENIKULLANICI_HPP

#include <QWidget>

namespace Ui {
class YeniKullanici;
}

class YeniKullanici : public QWidget
{
    Q_OBJECT

public:
    explicit YeniKullanici(QWidget *parent = nullptr);
    ~YeniKullanici();

private:
    Ui::YeniKullanici *ui;
};

#endif // YENIKULLANICI_HPP
