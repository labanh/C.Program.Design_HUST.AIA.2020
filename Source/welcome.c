/**********************************************
FileName: welcome.c
Author:   韩海若
Date:     2020/10/28
Description: 绘制欢迎界面
Function list: 
        int welcome() //欢迎界面的图形绘制
***********************************************/
#include "common.h"
#include "welcome.h"
/**********************
Function: int welcome()
Description: 欢迎界面的图形绘制
Calls:  无
Called by: main()
Input:  无
Output: 无 
Return: 1   -> 用户登录
        2   -> 管理员登录
       -1   -> 退出
**********************/
int welcome(void)
{
    int flg = 0;

    Bar1(0, 0, 1024, 768, 0x9eef); //0x9eef

    /*画出按钮阴影*/
    Bar1(403, 450, 590, 525, 0x7bef); //用户键
    Bar1(403, 560, 590, 635, 0x7bef); //管理员键

    /*画出按钮*/
    Bar1(400, 445, 585, 520, 0xde5d); //用户键
    Bar1(400, 555, 585, 630, 0xde5d); //管理员键

    Circlefill(420, 482, 10, 0xffff); //用户登录圆形标志
    Circlefill(420, 592, 10, 0xffff); //管理员登录圆形标志
    Bar2(400, 445, 585, 520, 0xffff); //用户登录键
    Bar2(400, 555, 585, 630, 0xffff); //管理员键

    /*画相关信息*/
    prt_hz16_size(285, 150, 5, 5, "新型冠状病毒", 0xffe0, "HZK\\Hzk16s");
    prt_hz16_size(285, 250, 5, 5, "疫情通报系统", 0xffe0, "HZK\\Hzk16s"); //0xffe0 亮黄色
    prt_hz24(455, 472, "用户登录", 0x0000, "HZK\\Hzk24s");
    prt_hz24(455, 582, "管理员", 0x0000, "HZK\\Hzk24s");

    /*绘制退出键*/
    Bar1(900, 5, 1024, 55, 0x7bef); //退出键阴影
    Bar1(895, 0, 1019, 50, 59004);  //退出键实体
    prt_hz24(935, 12, "退出", 0x0000, "HZK\\Hzk24h");

    /*交互设计*/
    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);
        if (MousePress(400, 445, 585, 520)) //点击用户键
        {
            return 1; //进入用户登录界面
        }
        if (MousePress(400, 555, 585, 630)) //点击管理员
        {
            return 2; //进入管理员界面
        }
        if (MousePress(895, 0, 1019, 50)) //点击退出
        {
            return -1;
        }
        if (flg == 0 && MouseIn(895, 0, 1019, 50)) //退出键反馈
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 56603);
            prt_hz24d(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }
        if (flg == 0 && MouseIn(400, 445, 585, 520)) //用户键反馈
        {
            MouseOff(&mouse);
            Bar2(400, 445, 585, 520, 0x429a);
            Circlefill(420, 482, 10, 0x429a);
            MouseOn(mouse);
            flg = 1;
        }
        if (flg == 0 && MouseIn(400, 555, 585, 630)) //管理员反馈
        {
            MouseOff(&mouse);
            Circlefill(420, 592, 10, 0x429a);
            Bar2(400, 555, 585, 630, 0x429a);
            MouseOn(mouse);
            flg = 1;
        }
        else if (flg == 1 && !(MouseIn(400, 445, 585, 520)) && !(MouseIn(400, 555, 585, 630)) && !(MouseIn(900, 0, 1024, 50)))
        {
            MouseOff(&mouse);
            Circlefill(420, 482, 10, 0xffff); //用户登录圆形标志
            Circlefill(420, 592, 10, 0xffff); //管理员登录圆形标志
            Bar2(400, 445, 585, 520, 0xffff); //用户登录键
            Bar2(400, 555, 585, 630, 0xffff); //管理员键
            Bar1(895, 0, 1019, 50, 59004);
            prt_hz24d(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 0;
        }
    }
}