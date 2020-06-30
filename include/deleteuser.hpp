#ifndef DELETEUSER_HPP
#define DELETEUSER_HPP

#include <QDialog>



class DatabaseManager;

namespace Ui {
class DeleteUser;
}

class DeleteUser : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteUser(DatabaseManager* dbmanager, QWidget *parent);
    ~DeleteUser();

private slots:
    void on_pushButton_delete_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::DeleteUser *ui;
    DatabaseManager* m_dbmanager;

    [[nodiscard]] bool validateForm();
};

#endif // DELETEUSER_HPP
