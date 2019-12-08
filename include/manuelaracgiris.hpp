#ifndef MANUELARACGIRIS_HPP
#define MANUELARACGIRIS_HPP

#include <QWidget>

namespace Ui {
class ManuelAracGiris;
}

class ManuelAracGiris : public QWidget
{
    Q_OBJECT

public:
    explicit ManuelAracGiris(QWidget *parent = nullptr);
    ~ManuelAracGiris();

private:
    Ui::ManuelAracGiris *ui;
};

#endif // MANUELARACGIRIS_HPP
