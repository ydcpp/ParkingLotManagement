#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LOGGER_HPP
