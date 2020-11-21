/************************************************
FileName: showinfo.h
Author:   韩海若
Date：    2020/10/28
Description: 该程序文件用于实现疫情数据排行图
Others: 无
Function List: 
        int showinfo_main(void); //参数初始化, 调用其他函数绘图
        void drawbar(int key); //绘制选择键
        void bubble_Sort(int arr[], int eq_loc[], int len); //冒泡排序
        void swap(int *a, int *b); //交换两数
*************************************************/
#include "common.h"
#include "dayinfo.h"
#include "draw.h"
#include "showinfo.h"
/***************************************************
Function: int showinfo_main(void)
Description: 参数初始化, 调用其他函数绘图
Calls:     void drawbar(int key); //绘制选择键
           void bubble_Sort(int arr[], int eq_loc[], int len); //冒泡排序
           void swap(int *a, int *b); //交换两数
           countareacases(i, &tmp1, &tmp2, &tmp3, &tmp4) //读取总数据
           
Called by: main()
Table Accessed: i.DAT(不同地区对应的数据文件)
Table Updated:  无
Input:  无
Output: 无 
Return: 5   -> 可视化界面
       -1   -> 退出
****************************************************/
int showinfo_main(void)
{
    //参数初始化
    int flg = 0, key = 0;
    int data[15] = {0};
    int tmp1, tmp2, tmp3, tmp4 = 10;
    int i, k;
    
    //初始化地名数组与匹配数组
    int eq_loc[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    char loc[15][20] = {"\0"};
    char loc_name[15][20] = 
    {"某市", "高新区", "任城区", "北湖社区", "南池社区", 
    "仙营社区", "古槐社区", "恒大名都", "风韵荷都", "丽景小区", 
    "南池小区", "桂园小区", "光明小区", "北门小区", "益民小区"};

    //绘制选择键
    drawbar(key);
    
    //标题
    prt_hz16_size(315, 60, 4, 4, "确诊病例排行", 0xffe0, "HZK\\Hzk16s");

    //读入确诊数据
    for (i = 14; i >= 0; i--)
    {
        countareacases(i, &tmp1, &tmp2, &tmp3, &tmp4);
        data[14 - i] = tmp1;
    }

    //对确诊数据进行冒泡排序
    bubble_Sort(data, eq_loc, 15);

    //地名匹配
    for (i = 0, k = 0; i < 15; i++)
    {
        stpcpy(loc[i], loc_name[eq_loc[k++]]);
    }

    //输出地名与条形图
    for (i = 0; i < 15; i++)
    {
        prt_hz24(75, 240 + 32 * i, loc[i], 0x0000, "HZK\\Hzk24k");
        draw_column(185, 240 + 32 * i, data[i]);
    }

    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);
        
        //每次循环为 eq_loc 重新正序赋值
        for (i = 0; i < 15; i++)
        {
            eq_loc[i] = i;
        }

        if (MousePress(895, 0, 1019, 50)) //点击退出
        {
            return -1;
        }
        if (MousePress(0, 0, 124, 50)) //点击返回
        {
            return 5; //返回可视化界面
        }
        if (MousePress(255, 160, 355, 200) && key != 0) //点击总确诊
        {
            for (i = 14; i >= 0; i--)
            {
                countareacases(i, &tmp1, &tmp2, &tmp3, &tmp4);
                data[14 - i] = tmp1;
            }
            key = 0;
            drawbar(key);
            prt_hz16_size(315, 60, 4, 4, "确诊病例排行", 0xffe0, "HZK\\Hzk16s");

            //对确诊数据进行冒泡排序
            bubble_Sort(data, eq_loc, 15);

            //地名匹配
            for (i = 0, k = 0; i < 15; i++)
            {
                stpcpy(loc[i], loc_name[eq_loc[k++]]);
            }
               
            //绘制条形图
            for (i = 0; i < 15; i++)
            {
                prt_hz24(70, 240 + 32 * i, loc[i], 0x0000, "HZK\\Hzk24k");
                draw_column(180, 240 + 32 * i, data[i]);
            }
        }
        if (MousePress(255 + 200, 160, 355 + 200, 200) && key != 1) //点击总治愈
        {
            for (i = 14; i >= 0; i--)
            {
                countareacases(i, &tmp1, &tmp2, &tmp3, &tmp4);
                data[14 - i] = tmp3;
            }
            key = 1;
            drawbar(key);
            prt_hz16_size(315, 60, 4, 4, "治愈病例排行", 0xffe0, "HZK\\Hzk16s");
            
            //对治愈数据进行冒泡排序
            bubble_Sort(data, eq_loc, 15);

            //地名匹配
            for (i = 0, k = 0; i < 15; i++)
            {
                stpcpy(loc[i], loc_name[eq_loc[k++]]);
            }
                
            //绘制条形图
            for (i = 0; i < 15; i++)
            {
                prt_hz24(70, 240 + 32 * i, loc[i], 0x0000, "HZK\\Hzk24k");
                draw_column(180, 240 + 32 * i, data[i]);
            }
        }
        if (MousePress(255 + 200 + 200, 160, 355 + 200 + 200, 200) && key != 2) //点击总死亡
        {
            for (i = 14; i >= 0; i--)
            {
                countareacases(i, &tmp1, &tmp2, &tmp3, &tmp4);
                data[14 - i] = tmp2;
            }
            key = 2;
            drawbar(key);
            prt_hz16_size(315, 60, 4, 4, "死亡病例排行", 0xffe0, "HZK\\Hzk16s");
            bubble_Sort(data, eq_loc, 15);

            //地名匹配
            for (i = 0, k = 0; i < 15; i++)
            {
                stpcpy(loc[i], loc_name[eq_loc[k++]]);
            }

            for (i = 0; i < 15; i++)
            {
                prt_hz24(70, 240 + 32 * i, loc[i], 0x0000, "HZK\\Hzk24k");
                draw_column(180, 240 + 32 * i, data[i] * 10);
            }
        }

        if (flg == 0 && MouseIn(895, 0, 1019, 50)) //退出框反馈
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 56603);
            prt_hz24d(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }
        if (flg == 0 && MouseIn(0, 0, 124, 50)) //返回框反馈
        {
            MouseOff(&mouse);
            Bar1(0, 0, 124, 50, 56603);
            prt_hz24d(38, 13, "返回", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flg = 1;
        }

        else if (flg == 1 && !(MouseIn(0, 0, 124, 50)) && !(MouseIn(900, 0, 1024, 50)))
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 59004); //退出框实体
            prt_hz24(935, 12, "退出", 0x0000, "HZK\\Hzk24h");

            Bar1(0, 0, 124, 50, 59004);
            prt_hz24(38, 13, "返回", 0x0000, "HZK\\Hzk24h");

            MouseOn(mouse);
            flg = 0;
        }
    }
}

/***************************************************
Function: void drawbar(int key)
Description: 绘制选择键         
Called by: showinfo_main(void)
Input:  int key 选择类型参数
        0 -> 总确诊
        1 -> 总治愈
        2 -> 总死亡
****************************************************/
void drawbar(int key)
{
    Bar1(0, 0, 1024, 768, 0x9efc);

    //绘制退出框
    Bar1(900, 5, 1024, 55, 0x7bef); //退出框阴影
    Bar1(895, 0, 1019, 50, 59004);  //退出框实体
    prt_hz24(935, 12, "退出", 0x0000, "HZK\\Hzk24h");

    //返回键
    Bar1(5, 5, 127, 53, 0x7bef); //0x7bef灰色
    Bar1(0, 0, 124, 50, 59004);
    prt_hz24(38, 13, "返回", 0x0000, "HZK\\Hzk24h");

    Bar1(258, 163, 358, 203, 0x7bef);
    Bar1(255, 160, 355, 200, 0xffff);
    prt_hz24(270, 168, "总确诊", 0x0000, "HZK\\Hzk24h");

    Bar1(255 + 203, 163, 355 + 203, 203, 0x7bef);
    Bar1(255 + 200, 160, 355 + 200, 200, 0xffff);
    prt_hz24(270 + 200, 168, "总治愈", 0x0000, "HZK\\Hzk24h");

    Bar1(255 + 200 + 203, 163, 355 + 200 + 203, 203, 0x7bef);
    Bar1(255 + 200 + 200, 160, 355 + 200 + 200, 200, 0xffff);
    prt_hz24(270 + 200 + 200, 168, "总死亡", 0x0000, "HZK\\Hzk24h");

    if (key == 0)
    {
        Bar2(255, 160, 355, 200, 56612);
    }
    if (key == 1)
    {
        Bar2(255 + 200, 160, 355 + 200, 200, 56612);
    }
    if (key == 2)
    {
        Bar2(255 + 200 + 200, 160, 355 + 200 + 200, 200, 56612);
    }
}

//交换两数
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//冒泡排序
void bubble_Sort(int arr[], int eq_loc[], int len)
{
    int i, j;
    for (i = 1; i < len; i++)
        for (j = 1; j < len - i; j++)
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                swap(&eq_loc[j], &eq_loc[j + 1]);
            }
    return;
}
