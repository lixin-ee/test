#include "maze.h"
#include<QScreen>
#include <QDebug>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    maze w;
    w.show();
    return a.exec();
}
