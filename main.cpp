#include "climatempo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClimaTempo w;
    w.show();

    return a.exec();
}
