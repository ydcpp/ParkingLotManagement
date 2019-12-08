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

private:
    Ui::AdminPanel *ui;
};

#endif // ADMINPANEL_HPP
