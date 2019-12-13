#include "logger.hpp"

Logger::Logger(QString filepath, QObject *parent) : QObject(parent)
{
    m_filepath = filepath;
}
