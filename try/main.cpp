#include "mainwindow.h"
#include <QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     QLabel label("Hello, world");
     label.show();
    return a.exec();
    //123
}
