#ifndef APPLICATIONWINDOW_HPP
#define APPLICATIONWINDOW_HPP

#include <QWidget>
#include <QMap>
#include <QString>

namespace Ui {
class ApplicationWindow;
}

class ApplicationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow();

    QMap<QString,QString> getAssetPaths() const;

private slots:
    void on_toolButton_quit_clicked();

private:
    Ui::ApplicationWindow *ui;
    QMap<QString, QString> m_assetPaths;

    // programda kullanılacak tüm asset'lerin adları ve dosya yolları burada girilmelidir.
    QList<QString> m_params = {
        "icon_close,        ./assets/images/close.png",
        "icon_print,        ./assets/images/print.png",
        "image_background,  ./assets/images/background.jpg"
    };
};

#endif // APPLICATIONWINDOW_HPP
