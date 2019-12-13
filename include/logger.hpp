#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QString filepath, QObject *parent = nullptr);

signals:

public slots:

private:
    QString m_filepath;
};

#endif // LOGGER_HPP
