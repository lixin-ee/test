#include "snake.h"
#include "ui_snake.h"
#include <QMessageBox>
#include <QString>
#include <QtDebug>
#include <windows.h>
#include <QThread>
#include <QStyle>

Snake::Snake(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Snake)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/image/logo.ico"));

    score = 0;
    level = 1;

    this->setWindowTitle("Snake");
    this->resize((MAX_X + 7) * Lable_Size,MAX_Y * Lable_Size); //窗体大小

    startButton = new QPushButton("StartGame",this);
    startButton->setStyleSheet("font-size:20px;QPushButton{ background-color: rgb(143,122,102); border-radius: 10px; font: bold; color: white; }");

    startButton->setGeometry(MAX_X * Lable_Size / 2 - 80,MAX_Y * Lable_Size / 2 - 40,160,80);

    mLabel = new QLabel(this);
    mLabel->setStyleSheet("font-size:30px;");

    //mLabel->setGeometry(MAX_X * Lable_Size,Lable_Size,6 * Lable_Size,(MAX_Y - 2) * Lable_Size);
    mLabel->setGeometry( MAX_X *Lable_Size,Lable_Size,6 * Lable_Size,(MAX_Y - 2) * Lable_Size);


    mLabel->setAlignment(Qt::AlignCenter);//函数setAlignment()主要将是消除布局中的空隙，让两个控件紧紧挨在一起
    // 将分数转换为QString类型
    viewText = QString::number (score,10);
    mLabel->setText("分数:" + viewText +'\n' + "关数:" + QString::number (level,10));
    mLabel->show();




    init();         // 初始化游戏窗口
    drawBorder();
    initSnake();
    //drawViewArea();

    QObject::connect(&timer,SIGNAL(timeout()),this,SLOT(snakeMoveSlots()));
    QObject::connect(startButton,SIGNAL(clicked()),this,SLOT(startGameSlots()));
    Sleep(2000);    // 显示开始画面
}

Snake::~Snake()
{
    delete ui;
}


// 画出显示分数区域的边界
void Snake::drawViewArea() {
    for(int x = MAX_X; x < MAX_X + 7; x++) {
        for(int y = 0; y < MAX_Y; y += MAX_Y - 1) {
            QLabel *label = new QLabel(this);
            label->setStyleSheet("background:gray");
            label->setGeometry(x * Lable_Size, y * Lable_Size, Lable_Size - 1, Lable_Size - 1);
        }
    }

    for(int y = 1; y < MAX_Y - 1; y++) {
        QLabel *label = new QLabel(this);
        label->setStyleSheet("background:gray");
        label->setGeometry(( MAX_X+6) * Lable_Size, y * Lable_Size, Lable_Size - 1, Lable_Size - 1);
    }

}

// 初始化游戏
void Snake::init() {
    foodCount = 0;
    moveSpeed = 400;
    // 先把所有的label都初始化为NORMAL类型
    for(int x = 0; x < MAX_X; x++) {
        for(int y = 0; y < MAX_Y; y++) {
            QLabel *label = new QLabel(this);
            label->setStyleSheet("background:gray");
            label->setGeometry(x * Lable_Size, y * Lable_Size, Lable_Size - 1, Lable_Size - 1);
            label->hide();

            snake_label[x][y] = new snakeNode;
            snake_label[x][y]->label = label;
            snake_label[x][y]->type = Normal_label;
            snake_label[x][y]->x = x;
            snake_label[x][y]->y = y;
        }
    }
}




// 画边界
void Snake::drawBorder() {
    for(int x = 0; x < MAX_X; x++) {
        for(int y = 0; y < MAX_Y; y++) {
            if(x == 0 || y == 0 || x == MAX_X -1 || y == MAX_Y - 1) {
                snake_label[x][y]->label->setStyleSheet("background:gray");
                snake_label[x][y]->label->show();
                snake_label[x][y]->type = Border_label;
            }
        }
    }
}


// 初始化蛇
void Snake::initSnake() {
    int snakeLen = 1;   // 蛇长
    int snakeX = 5;  // 蛇头初始化坐标
    int snakeY = 6;

    dX = 1;
    dY = 0;
    snake.clear();      // 清除蛇身
    // 将蛇结点追加到表尾，表尾即蛇头
    for(int x = snakeX; x < snakeX + snakeLen; x++) {
        snake.append(snake_label[x][snakeY]);
        snake.at(snake.length() - 1)->x = x;
        snake.at(snake.length() - 1)->y = snakeY;
        snake_label[x][snakeY]->type = Snake_label;
        //snake_label[x][snakeY]->label->setStyleSheet("background-color:#6ea8c9");
        snake_label[x][snakeY]->label->setStyleSheet("QLabel{border-image: url(:/image/image/head.png);}");
        snake_label[x][snakeY]->label->show();
    }
}

// 移动操作
void Snake::moveSnake() {
    // 获取蛇头和蛇尾指针
    getHeadTail();
    // 由键盘事件获得的方向来确定蛇头的位置
    snakeNode *tempNode = snake_label[head->x + dX][head->y + dY];
    tempNode->label->setStyleSheet("QLabel{border-image: url(:/image/image/tail.png);}");
   // tempNode->label->setStyleSheet("background-color:#6ea8c9");
    tempNode->label->show();
    // 游戏结束检测，撞到自己和边界即游戏结束
    if(tempNode->type == Border_label || tempNode->type == Snake_label) {
        tempNode->label->setStyleSheet("background:gray");
        gameOver();     // 游戏结束
    } else {
        // 吃到食物
        if(tempNode->type == Food_label) {
            showViewArea();
            tempNode->type = Snake_label;
            snake.append(tempNode); // 追加到末尾，不隐藏蛇尾
            createFood();           // 生成新的食物
        } else {
            tempNode->type = Snake_label;
            snake.append(tempNode);
            tail->label->hide();    // 将蛇尾隐藏
            tail->type = Normal_label;
            // 删除表头，即蛇尾
            snake.removeFirst();
        }
    }
}

// 游戏结束
void Snake::gameOver() {
    score = 0;      // 初始化数据
    level = 1;
    foodCount = 0;
    moveSpeed = 400;
    timer.stop();   // 计时器停止
    QMessageBox::information(this,"Message:","Game is over! Do you want to try it again?",QMessageBox::Ok);
    // 等同于刷新布局操作
    for(int x = 0; x < MAX_X-1; x++) {
        for(int y = 1; y < MAX_Y-1; y++) {
            this->snake_label[x][y]->type = Normal_label;
            this->snake_label[x][y]->label->hide();
        }
    }
    // 重新绘制边界
    drawBorder();
    // 显示按钮，可以进行下一次游戏
    startButton->setEnabled(true);
    startButton->show();
}

// 显示分数和等级
void Snake::showViewArea() {
    foodCount++;
    level = (foodCount / 10) + 1;   // 等级最高为7级
    if(level >= 8) {
        level = 8;
    }
    moveSpeed = 50 * (9 - level);   // 计算移动速度
   // moveSpeed = 50 * ( level);   // 计算移动速度
    qDebug()<<moveSpeed;
    score = (foodCount/10)* 10* (level-1) + ((foodCount%10  ) * level);      // 计算分数

    viewText = QString::number (score,10);
    mLabel->setText("分数:" + viewText +'\n' + "关数:" + QString::number (level,10));
    mLabel->setAlignment(Qt::AlignCenter);
}

// 获取蛇头和蛇尾指针
void Snake::getHeadTail() {
    // 蛇头位于表的尾部，即表头为蛇尾
    head = snake.at(snake.length() - 1);
    tail = snake.at(0);

}

void Snake::snakeMoveSlots() {
    moveSnake();
}

// 开始游戏
void Snake::startGameSlots() {

    drawBorder();
    initSnake();
    moveSnake();
    createFood();
    viewText = QString::number (score,10);
    mLabel->setText("分数:" + viewText +'\n' + "关数:" + QString::number (level,10));
    // 开始移动
    timer.start(moveSpeed);
    // 设置按钮不可用，以便窗口获取焦点
    startButton->setEnabled(false);
    startButton->hide();
}

// 键盘事件
void Snake::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
    // 同方向或者反方向不做任何操作

    case Qt::Key_Left:
        if(dX != 1){
            dX = -1;
            dY = 0;
            moveSnake();
        }
        break;
    case Qt::Key_Right:
        if(dX != -1){
            dX = 1;
            dY = 0;
            moveSnake();
        }
        break;
    case Qt::Key_Up:
        if(dY != 1){
            dX = 0;
            dY = -1;
            moveSnake();
            }
        break;
    case Qt::Key_Down:
        if(dY != -1){
            dX = 0;
            dY = 1;
            moveSnake();
            }
        break;


    // 游戏暂停
    case Qt::Key_Space:
        if(timer.isActive()) {
            timer.stop();
        }else {
       timer.start();
      }
        break;
    default:
        break;
    }
}

// 生成食物
void Snake::createFood() {
    int foodX;
    int foodY;
    // 随机生成食物坐标
    srand((unsigned)time(0));
    do{
        foodX = rand()%MAX_X;
        foodY = rand()%MAX_Y;
    }while(snake_label[foodX][foodY]->type != Normal_label);
    snake_label[foodX][foodY]->type = Food_label;

   // QPixmap pixmap("/image/image/food.png");



   // snake_label[foodX][foodY]->label->setStyleSheet("background:lightblue");
    //snake_label[foodX][foodY]->label->setStyleSheet("background-color:#fed46e");
    snake_label[foodX][foodY]->label->setStyleSheet("QLabel{border-image: url(:/image/image/food.png);}");
  // snake_label[foodX][foodY]->label->setPixmap(pixmap);
    snake_label[foodX][foodY]->label->show();
}

