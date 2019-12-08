#ifndef MANUELARACCIKIS_HPP
#define MANUELARACCIKIS_HPP

#include <QWidget>

namespace Ui {
class ManuelAracCikis;
}

class ManuelAracCikis : public QWidget
{
    Q_OBJECT

public:
    explicit ManuelAracCikis(QWidget *parent = nullptr);
    ~ManuelAracCikis();

private:
    Ui::ManuelAracCikis *ui;
};

#endif // MANUELARACCIKIS_HPP
