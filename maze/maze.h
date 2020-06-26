#ifndef MAZE_H
#define MAZE_H

#include<QLineEdit>
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
#include<QRadioButton>
#include<QPropertyAnimation>
#include<QSound>
#include<QCheckBox>
#include<QTcpSocket>
#include <QTableView>
#include <QStandardItemModel>
#define Label_Size  30
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class maze; }
QT_END_NAMESPACE
enum Label{
    wall_label,cat_label,mouse_label,food_label,ground_label,hammer_label,egg_label,jia_label,x_label
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
    void generateham();
    void generateegg();
    void generatejia();
    void walk();
    void present();
    void dwall();
    void aboutus();
    void jiaHint(int);
    void hamHint(int);
    void cdHint(int);
    void mainscreen();
    void rank_();
    void aboutme_();
    //void exit();
  private:
    Ui::maze *ui;
    QPushButton* setting;
    QTimer* counttimer;
    QPushButton* start1;
    QPushButton* start2;
    QPushButton* start3;
    QPushButton* back;
    QLabel* Clabel;
    QPushButton* Return;
    QPushButton* Replay;
    QPushButton* rank;
    QPushButton* aboutme;
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
    int screen_width;
    int screen_height;
    square*** allsquare=nullptr;
    QVector<square*>change;
    QTimer *cattimer;
    QPushButton* presentation;
    QTimer* ptimer;
    QPixmap*hammer;
    QPixmap*egg;
    QPixmap*jia;
    QPixmap* xl=nullptr;
    QSound* so;
    int dtype=2;
    bool denglu=0;
    QTimer* xtimer;
    QString name;
    QTcpSocket* mysocket;
    int pace=0;
    QPushButton* xiugai;

};
static int gamesta=0;
static int havehammer=0;
static int seekegg=0;
static int getstuck=0;
#endif // MAZE_H
