#ifndef KULLANICISIL_HPP
#define KULLANICISIL_HPP

#include <QWidget>

namespace Ui {
class KullaniciSil;
}

class KullaniciSil : public QWidget
{
    Q_OBJECT

public:
    explicit KullaniciSil(QWidget *parent = nullptr);
    ~KullaniciSil();

private:
    Ui::KullaniciSil *ui;
};

#endif // KULLANICISIL_HPP
