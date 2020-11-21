/*******************************************
FileName: choice.c
Author:   韩海若
Date：    2020/10/28
Description: 该程序文件用于实现地区分类下拉菜单
             与输入时间功能
Function List: 
        choose_district //下拉控制函数
        choose_date     //输入要查询的日期
        dis_bar         //下拉菜单的选择框
********************************************/
#include "choice.h"
#include "common.h"
#include "drawc.h" //使用findday函数

/***********************************
Function: choose_district
Description: 下拉控制函数
             参数area为地区对应序号
Called by: pop_window1()
*************************************/
int choose_district(int x, int y, char *area) //(x,y)为左上角坐标
{
    int flg = 0;
    int choice = 0;     //选项标记
    int pre_flg = 0;    //下拉控制参数
    int quit_flg = 0;   //退出参数
    int choose_flg = 0; //判断是否已选择区域

    //四个区域对应的选择框
    Bar1(x - 3, y - 3, x + 73, y + 33, 0);
    Bar1(x, y, x + 70, y + 30, 0xffff);
    prt_hz24d(x + 20, y + 5, "市", 0, "HZK\\Hzk24h");

    Bar1(x + 92, y - 3, x + 188, y + 33, 0);
    Bar1(x + 95, y, x + 185, y + 30, 0xffff);
    prt_hz24d(x + 125, y + 5, "区", 0, "HZK\\Hzk24h");

    Bar1(x + 207, y - 3, x + 323, y + 33, 0);
    Bar1(x + 210, y, x + 320, y + 30, 0xffff);
    prt_hz24d(x + 240, y + 5, "社区", 0, "HZK\\Hzk24h");

    Bar1(x + 342, y - 3, x + 458, y + 33, 0);
    Bar1(x + 345, y, x + 455, y + 30, 0xffff);
    prt_hz24d(x + 375, y + 5, "小区", 0, "HZK\\Hzk24h");

    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);
        if (flg == 0 && MouseIn(350, 415, 450, 455)) //确认框反馈
        {
            MouseOff(&mouse);
            Bar2(350, 415, 450, 455, 800);
            prt_hz24d(376, 423, "确认", 0, "HZK\\Hzk24h"); //确认键
            MouseOn(mouse);
            flg = 1;
        }

        if (flg == 0 && MouseIn(550, 415, 650, 455)) //取消框反馈
        {
            MouseOff(&mouse);
            Bar2(550, 415, 650, 455, 800);
            prt_hz24d(576, 423, "取消", 0, "HZK\\Hzk24h"); //取消
            MouseOn(mouse);
            flg = 1;
        }

        else if (flg == 1 && !(MouseIn(350, 415, 450, 455)) 
                           && !(MouseIn(550, 415, 650, 455)))
        {
            MouseOff(&mouse);
            Bar1(350, 415, 450, 455, 0x8ff2);
            prt_hz24d(376, 423, "确认", 0, "HZK\\Hzk24h"); //确认键
            Bar1(550, 415, 650, 455, 0x8ff2);
            prt_hz24d(576, 423, "取消", 0, "HZK\\Hzk24h"); //取消键
            MouseOn(mouse);
            flg = 0;
        }

        else if (MousePress(350, 415, 450, 455) && choose_flg) //点击确定键
        {
            return 1;
        }

        else if (MousePress(550, 415, 650, 455)) //点击取消键
        {
            Bar1(x, y, x + 70, y + 30, 0xffff);
            prt_hz24d(x + 20, y + 5, "市", 0, "HZK\\Hzk24h");
            Bar1(x + 95, y, x + 185, y + 30, 0xffff);
            prt_hz24d(x + 125, y + 5, "区", 0, "HZK\\Hzk24h");
            Bar1(x + 210, y, x + 320, y + 30, 0xffff);
            prt_hz24d(x + 240, y + 5, "社区", 0, "HZK\\Hzk24h");
            Bar1(x + 345, y, x + 455, y + 30, 0xffff);
            prt_hz24d(x + 375, y + 5, "小区", 0, "HZK\\Hzk24h");
            
            choose_flg = 0;
            if (quit_flg)
            {
                return 0;
            }
            quit_flg = 1; //进入管理员主界面
        }

        /*********************
		下拉框选择判断语句
		***********************/

        else if (MousePress(x, y, x + 70, y + 30) && choice == 0) 
        {//点击市，出现下拉框
            MouseOff(&mouse);
            dis_bar(x, y + 30, 70, 1);
            prt_hz24d(x + 12, y + 35, "某市", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            
            pre_flg = 1;
            quit_flg = 0;
        }

        else if (MousePress(x, y + 30, x + 70, y + 60) && pre_flg == 1) 
        {//选择"某市"
            MouseOff(&mouse);
            Bar1(x, y, x + 70, y + 30, 0xffff);
            prt_hz24d(x + 12, y + 5, "某市", 0, "HZK\\Hzk24h");
            Bar1(x - 3, y + 33, x + 73, y + 63, 0x8edf);
            
            choice = 1;
            pre_flg = 0;
            choose_flg = 1;
            MouseOn(mouse);
        }

        else if (MousePress(x + 95, y, x + 185, y + 30) && choice == 1) 
        {//点击区，出现下拉框
            MouseOff(&mouse);
            dis_bar(x + 95, y + 30, 90, 2);
            prt_hz24d(x + 105, y + 35, "任城区", 0, "HZK\\Hzk24h");
            prt_hz24d(x + 105, y + 68, "高新区", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            pre_flg = 2;
        }

        else if (MousePress(x + 95, y + 30, x + 185, y + 60) && pre_flg == 2) 
        {//选择"任城区"
            MouseOff(&mouse);
            Bar1(x + 95, y, x + 185, y + 30, 0xffff);
            prt_hz24d(x + 105, y + 5, "任城区", 0, "HZK\\Hzk24h");
            Bar1(x + 92, y + 33, x + 188, y + 100, 0x8edf);
            choice = 2;
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 210, y, x + 320, y + 30) && choice == 2) 
        {//点击社区，出现下拉框
            MouseOff(&mouse);
            dis_bar(x + 210, y + 30, 110, 2);
            prt_hz24d(x + 220, y + 35, "古槐社区", 0, "HZK\\Hzk24h");
            prt_hz24d(x + 220, y + 68, "仙营社区", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            pre_flg = 3;
        }

        else if (MousePress(x + 210, y + 30, x + 320, y + 60) && pre_flg == 3) 
        {//选择"古槐社区"
            MouseOff(&mouse);
            Bar1(x + 210, y, x + 320, y + 30, 0xffff);
            prt_hz24d(x + 220, y + 5, "古槐社区", 0, "HZK\\Hzk24h");
            Bar1(x + 207, y + 33, x + 323, y + 93, 0x8edf);
            choice = 3;
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 345, y, x + 455, y + 30) && choice == 3) 
        {//点击小区，出现下拉框
            MouseOff(&mouse);
            dis_bar(x + 345, y + 30, 110, 2);
            prt_hz24d(x + 355, y + 35, "益民小区", 0, "HZK\\Hzk24h");
            prt_hz24d(x + 355, y + 68, "北门小区", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            pre_flg = 4;
        }

        else if (MousePress(x + 345, y + 30, x + 455, y + 60) && pre_flg == 4) 
        {//选择"益民小区"
            MouseOff(&mouse);
            Bar1(x + 345, y, x + 455, y + 30, 0xffff);
            prt_hz24d(x + 355, y + 5, "益民小区", 0, "HZK\\Hzk24h");
            Bar1(x + 342, y + 33, x + 458, y + 93, 0x8edf);
            choice = 4;
            *area = '0';
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 345, y + 60, x + 455, y + 90) && pre_flg == 4) 
        {//选择"北门小区"
            MouseOff(&mouse);
            Bar1(x + 345, y, x + 455, y + 30, 0xffff);
            prt_hz24d(x + 355, y + 5, "北门小区", 0, "HZK\\Hzk24h");
            Bar1(x + 342, y + 33, x + 458, y + 93, 0x8edf);
            choice = 5;
            *area = '1';
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 210, y + 60, x + 320, y + 90) && pre_flg == 3) 
        {//选择"仙营社区"
            MouseOff(&mouse);
            Bar1(x + 210, y, x + 320, y + 30, 0xffff);
            prt_hz24d(x + 220, y + 5, "仙营社区", 0, "HZK\\Hzk24h");
            Bar1(x + 207, y + 33, x + 323, y + 93, 0x8edf);
            choice = 6;
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 345, y, x + 455, y + 30) && choice == 6) 
        {//点击小区，出现下拉框
            MouseOff(&mouse);
            dis_bar(x + 345, y + 30, 110, 2);
            prt_hz24d(x + 355, y + 35, "光明小区", 0, "HZK\\Hzk24h");
            prt_hz24d(x + 355, y + 68, "桂园小区", 0, "HZK\\Hzk24h");
            MouseOn(mouse);

            pre_flg = 4;
        }

        else if (MousePress(x + 345, y + 30, x + 455, y + 60) && pre_flg == 4) 
        {//选择"光明小区"
            MouseOff(&mouse);
            Bar1(x + 345, y, x + 455, y + 30, 0xffff);
            prt_hz24d(x + 355, y + 5, "光明小区", 0, "HZK\\Hzk24h");
            Bar1(x + 342, y + 33, x + 458, y + 93, 0x8edf);
            choice = 7;
            *area = '2';
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 345, y + 60, x + 455, y + 90) && pre_flg == 4) 
        {//选择"桂园小区"
            MouseOff(&mouse);
            Bar1(x + 345, y, x + 455, y + 30, 0xffff);
            prt_hz24d(x + 355, y + 5, "桂园小区", 0, "HZK\\Hzk24h");
            Bar1(x + 342, y + 33, x + 458, y + 93, 0x8edf);
            choice = 8;
            *area = '3';
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 95, y + 60, x + 185, y + 90) && pre_flg == 2) 
        {//选择"高新区"
            MouseOff(&mouse);
            Bar1(x + 95, y, x + 185, y + 30, 0xffff);
            prt_hz24d(x + 105, y + 5, "高新区", 0, "HZK\\Hzk24h");
            Bar1(x + 92, y + 33, x + 188, y + 100, 0x8edf);
            choice = 9;
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 210, y, x + 320, y + 30) && choice == 9) 
        {//点击社区，出现下拉框
            MouseOff(&mouse);
            dis_bar(x + 210, y + 30, 110, 2);
            prt_hz24d(x + 220, y + 35, "南池社区", 0, "HZK\\Hzk24h");
            prt_hz24d(x + 220, y + 68, "北湖社区", 0, "HZK\\Hzk24h");
            pre_flg = 5;
            MouseOn(mouse);
        }

        else if (MousePress(x + 210, y + 30, x + 320, y + 60) && pre_flg == 5) 
        {//选择"南池社区"
            MouseOff(&mouse);
            Bar1(x + 210, y, x + 320, y + 30, 0xffff);
            prt_hz24d(x + 220, y + 5, "南池社区", 0, "HZK\\Hzk24h");
            Bar1(x + 207, y + 33, x + 323, y + 93, 0x8edf);
            choice = 10;
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 345, y, x + 455, y + 30) && choice == 10) 
        {//点击小区，出现下拉框
            MouseOff(&mouse);
            dis_bar(x + 345, y + 30, 110, 2);
            prt_hz24d(x + 355, y + 35, "南池小区", 0, "HZK\\Hzk24h");
            prt_hz24d(x + 355, y + 68, "丽景小区", 0, "HZK\\Hzk24h");
            pre_flg = 7;
            MouseOn(mouse);
        }

        else if (MousePress(x + 345, y + 30, x + 455, y + 60) && pre_flg == 7) 
        {//选择"南池小区"
            MouseOff(&mouse);
            Bar1(x + 345, y, x + 455, y + 30, 0xffff);
            prt_hz24d(x + 355, y + 5, "南池小区", 0, "HZK\\Hzk24h");
            Bar1(x + 342, y + 33, x + 458, y + 93, 0x8edf);
            choice = 11;
            *area = '4';
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 345, y + 60, x + 455, y + 90) && pre_flg == 7) 
        {//选择"丽景小区"
            MouseOff(&mouse);
            Bar1(x + 345, y, x + 455, y + 30, 0xffff);
            prt_hz24d(x + 355, y + 5, "丽景小区", 0, "HZK\\Hzk24h");
            Bar1(x + 342, y + 33, x + 458, y + 93, 0x8edf);
            choice = 12;
            *area = '5';
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 210, y + 60, x + 320, y + 90) && pre_flg == 5) 
        {//选择"北湖社区"
            MouseOff(&mouse);
            Bar1(x + 210, y, x + 320, y + 30, 0xffff);
            prt_hz24d(x + 220, y + 5, "北湖社区", 0, "HZK\\Hzk24h");
            Bar1(x + 207, y + 33, x + 323, y + 93, 0x8edf);
            choice = 13;
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 345, y, x + 455, y + 30) && choice == 13) 
        {//点击小区，出现下拉框
            MouseOff(&mouse);
            dis_bar(x + 345, y + 30, 110, 2);
            prt_hz24d(x + 355, y + 35, "风韵荷都", 0, "HZK\\Hzk24h");
            prt_hz24d(x + 355, y + 68, "恒大名都", 0, "HZK\\Hzk24h");
            pre_flg = 8;
            MouseOn(mouse);
        }

        else if (MousePress(x + 345, y + 30, x + 455, y + 60) && pre_flg == 8) 
        {//选择"风韵荷都"
            MouseOff(&mouse);
            Bar1(x + 345, y, x + 455, y + 30, 0xffff);
            prt_hz24d(x + 355, y + 5, "风韵荷都", 0, "HZK\\Hzk24h");
            Bar1(x + 342, y + 33, x + 458, y + 93, 0x8edf);
            choice = 14;
            *area = '6';
            pre_flg = 0;
            MouseOn(mouse);
        }

        else if (MousePress(x + 345, y + 60, x + 455, y + 90) && pre_flg == 8) 
        {//选择"恒大名都"
            MouseOff(&mouse);
            Bar1(x + 345, y, x + 455, y + 30, 0xffff);
            prt_hz24d(x + 355, y + 5, "恒大名都", 0, "HZK\\Hzk24h");
            Bar1(x + 342, y + 33, x + 458, y + 93, 0x8edf);
            choice = 15;
            *area = '7';
            pre_flg = 0;
            MouseOn(mouse);
        }
    }
}

/***********************************
Function: choose_district
Description: 输入要查询的日期
Calls:  findday   //找到某日
Called by: pop_window1()
*************************************/
int choose_date(int x, int y, int *key) //key为输入时间对应日期信息在文件中相应的位置
{

    char year[4 + 1] = "\0";
    char month[2 + 1] = "\0";
    char day[2 + 1] = "\0";

    int quit_flg = 0;
    int flg = 0;
    int choose_flg = 0;

    Bar1(x - 3, y - 3, x + 83, y + 33, 0);
    Bar1(x, y, x + 80, y + 30, 0xffff);
    prt_hz24d(x + 25, y + 5, "年", 0, "HZK\\Hzk24h");
    Bar1(x + 107, y - 3, x + 183, y + 33, 0);
    Bar1(x + 110, y, x + 180, y + 30, 0xffff);
    prt_hz24d(x + 130, y + 5, "月", 0, "HZK\\Hzk24h");
    Bar1(x + 207, y - 3, x + 293, y + 33, 0);
    Bar1(x + 210, y, x + 290, y + 30, 0xffff);
    prt_hz24d(x + 235, y + 5, "日", 0, "HZK\\Hzk24h");

    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);
        if (flg == 0 && MouseIn(350, 415, 450, 455)) 
        {//确认框反馈
            MouseOff(&mouse);
            Bar2(350, 415, 450, 455, 800);
            prt_hz24d(376, 423, "确认", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }

        if (flg == 0 && MouseIn(550, 415, 650, 455))
        { //取消框反馈
            MouseOff(&mouse);
            Bar2(550, 415, 650, 455, 800);
            prt_hz24d(576, 423, "取消", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }

        else if (flg == 1 && !(MouseIn(350, 415, 450, 455)) 
                           && !(MouseIn(550, 415, 650, 455)))
        {
            MouseOff(&mouse);
            Bar1(350, 415, 450, 455, 0x8ff2);
            prt_hz24d(376, 423, "确认", 0, "HZK\\Hzk24h");
            Bar1(550, 415, 650, 455, 0x8ff2);
            prt_hz24d(576, 423, "取消", 0, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 0;
        }

        else if (MousePress(350, 415, 450, 455) && choose_flg)
        {//点击确定键
            return 1;
        }

        else if (MousePress(550, 415, 650, 455))
        {//点击取消键
            Bar1(x - 3, y - 3, x + 83, y + 33, 0);
            Bar1(x, y, x + 80, y + 30, 0xffff);
            prt_hz24d(x + 25, y + 5, "年", 0, "HZK\\Hzk24h");
            Bar1(x + 107, y - 3, x + 183, y + 33, 0);
            Bar1(x + 110, y, x + 180, y + 30, 0xffff);
            prt_hz24d(x + 130, y + 5, "月", 0, "HZK\\Hzk24h");
            Bar1(x + 207, y - 3, x + 293, y + 33, 0);
            Bar1(x + 210, y, x + 290, y + 30, 0xffff);
            prt_hz24d(x + 235, y + 5, "日", 0, "HZK\\Hzk24h");

            if (quit_flg)
            { 
                return 0;
            }
            quit_flg = 1;
        }

        if (MousePress(x, y, x + 80, y + 30)) //点击*年*
        {
            MouseOff(&mouse);
            Bar1(x, y, x + 80, y + 30, 0xffff);
            Getinfo(x + 10, y + 5, year, 4); //得到数据
            MouseOn(mouse);
        }
        else if (MousePress(x + 110, y, x + 180, y + 30)) //点击*月*
        {
            MouseOff(&mouse);
            Bar1(x + 110, y, x + 180, y + 30, 0xffff);
            Getinfo(x + 120, y + 5, month, 2); //得到数据
            MouseOn(mouse);
        }
        else if (MousePress(x + 210, y, x + 290, y + 30)) //点击*日*
        {
            MouseOff(&mouse);
            Bar1(x + 210, y, x + 290, y + 30, 0xffff);
            Getinfo(x + 220, y + 5, day, 2); //得到数据
            MouseOn(mouse);
            if (*key = findday(atoi(year), atoi(month), atoi(day)))
            {
                choose_flg = 1;
            }
            else
            {
				prt_hz24d(x+100,y+80,"找不到日期",0,"HZK\\Hzk24h");
				delay(1000);
				Bar1(x+98, y+78, x+350, y+120, 0x8edf);
			}
        }
    }
}

/***********************************
Function: dis_bar
Description: 绘制下拉方框
Called by: choose_district()
*************************************/
void dis_bar(int x, int y, int wid, int n)
{
    int i;
    Bar1(x - 3, y, x + wid + 3, y + 30 * n + 3, 0);
    for (i = 0; i < n; i++)
    {
        Bar1(x, y + i * 30 + 3, x + wid, y + i * 30 + 30, 0xffff);
    }
}
