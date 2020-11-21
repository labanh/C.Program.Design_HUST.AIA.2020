/*******************************************
FileName: report.c
Author:   刘子恒 
Date：    2020/10/27
Description: 该文件主要用于用户通报数据功能 
Others: 无
Function List: 
        report()  用户通报函数
********************************************/
#include "common.h"
#include "dayinfo.h"
#include "gettime.h"
#include "report.h"

/*****************************
Function: int report(void)
Description: 用户通报页面 
Calls:     re_area()
           gett()
           wr_day_inf()
Called by: main()
Table Accessed: area.DAT
Table Updated:  area.DAT(area:0-7) 
Input:  无
Output: 无 
Return: -1   -> 退出 
        5   -> 数据可视化界面 
******************************/
int report(void)
{
    //初始化
    int flag = 0, areakey;
    char area[6];
    char Ye[4 + 1] = {'\0'};
    char Mo[3] = {'\0'};
    char Da[3] = {'\0'};
    char In[6] = {'\0'};
    char De[6] = {'\0'};
    char He[6] = {'\0'};
    char filename[6];
    int key1 = 0, key2 = 0;
    int year, month, day;
    char User[13];

    re_area(&areakey);
    gett(&year, &month, &day);
    itoa(year, Ye, 10);
    itoa(month, Mo, 10);
    itoa(day, Da, 10);
    Bar1(0, 0, 1024, 768, 0x9efc);

    //绘制退出框
    Bar1(900, 5, 1024, 55, 0x7bef); //退出框阴影
    Bar1(895, 0, 1019, 50, 59004);  //退出框实体
    prt_hz24(935, 12, "退出", 0x0000, "HZK\\Hzk24h");

    //返回键
    Bar1(5, 5, 127, 53, 0x7bef); //0x7bef灰色
    Bar1(0, 0, 124, 50, 59004);
    prt_hz24(38, 13, "返回", 0x0000, "HZK\\Hzk24h");

    //标题
    prt_hz16_size(285, 80, 5, 5, "新型冠状病毒", 0xffe0, "HZK\\Hzk16s");
    prt_hz16_size(285, 180, 5, 5, "疫情信息通报", 0xffe0, "HZK\\Hzk16s");

    Bar1(374, 403 - 64, 661, 431 - 64, 0);
    Bar1(376, 405 - 64, 659, 429 - 64, 0xffff); //年

    Bar1(374, 403, 661, 431, 0);
    Bar1(376, 405, 659, 429, 0xffff); //月

    Bar1(374, 467, 661, 495, 0);
    Bar1(376, 469, 659, 493, 0xffff); //日

    Bar1(374, 531, 661, 559, 0);
    Bar1(376, 533, 659, 557, 0xffff); //新增感染

    Bar1(374, 531 + 64, 661, 559 + 64, 0);
    Bar1(376, 533 + 64, 659, 557 + 64, 0xffff); //新增死亡

    Bar1(374, 531 + 64 + 64, 661, 559 + 64 + 64, 0);
    Bar1(376, 533 + 64 + 64, 659, 557 + 64 + 64, 0xffff); //新增治愈

    Bar1(361, 614 + 100, 429, 648 + 100, 0x7bef);
    Bar1(356, 609 + 100, 424, 643 + 100, 0xffff); //确认

    Bar1(561, 614 + 100, 629, 648 + 100, 0x7bef);
    Bar1(556, 609 + 100, 624, 643 + 100, 0xffff); //取消框

    prt_hz24(307, 405 - 64, "年：", 0, "HZK\\Hzk24h");
    prt_hz24(307, 405, "月：", 0, "HZK\\Hzk24h");
    prt_hz24(307, 469, "日：", 0, "HZK\\Hzk24h");
    prt_hz24(259, 533, "新增感染", 0, "HZK\\Hzk24h");
    prt_hz24(259, 533 + 64, "新增死亡", 0, "HZK\\Hzk24h");
    prt_hz24(259, 533 + 64 + 64, "新增治愈", 0, "HZK\\Hzk24h");
    prt_hz24(366, 614 + 100, "确认", 0, "HZK\\Hzk24h");
    prt_hz24(566, 614 + 100, "取消", 0, "HZK\\Hzk24h");

    if (areakey == 0)
    {
        prt_hz24(790, 90, "已选中益民小区", 0x0000, "HZK\\Hzk24k");
        strcpy(filename, "0.DAT");
    }
    if (areakey == 1)
    {
        prt_hz24(790, 90, "已选中北门小区", 0x0000, "HZK\\Hzk24k");
        strcpy(filename, "1.DAT");
    }
    if (areakey == 2)
    {
        prt_hz24(790, 90, "已选中光明小区", 0x0000, "HZK\\Hzk24k");
        strcpy(filename, "2.DAT");
    }
    if (areakey == 3)
    {
        prt_hz24(790, 90, "已选中桂园小区", 0x0000, "HZK\\Hzk24k");
        strcpy(filename, "3.DAT");
    }
    if (areakey == 4)
    {
        prt_hz24(790, 90, "已选中南池小区", 0x0000, "HZK\\Hzk24k");
        strcpy(filename, "4.DAT");
    }
    if (areakey == 5)
    {
        prt_hz24(790, 90, "已选中丽景小区", 0x0000, "HZK\\Hzk24k");
        strcpy(filename, "5.DAT");
    }
    if (areakey == 6)
    {
        prt_hz24(790, 90, "已选中风韵荷都", 0x0000, "HZK\\Hzk24k");
        strcpy(filename, "6.DAT");
    }
    if (areakey == 7)
    {
        prt_hz24(790, 90, "已选中恒大名都", 0x0000, "HZK\\Hzk24k");
        strcpy(filename, "7.DAT");
    }

    re_user(User);

    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);

        if (flag == 0 && MouseIn(895, 0, 1019, 50)) //退出框反馈
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 56603);
            prt_hz24d(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }
        if (flag == 0 && MouseIn(0, 0, 124, 50)) //返回框反馈
        {
            MouseOff(&mouse);
            Bar1(0, 0, 124, 50, 56603);
            prt_hz24d(38, 13, "返回", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }

        else if (flag == 1 && !(MouseIn(895, 0, 1019, 50)) && !(MouseIn(0, 0, 124, 50)))
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 59004);
            Bar1(0, 0, 124, 50, 59004);
            prt_hz24d(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
            prt_hz24d(38, 13, "返回", 0x0000, "HZK\\Hzk24h");

            MouseOn(mouse);
            flag = 0;
        }
        else if (MousePress(376, 405 - 64, 659, 429 - 64)) //输入*年*
        {
            MouseOff(&mouse);
            Bar1(376, 405 - 64, 659, 429 - 64, 0xffff);
            Getinfo(380, 406 - 64, Ye, 4); //gets.h
            MouseOn(mouse);
        }
        else if (MousePress(378, 405, 659, 429)) //输入*月*
        {
            MouseOff(&mouse);
            Bar1(378, 405, 659, 429, 0xffff);
            Getinfo(380, 406, Mo, 2); //gets.h
            MouseOn(mouse);
        }
        else if (MousePress(378, 469, 659, 493)) //输入*日*
        {
            MouseOff(&mouse);
            Bar1(378, 469, 659, 493, 0xffff);
            Getinfo(380, 470, Da, 2);
            MouseOn(mouse);
        }
        else if (MousePress(376, 533, 659, 557)) //输入*新增感染*
        {
            MouseOff(&mouse);
            Bar1(376, 533, 659, 557, 0xffff);
            Getinfo(380, 534, In, 5);
            MouseOn(mouse);
        }
        else if (MousePress(378, 533 + 64, 659, 557 + 64)) //输入*新增死亡*
        {
            MouseOff(&mouse);
            Bar1(378, 533 + 64, 659, 557 + 64, 0xffff);
            Getinfo(380, 534 + 64, De, 5);
            MouseOn(mouse);
        }
        else if (MousePress(378, 533 + 64 + 64, 659, 557 + 64 + 64)) //输入*新增治愈*
        {
            MouseOff(&mouse);
            Bar1(378, 533 + 64 + 64, 659, 557 + 64 + 64, 0xffff);
            Getinfo(380, 534 + 64 + 64, He, 5);
            MouseOn(mouse);
        }
        if (MousePress(356, 609 + 100, 424, 643 + 100))
        {
            key1 = judge_date(Ye, Mo, Da);
            key2 = judge_cases(In, De, He);

            re_area(area);
            if (key1 == 0 && key2 == 0)
            {
                wr_day_inf(filename, Ye, Mo, Da, In, De, He, User);
                prt_hz24d(700, 554, "通报成功", 0, "HZK\\Hzk24h");
                delay(1000);
                return 5;
            }
            else
            {
                prt_hz24d(700, 554, "数据有误", 0, "HZK\\Hzk24h");
                delay(2000);
                Bar1(698, 550, 800, 600, 0x9efc);
            }
        }

        if (MousePress(895, 0, 1019, 50)) //点击退出
        {
            return -1;
        }
        else if (MousePress(0, 0, 124, 50)) //点击返回
        {
            return 5;
        }
    }
}