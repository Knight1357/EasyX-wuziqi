#include <graphics.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>

class chess {
    //棋子
public:
    int mx, my, i, j, now, board[20][20] = {0}, white[20][20] = {0}, red[20][20] = {0};
    void to_chess(int xx, int yy) {
        //鼠标左键的坐标转棋子下标
        mx = xx;
        my = yy;
        int x = mx % 50;
        int y = my % 50;
        if (x >= 25)
            mx = mx - x + 50;
        else
            mx = mx - x;
        if (y >= 25)
            my = my - y + 50;
        else
            my = my - y;
        i = mx / 50 - 1;
        j = my / 50 - 1;
    }
    bool Next() {
        if (board[i][j]) //已经有棋子不能下
            return 0;
        else {
            if (now % 2 == 0 && mx >= 50 && mx <= 750 && my >= 50 && my <= 750) {
                //红
                setfillcolor(RED);
                fillcircle(mx, my, 20);
                red[i][j] = 1;
                board[i][j] = 1;
                now++;
                if (is_win(red) == 1) {
                    settextstyle(50, 0, "宋体"); //大小 字体
                    settextcolor(RED);           //字体颜色红色
                    outtextxy(855, 600, "红子胜！");
                    return 1;
                }
            } else if (now % 2 == 1 && mx >= 50 && mx <= 750 && my >= 50 && my <= 750) {
                //白
                setfillcolor(WHITE);
                fillcircle(mx, my, 20);
                white[i][j] = 1;
                board[i][j] = 1;
                now++;
                if (is_win(white) == 1) {
                    settextstyle(50, 0, "宋体"); //大小 字体
                    settextcolor(WHITE);         //字体颜色红色
                    outtextxy(855, 600, "白子胜！");
                    return 1;
                }
            }
        }
        return 0;
    }
    bool is_win(int a[20][20]) {
        for (int i = 0; i < 15; i++)
            for (int j = 0; j < 15; j++)
                if (a[i][j] == 1 && a[i][j + 1] == 1 && a[i][j + 2] == 1 && a[i][j + 3] == 1 && a[i][j + 4] == 1) //横
                    return 1;
                else if (a[i][j] == 1 && a[i + 1][j] == 1 && a[i + 2][j] == 1 && a[i + 3][j] == 1 && a[i + 4][j] == 1) //竖
                    return 1;
                else if (a[i][j] == 1 && a[i + 1][j + 1] == 1 && a[i + 2][j + 2] == 1 && a[i + 3][j + 3] == 1 && a[i + 4][j + 4] == 1) //右下
                    return 1;
                else if (a[i][j] == 1 && a[i - 1][j + 1] == 1 && a[i - 2][j + 2] == 1 && a[i - 3][j + 3] == 1 && a[i - 4][j + 4] == 1) //左下
                    return 1;
        return 0;
    }
};

void start(); //开始游戏

void over(); //结束游戏

void game(); //游戏界面

void board(); //棋盘界面

void start() {
    initgraph(600, 800);          //窗口初始化
    setorigin(0, 0);              //设置原点
    settextstyle(100, 0, "宋体"); //大小100 宋体
    settextcolor(WHITE);          //字体颜色白色
    outtextxy(150, 150, "五子棋");
    settextstyle(50, 0, "宋体"); //大小50 宋体
    settextcolor(RED);           //字体颜色红色
    outtextxy(200, 500 - 25, "开始游戏");
    settextcolor(RED); //字体颜色红色
    outtextxy(200, 600 - 25, "结束游戏");
    setlinecolor(RED);                               //线的颜色
    roundrect(190, 490 - 25, 410, 560 - 25, 25, 25); //圆角矩形边框
    roundrect(190, 590 - 25, 410, 660 - 25, 25, 25); //圆角矩形边框
    settextstyle(16, 0, "宋体");                     //大小50 宋体
    settextcolor(WHITE);                             //字体颜色
    while (1) {
        MOUSEMSG m;        //定义一个鼠标
        m = GetMouseMsg(); //输入鼠标信息
        if (m.uMsg == WM_LBUTTONDOWN) {
            //输入左键
            if (m.x >= 190 && m.x <= 410 && m.y >= 490 - 25 && m.y <= 560 - 25) {
                outtextxy(0, 0, "开始"); //测试
                game();
            } else if (m.x >= 190 && m.x <= 410 && m.y >= 590 - 25 && m.y <= 660 - 25) {
                outtextxy(0, 0, "结束"); //测试
                over();
            }
        }
    }
}

void board() {
    initgraph(1200, 800); //窗口初始化
    setlinecolor(WHITE);
    for (int i = 50; i <= 750; i += 50)
        line(50, i, 750, i); //画线从x1 y1到x2 y2
    for (int i = 50; i <= 750; i += 50)
        line(i, 50, i, 750);             //画线从x1 y1到x2 y2
    fillcircle(200, 200, 5);             //棋盘上的点
    fillcircle(750 - 150, 200, 5);       //棋盘上的点
    fillcircle(200, 750 - 150, 5);       //棋盘上的点
    fillcircle(750 - 150, 750 - 150, 5); //棋盘上的点
    settextstyle(50, 0, "宋体");         //大小 字体
    settextcolor(RED);                   //字体颜色红色
    outtextxy(840, 100, "红方");
    setlinecolor(RED);
    roundrect(840 - 10, 100 - 10, 940 + 10, 150 + 10, 25, 25); //边框
    setfillcolor(RED);                                         //设置点的颜色
    fillcircle(1040, 125, 25);                                 //棋盘上的点
    settextstyle(50, 0, "宋体");                               //大小 字体
    settextcolor(WHITE);                                       //字体颜色红色
    outtextxy(840, 200, "白方");
    setlinecolor(WHITE);
    roundrect(840 - 10, 200 - 10, 940 + 10, 250 + 10, 25, 25); //边框
    setfillcolor(WHITE);                                       //设置点的颜色
    fillcircle(1040, 225, 25);                                 //棋盘上的点
    settextstyle(50, 0, "宋体");                               //大小 字体
    settextcolor(WHITE);                                       //字体颜色红色
    outtextxy(855, 400, "重新开始");
    roundrect(855 - 10, 400 - 10, 1050 + 15, 450 + 10, 25, 25); //边框
    settextstyle(50, 0, "宋体");                                //大小 字体
    settextcolor(WHITE);                                        //字体颜色红色
    outtextxy(855, 500, "结束游戏");
    roundrect(855 - 10, 500 - 10, 1050 + 15, 550 + 10, 25, 25); //边框
}

void win() {
    MOUSEMSG m; //定义一个鼠标
    while (1) {
        m = GetMouseMsg(); //输入鼠标信息
        if (m.uMsg == WM_LBUTTONDOWN) {
            if (m.x >= 855 - 10 && m.x <= 1050 + 15 && m.y >= 400 - 10 && m.y <= 450 + 10) {
                game();
            } else if (m.x >= 855 - 10 && m.x <= 1050 + 15 && m.y >= 500 - 10 && m.y <= 550 + 10) {
                over();
            }
        }
    }
}

void game() {
    board();
    MOUSEMSG m; //定义一个鼠标
    chess ch;   //定义一个棋子类
    while (1) {

        m = GetMouseMsg(); //输入鼠标信息
        if (m.uMsg == WM_LBUTTONDOWN) {
            if (m.x >= 855 - 10 && m.x <= 1050 + 15 && m.y >= 400 - 10 && m.y <= 450 + 10) {
                game();
            } else if (m.x >= 855 - 10 && m.x <= 1050 + 15 && m.y >= 500 - 10 && m.y <= 550 + 10) {
                over();
            }
            ch.to_chess(m.x, m.y); //输入棋子
            if (ch.Next())
                win();
        }
    }
}

void over() {
    initgraph(600, 800);          //窗口初始化
    setorigin(0, 0);              //设置原点
    settextstyle(100, 0, "宋体"); //大小100 宋体
    settextcolor(WHITE);          //字体颜色白色
    outtextxy(200, 200, "再见");
    settextstyle(16, 0, "宋体"); //大小50 宋体
    settextcolor(WHITE);         //字体颜色
    Sleep(1500);  //休眠
    closegraph(); //关闭
}

int main() {
    start();
    return 0;
}
