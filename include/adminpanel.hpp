#ifndef ADMINPANEL_HPP
#define ADMINPANEL_HPP

#include "newuser.hpp"
#include "deleteuser.hpp"
#include "totalincomes.hpp"

#include <QWidget>


class DatabaseManager;
class QSqlQueryModel;
class QSortFilterProxyModel;

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPanel(DatabaseManager* dbmanager, QWidget *parent = nullptr);
    ~AdminPanel();

    void keyPressEvent(QKeyEvent* e);

private slots:

    void on_pushButton_close_clicked();

    void on_pushButton_employees_clicked();

    void on_pushButton_managers_clicked();

    void on_pushButton_newUser_clicked();

    void on_pushButton_deleteUser_clicked();

    void on_pushButton_incomes_clicked();

    void on_pushButton_payments_clicked();

protected slots:

    void updateStatusText(QString text, qint32 milliseconds);
    void statusMessageSuccess(QString text, qint32 milliseconds);
    void statusMessageError(QString text, qint32 milliseconds);

private:
    Ui::AdminPanel *ui;
    DatabaseManager* m_dbmanager = nullptr;
    NewUser* window_yenikullanici = nullptr;
    DeleteUser* window_kullaniciSil = nullptr;
    TotalIncomes* window_toplamGelirler = nullptr;
    QSqlQueryModel* m_model = nullptr;
    QSortFilterProxyModel* m_proxymodel = nullptr;
};

#endif // ADMINPANEL_HPP
