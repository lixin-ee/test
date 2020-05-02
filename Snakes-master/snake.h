#ifndef SNAKE_H
#define SNAKE_H
#include <QWidget>
#include <QLabel>
#include <QList>
#include <QTimer>
#include <QKeyEvent>
#include <ctime>
#include <QPushButton>
#include <QFont>
#include <QLineEdit>
#include <cstdlib>
#define MAX_X 24
#define MAX_Y  20
#define Lable_Size  30 //label块大小

// label类型
//lable是用来提供文本或文章展示的
enum Label{
     // 普通类型，即背景
    Normal_label,
    // 边界类型
    Border_label,
      // 蛇结点类型
    Snake_label,
   // 食物类型
    Food_label
};//通过枚举给四个变量分别赋值1，2，3，4，相当于四个int型的数，用来判断每个节点的类型

// 结构体蛇结点
//struct可以看作一个没有成员函数的类
struct snakeNode {
    QLabel *label;
    int type;
    int x;
    int y;
};

namespace Ui {
class Snake;
}

class Snake : public QWidget
{
    Q_OBJECT

public:
    explicit Snake(QWidget *parent = 0);
    ~Snake();
    void init();            // 初始化游戏
    void drawBorder();      // 画边界
    void drawViewArea();    // 画显示区域
    void showViewArea();    // 显示分数和等级
    void gameOver();        // 游戏结束
    void initSnake();       // 初始化蛇
    void moveSnake();       // 移动蛇
    void getHeadTail();     // 获取蛇头和蛇尾
    void createFood();  // 创建食物

    QString part;
    //void setImage();

protected:
    void keyPressEvent(QKeyEvent *e);   // 键盘事件

private slots:
    void snakeMoveSlots();      // 移动操作
    void startGameSlots();      // 游戏开始





private:
    Ui::Snake *ui;

    QTimer timer;
    QPushButton *startButton;

    snakeNode *snake_label[MAX_X][MAX_Y];// 储存游戏画面
    QList<snakeNode*> snake;     // 蛇身

    int dX,dY;      // 移动方向
    int foodCount,moveSpeed;        // 食物数和速度
    int level,score;          // 分数和等级
    snakeNode *head;               // 蛇头和蛇尾指针
    snakeNode *tail;
    QLabel *mLabel;           //等级
    QString viewText;        // 显示区域文本

};

#endif // SNAKE_H
