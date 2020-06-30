#ifndef NEWUSER_HPP
#define NEWUSER_HPP

#include <QDialog>



class DatabaseManager;

namespace Ui {
class NewUser;
}

class NewUser : public QDialog
{
    Q_OBJECT

public:
    explicit NewUser(DatabaseManager* dbmanager, QWidget *parent);
    ~NewUser();


private slots:
    void on_pushButton_submit_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::NewUser *ui;
    DatabaseManager* m_dbmanager;

    [[nodiscard]] bool validateForm();
};

#endif // NEWUSER_HPP
