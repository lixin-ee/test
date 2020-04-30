#include "snake.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Snake w;
    w.show();

    //change without pull request
    return a.exec();
}
