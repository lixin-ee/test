#include "maze.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    maze w;
    w.show();
    return a.exec();
}
