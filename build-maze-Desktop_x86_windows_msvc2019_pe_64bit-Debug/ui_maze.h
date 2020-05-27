/********************************************************************************
** Form generated from reading UI file 'maze.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAZE_H
#define UI_MAZE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_maze
{
public:

    void setupUi(QWidget *maze)
    {
        if (maze->objectName().isEmpty())
            maze->setObjectName(QString::fromUtf8("maze"));
        maze->resize(815, 606);
        maze->setMaximumSize(QSize(16777215, 16777215));

        retranslateUi(maze);

        QMetaObject::connectSlotsByName(maze);
    } // setupUi

    void retranslateUi(QWidget *maze)
    {
        maze->setWindowTitle(QCoreApplication::translate("maze", "maze", nullptr));
    } // retranslateUi

};

namespace Ui {
    class maze: public Ui_maze {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAZE_H
