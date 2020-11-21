/*******************************************
FileName: inquiry.c
Author:   刘子恒 
Date：    2020/10/24
Description: 该文件主要用于用户通报数据功能 
Others: 无
Function List: 
        inquiry  用户查询主函数  
        drawarea 输出区域信息  
********************************************/
#include "choice.h"
#include "common.h"
#include "dayinfo.h"
#include "drawc.h"
#include "gettime.h"
#include "inquiry.h"
// 用户查询主函数
int inquiry(void)
{
    //初始化
    int flag = 0, areakey, datekey, judge;
    char area[6];
    char alinf[6] = {'\0'};
    char aldea[6] = {'\0'};
    char alhea[6] = {'\0'};
    char alnow[6] = {'\0'};
    //char filename[5+1]={'\0'};
    char cyear[5] = {'\0'};
    char cmonth[3] = {'\0'};
    char cday[3] = {'\0'};
    CHARTDATA data[135];
    SAVEDAY *dd = NULL;
    int alsuminf, alsumdea, alsumheal, alnowinf;
    int suminf, sumdea, sumheal, nowinf;
    int year, month, day, count = 0, today;
    re_area(&areakey);
    countareacases(14, &alsuminf, &alsumdea, &alsumheal, &alnowinf);
    itoa(alsuminf, alinf, 10);
    itoa(alsumdea, aldea, 10);
    itoa(alsumheal, alhea, 10);
    itoa(alnowinf, alnow, 10);
    Bar1(0, 0, 1024, 768, 0x9efc);

    if ((dd = (SAVEDAY *)malloc(sizeof(SAVEDAY))) == NULL)
    {
        printf("memory error CountCase");
        delay(3000);
        exit(1); //分配空间不足，退出程序
    }

    gett(&year, &month, &day);         //得到今天时间
    today = findday(year, month, day); //找到对应日期再数据库中的位置

    Bar1(248, 168, 752, 482, 0);
    Bar1(250, 170, 750, 480, 0x8edf); //弹窗底色

    prt_hz24d(380, 200, "请选择您要查询的日期", 0, "HZK\\Hzk24h");

    Bar1(348, 413, 452, 457, 0x4b32);
    Bar1(350, 415, 450, 455, 0x8ff2);
    prt_hz24d(376, 423, "确认", 0, "HZK\\Hzk24h"); //确认键
    Bar1(548, 413, 652, 457, 0x4b32);
    Bar1(550, 415, 650, 455, 0x8ff2);
    prt_hz24d(576, 423, "取消", 0, "HZK\\Hzk24h"); //取消键

    judge = choose_date(345, 255, &datekey);
    if (judge == 0)
    {
        return 5;
    }
    if (datekey > today) //判断日期是否合法
    {
        Bar1(0, 0, 1024, 768, 0x9efc);
        prt_hz16_size(420, 300, 2, 2, "输入数据有误", 0, "HZK\\Hzk16s");
        delay(2000);
        return 5;
    }
    getoneday(dd, areakey, datekey); //读取相应日期信息

    Bar1(0, 0, 1024, 768, 0x9efc);

	Bar1(600-1, 720-1, 650+1, 750+1, 0x0000);
    Bar1(500-1, 720-1, 550+1, 750+1, 0x0000);
    Bar1(600, 720, 650, 750, 0xffff);
    Bar1(500, 720, 550, 750, 0xffff);
    
    //绘制退出框
    Bar1(900, 5, 1024, 55, 0x7bef); //退出框阴影
    Bar1(895, 0, 1019, 50, 0xccff); //退出框实体
    prt_hz24(935, 12, "退出", 0xfc00, "HZK\\Hzk24h");

    //返回键
    Bar1(5, 5, 127, 53, 0x7bef); //0x7bef灰色
    Bar1(0, 0, 124, 50, 0xccff);
    prt_hz24(38, 13, "返回", 0x0000, "HZK\\Hzk24h");

    //标题
    prt_hz16_size(300, 20, 5, 5, "疫情信息查询", 0xffe0, "HZK\\Hzk16s"); //0xffe0 亮黄色
    
    prt_hz24(500, 720, "向前", 0x0000, "HZK\\Hzk24k");
    prt_hz24(600, 720, "向后", 0x0000, "HZK\\Hzk24k");

    put_asc16_size(185, 200 + 50, 2, 2, alinf, 0x0000);
    prt_hz24(100, 200 + 50, "总确诊", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(185 + 150, 200 + 50, 2, 2, aldea, 0x0000);
    prt_hz24(100 + 150, 200 + 50, "总死亡", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(185 + 150 + 150, 200 + 50, 2, 2, alhea, 0x0000);
    prt_hz24(100 + 150 + 150, 200 + 50, "总治愈", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(185 + 150 + 150 + 150 + 20, 200 + 50, 2, 2, alnow, 0x0000);
    prt_hz24(100 + 150 + 150 + 150, 200 + 50, "现存", 0x0000, "HZK\\Hzk24k");

    drawarea(areakey); //输出相应地区信息

    countareacases(areakey, &suminf, &sumdea, &sumheal, &nowinf); //计算对应区域信息

    gett(&year, &month, &day);

    put_asc16_size(285 + 80, 600, 2, 2, cyear, 0x0000);
    put_asc16_size(485 + 80, 600, 2, 2, cmonth, 0x0000);
    put_asc16_size(685 + 80, 600, 2, 2, cday, 0x0000);

    itoa(suminf, alinf, 10);
    itoa(sumdea, aldea, 10);
    itoa(sumheal, alhea, 10);
    itoa(nowinf, alnow, 10);
    put_asc16_size(185 + 80, 200, 2, 2, alinf, 0x0000);
    prt_hz24(100, 200, "选区总确诊", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(185 + 150 + 80 + 80, 200, 2, 2, aldea, 0x0000);
    prt_hz24(100 + 150 + 80, 200, "选区总死亡", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(185 + 150 + 150 + 80 + 80 + 80, 200, 2, 2, alhea, 0x0000);
    prt_hz24(100 + 150 + 150 + 80 + 80, 200, "选区总治愈", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(185 + 150 + 150 + 150 + 80 + 80 + 80 + 80, 200, 2, 2, alnow, 0x0000);
    prt_hz24(100 + 150 + 150 + 150 + 80 + 80 + 80, 200,
							 "选区现存确诊", 0x0000, "HZK\\Hzk24k");

    put_asc16_size(120-60, 100, 2, 2, dd->year, 0x0000);
    prt_hz24(140, 100, "年", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(165, 100, 2, 2, dd->month, 0x0000);
    prt_hz24(140+ 60, 100, "月", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(165 + 60, 100, 2, 2, dd->day, 0x0000);
    prt_hz24(140+ 2 * 60, 100, "日", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(165 + 60 , 160, 2, 2, dd->infestor, 0x0000);
    prt_hz24(100, 160, "当日确诊", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(165 + 60 * 3, 160, 2, 2, dd->heal, 0x0000);
    prt_hz24(100 + 140, 160, "当日治愈", 0x0000, "HZK\\Hzk24k");
    put_asc16_size(180 + 60 * 5, 160, 2, 2, dd->death, 0x0000);
    prt_hz24(100 + 140 * 2, 160, "当日死亡", 0x0000, "HZK\\Hzk24k");
//    put_asc16_size(165 + 60 * 6, 160, 2, 2, dd->allinf, 0x0000);
//    prt_hz24(100 + 140 * 3, 160 , "当日总确诊", 0x0000, "HZK\\Hzk24k");
//    put_asc16_size(165 + 60 * 7, 160, 2, 2, dd->allhea, 0x0000);
//    prt_hz24(100 + 140 * 4, 160, "当日总治愈", 0x0000, "HZK\\Hzk24k");
//    put_asc16_size(165 + 60 * 8, 160, 2, 2, dd->alldea, 0x0000);
//	prt_hz24(100 + 140 * 5, 160, "当日总死亡", 0x0000, "HZK\\Hzk24k");
//	
    drawchart(data, areakey, count); //画折线图

    Mouse_Init();
    while (1)
    {
        MouseShow(&mouse);

        if (flag == 0 && MouseIn(895, 0, 1019, 50)) //退出框反馈
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 0x9ea0);
            prt_hz24d(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }
        if (flag == 0 && MouseIn(0, 0, 124, 50)) //返回框反馈
        {
            MouseOff(&mouse);
            Bar1(0, 0, 124, 50, 0x9ea0);
            prt_hz24d(38, 13, "返回", 0x0000, "HZK\\Hzk24h");
            MouseOn(mouse);
            flag = 1;
        }

        else if (flag == 1 && !(MouseIn(895, 0, 1019, 50)) && !(MouseIn(0, 0, 124, 50)))
        {
            MouseOff(&mouse);
            Bar1(895, 0, 1019, 50, 0xccff);
            Bar1(0, 0, 124, 50, 0xccff);

            prt_hz24d(935, 12, "退出", 0x0000, "HZK\\Hzk24h");
            prt_hz24d(38, 13, "返回", 0x0000, "HZK\\Hzk24h");

            MouseOn(mouse);
            flag = 0;
        }
        if (MousePress(600, 720, 650, 750) && count > 0)
        {
            count--;
            Bar1(228, 280, 1024, 710, 0x9efc);
            drawchart(data, areakey, count); //画折线图
        }
        if (MousePress(500, 720, 550, 750) && count < 2)
        {
            count++;
            Bar1(228, 280, 1024, 710, 0x9efc);
            drawchart(data, areakey, count); //画折线图
        }

        if (MousePress(895, 0, 1019, 50)) //点击退出
        {
            return -1;
        }
        else if (MousePress(0, 0, 124, 50)) //点击返回
        {
            free(dd);
            return 5;
        }
    }
}
// 输出区域信息
void drawarea(int areakey)
{
    if (areakey == 0)
    {
        prt_hz24(790, 90, "已选中益民小区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 1)
    {
        prt_hz24(790, 90, "已选中北门小区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 2)
    {
        prt_hz24(790, 90, "已选中光明小区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 3)
    {
        prt_hz24(790, 90, "已选中桂园小区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 4)
    {
        prt_hz24(790, 90, "已选中南池小区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 5)
    {
        prt_hz24(790, 90, "已选中丽景小区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 6)
    {
        prt_hz24(790, 90, "已选中风韵荷都", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 7)
    {
        prt_hz24(790, 90, "已选中恒大名都", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 8)
    {
        prt_hz24(790, 90, "已选中古槐社区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 9)
    {
        prt_hz24(790, 90, "已选中仙营社区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 10)
    {
        prt_hz24(790, 90, "已选中南池社区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 11)
    {
        prt_hz24(790, 90, "已选中北湖社区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 12)
    {
        prt_hz24(790, 90, "已选中任城区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 13)
    {
        prt_hz24(790, 90, "已选中高新区", 0x0000, "HZK\\Hzk24k");
    }
    if (areakey == 14)
    {
        prt_hz24(790, 90, "已选中市", 0x0000, "HZK\\Hzk24k");
    }
}
