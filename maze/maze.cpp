#include "maze.h"
#include "ui_maze.h"
maze::maze(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::maze)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/tubiao.ico"));
    setWindowTitle("maze521");
    Clabel=new QLabel(this);
    start1=new QPushButton(this);
    start2=new QPushButton(this);
    start3=new QPushButton(this);
    setting=new QPushButton(this);
    resizewindow();
    QObject::connect(start1,SIGNAL(clicked()),this,SLOT(startgame1()));
    QObject::connect(start2,SIGNAL(clicked()),this,SLOT(startgame2()));
    QObject::connect(start3,SIGNAL(clicked()),this,SLOT(startgame3()));
    QObject::connect(setting,SIGNAL(clicked()),this,SLOT(settingslot()));
    mousegif=new QMovie(":/mouse1.gif");
    QSize s1(Label_Size+5,Label_Size+5);
    mousegif->setScaledSize(s1);       
}
void maze::startgame1()
{
    gamesta=1;
    initgame();
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
    Return=new QPushButton(this);
    Return->setFocusPolicy(Qt::NoFocus);
    Replay=new QPushButton(this);
    Replay->setFocusPolicy(Qt::NoFocus);
    clock1=new QLabel(this);
    clock2=new QLabel(this);
    printtime=new QLCDNumber(this);
    Return->setGeometry(0,MY*Label_Size,2*Label_Size,2*Label_Size);
    Return->setStyleSheet("QPushButton{border-image:url(:/return.png);}");
    Replay->setGeometry((MX-2)*Label_Size,MY*Label_Size,2*Label_Size,2*Label_Size);
    Replay->setStyleSheet("QPushButton{border-image:url(:/replay.png);}");
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
}
void maze::returnhome()//返回主界面
{
    wall.clear();
    ground.clear();
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
    delete counttimer;
    delete Return;
    delete Replay;
    delete printtime;
    delete clock1;
    delete clock2;
    delete mouse;
    delete mouse->label;
}
void maze::replay()//重玩
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
        allsquare[1][MY-2]->type=wall_label;
        allsquare[1][MY-2]->label->clear();
        allsquare[1][MY-2]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
        allsquare[1][MY-2]->label->show();
        cat->X=1;
        cat->Y=MY-2;
        cat->label->setGeometry(Label_Size,(MY-2)*Label_Size,Label_Size,Label_Size);
        cat->type=cat_label;
        for(square* a:change)
        {
            a->type = ground_label;
            a->label->clear();
            a->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
            a->label->show();
        }
        change.clear();
        cat->label->setMovie(catgif);
        catgif->start();
    }
}
void maze::startgame2()
{
    gamesta=2;
    initgame();
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
    gametime =MX*MY*0.2;
    updatetimer();
    cat=new square;
    cat->label=new QLabel(this);
    cat->X=1;
    cat->Y=MY-2;
    cat->label->setGeometry(Label_Size,(MY-2)*Label_Size,Label_Size,Label_Size);
    catgif=new QMovie(":/cat2.gif");
    allsquare[1][MY-2]->type=wall_label;
    allsquare[1][MY-2]->label->clear();
    allsquare[1][MY-2]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
    allsquare[1][MY-2]->label->show();
    QSize s2(Label_Size+10,Label_Size+10);
    catgif->setScaledSize(s2);
    cat->type=cat_label;
    cat->label->setMovie(catgif);
    catgif->start();
    cat->label->show();
    counttimer=new QTimer(this);
    QObject::connect(counttimer,SIGNAL(timeout()),this,SLOT(updatetimer()));
    QObject::connect(counttimer,SIGNAL(timeout()),this,SLOT(walk()));
    counttimer->start(1000);
    printtime->show();
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
             allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]->type=wall_label;
             allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]->label->clear();
             allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
             allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]->label->show();
             change.append( allsquare[(cat->label->x()/Label_Size)][(cat->label->y()/Label_Size)]);
         }
         cat->X=(cat->label->x()/Label_Size);
         cat->Y=(cat->label->y()/Label_Size);
    }
     if(dx1==-1||dy1==-1)
     {
         if(cat->X!=((cat->label->x()+dx1)/Label_Size)-dx1|| cat->Y!=((cat->label->y()+dy1)/Label_Size)-dy1)
         {
             allsquare[((cat->label->x()+dx1)/Label_Size)-dx1][((cat->label->y()+dy1)/Label_Size)-dy1]->type=wall_label;
             allsquare[((cat->label->x()+dx1)/Label_Size)-dx1][((cat->label->y()+dy1)/Label_Size)-dy1]->label->clear();
             allsquare[((cat->label->x()+dx1)/Label_Size)-dx1][((cat->label->y()+dy1)/Label_Size)-dy1]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
             allsquare[((cat->label->x()+dx1)/Label_Size)-dx1][((cat->label->y()+dy1)/Label_Size)-dy1]->label->show();
             change.append( allsquare[(cat->label->x()/Label_Size)-dx1][(cat->label->y()/Label_Size)-dy1]);
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
        }
    }
    for(int i=0;i<MX;i=i+2)
        {
            for(int j=0;j<MY;j=j+1)
            {
                allsquare[i][j]->type=wall_label;
                allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
                allsquare[i][j]->label->show();
                wall.append(allsquare[i][j]);
            }
        }

    for(int i=1;i<MX;i=i+2)
    {
        for (int j=0;j<MY;j=j+2)
        {
           /* allsquare[i][j]->type=wall_label;
            allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
            allsquare[i][j]->label->show();
            wall.append(allsquare[i][j]);*/
            //此处把ground改为wall
            allsquare[i][j]->type=wall_label;
            allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
            allsquare[i][j]->label->show();
            wall.append(allsquare[i][j]);
        }
    }
    int counter=0;
    for(int i=1;i<MX;i=i+2)
    {
        for (int j=1;j<MY;j=j+2)
        {
            //此处把ground改为wall
            allsquare[i][j]->type=wall_label;
            allsquare[i][j]->path=counter;
            allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
            allsquare[i][j]->label->show();
            wall.append(allsquare[i][j]);
            counter++;
        }
    }
    srand(time(0));
    destructwall();
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
      QLabel* length=new QLabel(setwindowsize);
      QLabel* width=new QLabel (setwindowsize);
      length->setText("长度:");
      width->setText("宽度:");
      length->setGeometry(30,50,40,40);
      width->setGeometry(30,100,40,40);
      setwindowsize->resize(400,400);
      save->setGeometry(50,300,100,50);
      cancle->setGeometry(250,300,100,50);
      L->setOrientation(Qt::Horizontal);
      W->setOrientation(Qt::Horizontal);
      L->setGeometry(60,50,300,50);
      W->setGeometry(60,100,100,50);
      L->setRange(6,26);
      L->setSingleStep(1);
      W->setRange(8,16);
      W->setSingleStep(1);
      L->setValue((MX+1)/2);
      W->setValue((MY+1)/2);
      QObject::connect(save,SIGNAL(clicked()),setwindowsize,SLOT(accept()));
      QObject::connect(cancle,SIGNAL(clicked()),setwindowsize,SLOT(reject()));
      if(setwindowsize->exec()==QDialog::Accepted)
      {
          MX=2*(L->value())-1;MY=2*(W->value())-1;
          resizewindow();
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

void maze::movemouse2()//响应键盘的移动函数，要有必要的判断，判断是否有墙
{
    square* tempMouse=allsquare[mouse->X+dx][mouse->Y+dy];//设置临时的指针，先让老鼠移动在判断是否有墙

        if(tempMouse->type==wall_label)//如果老鼠撞到了墙
        {
            tempMouse->type=ground_label;
        }
        else//如果老鼠没有撞到墙
        {
            if(tempMouse->type==food_label)
                gameover(1,0);
            else
                {
                tempMouse->type=mouse_label;
                allsquare[mouse->X][mouse->Y]->type=ground_label;
                allsquare[mouse->X][mouse->Y]->label->clear();
                allsquare[mouse->X][mouse->Y]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                allsquare[mouse->X][mouse->Y]->label->show();
                allsquare[mouse->X+dx][mouse->Y+dy]->type=mouse_label;
                allsquare[mouse->X+dx][mouse->Y+dy]->label->setMovie(mousegif);
                mousegif->start();
                mouse=tempMouse;
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
#define m (MX-2)//row
#define n (MY-2)
#define down 1
#define right 2
#define left 4
#define up 8
#define WALL -1
#define NOTHING 2

    struct block {
        int row, column, direction;
        block(int _row, int _column, int _direction) {
            row = _row;
            column = _column;
            direction = _direction;
        }
    };
    struct point {
        int x;
        int y;
    }start, end;

    vector<block> myblock;
    int x_num = 1, y_num = 1;//矿工位置
    int G[100][100];

    //将地图全部置为墙
    memset(G, WALL, sizeof(G));
    //定义起始点
    G[1][1] = NOTHING;
    start.x = start.y = 1;

    if (x_num + 1 <= m && G[x_num + 1][y_num] == WALL) {//down
        myblock.push_back(block(x_num + 1, y_num, down));
    }
    if (y_num + 1 <= n && G[x_num][y_num + 1] == WALL) {//right
        myblock.push_back(block(x_num, y_num + 1, right));
    }
    if (x_num - 1 >= 1 && G[x_num - 1][y_num] == WALL) {//up
        myblock.push_back(block(x_num - 1, y_num, up));
    }
    if (y_num - 1 >= 1 && G[x_num][y_num - 1] == WALL) {//left
        myblock.push_back(block(x_num, y_num - 1, left));
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
        case down: {
            x_num++;
            break;
        }
        case right: {
            y_num++;
            break;
        }
        case left: {
            y_num--;
            break;
        }
        case up: {
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
            if (x_num + 1 <= m && G[x_num + 1][y_num] == WALL) {//down
                myblock.push_back(block(x_num + 1, y_num, down));
            }
            if (y_num + 1 <= n && G[x_num][y_num + 1] == WALL) {//right
                myblock.push_back(block(x_num, y_num + 1, right));
            }
            if (x_num - 1 >= 1 && G[x_num - 1][y_num] == WALL) {//up
                myblock.push_back(block(x_num - 1, y_num, up));
            }
            if (y_num - 1 >= 1 && G[x_num][y_num - 1] == WALL) {//left
                myblock.push_back(block(x_num, y_num - 1, left));
            }
        }
        else {//如果不是呢？说明我们的矿工挖到了一个空旷的通路上面 休息一下就好了
         //relax
        }
        //删除这堵墙(把用不了的墙删了，对于那些已经施工过了不必再施工了，同时也是确保我们能跳出循环)
        myblock.erase(myblock.begin() + randnum);
    }
    for (int i = 0; i <= m + 1; i++)
    {
        for (int j = 0; j <= n + 1; j++)
        {
            if (G[i][j] == NOTHING)
            {
                allsquare[i][j]->type = ground_label;
                allsquare[i][j]->label->clear();
                allsquare[i][j]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                allsquare[i][j]->label->show();

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
                    image->setStyleSheet("QLabel{border-image:url(:/catwin.jpg);}");
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
                 wall.clear();
                 ground.clear();
                 if(a==0)
                 {gametime=MX*MY*0.2;}
                 counttimer->start();  
                structface();
                if(b==1)
                {
                    delete cat->label;
                    delete cat;
                    cat=new square;
                    cat->label=new QLabel(this);
                    cat->X=1;
                    cat->Y=MY-2;
                    cat->label->setGeometry(Label_Size,(MY-2)*Label_Size,Label_Size,Label_Size);
                    catgif=new QMovie(":/cat2.gif");
                    allsquare[1][MY-2]->type=wall_label;
                    allsquare[1][MY-2]->label->clear();
                    allsquare[1][MY-2]->label->setStyleSheet("QLabel{border-image:url(:/wall.jpg)}");
                    allsquare[1][MY-2]->label->show();
                    QSize s2(Label_Size+10,Label_Size+10);
                    catgif->setScaledSize(s2);
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
                    catgif=new QMovie(":/cat2.gif");

                    QSize s2(Label_Size+10,Label_Size+10);
                    catgif->setScaledSize(s2);
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
    start1->setStyleSheet("QPushButton{border-image:url(:/m1.png);}");
    start2->setGeometry(MX * Label_Size /2-width()/10,MY * Label_Size / 2+2*height()/15+20,width()/5,2*height()/15);
    start2->setStyleSheet("QPushButton{border-image:url(:/m2.png);}");
    start3->setGeometry(MX * Label_Size / 2 -width()/10,MY * Label_Size / 2+4*height()/15+20,width()/5,2*height()/15);
    start3->setStyleSheet("QPushButton{border-image:url(:/m3.png);}");
    setting->setStyleSheet("QPushButton{border-image:url(:/setting.png);}");
    setting->setGeometry(4*MX/5*Label_Size,MY*Label_Size,2*Label_Size,2*Label_Size);
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

