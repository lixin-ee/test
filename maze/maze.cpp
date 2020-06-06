#include "maze.h"
#include "ui_maze.h"
#include<QScreen>
#include <QApplication>
#define m (MX-2)//row
#define n (MY-2)
#define down 1
#define right 2
#define left 4
#define up 8
#define WALL -1
#define NOTHING 2
struct block
{
        int row, column, direction;
        block(int _row, int _column, int _direction)
        {
            row = _row;
            column = _column;
            direction = _direction;
        }
 };

int x_num , y_num ;//矿工位置
    vector<block> myblock;
    vector<block> Ling;
    bool flag=1;
    bool flag1=1;
    block temp2(0,0,0);
    int td=0;
    int G[100][100];
    int ptime=500;
    //将地图全部置为墙

maze::maze(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::maze)
{
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;
    screen_width = mm.width();
    screen_height = mm.height();
    int temp1=0.7*screen_width/(Label_Size*2);
    MX=2*temp1+1;
    temp1=0.9*screen_height/(Label_Size*2);
    MY=2*temp1-1;
    ui->setupUi(this);
    setWindowIcon(QIcon(":/tubiao.ico"));
    setWindowTitle("maze521");
    Clabel=new QLabel(this);
    start1=new QPushButton(this);
    start2=new QPushButton(this);
    start3=new QPushButton(this);
    setting=new QPushButton(this);
    presentation=new QPushButton(this);
    resizewindow();
    QObject::connect(start1,SIGNAL(clicked()),this,SLOT(startgame1()));
    QObject::connect(start2,SIGNAL(clicked()),this,SLOT(startgame2()));
    QObject::connect(start3,SIGNAL(clicked()),this,SLOT(startgame3()));
    QObject::connect(setting,SIGNAL(clicked()),this,SLOT(settingslot()));
    QObject::connect(presentation,SIGNAL(clicked()),this,SLOT(present()));
    mousegif=new QMovie(":/mouse1.gif");
    QSize s1(Label_Size+5,Label_Size+5);
    catgif=new QMovie(":/cat2.gif");
    QSize s2(Label_Size+10,Label_Size+10);
    mousegif->setScaledSize(s1);
    catgif->setScaledSize(s2);
    hammer=new QPixmap(":/hammer.png");
}
void maze::startgame1()
{

    gamesta=1;
    initgame();
    destructwall();
    gametime =MX*MY*0.2;
    updatetimer();
    counttimer=new QTimer(this);
    QObject::connect(counttimer,SIGNAL(timeout()),this,SLOT(updatetimer()));
    counttimer->start(1000);
    printtime->show();
}
void maze::initgame()//初始化游戏界面
{

    Clabel->hide();
    Clabel->setDisabled(true);
    setting->hide();
    setting->setDisabled(true);
    start1->hide();
    start1->setDisabled(true);
    start2->hide();
    start2->setDisabled(true);
    start3->hide();
    start3->setDisabled(true);
    presentation->hide();
    presentation->setDisabled(true);
    Return=new QPushButton(this);
    Return->setFocusPolicy(Qt::NoFocus);
    Replay=new QPushButton(this);
    Replay->setFocusPolicy(Qt::NoFocus);
    clock1=new QLabel(this);
    clock2=new QLabel(this);
    printtime=new QLCDNumber(this);
    Return->setGeometry(0,MY*Label_Size,2*Label_Size,2*Label_Size);
    Return->setStyleSheet("QPushButton{border-image:url(:/return.png);}"
                          "QPushButton:hover{border-image:url(:/return2.png);}"
                           );
    Replay->setGeometry((MX-2)*Label_Size,MY*Label_Size,2*Label_Size,2*Label_Size);
    Replay->setStyleSheet("QPushButton{border-image:url(:/replay.png);}"
                          "QPushButton:hover{border-image:url(:/replay2.png);}"
                           "QPushButton:pressed{border-image:url(:/replay1.png);}");
    clock1->setGeometry((2*MX/5-2)*Label_Size,MY*Label_Size,2*Label_Size,2*Label_Size);
    clock2->setGeometry(3*MX*Label_Size/5,MY*Label_Size,2*Label_Size,2*Label_Size);
    clock1->setStyleSheet("QLabel{border-image:url(:/time.png);}");
    clock2->setStyleSheet("QLabel{border-image:url(:/time.png);}");
    Return->show();
    Replay->show();
    clock1->show();
    clock2->show();
    printtime->setMode(QLCDNumber::Dec);
    printtime->setDigitCount(4);
    printtime->setGeometry((MX/2-1)*Label_Size,MY*Label_Size,2*Label_Size,2*Label_Size);
    printtime->setStyleSheet("font:50;color:red;");
    printtime->setSegmentStyle(QLCDNumber::Flat);
    printtime->show();
    QObject::connect(Return,SIGNAL(clicked()),this,SLOT(returnhome()));
    QObject::connect(Replay,SIGNAL(clicked()),this,SLOT(replay()));
    //铺地板，铺墙
    structface();
    x_num =2*((rand()%(m+1))/2)+1;
    y_num =2*((rand()%(n+1))/2)+1;
    if(dtype==1)
    {memset(G, WALL, sizeof(G));
        G[x_num][y_num] = NOTHING;}
    if(dtype==2)
    {memset(G, 0, sizeof(G));
    G[x_num][y_num]=1;}

   //定义起始点
}
void maze::returnhome()//返回主界面
{
    for(int i=0;i<MX;i++)
    {
        for (int j=0;j<MY;j++)
        {
           delete allsquare[i][j]->label;
           delete allsquare[i][j];
           allsquare[i][j]=nullptr;
        }
        delete allsquare[i];
    } 
    delete allsquare;
    allsquare=nullptr;
    if(gamesta==3)
    {
        change.clear();
        delete cat->label;
        delete cat;
        delete cattimer;
    }
    Clabel->show();
    Clabel->setDisabled(false);
    setting->show();
    setting->setDisabled(false);
    start1->show();
    start1->setDisabled(false);
    start2->show();
    start2->setDisabled(false);
    start3->show();
    start3->setDisabled(false);
    presentation->show();
    presentation->setDisabled(false);
   if(gamesta==4){delete ptimer;}
    else delete counttimer;
    delete Return;
    delete Replay;
    delete printtime;
    delete clock1;
    delete clock2;
    delete mouse;
    delete mouse->label;
    myblock.clear();
    Ling.clear();
    if(gamesta==2){change.clear();havehammer=0;}
}
void maze::replay()//重玩
{
    if(gamesta!=4)
     {
    gametime =MX*MY*0.2;
    updatetimer();
    counttimer->start(1000);
    mouse->label->clear();
    mouse->type=ground_label;
    allsquare[1][1]->type=mouse_label;
    mouse->X=1;
    mouse->Y=1;
    mouse->label->setGeometry(Label_Size,Label_Size,Label_Size,Label_Size);
    mouse->label->setMovie(mousegif);
    mousegif->start();
    mouse->label->show();
    mouse->type=mouse_label;
    if(gamesta==3)
    {
        cat->label->clear();
        cat->type=ground_label;
        for(square* a:change)
        {
            a->type = ground_label;
            a->label->clear();
            a->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
            a->label->show();
        }
        change.clear();
        if(rand()%2==0)
            {
            if(allsquare[1][MY-2]->type==ground_label)
                change.append(allsquare[1][MY-2]);
                cat->X=1;
                cat->Y=MY-2;
                cat->label->setGeometry(Label_Size,(MY-2)*Label_Size,Label_Size,Label_Size);
                allsquare[1][MY-2]->type=wall_label;
                allsquare[1][MY-2]->label->clear();
                allsquare[1][MY-2]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
                allsquare[1][MY-2]->label->show();

            }
            else
            {
            if(allsquare[MX-2][1]->type==ground_label)
                change.append(allsquare[MX-2][1]);
                cat->X=MX-2;
                cat->Y=1;
                cat->label->setGeometry((MX-2)*Label_Size,Label_Size,Label_Size,Label_Size);
                allsquare[MX-2][1]->type=wall_label;
                allsquare[MX-2][1]->label->clear();
                allsquare[MX-2][1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
                allsquare[MX-2][1]->label->show();
            }
        cat->type=cat_label;
        cat->label->setMovie(catgif);
        catgif->start();
        cattimer->start(100);
    }
    if(gamesta==2&&havehammer==1)
    {
       havehammer=0;
       for(auto& a:change)
       {
           a->type = wall_label;
           a->label->clear();
           a->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
           a->label->show();
       }
       change[0]->type=hammer_label;
       change[0]->label->setPixmap(*hammer);
       change[0]->label->setScaledContents(true);
       change[0]->label->show();
       change.clear();
    }
    }
}
void maze::startgame2()
{
    gamesta=2;
    initgame();
    destructwall();
    srand(time(0));
    int hamX=(rand()%(MX-5))+2;
    int hamY=(rand()%(MY-5))+2;
    allsquare[hamX][hamY]->type=hammer_label;
    allsquare[hamX][hamY]->label->setPixmap(*hammer);
    allsquare[hamX][hamY]->label->setScaledContents(true);
    allsquare[hamX][hamY]->label->show();
    gametime =MX*MY*0.2;
    updatetimer();
    counttimer=new QTimer(this);
    QObject::connect(counttimer,SIGNAL(timeout()),this,SLOT(updatetimer()));
    counttimer->start(1000);
    printtime->show();

}
void maze::startgame3()
{
    gamesta=3;
    initgame();
    destructwall();
    gametime =MX*MY*0.2;
    updatetimer();
    cat=new square;
    cat->label=new QLabel(this);
    if(rand()%2==0)
        {
        if(allsquare[1][MY-2]->type==ground_label)
            change.append(allsquare[1][MY-2]);
            cat->X=1;
            cat->Y=MY-2;
            cat->label->setGeometry(Label_Size,(MY-2)*Label_Size,Label_Size,Label_Size);
            catgif=new QMovie(":/cat2.gif");
            allsquare[1][MY-2]->type=wall_label;
            allsquare[1][MY-2]->label->clear();
            allsquare[1][MY-2]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
            allsquare[1][MY-2]->label->show();

        }
        else
        {
        if(allsquare[MX-2][1]->type==ground_label)
            change.append(allsquare[MX-2][1]);
            cat->X=MX-2;
            cat->Y=1;
            cat->label->setGeometry((MX-2)*Label_Size,Label_Size,Label_Size,Label_Size);
            catgif=new QMovie(":/cat2.gif");
            allsquare[MX-2][1]->type=wall_label;
            allsquare[MX-2][1]->label->clear();
            allsquare[MX-2][1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
            allsquare[MX-2][1]->label->show();
        }
    QSize s2(Label_Size+10,Label_Size+10);
    catgif->setScaledSize(s2);
    cat->type=cat_label;
    cat->label->setMovie(catgif);
    catgif->start();
    cat->label->show();
    counttimer=new QTimer(this);
    cattimer=new QTimer(this);
    QObject::connect(counttimer,SIGNAL(timeout()),this,SLOT(updatetimer()));
    QObject::connect(cattimer,SIGNAL(timeout()),this,SLOT(walk()));
    counttimer->start(1000);
    cattimer->start(100);
    printtime->show();
}
void maze::dwall()
{
    if(dtype==1)
    {
        if (myblock.size()&&flag==1) {
            int BlockSize = myblock.size();
            //随机选择一堵墙（生成0 ~ BlockSize-1之间的随机数，同时也是vector里墙的下标）
            int randnum = rand() % BlockSize;
            block SelectBlock = myblock[randnum];
            x_num = SelectBlock.row;//矿工来到我们“选择的墙”这里
            y_num = SelectBlock.column;
            //根据当前选择的墙的方向进行后续操作
            //此时，起始点 选择的墙 目标块 三块区域在同一直线上
            //我们让矿工从“选择的墙”继续前进到“目标块”
            //矿工有穿墙能力 ：)
            switch (SelectBlock.direction) {
            case right: {
                x_num++;
                break;
            }
            case down: {
                y_num++;
                break;
            }
            case up: {
                y_num--;
                break;
            }
            case left: {
                x_num--;
                break;
            }
            }
            //目标块如果是墙
            if (G[x_num][y_num] == WALL) {
                //打通墙和目标块
                G[SelectBlock.row][SelectBlock.column] = G[x_num][y_num] = NOTHING;
                //再次找出与矿工当前位置相邻的墙
                //找出与当前位置相邻的墙
                if (x_num + 1 <= m && G[x_num + 1][y_num] == WALL) {//right
                    myblock.push_back(block(x_num + 1, y_num, right));
                }
                if (y_num + 1 <= n && G[x_num][y_num + 1] == WALL) {//down
                    myblock.push_back(block(x_num, y_num + 1, down));
                }
                if (x_num - 1 >= 1 && G[x_num - 1][y_num] == WALL) {//left
                    myblock.push_back(block(x_num - 1, y_num, left));
                }
                if (y_num - 1 >= 1 && G[x_num][y_num - 1] == WALL) {//up
                    myblock.push_back(block(x_num, y_num - 1,  up));
                }
            }
            else {//如果不是呢？说明我们的矿工挖到了一个空旷的通路上面 休息一下就好了
             //relax
                allsquare[SelectBlock.row][SelectBlock.column]->label->clear();
                allsquare[SelectBlock.row][SelectBlock.column]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
                allsquare[SelectBlock.row][SelectBlock.column]->label->show();
            }
            //删除这堵墙(把用不了的墙删了，对于那些已经施工过了不必再施工了，同时也是确保我们能跳出循环)
            myblock.erase(myblock.begin() + randnum);

        for (int i = 0; i <= m + 1; i++)
        {
            for (int j = 0; j <= n + 1; j++)
            {
                if (G[i][j] == NOTHING&&allsquare[i][j]->type!=food_label)
                {
                    allsquare[i][j]->type = ground_label;
                    allsquare[i][j]->label->clear();
                    allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                    allsquare[i][j]->label->show();

                }
            }
        }
        for (int i=0;i<myblock.size();i++)
        {
           if(myblock[i].direction==down)
           {
           allsquare[myblock[i]. row][myblock[i].column]->label->setStyleSheet("QLabel{border-image:url(:/down.png)}");
           allsquare[myblock[i]. row][myblock[i].column]->label->show();
           }
           if(myblock[i].direction==up)
           {
           allsquare[myblock[i]. row][myblock[i].column]->label->setStyleSheet("QLabel{border-image:url(:/up.png)}");
           allsquare[myblock[i]. row][myblock[i].column]->label->show();
           }
           if(myblock[i].direction==left)
           {
           allsquare[myblock[i]. row][myblock[i].column]->label->setStyleSheet("QLabel{border-image:url(:/left.png)}");
           allsquare[myblock[i]. row][myblock[i].column]->label->show();
           }
           if(myblock[i].direction==right)
           {
           allsquare[myblock[i]. row][myblock[i].column]->label->setStyleSheet("QLabel{border-image:url(:/right.png)}");
           allsquare[myblock[i]. row][myblock[i].column]->label->show();
           }
        }
    }


        else
        {
           flag=0;
           if(flag1)
           {
               flag1=0;
               x_num=1;y_num=1;
               G[1][1]=1;
                myblock.push_back(block(x_num,y_num,0));
               if (x_num + 1 <= m && G[x_num + 1][y_num] == NOTHING) {//right
                   Ling.push_back(block(x_num + 1, y_num, right));
               }
               if (y_num + 1 <= n && G[x_num][y_num + 1] == NOTHING) {//down
                   Ling.push_back(block(x_num, y_num + 1, down));
               }
               if (x_num - 1 >= 1 && G[x_num - 1][y_num] == NOTHING) {//left
                   Ling.push_back(block(x_num - 1, y_num, left));
               }
               if (y_num - 1 >= 1 && G[x_num][y_num - 1] == NOTHING) {//up
                   Ling.push_back(block(x_num, y_num - 1,  up));
               }
           }
           if(G[m][n]!=1)
           {
               int rand2=rand()%Ling.size();
               x_num=Ling[rand2].row;
               y_num=Ling[rand2].column;
               G[x_num][y_num]=1;
               myblock.push_back(block(x_num,y_num,Ling[rand2].direction));
               if (x_num + 1 <= m && G[x_num + 1][y_num] == NOTHING) {//right
                   Ling.push_back(block(x_num + 1, y_num, right));
               }
               if (y_num + 1 <= n && G[x_num][y_num + 1] == NOTHING) {//down
                   Ling.push_back(block(x_num, y_num + 1, down));
               }
               if (x_num - 1 >= 1 && G[x_num - 1][y_num] == NOTHING) {//left
                   Ling.push_back(block(x_num - 1, y_num, left));
               }
               if (y_num - 1 >= 1 && G[x_num][y_num - 1] == NOTHING) {//up
                   Ling.push_back(block(x_num, y_num - 1,  up));
               }
               Ling.erase(Ling.begin()+rand2);
               for(int i=0;i<myblock.size();i++)
               {
                   if(allsquare[myblock[i]. row][myblock[i].column]->type!=food_label)
                  { allsquare[myblock[i]. row][myblock[i].column]->label->setStyleSheet("QLabel{border-image:url(:/path.jpg)}");
                   allsquare[myblock[i]. row][myblock[i].column]->label->show();}
               }
               td=myblock[myblock.size()-1].direction;
               temp2={x_num,y_num,0};
           }
           else
           {
               if(myblock.size())
               {
                   if(temp2.row==m&&temp2.column==n)
                   {
                       allsquare[temp2.row][temp2.column]->label->setStyleSheet("QLabel{border-image:url(:/cheese.jpg)}");
                       allsquare[temp2.row][temp2.column]->label->show();
                   }
                   else
                   {
                       allsquare[temp2.row][temp2.column]->label->setStyleSheet("QLabel{border-image:url(:/path.jpg)}");
                       allsquare[temp2.row][temp2.column]->label->show();
                   }

               switch (td) {
               case right: {
                     myblock.pop_back();
                     allsquare[x_num][y_num]->label->setStyleSheet("QLabel{border-image:url(:/right.png)}");
                     allsquare[x_num][y_num]->label->show();
                   if((x_num-1)==myblock[myblock.size()-1].row&&(y_num==myblock[myblock.size()-1].column))
                   {
                       temp2={x_num,y_num,td};
                       x_num--;
                       td=myblock[myblock.size()-1].direction;
                   }
                   else
                   {
                     allsquare[myblock[myblock.size()-1].row][myblock[myblock.size()-1].column]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                     allsquare[myblock[myblock.size()-1].row][myblock[myblock.size()-1].column]->label->show();
                   }
                   break;
               }
               case down: {
                     myblock.pop_back();
                     allsquare[x_num][y_num]->label->setStyleSheet("QLabel{border-image:url(:/down.png)}");
                     allsquare[x_num][y_num]->label->show();
                   if(x_num==myblock[myblock.size()-1].row&&((y_num-1)==myblock[myblock.size()-1].column))
                   {
                       temp2={x_num,y_num,td};
                       y_num--;
                       td=myblock[myblock.size()-1].direction;
                   }
                   else
                   {
                     allsquare[myblock[myblock.size()-1].row][myblock[myblock.size()-1].column]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                     allsquare[myblock[myblock.size()-1].row][myblock[myblock.size()-1].column]->label->show();
                   }
                   break;
               }
               case up: {
                     myblock.pop_back();
                     allsquare[x_num][y_num]->label->setStyleSheet("QLabel{border-image:url(:/up.png)}");
                     allsquare[x_num][y_num]->label->show();
                   if(x_num==myblock[myblock.size()-1].row&&((y_num+1)==myblock[myblock.size()-1].column))
                   {
                      temp2={x_num,y_num,td};
                       y_num++;
                       td=myblock[myblock.size()-1].direction;
                   }
                   else
                   {
                     allsquare[myblock[myblock.size()-1].row][myblock[myblock.size()-1].column]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                     allsquare[myblock[myblock.size()-1].row][myblock[myblock.size()-1].column]->label->show();
                   }
                   break;
               }
               case left: {
                     myblock.pop_back();
                     allsquare[x_num][y_num]->label->setStyleSheet("QLabel{border-image:url(:/left.png)}");
                     allsquare[x_num][y_num]->label->show();
                   if((x_num+1)==myblock[myblock.size()-1].row&&(y_num==myblock[myblock.size()-1].column))
                   {
                       temp2={x_num,y_num,td};
                       x_num++;
                       td=myblock[myblock.size()-1].direction;
                   }
                   else
                   {
                     allsquare[myblock[myblock.size()-1].row][myblock[myblock.size()-1].column]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                     allsquare[myblock[myblock.size()-1].row][myblock[myblock.size()-1].column]->label->show();
                   }
                   break;
               }
           }
           }
               else ptimer->stop();
         }
     }
  }
    if(dtype==2)
    {
        int rand1;
        if((myblock.size()!=0||flag==1)&&flag1)
        {
            flag=0;
            block temp(0,0,0);
         if(Ling.size())
         {
         rand1=rand()%Ling.size();
        myblock.push_back(block(x_num,y_num,Ling[rand1].direction));
        x_num=Ling[rand1].row;
        y_num=Ling[rand1].column;
        G[x_num][y_num]=1;
        switch (Ling[rand1].direction)
        {
        case right: {
            x_num--;
            break;
        }
        case down: {
             y_num--; 
            break;
        }
        case up: {
            y_num++;
             break;
        }
        case left: {
            x_num++;
            break;
        }

        }
         temp={x_num,y_num,Ling[rand1].direction};
        G[x_num][y_num]=1;
        x_num=Ling[rand1].row;
        y_num=Ling[rand1].column;
        }
         else
         {
             if(myblock.size())
             {
                 x_num=myblock[myblock.size()-1].row;
                 y_num=myblock[myblock.size()-1].column;
                 temp={x_num,y_num,myblock[myblock.size()-1].direction};
                 myblock.pop_back();
             }

         }
         for (int i = 1; i <=m; i++)
         {
             for (int j = 1; j <= n; j++)
             {
                 if (G[i][j] ==1&&allsquare[i][j]->type!=food_label)
                 {
                     allsquare[i][j]->type = ground_label;
                     allsquare[i][j]->label->clear();
                     allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                     allsquare[i][j]->label->show();
                 }
             }
         }
         switch (temp.direction)
         {
         case right: {
             if(Ling.size())
             allsquare[x_num-1][y_num]->label->setStyleSheet("QLabel{border-image:url(:/right.png)}");
             else
               allsquare[x_num+1][y_num]->label->setStyleSheet("QLabel{border-image:url(:/left.png)}");
             break;
         }
         case down: {
             if(Ling.size())
                 allsquare[x_num][y_num-1]->label->setStyleSheet("QLabel{border-image:url(:/down.png)}");
                 else
                 allsquare[x_num][y_num+1]->label->setStyleSheet("QLabel{border-image:url(:/up.png)}");
             break;
         }
         case up: {
             if(Ling.size())
               allsquare[x_num][y_num+1]->label->setStyleSheet("QLabel{border-image:url(:/up.png)}");
             else
              allsquare[x_num][y_num-1]->label->setStyleSheet("QLabel{border-image:url(:/down.png)}");
             break;
         }
         case left: {
             if(Ling.size())
                 allsquare[x_num+1][y_num]->label->setStyleSheet("QLabel{border-image:url(:/left.png)}");
             else
              allsquare[x_num-1][y_num]->label->setStyleSheet("QLabel{border-image:url(:/right.png)}");
             break;
         }
         }
          Ling.clear();
         if (x_num + 2 <= m && G[x_num + 2][y_num] == 0) {//right
             Ling.push_back(block(x_num + 2, y_num, right));
         }
         if (y_num + 2 <= n && G[x_num][y_num + 2] == 0) {//down
             Ling.push_back(block(x_num, y_num + 2, down));
         }
         if (x_num - 2 >= 1 && G[x_num - 2][y_num] == 0) {//left
             Ling.push_back(block(x_num - 2, y_num, left));
         }
         if (y_num - 2 >= 1 && G[x_num][y_num - 2] == 0) {//up
             Ling.push_back(block(x_num, y_num - 2,  up));
         }

        }
        else
        {   flag1=0;

            if(!flag)
            {
                for (int i = 1; i <=m; i++)
                {
                    for (int j = 1; j <= n; j++)
                    {
                        if (G[i][j] ==1&&allsquare[i][j]->type!=food_label)
                        {
                            allsquare[i][j]->type = ground_label;
                            allsquare[i][j]->label->clear();
                            allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                            allsquare[i][j]->label->show();
                        }
                    }
                }

                x_num=1;y_num=1;
                G[x_num][y_num]=2;
                if (x_num + 1 <= m && G[x_num + 1][y_num] == 1) {//right
                    Ling.push_back(block(x_num + 1, y_num, right));
                }
                if (y_num + 1 <= n && G[x_num][y_num + 1] == 1) {//down
                    Ling.push_back(block(x_num, y_num + 1, down));
                }
                if (x_num - 1 >= 1 && G[x_num - 1][y_num] == 1) {//left
                    Ling.push_back(block(x_num - 1, y_num, left));
                }
                if (y_num - 1 >= 1 && G[x_num][y_num - 1] == 1) {//up
                    Ling.push_back(block(x_num, y_num - 1,  up));
                }
            }
            if(G[m][n]!=2)
            {
                flag=1;
                if(Ling.size())
                {
                rand1=rand()%Ling.size();
               myblock.push_back(block(x_num,y_num,Ling[rand1].direction));
               x_num=Ling[rand1].row;
               y_num=Ling[rand1].column;
               G[x_num][y_num]=2;
               }
                else
                {
                    if(myblock.size())
                    {
                        allsquare[x_num][y_num]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                        allsquare[x_num][y_num]->label->show();
                        x_num=myblock[myblock.size()-1].row;
                        y_num=myblock[myblock.size()-1].column;
                        myblock.pop_back();
                    }

                }
                Ling.clear();
                if (x_num + 1 <= m && G[x_num + 1][y_num] == 1) {//right
                    Ling.push_back(block(x_num + 1, y_num, right));
                }
                if (y_num + 1 <= n && G[x_num][y_num + 1] == 1) {//down
                    Ling.push_back(block(x_num, y_num + 1, down));
                }
                if (x_num - 1 >= 1 && G[x_num - 1][y_num] == 1) {//left
                    Ling.push_back(block(x_num - 1, y_num, left));
                }
                if (y_num - 1 >= 1 && G[x_num][y_num - 1] == 1) {//up
                    Ling.push_back(block(x_num, y_num - 1,  up));
                }
                for(int i=0;i<myblock.size();i++)
                {
                    allsquare[myblock[i]. row][myblock[i].column]->label->setStyleSheet("QLabel{border-image:url(:/path.jpg)}");
                    allsquare[myblock[i]. row][myblock[i].column]->label->show();
                }
            }
            else ptimer->stop();
        }
    }

}
void maze::present()
{
    initgame();
    gamesta=4;
    if(dtype==1)
    {
    if (x_num + 1 <= m && G[x_num + 1][y_num] == WALL) {//right
        myblock.push_back(block(x_num + 1, y_num, right));
    }
    if (y_num + 1 <= n && G[x_num][y_num + 1] == WALL) {//down
        myblock.push_back(block(x_num, y_num + 1, down));
    }
    if (x_num - 1 >= 1 && G[x_num - 1][y_num] == WALL) {//left
        myblock.push_back(block(x_num - 1, y_num, left));
    }
    if (y_num - 1 >= 1 && G[x_num][y_num - 1] == WALL) {//up
        myblock.push_back(block(x_num, y_num - 1,  up));
    }
     flag=1;
     flag1=1;
    }
    if(dtype==2)
    {

       if (x_num + 2 <= m && G[x_num + 2][y_num] == 0) {//right
           Ling.push_back(block(x_num + 2, y_num, right));
       }
       if (y_num + 2 <= n && G[x_num][y_num + 2] == 0) {//down
           Ling.push_back(block(x_num, y_num + 2, down));
       }
       if (x_num - 2 >= 1 && G[x_num - 2][y_num] == 0) {//left
           Ling.push_back(block(x_num - 2, y_num, left));
       }
       if (y_num - 2 >= 1 && G[x_num][y_num - 2] == 0) {//up
           Ling.push_back(block(x_num, y_num - 2,  up));
       }
       flag=1;
       flag1=1;
    }
    ptimer=new QTimer(this);
    ptimer->start(ptime);
    QObject::connect(ptimer,SIGNAL(timeout()),this,SLOT(dwall()));

}
void maze::walk()
{
    movecat();
    if(cat->label->x()==mouse->label->x()&&cat->label->y()==mouse->label->y())
    {
        allsquare[cat->X][cat->Y]->label->clear();
        allsquare[cat->X][cat->Y]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
        allsquare[cat->X][cat->Y]->label->show();
        allsquare[cat->X][cat->Y]->label->setMovie(catgif);
        catgif->start();
        gameover(0,1);
    }
}
void maze::movecat()//响应键盘的移动函数，要有必要的判断，判断是否有墙
{
    if(allsquare[mouse->X][mouse->Y]->type==wall_label)
    {
        gameover(0,1);
    }
     if(mouse->label->x()>cat->label->x()&&mouse->label->y()<cat->label->y())
     {
         if(rand()%2==1)
         {
              dx1=0;dy1=-1;
         }
         else
         {
              dx1=1;dy1=0;
         }
     }
     if(mouse->label->x()>cat->label->x()&&mouse->label->y()>cat->label->y())
     {
         if(rand()%2==1)
         {
              dx1=0;dy1=1;
         }
         else
         {
              dx1=1;dy1=0;
         }
     }
     if(mouse->label->x()<cat->label->x()&&mouse->label->y()>cat->label->y())
     {
         if(rand()%2==1)
         {
              dx1=0;dy1=1;
         }
         else
         {
              dx1=-1;dy1=0;
         }
     }
     if(mouse->label->x()<cat->label->x()&&mouse->label->y()<cat->label->y())
     {
         if(rand()%2==1)
         {
              dx1=0;dy1=-1;
         }
         else
         {
              dx1=-1;dy1=0;
         }
     }
     if(mouse->label->x()==cat->label->x()&&mouse->label->y()<cat->label->y())
              {dx1=0;dy1=-1;}
     if(mouse->label->x()==cat->label->x()&&mouse->label->y()>cat->label->y())
              {dx1=0;dy1=1;}
     if(mouse->label->x()<cat->label->x()&&mouse->label->y()==cat->label->y())
              {dx1=-1;dy1=0;}
     if(mouse->label->x()>cat->label->x()&&mouse->label->y()==cat->label->y())
              {dx1=1;dy1=0;}
     if(dx1==1||dy1==1)
    {
         if(cat->X!=(cat->label->x()/Label_Size)|| cat->Y!=(cat->label->y()/Label_Size))
         {
             if(allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]->type==ground_label)
                 change.append( allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]);
             allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]->type=wall_label;
             allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]->label->clear();
             allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
             allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]->label->show();

         }
         cat->X=(cat->label->x()/Label_Size);
         cat->Y=(cat->label->y()/Label_Size);
    }
     if(dx1==-1||dy1==-1)
     {
         if(cat->X!=((cat->label->x()+dx1)/Label_Size)-dx1|| cat->Y!=((cat->label->y()+dy1)/Label_Size)-dy1)
         {
             if(allsquare[((cat->label->x()+dx1)/Label_Size)-dx1][((cat->label->y()+dy1)/Label_Size)-dy1]->type==ground_label)
                 change.append( allsquare[(cat->label->x()/Label_Size)-dx1][(cat->label->y()/Label_Size)-dy1]);
             allsquare[((cat->label->x()+dx1)/Label_Size)-dx1][((cat->label->y()+dy1)/Label_Size)-dy1]->type=wall_label;
             allsquare[((cat->label->x()+dx1)/Label_Size)-dx1][((cat->label->y()+dy1)/Label_Size)-dy1]->label->clear();
             allsquare[((cat->label->x()+dx1)/Label_Size)-dx1][((cat->label->y()+dy1)/Label_Size)-dy1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
             allsquare[((cat->label->x()+dx1)/Label_Size)-dx1][((cat->label->y()+dy1)/Label_Size)-dy1]->label->show();

         }
        cat->X=((cat->label->x()+dx1)/Label_Size)-dx1;
        cat->Y=((cat->label->y()+dy1)/Label_Size)-dy1;
     }
     if(dy==0)
     {
              cat->label->move(cat->label->x()+3*dx1,cat->label->y()+3*dy1);
     }

     if(dx==0)
     {
             cat->label->move(cat->label->x()+3*dx1,cat->label->y()+3*dy1);
     }
     if( allsquare[cat->X+1][cat->Y+1]->type==ground_label)
     {allsquare[cat->X+1][cat->Y+1]->type=wall_label;
         allsquare[cat->X+1][cat->Y+1]->label->clear();
         allsquare[cat->X+1][cat->Y+1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
         allsquare[cat->X+1][cat->Y+1]->label->show();
         change.append( allsquare[cat->X+1][cat->Y+1]);}
     if( allsquare[cat->X+1][cat->Y-1]->type==ground_label)
     {allsquare[cat->X+1][cat->Y-1]->type=wall_label;
         allsquare[cat->X+1][cat->Y-1]->label->clear();
         allsquare[cat->X+1][cat->Y-1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
         allsquare[cat->X+1][cat->Y-1]->label->show();
         change.append( allsquare[cat->X+1][cat->Y-1]);}
     if( allsquare[cat->X-1][cat->Y+1]->type==ground_label)
     {allsquare[cat->X-1][cat->Y+1]->type=wall_label;
         allsquare[cat->X-1][cat->Y+1]->label->clear();
         allsquare[cat->X-1][cat->Y+1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
         allsquare[cat->X-1][cat->Y+1]->label->show();
         change.append( allsquare[cat->X-1][cat->Y+1]);}
     if( allsquare[cat->X-1][cat->Y-1]->type==ground_label)
     {allsquare[cat->X-1][cat->Y-1]->type=wall_label;
         allsquare[cat->X-1][cat->Y-1]->label->clear();
         allsquare[cat->X-1][cat->Y-1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
         allsquare[cat->X-1][cat->Y-1]->label->show();
         change.append( allsquare[cat->X-1][cat->Y-1]);}
     if( allsquare[cat->X][cat->Y-1]->type==ground_label)
     {allsquare[cat->X][cat->Y-1]->type=wall_label;
         allsquare[cat->X][cat->Y-1]->label->clear();
         allsquare[cat->X][cat->Y-1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
         allsquare[cat->X][cat->Y-1]->label->show();
         change.append( allsquare[cat->X][cat->Y-1]);}
     if( allsquare[cat->X-1][cat->Y]->type==ground_label)
     {allsquare[cat->X-1][cat->Y]->type=wall_label;
         allsquare[cat->X-1][cat->Y]->label->clear();
         allsquare[cat->X-1][cat->Y]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
         allsquare[cat->X-1][cat->Y]->label->show();
         change.append( allsquare[cat->X-1][cat->Y]);}
     if( allsquare[cat->X][cat->Y+1]->type==ground_label)
     {allsquare[cat->X][cat->Y+1]->type=wall_label;
         allsquare[cat->X][cat->Y+1]->label->clear();
         allsquare[cat->X][cat->Y+1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
         allsquare[cat->X][cat->Y+1]->label->show();
         change.append( allsquare[cat->X][cat->Y+1]);}
     if( allsquare[cat->X+1][cat->Y]->type==ground_label)
     {allsquare[cat->X+1][cat->Y]->type=wall_label;
         allsquare[cat->X+1][cat->Y]->label->clear();
         allsquare[cat->X+1][cat->Y]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
         allsquare[cat->X+1][cat->Y]->label->show();
         change.append( allsquare[cat->X+1][cat->Y]);}



}

void maze::structface()
{
    allsquare=new square**[MX];
        for(int i=0;i<MX;i++)
        {
            allsquare[i]=new square*[MY];
            for (int j=0;j<MY;j++)
            {
                allsquare[i][j]=new square;
                allsquare[i][j]->X=i;
                allsquare[i][j]->Y=j;
                allsquare[i][j]->label=new QLabel(this);
                allsquare[i][j]->label->setGeometry(i*Label_Size,j*Label_Size,Label_Size,Label_Size);
                allsquare[i][j]->type=wall_label;
            }
        }
        for(int i=0;i<MX;i=i+2)
            {
                for(int j=0;j<MY;j=j+1)
                {
                    allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
                    allsquare[i][j]->label->show();
                }
            }

        for(int i=1;i<MX;i=i+2)
        {
            for (int j=0;j<MY;j=j+2)
            {
                allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
                allsquare[i][j]->label->show();
            }
        }
        for(int i=1;i<MX;i=i+2)
        {
            for (int j=1;j<MY;j=j+2)
            {
                allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/ground.jpg)}");
                allsquare[i][j]->label->show();
            }
        }

        srand(time(0));
        mouse=new square;
        mouse->label=new QLabel(this);
        food=allsquare[MX-2][MY-2];
        mouse->X=1;
        mouse->Y=1;
        mouse->label->setGeometry(Label_Size,Label_Size,Label_Size,Label_Size);
        mouse->label->setMovie(mousegif);
        mousegif->start();
        mouse->label->show();
        mouse->type=mouse_label;
        food->label->setStyleSheet("QLabel{border-image:url(:/cheese.jpg)}");
        food->type=food_label;
}
void maze::settingslot()//设置地图大小的函数
{
    QDialog* setwindowsize=new QDialog(this);
      setwindowsize->setWindowTitle("修改难度");
      QPushButton*save=new QPushButton ("ok",setwindowsize);
      QPushButton*cancle=new QPushButton("cancle",setwindowsize);
      QSlider* L=new QSlider (setwindowsize);
      QSlider* W=new QSlider (setwindowsize) ;
      QSlider* S=new QSlider (setwindowsize);
      QLabel* length=new QLabel(setwindowsize);
      QLabel* width=new QLabel (setwindowsize);
      QLabel* speed=new QLabel("生成速度:",setwindowsize);
      speed->show();
      length->setText("长度:");
      width->setText("宽度:");
      length->setGeometry(30,50,40,40);
      width->setGeometry(30,100,40,40);
      speed->setGeometry(10,150,80,40);
      setwindowsize->resize(400,400);
      save->setGeometry(50,300,100,50);
      cancle->setGeometry(250,300,100,50);
      L->setOrientation(Qt::Horizontal);
      W->setOrientation(Qt::Horizontal);
      S->setOrientation(Qt::Horizontal);
      L->setGeometry(60,50,300,50);
      W->setGeometry(60,100,100,50);
      S->setGeometry(100,150,250,50);
      int temp;
      temp=((0.9*screen_width/Label_Size+1)/2);
      L->setRange(6,temp);
      L->setSingleStep(1);
      temp=((0.9*screen_height/Label_Size+2)/2);
      W->setRange(6,temp);
      W->setSingleStep(1);
      temp=((MX+1)/2);
      L->setValue(temp);
      temp=((MY+1)/2);
      W->setValue(temp);
      S->setRange(2,100);
      S->setSingleStep(5);
      S->setValue(1000/ptime);
      QObject::connect(save,SIGNAL(clicked()),setwindowsize,SLOT(accept()));
      QObject::connect(cancle,SIGNAL(clicked()),setwindowsize,SLOT(reject()));
      QRadioButton* d1=new QRadioButton("广度优先生成迷宫",setwindowsize);
      QRadioButton* d2=new QRadioButton("深度优先生成迷宫",setwindowsize);
      d1->setGeometry(50,200,150,50);
      d2->setGeometry(250,200,150,50);
      if(dtype==1) d1->setChecked(true);
      if(dtype==2) d2->setChecked(true);
      if(setwindowsize->exec()==QDialog::Accepted)
      {
          MX=2*(L->value())-1;MY=2*(W->value())-1;
          resizewindow();
          ptime=1000/(S->value());
          if(d1->isChecked()){dtype=1;}
          if(d2->isChecked()){dtype=2;}
      }

      delete setwindowsize;
}
void maze::keyPressEvent(QKeyEvent *event)//键盘控制部分
{
    switch (event->key())
    {
    case Qt::Key_Up:
        dx=0;
        dy=-1;
        if(gamesta==1)
            movemouse();
        if(gamesta==2)
            movemouse2();
        if(gamesta==3)
            movemouse3();
        break;
    case Qt::Key_Down:
        dx=0;
        dy=1;
        if(gamesta==1)
            movemouse();
        if(gamesta==2)
            movemouse2();
        if(gamesta==3)
            movemouse3();
        break;
    case Qt::Key_Left:
        dx=-1;
        dy=0;
        if(gamesta==1)
            movemouse();
        if(gamesta==2)
            movemouse2();
        if(gamesta==3)
            movemouse3();
        break;
    case Qt::Key_Right:
        dx=1;
        dy=0;
        if(gamesta==1)
            movemouse();
        if(gamesta==2)
            movemouse2();
        if(gamesta==3)
            movemouse3();
        break;
    case Qt::Key_Space:
        if(gamesta==4)
        {
            if(ptimer->isActive())
                ptimer->stop();
            else ptimer->start();
        }
        break;

    }
}
void maze::movemouse()//响应键盘的移动函数，要有必要的判断，判断是否有墙
{
    if(dx==1||dy==1)
   {
        mouse->X=(mouse->label->x()/Label_Size);
        mouse->Y=(mouse->label->y()/Label_Size);
   }
    if(dx==-1||dy==-1)
    {
       mouse->X=((mouse->label->x()+dx)/Label_Size)-dx;
       mouse->Y=((mouse->label->y()+dy)/Label_Size)-dy;
    }
    if(dy==0)
    {
        if(mouse->label->y()%Label_Size==0)
        {
            square* tempMouse=allsquare[mouse->X+dx][mouse->Y+dy];//设置临时的指针，先让老鼠移动在判断是否有墙

                if(tempMouse->type==wall_label)//如果老鼠撞到了墙
                {

                }
                else//如果老鼠没有撞到墙
                {
                    if(tempMouse->type==food_label)
                    gameover(1,0);
                    if(tempMouse->type==ground_label)
                        {
                        mouse->label->move(mouse->label->x()+3*dx,mouse->label->y()+3*dy);
                       }
                }
        }
    }
    if(dx==0)
    {
        if(mouse->label->x()%Label_Size==0)
        {
            square* tempMouse=allsquare[mouse->X+dx][mouse->Y+dy];//设置临时的指针，先让老鼠移动在判断是否有墙

                if(tempMouse->type==wall_label)//如果老鼠撞到了墙
                {

                }
                else//如果老鼠没有撞到墙
                {
                    if(tempMouse->type==food_label)
                        gameover(1,0);
                    if(tempMouse->type==ground_label)
                        {
                        mouse->label->move(mouse->label->x()+3*dx,mouse->label->y()+3*dy);
                       }
                }
        }
    }

}
void maze::movemouse3()//响应键盘的移动函数，要有必要的判断，判断是否有墙
{
    if(dx==1||dy==1)
   {
        mouse->X=(mouse->label->x()/Label_Size);
        mouse->Y=(mouse->label->y()/Label_Size);
   }
    if(dx==-1||dy==-1)
    {
       mouse->X=((mouse->label->x()+dx)/Label_Size)-dx;
       mouse->Y=((mouse->label->y()+dy)/Label_Size)-dy;
    }
    if(dy==0)
    {
        if(mouse->label->y()%Label_Size==0)
        {
            square* tempMouse=allsquare[mouse->X+dx][mouse->Y+dy];//设置临时的指针，先让老鼠移动在判断是否有墙

                if(tempMouse->type==wall_label)//如果老鼠撞到了墙
                {

                }
                if(tempMouse->type==cat_label)//如果老鼠撞到了猫
                {
                    gameover(0,1);
                }
                else//如果老鼠没有撞到墙
                {
                    if(tempMouse->type==food_label)
                    gameover(1,1);
                    if(tempMouse->type==ground_label)
                        {
                        mouse->label->move(mouse->label->x()+3*dx,mouse->label->y()+3*dy);
                       }
                }
        }
    }
    if(dx==0)
    {
        if(mouse->label->x()%Label_Size==0)
        {
            square* tempMouse=allsquare[mouse->X+dx][mouse->Y+dy];//设置临时的指针，先让老鼠移动在判断是否有墙

                if(tempMouse->type==wall_label)//如果老鼠撞到了墙
                {

                }
                if(tempMouse->type==cat_label)//如果老鼠撞到了猫
                {
                    gameover(0,1);
                }
                else//如果老鼠没有撞到墙
                {
                    if(tempMouse->type==food_label)
                    gameover(1,1);
                    if(tempMouse->type==ground_label)
                        {
                        mouse->label->move(mouse->label->x()+3*dx,mouse->label->y()+3*dy);
                       }
                }
        }
    }

}

void maze::movemouse2()//响应键盘的移动函数，要有必要的判断，判断是否有墙
{
    if(dx==1||dy==1)
   {
        mouse->X=(mouse->label->x()/Label_Size);
        mouse->Y=(mouse->label->y()/Label_Size);
   }
    if(dx==-1||dy==-1)
    {
       mouse->X=((mouse->label->x()+dx)/Label_Size)-dx;
       mouse->Y=((mouse->label->y()+dy)/Label_Size)-dy;
    }
    if(dy==0)
    {
        if(mouse->label->y()%Label_Size==0)
        {
            square* tempMouse=allsquare[mouse->X+dx][mouse->Y+dy];//设置临时的指针，先让老鼠移动在判断是否有墙

            if(tempMouse->type==hammer_label)
           {
               tempMouse->type=ground_label;
               tempMouse->label->clear();
               tempMouse->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                tempMouse->label->show();
               havehammer=1;
            change.append(tempMouse);}
            if(tempMouse->type==wall_label)//如果老鼠撞到了墙
                {if(havehammer==1&&tempMouse->X!=MX-1&&tempMouse->X!=0&&tempMouse->Y!=MY-1&&tempMouse->Y!=0)
                    {tempMouse->type=ground_label;
                    tempMouse->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                    change.append(tempMouse);
                }
                    else ;
               }
                else//如果老鼠没有撞到墙
                {
                    if(tempMouse->type==food_label)
                        gameover(1,0);
                    if(tempMouse->type==ground_label)
                        {
                        mouse->label->move(mouse->label->x()+3*dx,mouse->label->y()+3*dy);
                       }
                }
        }
    }
    if(dx==0)
    {
        if(mouse->label->x()%Label_Size==0)
        {
            square* tempMouse=allsquare[mouse->X+dx][mouse->Y+dy];//设置临时的指针，先让老鼠移动在判断是否有墙

            if(tempMouse->type==hammer_label)
           {
               tempMouse->type=ground_label;
                tempMouse->label->clear();
               tempMouse->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
               havehammer=1;change.append(tempMouse);}
            if(tempMouse->type==wall_label)//如果老鼠撞到了墙
                {if(havehammer==1&&tempMouse->X!=MX-1&&tempMouse->X!=0&&tempMouse->Y!=MY-1&&tempMouse->Y!=0)
                    {tempMouse->type=ground_label;
                    tempMouse->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                change.append(tempMouse);}
                    else ;
               }
                else//如果老鼠没有撞到墙
                {
                    if(tempMouse->type==food_label)
                        gameover(1,0);
                    if(tempMouse->type==ground_label)
                        {
                        mouse->label->move(mouse->label->x()+3*dx,mouse->label->y()+3*dy);
                       }
                }
        }
    }


}

/*void maze::RandestructWall()//随机摧毁墙的构造地图函数，配合我写的砸墙函数使用，改用prim算法的时候记得注释掉--贾晟浩
{
    for(int i=1;i<MX-1;i++)
    {
        for(int j=1;j<MY-1;j++)
        {
            int ran=rand()%2+1;
            if(allsquare[i][j]->type==wall_label&&(allsquare[i+1][j]->type==wall_label||allsquare[i-1][j]->type==wall_label||
                      allsquare[i][j+1]->type==wall_label||allsquare[i][j-1]->type==wall_label))
            {
                    if(ran==1)
            {
                    allsquare[i][j]->label->clear();
                    allsquare[i][j]->type=ground_label;
                    allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                    allsquare[i][j]->label->show();
        }
        }
            if(allsquare[i][j+1]->type==wall_label&&allsquare[i][j-1]->type==wall_label&&
                    allsquare[i+1][j]->type==wall_label&&allsquare[i-1][j]->type==wall_label)
            {
                allsquare[i][j]->label->clear();
                allsquare[i][j]->type=ground_label;
                allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                allsquare[i][j]->label->show();
            }
            if(allsquare[i][j+1]->type==ground_label&&allsquare[i][j-1]->type==ground_label&&
                    allsquare[i+1][j]->type==ground_label&&allsquare[i-1][j]->type==ground_label&&
                    allsquare[i+1][j+1]->type==ground_label&&allsquare[i+1][j-1]->type==ground_label&&
                    allsquare[i-1][j+1]->type==ground_label&&allsquare[i-1][j-1]->type==ground_label)
            {
                allsquare[i][j]->label->clear();
                allsquare[i][j]->type=ground_label;
                allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                allsquare[i][j]->label->show();
            }
        }
    }
}*/

/*void maze::destructwall()//打通前往终点路线的函数，未使用prim算法，重写的时候可以整个函数注释掉，然后再重新写一遍destructwall
{
    int temp_x = MX - 2;
        int temp_y = MY - 2;

        int storeX[100] = { 0 };
        int storeY[100] = { 0 };

        int totalimit_X = 0;
        int totalimit_Y = 0;

        for (int i = 0; temp_x != 0; i += 2)
            {
                int randomX = rand() % (temp_x/2+1) -(temp_x/4) + 1;
                for (; randomX == 0||(randomX==1&&temp_x!=2&&temp_x!=1)||(randomX==-1&&temp_x!=2&&temp_x!=1) || totalimit_X + randomX <= 0;)
                {
                    randomX = rand() % (temp_x/2+1) -(temp_x/4) + 1;
                }
                totalimit_X += randomX;
                storeX[i] = randomX;
                temp_x = temp_x - randomX;
            }

        for (int j = 1; temp_y != 0; j += 2)
            {
                int randomY = rand() % (temp_y/2+1) -(temp_y/4) + 1;
                for (; randomY == 0||(randomY==1&&temp_y!=2&&temp_y!=1)||(randomY==-1&&temp_y!=2&&temp_y!=1)||totalimit_Y+randomY<=0;)
                {
                    randomY = rand() % (temp_y/2+1) -(temp_y/4) + 1;
                }
                totalimit_Y += randomY;
                storeY[j] = randomY;
                temp_y = temp_y - randomY;
            }


        int totalx = 0;
        int totaly = 0;

        for (int i = 0; i<100; i++)
        {


            if (i % 2 == 0 && storeX[i] != 0)
            {
                for (int j = 1; j < (storeX[i] > 0 ? (storeX[i] + 1) : (-storeX[i] + 1)); j++)
                {
                    if(totaly==0)
                    {
                        allsquare[totalx + j][totaly+1]->type = ground_label;
                        allsquare[totalx + j][totaly+1]->label->clear();
                        allsquare[totalx + j][totaly+1]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                        allsquare[totalx + j][totaly+1]->label->show();
                    }


                    else
                    {
                        if(storeX[i]>=0)
                        {
                            allsquare[totalx + j][totaly]->type = ground_label;
                            allsquare[totalx + j][totaly]->label->clear();
                            allsquare[totalx + j][totaly]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                            allsquare[totalx + j][totaly]->label->show();
                        }
                        else
                        {
                            allsquare[totalx - j][totaly]->type = ground_label;
                            allsquare[totalx - j][totaly]->label->clear();
                            allsquare[totalx - j][totaly]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                            allsquare[totalx - j][totaly]->label->show();
                        }
                    }


                }

            }
            totalx += storeX[i];
            if (i % 2 != 0 && storeY[i] != 0)
            {
                for (int j = 1; j < (storeY[i]>0?(storeY[i]+1):(-storeY[i]+1)); j++)
                {
                    if(storeY[i]>=0)
                    {
                        allsquare[totalx][totaly+j]->type= ground_label;
                        allsquare[totalx][totaly+j]->label->clear();
                        allsquare[totalx][totaly+j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                        allsquare[totalx][totaly+j]->label->show();
                    }
                    else
                    {
                        allsquare[totalx][totaly-j]->type= ground_label;
                        allsquare[totalx][totaly-j]->label->clear();
                        allsquare[totalx][totaly-j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                        allsquare[totalx][totaly-j]->label->show();
                    }
                }
            }
            totaly += storeY[i];

        }
        RandestructWall();
}*/
void maze::destructwall()//该函数借鉴于CSDN上用户god_speed、的函数
{
   if(dtype==1)
   {
       if (x_num + 1 <= m && G[x_num + 1][y_num] == WALL) {//right
           myblock.push_back(block(x_num + 1, y_num, right));
       }
       if (y_num + 1 <= n && G[x_num][y_num + 1] == WALL) {//down
           myblock.push_back(block(x_num, y_num + 1, down));
       }
       if (x_num - 1 >= 1 && G[x_num - 1][y_num] == WALL) {//left
           myblock.push_back(block(x_num - 1, y_num, left));
       }
       if (y_num - 1 >= 1 && G[x_num][y_num - 1] == WALL) {//up
           myblock.push_back(block(x_num, y_num - 1,  up));
       }

       while (myblock.size()) {
           int BlockSize = myblock.size();
           //随机选择一堵墙（生成0 ~ BlockSize-1之间的随机数，同时也是vector里墙的下标）
           int randnum = rand() % BlockSize;
           block SelectBlock = myblock[randnum];
           x_num = SelectBlock.row;//矿工来到我们“选择的墙”这里
           y_num = SelectBlock.column;
           //根据当前选择的墙的方向进行后续操作
           //此时，起始点 选择的墙 目标块 三块区域在同一直线上
           //我们让矿工从“选择的墙”继续前进到“目标块”
           //矿工有穿墙能力 ：)
           switch (SelectBlock.direction) {
           case right: {
               x_num++;
               break;
           }
           case down: {
               y_num++;
               break;
           }
           case up: {
               y_num--;
               break;
           }
           case left: {
               x_num--;
               break;
           }
           }
           //目标块如果是墙
           if (G[x_num][y_num] == WALL) {
               //打通墙和目标块
               G[SelectBlock.row][SelectBlock.column] = G[x_num][y_num] = NOTHING;
               //再次找出与矿工当前位置相邻的墙
               //找出与当前位置相邻的墙
               if (x_num + 1 <= m && G[x_num + 1][y_num] == WALL) {//right
                   myblock.push_back(block(x_num + 1, y_num, right));
               }
               if (y_num + 1 <= n && G[x_num][y_num + 1] == WALL) {//down
                   myblock.push_back(block(x_num, y_num + 1, down));
               }
               if (x_num - 1 >= 1 && G[x_num - 1][y_num] == WALL) {//left
                   myblock.push_back(block(x_num - 1, y_num, left));
               }
               if (y_num - 1 >= 1 && G[x_num][y_num - 1] == WALL) {//up
                   myblock.push_back(block(x_num, y_num - 1,  up));
               }
           }
           else {//如果不是呢？说明我们的矿工挖到了一个空旷的通路上面 休息一下就好了
            //relax
           }
           //删除这堵墙(把用不了的墙删了，对于那些已经施工过了不必再施工了，同时也是确保我们能跳出循环)
           myblock.erase(myblock.begin() + randnum);
       }
       for (int i = 1; i <= m; i++)
       {
           for (int j = 1; j <= n; j++)
           {
               if (G[i][j] == NOTHING&&allsquare[i][j]->type!=food_label)
               {
                   allsquare[i][j]->type = ground_label;
                   allsquare[i][j]->label->clear();
                   allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                   allsquare[i][j]->label->show();

               }
           }
       }

   }
   if(dtype==2)
   {
             if (x_num + 2 <= m && G[x_num + 2][y_num] == 0) {//right
                 Ling.push_back(block(x_num + 2, y_num, right));
             }
             if (y_num + 2 <= n && G[x_num][y_num + 2] == 0) {//down
                 Ling.push_back(block(x_num, y_num + 2, down));
             }
             if (x_num - 2 >= 1 && G[x_num - 2][y_num] == 0) {//left
                 Ling.push_back(block(x_num - 2, y_num, left));
             }
             if (y_num - 2 >= 1 && G[x_num][y_num - 2] == 0) {//up
                 Ling.push_back(block(x_num, y_num - 2,  up));
             }
             int rand1;
             flag=1;
             while(myblock.size()!=0||flag==1)
             {
                 flag=0;


              if(Ling.size())
              {
              rand1=rand()%Ling.size();

             myblock.push_back(block(x_num,y_num,0));
             x_num=Ling[rand1].row;
             y_num=Ling[rand1].column;
             G[x_num][y_num]=1;

             switch (Ling[rand1].direction)
             {
             case right: {
                 x_num--;
                 break;
             }
             case down: {
                 y_num--;
                 break;
             }
             case up: {
                 y_num++;
                 break;
             }
             case left: {
                 x_num++;
                 break;
             }

             }

             G[x_num][y_num]=1;
             x_num=Ling[rand1].row;
             y_num=Ling[rand1].column;
             Ling.clear();
             }
              else
              {
                  if(myblock.size())
                  {
                      x_num=myblock[myblock.size()-1].row;
                      y_num=myblock[myblock.size()-1].column;
                      myblock.pop_back();
                  }
              }
              if (x_num + 2 <= m && G[x_num + 2][y_num] == 0) {//right
                  Ling.push_back(block(x_num + 2, y_num, right));
              }
              if (y_num + 2 <= n && G[x_num][y_num + 2] == 0) {//down
                  Ling.push_back(block(x_num, y_num + 2, down));
              }
              if (x_num - 2 >= 1 && G[x_num - 2][y_num] == 0) {//left
                  Ling.push_back(block(x_num - 2, y_num, left));
              }
              if (y_num - 2 >= 1 && G[x_num][y_num - 2] == 0) {//up
                  Ling.push_back(block(x_num, y_num - 2,  up));
              }
             }
             for (int i = 1; i <=m; i++)
             {
                 for (int j = 1; j <= n; j++)
                 {
                     if (G[i][j] ==1&&allsquare[i][j]->type!=food_label)
                     {
                         allsquare[i][j]->type = ground_label;
                         allsquare[i][j]->label->clear();
                         allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                         allsquare[i][j]->label->show();

                     }
                 }
             }
   }

}
void maze::updatetimer()//主要负责显示时间
{
    gametime--;
    QString str;
   if(gametime<100&&gametime>=10){str="00"+QString::number(gametime);}
   if(gametime<10&&gametime>=0){str="000"+QString::number(gametime);}
   if(gametime>100){str="0"+QString::number(gametime);}
   printtime->display(str);
   if(gametime==0&&gamesta==1){gameover(0,0);}
   if(gametime==0&&gamesta==2){gameover(0,0);}
   if(gametime==0&&gamesta==3){gameover(0,1);}
}
void maze::gameover(int a,int b)
{

    //接下来可以做游戏结束界面，记得，先删除当前界面,除了下方栏；
    counttimer->stop();
   if(gamesta==3){ cattimer->stop();}
    QDialog *donghua=new QDialog(this);
             donghua->setWindowTitle("游戏结束");
             donghua->resize(400,400);
             QLabel* image=new QLabel(donghua);
                  if(a==1)
                  {
                    image->setStyleSheet("QLabel{border-image:url(:/mousewin.jpg);}");
                  }
                  else
                  {
                    image->setStyleSheet("QLabel{border-image:url(:/catwin2.jpg);}");
                  }
                  image->setGeometry(0,0,400,300);
             QPushButton *ok=new QPushButton("OK",donghua);
             QPushButton *cancle=new QPushButton("Cancle",donghua);
             ok->setGeometry(50,300,100,50);
             cancle->setGeometry(250,300,100,50);
             QObject::connect(ok,SIGNAL(clicked()),donghua,SLOT(accept()));
             QObject::connect(cancle,SIGNAL(clicked()),donghua,SLOT(reject()));
             if(donghua->exec()==QDialog::Accepted)
             {

                 for(int i=0;i<MX;i++)
                 {
                     for (int j=0;j<MY;j++)
                     {
                        delete allsquare[i][j]->label;
                        delete allsquare[i][j];
                     }
                     delete allsquare[i];
                 }
                 delete allsquare;
                 allsquare=nullptr;
                 delete mouse;
                 delete mouse->label;
                 gametime=MX*MY*0.2;
                 counttimer->start();
                 x_num = 2*((rand()%(m+1))/2)+1;
                 y_num = 2*((rand()%(n+1))/2)+1;//矿工位置
                 if(dtype==1){memset(G, WALL, sizeof(G));G[x_num][y_num] = NOTHING;}
                 if(dtype==2){memset(G,0,sizeof(G));G[x_num][y_num] =1;}
                 //定义起始点
                 structface();
                destructwall();
                if(gamesta==2)

                {
                    change.clear();
                    havehammer=0;srand(time(0));
                    int hamX=(rand()%(MX-5))+2;
                    int hamY=(rand()%(MY-5))+2;
                    allsquare[hamX][hamY]->type=hammer_label;
                    allsquare[hamX][hamY]->label->setPixmap(*hammer);
                    allsquare[hamX][hamY]->label->setScaledContents(true);
                    allsquare[hamX][hamY]->label->show();
                }

                if(b==1)
                {

                    delete cat->label;
                    delete cat;
                    cat=new square;
                    cat->label=new QLabel(this);
                    cattimer->start();
                    if(rand()%2==0)
                        {
                            cat->X=1;
                            cat->Y=MY-2;
                            cat->label->setGeometry(Label_Size,(MY-2)*Label_Size,Label_Size,Label_Size);
                            allsquare[1][MY-2]->type=wall_label;
                            allsquare[1][MY-2]->label->clear();
                            allsquare[1][MY-2]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
                            allsquare[1][MY-2]->label->show();
                            change.append(allsquare[1][MY-2]);
                        }
                        else
                        {
                            cat->X=MX-2;
                            cat->Y=1;
                            cat->label->setGeometry((MX-2)*Label_Size,Label_Size,Label_Size,Label_Size);
                            allsquare[MX-2][1]->type=wall_label;
                            allsquare[MX-2][1]->label->clear();
                            allsquare[MX-2][1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
                            allsquare[MX-2][1]->label->show();
                            change.append(allsquare[MX-2][1]);
                        }
                    cat->type=cat_label;
                    cat->label->setMovie(catgif);
                    catgif->start();
                    cat->label->show();
                    change.clear();
                }


             }
             else
             {
                if(b==1)
                {
                    delete cat->label;
                    delete cat;
                    cat=new square;
                    cat->label=new QLabel(this);
                    cat->X=1;
                    cat->Y=MY-2;
                    cat->label->setGeometry(Label_Size,(MY-2)*Label_Size,Label_Size,Label_Size);
                    cat->type=cat_label;
                    cat->label->setMovie(catgif);
                    catgif->start();
                    cat->label->show();
                    mouse->label->clear();
                }
             }
             delete donghua;
}

void maze::resizewindow()
{

    resize((MX)*Label_Size,(MY+2)*Label_Size);
    Clabel->setStyleSheet("QLabel{border-image:url(:/cover.jpg);}");
    Clabel->setGeometry(0,0,MX*Label_Size,MY*Label_Size);
    start1->setGeometry(MX * Label_Size / 2-width()/10 ,MY * Label_Size / 2,width()/5,2*height()/15);
    start1->setStyleSheet("QPushButton{border-image:url(:/m1.png);}"
                          "QPushButton:hover{border-image:url(:/m12.png);}"
                           "QPushButton:pressed{border-image:url(:/m11.png);}");
    start2->setGeometry(MX * Label_Size /2-width()/10,MY * Label_Size / 2+2*height()/15+20,width()/5,2*height()/15);
    start2->setStyleSheet("QPushButton{border-image:url(:/m2.png);}"
                          "QPushButton:hover{border-image:url(:/m22.png);}"
                           "QPushButton:pressed{border-image:url(:/m21.png);}");
    start3->setGeometry(MX * Label_Size / 2 -width()/10,MY * Label_Size / 2+4*height()/15+20,width()/5,2*height()/15);
    start3->setStyleSheet("QPushButton{border-image:url(:/m3.png);}"
                          "QPushButton:hover{border-image:url(:/m32.png);}"
                           "QPushButton:pressed{border-image:url(:/m31.png);}");
    setting->setStyleSheet("QPushButton{border-image:url(:/setting.png);}"
                           "QPushButton:hover{border-image:url(:/setting2.png);}"
                           );
    setting->setGeometry(4*MX/5*Label_Size,MY*Label_Size,2*Label_Size,2*Label_Size);
    presentation->setGeometry(1*MX/5*Label_Size,MY*Label_Size,2*Label_Size,2*Label_Size);
    presentation->setStyleSheet("QPushButton{border-image:url(:/present.png);}"
                                "QPushButton:hover{border-image:url(:/present2.png);}"
                                 "QPushButton:pressed{border-image:url(:/present1.png);}");
}
maze::~maze()
{
    if(allsquare==nullptr){;}
    else {for(int i=0;i<MX;i++)
     {

        for (int j=0;j<MY;j++)
        {
            delete allsquare[i][j];
        }
        delete [] allsquare[i];
     }
    delete [] allsquare;}
}

