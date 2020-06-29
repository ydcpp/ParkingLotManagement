#ifndef VEHICLESEARCH_HPP
#define VEHICLESEARCH_HPP

#include <QDialog>

class DatabaseManager;
class QSqlQueryModel;
class QSortFilterProxyModel;

namespace Ui {
class VehicleSearch;
}

class VehicleSearch : public QDialog
{
    Q_OBJECT

public:
    explicit VehicleSearch(DatabaseManager* database, QWidget *parent);
    ~VehicleSearch();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_listAll_clicked();

private:
    Ui::VehicleSearch *ui;
    DatabaseManager* dbmanager{nullptr};
    QSqlQueryModel* m_model{nullptr};
    QSortFilterProxyModel* m_proxymodel{nullptr};

    void clearVehicleInfo();
    void setVehicleInfo(const QString& plate, const QString& model, const QString& color, const QString& type);
};

#endif // VEHICLESEARCH_HPP
