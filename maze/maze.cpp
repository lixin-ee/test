#include "maze.h"
#include "ui_maze.h"
#include<QScreen>
#include<QSound>
#include <QApplication>
#include<QFile>
#include<QMessageBox>
#include<QInputDialog>
#include<QString>
#include <QStandardItemModel>
#include<QDebug>
#define m (MX-2)//row
#define n (MY-2)
#define down 1
#define right 2
#define left 4
#define up 8
#define WALL -1
#define NOTHING 2
#define ip "182.254.145.163"
//#define ip "127.0.0.1"
//#define port 25565
#define port 24798

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
struct player
{
     char name[20];
     int classic_number,entertain_number,devil_number,classic_vic,entertain_egg,devil_vic;double classic_rate,devil_rate;
    player(QString _name="",int _calssic_number=0,int _entertain_number=0,int _devil_number=0,int _classic_vic=0,
           int _entertain_egg=0,int _devil_vic=0,double _classic_rate=0,double _devil_rate=0)
    {
         qstrcpy(name,_name.toStdString().c_str());
         classic_number=_calssic_number;entertain_number=_entertain_number;devil_number=_devil_number;
         classic_vic=_classic_vic;entertain_egg=_entertain_egg;devil_vic=_devil_vic;classic_rate=_classic_rate;
         devil_rate=_devil_rate;
    }
};
    QFile file("record.dat");
    player player1,player2,player3;//player3用于天梯榜的读取
    int x_num , y_num ;//矿工位置
    vector<block> myblock;
    vector<block> Ling;
    bool flag=1;
    bool flag1=1;
    bool isfocus=1;
    block temp2(0,0,0);
    int td=0;
    int G[100][100];
    int ptime=20;
    int xtime=5000;
    int xcount=1;
    int xx=0;
    int xy=0;
    int warning=0;
    int needHamHin=1;
    int needCdHint=1;
    int needJiaHint=1;
    QLabel* xlabel;
    QPropertyAnimation *animation;
    int tempMX;
    int tempMY;
    square* tempegg=nullptr;
    //将地图全部置为墙
     int filesize=0;
     int receivesize=0;
     int pace=0;
     QFile tem_rankFile("rank.dat");
maze::maze(QWidget *parent)//mainly written by lixin
    : QWidget(parent)
    , ui(new Ui::maze)
{
        QScreen *screen=QGuiApplication::primaryScreen ();
        QRect mm=screen->availableGeometry() ;
        screen_width = mm.width();
        screen_height = mm.height();
        int temp1=0.7*screen_width/(Label_Size*2);
        MX=2*temp1+1;
        tempMX=MX;
        temp1=0.9*screen_height/(Label_Size*2);
        MY=2*temp1-1;
        tempMY=MY;
        Clabel=new QLabel(this);
        Clabel->setStyleSheet("QLabel{border-image:url(:/cover.jpg);}");
        ui->setupUi(this);
        this->setFixedSize(this->width(),this->height());
        Clabel->setGeometry(0,0,this->width(),this->height());
        setWindowIcon(QIcon(":/tubiao.ico"));
        //ui->tableWidget->hide();
        setWindowTitle("maze521.v2.0");
        mousegif=new QMovie(":/mouse1.gif");
        QSize s1(Label_Size+5,Label_Size+5);
        catgif=new QMovie(":/cat2.gif");
        QSize s2(Label_Size+10,Label_Size+10);
        mousegif->setScaledSize(s1);
        catgif->setScaledSize(s2);
        jiazaigif=new QMovie(":/jiazai.gif");
        hammer=new QPixmap(":/hammer.png");
        egg=new QPixmap(":/caidan.png");
        jia=new QPixmap(":/jia.png");
        animation = new QPropertyAnimation(this,"windowOpacity");
        xtimer=new QTimer(this);
        if(!file.open(QIODevice::ReadOnly))
                {
                    file.open(QIODevice::WriteOnly);
                    file.close();
                }
        else
        {

            if(file.read(reinterpret_cast<char*>(&player1),sizeof(player)))
            {
                file.close();
                denglu=1;
                mainscreen();
            }
            else
            {
                file.close();
            }
        }
        QObject::connect(xtimer,SIGNAL(timeout()),this,SLOT(aboutus()));
        QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(mainscreen()));
        ui->label_3->hide();
        ui->label_3->setDisabled(true);
        ui->label_4->hide();
        ui->label_4->setDisabled(true);
        ui->label_5->hide();
        ui->label_5->setDisabled(true);
        ui->label_6->hide();
        ui->label_6->setDisabled(true);
        ui->label_7->hide();
        ui->label_7->setDisabled(true);
        ui->label_8->hide();
        ui->label_8->setDisabled(true);
        ui->label_9->hide();
        ui->label_9->setDisabled(true);
        ui->label_10->hide();
        ui->label_10->setDisabled(true);
        ui->label_11->hide();
        ui->label_11->setDisabled(true);
        ui->label_12->hide();
        ui->label_12->setDisabled(true);
        ui->label_13->hide();
        ui->label_13->setDisabled(true);
        ui->label_14->hide();
        ui->label_14->setDisabled(true);
        ui->label_15->hide();
        ui->label_15->setDisabled(true);
        ui->label_16->hide();
        ui->label_16->setDisabled(true);
        ui->label_17->hide();
        ui->label_17->setDisabled(true);
        ui->label_18->hide();
        ui->label_18->setDisabled(true);
        ui->label_19->hide();
        ui->label_19->setDisabled(true);
        ui->label_20->hide();
        ui->label_20->setDisabled(true);
        ui->label_21->hide();
        ui->label_21->setDisabled(true);
        ui->label_22->hide();
        ui->label_22->setDisabled(true);
        ui->label_23->hide();
        ui->label_23->setDisabled(true);
        ui->label_24->hide();
        ui->label_24->setDisabled(true);
        ui->label_25->hide();
        ui->label_25->setDisabled(true);
        ui->label_26->hide();
        ui->label_26->setDisabled(true);
}
/*void maze::exit()
{
    int temp1=0.7*screen_width/(Label_Size*2);
    MX=2*temp1+1;
    temp1=0.9*screen_height/(Label_Size*2);
    MY=2*temp1-1;
    resize(MX*Label_Size,(MY+2)*Label_Size);
    Clabel->setGeometry(0,0,MX*Label_Size,MY*Label_Size);
    denglu=1;
    delete back;
    delete rank;
    delete aboutme;
    delete setting;
    delete start1;
    delete start2;
    delete start3;
    delete presentation;
    ui->label_2->show();
    ui->label->setDisabled(false);
    ui->label->show();
    ui->lineEdit->show();
    ui->pushButton->show();
    ui->pushButton->setDisabled(false);
    name="";
    if(file.open(QIODevice::WriteOnly))
    {
        file.seek(file.size());
        file.write(reinterpret_cast<char*>(&player1),sizeof(player1));
        file.close();
    }
}*/
void maze::mainscreen()
{
    if(!denglu)
    {
        if(ui->lineEdit->text()==NULL)
      {
            QMessageBox::information(NULL,"注册","昵称不能为空");//提示不能为空，messagebox怎么用，去看expclient里面我用过
      }
        else
      {
        if(ui->lineEdit->text().count()>5)
        {
            QMessageBox::information(NULL,"注册","昵称字数超过5，请重新输入");
        }
        else{
            mysocket=new QTcpSocket(this);
            mysocket->connectToHost(ip,port);
            QString tempstr='<'+ui->lineEdit->text()+'>';

            QDialog* wait=new QDialog(this);
            QTimer* temptimer=new QTimer(wait);
            temptimer->start(2000);
            wait->resize(200,200);
            wait->setWindowOpacity(0.8);
            wait->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
            wait->setWindowModality(Qt::WindowModal);
            QLabel* templabel=new QLabel(wait);
            QLabel* templabel1=new QLabel("正在加载中(*^_^*)",wait);
            templabel->setMovie(jiazaigif);
            templabel->setGeometry(50,50,110,110);
            templabel1->setGeometry(50,150,150,50);
            templabel->show();
            templabel1->show();
            jiazaigif->start();
            wait->show();
            while(mysocket->state()!=QAbstractSocket::ConnectedState)
            {
                if(temptimer->remainingTime()==0)
                {
                    break;
                }
                QCoreApplication::processEvents();
            }
            wait->close();
            delete wait;
            if(mysocket->state()==QAbstractSocket::ConnectedState)
            {
                mysocket->write(tempstr.toUtf8());
                QObject::connect(mysocket,&QTcpSocket::readyRead,[&]()
                {
                    QByteArray tempbyte=mysocket->readAll();
                    //报服务器检查是否可注册
                    if(tempbyte=="注册失败")
                    {
                        QMessageBox::information(NULL,"注册","昵称重复，请重新定义你的用户名");//提示名称重复
                        QString info="结束";
                        mysocket->write(info.toUtf8());//服务器主动断开
                        while(mysocket->state()!=QAbstractSocket::UnconnectedState)
                        {
                            QCoreApplication::processEvents();
                        }
                        mysocket->deleteLater();
                    }//失败
                    if(tempbyte=="注册成功")
                    {
                      qstrcpy(player1.name,ui->lineEdit->text().toStdString().c_str());
                      file.open(QIODevice::WriteOnly);
                      file.write((char*)&player1,sizeof(player));
                      file.close();
                      QString info="结束";
                      mysocket->write(info.toUtf8());//服务器主动断开
                      while(mysocket->state()!=QAbstractSocket::UnconnectedState)
                      {
                          QCoreApplication::processEvents();
                      }
                      denglu=1;
                      mainscreen();
                      mysocket->deleteLater();
                    }//成功

                });
            }
            else
            {
                QMessageBox::information(NULL,"服务器连接","服务器连接失败/(ㄒoㄒ)/~~，请稍后再试！！");
            }

         }
     }
}
    if(denglu)
    {
    start1=new QPushButton(this);
    start2=new QPushButton(this);
    start3=new QPushButton(this);
    setting=new QPushButton(this);
    presentation=new QPushButton(this);
    ui->label_2->hide();
    ui->label->setDisabled(true);
    ui->label->hide();
    ui->lineEdit->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_2->setDisabled(true);
    ui->textEdit->hide();
    ui->pushButton->setDisabled(true);
    if(!isyouke)
    {
    rank=new QPushButton(this);
    aboutme=new QPushButton(this);
    QObject::connect(aboutme,SIGNAL(clicked()),this,SLOT(aboutme_()));
    QObject::connect(rank,SIGNAL(clicked()),this, SLOT(rank_()));
    rank->show();
    aboutme->show();
    }
    start1->show();
    start2->show();
    start3->show();
    setting->show();
    presentation->show();
    resizewindow();
    QObject::connect(start1,SIGNAL(clicked()),this,SLOT(startgame1()));
    QObject::connect(start2,SIGNAL(clicked()),this,SLOT(startgame2()));
    QObject::connect(start3,SIGNAL(clicked()),this,SLOT(startgame3()));
    QObject::connect(setting,SIGNAL(clicked()),this,SLOT(settingslot()));
    QObject::connect(presentation,SIGNAL(clicked()),this,SLOT(present()));
    }

}
void maze::aboutus()//mainly written by lixin
{

    switch(xcount)
    {
    case 1:
        player1.entertain_egg=player1.entertain_egg+1;
        Return->setDisabled(true);
        Replay->setDisabled(true);
        so=new QSound(":/heirentaiguan.wav");
        so->play();
        xlabel=new QLabel(this);
        xlabel->setStyleSheet("QLabel{border-image:url(:/t3.jpg);}");
        xlabel->setGeometry(0,0,MX*Label_Size,MY*Label_Size);
         xlabel->show();
        animation->setDuration(xtime-4800);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start();
        for(int i=0;i<MX;i++)
        {
            for (int j=0;j<MY;j++)
            {
             allsquare[i][j]->label->hide();
            }
        }
        mouse->label->hide();
        xcount++;
        break;
    case 2:
        xlabel->setStyleSheet("QLabel{border-image:url(:/t1.png);}");
        xlabel->setGeometry(0,0,MX*Label_Size,MY*Label_Size);

        animation->setDuration(xtime-3000);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start();
        xcount++;
        break;
    case 3:
        xlabel->setStyleSheet("QLabel{border-image:url(:/t2.png);}");
        xlabel->setGeometry(0,0,MX*Label_Size,MY*Label_Size);
         xlabel->show();
        animation->setDuration(xtime-3000);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start();
        xcount++;
        break;
    case 4:
           xlabel->setStyleSheet("QLabel{border-image:url(:/t4.jpg);}");
           xlabel->setGeometry(0,0,MX*Label_Size,MY*Label_Size);
            xlabel->show();
           animation->setDuration(xtime-4500);
           animation->setStartValue(0);
           animation->setEndValue(1);
           animation->start();
           xcount++;
           break;
       case 5:
           xlabel->setStyleSheet("QLabel{border-image:url(:/t4.jpg);}");
           xlabel->setGeometry(0,0,MX*Label_Size,MY*Label_Size);
            xlabel->show();
           animation->setDuration(0);
           animation->setStartValue(0);
           animation->setEndValue(1);
           animation->start();
           xcount++;
           break;
       case 6:
           xcount=1;
           Return->setDisabled(false);
           Replay->setDisabled(false);
           animation->setDuration(xtime-3000);
           animation->setStartValue(0);
           animation->setEndValue(1);
           for(int i=0;i<MX;i++)
           {
               for (int j=0;j<MY;j++)
               {
                allsquare[i][j]->label->show();
               }
           }
           mouse->label->show();
           xtimer->stop();
           counttimer->start(1000);
           delete xlabel;
           delete so;
           allsquare[xx][xy]->label->clear();
                     allsquare[xx][xy]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                     allsquare[xx][xy]->type=ground_label;
                     if(xx==1&&xy==MY-2)
                     {
                         xx=MX-2;
                         xy=1;
                     }
                     else
                     {
                         xx=1;xy=MY-2;
                     }
                    allsquare[xx][xy]->type=x_label;
           break;
    }
}
void maze::startgame1()//mainly written by lixin
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
void maze::aboutme_()
{
    gamesta=5;
    this->setFixedSize(tempMX*Label_Size,(tempMY+2)*Label_Size);
    rank->hide();
    rank->setDisabled(true);
    aboutme->hide();
    aboutme->setDisabled(true);
    Clabel->hide();
    Clabel->setDisabled(true);
    setting->hide();
    setting->setDisabled(true);
    presentation->hide();
    presentation->setDisabled(true);

    ui->label_3->show();
    ui->label_3->setDisabled(false);
    ui->label_4->show();
    ui->label_4->setDisabled(false);
    ui->label_5->show();
    ui->label_5->setDisabled(false);
    ui->label_6->show();
    ui->label_6->setDisabled(false);
    ui->label_7->show();
    ui->label_7->setDisabled(false);
    ui->label_8->show();
    ui->label_8->setDisabled(false);

    ui->label_9->show();
    ui->label_9->setDisabled(false);
    ui->label_10->show();
    ui->label_10->setDisabled(false);
    ui->label_11->show();
    ui->label_11->setDisabled(false);
    ui->label_12->show();
    ui->label_12->setDisabled(false);
    ui->label_13->show();
    ui->label_13->setDisabled(false);
    ui->label_14->show();
    ui->label_14->setDisabled(false);
    ui->label_15->show();
    ui->label_15->setDisabled(false);
    ui->label_16->show();
    ui->label_16->setDisabled(false);
    ui->label_17->show();
    ui->label_17->setDisabled(false);

    ui->label_18->show();
    ui->label_18->setDisabled(false);
    ui->label_19->show();
    ui->label_19->setDisabled(false);
    ui->label_20->show();
    ui->label_20->setDisabled(false);
    ui->label_21->show();
    ui->label_21->setDisabled(false);
    ui->label_22->show();
    ui->label_22->setDisabled(false);
    ui->label_23->show();
    ui->label_23->setDisabled(false);
    ui->label_24->show();
    ui->label_24->setDisabled(false);
    ui->label_25->show();
    ui->label_25->setDisabled(false);
    ui->label_26->show();
    ui->label_26->setDisabled(false);


ui->label_17->setStyleSheet("QLabel{border-image:url(:/preview.jpg);}");
ui->label_17->setGeometry(0,0,tempMX*Label_Size,tempMY*Label_Size);

ui->label_10->setStyleSheet("color:yellow;");
ui->label_12->setStyleSheet("color:red;");
ui->label_9->setStyleSheet("color:yellow;");
ui->label_13->setStyleSheet("color:blue;");
ui->label_3->setStyleSheet("color:green;");
ui->label_4->setStyleSheet("color:yellow;");

    Return=new QPushButton(this);
    Return->setFocusPolicy(Qt::NoFocus);
    Return->setGeometry(0,tempMY*Label_Size,2*Label_Size,2*Label_Size);
    Return->setStyleSheet("QPushButton{border-image:url(:/return.png);}"
                          "QPushButton:hover{border-image:url(:/return2.png);}"
                           );
    QObject::connect(Return,SIGNAL(clicked()),this,SLOT(returnhome()));
    Return->show();
    start1->hide();
    start1->setDisabled(true);
    start2->hide();
    start2->setDisabled(true);
    start3->hide();
    start3->setDisabled(true);
    xiugai=new QPushButton("修改昵称",this);
    xiugai->setGeometry(tempMX*Label_Size-180,tempMY*Label_Size/2-325,100,40);//位置之后自己调节；
    xiugai->show();

    ui->label_11->setText((QString)player1.name);
    ui->label_7->setText(QString::number(player1.classic_number));
    ui->label_6->setText(QString::number(player1.entertain_number));
    ui->label_8->setText(QString::number(player1.devil_number));
    ui->label_15->setText(QString::number(player1.classic_rate*100)+"%");
    ui->label_16->setText(QString::number(player1.entertain_egg));
    ui->label_14->setText(QString::number(player1.devil_rate*100)+"%");

    ui->label_24->setText(QString::number(player1.classic_number+player1.entertain_number+player1.devil_number));
    ui->label_25->setText(QString::number(player1.classic_vic));
    ui->label_26->setText(QString::number(player1.devil_vic));

    QObject::connect(xiugai,&QPushButton::clicked,[&]()
       {
           bool issuc=false; //是否成功
           QString tempstr1;//存储修改后的昵称
           while(!issuc)
           {
             tempstr1 = QInputDialog::getText(NULL, "修改昵称", "Please input your name", QLineEdit::Normal,NULL, &issuc);
             qDebug()<<"1"<<tempstr1;
             if(issuc)
              {
                if(tempstr1==NULL)
                {
                    QMessageBox::information(NULL,"提示","昵称不能为空");
                    issuc=false;
                    continue;
                }
                if(strcmp(tempstr1.toStdString().c_str(),player1.name)==0)
                {
                  QMessageBox::information(NULL,"修改昵称","修改成功！");
                  issuc=true;
                  break;
                }//修改不变，自然成功
                if(tempstr1.count()>5)
                {
                    QMessageBox::information(NULL,"修改昵称","昵称字数大于5，请重新输入！");
                    issuc=false;
                    continue;
                }
                else
                {
                    qDebug()<<"2"<<"lianji";
                    mysocket=new QTcpSocket(this);
                    mysocket->connectToHost(ip,port);
                    mysocket->open(QIODevice::ReadWrite);
                    QString tempstr="修改昵称#"+QString(player1.name)+'#'+tempstr1;
                    //
                    //bool* lianjie=new bool(false);

                    QDialog* wait=new QDialog(this);
                    QTimer* temptimer=new QTimer(wait);
                    temptimer->start(2000);
                    wait->resize(200,200);
                    wait->setWindowOpacity(0.8);
                    wait->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
                    wait->setWindowModality(Qt::WindowModal);
                    QLabel* templabel=new QLabel(wait);
                    QLabel* templabel1=new QLabel("正在加载中(*^_^*)",wait);
                    templabel->setMovie(jiazaigif);
                    templabel->setGeometry(50,50,110,110);
                    templabel1->setGeometry(50,150,150,50);
                    templabel->show();
                    templabel1->show();
                    jiazaigif->start();
                    wait->show();
                    while(mysocket->state()!=QAbstractSocket::ConnectedState)
                    {
                        if(temptimer->remainingTime()==0)
                        {
                            break;
                        }
                        QCoreApplication::processEvents();
                    }
                    wait->close();
                    delete wait;
                    if(mysocket->state()==QAbstractSocket::ConnectedState)
                    {
                        mysocket->write(tempstr.toUtf8());
                        QObject::connect(mysocket,&QTcpSocket::readyRead,[=]()
                        {
                            QByteArray tempbyte=mysocket->readAll();
                            qDebug()<<"3"<<QString(tempbyte);
                            //报服务器检查是否可注册
                            if(tempbyte=="修改失败")
                            {
                               QMessageBox::information(NULL,"修改昵称","昵称重复，请重新定义你的用户名");
                               QString info="结束";
                               mysocket->write(info.toUtf8());//服务器主动断开
                               while(mysocket->state()!=QAbstractSocket::UnconnectedState)
                               {
                                   QCoreApplication::processEvents();
                               }
                               mysocket->deleteLater();
                                //提示名称重复
                            }//失败
                            if(tempbyte=="修改成功")
                            {
                              qstrcpy(player1.name,tempstr1.toStdString().c_str());
                              qDebug()<<"4"<<player1.name;
                              QMessageBox::information(NULL,"修改昵称","修改成功！");
                              QString info="结束";
                              mysocket->write(info.toUtf8());//服务器主动断开
                              while(mysocket->state()!=QAbstractSocket::UnconnectedState)
                              {
                                  QCoreApplication::processEvents();
                              }
                              ui->label_11->setText(tempstr1);
                              mysocket->deleteLater();
                            }//成功

                        });

                    }
                    else
                    {
                        QMessageBox::information(NULL,"服务器连接","服务器连接失败/(ㄒoㄒ)/~~，请稍后再试！！");
                    }
                }
                }
             else
             {
                 break;
             }
                }
            });
           }
//创建标准对话框获取修改后的昵称,怎么做？还是看ecpclient,同时用messagebox提示是否为空，后面不做是否为空的判断,默认不考虑是否为空，
    void maze::rank_()

    {
        mysocket=new QTcpSocket(this);
        mysocket->connectToHost(ip,port);
        QDialog* wait=new QDialog(this);
        QTimer* temptimer=new QTimer(wait);
        temptimer->start(1000);
        wait->resize(200,200);
        wait->setWindowOpacity(0.8);
        wait->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
        wait->setWindowModality(Qt::WindowModal);
        QLabel* templabel=new QLabel(wait);
        QLabel* templabel1=new QLabel("正在加载中(*^_^*)",wait);
        templabel->setMovie(jiazaigif);
        templabel->setGeometry(50,50,110,110);
        templabel1->setGeometry(50,150,150,50);
        templabel->show();
        templabel1->show();
        jiazaigif->start();
        wait->show();
        while(mysocket->state()!=QAbstractSocket::ConnectedState)
        {
            if(temptimer->remainingTime()==0)
            {
                break;
            }
            QCoreApplication::processEvents();
        }
        wait->close();
        delete wait;

        //QTemporaryFile tem_rankFile;//创建临时文件，用于接收服务器发送的排行榜的消息
        //tem_rankFile.open();
        if(mysocket->state()==QAbstractSocket::ConnectedState)
       {
        QString info="发送结构体"; //提示服务器数据的收发开始了
        mysocket->write(info.toUtf8());
        tem_rankFile.open(QIODevice::WriteOnly);
        QObject::connect(mysocket,&QTcpSocket::readyRead,[=]()mutable
        {
            qDebug()<<pace;
            QString tempstr3;
            QByteArray tempbyte;
            QString filename;
            //tem_rankFile.write(tempbyte.toStdString().data());
            if(pace==0)//第一步，向服务器发送当前的玩家信息
            {
                mysocket->write((char*)&player1,sizeof(player));
                //this_thread::sleep_for(chrono::milliseconds(100));
                /*tempstr3=QString(tempbyte);*/
                //this_thread::sleep_for(chrono::milliseconds(100));
            }

            if(pace==1)//第二步，接收服务器发来的文件名和文件大小，并且将其分别放至filename和filesize中

            {
                 tempbyte=mysocket->readAll();
                tempstr3=QString(tempbyte);
                QStringList list=tempstr3.split('#');
                filesize=list[1].toInt();
                //接收包头，处理包头，
                QString info="接收包头成功";
                mysocket->write(info.toUtf8());
                //this_thread::sleep_for(chrono::milliseconds(100));
            }
           if(pace==2)//第三步，接收服务器发来的文件并将其写入创建的临时文件中

            {
                    //tem_rankFile.open(QIODevice::WriteOnly);
                    tempbyte=mysocket->readAll();
                    if(receivesize<filesize)
                    {
                        //tem_rankFile.open(QIODevice::WriteOnly);
                        //tempbyte=mysocket->readAll();
                        receivesize+=tem_rankFile.write(tempbyte);
                         qDebug()<<filesize<<receivesize;
                         pace--;
                    }
                    if(filesize<=receivesize)
                    {
                      pace++;
                    //file.close();                   //接收文件,循环直至接收文件大小与包头描述一致；
                    //this_thread::sleep_for(chrono::milliseconds(100))
                    QString info1="文件接收完毕";
                    mysocket->write(info1.toUtf8());//与服务器断开连接
                    while(mysocket->state()!=QAbstractSocket::UnconnectedState)
                    {
                        QCoreApplication::processEvents();
                    }
                    tem_rankFile.close();
                    mysocket->deleteLater();

                    QDialog * tempweight=new QDialog(this);
                    tempweight->setFixedSize(900,600);
                    tempweight->setWindowTitle("天梯榜");
                    int playerNum=tem_rankFile.size()/(sizeof(player)*3);//定义当前玩家的数量
                    // 构造了一个QTableWidget的对象，并且设置为10行，5列
                    QTableWidget *tableWidget = new QTableWidget(playerNum,3,tempweight);
                    // 也可用下面的方法构造QTableWidget对象
                    // QTableWidget *tableWidget = new QTableWidget;
                    // tableWidget->setRowCount(10); //设置行数为10
                    // tableWidget->setColumnCount(5); //设置列数为5
                    //tableWidget->setWindowTitle("QTableWidget & Item");
                    tableWidget->resize(900,600); //设置表格
                    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//将表格设置为只读

                    tableWidget->setColumnWidth(0,300);//setColumnWidth用于设置某一列的宽度
                    tableWidget->setColumnWidth(1,300);
                    tableWidget->setColumnWidth(2,300);

                    for(int i=0;i<playerNum;i++){
                        tableWidget->setRowHeight(i,100);//setRowHeight用于设置某一行的高度
                    }

                    //tableWidget->setRowHeight(1,200);

                    QStringList header;//表题
                    header<<"娱乐彩蛋榜"<<"魔鬼胜率榜"<<"总场数榜";//设置表题
                    tableWidget->setHorizontalHeaderLabels(header);
                    tableWidget->horizontalHeader()->setFixedHeight(150);//加宽表头
                    QTableWidgetItem* columnHeaderItem0=tableWidget->horizontalHeaderItem(0);
                    columnHeaderItem0->setFont(QFont("SimHei",28));//设置表头字体
                    //columnHeaderItem0->setBackground(QColor(255,20,147));//设置表头背景颜色
                    columnHeaderItem0->setForeground(QColor(255,20,147));//设置文字颜色

                    QTableWidgetItem* columnHeaderItem1=tableWidget->horizontalHeaderItem(1);
                    columnHeaderItem1->setFont(QFont("SimHei",28));//设置表头字体
                    //columnHeaderItem1->setBackground(QColor(255,20,147));//设置表头背景颜色
                    columnHeaderItem1->setForeground(QColor(0,0,139));//设置文字颜色

                    QTableWidgetItem* columnHeaderItem2=tableWidget->horizontalHeaderItem(2);
                    columnHeaderItem2->setFont(QFont("SimHei",28));//设置表头字体
                    //columnHeaderItem2->setBackground(QColor(255,20,147));//设置表头背景颜色
                    columnHeaderItem2->setForeground(QColor(0,0,255));//设置文字颜色

                    QFont font=tableWidget->horizontalHeader()->font();
                    font.setBold(true);
                    tableWidget->horizontalHeader()->setFont(font);//加粗标题


                    /*QLabel* image=new QLabel(tempweight);
                    image->setStyleSheet("QLabel{border-image:url(:/caidan2.jpg)}");
                    image->setGeometry(0,0,400,300);
                    setAutoFillBackground(true);
                    image->show();
                    image->deleteLater();*/

                    /*QPalette pal;
                    QPixmap pixmap(":/caidan2.jpg");
                    pal.setBrush(QPalette::Window,QBrush(pixmap));
                    setPalette(pal);*/

                    /*QPalette palette = tempweight->palette();

                    palette.setBrush(QPalette::Active,QPalette::Window,QBrush(Qt::red));

                    tempweight->setPalette(palette);

                    tempweight->setAutoBackground(true);  */
                    tempweight->setStyleSheet("border-image:url(:/rank_background.jpg);"); //设置背景图片

                    /*tableWidget->setItem(0,0,new QTableWidgetItem("Jan"));
                    tableWidget->setItem(1,0,new QTableWidgetItem("Feb"));
                    tableWidget->setItem(2,0,new QTableWidgetItem("Mar"));

                    tableWidget->setItem(0,1,new QTableWidgetItem(QIcon(":/Image/IED.png"), "Jan's month"));
                    tableWidget->setItem(1,1,new QTableWidgetItem(QIcon(":/Image/IED.png"), "Feb's month"));
                    tableWidget->setItem(2,1,new QTableWidgetItem(QIcon(":/Image/IED.png"), "Mar's month"));*/

                    tem_rankFile.open(QIODevice::ReadOnly);
                    for(int i=0;i<playerNum;i++){
                        tem_rankFile.read((char*)&player3,sizeof (player));
                        QTableWidgetItem *item1;
                        if(QString(player3.name)==QString(player1.name)){
                            item1=new QTableWidgetItem("昵称："+QString(player3.name)+"(本人)\n娱乐场数："+QString::number(player3.entertain_number)
                                                                         +"\n娱乐彩蛋数："+QString::number(player3.entertain_egg));
                            //item1->setBackground(QColor(255,228,196));
                            item1->setForeground(QColor(0,0,255));//将玩家自己的昵称标记为蓝色
                        }else{
                            item1=new QTableWidgetItem("昵称："+QString(player3.name)+"\n娱乐场数："+QString::number(player3.entertain_number)
                                                                         +"\n娱乐彩蛋数："+QString::number(player3.entertain_egg));
                        }


                        if(i<3&&QString(player3.name)!=QString(player1.name)){
                            item1->setForeground(QColor(200,111,100));//位于前三名的玩家会用红色字体显示
                        }
                        tableWidget->setItem(i,0,item1);//写入第一列的数据
                        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文字居中
                        item1->setFont(QFont("SimHei",15));//设置字体
                        //delete item1;
                        //delete item2;
                        //delete item3;
                    }

                    for(int i=0;i<playerNum;i++){
                        tem_rankFile.read((char*)&player3,sizeof (player));
                        QTableWidgetItem *item2;
                        if(QString(player3.name)==QString(player1.name)){
                            item2=new QTableWidgetItem("昵称："+QString(player3.name)+"(本人)\n魔鬼场数："+QString::number(player3.devil_number)
                                                       +"\n魔鬼胜率："+QString::number(player3.devil_rate*100)+"%");
                            //item2->setBackground(QColor(255,228,196));
                            item2->setForeground(QColor(0,0,255));//将玩家自己的昵称标记为蓝色
                        }else{
                            item2=new QTableWidgetItem("昵称："+QString(player3.name)+"\n魔鬼场数："+QString::number(player3.devil_number)
                                                       +"\n魔鬼胜率："+QString::number(player3.devil_rate*100)+"%");
                        }
                        if(i<3&&QString(player3.name)!=QString(player1.name)){
                            item2->setForeground(QColor(200,111,100));//位于前三名的玩家会用红色字体显示
                        }
                        tableWidget->setItem(i,1,item2);//写入第二列的数据
                        item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文字居中
                        item2->setFont(QFont("SimHei",15));//设置字体
                        //delete item1;
                        //delete item2;
                        //delete item3;
                    }

                    for(int i=0;i<playerNum;i++){
                        tem_rankFile.read((char*)&player3,sizeof (player));
                        QTableWidgetItem *item3;
                        if(QString(player3.name)==QString(player1.name)){
                            item3=new QTableWidgetItem("昵称："+QString(player3.name)+"(本人)\n总场数："+QString::number(player3.devil_number+player3.classic_number+player3.entertain_number));
                            //item3->setBackground(QColor(255,228,196));
                            item3->setForeground(QColor(0,0,255));//将玩家自己的昵称标记为蓝色
                        }else{
                            item3=new QTableWidgetItem("昵称："+QString(player3.name)+"\n总场数："+QString::number(player3.devil_number+player3.classic_number+player3.entertain_number));
                        }
                        if(i<3&&QString(player3.name)!=QString(player1.name)){
                            item3->setForeground(QColor(200,111,100));//位于前三名的玩家会用红色字体显示
                        }
                        tableWidget->setItem(i,2,item3);//写入第三列的数据
                        item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文字居中
                        item3->setFont(QFont("SimHei",15));//设置字体
                        //delete item1;
                        //delete item2;
                        //delete item3;
                    }
                    tem_rankFile.close();
                    tableWidget->show();
                    tempweight->exec();
                    tempweight->deleteLater();
                    }

                }
            pace++;
            if(pace==3)
            {
                pace=0;
                filesize=0;
                receivesize=0;
            }
        });
        }
        else
        {
            QMessageBox::information(NULL,"服务器连接","服务器连接失败/(ㄒoㄒ)/~~，请稍后再试！！");
        }
        //这部分会先于数据接收执行，原因未知

        /*QLabel* image=new QLabel(this);
        image->setStyleSheet("QLabel{border-image:url(:/rank.jpg)}");

        image->setGeometry(0,0,1500,800);
        image->show();


        *///这里来添加图片

        /*if(Return->isFlat()){
            delete tableWidget;
        }*/
        //需要找一个合适的时候delete掉
}

void maze::initgame()//mainly written by lixin 初始化游戏界面
{
    if(!isyouke)
    {
    rank->hide();
    rank->setDisabled(true);
    aboutme->hide();
    aboutme->setDisabled(true);
    }
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
    isfocus=true;
    warning=0;
   //定义起始点
}
void maze::returnhome()//mainly written by lixin  返回主界面
{
    if(gamesta<5)
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
        delete mouse;
        delete mouse->label;
        delete Replay;
        delete printtime;
        delete clock1;
        delete clock2;
        if(gamesta==4)
        {delete ptimer;}
         else delete counttimer;
        if(gamesta==3)
        {
            change.clear();
            delete cat->label;
            delete cat;
            delete cattimer;
        }
        myblock.clear();
        Ling.clear();
        if(gamesta==2){
            change.clear();havehammer=0;seekegg=0;
        }
        warning=0;
        if(player1.classic_number!=0)
        {player1.classic_rate=double(player1.classic_vic)/double(player1.classic_number);}
        if(player1.devil_number!=0)
        {player1.devil_rate=double(player1.devil_vic)/double(player1.devil_number);}
 }
   delete Return;
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
   if(!isyouke)
   {
   rank->show();
   rank->setDisabled(false);
   aboutme->show();
   aboutme->setDisabled(false);
   }
   if(gamesta==5)
   {
       this->setFixedSize(MX*Label_Size,(MY+2)*Label_Size);
       ui->label_3->hide();
       ui->label_3->setDisabled(true);
       ui->label_4->hide();
       ui->label_4->setDisabled(true);
       ui->label_5->hide();
       ui->label_5->setDisabled(true);
       ui->label_6->hide();
       ui->label_6->setDisabled(true);
       ui->label_7->hide();
       ui->label_7->setDisabled(true);
       ui->label_8->hide();
       ui->label_8->setDisabled(true);
       ui->label_9->hide();
       ui->label_9->setDisabled(true);
       ui->label_10->hide();
       ui->label_10->setDisabled(true);
       ui->label_11->hide();
       ui->label_11->setDisabled(true);
       ui->label_12->hide();
       ui->label_12->setDisabled(true);
       ui->label_13->hide();
       ui->label_13->setDisabled(true);
       ui->label_14->hide();
       ui->label_14->setDisabled(true);
       ui->label_15->hide();
       ui->label_15->setDisabled(true);
       ui->label_16->hide();
       ui->label_16->setDisabled(true);
       ui->label_17->hide();
       ui->label_17->setDisabled(true);
       ui->label_18->hide();
       ui->label_18->setDisabled(true);
       ui->label_19->hide();
       ui->label_19->setDisabled(true);
       ui->label_20->hide();
       ui->label_20->setDisabled(true);
       ui->label_21->hide();
       ui->label_21->setDisabled(true);
       ui->label_22->hide();
       ui->label_22->setDisabled(true);
       ui->label_23->hide();
       ui->label_23->setDisabled(true);
       ui->label_24->hide();
       ui->label_24->setDisabled(true);
       ui->label_25->hide();
       ui->label_25->setDisabled(true);
       ui->label_26->hide();
       ui->label_26->setDisabled(true);
       delete xiugai;
   }
}
void maze::replay()//mainly written by
{
    if(gamesta!=4)
     {
        isfocus=true;
    gametime =MX*MY*0.2;
    updatetimer();
    counttimer->start(1000);
    mouse->label->clear();
    mouse->X=1;
    mouse->Y=1;
    mouse->label->setGeometry(Label_Size,Label_Size,Label_Size,Label_Size);
    mouse->label->setMovie(mousegif);
    mousegif->start();
    mouse->label->show();
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
       change[0]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
       change[0]->label->setPixmap(*hammer);
       change[0]->label->setScaledContents(true);
       change[0]->label->show();
       change.clear();
    }
    if(gamesta==2&&seekegg==1)
    {
       seekegg=0;
       tempegg->type=egg_label;
       tempegg->label->setPixmap(*egg);
       tempegg->label->setScaledContents(true);
       tempegg->label->show();

    }
    if(gamesta==2)
    {
        allsquare[xx][xy]->label->clear();
        allsquare[xx][xy]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
        allsquare[xx][xy]->type=ground_label;
        if(xx==1&&xy==MY-2)
        {
            xx=MX-2;
            xy=1;
        }
        else
        {
            xx=1;xy=MY-2;
        }
    }
    }
    warning=0;
    switch(gamesta)
       {
        case 1:
       {
           player1.classic_number=player1.classic_number+1;
           break;
       }
        case 2:
       {
           player1.entertain_number=player1.entertain_number+1;
           break;
       }

        case 3:
       {
           player1.devil_number=player1.devil_number+1;
           break;
       }

       }
}
void maze::startgame2()//mainly written by huanghaoxiang
{
    gamesta=2;
    initgame();
    destructwall();
    srand(time(0));
    //generateham();
    int hamX=(rand()%(MX-5))+2;
    int hamY=(rand()%(MY-5))+2;
    while(allsquare[hamX][hamY]->type!=ground_label)
    {hamX+=1;hamY+=1;
    if (hamX==MX-1||hamY==MY-1)
    {
        hamX=(rand()%(MX-5))+2;
        hamY=(rand()%(MY-5))+2;
    }
    }
    allsquare[hamX][hamY]->type=hammer_label;
    allsquare[hamX][hamY]->label->setPixmap(*hammer);
    allsquare[hamX][hamY]->label->setScaledContents(true);
    allsquare[hamX][hamY]->label->show();
   //generateegg();
    int eggX=(rand()%(MX-5))+2;
    int eggY=(rand()%(MY-5))+2;
    while(allsquare[eggX][eggY]->type!=ground_label)
    {eggX+=1;eggY+=1;
        if (eggX==MX-1||eggY==MY-1)
        {
            eggX=(rand()%(MX-5))+2;
            eggY=(rand()%(MY-5))+2;
        }}
    allsquare[eggX][eggY]->type=egg_label;
    allsquare[eggX][eggY]->label->setPixmap(*egg);
    allsquare[eggX][eggY]->label->setScaledContents(true);
    allsquare[eggX][eggY]->label->show();
   //generatejia();
    int jiaX=(rand()%(MX-5))+2;
    int jiaY=(rand()%(MY-5))+2;
    while(allsquare[jiaX][jiaY]->type!=ground_label)
    {jiaX+=1;jiaY+=1;
        if (jiaX==MX-1||jiaY==MY-1)
        {
            jiaX=(rand()%(MX-5))+2;
            jiaY=(rand()%(MY-5))+2;
        }}
    allsquare[jiaX][jiaY]->type=jia_label;
    allsquare[jiaX][jiaY]->label->setPixmap(*jia);
    allsquare[jiaX][jiaY]->label->setScaledContents(true);
    allsquare[jiaX][jiaY]->label->show();

    if(xx==1&&xy==MY-2)
    {
        xx=MX-2;
        xy=1;
    }
    else
    {
        xx=1;xy=MY-2;
    }
    gametime =MX*MY*0.2;
    updatetimer();
    counttimer=new QTimer(this);
    QObject::connect(counttimer,SIGNAL(timeout()),this,SLOT(updatetimer()));
    counttimer->start(1000);
    printtime->show();

}
void maze::startgame3()//mainly written by houyujie
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
void maze::dwall()//mainly written by lixin
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
void maze::present()//mainly written by lixin
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
void maze::walk()//mainly written by houyujie
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
void maze::movecat()//mainly written by houyujie响应键盘的移动函数，要有必要的判断，判断是否有墙
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

void maze::structface()//mainly written by lixin and jiashenghao
{
    switch(gamesta)
       {
        case 1:
       {
           player1.classic_number=player1.classic_number+1;
           break;
       }
        case 2:
       {
           player1.entertain_number=player1.entertain_number+1;
           break;
       }

        case 3:
       {
           player1.devil_number=player1.devil_number+1;
           break;
       }

       }
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
void maze::settingslot()//mainly written by lixin 设置地图大小的函数
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
void maze::keyPressEvent(QKeyEvent *event)//mainly wroten by jiashenghao 键盘控制部分
{
    switch (event->key())
    {
    case Qt::Key_Up:
        dx=0;
        dy=-1;
        if(gamesta==1&&isfocus)
            movemouse();
        if(gamesta==2&&isfocus)
            movemouse2();
        if(gamesta==3&&isfocus)
            movemouse3();
        break;
    case Qt::Key_Down:
        dx=0;
        dy=1;
        if(gamesta==1&&isfocus)
            movemouse();
        if(gamesta==2&&isfocus)
            movemouse2();
        if(gamesta==3&&isfocus)
            movemouse3();
        break;
    case Qt::Key_Left:
        dx=-1;
        dy=0;
        if(gamesta==1&&isfocus)
            movemouse();
        if(gamesta==2&&isfocus)
            movemouse2();
        if(gamesta==3&&isfocus)
            movemouse3();
        break;
    case Qt::Key_Right:
        dx=1;
        dy=0;
        if(gamesta==1&&isfocus)
            movemouse();
        if(gamesta==2&&isfocus)
            movemouse2();
        if(gamesta==3&&isfocus)
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
void maze::movemouse()//mainly written by jiashenghao 响应键盘的移动函数，要有必要的判断，判断是否有墙
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
        if(mouse->label->y()%Label_Size==0||(mouse->label->y()+3)%Label_Size==0||(mouse->label->y()-3)%Label_Size==0
                        ||(mouse->label->y()+6)%Label_Size==0||(mouse->label->y()-6)%Label_Size==0)
        {
            if((mouse->label->y()+3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()+3);
                        }
                        if((mouse->label->y()-3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()-3);
                        }
                        if((mouse->label->y()+6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()+6);
                        }
                        if((mouse->label->y()-6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()-6);
                        }
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
        if(mouse->label->x()%Label_Size==0||(mouse->label->x()+3)%Label_Size==0||(mouse->label->x()-3)%Label_Size==0
                        ||(mouse->label->x()+6)%Label_Size==0||(mouse->label->x()-6)%Label_Size==0)
        {
            if((mouse->label->x()+3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()+3,mouse->label->y());
                        }
                        if((mouse->label->x()-3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()-3,mouse->label->y());
                        }
                        if((mouse->label->x()+6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()+6,mouse->label->y());
                        }
                        if((mouse->label->x()-6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()-6,mouse->label->y());
                        }
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
void maze::movemouse3()//mainly written by houyujie 响应键盘的移动函数，要有必要的判断，判断是否有墙
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
        if(mouse->label->y()%Label_Size==0||(mouse->label->y()+3)%Label_Size==0||(mouse->label->y()-3)%Label_Size==0
                        ||(mouse->label->y()+6)%Label_Size==0||(mouse->label->y()-6)%Label_Size==0)
        {
            if((mouse->label->y()+3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()+3);
                        }
                        if((mouse->label->y()-3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()-3);
                        }
                        if((mouse->label->y()+6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()+6);
                        }
                        if((mouse->label->y()-6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()-6);
                        }
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
        if(mouse->label->x()%Label_Size==0||(mouse->label->x()+3)%Label_Size==0||(mouse->label->x()-3)%Label_Size==0
                        ||(mouse->label->x()+6)%Label_Size==0||(mouse->label->x()-6)%Label_Size==0)
        {
            if((mouse->label->x()+3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()+3,mouse->label->y());
                        }
                        if((mouse->label->x()-3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()-3,mouse->label->y());
                        }
                        if((mouse->label->x()+6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()+6,mouse->label->y());
                        }
                        if((mouse->label->x()-6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()-6,mouse->label->y());
                        }
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

void maze::movemouse2()//mainly written by huanghaoxiang 响应键盘的移动函数，要有必要的判断，判断是否有墙
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
    jiaHint(needJiaHint);
    if(dy==0)
    {
        if(mouse->label->y()%Label_Size==0||(mouse->label->y()+3)%Label_Size==0||(mouse->label->y()-3)%Label_Size==0
                        ||(mouse->label->y()+6)%Label_Size==0||(mouse->label->y()-6)%Label_Size==0)
        {
            if((mouse->label->y()+3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()+3);
                        }
                        if((mouse->label->y()-3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()-3);
                        }
                        if((mouse->label->y()+6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()+6);
                        }
                        if((mouse->label->y()-6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x(),mouse->label->y()-6);
                        }
            square* tempMouse=allsquare[mouse->X+dx][mouse->Y+dy];//设置临时的指针，先让老鼠移动在判断是否有墙

            if(tempMouse->type==hammer_label)
           {
                hamHint(needHamHin);

               tempMouse->type=ground_label;
               tempMouse->label->clear();
               tempMouse->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                tempMouse->label->show();
               havehammer=1;
            change.append(tempMouse);}

            if(tempMouse->type==egg_label)
           {
                cdHint(needCdHint);
                allsquare[xx][xy]->type=x_label;
               tempMouse->type=ground_label;
               tempMouse->label->clear();
               tempMouse->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                tempMouse->label->show();
               seekegg=1;
               tempegg=tempMouse;
           }

          if(tempMouse->type==jia_label)
          {
          gameover(0,0);
           }
          if(tempMouse->type==x_label)
          {
              if(xcount==1)
              {aboutus();
              xtimer->start(xtime);
              counttimer->stop();}
          }
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
        if(mouse->label->x()%Label_Size==0||(mouse->label->x()+3)%Label_Size==0||(mouse->label->x()-3)%Label_Size==0
                        ||(mouse->label->x()+6)%Label_Size==0||(mouse->label->x()-6)%Label_Size==0)
        {
            if((mouse->label->x()+3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()+3,mouse->label->y());
                        }
                        if((mouse->label->x()-3)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()-3,mouse->label->y());
                        }
                        if((mouse->label->x()+6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()+6,mouse->label->y());
                        }
                        if((mouse->label->x()-6)%Label_Size==0)
                        {
                            mouse->label->move(mouse->label->x()-6,mouse->label->y());
                        }
            square* tempMouse=allsquare[mouse->X+dx][mouse->Y+dy];//设置临时的指针，先让老鼠移动在判断是否有墙

            if(tempMouse->type==hammer_label)
           {
                hamHint(needHamHin);
               tempMouse->type=ground_label;
                tempMouse->label->clear();
               tempMouse->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
               havehammer=1;change.append(tempMouse);}

            if(tempMouse->type==egg_label)
           {
                cdHint(needCdHint);
               allsquare[xx][xy]->type=x_label;
               tempMouse->type=ground_label;
               tempMouse->label->clear();
               tempMouse->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
                tempMouse->label->show();
               seekegg=1;
               tempegg=tempMouse;
            }

            if(tempMouse->type==jia_label)
            {
            gameover(0,0);
            }
            if(tempMouse->type==x_label)
            {
                if(xcount==1)
                {aboutus();
                xtimer->start(xtime);
                counttimer->stop();}
            }
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
   if(seekegg)
{
          int mx=mouse->X;int my=mouse->Y;
        if((mx-xx)<=2&&(xx-mx)<=2&&(xy-my)<=2&&(my-xy)<=2)
        {
            if(xl==nullptr)
            {
               xl=new QPixmap(":/xuanwo.png");
               allsquare[xx][xy]->label->setPixmap(*xl);
               allsquare[xx][xy]->label->setScaledContents(true);
               allsquare[xx][xy]->label->show();
            }
        }
        else
        {
            if(xl!=nullptr)
            {
                delete xl;
                xl=nullptr;
             allsquare[xx][xy]->label->clear();
             allsquare[xx][xy]->label->setStyleSheet("QLabel{border-image:url(:/diban.jpg)}");
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

/*void maze::destructwall0()//打通前往终点路线的函数，未使用prim算法，重写的时候可以整个函数注释掉，然后再重新写一遍destructwall
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
void maze::destructwall()//mainly written by jiashenghao   该函数借鉴于CSDN上用户god_speed、的函数
/*由于自己做出来的地图效果不是很理想，因此在网上搜了有关随机构造地图的好的算法，该函数引自CSDN上用户god_speed、的函数，在此基础上做了一定的修改，使其能够配套这个迷宫来使用。其原理如下：
1.通过宏来定义各种各样的标签，在构造地图的时候清楚地知道数组的每一个元素分别代表了什么，注意到把m和n即长和宽分别定义了MX-2和MY-2是因为在砸墙的过程中要保证边缘的墙不会被砸掉。
2.定义一个结构体block，共有三个数据成员分别是行，列，方向，表示这堵墙所在的行数和列数以及它相对于定位到他的空地的方向。
3.定义一个结构体point，有两个数据成员x和y，以及两个对象start和end，用来指示开始和结束时的方格坐标。
4.用矢量vector，用block作为其类型，之后在砸墙和补墙中用。
5.定义两个int型数作为“矿工”的位置—即我们在不断移动寻找通路时的位置，定义一个足够大数组G用来表示整个迷宫里每个方块的状态，并将其全部初始化为墙。将起始位置的位置定义在（1，1）。
6.接下来出现一个小函数①，即四个if语句，这个模块的功能是以矿工所在位置为中心，观察上下左右四个方块，如果有方块是墙并且没有越过边界的话，就把这个墙的坐标以及关于矿工的位置放到一个block块中并放入之前定义的矢量之中。
7.下面进入一个循环，如果vector内还有元素就会一直循环直到vector中的元素全部被清空为止。
8.随机找到vector里一个元素的下标，创建临时变量将该元素对应的墙的信息复制一份，以防对原来的地图状态产生影响。让“矿工”来到我们定位到的这堵墙中。
9.根据墙的方向来确定矿工的操作，如果墙的方向相对于之前空地向下，就让矿工再向下走一格，其余方向均同理，使矿工原来在的空地、选中的墙以及矿工现在的位置在同一条直线上。
10.如果矿工现在所在的位置是一堵墙的话，表明原先的空地和这里并不联通，就把从原来空地到这里直线经过的两个格子全部打通，并且再次调用模块①，观察矿工现在所在位置四周的方格状态；如果矿工所在位置是一个空地的话，那么矿工就没有必要打通原来的空地和现在的空地，并且这个空地周围的墙一定都被勘探过了，也就是说都已经在vector里了，就不需要再勘探一遍了，此时矿工就可以原地“休息”一下。
11.无论如何，夹在中间的墙都不再需要再次勘探了，因此把它从原先的vector中删除就可以了，如果这堵墙是vector中的最后一个元素，由于矿工走的过程中始终能保证他到达过的地方都是相连的，那么表示整个迷宫都已经被打通了，砸墙过程也就结束了，就可以跳出循环了。
12.此时二维数组G中就储存了全部的地图信息，只需要把其一一对应地赋给相应地地图块即可，这样就做出了一个全连通的地图。
*/

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
void maze::updatetimer()//mainly written by lixin 主要负责显示时间
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
void maze::gameover(int a,int b)//mainly written by lixin
{

    //接下来可以做游戏结束界面，记得，先删除当前界面,除了下方栏；
    if(a==1)
    {
        switch(gamesta)
        {
            case 1:
                {player1.classic_vic++;
            break;}
            case 3:
                {player1.devil_vic++;break;}
        }
    }
    player1.classic_rate=double(player1.classic_vic)/double(player1.classic_number);
    player1.devil_rate=double(player1.devil_vic)/double(player1.devil_number);
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
                  {if(seekegg==0)
                    image->setStyleSheet("QLabel{border-image:url(:/catwin2.jpg);}");
                    else {
                          QLabel* temptext1=new QLabel("翻译：彩蛋都拿到了还能输？f 🤯 w，(╯▔皿▔)╯",donghua);
                          QLabel* temptext2=new QLabel("To find it, you did not even have to win.",donghua);
                          QLabel* temptext3=new QLabel("You just had to play searching around…",donghua);
                          image->setStyleSheet("QLabel{border-image:url(:/chenming.jpg);}");
                          temptext2->setGeometry(30,335,400,20);
                          temptext1->setGeometry(30,375,400,20);
                          temptext3->setGeometry(30,355,400,20);
                      }
                  }
                  image->setGeometry(0,0,400,300);
             QPushButton *ok=new QPushButton("OK",donghua);
             QPushButton *cancle=new QPushButton("Cancle",donghua);
             ok->setGeometry(50,300,100,30);
             cancle->setGeometry(250,300,100,30);
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
                    generateham();
                    seekegg=0;srand(time(0));
                    generateegg();
                    generatejia();
                     if(xx==1&&xy==MY-2)
                    {
                        xx=MX-2;
                        xy=1;
                    }
                    else
                    {
                        xx=1;xy=MY-2;
                    }
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
                 isfocus=false;
                if(b==1)
                {
                mouse->label->clear();
                }
             }
             delete donghua;
             warning=0;
}

void maze::generateham()//mainly written by huanghaoxiang
{
    int hamX=(rand()%(MX-5))+2;
    int hamY=(rand()%(MY-5))+2;
    while(allsquare[hamX][hamY]->type!=ground_label)
    {hamX+=1;hamY+=1;
    if (hamX==MX-1||hamY==MY-1)
    {
        hamX=(rand()%(MX-5))+2;
        hamY=(rand()%(MY-5))+2;
    }
    }
    allsquare[hamX][hamY]->type=hammer_label;
    allsquare[hamX][hamY]->label->setPixmap(*hammer);
    allsquare[hamX][hamY]->label->setScaledContents(true);
    allsquare[hamX][hamY]->label->show();

}
void maze::generateegg()//mainly written by huanghaoxiang
{
    int eggX=(rand()%(MX-5))+2;
    int eggY=(rand()%(MY-5))+2;
    while(allsquare[eggX][eggY]->type!=ground_label)
    {eggX+=1;eggY+=1;
        if (eggX==MX-1||eggY==MY-1)
        {
            eggX=(rand()%(MX-5))+2;
            eggY=(rand()%(MY-5))+2;
        }}
    allsquare[eggX][eggY]->type=egg_label;
    allsquare[eggX][eggY]->label->setPixmap(*egg);
    allsquare[eggX][eggY]->label->setScaledContents(true);
    allsquare[eggX][eggY]->label->show();

}
void maze::generatejia()//mainly written by huanghaoxiang
{
    int jiaX=(rand()%(MX-5))+2;
    int jiaY=(rand()%(MY-5))+2;
    while(allsquare[jiaX][jiaY]->type!=ground_label)
    {jiaX+=1;jiaY+=1;
        if (jiaX==MX-1||jiaY==MY-1)
        {
            jiaX=(rand()%(MX-5))+2;
            jiaY=(rand()%(MY-5))+2;
        }}
    allsquare[jiaX][jiaY]->type=jia_label;
    allsquare[jiaX][jiaY]->label->setPixmap(*jia);
    allsquare[jiaX][jiaY]->label->setScaledContents(true);
    allsquare[jiaX][jiaY]->label->show();


}

void maze::hamHint(int isneed)
{
    if(isneed)
    {
        QDialog* donghua=new QDialog(this);
        donghua->setWindowTitle("游戏提示");
        donghua->resize(400,400);
        QLabel* image=new QLabel(donghua);
        image->setStyleSheet("QLabel{border-image:url(:/HAMMER.jpg)}");
        QLabel* text=new QLabel("你获得了一把锤子！你可以用它凿穿墙壁！",donghua);
        text->setGeometry(30,300,400,20);
        image->setGeometry(0,0,400,300);
        QPushButton* ok=new QPushButton("OK",donghua);
        ok->setGeometry(150,350,100,30);
        QCheckBox* need=new QCheckBox("之后不再显示",donghua);
        need->setGeometry(30,325,400,20);
        QObject::connect(ok,SIGNAL(clicked()),donghua,SLOT(accept()));
        image->show();
        counttimer->stop();
        if(donghua->exec()==QDialog::Accepted)
        {
            if(need->isChecked()==true)
            {
                needHamHin=0;
            }

            counttimer->start();
            image->clear();
        }
        delete image;
    }

}

void maze::cdHint(int isneed)
{
    if(isneed)
    {
        QDialog* donghua=new QDialog(this);
        donghua->setWindowTitle("游戏提示");
        donghua->resize(400,400);
        QLabel* image=new QLabel(donghua);
        image->setStyleSheet("QLabel{border-image:url(:/caidan2.jpg)}");
        QLabel* text=new QLabel("你捡到了一个彩蛋！一些变化发生了！",donghua);
        text->setGeometry(30,300,400,20);
        image->setGeometry(0,0,400,300);
        QPushButton* ok=new QPushButton("OK",donghua);
        ok->setGeometry(150,350,100,30);
        QCheckBox* need=new QCheckBox("之后不再显示",donghua);
        need->setGeometry(30,325,400,20);
        QObject::connect(ok,SIGNAL(clicked()),donghua,SLOT(accept()));
        image->show();
        counttimer->stop();
        if(donghua->exec()==QDialog::Accepted)
        {
            if(need->isChecked()==true)
            {
                needCdHint=0;
            }
            counttimer->start();
            image->clear();
        }
        delete image;
    }

}

void maze::jiaHint(int isneed)
{
    if(isneed)
    {
        if(
                ((mouse->X+2<=MX-1&&allsquare[mouse->X+2][mouse->Y]->type==jia_label)
                 ||(mouse->X-2>=0&&allsquare[mouse->X-2][mouse->Y]->type==jia_label)
                ||(mouse->Y+2<=MY-1&&allsquare[mouse->X][mouse->Y+2]->type==jia_label)
                 ||(mouse->Y-2>=0&&allsquare[mouse->X][mouse->Y-2]->type==jia_label)
                ||((mouse->X+1<=MX-1&&allsquare[mouse->X+1][mouse->Y]->type==jia_label)
                   ||(mouse->X-1>=0&&allsquare[mouse->X-1][mouse->Y]->type==jia_label)
                  ||(mouse->Y+1<=MY-1&&allsquare[mouse->X][mouse->Y+1]->type==jia_label)
                   ||(mouse->Y-1>=0&&allsquare[mouse->X][mouse->Y-1]->type==jia_label)))
                &&warning==0)
        {
            QDialog* donghua=new QDialog(this);
            donghua->setWindowTitle("游戏提示");
            donghua->resize(400,400);
            QLabel* image=new QLabel(donghua);
            image->setStyleSheet("QLabel{border-image:url(:/jia2.jpg)}");
            QLabel* text=new QLabel("小心老鼠夹！它会让你输掉游戏！",donghua);
            text->setGeometry(30,300,400,20);
            image->setGeometry(0,0,400,300);
            QPushButton* ok=new QPushButton("OK",donghua);
            ok->setGeometry(150,350,100,30);
            QCheckBox* need=new QCheckBox("之后不再显示",donghua);
            need->setGeometry(30,325,400,20);

            QObject::connect(ok,SIGNAL(clicked()),donghua,SLOT(accept()));
            image->show();
            counttimer->stop();
            if(donghua->exec()==QDialog::Accepted)
            {
                if(need->isChecked()==true)
                {
                    needJiaHint=0;
                }
                counttimer->start();
                image->clear();
            }
            delete image;
            warning=1;
        }
    }

}
void maze::resizewindow()//mainly written by lixin
{

        setFixedSize((MX)*Label_Size,(MY+2)*Label_Size);
    Clabel->setStyleSheet("QLabel{border-image:url(:/cover.jpg);}");
    Clabel->setGeometry(0,0,MX*Label_Size,MY*Label_Size);
    if(!isyouke)
    {
    rank->setGeometry(MX*Label_Size-2*Label_Size,MY*Label_Size,2*Label_Size,2*Label_Size);
    rank->setStyleSheet("QPushButton{border-image:url(:/rank.png);}"
                        "QPushButton:hover{border-image:url(:/rank1.png);}"
                         "QPushButton:pressed{border-image:url(:/rank2.png);}");
    aboutme->setGeometry(1,MY*Label_Size,2*Label_Size,2*Label_Size);
    aboutme->setStyleSheet("QPushButton{border-image:url(:/aboutme.png);}"
                        "QPushButton:hover{border-image:url(:/aboutme1.png);}"
                         "QPushButton:pressed{border-image:url(:/aboutme2.png);}");
    }
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
    setting->setGeometry((4*MX/5-1)*Label_Size,MY*Label_Size,2*Label_Size,2*Label_Size);
    presentation->setGeometry(1*MX/5*Label_Size,MY*Label_Size,2*Label_Size,2*Label_Size);
    presentation->setStyleSheet("QPushButton{border-image:url(:/present.png);}"
                                "QPushButton:hover{border-image:url(:/present2.png);}"
                                 "QPushButton:pressed{border-image:url(:/present1.png);}");
}

void maze::on_pushButton_2_clicked()
{
    isyouke=true;
    denglu=true;
    mainscreen();
    ui->pushButton_2->hide();
    ui->pushButton_2->setDisabled(true);
    ui->textEdit->hide();
}
maze::~maze()//mainly written by lixin
{
    if(file.size()!=0)
        {
            if(player1.classic_number!=0)
            {
            player1.classic_rate=double(player1.classic_vic)/double(player1.classic_number);
            }
            if(player1.devil_number!=0)
            {
            player1.devil_rate=double(player1.devil_vic)/double(player1.devil_number);
            }
            if(file.open(QIODevice::WriteOnly))
            {
                file.write(reinterpret_cast<char*>(&player1),sizeof(player1));
                file.close();
            }
        }
    qDebug()<<"昵称"<<player1.name<<"classic_num"<<player1.classic_number<<"classic_vic"<<
              player1.classic_vic<<"classic_rate"<<player1.classic_rate<<"entertain-num"<<
              player1.entertain_number<<"entertain_egg"<<player1.entertain_egg<<"devil_num"<<player1.devil_number<<"devil_vic"<<
              player1.devil_vic<<"devil_rate"<<player1.devil_rate;

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


