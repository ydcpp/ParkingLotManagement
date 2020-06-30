#ifndef TOTALINCOMES_HPP
#define TOTALINCOMES_HPP

#include <QDialog>



class DatabaseManager;

namespace Ui {
class TotalIncomes;
}

class TotalIncomes : public QDialog
{
    Q_OBJECT

public:
    explicit TotalIncomes(DatabaseManager* dbmanager, QWidget *parent);
    ~TotalIncomes();

    [[nodiscard]] float GetMonthlyIncomeAmount();
    [[nodiscard]] float GetWeeklyIncomeAmount();
    [[nodiscard]] float GetDailyIncomeAmount();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::TotalIncomes *ui;
    DatabaseManager* m_dbmanager;
};

#endif // TOTALINCOMES_HPP
