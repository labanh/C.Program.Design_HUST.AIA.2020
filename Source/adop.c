/*******************************************
FileName: adop.c
Author:   刘子恒 
Date：    2020/10/27
Description: 该文件主要用于管理员选择操作界面 
Others: 无
Function List: 
        admin_menu() 选择操作菜单函数 
		admindraw()  画图函数 
		admindraw2() 画图函数 
		adminbutton()按钮反馈函数 
********************************************/
#include "adop.h"
#include "common.h"

/*****************************
Function: int admin_menu(void)
Description: 选择操作菜单
Calls:     admindraw()
           admindraw2()
           adminbutton()
Called by: main()
Table Accessed: 无
Table Updated:  无
Input:  无
Output: 无 
Return: -1  -> 退出 
        0   -> 欢迎界面函数
		9   -> 用户信息管理函数 
		10	-> 审核用户通报函数 
		11	-> 管理疫情数据函数 
******************************/
int admin_menu(void)
{
    int flag = 0;
    admindraw(); //画图函数
    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);
        admin_button(&flag);                //反馈函数
        if (MousePress(400, 450, 650, 500)) //审核用户通报
            return 10;
        else if (MousePress(400, 550, 650, 600)) //管理疫情数据
            return 11;
        else if (MousePress(400, 650, 650, 700)) //用户信息管理
            return 9;
        else if (MousePress(0, 0, 150, 55)) //返回
            return 0;
        else if (MousePress(874, 0, 1024, 55)) //退出
            return -1;
    }
}
/*****************************
Function: admindraw(void)
Description: 画图函数 
Calls:     无 
Called by: admin_menu() 
Table Accessed: 无
Table Updated:  无
Input:  无
Output: 无 
Return: 无 
******************************/
void admindraw(void)
{
    Bar1(0, 0, 1024, 768, 1658);

    Bar1(5, 5, 155, 60, 0x5b4f);
    Bar1(0, 0, 150, 55, 59004);
    prt_hz24(45, 12, "返回", 0, "HZK\\Hzk24h");
    Bar1(869, 5, 1029, 60, 0x5b4f);
    Bar1(874, 0, 1024, 55, 59004);
    prt_hz24(919, 12, "退出", 0, "HZK\\Hzk24h");
    admindraw2();

    Bar1(406, 456, 656, 506, 0x7bef);
    Bar1(400, 450, 650, 500, 44925);
    Circlefill(420, 475, 10, 0xffff); //地点管理

    Bar1(406, 556, 656, 606, 0x7bef);
    Bar1(400, 550, 650, 600, 44925);
    Circlefill(420, 575, 10, 0xffff); //司机信息管理

    Bar1(406, 656, 656, 706, 0x7bef);
    Bar1(400, 650, 650, 700, 44925);
    Circlefill(420, 675, 10, 0xffff); //用户信息查询

    prt_hz24(453, 462, "审核用户通报", 0, "HZK//HzK24h");
    prt_hz24(453, 562, "管理疫情数据", 0, "HZK//HzK24h");
    prt_hz24(453, 662, "用户信息管理", 0, "HZK//HzK24h");
    Line3(426, 250, 426, 400, 3, 0);
    Line3(426, 250, 626, 250, 3, 0);
    Line3(626, 250, 626, 400, 3, 0);
    Circlefill(526, 190, 60, 0);
    Circlefill(526, 190, 55, 1658); //管理员图标
}
/*****************************
Function: admindraw2(void)
Description: 画图函数 
Calls:     无 
Called by: admin_menu() 
Table Accessed: 无
Table Updated:  无
Input:  无
Output: 无 
Return: 无 
******************************/
void admindraw2(void)
{
    prt_hz16_size(100, 100, 2, 2, "尊", 0, "HZK\\Hzk16s");
    prt_hz16_size(100, 150, 2, 2, "敬", 0, "HZK\\Hzk16s");
    prt_hz16_size(100, 200, 2, 2, "的", 0, "HZK\\Hzk16s");
    prt_hz16_size(100, 250, 2, 2, "管", 0, "HZK\\Hzk16s");
    prt_hz16_size(100, 300, 2, 2, "理", 0, "HZK\\Hzk16s");
    prt_hz16_size(100, 350, 2, 2, "员", 0, "HZK\\Hzk16s");
    prt_hz16_size(140, 100, 2, 2, "欢", 0, "HZK\\Hzk16s");
    prt_hz16_size(140, 150, 2, 2, "迎", 0, "HZK\\Hzk16s");
    prt_hz16_size(140, 200, 2, 2, "您", 0, "HZK\\Hzk16s");
    prt_hz16_size(230, 100, 3, 3, "请", 0, "HZK\\Hzk16s");
    prt_hz16_size(230, 160, 3, 3, "选", 0, "HZK\\Hzk16s");
    prt_hz16_size(230, 220, 3, 3, "择", 0, "HZK\\Hzk16s");
    prt_hz16_size(230, 280, 3, 3, "您", 0, "HZK\\Hzk16s");
    prt_hz16_size(230, 340, 3, 3, "要", 0, "HZK\\Hzk16s");
    prt_hz16_size(230, 400, 3, 3, "执", 0, "HZK\\Hzk16s");
    prt_hz16_size(230, 460, 3, 3, "行", 0, "HZK\\Hzk16s");
    prt_hz16_size(230, 520, 3, 3, "的", 0, "HZK\\Hzk16s");
    prt_hz16_size(230, 580, 3, 3, "操", 0, "HZK\\Hzk16s");
    prt_hz16_size(230, 640, 3, 3, "作", 0, "HZK\\Hzk16s");
}
/*****************************
Function: admin_button(int *flag)
Description: 按钮反馈函数 
Calls:     无 
Called by: admin_menu() 
Table Accessed: 无
Table Updated:  无
Input:  &flag 
Output: 无 
Return: 无 
******************************/
void admin_button(int *flag)
{
    if (*flag == 0 && MouseIn(0, 0, 150, 55)) //返回框反馈
    {
        MouseOff(&mouse);
        Bar1(0, 0, 150, 55, 56603);
        prt_hz24d(45, 12, "返回", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 1;
    }
    if (*flag == 0 && MouseIn(874, 0, 1024, 55))
    {
        MouseOff(&mouse);
        Bar1(874, 0, 1024, 55, 56603);
        prt_hz24d(919, 12, "退出", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 2;
    }
    if (*flag == 0 && MouseIn(400, 450, 650, 500))
    {
        MouseOff(&mouse);
        Bar1(400, 450, 650, 500, 46876);
        Circlefill(420, 475, 10, 0x429a);
        prt_hz24d(453, 462, "审核用户通报", 0, "HZK//HzK24h");
        MouseOn(mouse);
        *flag = 3;
    }
    if (*flag == 0 && MouseIn(400, 550, 650, 600))
    {
        MouseOff(&mouse);
        Bar1(400, 550, 650, 600, 46876);
        Circlefill(420, 575, 10, 0x429a);
        prt_hz24d(453, 562, "管理疫情数据", 0, "HZK//HzK24h");
        MouseOn(mouse);
        *flag = 4;
    }
    if (*flag == 0 && MouseIn(400, 650, 650, 700))
    {
        MouseOff(&mouse);
        Bar1(400, 650, 650, 700, 46876);
        Circlefill(420, 675, 10, 0x429a);
        prt_hz24d(453, 662, "用户信息管理", 0, "HZK//HzK24h");
        MouseOn(mouse);
        *flag = 5;
    }
    else if (*flag == 1 && !(MouseIn(0, 0, 150, 55)))
    {
        MouseOff(&mouse);
        Bar1(0, 0, 150, 55, 59004);
        prt_hz24d(45, 12, "返回", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*flag == 2 && !(MouseIn(874, 0, 1024, 55)))
    {
        MouseOff(&mouse);
        Bar1(874, 0, 1024, 55, 59004);
        prt_hz24d(919, 12, "退出", 0, "HZK\\Hzk24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*flag == 3 && !(MouseIn(400, 450, 650, 500)))
    {
        MouseOff(&mouse);
        Bar1(400, 450, 650, 500, 44925);
        Circlefill(420, 475, 10, 0xffff);
        prt_hz24d(453, 462, "审核用户通报", 0, "HZK//HzK24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*flag == 4 && !(MouseIn(400, 550, 650, 600)))
    {
        MouseOff(&mouse);
        Bar1(400, 550, 650, 600, 44925);
        Circlefill(420, 575, 10, 0xffff);
        prt_hz24d(453, 562, "管理疫情数据", 0, "HZK//HzK24h");
        MouseOn(mouse);
        *flag = 0;
    }
    else if (*flag == 5 && !(MouseIn(400, 650, 650, 700)))
    {
        MouseOff(&mouse);
        Bar1(400, 650, 650, 700, 44925);
        Circlefill(420, 675, 10, 0xffff);
        prt_hz24d(453, 662, "用户信息管理", 0, "HZK//HzK24h");
        MouseOn(mouse);
        *flag = 0;
    }
}
