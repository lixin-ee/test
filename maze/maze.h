#ifndef MAZE_H
#define MAZE_H

#include <QWidget>
#include<QMovie>
#include<QLabel>
#include<QIcon>
#include<QTimer>
#include<QPushButton>
#include<QVector>
#include<QLayout>
#include<QPixmap>
#include<QMovie>
#include<QObject>
#include<QLCDNumber>
#include<QKeyEvent>
#include<QString>
#include<QFont>
#include<QDialog>
#include<QSlider>
#include<cstdlib>
#include<ctime>
#define Label_Size  30
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class maze; }
QT_END_NAMESPACE
enum Label{
    wall_label,cat_label,mouse_label,food_label,ground_label
};
struct square
{
    int type;
    int X;
    int Y;
    int path;
    QLabel *label;
};
class maze : public QWidget
{
    Q_OBJECT

public:
    maze(QWidget *parent = nullptr);
    void gameover(int,int);
    void destructwall();
    void RandestructWall();
    void movecat();
    void structface();
    void keyPressEvent(QKeyEvent *event);
    void resizewindow();
    ~maze();
private slots:
    //void findpath();这个可以看情况做不做，如果太难实现就不做了，主要负责寻路，类似提示路线；
   void startgame1();
   void startgame2();
    void startgame3();
    void replay();
    void returnhome();
    void initgame();
    void settingslot();
    void updatetimer();
    void movemouse();
    void movemouse2();
    void movemouse3();
    void walk();
private:
    Ui::maze *ui;
    QPushButton* setting;
    QTimer* counttimer;
    QPushButton* start1;
    QPushButton* start2;
    QPushButton* start3;
    QLabel* Clabel;
    QPushButton* Return;
    QPushButton* Replay;
    QLCDNumber* printtime;
    QLabel* clock1;
    QLabel* clock2;
    square*cat;
    square*mouse;
    square*food;
    QMovie* mousegif;
    QMovie* catgif;
    int dx=1;
    int dy=0;
    int dx1=0;
    int dy1=-1;
    int MX=41;
    int MY=31;
    int gametime;
    QVector<square*>wall;
    square*** allsquare=nullptr;
    QVector<square*>ground;
    QVector<square*>change;

};
static int gamesta=0;
#endif // MAZE_H
