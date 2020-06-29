#include "parkyerim.hpp"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ParkYerim w;
    w.show();
    return a.exec();
}
