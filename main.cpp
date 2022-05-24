#include "tankwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TankWindow w;
    w.show();
    return a.exec();
}
