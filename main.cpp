#include "lottery.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lottery w;
    w.show();

    return a.exec();
}
