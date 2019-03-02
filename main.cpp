#include "solve.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Solve w;
    w.show();

    return a.exec();
}
